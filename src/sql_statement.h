//  Copyright (c) 2014 Yan Chen.
//  All rights reserved.
//
//  Author: yan.chen.im@gmail.com (Yan Chen)

#ifndef MINIDB_SQL_STATEMENT_H_
#define MINIDB_SQL_STATEMENT_H_

#include <string>
#include <vector>

#include "catalog_manager.h"

class CatalogManager;
class Database;
class Table;
class Attribute;
class Index;

class TKey {
private:
  int key_type_;
  char *key_;
  int length_;

public:
  TKey(int keytype, int length) {
    key_type_ = keytype;
    if (keytype == 2)
      length_ = length;
    else
      length_ = 4;
    key_ = new char[length_];
  }

  TKey(const TKey &t1) {
    key_type_ = t1.key_type_;
    length_ = t1.length_;
    key_ = new char[length_];
    memcpy(key_, t1.key_, length_);
  }

  void ReadValue(const char *content) {
    switch (key_type_) {
    case 0: {
      int a = std::atoi(content);
      memcpy(key_, &a, length_);
    } break;
    case 1: {
      float a = std::atof(content);
      memcpy(key_, &a, length_);
    } break;
    case 2: {
      memcpy(key_, content, length_);
    } break;
    }
  }

  void ReadValue(std::string str) {
    switch (key_type_) {
    case 0: {
      int a = std::atoi(str.c_str());
      memcpy(key_, &a, length_);
    } break;
    case 1: {
      float a = std::atof(str.c_str());
      memcpy(key_, &a, length_);
    } break;
    case 2: {
      memcpy(key_, str.c_str(), length_);
    } break;
    }
  }

  int key_type() { return key_type_; }
  char *key() { return key_; };
  int length() { return length_; }

  ~TKey() {
    if (key_ != NULL)
      delete[] key_;
  }

  friend std::ostream &operator<<(std::ostream &out, const TKey &object);

  bool operator<(const TKey t1) {
    switch (t1.key_type_) {
    case 0:
      return *(int *)key_ < *(int *)t1.key_;
    case 1:
      return *(float *)key_ < *(float *)t1.key_;
    case 2:
      return (strncmp(key_, t1.key_, length_) < 0);
    default:
      return false;
    }
  }

  bool operator>(const TKey t1) {
    switch (t1.key_type_) {
    case 0:
      return *(int *)key_ > *(int *)t1.key_;
    case 1:
      return *(float *)key_ > *(float *)t1.key_;
    case 2:
      return (strncmp(key_, t1.key_, length_) > 0);
    default:
      return false;
    }
  }

  bool operator<=(const TKey t1) { return !(operator>(t1)); }

  bool operator>=(const TKey t1) { return !(operator<(t1)); }

  bool operator==(const TKey t1) {
    switch (t1.key_type_) {
    case 0:
      return *(int *)key_ == *(int *)t1.key_;
    case 1:
      return *(float *)key_ == *(float *)t1.key_;
    case 2:
      return (strncmp(key_, t1.key_, length_) == 0);
    default:
      return false;
    }
  }

  bool operator!=(const TKey t1) {
    switch (t1.key_type_) {
    case 0:
      return *(int *)key_ != *(int *)t1.key_;
    case 1:
      return *(float *)key_ != *(float *)t1.key_;
    case 2:
      return (strncmp(key_, t1.key_, length_) != 0);
    default:
      return false;
    }
  }
};

class SQL {
protected:
  int sql_type_;

public:
  SQL() : sql_type_(-1) {}
  SQL(int sqltype) { sql_type_ = sqltype; }
  virtual ~SQL() {}
  int sql_type() { return sql_type_; }
  void set_sql_type(int sqltype) { sql_type_ = sqltype; }
  virtual void Parse(std::vector<std::string> sql_vector) = 0;
  int ParseDataType(std::vector<std::string> sql_vector, Attribute &attr,
                    unsigned int pos);
};

class SQLCreateDatabase : public SQL {
private:
  std::string db_name_;

public:
  SQLCreateDatabase(std::vector<std::string> sql_vector) { Parse(sql_vector); }
  std::string db_name() { return db_name_; }
  void set_db_name(std::string dbname) { db_name_ = dbname; }
  void Parse(std::vector<std::string> sql_vector);
};

class SQLDropDatabase : public SQL {
private:
  std::string db_name_;

public:
  SQLDropDatabase(std::vector<std::string> sql_vector) { Parse(sql_vector); }
  std::string db_name() { return db_name_; }
  void set_db_name(std::string dbname) { db_name_ = dbname; }
  void Parse(std::vector<std::string> sql_vector);
};

class SQLDropTable : public SQL {
private:
  std::string tb_name_;

public:
  SQLDropTable(std::vector<std::string> sql_vector) { Parse(sql_vector); }
  std::string tb_name() { return tb_name_; }
  void set_tb_name(std::string tbname) { tb_name_ = tbname; }
  void Parse(std::vector<std::string> sql_vector);
};

class SQLDropIndex : public SQL {
private:
  std::string idx_name_;

public:
  SQLDropIndex(std::vector<std::string> sql_vector) { Parse(sql_vector); }
  std::string idx_name() { return idx_name_; }
  void set_idx_name(std::string idxname) { idx_name_ = idxname; }
  void Parse(std::vector<std::string> sql_vector);
};

class SQLUse : public SQL {
private:
  std::string db_name_;

public:
  SQLUse(std::vector<std::string> sql_vector) { Parse(sql_vector); }
  std::string db_name() { return db_name_; }
  void set_db_name(std::string dbname) { db_name_ = dbname; }
  void Parse(std::vector<std::string> sql_vector);
};

class SQLCreateTable : public SQL {
private:
  std::string tb_name_;
  std::vector<Attribute> attrs_;

public:
  SQLCreateTable(std::vector<std::string> sql_vector) { Parse(sql_vector); }
  std::string tb_name() { return tb_name_; }
  void set_tb_name(std::string tbname) { tb_name_ = tbname; }
  std::vector<Attribute> attrs() { return attrs_; };
  void set_attrs(std::vector<Attribute> att) { attrs_ = att; }
  void Parse(std::vector<std::string> sql_vector);
};

typedef struct {
  int data_type;
  std::string value;
} SQLValue;

class SQLInsert : public SQL {
private:
  std::string tb_name_;
  std::vector<SQLValue> values_;

public:
  SQLInsert(std::vector<std::string> sql_vector) { Parse(sql_vector); }
  void Parse(std::vector<std::string> sql_vector);
  std::string tb_name() { return tb_name_; }
  std::vector<SQLValue> &values() { return values_; }
};

class SQLExec : public SQL {
private:
  std::string file_name_;

public:
  SQLExec(std::vector<std::string> sql_vector) { Parse(sql_vector); }
  void Parse(std::vector<std::string> sql_vector);
  std::string file_name() { return file_name_; }
};

typedef struct {
  std::string key;
  int sign_type;
  std::string value;
} SQLWhere;

class SQLSelect : public SQL {
private:
  std::string tb_name_;
  std::vector<SQLWhere> wheres_;

public:
  SQLSelect(std::vector<std::string> sql_vector) { Parse(sql_vector); }
  void Parse(std::vector<std::string> sql_vector);
  std::string tb_name() { return tb_name_; }
  std::vector<SQLWhere> &wheres() { return wheres_; }
};

class SQLCreateIndex : public SQL {
private:
  std::string index_name_;
  std::string tb_name_;
  std::string col_name_;

public:
  SQLCreateIndex(std::vector<std::string> sql_vector) { Parse(sql_vector); }
  void Parse(std::vector<std::string> sql_vector);
  std::string index_name() { return index_name_; }
  std::string tb_name() { return tb_name_; }
  std::string col_name() { return col_name_; }
};

class SQLDelete : public SQL {
private:
  std::string tb_name_;
  std::vector<SQLWhere> wheres_;

public:
  SQLDelete(std::vector<std::string> sql_vector) { Parse(sql_vector); }
  void Parse(std::vector<std::string> sql_vector);
  std::string tb_name() { return tb_name_; }
  std::vector<SQLWhere> &wheres() { return wheres_; }
};

typedef struct {
  std::string key;
  std::string value;
} SQLKeyValue;

class SQLUpdate : public SQL {
private:
  std::string tb_name_;
  std::vector<SQLWhere> wheres_;
  std::vector<SQLKeyValue> keyvalues_;

public:
  SQLUpdate(std::vector<std::string> sql_vector) { Parse(sql_vector); }
  void Parse(std::vector<std::string> sql_vector);
  std::string tb_name() { return tb_name_; }
  std::vector<SQLWhere> &wheres() { return wheres_; }
  std::vector<SQLKeyValue> &keyvalues() { return keyvalues_; }
};

#endif
