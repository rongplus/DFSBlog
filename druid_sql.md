SQL tips about QueryBook and Druid board


1， use single quotation mark not double quotation mark in where condition statement
Like "metricName" <> 'msg', the first double quotation mark is OK, but the double quotation mark will not work in the second quotation.

2, alias can be the column's title but alias is not used in the group by  statement.
Like DT, Total are column title, but DT, Total can’t use in group by statement

3, time function, from long to date time;
DATE_TRUNC('hour',MILLIS_TO_TIMESTAMP(PARSE_LONG( "timestamp"  ) ) )


4
 select DATE_TRUNC('hour',MILLIS_TO_TIMESTAMP(PARSE_LONG( "timestamp"  ) ) )as "DT", "metricName","serverAddress",sum(CAST( "count" as BIGINT)) as "Total"
from "goku-query-log" where "serverAddress" is not NULL  and  "metricName" <> 'dummy_hot_key_log'
and __time >= TIMESTAMP '2021-11-12 00:00:00.000000' and __time <= TIMESTAMP '2021-11-15 23:59:00.000000' 
GROUP BY DATE_TRUNC('hour',MILLIS_TO_TIMESTAMP(PARSE_LONG( "timestamp"  ) ) ), "metricName","serverAddress"

SQL tips about QueryBook and Druid board

Sample:
select DATE_TRUNC('hour',MILLIS_TO_TIMESTAMP(PARSE_LONG( "timestamp"  ) ) )as "DT", "metricName","serverAddress",sum(CAST( "count" as BIGINT)) as "Total"
from "goku-query-log" where "serverAddress" is not NULL  and  "metricName" <> 'dummy_hot_key_log'
and __time >= TIMESTAMP '2021-11-12 00:00:00.000000' and __time <= TIMESTAMP '2021-11-15 23:59:00.000000' 
GROUP BY DATE_TRUNC('hour',MILLIS_TO_TIMESTAMP(PARSE_LONG( "timestamp"  ) ) ), "metricName","serverAddress"

