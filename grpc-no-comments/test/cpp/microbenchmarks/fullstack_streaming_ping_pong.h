
// Copyright 2016 gRPC authors.

#ifndef GRPC_TEST_CPP_MICROBENCHMARKS_FULLSTACK_STREAMING_PING_PONG_H
#define GRPC_TEST_CPP_MICROBENCHMARKS_FULLSTACK_STREAMING_PING_PONG_H

#include <benchmark/benchmark.h>

#include <sstream>

#include "absl/log/check.h"
#include "src/proto/grpc/testing/echo.grpc.pb.h"
#include "test/cpp/microbenchmarks/fullstack_context_mutators.h"
#include "test/cpp/microbenchmarks/fullstack_fixtures.h"

namespace grpc {
namespace testing {

static void* tag(intptr_t x) { return reinterpret_cast<void*>(x); }

//      Note: One ping-pong means two messages (one from client to server and

template <class Fixture, class ClientContextMutator, class ServerContextMutator>
static void BM_StreamingPingPong(benchmark::State& state) {
  const int msg_size = state.range(0);
  const int max_ping_pongs = state.range(1);

  EchoTestService::AsyncService service;
  std::unique_ptr<Fixture> fixture(new Fixture(&service));
  {
    EchoResponse send_response;
    EchoResponse recv_response;
    EchoRequest send_request;
    EchoRequest recv_request;

    if (msg_size > 0) {
      send_request.set_message(std::string(msg_size, 'a'));
      send_response.set_message(std::string(msg_size, 'b'));
    }

    std::unique_ptr<EchoTestService::Stub> stub(
        EchoTestService::NewStub(fixture->channel()));

    for (auto _ : state) {
      ServerContext svr_ctx;
      ServerContextMutator svr_ctx_mut(&svr_ctx);
      ServerAsyncReaderWriter<EchoResponse, EchoRequest> response_rw(&svr_ctx);
      service.RequestBidiStream(&svr_ctx, &response_rw, fixture->cq(),
                                fixture->cq(), tag(0));

      ClientContext cli_ctx;
      ClientContextMutator cli_ctx_mut(&cli_ctx);
      auto request_rw = stub->AsyncBidiStream(&cli_ctx, fixture->cq(), tag(1));

      void* t;
      bool ok;
      int need_tags = (1 << 0) | (1 << 1);
      while (need_tags) {
        CHECK(fixture->cq()->Next(&t, &ok));
        CHECK(ok);
        int i = static_cast<int>(reinterpret_cast<intptr_t>(t));
        CHECK(need_tags & (1 << i));
        need_tags &= ~(1 << i);
      }

      int ping_pong_cnt = 0;
      while (ping_pong_cnt < max_ping_pongs) {
        request_rw->Write(send_request, tag(0));
        response_rw.Read(&recv_request, tag(1));
        request_rw->Read(&recv_response, tag(2));

        need_tags = (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);
        while (need_tags) {
          CHECK(fixture->cq()->Next(&t, &ok));
          CHECK(ok);
          int i = static_cast<int>(reinterpret_cast<intptr_t>(t));

          if (i == 1) {
            response_rw.Write(send_response, tag(3));
          }

          CHECK(need_tags & (1 << i));
          need_tags &= ~(1 << i);
        }

        ping_pong_cnt++;
      }

      request_rw->WritesDone(tag(0));
      response_rw.Finish(Status::OK, tag(1));

      Status recv_status;
      request_rw->Finish(&recv_status, tag(2));

      need_tags = (1 << 0) | (1 << 1) | (1 << 2);
      while (need_tags) {
        CHECK(fixture->cq()->Next(&t, &ok));
        int i = static_cast<int>(reinterpret_cast<intptr_t>(t));
        CHECK(need_tags & (1 << i));
        need_tags &= ~(1 << i);
      }

      CHECK(recv_status.ok());
    }
  }

  fixture.reset();
  state.SetBytesProcessed(msg_size * state.iterations() * max_ping_pongs * 2);
}

template <class Fixture, class ClientContextMutator, class ServerContextMutator>
static void BM_StreamingPingPongMsgs(benchmark::State& state) {
  const int msg_size = state.range(0);

  EchoTestService::AsyncService service;
  std::unique_ptr<Fixture> fixture(new Fixture(&service));
  {
    EchoResponse send_response;
    EchoResponse recv_response;
    EchoRequest send_request;
    EchoRequest recv_request;

    if (msg_size > 0) {
      send_request.set_message(std::string(msg_size, 'a'));
      send_response.set_message(std::string(msg_size, 'b'));
    }

    std::unique_ptr<EchoTestService::Stub> stub(
        EchoTestService::NewStub(fixture->channel()));

    ServerContext svr_ctx;
    ServerContextMutator svr_ctx_mut(&svr_ctx);
    ServerAsyncReaderWriter<EchoResponse, EchoRequest> response_rw(&svr_ctx);
    service.RequestBidiStream(&svr_ctx, &response_rw, fixture->cq(),
                              fixture->cq(), tag(0));

    ClientContext cli_ctx;
    ClientContextMutator cli_ctx_mut(&cli_ctx);
    auto request_rw = stub->AsyncBidiStream(&cli_ctx, fixture->cq(), tag(1));

    void* t;
    bool ok;
    int need_tags = (1 << 0) | (1 << 1);
    while (need_tags) {
      CHECK(fixture->cq()->Next(&t, &ok));
      CHECK(ok);
      int i = static_cast<int>(reinterpret_cast<intptr_t>(t));
      CHECK(need_tags & (1 << i));
      need_tags &= ~(1 << i);
    }

    for (auto _ : state) {
      request_rw->Write(send_request, tag(0));
      response_rw.Read(&recv_request, tag(1));
      request_rw->Read(&recv_response, tag(2));

      need_tags = (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);
      while (need_tags) {
        CHECK(fixture->cq()->Next(&t, &ok));
        CHECK(ok);
        int i = static_cast<int>(reinterpret_cast<intptr_t>(t));

        if (i == 1) {
          response_rw.Write(send_response, tag(3));
        }

        CHECK(need_tags & (1 << i));
        need_tags &= ~(1 << i);
      }
    }

    request_rw->WritesDone(tag(0));
    response_rw.Finish(Status::OK, tag(1));
    Status recv_status;
    request_rw->Finish(&recv_status, tag(2));

    need_tags = (1 << 0) | (1 << 1) | (1 << 2);
    while (need_tags) {
      CHECK(fixture->cq()->Next(&t, &ok));
      int i = static_cast<int>(reinterpret_cast<intptr_t>(t));
      CHECK(need_tags & (1 << i));
      need_tags &= ~(1 << i);
    }

    CHECK(recv_status.ok());
  }

  fixture.reset();
  state.SetBytesProcessed(msg_size * state.iterations() * 2);
}

//      Note: One ping-pong means two messages (one from client to server and

template <class Fixture, class ClientContextMutator, class ServerContextMutator>
static void BM_StreamingPingPongWithCoalescingApi(benchmark::State& state) {
  const int msg_size = state.range(0);
  const int max_ping_pongs = state.range(1);

  const int write_and_finish = state.range(2);

  EchoTestService::AsyncService service;
  std::unique_ptr<Fixture> fixture(new Fixture(&service));
  {
    EchoResponse send_response;
    EchoResponse recv_response;
    EchoRequest send_request;
    EchoRequest recv_request;

    if (msg_size > 0) {
      send_request.set_message(std::string(msg_size, 'a'));
      send_response.set_message(std::string(msg_size, 'b'));
    }

    std::unique_ptr<EchoTestService::Stub> stub(
        EchoTestService::NewStub(fixture->channel()));

    for (auto _ : state) {
      ServerContext svr_ctx;
      ServerContextMutator svr_ctx_mut(&svr_ctx);
      ServerAsyncReaderWriter<EchoResponse, EchoRequest> response_rw(&svr_ctx);
      service.RequestBidiStream(&svr_ctx, &response_rw, fixture->cq(),
                                fixture->cq(), tag(0));

      ClientContext cli_ctx;
      ClientContextMutator cli_ctx_mut(&cli_ctx);
      cli_ctx.set_initial_metadata_corked(true);

      auto request_rw = stub->AsyncBidiStream(&cli_ctx, fixture->cq(), tag(1));

      void* t;
      bool ok;
      int expect_tags = 0;

      int ping_pong_cnt = 0;
      while (ping_pong_cnt < max_ping_pongs) {
        if (ping_pong_cnt == max_ping_pongs - 1) {
          request_rw->WriteLast(send_request, WriteOptions(), tag(2));
        } else {
          request_rw->Write(send_request, tag(2));
        }

        int await_tags = (1 << 2);

        if (ping_pong_cnt == 0) {

          CHECK(fixture->cq()->Next(&t, &ok));
          while (static_cast<int>(reinterpret_cast<intptr_t>(t)) != 0) {

            int i = static_cast<int>(reinterpret_cast<intptr_t>(t));
            CHECK(await_tags & (1 << i));
            await_tags &= ~(1 << i);
            CHECK(fixture->cq()->Next(&t, &ok));
          }
        }

        response_rw.Read(&recv_request, tag(3));
        request_rw->Read(&recv_response, tag(4));

        await_tags |= (1 << 3) | (1 << 4);
        expect_tags = await_tags;
        await_tags |= (1 << 5);

        while (await_tags != 0) {
          CHECK(fixture->cq()->Next(&t, &ok));
          CHECK(ok);
          int i = static_cast<int>(reinterpret_cast<intptr_t>(t));

          if (i == 3) {
            if (ping_pong_cnt == max_ping_pongs - 1) {
              if (write_and_finish == 1) {
                response_rw.WriteAndFinish(send_response, WriteOptions(),
                                           Status::OK, tag(5));
                expect_tags |= (1 << 5);
              } else {
                response_rw.WriteLast(send_response, WriteOptions(), tag(5));

                await_tags &= ~(1 << 4);
                await_tags &= ~(1 << 5);
                expect_tags |= (1 << 5);
              }
            } else {
              response_rw.Write(send_response, tag(5));
              expect_tags |= (1 << 5);
            }
          }

          CHECK(expect_tags & (1 << i));
          expect_tags &= ~(1 << i);
          await_tags &= ~(1 << i);
        }

        ping_pong_cnt++;
      }

      if (max_ping_pongs == 0) {
        expect_tags |= (1 << 6) | (1 << 7) | (1 << 8);
      } else {
        if (write_and_finish == 1) {
          expect_tags |= (1 << 8);
        } else {

          expect_tags |= (1 << 7) | (1 << 8);
        }
      }

      if (max_ping_pongs == 0) {
        request_rw->WritesDone(tag(6));

        CHECK(fixture->cq()->Next(&t, &ok));
        while (static_cast<int>(reinterpret_cast<intptr_t>(t)) != 0) {
          int i = static_cast<int>(reinterpret_cast<intptr_t>(t));
          CHECK(expect_tags & (1 << i));
          expect_tags &= ~(1 << i);
          CHECK(fixture->cq()->Next(&t, &ok));
        }
        response_rw.Finish(Status::OK, tag(7));
      } else {
        if (write_and_finish != 1) {
          response_rw.Finish(Status::OK, tag(7));
        }
      }

      Status recv_status;
      request_rw->Finish(&recv_status, tag(8));

      while (expect_tags) {
        CHECK(fixture->cq()->Next(&t, &ok));
        int i = static_cast<int>(reinterpret_cast<intptr_t>(t));
        CHECK(expect_tags & (1 << i));
        expect_tags &= ~(1 << i);
      }

      CHECK(recv_status.ok());
    }
  }

  fixture.reset();
  state.SetBytesProcessed(msg_size * state.iterations() * max_ping_pongs * 2);
}
}
}

#endif
