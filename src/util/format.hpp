#pragma once
#include <string>


template<typename... _Tys>
inline std::string strfmt(const std::string& _param, _Tys&&... args)
{
    std::string str = _param;

    size_t L = str.length();
    size_t i = 0;
    const auto fmt = [&]<typename T>(T& arg1) -> void
    {
        for(; i < L; i++)
        {
            char c = str.at(i);

            switch(c)
            {
                case '{':
                {
                    char n;
                    if (i + 1 < L && (n = str.at(i + 1)) == '{')
                        continue;

                    if (n != '}')
                        continue;
                    if constexpr (std::is_arithmetic_v<T>)
                    {
                        std::string replacement = std::to_string(arg1);
                        str.replace(i, 2, replacement);
                        i += str.length() - 2;
                    }
                    else
                    {
                        str.replace(i, 2, arg1);
                        i += arg1.length() - 2;
                    }
                    L = str.length();
                    break;
                }
            }
        }
    };

    (fmt(args), ...);
    return str;

}