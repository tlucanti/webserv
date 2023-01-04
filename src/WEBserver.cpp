
#include <WEBcommon.hpp>
#include <WEBcore.hpp>

namespace WEBnamespace
{
    NORETURN void webserver(const std::string &addr, uint16_t port)
    {
        WEBcore core(addr, port);

        while (true) {
            WEBsocket sock;
            std::string content;

            switch (core.next_event(sock)) {
                case WEBcore::NO_EVENT:
                    usleep(100);
                    break ;
                case WEBcore::NEW_CLIENT:
                    break ;
                case WEBcore::POLL_IN:
                    content = sock.recv();
                    VERBOSE("server", "content:\n" + content);
                    break ;
            }
        }
    }
}

