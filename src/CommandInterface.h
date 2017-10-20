#pragma once

#include <memory>

namespace Game
{
class GameState;

class CommandInterface
{
public:
    CommandInterface( ) = default;
    virtual ~CommandInterface( ) = default;

    virtual bool is_valid( const GameState& gameplay ) const = 0;

    virtual bool is_finished( const GameState& gameplay ) const = 0;

    virtual bool apply( GameState& gameplay ) = 0;

    virtual bool undo( GameState& gameplay ) = 0;
};

using CommandInterfaceSharedPtr = std::shared_ptr< CommandInterface >;
}