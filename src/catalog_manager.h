#ifndef MINIDB_CATALOG_MANAGER_H_
#define MINIDB_CATALOG_MANAGER_H_

#include <vector>
#include <string>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/vector.hpp>

#include "sql_statement.h"

class Database;
class Table;
class Attribute;
class Index;
class SQLCreateTable;
class SQLDropTable;
class SQLDropIndex;

class CatalogManager {
private:
    friend class boost::serialization::access;
    
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & dbs_;
    }
    std::string path_;
    std::vector<Database> dbs_;
public:
    CatalogManager(std::string p);
    ~CatalogManager();
    std::vector<Database>& dbs() { return dbs_; }
    std::string path() { return path_; }
    Database* GetDB(std::string db_name);
    void ReadArchiveFile();
    void WriteArchiveFile();
    void CreateDatabase(std::string dbname);
    void DeleteDatabase(std::string dbname);
};

class Database {
private:
    friend class boost::serialization::access;
    
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & db_name_;
        ar & tbs_;
    }
    std::string db_name_;
    std::vector<Table> tbs_;
public:
    Database() {}
    Database(std::string dbname);
    ~Database() {}
    Table* GetTable(std::string tb_name);
    std::string db_name() { return db_name_; }
    void CreateTable(SQLCreateTable& st);
    void DropTable(SQLDropTable& st);
    void DropIndex(SQLDropIndex& st);
    std::vector<Table>& tbs() { return tbs_; }
    bool CheckIfIndexExists(std::string index_name);
};

class Table {
private:
    friend class boost::serialization::access;
    
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & tb_name_;
        ar & record_length_;
        ar & first_block_num_;
        ar & first_rubbish_num_;
        ar & block_count_;
        ar & ats_;
        ar & ids_;
    }
    
    std::string tb_name_;
    int record_length_;
    
    int first_block_num_;
    int first_rubbish_num_;
    int block_count_;
    
    std::vector<Attribute> ats_;
    std::vector<Index> ids_;
public:
    Table():tb_name_(""),
    		record_length_(-1),
    		first_block_num_(-1),
    		first_rubbish_num_(-1),
    		block_count_(0) {}
    ~Table() {}
    
    std::string tb_name() { return tb_name_; }
    void set_tb_name(std::string tbname) { tb_name_ = tbname; }
    
    int record_length() { return record_length_; }
    void set_record_length(int len) { record_length_ = len; }
    
    std::vector<Attribute>& ats() { return ats_; }
    Attribute* GetAttribute(std::string name);
    int GetAttributeIndex(std::string name);
    
    int first_block_num() { return first_block_num_; }
    void set_first_block_num(int num) { first_block_num_ = num; }
    int first_rubbish_num() { return first_rubbish_num_; }
    void set_first_rubbish_num(int num) { first_rubbish_num_ = num; }
    int block_count() { return block_count_; }
    
    unsigned long GetAttributeNum() { return ats_.size(); }
    void AddAttribute(Attribute& attr) { ats_.push_back(attr); }
    void IncreaseBlockCount() { block_count_++; }
    
    std::vector<Index>& ids() { return ids_; }
    Index* GetIndex(int num) { return &(ids_[num]); }
    unsigned long GetIndexNum() { return ids_.size(); }
    void AddIndex(Index& idx) { ids_.push_back(idx); }
};

class Attribute {
private:
    friend class boost::serialization::access;
    
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & attr_name_;
        ar & data_type_;
        ar & length_;
        ar & attr_type_;
    }
    
    std::string attr_name_;
    int data_type_;
    int length_;
    int attr_type_;
public:
    Attribute():attr_name_(""),data_type_(-1),length_(-1),attr_type_(0) {}
    ~Attribute() {}
    
    std::string attr_name() { return attr_name_; }
    
    void set_attr_name(std::string name) { attr_name_ = name; }
    
    int attr_type() { return attr_type_; }
    void set_attr_type(int type) { attr_type_ = type; }
    
    int data_type() { return data_type_; }
    void set_data_type(int type) { data_type_ = type; }
    
    void set_length(int length) { length_ = length; }
    int length() { return length_; }
};

class Index {
private:
    friend class boost::serialization::access;
    
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & max_count_;
		ar & attr_name_;
		ar & name_;
		ar & key_len_;
		ar & key_type_;
		ar & rank_;
		ar & rubbish_;
		ar & root_;
		ar & leaf_head_;
		ar & key_count_;
		ar & level_;
		ar & node_count_;
    }
    int max_count_;
	int key_len_;
	int key_type_;
	int rank_;
	int rubbish_;
	int root_;
	int leaf_head_;
	int key_count_;
	int level_;
	int node_count_;
    std::string attr_name_;
    std::string name_;
public:
    Index() {}
    Index(std::string name, std::string attr_name, int keytype, int keylen,int rank)
	{
        attr_name_ = attr_name;
        name_ = name;
		key_count_ = 0;
		level_ = -1;
		node_count_ = 0;
		root_ = -1;
		leaf_head_ = -1;
		key_type_ = keytype;
		key_len_ = keylen;
		rank_ = rank;
		rubbish_ = -1;
		max_count_ = 0;
	}
    
    // accessors and mutators
    std::string attr_name() { return attr_name_; }
    
    int key_len() { return key_len_; }
    
	int key_type() { return key_type_; }
    
    int rank() { return rank_; }
    
    int root() { return root_; }
    void set_root(int root) { root_ = root; }
    
    int leaf_head() { return leaf_head_; }
    void set_leaf_head(int leaf_head) { leaf_head_ = leaf_head; }
    
    int key_count() { return key_count_; }
    void set_key_count(int key_count) { key_count_ = key_count; }
    
    int level() { return level_; }
    void set_level(int level) { level_ = level; }
    
    int node_count() { return node_count_; }
    void set_node_count(int node_count) { node_count_ = node_count; }
    
    std::string name() { return name_; }
    
    int IncreaseMaxCount() { return max_count_++; }
    int IncreaseKeyCount() { return key_count_++; }
    int IncreaseNodeCount() { return node_count_++; }
    int IncreaseLevel() { return level_++; }
    int DecreaseKeyCount() { return key_count_--; }
    int DecreaseNodeCount() { return node_count_--; }
    int DecreaseLevel() { return level_--; }
};

#endif
