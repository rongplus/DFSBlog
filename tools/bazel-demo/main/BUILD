

load("@rules_cc//cc:defs.bzl", "cc_library")

filegroup(
    name = "srcs",
    srcs = glob([
        "*.cpp",
        "*.h",
    ]),
)
cc_library(
  name = "myfolly",
  hdrs = glob(["include/**"]),
  srcs = [
    "lib64/folly.so",
  ],
  includes = [
    "folly",
    "boost",
  ],
  visibility = ["//visibility:public"],
)

cc_library(
    name = "hello-lib",
    srcs = glob([ "*.cpp"]),
    hdrs = glob([ "*.h"]),

    deps = [
        "@com_github_gflags_gflags//:gflags",
        "@glog",
        "@myfolly//:headers",
       
     
    ],
    includes = [
        ".",
    ],

    linkopts=["-pthread"],

 
     copts = [
        "-DPINTEREST_INTERNAL",
        "-DBOOST_LOG_DYN_LINK",
        "-Iexternal/usr/local/include",
        "-Iexternal/usr/local/Cellar/folly/2022.01.10.00/include",
         "-Iexternal/myfolly",
     ],
     visibility = ["//main:__pkg__"],
)

cc_binary(
    name = "hello-goku",
    srcs = ["goku_s.cpp"],
    deps = [
        ":hello-lib",
    ],
)


cc_import(
  name = "folly",
  
  static_library = "libfollylib.a",
  shared_library = "libfollylib.so",
)