#include "CommandFactory.h"

// Game
#include "CollapseCommand.h"
#include "CommandInterface.h"
#include "InputHandler.h"
#include "RemoveGemsCommand.h"
#include "SwapCommand.h"

// Standard
#include <memory>

namespace Game
{
std::deque< CommandInterfaceSharedPtr >
CommandFactory::create_command_list( const EventSharedPtr& e )
{
    std::deque< CommandInterfaceSharedPtr > actions;
    DragEventSharedPtr d = std::dynamic_pointer_cast< DragEvent >( e );
    if ( d != nullptr )
    {
        actions.push_back( std::make_shared< SwapCommand >( d->start, d->end ) );
        actions.push_back( std::make_shared< RemoveGemsCommand >( ) );
        actions.push_back( std::make_shared< CollapseCommand >( ) );
    }
    return actions;
}
}