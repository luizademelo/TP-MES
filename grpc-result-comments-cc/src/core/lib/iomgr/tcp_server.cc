Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

#include "src/core/lib/iomgr/tcp_server.h"
#include <grpc/support/port_platform.h>

// Pointer to the implementation's virtual function table for TCP server operations
grpc_tcp_server_vtable* grpc_tcp_server_impl;

// Creates a new TCP server instance
// Parameters:
//   shutdown_complete: Closure to be called when server shutdown is complete
//   config: Endpoint configuration for the server
//   on_accept_cb: Callback to be invoked when a new connection is accepted
//   cb_arg: Argument to pass to the accept callback
//   server: Output parameter for the created server instance
// Returns: Error handle indicating success or failure
grpc_error_handle grpc_tcp_server_create(
    grpc_closure* shutdown_complete,
    const grpc_event_engine::experimental::EndpointConfig& config,
    grpc_tcp_server_cb on_accept_cb, void* cb_arg, grpc_tcp_server** server) {
  return grpc_tcp_server_impl->create(shutdown_complete, config, on_accept_cb,
                                      cb_arg, server);
}

// Starts the TCP server and begins accepting connections
// Parameters:
//   server: The TCP server instance to start
//   pollsets: Set of pollsets to use for connection handling
void grpc_tcp_server_start(grpc_tcp_server* server,
                           const std::vector<grpc_pollset*>* pollsets) {
  grpc_tcp_server_impl->start(server, pollsets);
}

// Adds a listening port to the TCP server
// Parameters:
//   s: The TCP server instance
//   addr: The address to bind to
//   out_port: Output parameter for the actual bound port (useful when requesting port 0)
// Returns: Error handle indicating success or failure
grpc_error_handle grpc_tcp_server_add_port(grpc_tcp_server* s,
                                           const grpc_resolved_address* addr,
                                           int* out_port) {
  return grpc_tcp_server_impl->add_port(s, addr, out_port);
}

// Creates a file descriptor handler for the TCP server
// Parameters:
//   s: The TCP server instance
// Returns: Pointer to the created file descriptor handler
grpc_core::TcpServerFdHandler* grpc_tcp_server_create_fd_handler(
    grpc_tcp_server* s) {
  return grpc_tcp_server_impl->create_fd_handler(s);
}

// Gets the number of file descriptors for a specific port
// Parameters:
//   s: The TCP server instance
//   port_index: Index of the port to query
// Returns: Number of file descriptors for the specified port
unsigned grpc_tcp_server_port_fd_count(grpc_tcp_server* s,
                                       unsigned port_index) {
  return grpc_tcp_server_impl->port_fd_count(s, port_index);
}

// Gets a specific file descriptor for a port
// Parameters:
//   s: The TCP server instance
//   port_index: Index of the port to query
//   fd_index: Index of the file descriptor within the port
// Returns: The requested file descriptor
int grpc_tcp_server_port_fd(grpc_tcp_server* s, unsigned port_index,
                            unsigned fd_index) {
  return grpc_tcp_server_impl->port_fd(s, port_index, fd_index);
}

// Increases the reference count of the TCP server
// Parameters:
//   s: The TCP server instance
// Returns: The same server instance (for chaining)
grpc_tcp_server* grpc_tcp_server_ref(grpc_tcp_server* s) {
  return grpc_tcp_server_impl->ref(s);
}

// Adds a closure to be called when server shutdown begins
// Parameters:
//   s: The TCP server instance
//   shutdown_starting: Closure to be called when shutdown begins
void grpc_tcp_server_shutdown_starting_add(grpc_tcp_server* s,
                                           grpc_closure* shutdown_starting) {
  grpc_tcp_server_impl->shutdown_starting_add(s, shutdown_starting);
}

// Decreases the reference count of the TCP server and destroys it if count reaches zero
// Parameters:
//   s: The TCP server instance
void grpc_tcp_server_unref(grpc_tcp_server* s) {
  grpc_tcp_server_impl->unref(s);
}

// Shuts down all listeners (stops accepting new connections)
// Parameters:
//   s: The TCP server instance
void grpc_tcp_server_shutdown_listeners(grpc_tcp_server* s) {
  grpc_tcp_server_impl->shutdown_listeners(s);
}

// Gets the pre-allocated file descriptor for the server
// Parameters:
//   s: The TCP server instance
// Returns: The pre-allocated file descriptor
int grpc_tcp_server_pre_allocated_fd(grpc_tcp_server* s) {
  return grpc_tcp_server_impl->pre_allocated_fd(s);
}

// Sets a pre-allocated file descriptor for the server
// Parameters:
//   s: The TCP server instance
//   fd: The file descriptor to set
void grpc_tcp_server_set_pre_allocated_fd(grpc_tcp_server* s, int fd) {
  grpc_tcp_server_impl->set_pre_allocated_fd(s, fd);
}

// Sets the implementation virtual function table for TCP server operations
// Parameters:
//   impl: Pointer to the implementation's virtual function table
void grpc_set_tcp_server_impl(grpc_tcp_server_vtable* impl) {
  grpc_tcp_server_impl = impl;
}
```