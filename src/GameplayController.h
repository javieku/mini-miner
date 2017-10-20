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

    void update( GameState& gameplay );

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
    is_valid( const GameState& gameplay ) const override
    {
        return true;
    };

    bool
    is_finished( const GameState& gameplay ) const override
    {
        return m_swap_command->is_finished( gameplay )
               && m_collapse_command->is_finished( gameplay );
    };

    bool
    apply( GameState& gameplay ) override
    {
        m_swap_command->apply( gameplay );

        if ( m_swap_command->is_finished( gameplay ) )
        {
            if ( m_collapse_command->is_valid( gameplay ) )
            {
                m_collapse_command->apply( gameplay );
            }
            else
            {
                m_swap_command->undo( gameplay );
            };
        }
    }

    bool
    undo( GameState& gameplay ) override
    {
        m_swap_command->undo( gameplay );
        m_collapse_command->undo( gameplay );
    }

private:
    SwapCommandSharedPtr m_swap_command;
    RemoveGemsCommandSharedPtr m_collapse_command;
};

using UserSwapCommandListSharedPtr = std::shared_ptr< UserSwapCommandList >;
/*
template < class CommandType >
class And
{
    CommandType c1;
    CommandType c2;
};

template < class CommandType >
bool
And< CommandType >::is_valid( const Gameplay& gameplay ) const
{
    return c1->is_valid( gameplay ) && c2->is_valid( gameplay );
}

template < class CommandType >
bool
And< CommandType >::is_finished( const Gameplay& gameplay ) const
{
    return c1->is_finished( gameplay ) && c2->is_finished( gameplay );
}*/
}