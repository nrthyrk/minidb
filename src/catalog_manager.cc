#include "catalog_manager.h"

#include <fstream>

#include <boost/filesystem.hpp>

using namespace std;

//=======================CatalogManager=======================//

CatalogManager::CatalogManager(std::string p):path_(p) {
    ReadArchiveFile();
}

CatalogManager::~CatalogManager() {
    WriteArchiveFile();
}

void CatalogManager::ReadArchiveFile() {
    std::string file_name = path_ + "catalog";
	boost::filesystem::path file_path(file_name);
    
    file_path.imbue(std::locale("en_US.UTF-8"));
    
    if (boost::filesystem::exists(file_path)) {
        std::ifstream ifs;
        ifs.open(file_name.c_str(), std::ios::binary);
        boost::archive::binary_iarchive iar( ifs );
        iar >> (*this);
        ifs.close();
    }
}

void CatalogManager::WriteArchiveFile() {
    std::string file_name = path_ + "catalog";
    
	std::ofstream ofs;
	ofs.open(file_name.c_str(),std::ios::binary);
	boost::archive::binary_oarchive oar( ofs );
    oar << (*this);
	ofs.close();
}

void CatalogManager::CreateDatabase(std::string dbname) {
    dbs_.push_back(Database(dbname));
}

void CatalogManager::DeleteDatabase(std::string dbname) {
    for(unsigned int i=0;i<dbs_.size();i++)
    {
        if(dbs_[i].db_name() == dbname)
        {
            dbs_.erase(dbs_.begin() + i);
        }
    }
}

Database* CatalogManager::GetDB(std::string db_name) {
    for (unsigned int i = 0; i < dbs_.size(); ++i) {
        if(dbs_[i].db_name() == db_name)
        {
            return &dbs_[i];
        }
    }
    return NULL;
}

//=======================Database=============================//

Database::Database(std::string dbname):db_name_(dbname) {
    
}

void Database::CreateTable(SQLCreateTable& st) {
    int record_length = 0;
    Table tb;
    for (int i=0; i<st.attrs().size(); ++i) {
        tb.AddAttribute(st.attrs()[i]);
        record_length += st.attrs()[i].length();
    }
    tb.set_tb_name(st.tb_name());
    tb.set_record_length(record_length);
    tbs_.push_back(tb);
}

void Database::DropTable(SQLDropTable& st) {
    vector<Table>::iterator i;
	for(i=tbs_.begin(); i!=tbs_.end(); i++) {
		if(i->tb_name()==st.tb_name()) {
            tbs_.erase(i);
            return;
        }
	}
}

void Database::DropIndex(SQLDropIndex& st) {
    for(int i=0; i<tbs_.size(); i++) {
		for(vector<Index>::iterator j = tbs_[i].ids().begin(); j<tbs_[i].ids().end(); j++) {
			if(j->name() == st.idx_name()) {
                tbs_[i].ids().erase(j);
				return;
            }
		}
	}
}

Table* Database::GetTable(std::string tb_name) {
    for (unsigned int i = 0; i < tbs_.size(); ++i) {
        if(tbs_[i].tb_name() == tb_name)
        {
            return &tbs_[i];
        }
    }
    return NULL;
}

bool Database::CheckIfIndexExists(std::string index_name) {
    bool exists = false;
    for (unsigned int i = 0; i < tbs_.size(); ++i) {
        for (unsigned int j = 0; j < tbs_[i].ids().size(); ++j) {
            if (tbs_[i].ids()[j].name() == index_name) {
                exists = true;
            }
        }
    }
    return exists;
}

//=======================Table===============================//

Attribute* Table::GetAttribute(std::string name) {
    for (unsigned int i = 0; i < ats_.size(); ++i) {
        if(ats_[i].attr_name() == name)
        {
            return &ats_[i];
        }
    }
    return NULL;
}

int Table::GetAttributeIndex(std::string name) {
    for (unsigned int i = 0; i < ats_.size(); ++i) {
        if(ats_[i].attr_name() == name)
        {
            return i;
        }
    }
    return -1;
}