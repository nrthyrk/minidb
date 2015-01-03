//  Copyright (c) 2014 Yan Chen.
//  All rights reserved.
//
//  Author: yan.chen.im@gmail.com (Yan Chen)


#ifndef MINIDB_BLOCK_INFO_H_
#define MINIDB_BLOCK_INFO_H_

#include <sys/types.h>

#include "file_info.h"
#include "commons.h"

class FileInfo;

class BlockInfo {
private:
    FileInfo *file_;
    int block_num_;
    char *data_;
    bool dirty_;
    long age_;
    BlockInfo *next_;
public:
    BlockInfo(int num):dirty_(false), next_(NULL), file_(NULL), age_(0), block_num_(num) {
        data_ = new char[4*1024];
    }
    virtual ~BlockInfo() {
        delete[] data_;
    }
    FileInfo* file() { return file_; }
    void set_file(FileInfo* f) { file_ = f; }
    
    int block_num() { return block_num_; }
    void set_block_num(int num) { block_num_ = num; }
    
    char* data() { return data_; }
    
    long age() { return age_; }
    
    bool dirty() { return dirty_; }
    void set_dirty(bool dt) { dirty_ = true; }
    
    BlockInfo* next() { return next_; }
    void set_next(BlockInfo* block) { next_ = block; }
    
    void IncreaseAge() { ++age_; }
    void ResetAge() { age_ = 0; }
    
    void SetPrevBlockNum(int num) {
        *(int*)(data_) = num;
    }
    
    int GetPrevBlockNum() {
        return *(int*)(data_);
    }
    
    void SetNextBlockNum(int num) {
        *(int*)(data_+4) = num;
    }
    
    int GetNextBlockNum() {
        return *(int*)(data_+4);
    }
    
    void SetRecordCount(int count) {
        *(int*)(data_+8) = count;
    }
    
    void DecreaseRecordCount() {
        *(int*)(data_+8) = *(int*)(data_+8) - 1;
    }
    
    int GetRecordCount() {
        return *(int*)(data_+8);
    }
    
    char* GetContentAddress() { return data_ + 12; }
    
    void ReadInfo(std::string path);
    void WriteInfo(std::string path);
};

#endif /* MINIDB_BLOCK_INFO_H_ */
