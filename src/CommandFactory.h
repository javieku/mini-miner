#pragma once

// Game
#include "CommandInterface.h"
#include "Event.h"

// Standard
#include <deque>
#include <memory>

namespace Game
{
class CommandFactory
{
public:
    static std::deque< CommandInterfaceSharedPtr > create_command_list(
        const EventSharedPtr& e );
};
}