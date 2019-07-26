/**
 * @file    TimeSpan.h
 * @author  ggomdyu
 * @since   07/16/2019
 */

#pragma once
#include <cstdint>

namespace tgon
{

class TimeSpan final
{
/**@section Constructor */
public:
    constexpr TimeSpan(int32_t hours, int32_t minutes, int32_t seconds) noexcept;
    constexpr TimeSpan(int32_t days, int32_t hours, int32_t minutes, int32_t seconds) noexcept;
    constexpr TimeSpan(int32_t days, int32_t hours, int32_t minutes, int32_t seconds, int32_t milliseconds) noexcept;
    constexpr explicit TimeSpan(int64_t ticks) noexcept;

/**@section Operator */
public:
    constexpr bool operator==(const TimeSpan& rhs) const noexcept;
    constexpr bool operator!=(const TimeSpan& rhs) const noexcept;
    constexpr bool operator>(const TimeSpan& rhs) const noexcept;
    constexpr bool operator>=(const TimeSpan& rhs) const noexcept;
    constexpr bool operator<(const TimeSpan& rhs) const noexcept;
    constexpr bool operator<=(const TimeSpan& rhs) const noexcept;
    constexpr TimeSpan operator+(const TimeSpan& rhs) const noexcept;
    constexpr TimeSpan operator-(const TimeSpan& rhs) const noexcept;
    TimeSpan& operator+=(const TimeSpan& rhs) noexcept;
    TimeSpan& operator-=(const TimeSpan& rhs) noexcept;
    constexpr TimeSpan operator*(const TimeSpan& timeSpan) const noexcept;
    friend constexpr TimeSpan operator*(double factor, const TimeSpan& timeSpan) noexcept;
    constexpr TimeSpan operator/(double divisor) const noexcept;
    constexpr TimeSpan operator-() const noexcept;
    constexpr TimeSpan operator+() const noexcept;

/**@section Method */
public:
    static constexpr int Compare(const TimeSpan& lhs, const TimeSpan& rhs) noexcept;
    constexpr int CompareTo(const TimeSpan& value) const noexcept;
    constexpr int32_t GetDays() const noexcept;
    constexpr int32_t GetHours() const noexcept;
    constexpr int32_t GetMinutes() const noexcept;
    constexpr int32_t GetSeconds() const noexcept;
    constexpr int32_t GetMilliseconds() const noexcept;
    constexpr int64_t GetTicks() const noexcept;
    constexpr double GetTotalDays() const noexcept;
    constexpr double GetTotalHours() const noexcept;
    constexpr double GetTotalMinutes() const noexcept;
    constexpr double GetTotalSeconds() const noexcept;
    constexpr double GetTotalMilliseconds() const noexcept;
    constexpr TimeSpan Add(const TimeSpan& timeSpan) const noexcept;
    constexpr TimeSpan Divide(double divisor) const noexcept;
    constexpr double Divide(const TimeSpan& timeSpan) const noexcept;
    constexpr TimeSpan Multiply(double factor) const noexcept;
    constexpr TimeSpan Negate() const noexcept;
    constexpr TimeSpan Subtract(const TimeSpan& timeSpan) const noexcept;
    constexpr TimeSpan Duration() const noexcept;
    static constexpr TimeSpan FromDays(double value) noexcept;
    static constexpr TimeSpan FromHours(double value) noexcept;
    static constexpr TimeSpan FromMinutes(double value) noexcept;
    static constexpr TimeSpan FromSeconds(double value) noexcept;
    static constexpr TimeSpan FromMilliseconds(double value) noexcept;
    static constexpr TimeSpan FromTicks(int64_t value) noexcept;
    constexpr size_t GetHashCode() const noexcept;
    //string ToString();
    //string ToString(string format);
    //string ToString(string format, IFormatProvider formatProvider);

private:
    static constexpr int64_t TimeToTicks(int32_t hour, int32_t minute, int32_t second) noexcept;

/**@section Variable */
public:
    //static readonly TimeSpan MaxValue;
    //static readonly TimeSpan MinValue;
    //static constexpr TimeSpan Zero;

    static constexpr int64_t TicksPerMillisecond = 10000;
    static constexpr int64_t TicksPerSecond = TicksPerMillisecond * 1000;
    static constexpr int64_t TicksPerMinute = TicksPerSecond * 60;
    static constexpr int64_t TicksPerHour = TicksPerMinute * 60;
    static constexpr int64_t TicksPerDay = TicksPerHour * 24;

private:
    static constexpr double DaysPerTick = 1.0 / TicksPerDay;
    static constexpr double HoursPerTick = 1.0 / TicksPerHour;
    static constexpr double MinutesPerTick = 1.0 / TicksPerMinute;
    static constexpr double SecondsPerTick = 1.0 / TicksPerSecond;
    static constexpr double MillisecondsPerTick = 1.0 / TicksPerMillisecond;

    int64_t m_ticks;
};

constexpr TimeSpan::TimeSpan(int32_t hours, int32_t minutes, int32_t seconds) noexcept :
    TimeSpan(0, hours, minutes, seconds, 0)
{
}

constexpr TimeSpan::TimeSpan(int32_t days, int32_t hours, int32_t minutes, int32_t seconds) noexcept :
    TimeSpan(days, hours, minutes, seconds, 0)
{
}

constexpr TimeSpan::TimeSpan(int32_t days, int32_t hours, int32_t minutes, int32_t seconds, int32_t milliseconds) noexcept :
    m_ticks((TicksPerDay * days) + (TicksPerHour * hours) + (TicksPerMinute * minutes) + (TicksPerSecond * seconds) + (TicksPerMillisecond * milliseconds))
{
}

constexpr TimeSpan::TimeSpan(int64_t ticks) noexcept :
    m_ticks(ticks)
{
}

constexpr bool TimeSpan::operator==(const TimeSpan& rhs) const noexcept
{
    return m_ticks == rhs.m_ticks;
}

constexpr bool TimeSpan::operator!=(const TimeSpan& rhs) const noexcept
{
    return m_ticks != rhs.m_ticks;
}

constexpr bool TimeSpan::operator>(const TimeSpan& rhs) const noexcept
{
    return m_ticks > rhs.m_ticks;
}

constexpr bool TimeSpan::operator>=(const TimeSpan& rhs) const noexcept
{
    return m_ticks >= rhs.m_ticks;
}

constexpr bool TimeSpan::operator<(const TimeSpan& rhs) const noexcept
{
    return m_ticks < rhs.m_ticks;
}

constexpr bool TimeSpan::operator<=(const TimeSpan& rhs) const noexcept
{
    return m_ticks <= rhs.m_ticks;
}

constexpr TimeSpan TimeSpan::operator*(const TimeSpan& timeSpan) const noexcept
{
    return TimeSpan(m_ticks * timeSpan.m_ticks);
}

constexpr TimeSpan TimeSpan::operator+(const TimeSpan& rhs) const noexcept
{
    return TimeSpan(m_ticks + rhs.m_ticks);
}

constexpr TimeSpan TimeSpan::operator-(const TimeSpan& rhs) const noexcept
{
    return TimeSpan(m_ticks - rhs.m_ticks);
}

inline TimeSpan& TimeSpan::operator+=(const TimeSpan& rhs) noexcept
{
    m_ticks += rhs.m_ticks;
    return *this;
}

inline TimeSpan& TimeSpan::operator-=(const TimeSpan& rhs) noexcept
{
    m_ticks -= rhs.m_ticks;
    return *this;
}

constexpr TimeSpan TimeSpan::operator/(double divisor) const noexcept
{
    return TimeSpan(static_cast<int64_t>(static_cast<double>(m_ticks) / divisor));
}

constexpr TimeSpan operator*(double factor, const TimeSpan& timeSpan) noexcept
{
    return TimeSpan(static_cast<int64_t>(factor * static_cast<double>(timeSpan.m_ticks)));
}

constexpr TimeSpan TimeSpan::operator-() const noexcept
{
    return TimeSpan(-m_ticks);
}

constexpr TimeSpan TimeSpan::operator+() const noexcept
{
    return TimeSpan(m_ticks);
}

constexpr int TimeSpan::Compare(const TimeSpan& lhs, const TimeSpan& rhs) noexcept
{
    return lhs.CompareTo(rhs);
}

constexpr int TimeSpan::CompareTo(const TimeSpan& value) const noexcept
{
    if (m_ticks > value.m_ticks)
    {
        return 1;
    }
    else if (m_ticks < value.m_ticks)
    {
        return -1;
    }

    return 0;
}

constexpr int32_t TimeSpan::GetDays() const noexcept
{
    return static_cast<int32_t>(m_ticks / TicksPerDay);
}

constexpr int32_t TimeSpan::GetHours() const noexcept
{
    return (m_ticks / TicksPerHour) % 24;
}

constexpr int32_t TimeSpan::GetMinutes() const noexcept
{
    return (m_ticks / TicksPerMinute) % 60;
}

constexpr int32_t TimeSpan::GetSeconds() const noexcept
{
    return (m_ticks / TicksPerSecond) % 60;
}

constexpr int32_t TimeSpan::GetMilliseconds() const noexcept
{
    return static_cast<int32_t>((m_ticks / TicksPerMillisecond) % 1000);
}

constexpr int64_t TimeSpan::GetTicks() const noexcept
{
    return m_ticks;
}

constexpr double TimeSpan::GetTotalDays() const noexcept
{
    return static_cast<double>(m_ticks) * DaysPerTick;
}

constexpr double TimeSpan::GetTotalHours() const noexcept
{
    return static_cast<double>(m_ticks) * HoursPerTick;
}

constexpr double TimeSpan::GetTotalMinutes() const noexcept
{
    return static_cast<double>(m_ticks) * MinutesPerTick;
}

constexpr double TimeSpan::GetTotalSeconds() const noexcept
{
    return static_cast<double>(m_ticks) * SecondsPerTick;
}

constexpr double TimeSpan::GetTotalMilliseconds() const noexcept
{
    return static_cast<double>(m_ticks) * MillisecondsPerTick;
}

constexpr TimeSpan TimeSpan::Add(const TimeSpan& timeSpan) const noexcept
{
    return TimeSpan(m_ticks + timeSpan.m_ticks);
}

constexpr TimeSpan TimeSpan::Divide(double divisor) const noexcept
{
    return TimeSpan(static_cast<int64_t>(static_cast<double>(m_ticks) / divisor));
}

constexpr double TimeSpan::Divide(const TimeSpan& timeSpan) const noexcept
{
    return static_cast<double>(m_ticks / timeSpan.m_ticks);
}

constexpr TimeSpan TimeSpan::Multiply(double factor) const noexcept
{
    return TimeSpan(static_cast<int64_t>(static_cast<double>(m_ticks) * factor));
}

constexpr TimeSpan TimeSpan::Negate() const noexcept
{
    return TimeSpan(-m_ticks);
}

constexpr TimeSpan TimeSpan::Subtract(const TimeSpan& timeSpan) const noexcept
{
    return TimeSpan(m_ticks - timeSpan.m_ticks);
}

constexpr TimeSpan TimeSpan::Duration() const noexcept
{
    return TimeSpan(m_ticks);
}

constexpr TimeSpan TimeSpan::FromDays(double value) noexcept
{
    return TimeSpan(static_cast<int64_t>(value * static_cast<double>(TimeSpan::TicksPerDay)));
}

constexpr TimeSpan TimeSpan::FromHours(double value) noexcept
{
    return TimeSpan(static_cast<int64_t>(value * static_cast<double>(TimeSpan::TicksPerHour)));
}

constexpr TimeSpan TimeSpan::FromMinutes(double value) noexcept
{
    return TimeSpan(static_cast<int64_t>(value * static_cast<double>(TimeSpan::TicksPerMinute)));
}

constexpr TimeSpan TimeSpan::FromSeconds(double value) noexcept
{
    return TimeSpan(static_cast<int64_t>(value * static_cast<double>(TimeSpan::TicksPerSecond)));
}

constexpr TimeSpan TimeSpan::FromMilliseconds(double value) noexcept
{
    return TimeSpan(static_cast<int64_t>(value * static_cast<double>(TimeSpan::TicksPerMillisecond)));
}

constexpr TimeSpan TimeSpan::FromTicks(int64_t value) noexcept
{
    return TimeSpan(value);
}

constexpr int64_t TimeSpan::TimeToTicks(int32_t hour, int32_t minute, int32_t second) noexcept
{
    int64_t totalSeconds = (static_cast<int64_t>(hour) * 3600) + (static_cast<int64_t>(minute) * 60) * (static_cast<int64_t>(second));
    return totalSeconds * TicksPerSecond;
}

constexpr size_t TimeSpan::GetHashCode() const noexcept
{
    return static_cast<size_t>(m_ticks ^ (m_ticks >> 32));
}

} /* namespace tgon */
