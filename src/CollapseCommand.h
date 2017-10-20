#pragma once

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
    is_valid( const GameState& gameplay ) const override
    {
        return generate_comand->is_valid( gameplay ) && remove_comand->is_valid( gameplay );
    }

    bool
    is_finished( const GameState& gameplay ) const override
    {
        return generate_comand->is_finished( gameplay ) && remove_comand->is_finished( gameplay );
    }

    bool
    apply( GameState& gameplay ) override
    {
        if ( generate_comand->is_finished( gameplay ) )
        {
            generate_comand = std::make_shared< GenerateGemsCommand >( );
            remove_comand->apply( gameplay );
        }
        else
        {
            remove_comand = std::make_shared< RemoveGemsCommand >( );
            generate_comand->apply( gameplay );
        }
        return true;
    }
    bool
    undo( GameState& gameplay ) override
    {
        generate_comand->undo( gameplay );
        remove_comand->undo( gameplay );
        return true;
    }

private:
    CreateGemsCommandSharedPtr generate_comand;
    RemoveGemsCommandSharedPtr remove_comand;

    bool first_time = true;
};
using CollapseCommandSharedPtr = std::shared_ptr< CollapseCommand >;
}