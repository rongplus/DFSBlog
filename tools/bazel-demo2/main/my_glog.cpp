#include "my_glog.h"
#include <iostream>

#include <glog/logging.h>
void glog_test() {
  // Initialize Google's logging library.
  std::cout << __func__ << std::endl;
  FLAGS_logtostderr = false;
  FLAGS_log_dir = "/Users/ronghuang/work/log/";
  google::InitGoogleLogging("my_glog");
  google::SetLogDestination(google::GLOG_INFO, "/Users/ronghuang/work/log/");

  google::SetStderrLogging(google::GLOG_INFO);
  google::SetLogFilenameExtension("log_");
  // google::InitGoogleLogging(argv[0]);
  FLAGS_colorlogtostderr = true;          // Set log color
  FLAGS_logbufsecs = 0;                   // Set log output speed(s)
  FLAGS_max_log_size = 1024;              // Set max log file size
  FLAGS_stop_logging_if_full_disk = true; // If disk is full

  int num_cookies = 100;
  // ...
  LOG(INFO) << "Found " << num_cookies << " cookies";
  DLOG(INFO) << "Found cookies";

  DLOG_IF(INFO, num_cookies > 10) << "Got lots of cookies";

  DLOG_EVERY_N(INFO, 10) << "Got the " << google::COUNTER << "th cookie";

  LOG(INFO) << "info test";       //输出一个Info日志
  LOG(WARNING) << "warning test"; //输出一个Warning日志
  LOG(ERROR) << "error test";     //输出一个Error日志
  // LOG(FATAL) << "fatal test";     // this will end the program
  //输出一个Fatal日志，这是最严重的日志并且输出之后会中止程序

  google::ShutdownGoogleLogging();
}