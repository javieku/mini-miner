#pragma once

#include "CommandInterface.h"

namespace Game
{
class BreakGemsCommand : public CommandInterface
{
public:
    BreakGemsCommand( );
    ~BreakGemsCommand( ) = default;

    bool is_valid( Gameplay& gameplay ) const override;
    bool is_finished( Gameplay& gameplay ) const override;
    bool apply( Gameplay& gameplay ) override;
    bool undo( Gameplay& gameplay ) override;

private:
    bool m_done;
};

using BreakGemsCommandSharedPtr = std::shared_ptr< BreakGemsCommand >;
}
