#pragma once

#include <string>
#include <string_view>
#include <fstream>
#include <sstream>
#include <numeric>

namespace owl::util {

template<typename T>
static constexpr inline T
MapToRange(T value, T valueRangeStart, T valueRangeEnd, T resultRangeStart, T resultRangeEnd) {
    return resultRangeStart +
           (((value - valueRangeStart) / (valueRangeEnd - valueRangeStart)) * (resultRangeEnd - resultRangeStart));
}

static inline std::string ReadFromFile(std::string_view path) {
    std::ifstream fileStream(path.data());
    std::stringstream stringStream;
    stringStream << fileStream.rdbuf();
    std::string fileContents = stringStream.str();
    return fileContents;
}

template <typename T>
static constexpr inline T DegToRad(T deg) {

}

template <typename T>
static constexpr inline T RadToDeg(T deg) {

}

}