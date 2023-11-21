//
// Created by geektcp on 11/14/23.
//

#ifndef EXECUTOR_PASER_H
#define EXECUTOR_PASER_H

#include "json.h"

class parser {
public:
    static Json::Value parseString(std::string str);

};


#endif //EXECUTOR_PASER_H
