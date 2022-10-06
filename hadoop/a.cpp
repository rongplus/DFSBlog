#include <iostream>
#include <cstring>
#include "hdfs.h"
#include <string>

int main() {
    std::cout << "Hello, World!" << std::endl;
    // 在 $HADOOP_HOME/etc/hadoop/core-site.xml 中配置
    std::cout <<__LINE__<<std::endl;
    hdfsFS fs = hdfsConnect("hdfs://node1", 8020);
    std::cout <<__LINE__<<  fs<< std::endl;
    const char *writePath = "/home/hduser_/work/tmp/testfile.txt";
    hdfsFile writeFile = hdfsOpenFile(fs, writePath, O_WRONLY | O_CREAT, 0, 0, 0);
    if (!writeFile) {
        fprintf(stderr, "Failed to open %s for writing!\n", writePath);
        exit(-1);
    }

    char *buffer = new char[5];
    tSize num_written_bytes = hdfsWrite(fs, writeFile, (void *) buffer, strlen(buffer) + 1);
    if (hdfsFlush(fs, writeFile)) {
        fprintf(stderr, "Failed to 'flush' %s\n", writePath);
        exit(-1);
    }

    std::cout << num_written_bytes << std::endl;
    hdfsCloseFile(fs, writeFile);

    return 0;
}
//g++ a.cpp -I/home/hduser_/work/hadoop/include -L/home/hduser_/work/hadoop/lib/native -lhdfs
//g++ tt.cpp -I/usr/local/hadoop/include -L/usr/local/hadoop/lib/native -lhdfs -o tt -L/usr/lib/jvm/java-8-openjdk-amd64/jre/lib/amd64/server -ljvm -lhadooppipes -lhadooputils -lpthread 
//g++ tt.cpp -I/usr/local/hadoop/include -L/usr/local/hadoop/lib/native -lhdfs -o tt -L/usr/lib/jvm/java-8-openjdk-amd64/jre/lib/amd64/server -ljvm -lhadooppipes -lhadooputils -lpthread  -lcrypto -lssl  -ltirpc
