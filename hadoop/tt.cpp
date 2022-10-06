#include"Pipes.hh"
#include"TemplateFactory.hh"
#include"StringUtils.hh"
 
class DataCountMap:public HadoopPipes::Mapper {
public:
  DataCountMap(HadoopPipes::TaskContext&context){}
  void map(HadoopPipes::MapContext&context) {
    std::vector<std::string>words=HadoopUtils::splitString(context.getInputValue()," ");    // 这里是分割字符串，如前文所述，每一行数据中的各项是以空格来分割的。分割的结果保存到了一个std::vector中
    if("kkk"==words[1]) {
      context.emit("kkk","1");
    } else if("nnn"==words[1]) {
      context.emit("nnn","1");
    }
  }
};
 
class DataCountReduce:public HadoopPipes::Reducer {
public:
  DataCountReduce(HadoopPipes::TaskContext&context){}
  void reduce(HadoopPipes::ReduceContext&context)
  {
    int sum=0;
    while(context.nextValue()) {
      sum++;
    }
    context.emit(context.getInputKey(),HadoopUtils::toString(sum));
  }
};
 
int main(int argc,char*argv[])
{
  return HadoopPipes::runTask(HadoopPipes::TemplateFactory<DataCountMap, DataCountReduce>());
}
//mapred pipes -D hadoop.pipes.java.recordreader=true -D hadoop.pipes.java.recordwriter=true -input /data/nums.txt  -output /output_dd -program /bin/tt
//g++ tt.cpp -I/usr/local/hadoop/include -L/usr/local/hadoop/lib/native -lhdfs -o tt -L/usr/lib/jvm/java-8-openjdk-amd64/jre/lib/amd64/server -ljvm -lhadooppipes -lhadooputils -lpthread  -lcrypto -lssl  -ltirpc
/*
HADOOP_INSTALL = /usr/local/hadoop

INCLUDE_PATH = $(HADOOP_INSTALL)/src/c++/

 

CC              = g++

CXXFLAGS = -Wall -g \

                  -I${INCLUDE_PATH}pipes/api/hadoop \

                  -I${INCLUDE_PATH}utils/api/hadoop

LDFLAGS = -ljvm -lhadooppipes -lhadooputils -lpthread

 

OBJECTS=dz_count.o

dz_count: $(OBJECTS)

$(CC) $(CXXFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)
*/