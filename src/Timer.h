#pragma once

// Game
#include "Entity.h"

// Standard
#include <chrono>
#include <string>

namespace Game
{
class Timer : public Entity
{
public:
    Timer( )
        : Entity( {75u, 175u} )
    {
        // TODO Initialize it in Gamestate using constructor
        text = "Time: ";
        duration = 60u;
    }
    ~Timer( ){};

    void
    start( )
    {
        t1 = Clock::now( );
    }

    void
    stop( )
    {
        t1 = Clock::now( );
    }

    long long
    elapsed_seconds( ) const
    {
        auto t2 = Clock::now( );
        return std::chrono::duration_cast< std::chrono::seconds >( t2 - t1 ).count( );
    }

    long long
    elapsed_milliseconds( ) const
    {
        auto t2 = Clock::now( );
        return std::chrono::duration_cast< std::chrono::milliseconds >( t2 - t1 ).count( );
    }

    long long
    countdown( ) const
    {
        return duration - elapsed_seconds( );
    }

public:
    std::string text;
    int duration;

private:
    typedef std::chrono::high_resolution_clock Clock;
    std::chrono::time_point< std::chrono::steady_clock > t1 = Clock::now( );
};
}