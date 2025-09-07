#include "file.hpp"


std::optional<std::string> readfile(const char* fileName)
{
    std::ifstream fstream(fileName);

    if (!fstream.good()) return std::optional<std::string>();

    std::string str;

    while(fstream >> str);

    return str;
}