
#include <WEBcommon.hpp>
#include <WEBcore.hpp>

namespace WEBnamespace
{
    namespace {
        struct worker_data {
            pthread_mutex_t lock;
            WEBcore *core;
        };

        NORETURN void *_poll_worker(struct worker_data *data)
        {
            WEBsocket sock;
            std::string content;

            while (true) {
                data->core->next_poll(sock);
                content = sock.recv();
                VERBOSE("server", "content from cilent " << sock.fd() << ": " << content);
            }
        }

        NORETURN void *_accept_worker(struct worker_data *data)
        {
            WEBsocket sock;

            while (true) {
                if (data->core->next_accept(sock)) {
                    VERBOSE("server", "added new client " << sock.fd());
                } else {
                    usleep(100000);
                }
            }
        }
    }

    NORETURN void webserver(const std::string &addr, uint16_t port)
    {
        pthread_t poll_worker, accept_worker;
        pthread_mutex_t lock;
        struct worker_data_
        WEBcore core(addr, port);

        pthread_create()
    }
}

