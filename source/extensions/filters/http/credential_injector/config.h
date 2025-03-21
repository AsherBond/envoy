#pragma once

#include "envoy/extensions/filters/http/credential_injector/v3/credential_injector.pb.h"
#include "envoy/extensions/filters/http/credential_injector/v3/credential_injector.pb.validate.h"

#include "source/extensions/filters/http/common/factory_base.h"

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace CredentialInjector {

class CredentialInjectorFilterFactory
    : public Common::DualFactoryBase<
          envoy::extensions::filters::http::credential_injector::v3::CredentialInjector> {
public:
  CredentialInjectorFilterFactory() : DualFactoryBase("envoy.filters.http.credential_injector") {}

private:
  absl::StatusOr<Http::FilterFactoryCb> createFilterFactoryFromProtoTyped(
      const envoy::extensions::filters::http::credential_injector::v3::CredentialInjector& config,
      const std::string& stats_prefix, DualInfo dual_info,
      Server::Configuration::ServerFactoryContext& context) override;
};

using UpstreamCredentialInjectorFilterFactory = CredentialInjectorFilterFactory;

} // namespace CredentialInjector
} // namespace HttpFilters
} // namespace Extensions
} // namespace Envoy
