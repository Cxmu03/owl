#ifndef OWL_UTIL_HPP
#define OWL_UTIL_HPP

namespace owl {

template<typename T>
static constexpr inline T
MapToRange(T value, T valueRangeStart, T valueRangeEnd, T resultRangeStart, T resultRangeEnd) {
    return resultRangeStart +
           (((value - valueRangeStart) / (valueRangeEnd - valueRangeStart)) * (resultRangeEnd - resultRangeStart));
}

}

#endif //OWL_UTIL_HPP
