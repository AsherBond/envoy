load(
    "//bazel:envoy_build_system.bzl",
    "envoy_cc_mock",
    "envoy_cc_test",
    "envoy_package",
)

licenses(["notice"])  # Apache 2

envoy_package()

envoy_cc_test(
    name = "check_request_utils_test",
    srcs = ["check_request_utils_test.cc"],
    rbe_pool = "6gig",
    deps = [
        "//source/common/network:address_lib",
        "//source/common/protobuf",
        "//source/extensions/filters/common/ext_authz:check_request_utils_lib",
        "//source/extensions/filters/common/ext_authz:ext_authz_interface",
        "//test/mocks/http:http_mocks",
        "//test/mocks/network:network_mocks",
        "//test/mocks/server:server_factory_context_mocks",
        "//test/mocks/ssl:ssl_mocks",
        "//test/mocks/stream_info:stream_info_mocks",
        "//test/test_common:utility_lib",
        "@envoy_api//envoy/config/core/v3:pkg_cc_proto",
        "@envoy_api//envoy/extensions/filters/http/ext_authz/v3:pkg_cc_proto",
        "@envoy_api//envoy/service/auth/v3:pkg_cc_proto",
    ],
)

envoy_cc_test(
    name = "ext_authz_grpc_impl_test",
    srcs = ["ext_authz_grpc_impl_test.cc"],
    rbe_pool = "6gig",
    deps = [
        "//source/extensions/filters/common/ext_authz:ext_authz_grpc_lib",
        "//test/extensions/filters/common/ext_authz:ext_authz_test_common",
        "//test/mocks/tracing:tracing_mocks",
        "@envoy_api//envoy/service/auth/v3:pkg_cc_proto",
        "@envoy_api//envoy/type/v3:pkg_cc_proto",
    ],
)

envoy_cc_test(
    name = "ext_authz_http_impl_test",
    srcs = ["ext_authz_http_impl_test.cc"],
    rbe_pool = "6gig",
    deps = [
        "//source/common/formatter:formatter_extension_lib",
        "//source/extensions/filters/common/ext_authz:ext_authz_http_lib",
        "//test/extensions/filters/common/ext_authz:ext_authz_test_common",
        "//test/mocks/server:server_factory_context_mocks",
        "//test/mocks/stream_info:stream_info_mocks",
        "//test/mocks/upstream:cluster_manager_mocks",
        "@envoy_api//envoy/extensions/filters/http/ext_authz/v3:pkg_cc_proto",
        "@envoy_api//envoy/service/auth/v3:pkg_cc_proto",
    ],
)

envoy_cc_mock(
    name = "ext_authz_mocks",
    srcs = ["mocks.cc"],
    hdrs = ["mocks.h"],
    deps = [
        "//source/extensions/filters/common/ext_authz:ext_authz_interface",
        "@envoy_api//envoy/service/auth/v3:pkg_cc_proto",
    ],
)

envoy_cc_mock(
    name = "ext_authz_test_common",
    srcs = ["test_common.cc"],
    hdrs = ["test_common.h"],
    deps = [
        "//source/common/http:headers_lib",
        "//source/common/protobuf",
        "//source/extensions/filters/common/ext_authz:ext_authz_grpc_lib",
        "//test/extensions/filters/common/ext_authz:ext_authz_mocks",
        "//test/mocks/grpc:grpc_mocks",
        "//test/test_common:utility_lib",
        "@envoy_api//envoy/config/core/v3:pkg_cc_proto",
        "@envoy_api//envoy/service/auth/v3:pkg_cc_proto",
        "@envoy_api//envoy/type/v3:pkg_cc_proto",
    ],
)
