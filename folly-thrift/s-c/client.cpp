// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.
// g++ Server.cpp gen-cpp/test_types.cpp -lthrift  -std=c++14 -o test
// g++ Server.cpp gen-cpp/test_types.cpp -lthrift  -std=c++14 -o test
// -L/Users/ronghuang/work/3rd_lib/boost/lib -lboost_log_setup -lboost_log
//-lpthread -lboost_log-mt -lboost_thread-mt -lboost_system-mt
// otool -L exefile
// install_name_tool -change @executable_path/libboost_something.dylib
// /opt/local/lib/libboost_something.dylib exefile
//
// g++ boost_log.cpp  -L/Users/ronghuang/work/3rd_lib/boost_1_76_0/stage/lib
// -lboost_log_setup-mt -lboost_log-mt -lboost_thread-mt -lboost_system-mt
// -DBOOST_LOG_DYN_LINK -o blog//

// g++ Server.cpp gen-cpp/test_types.cpp -lthrift  -std=c++14 -o test
// -L/Users/ronghuang/work/3rd_lib/boost/lib -lboost_log_setup -lboost_log

#include "gen-cpp/test_types.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TServerSocket.h>

#include "thrift/protocol/TBinaryProtocol.h"
#include "thrift/transport/TBufferTransports.h"
#include <boost/shared_ptr.hpp>

#include <iostream>
#include <string>

#include <memory>
#include <sstream>

#include <boost/crc.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sources/logger.hpp>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using apache::thrift::protocol::TBinaryProtocol;
using apache::thrift::transport::TMemoryBuffer;

using boost::shared_ptr;
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

#define MAX_NUM 200
#include <fstream>

// void init() {
//   logging::add_file_log(keywords::file_name = "sample_%N.log",
//                         keywords::rotation_size = 10 * 1024 * 1024,
//                         keywords::time_based_rotation =
//                             sinks::file::rotation_at_time_point(0, 0, 0),
//                         keywords::format = "[%TimeStamp%]: %Message%");
//   logging::core::get()->set_filter(logging::trivial::severity >=
//                                    logging::trivial::info);
// }

int main(int argc, char **argv) {
  int port = 9090;

  // boost::log::sources::logger_mt logger_;

  User u;
  u.__set_name("ddd");
  u.__set_age(9);
  u.__set_vip(true);

  std::string thriftStr, jsonStr;
  std::stringstream ss;

  ss << u;
  std::string s = ss.str();
  std::cout << s << '\n';
  //  int time;

  //  //①序列化为thrift binary protocol
  //  boost::shared_ptr<TMemoryBuffer> buffer(new TMemoryBuffer());

  // TBinaryProtocol binaryProtcol(*buffer);

  //  u.write(&binaryProtcol );
  //      buffer->getBufferAsString();
  //     auto str = buffer->getBufferAsString();

  // Use TFramedTransport
  const auto memory_buffer =
      std::make_shared<apache::thrift::transport::TMemoryBuffer>();
  apache::thrift::transport::TFramedTransport framed_transport(memory_buffer);
  framed_transport.write(reinterpret_cast<const uint8_t *>(s.data()),
                         (uint32_t)s.length());
  framed_transport.flush();
  std::string msg_content_framed = memory_buffer->getBufferAsString();

  std::cout << "thrift反序列化" << u << "==-ms\n";

  const auto buff =
      std::make_shared<apache::thrift::transport::TMemoryBuffer>();
  // apache::thrift::transport::TFramedTransport ff(buff);
  // ff.write(reinterpret_cast<const uint8_t*>(u.data()));

  std::fstream myfile;
  myfile = std::fstream("file.binary", std::ios::out | std::ios::binary);
  myfile << u;
  myfile.close();
  // BOOST_LOG(logger_) << std::move(s);

  // //②反序列thrift binary data
  // thriftSerializeTest::thriftBinaryDeserialize(thriftStr, &time);
  // cout << "thrift反序列化" << MAX_NUM << "次时间为" << time << "ms\n";

  // //③jsoncpp序列化为json
  // thriftSerializeTest::jsonSerialize(sc, &jsonStr, &time);
  // cout << "jsoncpp序列化json" << MAX_NUM << "次时间为" << time << "ms\n";

  // //④jsoncpp反序列化json
  // thriftSerializeTest::jsonDeserialize(jsonStr, &time);

  return 0;
}