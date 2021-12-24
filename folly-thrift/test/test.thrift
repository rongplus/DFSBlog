struct User{
  1:i64 id,

  2:string name,

  3:i32 age,

  4:bool vip

}

struct Tag {
  1: required string key,
  2: required string value,
}

enum MetadataLogActionType {
  ADD = 0,
  DELETE = 1
}

struct MetricMetadataLogEntry {
  # Logging time in ms
  1: required i64 timestampMs,
  # The name of a new metric or a removed one
  2: required string metricName,
  # Key value pairs to specify the properties of a metric
  3: required list<Tag> tags,
  # The kind of action performed on the metric
  4: required MetadataLogActionType action
}