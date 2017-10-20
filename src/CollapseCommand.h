#pragma once

// Game
#include "CommandInterface.h"
#include "GenerateGemsCommand.h"
#include "RemoveGemsCommand.h"

namespace Game
{
class CollapseCommand : public CommandInterface
{
public:
    CollapseCommand( )
    {
        remove_comand = std::make_shared< RemoveGemsCommand >( );
        generate_comand = std::make_shared< GenerateGemsCommand >( );
    };
    ~CollapseCommand( ) = default;

    bool
    is_valid( const GameState& state ) const override
    {
        return generate_comand->is_valid( state ) && remove_comand->is_valid( state );
    }

    bool
    is_finished( const GameState& state ) const override
    {
        return generate_comand->is_finished( state ) && remove_comand->is_finished( state );
    }

    void
    apply( GameState& state ) override
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
    undo( GameState& state ) override
    {
        generate_comand->undo( state );
        remove_comand->undo( state );
    }

private:
    CreateGemsCommandSharedPtr generate_comand;
    RemoveGemsCommandSharedPtr remove_comand;

};
using CollapseCommandSharedPtr = std::shared_ptr< CollapseCommand >;
}