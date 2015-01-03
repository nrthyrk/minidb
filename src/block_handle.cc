//  Copyright (c) 2014 Yan Chen.
//  All rights reserved.
//
//  Author: yan.chen.im@gmail.com (Yan Chen)


#include "block_handle.h"

BlockHandle::~BlockHandle() {
    BlockInfo* p = first_block_;
    while (bcount_ > 0) {
        BlockInfo* pn = p->next();
        delete p;
        p = pn;
        bcount_--;
    }
}

BlockInfo* BlockHandle::Add(BlockInfo* block) {
    BlockInfo* adder = new BlockInfo(0);
    adder->set_next(block->next());
    block->set_next(adder);
    bcount_++;
    if (bcount_ == bsize_) {
        return adder;
    } else {
        return Add(adder);
    }
}

BlockInfo* BlockHandle::GetUsableBlock() {
    if (bcount_ == 0) {
        return NULL;
    }
    
    BlockInfo* p = first_block_->next();
    first_block_->set_next(first_block_->next()->next());
    bcount_--;
    p->ResetAge();
    p->set_next(NULL);
    return p;
}

void BlockHandle::FreeBlock(BlockInfo* block) {
    if (bcount_ == 0) {
        first_block_ = block;
        block->set_next(block);
    } else {
        block->set_next(first_block_->next());
        first_block_->set_next(block);
    }
    bcount_++;
}