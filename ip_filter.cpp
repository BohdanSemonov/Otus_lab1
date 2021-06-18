#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
auto split(const std::string &str, char d)
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

    r.push_back(str.substr(start).c_str());

    return r;
}//split

auto ip_tostring(const std::vector<int> &ip)
{
   std::string ip_str;
   for (const auto &ip_part : ip)
       ip_str += std::to_string(ip_part) + ".";
   ip_str.erase(ip_str.end() - 1);

   return ip_str;
}

void ip_print(const std::vector<std::vector<int>> &ip_pool)
{
    for (const auto &ip : ip_pool)
        std::cout << ip_tostring(ip) << std::endl;
}

auto filter(const std::vector<std::vector<int>> &ip_pool)
{
    auto ip_pool_cp = ip_pool;
    std::sort(ip_pool_cp.begin(), ip_pool_cp.end(), std::greater<std::vector<int>>());
    return ip_pool_cp;
}//filter

auto filter(const std::vector<std::vector<int>> &ip_pool, int first_byte, int second_byte = -1)
{
    std::vector<std::vector<int>> ip_pool_cp;

    for (const auto ip : ip_pool)
    {
        if (ip.at(0) == first_byte && (second_byte == -1 || ip.at(1) == second_byte))
        ip_pool_cp.push_back(ip);
    }

    return filter(ip_pool_cp);
}//filter

auto filter_any(const std::vector<std::vector<int>> &ip_pool, int any_byte)
{
    std::vector<std::vector<int>> ip_pool_cp;

    for (const auto ip : ip_pool)
    {
        if (
            ip.at(0) == any_byte ||
            ip.at(1) == any_byte ||
            ip.at(2) == any_byte ||
            ip.at(3) == any_byte
           )
        ip_pool_cp.push_back(ip);
    }

    return filter(ip_pool_cp);
}//filter_any

int main()
{
    try
    {
        std::vector<std::vector<int>> ip_pool;
        std::vector<int> ip_int;

        for(std::string line; std::getline(std::cin, line);)
        {
            auto v = split(line, '\t');
            auto ip_str = split(v.at(0), '.');

            ip_int.clear();
            for (const auto ip_part : ip_str)
                ip_int.push_back(atoi(ip_part.c_str()));

            ip_pool.push_back(ip_int);
        }

        // Task 1
        ip_print(filter(ip_pool));

        // Task 2
        ip_print(filter(ip_pool, 1));

        // Task 3
        ip_print(filter(ip_pool, 46, 70));

        // Task 4
        ip_print(filter_any(ip_pool, 46));

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
