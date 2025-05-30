#!/usr/bin/env python3
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Manage TCP ports for unit tests; started by run_tests.py"""

from __future__ import print_function

import argparse
import hashlib
import os
import platform
import random
import socket
import sys
import threading
import time

from six.moves.BaseHTTPServer import BaseHTTPRequestHandler
from six.moves.BaseHTTPServer import HTTPServer
from six.moves.socketserver import ThreadingMixIn

_MY_VERSION = 21

if len(sys.argv) == 2 and sys.argv[1] == "dump_version":
    print(_MY_VERSION)
    sys.exit(0)

argp = argparse.ArgumentParser(description="Server for httpcli_test")
argp.add_argument("-p", "--port", default=12345, type=int)
argp.add_argument("-l", "--logfile", default=None, type=str)
args = argp.parse_args()

if args.logfile is not None:
    sys.stdin.close()
    sys.stderr.close()
    sys.stdout.close()
    sys.stderr = open(args.logfile, "w")
    sys.stdout = sys.stderr

print("port server running on port %d" % args.port)

pool = []
in_use = {}
mu = threading.Lock()

def can_connect(port):

    if platform.system() == "Windows":
        return False
    s = socket.socket()
    try:
        s.connect(("localhost", port))
        return True
    except socket.error as e:
        return False
    finally:
        s.close()

def can_bind(port, proto):
    s = socket.socket(proto, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    try:
        s.bind(("localhost", port))
        return True
    except socket.error as e:
        return False
    finally:
        s.close()

def refill_pool(max_timeout, req):
    """Scan for ports not marked for being in use"""
    chk = [port for port in range(1025, 32766)]
    random.shuffle(chk)
    for i in chk:
        if len(pool) > 100:
            break
        if i in in_use:
            age = time.time() - in_use[i]
            if age < max_timeout:
                continue
            req.log_message("kill old request %d" % i)
            del in_use[i]
        if (
            can_bind(i, socket.AF_INET)
            and can_bind(i, socket.AF_INET6)
            and not can_connect(i)
        ):
            req.log_message("found available port %d" % i)
            pool.append(i)

def allocate_port(req):
    global pool
    global in_use
    global mu
    mu.acquire()
    max_timeout = 600
    while not pool:
        refill_pool(max_timeout, req)
        if not pool:
            req.log_message("failed to find ports: retrying soon")
            mu.release()
            time.sleep(1)
            mu.acquire()
            max_timeout /= 2
    port = pool[0]
    pool = pool[1:]
    in_use[port] = time.time()
    mu.release()
    return port

keep_running = True

class Handler(BaseHTTPRequestHandler):
    def setup(self):

        self.timeout = 5
        BaseHTTPRequestHandler.setup(self)

    def do_GET(self):
        global keep_running
        global mu
        if self.path == "/get":

            self.send_response(200)
            self.send_header("Content-Type", "text/plain")
            self.end_headers()
            p = allocate_port(self)
            self.log_message("allocated port %d" % p)
            self.wfile.write(str(p).encode("ascii"))
        elif self.path[0:6] == "/drop/":
            self.send_response(200)
            self.send_header("Content-Type", "text/plain")
            self.end_headers()
            p = int(self.path[6:])
            mu.acquire()
            if p in in_use:
                del in_use[p]
                pool.append(p)
                k = "known"
            else:
                k = "unknown"
            mu.release()
            self.log_message("drop %s port %d" % (k, p))
        elif self.path == "/version_number":

            self.send_response(200)
            self.send_header("Content-Type", "text/plain")
            self.end_headers()
            self.wfile.write(str(_MY_VERSION).encode("ascii"))
        elif self.path == "/dump":

            import yaml

            self.send_response(200)
            self.send_header("Content-Type", "text/plain")
            self.end_headers()
            mu.acquire()
            now = time.time()
            out = yaml.dump(
                {
                    "pool": pool,
                    "in_use": dict(
                        (k, now - v) for k, v in list(in_use.items())
                    ),
                }
            )
            mu.release()
            self.wfile.write(out.encode("ascii"))
        elif self.path == "/quitquitquit":
            self.send_response(200)
            self.end_headers()
            self.server.shutdown()

class ThreadedHTTPServer(ThreadingMixIn, HTTPServer):
    """Handle requests in a separate thread"""

ThreadedHTTPServer(("", args.port), Handler).serve_forever()
