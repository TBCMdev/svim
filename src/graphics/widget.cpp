#include "widget.hpp"

#include <sstream>

void s_widget::setLine(size_t line, const std::string& str)
{
    if (line >= lines.size())
        lines.resize(line + 1);

    lines.at(line) = str;
} 

std::string s_widget::drawContents()
{
    std::stringstream stream;

    for(size_t i = 0; i < lines.size(); i++)
    {
        std::string& line = lines.at(i);
        if (line.length() != (size_t)width)
            line.resize(width, ' ');
        auto iter = insersions.find(i);

        if (iter != insersions.end())
        {
            std::vector<s_widget_content_inserter> v = iter->second;

            size_t offset = 0;
            for(auto& inserter : v)
            {
                if (!inserter.cont) continue;
                size_t insertAt = inserter.at;
                
                if (!inserter.constant)
                    insertAt += offset;

                if (insertAt >= line.size())
                {
                    // insert at last possible char

                    long long x = static_cast<long long>(line.size()) - inserter.cont->length();

                    insertAt    = std::max(x, 0LL);
                }

                line.insert(insertAt, *inserter.cont);
            }

        }

        stream << line;
    }
    return stream.str();
}