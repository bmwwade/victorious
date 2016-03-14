#include "player.h"
#include <cmath>
#include <climits>
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
    stdBoard = new Board();

    alpha = INT_MIN;
    beta = INT_MAX;
}

/*
 * Destructor for the player.
 */
Player::~Player() {
    delete stdBoard;
}

void Player::setBoard(Board *newBoard) {
    stdBoard = newBoard->copy();
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
    stdBoard->doMove(opponentsMove, otherSide);
    if (!stdBoard->hasMoves(mySide))
    {
        return NULL;
    }

    int scoreboard[8][8];
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Move testMove(i, j);
            if (stdBoard->checkMove(&testMove, mySide))
            {
                Board *testBoard = stdBoard->copy();
                testBoard->doMove(&testMove, mySide);

                int base = calcBase(testBoard, mySide);
                if (testingMinimax)
                {
                    if (!testBoard->hasMoves(otherSide))
                        scoreboard[i][j] = base;   
                    else
                        scoreboard[i][j] = miniMax(testBoard, mySide, otherSide);
                }
                else
                    scoreboard[i][j] = deepMiniMax(testBoard, true, 4);
            }
            else
            {
                scoreboard[i][j] = -10000;
            }
        }
    }
    Move *nextMove = getBestMove(scoreboard);
    stdBoard->doMove(nextMove, mySide);
    return nextMove;

}

int Player::deepMiniMax(Board *board, bool isMax, int depth)
{
    Side currSide;
    Side nextSide;
    if (isMax)
    {
        currSide = mySide;
        nextSide = otherSide;
    }
    else
    {
        currSide = otherSide;
        nextSide = mySide;
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (alpha >= beta)
            {
                if (isMax)
                    return alpha;
                else
                    return beta;
            }
            Move test(i, j);
            if (board->checkMove(&test, nextSide))
            {
                Board *newBoard = board->copy();
                newBoard->doMove(&test, nextSide);
                int score;
                if (depth == 0)
                {
                    score = calcBase(newBoard, currSide);
                    score = improveHeuristic(score, i, j);
                }
                else
                    score = deepMiniMax(newBoard, !isMax, depth - 1);
                if (isMax && score > alpha)
                    alpha = score;
                else if (!isMax && score < beta)
                    beta = score;
            }
        }
    }
    if (isMax)
    {
        return alpha;
    }
    else
        return beta;

}

Move *getBestMove(int scoreboard[][8])
{
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
    Move *bestMove = new Move(maxi, maxj);
    return bestMove;
}

int calcBase(Board *board, Side side)
{
    int black, white, base;
    black = board->countBlack();
    white = board->countWhite();
    if (side == BLACK)
    {
        base = black - white;
    }
    else
    {
        base = white - black;
    }

    return base;
}

int improveHeuristic(int base, int i, int j)
{
    int score = 0;
    if (i == 0 || i == 7)
    {
        if (j == 0 || j == 7)
        {
            score = base + 6;
        }
        else if (j == 1 || j == 6)
        {
            score = base - 5;
        }
        else
        {
            score = base + 3;
        }
    }
    else if (i == 1 || i == 6)
    {
        if (j == 0 || j == 7)
        {
            score = base - 5;
        }
        else if (j == 1 || j == 6)
        {
            score = base - 6;
        }
        else
        {
            score = base - 2;
        }
    }
    else if (j == 0 || j == 7)
    {
        score = base + 3;
    }
    else if (j == 1 || j == 6)
    {
        score = base - 2;
    }
    else
    {
        score = base;
    }
    return score;
}

int miniMax(Board *board, Side mySide, Side otherSide)
{

    int minScore = 1000;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Move test(i, j);
            if (board->checkMove(&test, otherSide))
            {
                Board *newBoard = board->copy();
                newBoard->doMove(&test, otherSide);
                
                int score = calcBase(newBoard, mySide);
                if (score < minScore)
                {
                    minScore = score;
                }
            }
        }
    }

    return minScore;
}

