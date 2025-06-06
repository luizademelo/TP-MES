# gRPC Web

gRPC-Web provides a JS client library that supports the same API
as gRPC-Node to access a gRPC service. Due to browser limitation,
the Web client library implements a different protocol than the
[native gRPC protocol](PROTOCOL-HTTP2.md).
This protocol is designed to make it easy for a proxy to translate
between the protocols as this is the most likely deployment model.

This document lists the differences between the two protocols.
To help tracking future revisions, this document describes a delta
with the protocol details specified in the
[native gRPC protocol](PROTOCOL-HTTP2.md).

# Design goals

For the gRPC-Web protocol, we have decided on the following design goals:

* adopt the same framing as “application/grpc” whenever possible
* decouple from HTTP/2 framing which is not, and will never be, directly
exposed by browsers
* support text streams (e.g. base64) in order to provide cross-browser
support (e.g. IE-10)

While the new protocol will be published/reviewed publicly, we also
intend to keep the protocol as an internal detail to gRPC-Web.
More specifically, we expect the protocol to

* evolve over time, mainly to optimize for browser clients or support
web-specific features such as CORS, XSRF
* become optional (in 1-2 years) when browsers are able to speak the native
gRPC protocol via the new [whatwg streams API](https://github.com/whatwg/streams)

# Protocol differences vs [gRPC over HTTP2](PROTOCOL-HTTP2.md)

Content-Type

1. application/grpc-web
  * e.g. application/grpc-web+[proto, json, thrift]
  * the sender should always specify the message format, e.g. +proto, +json
  * the receiver should assume the default is "+proto" when the message format is missing in Content-Type (as "application/grpc-web")
2. application/grpc-web-text
  * text-encoded streams of “application/grpc-web”
  * e.g. application/grpc-web-text+[proto, thrift]

---

HTTP wire protocols

1. support any HTTP/*, with no dependency on HTTP/2 specific framing
2. header names may be upper- or mixed-case over HTTP/1.1, but trailers encoded in
   the last length-prefixed message must always use lower-case names.
3. use EOF (end of body) to close the stream

---

HTTP/2 related behavior (specified in [gRPC over HTTP2](PROTOCOL-HTTP2.md))

1. stream-id is not supported or used
2. go-away is not supported or used

---

Message framing (vs. [http2-transport-mapping](PROTOCOL-HTTP2.md#http2-transport-mapping))

1. Response status encoded as part of the response body
  * Key-value pairs encoded as a HTTP/1 headers block (without the terminating newline), per https://tools.ietf.org/html/rfc7230#section-3.2
  ```
    key1: foo\r\n
    key2: bar\r\n
  ```
2. 8th (MSB) bit of the 1st gRPC frame byte
  * 0: data
  * 1: trailers
  ```
    10000000b: an uncompressed trailer (as part of the body)
    10000001b: a compressed trailer
  ```
3. Trailers must be the last message of the response, as enforced
by the implementation
4. Trailers-only responses: no change to the gRPC protocol spec.
Trailers may be sent together with response headers, with no message
in the body.

---

User Agent

* Do NOT use User-Agent header (which is to be set by browsers, by default)
* Use X-User-Agent: grpc-web-javascript/0.1 (follow the same format as specified in [gRPC over HTTP2](PROTOCOL-HTTP2.md))

---

Text-encoded (response) streams

1. The client library should indicate to the server via the "Accept" header that
the response stream needs to be text encoded e.g. when XHR is used or due
to security policies with XHR
  * Accept: application/grpc-web-text
2. The default text encoding is base64
  * Note that “Content-Transfer-Encoding: base64” should not be used.
  Due to in-stream base64 padding when delimiting messages, the entire
  response body is not necessarily a valid base64-encoded entity
  * While the server runtime will always base64-encode and flush gRPC messages
  atomically the client library should not assume base64 padding always
  happens at the boundary of message frames. That is, the implementation may send base64-encoded "chunks" with potential padding whenever the runtime needs to flush a byte buffer.

# Other features

Retries, caching

* Will spec out the support after their respective gRPC spec extensions
are finalized
  * Safe retries: PUT
  * Caching: header encoded request and/or a web specific spec

---

Keep-alive

* HTTP/2 PING is not supported or used
* Will not support send-beacon (GET)

---

Bidi-streaming, with flow-control

* Pending on [whatwg fetch/streams](https://github.com/whatwg/fetch) to be
finalized and implemented in modern browsers
* gRPC-Web client will support the native gRPC protocol with modern browsers

---

Versioning

* Special headers may be introduced to support features that may break compatibility.

---

Browser-specific features

* For features that are unique to browser or HTML clients, check the [spec doc](https://github.com/grpc/grpc-web/blob/master/doc/browser-features.md) published in the grpc/grpc-web repo.
