//  Copyright (c) 2014 Yan Chen.
//  All rights reserved.
//
//  Author: yan.chen.im@gmail.com (Yan Chen)

#ifndef MINIDB_FILE_HANDLE_H_
#define MINIDB_FILE_HANDLE_H_

#include <string>

#include "block_info.h"
#include "file_info.h"

class FileHandle {
private:
  FileInfo *first_file_;
  std::string path_;

public:
  FileHandle(std::string p) : first_file_(new FileInfo()), path_(p) {}
  ~FileHandle();
  FileInfo *GetFileInfo(std::string db_name, std::string tb_name,
                        int file_type);
  BlockInfo *GetBlockInfo(FileInfo *file, int block_pos);
  void AddBlockInfo(BlockInfo *block);
  void IncreaseAge();
  BlockInfo *RecycleBlock();
  void AddFileInfo(FileInfo *file);
  void WriteToDisk();
};

#endif /* defined(MINIDB_FILE_HANDLE_H_) */
