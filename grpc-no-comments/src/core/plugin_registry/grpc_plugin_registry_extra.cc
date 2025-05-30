
// Copyright 2021 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>

#include "src/core/config/core_configuration.h"

namespace grpc_core {
#ifndef GRPC_NO_XDS
extern void RbacFilterRegister(CoreConfiguration::Builder* builder);
extern void StatefulSessionFilterRegister(CoreConfiguration::Builder* builder);
extern void GcpAuthenticationFilterRegister(
    CoreConfiguration::Builder* builder);
extern void RegisterXdsChannelStackModifier(
    CoreConfiguration::Builder* builder);
extern void RegisterChannelDefaultCreds(CoreConfiguration::Builder* builder);
extern void RegisterXdsResolver(CoreConfiguration::Builder* builder);
extern void RegisterCloud2ProdResolver(CoreConfiguration::Builder* builder);
extern void RegisterXdsClusterManagerLbPolicy(
    CoreConfiguration::Builder* builder);
extern void RegisterXdsClusterImplLbPolicy(CoreConfiguration::Builder* builder);
extern void RegisterCdsLbPolicy(CoreConfiguration::Builder* builder);
extern void RegisterXdsOverrideHostLbPolicy(
    CoreConfiguration::Builder* builder);
extern void RegisterXdsWrrLocalityLbPolicy(CoreConfiguration::Builder* builder);
extern void RegisterFileWatcherCertificateProvider(
    CoreConfiguration::Builder* builder);
extern void RegisterXdsHttpProxyMapper(CoreConfiguration::Builder* builder);
#endif
void RegisterExtraFilters(CoreConfiguration::Builder* builder) {

  (void)builder;
#ifndef GRPC_NO_XDS

  RbacFilterRegister(builder);
  StatefulSessionFilterRegister(builder);
  GcpAuthenticationFilterRegister(builder);
  RegisterXdsChannelStackModifier(builder);
  RegisterChannelDefaultCreds(builder);
  RegisterXdsResolver(builder);
  RegisterCloud2ProdResolver(builder);
  RegisterXdsClusterManagerLbPolicy(builder);
  RegisterXdsClusterImplLbPolicy(builder);
  RegisterCdsLbPolicy(builder);
  RegisterXdsOverrideHostLbPolicy(builder);
  RegisterXdsWrrLocalityLbPolicy(builder);
  RegisterFileWatcherCertificateProvider(builder);
  RegisterXdsHttpProxyMapper(builder);
#endif
}
}
