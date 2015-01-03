//  Copyright (c) 2014 Yan Chen.
//  All rights reserved.
//
//  Author: yan.chen.im@gmail.com (Yan Chen)

#ifndef MINIDB_INTERPRETER_H_
#define MINIDB_INTERPRETER_H_

#include <string>
#include <vector>

#include "sql_statement.h"
#include "minidb_api.h"

class Interpreter {
private:
    MiniDBAPI* api;
    std::string sql_statement_;
    std::vector<std::string> sql_vector_;
    int sql_type_;
    void TellSQLType();
    void FormatSQL();
    void Run();
public:
    Interpreter();
    ~Interpreter();
    void ExecSQL(std::string statement);
};

#endif /* MINIDB_INTERPRETER_H_ */
