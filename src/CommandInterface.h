#pragma once

#include <memory>

namespace Game
{
class Gameplay;

class CommandInterface
{
public:
    CommandInterface( ) = default;
    virtual ~CommandInterface( ) = default;

    virtual bool is_valid( const Gameplay& gameplay ) const = 0;

    virtual bool is_finished( const Gameplay& gameplay ) const = 0;

    virtual bool apply( Gameplay& gameplay ) = 0;

    virtual bool undo( Gameplay& gameplay ) = 0;
};

using CommandInterfaceSharedPtr = std::shared_ptr< CommandInterface >;
}