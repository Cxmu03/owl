#pragma once

#include <chrono>
#include <optional>

namespace owl {

class FramerateLimiter {
public:
    FramerateLimiter() : enabled(true), m_Capped(false) {}

public:
    auto SetLimit(size_t) -> void;
    auto SetCapped(bool) -> void;
    auto IsCapped() -> bool;
    auto NextFrame() -> double;

public:
    bool enabled;

private:
    bool m_Capped;
    std::chrono::nanoseconds m_DeltaNanos;
    std::chrono::steady_clock::time_point t1;
    std::chrono::steady_clock::time_point t2;
    std::optional<std::chrono::steady_clock::time_point> m_LastTime;
};

}