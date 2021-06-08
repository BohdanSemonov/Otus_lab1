#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}//split

auto ip_tostring(const std::vector<std::string> &ip)
{
   std::string ip_str;
   for (const auto &ip_part : ip)
       ip_str += ip_part + ".";
   ip_str.erase(ip_str.end() - 1);

   return ip_str;
}

void ip_print(const std::vector<std::vector<std::string>> &ip_pool)
{
    for (const auto &ip : ip_pool)
        std::cout << ip_tostring(ip) << std::endl;
}

auto filter(const std::vector<std::vector<std::string>> &ip_pool)
{
    auto ip_pool_cp = ip_pool;

    if (ip_pool_cp.size() < 2)
        return ip_pool_cp;

    // init ip bytes number
    constexpr int ipv4_bytes_num = 4;
    bool is_swap = false;
    size_t i = 1;

    do
    {
        is_swap = false;
        i = 1;
        do
        {
            int ip_bytes_prev[ipv4_bytes_num];
            int ip_bytes_curr[ipv4_bytes_num];

            for (int b = 0; b < ipv4_bytes_num; ++b)
                ip_bytes_prev[b] = atoi(ip_pool_cp[i - 1][b].c_str());
            for (int b = 0; b < ipv4_bytes_num; ++b)
                ip_bytes_curr[b] = atoi(ip_pool_cp[i][b].c_str());

            if (
                (ip_bytes_prev[0] < ip_bytes_curr[0]) ||
                (ip_bytes_prev[0] == ip_bytes_curr[0] && ip_bytes_prev[1] < ip_bytes_curr[1]) ||
                (ip_bytes_prev[0] == ip_bytes_curr[0] && ip_bytes_prev[1] == ip_bytes_curr[1] && ip_bytes_prev[2] < ip_bytes_curr[2]) ||
                (ip_bytes_prev[0] == ip_bytes_curr[0] && ip_bytes_prev[1] == ip_bytes_curr[1] && ip_bytes_prev[2] == ip_bytes_curr[2] && ip_bytes_prev[3] < ip_bytes_curr[3])
               )
            {
                auto tmp = ip_pool_cp[i];
                ip_pool_cp[i] = ip_pool_cp[i - 1];
                ip_pool_cp[i - 1] = tmp;
                is_swap = true;
            }

            ++i;
        } while (i < ip_pool_cp.size());
    } while (is_swap);

    return ip_pool_cp;
}//filter

auto filter(const std::vector<std::vector<std::string>> &ip_pool, const std::string &mask)
{
    std::vector<std::vector<std::string>> sorted_ip;

    for (const auto &ip : ip_pool)
    {
        auto cm = std::cmatch();
        bool is_match = std::regex_match(ip_tostring(ip).c_str(), cm, std::regex(mask));

        if (is_match)
            sorted_ip.push_back(ip);
    }

    return filter(sorted_ip);
}//filter

int main()
{
    try
    {
        std::vector<std::vector<std::string>> ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // Task 1
        ip_print(filter(ip_pool));

        // Task 2
        ip_print(filter(ip_pool, "1.[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}"));

        // Task 3
        ip_print(filter(ip_pool, "46.70.[0-9]{1,3}.[0-9]{1,3}"));

        // Task 4
        ip_print(filter(ip_pool, "(46.[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}|[0-9]{1,3}.46.[0-9]{1,3}.[0-9]{1,3}|[0-9]{1,3}.[0-9]{1,3}.46.[0-9]{1,3}|[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}.46)"));

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}//main
