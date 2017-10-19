#pragma once

#include "CommandInterface.h"
#include "Gameplay.h"

namespace Game
{
class SwapCommand : public CommandInterface
{
public:
    SwapCommand( const Coordinates& one, const Coordinates& other );
    ~SwapCommand( );

    bool is_valid( Gameplay& gameplay ) const override;

    bool is_finished( Gameplay& gameplay ) const override;

    bool apply( Gameplay& gameplay ) override;

    bool undo( Gameplay& gameplay )  override;

private:
    Coordinates m_one_coordinate;
    Coordinates m_other_coordinate;

	Cell m_previous_cell_one;
	Cell m_previous_cell_other;

	CellPosition m_one_position;
	CellPosition m_another_position;

	bool first_time;
};
}