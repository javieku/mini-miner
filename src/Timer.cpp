#include "Timer.h"

// Game
#include "Utils.h"

namespace Game
{
Timer::Timer( const Coordinates& c, const std::string& t, int32_t d )
    : Text( c, t )
    , duration( d )
{
    this->visible = true;
}

void
Timer::start( )
{
    t1 = Clock::now( );
}

void
Timer::stop( )
{
    t1 = Clock::now( );
}

long long
Timer::elapsed_seconds( ) const
{
    auto t2 = Clock::now( );
    return std::chrono::duration_cast< std::chrono::seconds >( t2 - t1 ).count( );
}

long long
Timer::elapsed_milliseconds( ) const
{
    auto t2 = Clock::now( );
    return std::chrono::duration_cast< std::chrono::milliseconds >( t2 - t1 ).count( );
}

long long
Timer::countdown( ) const
{
    return duration - elapsed_seconds( );
}
}