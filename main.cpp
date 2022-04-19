
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

#include <ip_filter.h>

using ip_filter::IpAddress;
using ip_filter::parseIp;
using ip_filter::printIp;

template <typename Predicate>
void printIpsIf(const std::vector<IpAddress>& ips, Predicate pred) {
    for (auto& ip : ips) {
        if (pred(ip)) {
            std::cout << printIp(ip) << std::endl;
        }
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

    auto sortedIps = ips; // copy
    std::sort(begin(sortedIps), end(sortedIps), std::greater{});

    // Полный список адресов после сортировки. Одна строка - один адрес
    printIpsIf(sortedIps, [](const IpAddress&) { return true; });

    // Сразу следом список адресов, первый байт которых равен 1. Порядок сортировки не меняется.
    // Одна строка - один адрес. Списки ничем не разделяются
    printIpsIf(ips, [](const IpAddress& ip) { return ip.bytes[0] == 1; });

    // Сразу продолжается список адресов, первый байт которых равен 46, а второй 70. Порядок
    // сортировки не меняется. Одна строка - один адрес. Списки ничем не разделяются
    printIpsIf(ips, [](const IpAddress& ip) { return ip.bytes[0] == 46 && ip.bytes[1] == 70; });

    // Сразу продолжается список адресов, любой байт которых равен 46. Порядок сортировки не
    // меняется. Одна строка - один адрес. Списки ничем не разделяются
    printIpsIf(ips, [](const IpAddress& ip) { return std::find(begin(ip.bytes), end(ip.bytes), 46) != end(ip.bytes); });

    return 0;
}