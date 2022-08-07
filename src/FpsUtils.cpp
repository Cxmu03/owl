#include <stdint.h>
#include <thread>
#include <iostream>

#include <FpsUtils.hpp>

namespace owl {

auto FramerateLimiter::SetCapped(bool capped) -> void {
    m_Capped = capped;
}

auto FramerateLimiter::IsCapped() -> bool {
    return m_Capped;
}

auto FramerateLimiter::SetLimit(size_t limit) -> void {
    if (limit == 0) {
        m_Capped = false;
        return;
    }
    m_Capped = true;
    auto deltaSeconds = std::chrono::duration<double>(1. / static_cast<double>(limit));
    m_DeltaNanos = std::chrono::duration_cast<std::chrono::nanoseconds>(deltaSeconds);
}

auto FramerateLimiter::NextFrame() -> double {
    if (!m_LastTime.has_value()) {
        m_LastTime = std::chrono::steady_clock::now();
        return 0.;
    }

    auto currentTime = std::chrono::steady_clock::now();

    auto deltaSoFar = currentTime - m_LastTime.value();

    if (!enabled || !m_Capped || deltaSoFar > m_DeltaNanos) {
        m_LastTime = currentTime;
        return std::chrono::duration<double>(deltaSoFar).count();
    }

    auto sleepDuration = m_DeltaNanos - deltaSoFar;
    std::this_thread::sleep_for(sleepDuration);
    m_LastTime = std::chrono::steady_clock::now();
    return std::chrono::duration<double>(deltaSoFar + sleepDuration).count();
}

}