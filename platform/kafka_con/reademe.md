# ------start multiple zookeeper---------
# server1
./zookeeper-server-start.sh ../config/zookeeper.properties
# server2
./zookeeper-server-start.sh ../config/zookeeper.properties
# server3
./zookeeper-server-start.sh ../config/zookeeper.properties
# - put a myid file under dataDir with id
"""
touch myid
echo "1" > myid
"""

# ------start multiple kafka server---------
# server1
bin/kafka-server-start.sh    config/server-1.properties
# server2
bin/kafka-server-start.sh    config/server-2.properties
# server3
bin/kafka-server-start.sh    config/server-3.properties


# -------Create Topic--------
"""
set topic replic and partition
"""
./kafka-topics.bat --create --zookeeper localhost:2181 --replication-factor 1 --partitions 1 --topic test


# --------Produce messages-------
"""
enable key and separator between key|value
"""
./kafka-console-producer.bat  --broker-list localhost:9092 --topic test  --property parse.key=true --property key.separator=*

# -------Consume messages-----
"""
group consumer is usefull
"""
./kafka-console-consumer.bat --bootstrap-server localhost:9092 --topic group_message --group my-console-client --property print.key=true  --property print.timestamp=true 
./kafka-consumer-groups.bat --bootstrap-server localhost:9092  --group my-console-client  --topic group_message  --reset-offsets --to-earliest

"""
single consumer 
"""
./kafka-console-consumer.sh --bootstrap-server localhost:9092 --topic test-events  --from-beginning --property print.timestamp=true --property print.key=true


val df = spark.readStream.format("kafka").option("kafka.bootstrap.servers", "localhost:9092").option("subscribe", "test-events").option("startingOffsets", "earliest") .load()



./kafka-console-producer.sh  --broker-list localhost:9092 --topic test-events  --property parse.key=true --property key.separator=*

More properties are available such as:

print.partition

print.offset

print.headers

key.separator

line.separator

headers.separator




./kafka-console-consumer.sh --bootstrap-server localhost:9092 --topic test-events  --from-beginning


1003* Test 110 20230510-10:30:20 true


val usersDF = spark.read.format("avro").load("examples/src/main/resources/users.avro")
usersDF.select("name", "favorite_color").write.format("avro").save("namesAndFavColors.avro")



kafka-console-consumer.sh --bootstrap-server localhost:9092 --topic first_topic --formatter kafka.tools.DefaultMessageFormatter --property print.timestamp=true --property print.key=true --property print.value=true --from-beginning

CreateTime:1641810588071	null	hello
CreateTime:1641823304170	name	Stephane
CreateTime:1641823301294	example key	example value


var df=spark.readStream.format("kafka").option("kafka.bootstrap.servers","localhost/127.0.0.1:9092").option("subscribe","streaming.orders.input").load()