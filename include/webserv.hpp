
#ifndef __WEBSERBER_HPP__
# define __WEBSERBER_HPP__

# include <WEBcommon.hpp>
# include <WEBrouter.hpp>
# include <WEBcore.hpp>

namespace web
{
    NORETURN void webserver(const std::string &addr, uint16_t port);
}

#endif /* __WEBSERBER_HPP__ */
