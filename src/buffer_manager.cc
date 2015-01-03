//  Copyright (c) 2014 Yan Chen.
//  All rights reserved.
//
//  Author: yan.chen.im@gmail.com (Yan Chen)

#include "buffer_manager.h"

#include <fstream>

#include "commons.h"

using namespace std;

BlockInfo* BufferManager::GetFileBlock(string db_name, string tb_name, int file_type, int block_num){
    
    fhandle_->IncreaseAge();
    
    FileInfo* file = fhandle_->GetFileInfo(db_name, tb_name, file_type);
	
	if(file){
        BlockInfo* block = fhandle_->GetBlockInfo(file, block_num);
        if (block) {
            return block;
        } else {
            BlockInfo* bp = GetUsableBlock();
            bp->set_block_num(block_num);
            bp->set_file(file);
            bp->ReadInfo(path_);
            fhandle_->AddBlockInfo(bp);
            return bp;
        }
	} else {
        BlockInfo* bp = GetUsableBlock();
        bp->set_block_num(block_num);
		FileInfo* fp = new FileInfo(db_name, file_type, tb_name, 0, 0, NULL, NULL);
        fhandle_->AddFileInfo(fp);
        bp->set_file(fp);
        bp->ReadInfo(path_);
        fhandle_->AddBlockInfo(bp);
        return bp;
	}
    return 0;
}

BlockInfo* BufferManager::GetUsableBlock() {
    if (bhandle_->bcount() > 0) {
        return bhandle_->GetUsableBlock();
    } else {
        return fhandle_->RecycleBlock();
    }
}

void BufferManager::WriteBlock(BlockInfo* block) {
    block->set_dirty(true);
}

void BufferManager::WriteToDisk() {
    fhandle_->WriteToDisk();
}