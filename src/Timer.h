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
    {
        // TODO Inject from Gameplay
        this->x = 75u;
        this->y = 175u;
    }
    ~Timer( ){};

    void
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

    long long
    countdown( ) const
    {
        return duration - elapsed( );
    }

public:
    // TODO Inject from Gameplay
    std::string text = "Time: ";
    int duration = 60;

private:
    typedef std::chrono::high_resolution_clock Clock;
    std::chrono::time_point< std::chrono::steady_clock > t1 = Clock::now( );
};
}