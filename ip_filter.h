#pragma once

#include <array>
#include <cinttypes>
#include <string_view>
#include <vector>

namespace ip_filter {

    struct IpAddress {
        std::array<std::uint8_t, 4> bytes;

        IpAddress() = default;
        IpAddress(std::uint8_t b1, std::uint8_t b2, std::uint8_t b3, std::uint8_t b4)
            : bytes { b1, b2, b3, b4 } {}

        bool operator==(const IpAddress& other) const {
            return bytes == other.bytes;
        }

        bool operator!=(const IpAddress& other) const {
            return !operator==(other);
        }
    };

    IpAddress parseIp(std::string_view ipStr);

    IpAddress parseIpLine(std::string_view ipLine);

    std::string printIp(const IpAddress& ip);

    
}