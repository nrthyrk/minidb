//  Copyright (c) 2014 Yan Chen.
//  All rights reserved.
//
//  Author: yan.chen.im@gmail.com (Yan Chen)


#include "block_info.h"

#include <fstream>

#include "commons.h"

using namespace std;

void BlockInfo::ReadInfo(std::string path) {
    path += file_->db_name() + "/" + file_->file_name();
    
    if (file_->type() == FORMAT_INDEX) {
        path += ".index";
    } else {
        path += ".records";
    }
    
    ifstream ifs(path, ios::binary);
    ifs.seekg(block_num_*4*1024);
    ifs.read(data_, 4*1024);
    ifs.close();
}

void BlockInfo::WriteInfo(std::string path) {
    path += file_->db_name() + "/" + file_->file_name();
    
    if (file_->type() == FORMAT_INDEX) {
        path += ".index";
    } else {
        path += ".records";
    }
    
    ofstream ofs(path, ios::binary);
    ofs.seekp(block_num_*4*1024);
    ofs.write(data_, 4*1024);
    ofs.close();
}