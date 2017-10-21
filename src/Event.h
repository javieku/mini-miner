#pragma once

// Game
#include "Coordinates.h"

// Standard
#include <memory>

namespace Game
{
// TODO Move to engine logic
struct Event
{
    Event( ) = default;
    virtual ~Event( ){};
};

using EventSharedPtr = std::shared_ptr< Event >;

struct DragEvent : public Event
{
    Coordinates start;
    Coordinates end;

    DragEvent( const Coordinates& s, const Coordinates& e )
        : start( s )
        , end( e )
    {
    }
};

using DragEventSharedPtr = std::shared_ptr< DragEvent >;

struct ClickEvent : public Event
{
    Coordinates coordinates;

    ClickEvent( const Coordinates& c )
        : coordinates( c )
    {
    }
};

using ClickEventSharedPtr = std::shared_ptr< ClickEvent >;
}