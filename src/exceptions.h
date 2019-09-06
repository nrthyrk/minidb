//  Copyright (c) 2014 Yan Chen.
//  All rights reserved.
//
//  Author: yan.chen.im@gmail.com (Yan Chen)

#ifndef MINIDB_EXCEPTIONS_H_
#define MINIDB_EXCEPTIONS_H_

#include <exception>

class SyntaxErrorException : public std::exception {};

class NoDatabaseSelectedException : public std::exception {};

class DatabaseNotExistException : public std::exception {};

class DatabaseAlreadyExistsException : public std::exception {};

class TableNotExistException : public std::exception {};

class TableAlreadyExistsException : public std::exception {};

class IndexAlreadyExistsException : public std::exception {};

class IndexNotExistException : public std::exception {};

class OneIndexEachTableException : public std::exception {};

class BPlusTreeException : public std::exception {};

class IndexMustBeCreatedOnPKException : public std::exception {};

class PrimaryKeyConflictException : public std::exception {};

#endif