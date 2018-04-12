# hotdbcheck
用于检查hotdb路由数据的正确性

- 帮助信息
```
hotdb-db	is HotDB logic db. Default is test.
hotdb-port	is HotDB port. Default is 3323.
hotdb-user	is HotDB server account. Default is root.
hotdb-password	is HotDB server password. Default is root.
hotdb-host	is HotDB server ip. Default is 127.0.0.1.

mysql-host	is HotDB config ip. Default is 127.0.0.1.
mysql-password	is HotDB config password. Default is 123456.
mysql-port	is HotDB config port. Default is 3306.
mysql-user	is HotDB config account. Default is hotdb_config
mysql-db	is HotDB config db. Default is hotdb_config.

tasks		is running task. Default is 8.
each-data	is number of check for each task. Default is 10000.
table-name	is table_name. Default is t1.
help		show help info.
```
- 示例
```
./hotdbcheck --hotdb-user=root --hotdb-host=192.168.56.101 --hotdb-port=3338 --hotdb-password=root --hotdb-db=benchmark --mysql-host=127.0.0.1 --mysql-port=3306 --mysql-password=123456 --mysql-user=root --mysql-db=mysqldb  --table-name=checktablename --tasks=16 --each-data=10000
```
- make 用例
1. debug版本
```
make
```
2. release版本

```
make RELEASE=1
```

- 编译器要求
1. gcc >= 4.8
2. 存在mysql-devel
