//  Copyright (c) 2014 Yan Chen.
//  All rights reserved.
//
//  Author: yan.chen.im@gmail.com (Yan Chen)

#ifndef MINIDB_RECORD_MANAGER_H_
#define MINIDB_RECORD_MANAGER_H_

#include <string>
#include <vector>

#include "block_info.h"
#include "buffer_manager.h"
#include "catalog_manager.h"
#include "exceptions.h"
#include "sql_statement.h"

class RecordManager {
private:
  BufferManager *hdl_;
  CatalogManager *cm_;
  std::string db_name_;

public:
  RecordManager(CatalogManager *cm, BufferManager *hdl, std::string db)
      : cm_(cm), hdl_(hdl), db_name_(db) {}
  ~RecordManager() {}
  void Insert(SQLInsert &st);
  void Select(SQLSelect &st);
  void Delete(SQLDelete &st);
  void Update(SQLUpdate &st);

  BlockInfo *GetBlockInfo(Table *tbl, int block_num);
  std::vector<TKey> GetRecord(Table *tbl, int block_num, int offset);
  void DeleteRecord(Table *tbl, int block_num, int offset);
  void UpdateRecord(Table *tbl, int block_num, int offset,
                    std::vector<int> &indices, std::vector<TKey> &values);

  bool SatisfyWhere(Table *tbl, std::vector<TKey> keys, SQLWhere where);
};

#endif /* MINIDB_RECORD_MANAGER_H_ */
