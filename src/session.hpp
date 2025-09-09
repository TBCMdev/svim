#pragma once
#include <ctime>
#include <chrono>

struct file_info
{
    size_t lineCount;
    std::string content;
};

struct session
{
    time_t timestamp;
    std::unique_ptr<file_info> currentFileInfo;
    std::tm* tm_timestamp;

    std::chrono::steady_clock::time_point sessionBegin;

    int sessionHours, sessionSeconds, sessionMinutes;
};