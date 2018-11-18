#include <iostream>
#include <string>

#include <boost/algorithm/string.hpp>

#include "interpreter.h"


int main(int argc, const char* argv[]) {

    // output help info
    std::cout << "usage: example <sql>;" << std::endl;
    // check input
    if(argc != 2){
        return 1;
    }

    Interpreter itp;
    const char *line = argv[1];
    std::string sql = std::string(line);
    boost::algorithm::trim(sql);
    
    if (sql.compare(0, 4, "exit") == 0 || sql.compare(0, 4, "quit") == 0) {
        itp.ExecSQL("quit");
    }
    
    itp.ExecSQL(sql);
    std::cout << std::endl;

    return 0;
}