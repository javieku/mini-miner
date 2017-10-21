#include "CollapseCommand.h"

namespace Game
{
CollapseCommand::CollapseCommand( )
{
    remove_comand = std::make_shared< RemoveGemsCommand >( );
    generate_comand = std::make_shared< GenerateGemsCommand >( );
};

bool
CollapseCommand::is_valid( const GameState& state ) const
{
    return generate_comand->is_valid( state ) || remove_comand->is_valid( state );
}

bool
CollapseCommand::is_finished( const GameState& state ) const
{
    return generate_comand->is_finished( state ) && remove_comand->is_finished( state );
}

void
CollapseCommand::apply( GameState& state )
{
    if ( generate_comand->is_finished( state ) )
    {
        generate_comand = std::make_shared< GenerateGemsCommand >( );
        remove_comand->apply( state );
    }
    else
    {
        remove_comand = std::make_shared< RemoveGemsCommand >( );
        generate_comand->apply( state );
    }
}
void
CollapseCommand::undo( GameState& state )
{
    generate_comand->undo( state );
    remove_comand->undo( state );
}
}