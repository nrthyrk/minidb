//  Copyright (c) 2014 Yan Chen.
//  All rights reserved.
//
//  Author: yan.chen.im@gmail.com (Yan Chen)

#ifndef MINIDB_BUFFER_MANAGER_H_
#define MINIDB_BUFFER_MANAGER_H_

#include <string>

#include "block_handle.h"
#include "file_handle.h"

class BufferManager {
private:
    BlockHandle* bhandle_;
    FileHandle* fhandle_;
    std::string path_;
    
    BlockInfo* GetUsableBlock();
public:
    BufferManager(std::string p):bhandle_(new BlockHandle(p)), fhandle_(new FileHandle(p)), path_(p) {}
    ~BufferManager() {
        delete bhandle_;
        delete fhandle_;
    }
    
    BlockInfo* GetFileBlock(std::string db_name, std::string tb_name, int file_type, int block_num);
    void WriteBlock(BlockInfo* block);
    void WriteToDisk();
};

#endif /* defined(MINIDB_HANDLE_H_) */
