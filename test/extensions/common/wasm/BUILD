load(
    "//bazel:envoy_build_system.bzl",
    "envoy_cc_test",
    "envoy_cc_test_binary",
    "envoy_cc_test_library",
    "envoy_package",
)
load(
    "//bazel:envoy_select.bzl",
    "envoy_select_wasm_cpp_tests",
    "envoy_select_wasm_rust_tests",
)

licenses(["notice"])  # Apache 2

envoy_package()

envoy_cc_test(
    name = "wasm_vm_test",
    srcs = ["wasm_vm_test.cc"],
    data = envoy_select_wasm_rust_tests([
        "//test/extensions/common/wasm/test_data:test_rust.wasm",
    ]),
    rbe_pool = "6gig",
    tags = ["skip_on_windows"],
    deps = [
        "//source/extensions/common/wasm:wasm_lib",
        "//test/extensions/common/wasm:wasm_runtime",
        "//test/test_common:environment_lib",
        "//test/test_common:registry_lib",
        "//test/test_common:utility_lib",
    ],
)

envoy_cc_test(
    name = "wasm_test",
    size = "large",
    srcs = ["wasm_test.cc"],
    data = envoy_select_wasm_cpp_tests([
        "//test/extensions/common/wasm/test_data:bad_signature_cpp.wasm",
        "//test/extensions/common/wasm/test_data:test_context_cpp.wasm",
        "//test/extensions/common/wasm/test_data:test_cpp.wasm",
        "//test/extensions/common/wasm/test_data:test_restriction_cpp.wasm",
    ]),
    rbe_pool = "4core",
    tags = ["skip_on_windows"],
    deps = [
        "//source/common/common:base64_lib",
        "//source/common/common:hex_lib",
        "//source/common/crypto:utility_lib",
        "//source/common/event:dispatcher_lib",
        "//source/common/stats:isolated_store_lib",
        "//source/common/stats:stats_lib",
        "//source/extensions/common/wasm:wasm_lib",
        "//test/extensions/common/wasm:wasm_runtime",
        "//test/extensions/common/wasm/test_data:test_context_cpp_plugin",
        "//test/extensions/common/wasm/test_data:test_cpp_plugin",
        "//test/extensions/common/wasm/test_data:test_restriction_cpp_plugin",
        "//test/mocks/local_reply:local_reply_mocks",
        "//test/mocks/server:server_mocks",
        "//test/test_common:environment_lib",
        "//test/test_common:registry_lib",
        "//test/test_common:simulated_time_system_lib",
        "//test/test_common:test_runtime_lib",
        "//test/test_common:wasm_lib",
        "@com_google_absl//absl/types:optional",
    ],
)

envoy_cc_test(
    name = "plugin_test",
    srcs = ["plugin_test.cc"],
    rbe_pool = "6gig",
    tags = ["skip_on_windows"],
    deps = [
        "//source/extensions/common/wasm:wasm_lib",
        "//test/test_common:environment_lib",
    ],
)

envoy_cc_test_binary(
    name = "wasm_speed_test",
    srcs = ["wasm_speed_test.cc"],
    rbe_pool = "6gig",
    tags = ["skip_on_windows"],
    deps = [
        "//source/common/event:dispatcher_lib",
        "//source/extensions/common/wasm:wasm_lib",
        "//test/extensions/common/wasm:wasm_runtime",
        "//test/mocks/server:server_mocks",
        "//test/mocks/upstream:upstream_mocks",
        "//test/test_common:environment_lib",
        "@com_github_google_benchmark//:benchmark",
        "@com_google_absl//absl/types:optional",
    ],
)

envoy_cc_test_library(
    name = "wasm_runtime",
    srcs = ["wasm_runtime.cc"],
    hdrs = ["wasm_runtime.h"],
    tags = ["skip_on_windows"],
    deps = [
        "//envoy/http:codec_interface",
        "//source/extensions/wasm_runtime/null:config",
        "//source/extensions/wasm_runtime/v8:config",
        "//source/extensions/wasm_runtime/wamr:config",
        "//source/extensions/wasm_runtime/wasmtime:config",
    ],
)

envoy_cc_test(
    name = "wasm_runtime_factory_test",
    srcs = ["wasm_runtime_factory_test.cc"],
    rbe_pool = "6gig",
    tags = ["skip_on_windows"],
    deps = [
        "//envoy/registry",
        "//source/extensions/common/wasm:wasm_runtime_factory_interface",
        "//test/test_common:environment_lib",
    ],
)

envoy_cc_test(
    name = "context_test",
    srcs = ["context_test.cc"],
    rbe_pool = "6gig",
    tags = ["skip_on_windows"],
    deps = [
        "//envoy/common:base_includes",
        "//source/extensions/common/wasm:wasm_lib",
        "//test/mocks/http:http_mocks",
        "//test/mocks/network:network_mocks",
        "//test/mocks/stream_info:stream_info_mocks",
        "//test/test_common:test_runtime_lib",
    ],
)

envoy_cc_test(
    name = "foreign_test",
    srcs = ["foreign_test.cc"],
    copts = select({
        "//bazel:windows_x86_64": [],  # TODO: fix the windows ANTLR build
        "//conditions:default": [
            "-DWASM_USE_CEL_PARSER",
        ],
    }),
    data = envoy_select_wasm_cpp_tests([
        "//test/extensions/common/wasm/test_data:test_context_cpp.wasm",
    ]),
    rbe_pool = "6gig",
    tags = ["skip_on_windows"],
    deps = [
        ":wasm_runtime",
        "//source/common/network:filter_state_dst_address_lib",
        "//source/common/tcp_proxy",
        "//source/extensions/clusters/original_dst:original_dst_cluster_lib",
        "//source/extensions/common/wasm:wasm_hdr",
        "//source/extensions/common/wasm:wasm_lib",
        "//test/extensions/common/wasm/test_data:test_context_cpp_plugin",
        "//test/mocks/http:http_mocks",
        "//test/mocks/local_info:local_info_mocks",
        "//test/mocks/network:network_mocks",
        "//test/mocks/upstream:upstream_mocks",
        "//test/test_common:environment_lib",
        "//test/test_common:wasm_lib",
        "@proxy_wasm_cpp_host//:base_lib",
    ],
)

envoy_cc_test(
    name = "remote_async_datasource_test",
    srcs = ["remote_async_datasource_test.cc"],
    rbe_pool = "6gig",
    deps = [
        "//source/common/common:empty_string",
        "//source/common/crypto:utility_lib",
        "//source/common/http:message_lib",
        "//source/common/protobuf:utility_lib",
        "//source/extensions/common/wasm:remote_async_datasource_lib",
        "//test/mocks/event:event_mocks",
        "//test/mocks/init:init_mocks",
        "//test/mocks/runtime:runtime_mocks",
        "//test/mocks/upstream:cluster_manager_mocks",
        "//test/test_common:utility_lib",
        "@envoy_api//envoy/config/core/v3:pkg_cc_proto",
    ],
)
