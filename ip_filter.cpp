#include "ip_filter.h"

#include <vector>
#include <string>
#include <sstream>

namespace {
    std::uint8_t str2byte(const std::string& s) {
        return static_cast<std::uint8_t>(std::stoul(s));
    }
}

namespace ip_filter {
    IpAddress parseIp(std::string_view ipStr) {
        std::vector<std::string> splitted;
        std::size_t pos = 0;
        while (true) {
            auto endPos = ipStr.find('.', pos);
            splitted.emplace_back(ipStr.substr(pos, endPos));
            if (endPos == ipStr.npos) {
                break;
            }
            pos = endPos + 1;
        }
        if (splitted.size() == 4) {
            return { str2byte(splitted[0]), str2byte(splitted[1]), str2byte(splitted[2]), str2byte(splitted[3]) };
        }
        return {};
    }

    std::string printIp(const IpAddress& ip) {
        std::stringstream ss;
        ss << static_cast<unsigned>(ip.bytes[0]) << '.'
            << static_cast<unsigned>(ip.bytes[1]) << '.'
            << static_cast<unsigned>(ip.bytes[2]) << '.'
            << static_cast<unsigned>(ip.bytes[3]);
        return ss.str();
    }
}