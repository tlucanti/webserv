
#ifndef WEB_CORE_HPP
# define WEB_CORE_HPP

# include <vector>
# include <sys/poll.h>

# include <WEBcommon.hpp>
# include <WEBexception.hpp>
# include <WEBsocket.hpp>

namespace WEBnamespace
{
    class WEBcore
    {
    public:
        enum WEBcoreEvent
        {
            WEB_NO_EVENT,
            WEB_NEW_CLIENT,
            WEB_POLL_IN
        };

        WEBcore(const std::string &address, uint16_t port) :
            server_socket(address, port, true),
            polls_remaining(0),
            last_fd(-1)
        {}

        WEBcoreEvent next_event(WEBsocket &soc)
        {
            int new_client;

            new_client = _accept();
            if (new_client >= 0) {
                soc.assign(new_client);
                struct pollfd cli;
                cli.fd = new_client;
                cli.events = POLLIN;
                cli.revents = 0;
                clients.push_back(cli);
                return WEB_NEW_CLIENT;
            }

            if (polls_remaining == 0) {
                polls_remaining = poll(clients.data(), clients.size(), 0);
                last_fd = -1;
                PANIC_ON(polls_remaining < 0, "core", "poll error");
                if (polls_remaining == 0) {
                    return WEB_NO_EVENT;
                }
            }
            for (++last_fd; last_fd < static_cast<int>(clients.size()); ++last_fd) {
                if (clients.at(last_fd).revents & POLLIN) {
                    clients.at(last_fd).revents = 0;
                    --polls_remaining;
                    soc.assign(clients.at(last_fd).fd);
                    return WEB_POLL_IN;
                }
            }
            PANIC_ON(true, "core", "no events after poll");
        }


    private:
        int _accept()
        {
            struct sockaddr addr;
            socklen_t addrlen;
            int sock;

            sock = accept(server_socket.fd(), &addr, &addrlen);
            PANIC_ON(sock < 0 and errno != EAGAIN, "core", "cannot accept socket");
            if (sock >= 0)
                INFO("core", "accepted client " << sock << ' ' << errno);
            return sock;
        }

        WEBsocket server_socket;
        int polls_remaining;
        int last_fd;
        std::vector<struct pollfd> clients;
    };
}

#endif /* WEB_SERVER_HPP */
