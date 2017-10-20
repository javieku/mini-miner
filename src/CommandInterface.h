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

    virtual bool is_valid( const GameState& state ) const = 0;

    virtual bool is_finished( const GameState& state ) const = 0;

    virtual void apply( GameState& state ) = 0;

    virtual void undo( GameState& state ) = 0;
};

using CommandInterfaceSharedPtr = std::shared_ptr< CommandInterface >;
}