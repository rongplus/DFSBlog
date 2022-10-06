http://localhost:9870/dfshealth.html#tab-overview
http://localhost:8088/cluster

https://www.cnblogs.com/lanxuezaipiao/p/3648853.html
https://github.com/autopear/Intellij-Hadoop
   
添加lib路径到系统
   sudo ldconfig /usr/local/lib
   export LD_LIBRARY_PATH=/usr/lib/jvm/java-11-openjdk-amd64/lib/server

查看目录

readlink -f /usr/bin/java | sed "s:bin/java::"
Option 1: Set a Static Value
/usr/local/hadoop/etc/hadoop/hadoop-env.sh
 . . .
#export JAVA_HOME=
export JAVA_HOME=/usr/lib/jvm/java-11-openjdk-amd64/
 . . .
Option 2: Use Readlink to Set the Value Dynamically
/usr/local/hadoop/etc/hadoop/hadoop-env.sh
 . . .
#export JAVA_HOME=
export JAVA_HOME=$(readlink -f /usr/bin/java | sed "s:bin/java::")
 . . .
 export CLASSPATH=$JAVA_HOME/lib/dt.jar:$JAVA_HOME/lib/tools.jar:.


g++ b.cpp -o test  -I/usr/local/hadoop/include -L/usr/local/hadoop/lib/native -L/usr/lib/jvm/java-11-openjdk-amd64/lib/server -ljvm -lhadooppipes -lhadooputils -lpthread -lssl -lcrypto


hadoop pipes -D hadoop.pipes.java.recordreader=true -D hadoop.pipes.java.recordwriter=true -program /bin/dd


--- build
g++ d.cpp -o dd  -I/usr/local/hadoop/include -L/usr/local/hadoop/lib/native -L/usr/lib/jvm/java-11-openjdk-amd64/lib/server -ljvm -lhadooppipes -lhadooputils -lpthread -lssl -lcrypto

-- put to 
hadoop fs -mkdir /bin
hadoop fs -put counter /bin
hadoop fs -ls /bin
--- add data
hadoop fs -put num.txt /data

---run
hadoop fs -rm -r /output
hadoop pipes -conf job_config.xml -input /data/num.txt -output /output -program /bin/counter

hadoop jar hadoop-mapreduce-examples-3.3.4.jar wordcount -input /data  -output /output
hadoop jar hadoop-mapreduce-examples-3.3.4.jar wordcount /data /output
hadoop /bin/counter -conf job_config.xml -input /data/num.txt -output /output 

hadoop pipes -D hadoop.pipes.java.recordreader=true -D hadoop.pipes.java.recordwriter=true -input /data/num.txt -output /output_dd -program /bin/dd





2

In mapred-site.xml add this property:

<property>
    <name>mapreduce.framework.name</name>
    <value>yarn</value>
</property>
In yarn-site.xml add this property:

<property>
    <name>yarn.nodemanager.aux-services</name>
    <value>map reduce_shuffle</value>
</property>
I also got the same error, adding above two properties solved the problem...

 hadoop jar ./target/Test1-1.0-SNAPSHOT.jar com.rong.WordCount /Input /output`
  hadoop jar ./target/Test1-1.0-SNAPSHOT.jar com.rong.WordCount /input /output1