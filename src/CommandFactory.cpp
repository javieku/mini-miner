#include "CommandFactory.h"

// Game
#include "CollapseCommand.h"
#include "CommandInterface.h"
#include "EndGameCommand.h"
#include "InputHandler.h"
#include "RemoveCommand.h"
#include "SwapCommand.h"

// Standard
#include <memory>

namespace Game
{
std::deque< CommandInterfaceSharedPtr >
CommandFactory::create_command_list( const EventSharedPtr& e )
{
    std::deque< CommandInterfaceSharedPtr > actions;

    if ( std::dynamic_pointer_cast< DragEvent >( e ) != nullptr )
    {
        auto d = std::dynamic_pointer_cast< DragEvent >( e );
        actions.push_back( std::make_shared< SwapCommand >( d->start, d->end ) );
        actions.push_back( std::make_shared< RemoveCommand >( ) );
        actions.push_back( std::make_shared< CollapseCommand >( ) );
    }

    if ( std::dynamic_pointer_cast< ClickEvent >( e ) != nullptr )
    {
        auto c = std::dynamic_pointer_cast< ClickEvent >( e );
        actions.push_back( std::make_shared< SwapCommand >( c->start, c->end ) );
        actions.push_back( std::make_shared< RemoveCommand >( ) );
        actions.push_back( std::make_shared< CollapseCommand >( ) );
    }

    if ( std::dynamic_pointer_cast< GameOverEvent >( e ) != nullptr )
    {
        actions.push_back( std::make_shared< EndGameCommand >( ) );
    }

    return actions;
}
}