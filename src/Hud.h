#pragma once

#include <chrono>
#include <string>

namespace Game
{
class Score
{
public:
    Score( );
    ~Score( );

public:
    float x = 75u;
    float y = 225u;
    std::string text = "Score: ";
    int score;
};

class Timer
{
public:
    Timer( ){};
    ~Timer( ){};

public:
    float x = 75u;
    float y = 175u;
    std::string text = "Time: ";
    typedef std::chrono::high_resolution_clock Clock;
    std::chrono::time_point< std::chrono::steady_clock > t1 = Clock::now( );

    int
    start( )
    {
        t1 = Clock::now( );
    }

    long long
    elapsed( ) const
    {
        auto t2 = Clock::now( );
        return std::chrono::duration_cast< std::chrono::seconds >( t2 - t1 ).count( );
    }
};
}