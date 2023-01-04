
#ifndef WEB_FILE_UTILS_HPP
# define WEB_FILE_UTILS_HPP

# include <fstream>
# include <string>
# include <sstream>

# include <WEBcommon>

namespace WEBnamespace
{
    namespace utils
    {
        inline bool file_exists(const std::string &fname) {
            return access(name.c_str(), F_OK) != -1;
        }

        inline std::string read_file(const std::string &fname) {
            std::ifstream f(name.c_str());
            std::stringstream buffer;

            PANIC_ON(f.bad(), "reader", "file `" + fname + "` not exists");
            buffer << f.rdbuf();
            return buffer.str();
        }
    }
}

#endif /* WEB_FILE_UTILS_HPP */

