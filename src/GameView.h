#pragma once

namespace King
{
class Engine;
}

namespace Game
{
class Board;
class GameState;
class Score;
class Text;
class Timer;
/**
 * Renders all the components by using King::Engine.
 * Just access the model components with almost no logic.
 **/
class GameView
{
public:
    GameView( ) = delete;
    explicit GameView( King::Engine& engine );
    ~GameView( );

    void render( const GameState& model );

private:
    void render( const Board& board );
    void render( const Timer& timer );
    void render( const Text& text );
    void render( const Score& score );

private:
    King::Engine& m_engine;
};
}