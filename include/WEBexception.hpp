
#ifndef WEB_EXCEPTION_HPP
# define WEB_EXCEPTION_HPP

# include <stdexcept>
# include <string>

# include <WEBcommon.hpp>

namespace
{
    static constexpr const char *FORBIDDEN_HTML_PAGE =
    "<html>"
    "  <head>"
    "    <body>"
    "      <center>"
    "        <h1>403 Forbidden</h1>"
    "      </center>"
    "    </body>"
    "  </head>"
    "</html>";
}

namespace WEBnamespace
{
    class WEBexception : public std::runtime_error
    {
public:
        WEBexception(const std::string &str)
            : std::runtime_error(str.c_str())
        {}

        WEBexception(const char *str)
            : std::runtime_error(str)
        {}
    };

    class HTTPexception : public WEBexception
    {
public:
        HTTPexception(const std::string &content)
            : WEBexception(content)
        {}
    };

    class HTTPforbidden : public HTTPexception
    {
public:
        HTTPforbidden()
            : HTTPexception(FORBIDDEN_HTML_PAGE)
        {}
    };
}

#endif /* WEB_EXCEPTION_HPP */

