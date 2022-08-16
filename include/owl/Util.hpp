#pragma once

#include <string>
#include <string_view>
#include <fstream>
#include <sstream>
#include <numeric>

namespace owl::util {

template<typename T>
static constexpr inline auto
MapToRange(T value, T valueRangeStart, T valueRangeEnd, T resultRangeStart, T resultRangeEnd) -> T {
    return resultRangeStart +
           (((value - valueRangeStart) / (valueRangeEnd - valueRangeStart)) * (resultRangeEnd - resultRangeStart));
}

static inline auto ReadFromFile(std::string_view path) -> std::string {
    std::ifstream fileStream(path.data());
    std::stringstream stringStream;
    stringStream << fileStream.rdbuf();
    std::string fileContents = stringStream.str();
    return fileContents;
}

template <typename T>
static constexpr inline auto DegToRad(T deg) -> T {
    return (static_cast<double>(deg) * std::numbers::pi) / 180.;
}

template <typename T>
static constexpr inline auto RadToDeg(T deg) -> T {
    return (static_cast<double>(deg) * 180.) / std::numbers::pi;
}

}