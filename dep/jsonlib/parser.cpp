//
// Created by geektcp on 11/14/23.
//

#include "parser.h"

#include <iostream>

Json::Value parser::parseString(std::string rawJson)
{
    const auto rawJsonLength = static_cast<int>(rawJson.length());
    JSONCPP_STRING err;
    Json::Value root;

    Json::CharReaderBuilder builder;
    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    if (!reader->parse(
            rawJson.c_str(),
            rawJson.c_str() + rawJsonLength,
            &root,
            &err))
    {
        printf("parse json failed: %s", rawJson);
    }

    return root;
}