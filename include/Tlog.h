//
// Created by geektcp on 10/9/23.
//
#pragma once
#include "spdlog/spdlog.h"


class Tlog {
private:
    std::shared_ptr<spdlog::logger> _logger;

public:

    /**
     * Default constructor for Dummy (does nothing).
     */
    Tlog() = default;

    /**
     * Returns a bool.
     * @return Always True.
     */
    bool innerLog(){
        spdlog::info("Welcome to Tlog!");
        return false;
    }

    bool log();
};


