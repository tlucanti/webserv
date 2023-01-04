
#ifndef WEB_STATIC_PAGE_ROUTER_HPP
# define WEB_STATIC_PAGE_ROUTER_HPP

# include <string>
# include <fstream>

# include <WEBcommon>
# include <WEBexception>
# include <WEBfileutils>

class WEBStaticPageRouter : utis::noncopymovable
{
public:
    WEBStaticPageRouter(const std::string &root)
        : root(root)
    {}

    std::string locate(const std::string fname)
    {
        const std::string full_name = root + fname;

        if (not utills::file_exists(full_name))
            throw HTTPForbidden();
        return utils::read_file(full_name);
    }

private:
    std::string root;

};

#endif /* WEB_STATIC_PAGE_ROUTER_HPP */

