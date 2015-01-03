#### Help
```
MiniDB> help;
SQL TYPE: #HELP#
SQL STATEMENT: help
MiniDB 1.0.0
Implemented SQL types:
#QUIT#
#HELP#
#EXEC#
#CREATE DATABASE#
#SHOW DATABASES#
#USE#
#DROP DATABASE#
#CREATE TABLE#
#SHOW TABLES#
#DROP TABLES#
#CREATE INDEX#
#DROP INDEX#
#SELECT#
#INSERT#
#DELETE#
#UPDATE#
```
#### Create Database
```
MiniDB> create database abc;
SQL TYPE: #CREATE DATABASE#
SQL STATEMENT: create database abc
DB NAME: abc
Creating database: abc
Database folder created!
Catalog written!
```
#### Show Databases
```
MiniDB> show databases;
SQL TYPE: #SHOW DATABASES#
SQL STATEMENT: show databases
DATABASE LIST:
	abc
```
#### Use
```
MiniDB> use abc;
SQL TYPE: #USE#
SQL STATEMENT: use abc
DB NAME: abc
```
#### Create Table
```
MiniDB> create table aaa (col1 int, col2 float, col3 char(2), primary key (col1));
SQL TYPE: #CREATE TABLE#
SQL STATEMENT: create table aaa ( col1 int , col2 float , col3 char ( 2 )  , primary key ( col1 )  ) 
TABLE NAME: aaa
COLUMN: col1
TYPE: int
COLUMN: col2
TYPE: float
COLUMN: col3
PRIMARY KEY: col1
Creating table: aaa
Table file created!
Catalog written!
```
#### Show Tables
```
MiniDB> show tables;
SQL TYPE: #SHOW TABLES#
SQL STATEMENT: show tables
CURRENT DATABASE: abc
TABLE LIST:
	aaa
```
#### Insert
```
MiniDB> insert into aaa values (111, 222.2, 'xy');
SQL TYPE: #INSERT#
SQL STATEMENT: insert into aaa values ( 111 , 222.2 , 'xy' ) 
TABLE NAME: aaa
0 : 111
1 : 222.2
2 : xy


MiniDB> insert into aaa values (222, 333.3, 'pq');
SQL TYPE: #INSERT#
SQL STATEMENT: insert into aaa values ( 222 , 333.3 , 'pq' ) 
TABLE NAME: aaa
0 : 222
1 : 333.3
2 : pq


MiniDB> insert into aaa values (222, 555.5, 'qq');
SQL TYPE: #INSERT#
SQL STATEMENT: insert into aaa values ( 222 , 555.5 , 'qq' ) 
TABLE NAME: aaa
0 : 222
1 : 555.5
2 : qq
Primary key conflicts!
```
#### Select
```
MiniDB> select * from aaa where col2 <> 222.2;
SQL TYPE: #SELECT#
SQL STATEMENT: select * from aaa where col2 <> 222.2
TABLE NAME: aaa
col2 1 222.2
col1     col2     col3     
222      333.3    pq   
```
#### Create Index
```
MiniDB> create index aaacol1 on aaa (col1);
SQL TYPE: #CREATE INDEX#
SQL STATEMENT: create index aaacol1 on aaa ( col1 ) 
INDEX NAME: aaacol1
TABLE NAME: aaa
COLUMN NAME: col1
*****************************************************
KeyCount: 2, NodeCount: 1, Level: 1, Root: 0 
----------------------
BlockNum: 0 Count: 2, Parent: -1  IsLeaf:1
Keys: { 111      222       }
Vals: { 0000000 0000001  }
NextLeaf:    -1


MiniDB> insert into aaa values (333, 444.4, 'qq');
SQL TYPE: #INSERT#
SQL STATEMENT: insert into aaa values ( 333 , 444.4 , 'qq' ) 
TABLE NAME: aaa
0 : 333
1 : 444.4
2 : qq


MiniDB> select * from aaa;
SQL TYPE: #SELECT#
SQL STATEMENT: select * from aaa
TABLE NAME: aaa
col1     col2     col3     
111      222.2    xy       
222      333.3    pq       
333      444.4    qq       
*****************************************************
KeyCount: 3, NodeCount: 1, Level: 1, Root: 0 
----------------------
BlockNum: 0 Count: 3, Parent: -1  IsLeaf:1
Keys: { 111      222      333       }
Vals: { 0000000 0000001 0000002  }
NextLeaf:    -1
5.10	Update
MiniDB> update aaa set col1 = 444 where col1 = 111;
SQL TYPE: #UPDATE#
SQL STATEMENT: update aaa set col1 = 444 where col1 = 111
TABLE NAME: aaa
col1 444
col1 0 111


MiniDB> select * from aaa;
SQL TYPE: #SELECT#
SQL STATEMENT: select * from aaa
TABLE NAME: aaa
col1     col2     col3     
444      222.2    xy       
222      333.3    pq       
333      444.4    qq       
*****************************************************
KeyCount: 3, NodeCount: 1, Level: 1, Root: 0 
----------------------
BlockNum: 0 Count: 3, Parent: -1  IsLeaf:1
Keys: { 222      333      444       }
Vals: { 0000001 0000002 0000000  }
NextLeaf:    -1
5.11	Delete
MiniDB> delete from aaa where col1 = 222;
SQL TYPE: #DELETE#
SQL STATEMENT: delete from aaa where col1 = 222
TABLE NAME: aaa
col1 0 222


MiniDB> select * from aaa;
SQL TYPE: #SELECT#
SQL STATEMENT: select * from aaa
TABLE NAME: aaa
col1     col2     col3     
444      222.2    xy       
333      444.4    qq       
*****************************************************
KeyCount: 2, NodeCount: 1, Level: 1, Root: 0 
----------------------
BlockNum: 0 Count: 2, Parent: -1  IsLeaf:1
Keys: { 333      444       }
Vals: { 0000002 0000000  }
NextLeaf:    -1
5.12	Drop Index
MiniDB> drop index aaacol1;
SQL TYPE: #DROP INDEX#
SQL STATEMENT: drop index aaacol1
IDX NAME: aaacol1
Index file removed!
Catalog written!
5.13	Drop Table
MiniDB> drop table aaa;
SQL TYPE: #DROP TABLE#
SQL STATEMENT: drop table aaa
TB NAME: aaa
Table file removed!
Removing Index files!
Catalog written!
5.14	Drop Database
MiniDB> drop database abc;
SQL TYPE: #DROP DATABASE#
SQL STATEMENT: drop database abc
DB NAME: abc
Dropping database: abc
Database folder deleted!
Database removed from catalog!
```
#### Exec
Content of file named "input":
```
show databases;
create database abc;
use abc;
show tables;
create table aaa (col1 int, col2 float, col3 char(2), primary key (col1));
insert into aaa values (111, 222.2, 'xy');
insert into aaa values (222, 333.3, 'pq');
select * from aaa where col2 <> 222.2;
insert into aaa values (111, 444.4, 'qq');
create index aaacol1 on aaa (col1);
insert into aaa values (333, 444.4, 'qq');
select * from aaa;
update aaa set col1 = 222 where col1 = 111;
select * from aaa;
update aaa set col1 = 444 where col1 = 111;
select * from aaa;
delete from aaa where col1 = 222;
select * from aaa;
```
Execution result:
```
MiniDB> exec input;
SQL TYPE: #EXEC#
SQL STATEMENT: exec input
FILE NAME: input

SQL TYPE: #SHOW DATABASES#
SQL STATEMENT: show databases
DATABASE LIST:

SQL TYPE: #CREATE DATABASE#
SQL STATEMENT: create database abc
DB NAME: abc
Creating database: abc
Database folder created!
Catalog written!

SQL TYPE: #USE#
SQL STATEMENT: use abc
DB NAME: abc

SQL TYPE: #SHOW TABLES#
SQL STATEMENT: show tables
CURRENT DATABASE: abc
TABLE LIST:

SQL TYPE: #CREATE TABLE#
SQL STATEMENT: create table aaa ( col1 int , col2 float , col3 char ( 2 )  , primary key ( col1 )  ) 
TABLE NAME: aaa
COLUMN: col1
TYPE: int
COLUMN: col2
TYPE: float
COLUMN: col3
PRIMARY KEY: col1
Creating table: aaa
Table file created!
Catalog written!

SQL TYPE: #INSERT#
SQL STATEMENT: insert into aaa values ( 111 , 222.2 , 'xy' ) 
TABLE NAME: aaa
0 : 111
1 : 222.2
2 : xy

SQL TYPE: #INSERT#
SQL STATEMENT: insert into aaa values ( 222 , 333.3 , 'pq' ) 
TABLE NAME: aaa
0 : 222
1 : 333.3
2 : pq

SQL TYPE: #SELECT#
SQL STATEMENT: select * from aaa where col2 <> 222.2
TABLE NAME: aaa
col2 1 222.2
col1     col2     col3     
222      333.3    pq       

SQL TYPE: #INSERT#
SQL STATEMENT: insert into aaa values ( 111 , 444.4 , 'qq' ) 
TABLE NAME: aaa
0 : 111
1 : 444.4
2 : qq
Primary key conflicts!

SQL TYPE: #CREATE INDEX#
SQL STATEMENT: create index aaacol1 on aaa ( col1 ) 
INDEX NAME: aaacol1
TABLE NAME: aaa
COLUMN NAME: col1
*****************************************************
KeyCount: 2, NodeCount: 1, Level: 1, Root: 0 
----------------------
BlockNum: 0 Count: 2, Parent: -1  IsLeaf:1
Keys: { 111      222       }
Vals: { 0000000 0000001  }
NextLeaf:    -1

SQL TYPE: #INSERT#
SQL STATEMENT: insert into aaa values ( 333 , 444.4 , 'qq' ) 
TABLE NAME: aaa
0 : 333
1 : 444.4
2 : qq

SQL TYPE: #SELECT#
SQL STATEMENT: select * from aaa
TABLE NAME: aaa
col1     col2     col3     
111      222.2    xy       
222      333.3    pq       
333      444.4    qq       
*****************************************************
KeyCount: 3, NodeCount: 1, Level: 1, Root: 0 
----------------------
BlockNum: 0 Count: 3, Parent: -1  IsLeaf:1
Keys: { 111      222      333       }
Vals: { 0000000 0000001 0000002  }
NextLeaf:    -1

SQL TYPE: #UPDATE#
SQL STATEMENT: update aaa set col1 = 222 where col1 = 111
TABLE NAME: aaa
col1 222
col1 0 111
Primary key conflicts!

SQL TYPE: #SELECT#
SQL STATEMENT: select * from aaa
TABLE NAME: aaa
col1     col2     col3     
111      222.2    xy       
222      333.3    pq       
333      444.4    qq       
*****************************************************
KeyCount: 3, NodeCount: 1, Level: 1, Root: 0 
----------------------
BlockNum: 0 Count: 3, Parent: -1  IsLeaf:1
Keys: { 111      222      333       }
Vals: { 0000000 0000001 0000002  }
NextLeaf:    -1

SQL TYPE: #UPDATE#
SQL STATEMENT: update aaa set col1 = 444 where col1 = 111
TABLE NAME: aaa
col1 444
col1 0 111

SQL TYPE: #SELECT#
SQL STATEMENT: select * from aaa
TABLE NAME: aaa
col1     col2     col3     
444      222.2    xy       
222      333.3    pq       
333      444.4    qq       
*****************************************************
KeyCount: 3, NodeCount: 1, Level: 1, Root: 0 
----------------------
BlockNum: 0 Count: 3, Parent: -1  IsLeaf:1
Keys: { 222      333      444       }
Vals: { 0000001 0000002 0000000  }
NextLeaf:    -1

SQL TYPE: #DELETE#
SQL STATEMENT: delete from aaa where col1 = 222
TABLE NAME: aaa
col1 0 222

SQL TYPE: #SELECT#
SQL STATEMENT: select * from aaa
TABLE NAME: aaa
col1     col2     col3     
444      222.2    xy       
333      444.4    qq       
*****************************************************
KeyCount: 2, NodeCount: 1, Level: 1, Root: 0 
----------------------
BlockNum: 0 Count: 2, Parent: -1  IsLeaf:1
Keys: { 333      444       }
Vals: { 0000002 0000000  }
NextLeaf:    -1
5.16	Exit/Quit
MiniDB> quit
SQL TYPE: #QUIT#
SQL STATEMENT: quit
Quiting...
```
