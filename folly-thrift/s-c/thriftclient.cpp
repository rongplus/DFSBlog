#include "gen-cpp/Serv.h"
#include "gen-cpp/test_types.h"

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TSocket.h>

#include "thrift/protocol/TBinaryProtocol.h"
#include "thrift/transport/TBufferTransports.h"
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;
// g++ thriftserver.cpp gen-cpp/test_types.cpp gen-cpp/Serv.cpp -lthrift
// -std=c++14 -o thriftClient -L/Users/ronghuang/work/3rd_lib/boost/lib
// -lbooslog_setup -lboost_log it is a client

// goto gen-cpp
// g++ Serv.cpp test_types.cpp Serv_server.skeleton.cpp -lthrift  -std=c++14 -o
// thriftServer -L/Users/ronghuang/work/3rd_lib/boost/lib -lboost_log_setup
// -lboost_log

using boost::shared_ptr;
#include <iostream>

int main(int argc, char **argv) {
  // boost::shared_ptr<::apache::thrift::transport::TSocket> socket(
  //     new ::apache::thrift::transport::TSocket("localhost", 9090));
  // boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  // boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

  std::shared_ptr<TTransport> socket(new TSocket("localhost", 9090));
  std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

  transport->open();

  // 我们的代码写在这里
  //********添加部分***********
  Student s;
  s.sno = 123;
  s.sname = "xiaoshe";
  s.ssex = 1;
  s.sage = 30;
  ServClient client(protocol);
  client.put(s);
  std::cout << client.add(29, 10);
  　　 //********添加部分***********

      transport->close();
  return 0;
}