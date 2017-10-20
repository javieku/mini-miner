#pragma once

#include "CommandInterface.h"
#include "GameState.h"

namespace Game
{
class MoveCommand;

class SwapCommand : public CommandInterface
{
public:
    SwapCommand( const Coordinates& one, const Coordinates& other );
    ~SwapCommand( );

    bool is_valid( const GameState& state ) const override;

    bool is_finished( const GameState& state ) const override;

    void apply( GameState& state ) override;

    void undo( GameState& state ) override;

private:
    void move( GameState& state,
               const GemPosition& one_position,
               const GemPosition& another_position );

private:
    Coordinates m_one_coordinate;
    Coordinates m_other_coordinate;

    Gem m_previous_one_gem;
    Gem m_previous_other_gem;

    GemPosition m_one_position;
    GemPosition m_another_position;

    bool first_time;

    std::unique_ptr< MoveCommand > move1;
    std::unique_ptr< MoveCommand > move2;
};
using SwapCommandSharedPtr = std::shared_ptr< SwapCommand >;
}