MiniDB: Mini Database Engine in C++
===================================

A simplified database engine is implemented in C++ here, for the purpose of understanding the underlying details of database system. This database engine implements the most basic SQL operations as well as index on B+ tree.

## Compile

To compile, you need two open source C++ libraries installed:
* boost
* readline

On Mac OS X, XCode could be used to open "MiniDB.xcodeproj" directly. It's recommended to install the two libraries needed with Homebrew. If you are using readline library not through Homebrew or not with version 6.2.4, you should change the header search path and library search path in XCode to approapriate paths.

On platforms where Eclipse is availbable, the whole folder could be imported to Eclipse without any trouble.

To run it, you need to have global environment variable "HOME" set, the data will be stored at "$HOME/MiniDBData" automatically.

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

## Design & Implementation
See [wiki](https://github.com/halfvim/MiniDB/wiki/Design-&-Implementation).

## Test Runs
See [wiki](https://github.com/halfvim/MiniDB/wiki/Test-Run).
