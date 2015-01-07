MiniDB: Mini Database Engine in C++
===================================

A simplified database engine is implemented in C++ here, for the purpose of understanding the underlying details of database system. This database engine implements the most basic SQL operations as well as index on B+ tree.

## Features

#### Database Management
*	Create Database
```
Syntax:		CREATE DATABASE database_name;
Example:	CREATE DATABASE abc;
```
*	Drop Database
```
Syntax:		DROP DATABASE database_name;
Example: 	DROP DATABASE abc;
```
*	Show Databases
```
Syntax:		SHOW DATABASES;
Example: 	SHOW DATABASES;
```
*	Use
```
Syntax:		USE database_name;
Example: 	USE abc;
```
####	Table Management
*	Create Table
```
Syntax:		CREATE TABLE table_name
			(
			column_name1 data_type(size),
			column_name2 data_type(size),
			column_name3 data_type(size),
			....,
			PRIMARY KEY (column_name)
			);
Example: 	CREATE TABLE aaa
			(
			col1 int,
			col2 float,
			col3 char(8),
			PRIMARY KEY (col1)
			);
```
Note:	Available data types include int, float and char(N). Only one primary key could be created.

*	Drop Table
```
Syntax:		DROP TABLE table_name;
Example:	DROP TABLE aaa;
```
*	Show Tables
```
Syntax:		SHOW TABLES;
Example: 	SHOW TABLES;
```
####	Index Management

*	Create Index
```
Syntax:		CREATE INDEX index_name
			ON table_name (column_name);
Example: 	CREATE INDEX aaacol1 
			ON aaa (col1);
```
Note:	Index can only be created on primary key. B+ tree manipulation is implemented in all data manipulation SQLs.

*	Drop Index
```
Syntax:		DROP INDEX index_name;
Example:	DROP INDEX aaacol1;
```
####	Data Manipulation
*	Insert
```
Syntax:		INSERT INTO table_name
			VALUES (value1, value2, value3, ...);
Example: 	INSERT INTO aaa
			VALUES (111, 222.2, 'xyz');
```
*	Select
```
Syntax:		SELECT * FROM table_name
			WHERE column1 = value1
			and column2 = value2
			and ...;
Example:	SELECT * FROM aaa
			WHERE col1 = 111;
```
Note:		Only "and" logic is allowed. Only "*" is allowed.

*	Delete
```
Syntax:		DELETE FROM table_name 
			WHERE column1 = value1
			and column2 = value2
			and ...;
Example:	DELETE FROM aaa
			WHERE col1 = 111;
```
Note:		Only "and" logic is allowed.

*	Update
```
Syntax:		UPDATE table_name
			SET column1 = value1, column2 = value2, ...
			WHERE column1 = value1
			and column2 = value2
			and ...;
Example:	UPDATE aaa
			SET col2 = 555.5
			WHERE col1 = 1;
```
Note:		Only "and" logic is allowed.

####	Other Features Implemented

*	Help
```
Syntax:		HELP;
Example: 	HELP;
```
*	Quit
```
Syntax:		EXIT
			or
			QUIT
Example:	EXIT
			or
			QUIT
```
*	Exec
```
Syntax:		EXEC file_name;
Example: 	EXEC input.txt;
```

####	Unimplemented Features
*	Transaction Management
*	User Management
*	Authentication
*	Join
*	Foreign Keys
*	Views
*	Complex Select

## Compile

To compile, you need two open source C++ libraries installed:
* boost
* readline

On Mac OS X, XCode could be used to open "MiniDB.xcodeproj" directly. It's recommended to install the two libraries needed with Homebrew. If you are using readline library not through Homebrew or not with version 6.2.4, you should change the header search path and library search path in XCode to approapriate paths.

On platforms where Eclipse is availbable, the whole folder could be imported to Eclipse without any trouble.

To run it, you need to have global environment variable "HOME" set, the data will be stored at "$HOME/MiniDBData" automatically.

## Design & Implementation
There are 6 main modules in this database engine: Interpreter, API, Record Manager, Index Manager, Catalog Manager and Buffer Manager.

#### Interpreter
The function of this module is to interprate and execute SQL statements. Everytime the interpreter receives a SQL statement; it formats the SQL statement, constructs a SQL statement object, and passes this object to the appropriate function in API. If it detects an incorrect syntax, it will throw a syntax error exception.
There are the following main classes in this module:
* Interpreter: the class interprating SQL statements;
* TKey: a uniform class which stores values in SQL statements;
* SQL: base class for the following SQL statement classes storing statements;
* SQLCreateDatabase
* SQLDropDatabase
* SQLDropTable
* SQLDropIndex
* SQLUse
* SQLCreateTable
* SQLInsert
* SQLExec
* SQLSelect
* SQLCreateIndex
* SQLDelete
* SQLUpdate

#### API
This module wraps the interface Record Manager, Index Manager and Catalog Manager provide, so that the interpreter could use a uniform program interface.

There is only one class in this module:
* MiniDBAPI

#### Record Manager
This module provides programming interface for record manipulation including select, insert, delete, and update.

There is only one class in this module:

* RecordManager

#### Index Manager
This module provides programming interface for index management such as create index. It includes an implementation of B+ tree.

There are three classes in this module:
* IndexManager
* BPlusTree: B+ tree
* BPlusTreeNode: B+ tree node

#### Catalog Manager
This module manges the catalog information, and stores the information on disk using boost serialization library. The information includes databases, tables, indexes, and attributes.

There are five classes in this module:

* CatalogManager
* Database
* Table
* Attribute
* Index

#### Buffer Manager

This module manages the buffer. The replacement policy used here is LRU (least recent used). In buffer manager, each block has a size of 4K. 

There are two linked lists in this module.

##### Free Block Chain: BlockHandle

In this linked list, all blocks are free to use. 

##### File Chain: FileHandle

In this chain, each file node has two linked lists, one of which is the current used block chain, and the other is the recycled block chain. When the database engine needs a new block, it first checks whether there is a usable recycled block chain. If not, it queries BlockHandle to ask whether it has a free block to offer. If not again, LRU will come into work.

## Test Runs
See [wiki](https://github.com/halfvim/MiniDB/wiki/Test-Run)
