#pragma once

#include "CommandInterface.h"
#include "MoveCommand.h"

namespace Game
{
class GenerateGemsCommand : public CommandInterface
{
public:
    GenerateGemsCommand( ) = default;
    ~GenerateGemsCommand( ) = default;

    bool is_valid( const GameState& gameplay ) const override;
    bool is_finished( const GameState& gameplay ) const override;
    bool apply( GameState& gameplay ) override;
    bool undo( GameState& gameplay ) override;

private:
    bool has_broken_cell( const Colum& colum );

private:
    std::vector< MoveCommandSharedPtr > m_falling_gems;
    bool first_time = true;
};

using CreateGemsCommandSharedPtr = std::shared_ptr< GenerateGemsCommand >;
}