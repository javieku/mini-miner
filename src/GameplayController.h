#pragma once

#include "GameState.h"
#include "InputHandler.h"

#include "CommandInterface.h"
#include "GenerateGemsCommand.h"
#include "RemoveGemsCommand.h"
#include "SwapCommand.h"

#include <deque>

namespace Game
{
class GameplayController
{
public:
    GameplayController( InputHandler& input_handler );
    ~GameplayController( );

    void update( GameState& state );

private:
    InputHandler& m_input_handler;

    Game::CommandInterfaceSharedPtr m_action;

    Game::CommandInterfaceSharedPtr m_current_action;
    Game::CommandInterfaceSharedPtr m_last_action;
    std::deque< Game::CommandInterfaceSharedPtr > m_actions;
};

class UserSwapCommandList : public CommandInterface
{
public:
    UserSwapCommandList( ){};
    ~UserSwapCommandList( ){};

    bool
    is_valid( const GameState& state ) const override
    {
        return true;
    };

    bool
    is_finished( const GameState& state ) const override
    {
        return m_swap_command->is_finished( state ) && m_collapse_command->is_finished( state );
    };

    void
    apply( GameState& state ) override
    {
        m_swap_command->apply( state );

        if ( m_swap_command->is_finished( state ) )
        {
            if ( m_collapse_command->is_valid( state ) )
            {
                m_collapse_command->apply( state );
            }
            else
            {
                m_swap_command->undo( state );
            }
        }
    }

    void
    undo( GameState& state ) override
    {
        m_swap_command->undo( state );
        m_collapse_command->undo( state );
    }

private:
    SwapCommandSharedPtr m_swap_command;
    RemoveGemsCommandSharedPtr m_collapse_command;
};

using UserSwapCommandListSharedPtr = std::shared_ptr< UserSwapCommandList >;
}