#pragma once

#include "source/common/singleton/const_singleton.h"
#include "source/extensions/common/aws/credentials_provider.h"
#include "source/extensions/common/aws/signer_base_impl.h"

namespace Envoy {
namespace Extensions {
namespace Common {
namespace Aws {

using SigV4SignatureHeaders = ConstSingleton<SignatureHeaderValues>;

class SigV4SignatureConstants : public SignatureConstants {
public:
  static constexpr absl::string_view SigV4AuthorizationHeaderFormat{
      "{} Credential={}, SignedHeaders={}, Signature={}"};
  static constexpr absl::string_view SigV4CredentialScopeFormat{"{}/{}/{}/aws4_request"};
  static constexpr absl::string_view SigV4SignatureVersion{"AWS4"};
  static constexpr absl::string_view SigV4StringToSignFormat{"{}\n{}\n{}\n{}"};
  static constexpr absl::string_view SigV4Algorithm{"AWS4-HMAC-SHA256"};
};

using AwsSigningHeaderExclusionVector = std::vector<envoy::type::matcher::v3::StringMatcher>;

/**
 * Implementation of the Signature V4 signing process.
 * See https://docs.aws.amazon.com/general/latest/gr/signature-version-4.html
 *
 * Query parameter support is implemented as per:
 * https://docs.aws.amazon.com/AmazonS3/latest/API/sigv4-query-string-auth.html
 */
class SigV4SignerImpl : public SignerBaseImpl {

  // Allow friend access for signer corpus testing
  friend class SigV4SignerImplFriend;

public:
  SigV4SignerImpl(absl::string_view service_name, absl::string_view region,
                  const CredentialsProviderChainSharedPtr& credentials_provider,
                  Server::Configuration::CommonFactoryContext& context,
                  const AwsSigningHeaderExclusionVector& matcher_config,
                  const bool query_string = false,
                  const uint16_t expiration_time = SignatureQueryParameterValues::DefaultExpiration)
      : SignerBaseImpl(service_name, region, credentials_provider, context, matcher_config,
                       query_string, expiration_time) {}

private:
  std::string createCredentialScope(const absl::string_view short_date,
                                    const absl::string_view override_region) const override;

  std::string createStringToSign(const absl::string_view canonical_request,
                                 const absl::string_view long_date,
                                 const absl::string_view credential_scope) const override;

  std::string createSignature(ABSL_ATTRIBUTE_UNUSED const absl::string_view access_key_id,
                              const absl::string_view secret_access_key,
                              const absl::string_view short_date,
                              const absl::string_view string_to_sign,
                              const absl::string_view override_region) const override;

  std::string createAuthorizationHeader(const absl::string_view access_key_id,
                                        const absl::string_view credential_scope,
                                        const std::map<std::string, std::string>& canonical_headers,
                                        const absl::string_view signature) const override;

  absl::string_view getAlgorithmString() const override;
};

} // namespace Aws
} // namespace Common
} // namespace Extensions
} // namespace Envoy
