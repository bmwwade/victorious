#include "player.h"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    mySide = side;
    if (mySide == BLACK)
    {
        otherSide = WHITE;
    }
    else
    {
        otherSide = BLACK;
    }
    stdBoard = Board();
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    stdBoard.doMove(opponentsMove, otherSide);
    if (!stdBoard.hasMoves(mySide))
    {
        return NULL;
    }

    int scoreboard[9][9];
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Move *testMove = new Move(i, j);
            if (stdBoard.checkMove(testMove, mySide))
            {
                Board *testBoard = stdBoard.copy();
                int black, white;
                testBoard->doMove(testMove, mySide);
                black = testBoard->countBlack();
                white = testBoard->countWhite();
                if (mySide == BLACK)
                {
                    scoreboard[i][j] = black - white;
                }
                else
                {
                    scoreboard[i][j] = white - black;
                }

            }
            else
            {
                scoreboard[i][j] = -10000;
            }
            delete testMove;
        }
    }
    int maxi = 0, maxj = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (scoreboard[i][j] > scoreboard[maxi][maxj])
            {
                maxi = i;
                maxj = j;
            }
        }
    }
    Move *nextMove = new Move(maxi, maxj);
    stdBoard.doMove(nextMove, mySide);
    return nextMove;

}
