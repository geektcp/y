// Copyright(c) 2015-present, Gabi Melman & spdlog contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef SPDLOG_COMPILED_LIB
    #error Please define SPDLOG_COMPILED_LIB to compile this file.
#endif

#include "async.h"
#include "async_logger-inl.h"
#include "log/spdlog/details/periodic_worker-inl.h"
#include "log/spdlog/details/thread_pool-inl.h"
