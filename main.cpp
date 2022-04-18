
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

#include <ip_filter.h>

using ip_filter::IpAddress;
using ip_filter::parseIp;
using ip_filter::printIp;

void printIps(const std::vector<IpAddress>& ips) {
    for (auto &ip : ips) {
        std::cout << printIp(ip) << std::endl;
    }
}

int main() {
    std::string line;
    std::vector<IpAddress> ips;
    while (std::getline(std::cin, line)) {
        const std::string ipStr = line.substr(0, line.find('\t'));
        IpAddress&& ip = parseIp(ipStr);
        ips.emplace_back(std::move(ip));
    }

    std::sort(std::begin(ips), std::end(ips), std::greater{});

    printIps(ips);

    return 0;
}