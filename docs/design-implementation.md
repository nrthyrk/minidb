There are 6 main modules in this database engine: Interpreter, API, Record Manager, Index Manager, Catalog Manager and Buffer Manager.

```
+-----------------------------------------------------------------+
|                           Interpreter                           |
+--------------+----------------------------------+---------------+
               |                                  |
              <->                                <->
               |                                  |
       +-------v------------------------+         |
       |              API               |         |
       +---+------------+----------+----+         |
           |            |           \             |
          <->          <->          <->           |
           |            |             \           |
    +------v------+ +---v---------+   +v----------v---+
    |   Record    | |    Index    |   |    Catalog    |
    |   Manager   | |   Manager   |   |    Manager    |
    +------+------+ +------+------+   +-------+-------+
           |               |                  |
          <->             <->                 |
           |               |                  |
    +------v---------------v------+           |
    |        Buffer Manager       |           |
    +--------------+--------------+           |
                   |                          |
                  <->                         |
                   |                          |
             +-----v-----+                    |
             |           |                    |
             |  DB Files | <------------------+
             +-----------+
```

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
