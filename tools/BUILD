

load("@rules_cc//cc:defs.bzl", "cc_library")


cc_library(
    name="hello-lib",
    srcs=glob(["*.cpp"]),
    hdrs=glob(["*.h"]),

    deps=[
        "@com_github_gflags_gflags//:gflags",
        "@glog",
         #"@usr//:headers",
         #"@folly_libs//:folly",
        # "@system_libs//:x11",
    ],
    includes=[
        ".",
    ],

    linkopts=["-pthread"],


    copts=[
        "-DPINTEREST_INTERNAL",
        "-DBOOST_LOG_DYN_LINK",      
    ],
    visibility=["//main:__pkg__"],
)

cc_binary(
    name="hello-bazel",
    srcs=["goku_s.cpp"],
    deps=[
        ":hello-lib",
    ],
    linkopts=["-pthread"],
)
