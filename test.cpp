#include <gtest/gtest.h>

#include <ip_filter.h>

using ip_filter::IpAddress;
using ip_filter::parseIp;

TEST(ParseIp, ParseIp) {

  static std::pair<const char*, IpAddress> table[] = {
    {"0.0.0.0", IpAddress(0, 0, 0, 0)},
    {"1.1.1.1", IpAddress(1, 1, 1, 1)},
    {"1.2.3.4", IpAddress(1, 2, 3, 4)},
    {"11.12.13.14", IpAddress(11, 12, 13, 14)},
    {"111.1.222.9", IpAddress(111, 1, 222, 9)},
    {"255.255.255.255", IpAddress(255, 255, 255, 255)},
  };

  for (auto [str, expectedIp] : table) {
    auto ip = parseIp(str);
    EXPECT_EQ(ip, expectedIp);
  }
}