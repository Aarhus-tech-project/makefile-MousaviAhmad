#include "hanoi.hpp"
#include <stdexcept>
#include <limits>

std::uint64_t calculate_minimum_hanoi_moves(int disk_count) {
    if (disk_count < 0) {
        throw std::invalid_argument("disk_count must be >= 0");
    }
    if (disk_count >= static_cast<int>(std::numeric_limits<std::uint64_t>::digits)) {
        throw std::out_of_range("disk_count too large to compute 2^n - 1 in 64-bit");
    }
    if (disk_count == 0) return 0ULL;
    return (1ULL << disk_count) - 1ULL;
}
