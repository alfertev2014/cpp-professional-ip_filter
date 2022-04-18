#pragma once

#include <array>
#include <cinttypes>
#include <string_view>
#include <vector>

namespace ip_filter {

    // We could simply use
    // using IpAddress = std::array<std::uint8_t, 4>;

    struct IpAddress {
        std::array<std::uint8_t, 4> bytes;

        IpAddress() = default;
        IpAddress(std::uint8_t b1, std::uint8_t b2, std::uint8_t b3, std::uint8_t b4)
            : bytes { b1, b2, b3, b4 } {}

        inline bool operator==(const IpAddress& other) const {
            return bytes == other.bytes;
        }

        inline bool operator!=(const IpAddress& other) const {
            return bytes != other.bytes;
        }

        inline bool operator<(const IpAddress& other) const {
            return bytes < other.bytes;
        }

        inline bool operator>(const IpAddress& other) const {
            return bytes > other.bytes;
        }

        inline bool operator<=(const IpAddress& other) const {
            return bytes <= other.bytes;
        }

        inline bool operator>=(const IpAddress& other) const {
            return bytes >= other.bytes;
        }

        // We have no operator<=> in C++17 :(
    };

    IpAddress parseIp(std::string_view ipStr);

    std::string printIp(const IpAddress& ip);


}