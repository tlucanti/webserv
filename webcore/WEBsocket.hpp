
#ifndef WEB_SOCKET_HPP
# define WEB_SOCKET_HPP

# include <sys/socket.h>
# include <unistd.h>
# include <fcntl.h>
# include <arpa/inet.h>

# include <WEBcommon.hpp>

namespace WEBnamespace
{
    class WEBsocket
    {
    public:
        WEBsocket() :
            sock(-1)
        {}

        WEBsocket(const std::string &address, uint16_t port, bool nonblock=true)
        {
            struct sockaddr_in addr;
            int yes = 1;

            sock = socket(AF_INET, SOCK_STREAM, 0);
            PANIC_ON(sock < 0, "socket", "canno create socket");
            if (nonblock) {
                ALWAYS_POSITIVE(fcntl(sock, F_SETFL, O_NONBLOCK));
            }
            ALWAYS_ZERO(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)));
            PANIC_ON(inet_pton(AF_INET, address.c_str(), &addr.sin_addr) <= 0,
                     "socket", "invalid address: " + address);
            addr.sin_port = htons(port);
            PANIC_ON(bind(sock,
                          reinterpret_cast<sockaddr *>(&addr),
                          sizeof(struct sockaddr_in)),
                     "socket", "cannot bind port");
            PANIC_ON(listen(sock, 20), "sock", "cannot listen port");
        }

        std::string recv()
        {
            std::string content(4096, 0);

            ::recv(sock, content.data(), 4096, 0);
            return content;
        }

        void assign(int fd)
        {
            sock = fd;
        }

        int fd() const
        {
            return sock;
        }

    private:
        int sock;
    };
}

#endif /* WEB_SOCKET_HPP */
