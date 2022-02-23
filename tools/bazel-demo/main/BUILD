

load("@rules_cc//cc:defs.bzl", "cc_library")


cc_library(
    name="hello-lib",
    srcs=glob(["*.cpp"]),
    hdrs=glob(["*.h"]),

    deps=[
        "@com_github_gflags_gflags//:gflags",
        "@glog",
         #"@boost//:headers",
         "@boost_libs//:boost",
         "@boost//:headers",
    ],
    includes=[
        ".",
    ],

    linkopts=["-pthread"],


    copts=[
        "-DPINTEREST_INTERNAL",
        "-DBOOST_LOG_DYN_LINK",
        # "-Iexternal/home/ronghuang/work-local/boost/include/",
        #  "-Iexternal/usr/local/Cellar/folly/2022.01.10.00/include",
         "-Iexternal/boost",
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
