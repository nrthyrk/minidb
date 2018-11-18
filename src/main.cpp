#include <iostream>
#include <string>

#include <readline/readline.h>
#include <readline/history.h>
#include <boost/algorithm/string.hpp>

#include "interpreter.h"

using namespace std;

int main(int argc, const char * argv[]) {

	string sql;
    Interpreter itp;
    
    char *line;
    size_t found;
    
    using_history();
    
    while (true) {
        line = readline ("MiniDB> ");
        sql = string(line);
        free(line);
        boost::algorithm::trim(sql);
        
        if (sql.compare(0, 4, "exit") == 0 || sql.compare(0, 4, "quit") == 0) {
            itp.ExecSQL("quit");
            break;
        }
        
        while((found = sql.find(";")) == string::npos) {
            line = readline("");
            sql += "\n" + string(line);
            free(line);
        }
        
        if (sql.length() != 0) {
            add_history(sql.c_str());
        }
        
        itp.ExecSQL(sql);
        std::cout << std::endl;
    }
    return 0;
}

