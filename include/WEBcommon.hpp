
#ifndef WEB_COMMON_HPP
# define WEB_COMMON_HPP

# define WEBnamespace web

# ifdef __cpp23
#  define ATTRIBUTE(__attr) [[__attr]]
#  define WUR ATTRIBUTE(nodiscard)
#  define UNUSED ATRRIBUTE(maybe_unused)
#  define NORETURN ATTRIBUTE(noreturn)
# else /* __cpp98 */
#  define ATTRIBUTE(__attr) __attribute__((__attr))
#  define WUR ATTRIBUTE(__warn_unused_result__)
#  define UNUSED ATTRIBUTE(__unused__)
#  define NORETURN ATTRIBUTE(__noreturn__)
# endif /* __cpp98 */


# include <sys/types.h>
# include <errno.h>
# include <string>
# include <sstream>
# include <cstring>
# include <iostream>
# include <color.hpp>
# include <cstdlib>

# define __log_msg(__parent, __msg, __level) do {                       \
    std::cout << __level << ANSI_YELLOW << __parent <<                  \
        ANSI_WHITE ": " << __msg <<                                     \
        ANSI_PURPLE << " (" << std::strerror(errno) << ")\n" ANSI_RESET;\
    errno = 0;                                                          \
} while (false)

# define __panic_on_msg(__expr, __parent, __msg, __file, __line) do {   \
    if (__expr) {                                                       \
        ERR(__parent, __msg);                                           \
        __panic_on(true, __file, __line);                               \
    }                                                                   \
} while (false)

# define __panic_on(__expr, __file, __line) do {                        \
    if (__expr) {                                                       \
        std::cout << ANSI_DARK_RED "panic on " <<                            \
            __file << ":" << __line << ANSI_RESET "\n";                 \
        std::abort();                                                   \
    }                                                                   \
} while (false)

# define INFO(__parent, __msg)  __log_msg(__parent, __msg, ANSI_BLUE "[INFO] ")
# define OK(__parent, __msg)    __log_msg(__parent, __msg, ANSI_GREEN "[ OK ] ")
# define WARN(__parent, __msg)  __log_msg(__parent, __msg, ANSI_YELLOW "[WARN] ")
# define ERR(__parent, __msg)   __log_msg(__parent, __msg, ANSI_RED "[PANIC] ")
# ifdef DO_VERBOSE
#  define VERBOSE(__parent, __msg) __log_msg(__parent, __msg, "")
# else
#  define VERBOSE(__parent, __msg) /* empty */
# endif /* DO_VERBOSE */

# define PANIC_ON(__expr, __parent, __msg) __panic_on_msg(__expr, __parent, __msg, __FILE__, __LINE__)
# define ALWAYS_ZERO(__expr) __panic_on((__expr) != 0, __FILE__, __LINE__)
# define ALWAYS_POSITIVE(__expr) __panic_on((__expr) < 0, __FILE__, __LINE__)

namespace WEBnamespace
{
    namespace utils
    {
        class noncopyble
        {
        public:
# ifdef __cpp23
            noncopyble() = default;
            noncopyble(const noncopyble &) = delete;
            noncopyble &operator =(const noncopyble &) = delete;
# endif
        };

        class nonmovable
        {
        public:
# ifdef __cpp23
            nonmovable() = default;
            nonmovable(const nonmovable &&) = delete;
            nonmovable &&operator =(const nonmovable &&) = delete;
# endif
        };

        class noncopymovable : public noncopyble, public nonmovable
        {
        public:
# ifdef __cpp23
            noncopymovable() = default;
# endif
        };
    }
}

class stringifier
{
public:
    std::ostream *save;

    template <class value_type>
    friend stringifier &operator <<(stringifier &s, const value_type &v)
    {
        *s.save << ' ' << v;
        return s;
    }

    friend stringifier &operator <<(std::ostream &out, stringifier &s)
    {
        s.save = &out;
        return s;
    }
};


inline stringifier SS;

#endif /* WEB_COMMON_HPP */

