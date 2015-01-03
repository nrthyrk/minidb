//  Copyright (c) 2014 Yan Chen.
//  All rights reserved.
//
//  Author: yan.chen.im@gmail.com (Yan Chen)


#include "file_handle.h"

#include <fstream>

#include "commons.h"

using namespace std;

FileHandle::~FileHandle() {
    WriteToDisk();
    FileInfo* fp = first_file_;
    while (fp != NULL) {
        FileInfo* fpn = fp->next();
        BlockInfo* bp = fp->first_block();
        while (bp != NULL) {
            BlockInfo* bpn = bp->next();
            delete bp;
            bp = bpn;
        }
        delete fp;
        fp = fpn;
    }
}

void FileHandle::AddFileInfo(FileInfo* file) {
    FileInfo* p = first_file_;
    if (p == NULL) {
        p = file;
    } else {
        while (p->next() != NULL) {
            p = p->next();
        }
        p->set_next(file);
    }
}

FileInfo* FileHandle::GetFileInfo(std::string db_name, std::string tb_name, int file_type) {
    FileInfo* p = first_file_;
    while (p != NULL) {
        if (p->db_name() == db_name && p->type() == file_type && p->file_name() == tb_name) {
            return p;
        }
        p = p->next();
    }
    return NULL;
}

BlockInfo* FileHandle::GetBlockInfo(FileInfo* file, int block_pos) {
    BlockInfo* p = file->first_block();
    while (p != NULL) {
        if (p->block_num() == block_pos) {
            return p;
        }
        p = p->next();
    }
    return NULL;
}

void FileHandle::AddBlockInfo(BlockInfo* block) {
    BlockInfo* p = block->file()->first_block();
    if (p == NULL) {
        block->file()->set_first_block(block);
    } else {
        while (p->next() != NULL) {
            p = p->next();
        }
        p->set_next(block);
    }
    block->file()->IncreaseRecordAmount();
    block->file()->IncreaseRecordLength();
}

void FileHandle::IncreaseAge() {
    FileInfo* fp = first_file_;
    while (fp != NULL) {
        BlockInfo* bp = fp->first_block();
        while (bp != NULL) {
            bp->IncreaseAge();
            bp = bp->next();
        }
        fp = fp->next();
    }
}

BlockInfo* FileHandle::RecycleBlock() {
    
    FileInfo* fp = first_file_;
    
    BlockInfo* oldestbefore = NULL;
    BlockInfo* oldest = fp->first_block();
    
    while (fp != NULL) {
        BlockInfo* bpbefore = NULL;
        BlockInfo* bp = fp->first_block();
        while (bp != NULL) {
            
            if (bp->age() > oldest->age()) {
                oldestbefore = bpbefore;
                oldest = bp;
            }
            bpbefore = bp;
            bp = bp->next();
        }
        fp = fp->next();
    }
    
    if (oldest->dirty()) {
        oldest->WriteInfo(path_);
    }
    
    if (oldestbefore == NULL) {
        oldest->file()->set_first_block(oldest->next());
    } else {
        oldestbefore->set_next(oldest->next());
    }
    
    oldest->ResetAge();
    oldest->set_next(NULL);
    
    return oldest;
}

void FileHandle::WriteToDisk() {
    FileInfo* fp = first_file_;
    while (fp != NULL) {
        BlockInfo* bp = fp->first_block();
        while (bp != NULL) {
            if (bp->dirty()) {
                bp->WriteInfo(path_);
                bp->set_dirty(false);
            }
            bp = bp->next();
        }
        fp = fp->next();
    }
}