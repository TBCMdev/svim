#pragma once
#include <ctime>

struct session
{
    time_t timestamp;

    std::tm* tm_timestamp;
};