#pragma once

// Game
#include "Text.h"

// Standard
#include <chrono>
#include <string>

namespace Game
{
/**
 * Simple model to show the game duration.
 **/
class Timer : public Text
{
public:
    Timer( const Coordinates& c, const std::string& t, int32_t d );
    ~Timer( ) = default;

    void start( );
    void stop( );

    long long elapsed_seconds( ) const;
    long long elapsed_milliseconds( ) const;
    long long countdown( ) const;

public:
    int32_t duration;

private:
    typedef std::chrono::high_resolution_clock Clock;
    std::chrono::time_point< std::chrono::steady_clock > t1 = Clock::now( );
};
}