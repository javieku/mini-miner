#define GLM_FORCE_RADIANS

// Game
#include "MiniMiner.h"

// Standard
#include <ctime>

int
main( int argc, char* argv[] )
{
    std::srand( (unsigned int)std::time( 0u ) );

    Game::MiniMiner game;
    game.Start( );

    return 0;
}
