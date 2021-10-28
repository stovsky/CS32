// Game.cpp

#include "provided.h"
#include <iostream>
using namespace std;

class GameImpl
{
  public:
    GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black);
    bool completed(int& winner) const;
    bool takeTurn();
    void play();
    int checkerAt(int c, int r) const;
    
    int checkHorizontalWinner() const;
    int checkVerticalWinner() const;
    int checkDiagonalWinner() const;
    

private:
    Scaffold m_game;
    int m_N;
    bool m_redTurn;
    Player* m_red;
    Player* m_black;
};


GameImpl::GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black) : m_game(nColumns, nLevels)
{
    m_N = N;
    m_red = red;
    m_black = black;
    m_redTurn = true;
    
}

int GameImpl::checkDiagonalWinner() const {
    int red_counter = 0;
    int black_counter = 0;
    
    // Check for a winner going SE
    for (int c = 1; c <= m_game.cols() - m_N + 1; c++) {
        for (int l = m_N - 1; l <= m_game.levels(); l++) {
            for (int i = 0; i < m_N && (c + i <= m_game.cols()) && (l - i > 0); i++) {
                if (m_game.checkerAt(c + i, l - i) == RED) {
                    red_counter++;
                }
                if (red_counter >= m_N) {
                    return RED;
                }
                
                if (m_game.checkerAt(c + i, l - i) == BLACK) {
                    black_counter++;
                }
                if (black_counter >= m_N) {
                    return BLACK;
                }
            }
            red_counter = 0;
            black_counter = 0;
            }
        }
    
    // Check for a winner going NE
    for (int c = 1; c <= m_game.cols() - m_N + 1; c++) {
        for (int l = 1; l <= m_game.levels() - m_N + 1; l++) {
            for (int i = 0; i < m_N && (c + i <= m_game.cols()) && (l + i <= m_game.levels()); i++) {
                if (m_game.checkerAt(c + i, l + i) == RED) {
                    red_counter++;
                }
                if (red_counter >= m_N) {
                    return RED;
                }
                
                if (m_game.checkerAt(c + i, l + i) == BLACK) {
                    black_counter++;
                }
                if (black_counter >= m_N) {
                    return BLACK;
                }
            }
            red_counter = 0;
            black_counter = 0;
            }
        }
    
    
    return -10;
}

int GameImpl::checkHorizontalWinner() const {
    
    int red_counter = 0;
    int black_counter = 0;

    // Check for a winner horizontally
    for (int c = 1; c <= m_game.cols() - m_N + 1; c++) {
        for (int l = 1; l <= m_game.levels(); l++) {
            for (int i = 0; i < m_N && (c + i <= m_game.cols()); i++) {
                if (m_game.checkerAt(c + i, l) == RED) {
                    red_counter++;
                }
                if (red_counter >= m_N) {
                    return RED;
                }
                
                if (m_game.checkerAt(c + i, l) == BLACK) {
                    black_counter++;
                }
                if (black_counter >= m_N) {
                    return BLACK;
                }
            }
            red_counter = 0;
            black_counter = 0;
        }
    }
    return -10;
}

int GameImpl::checkVerticalWinner() const {
    
    int red_counter = 0;
    int black_counter = 0;

    // Check for a winner vertically
    for (int c = 1; c <= m_game.cols(); c++) {
        for (int l = 1; l <= m_game.levels() - m_N + 1; l++) {
            for (int i = 0; i < m_N && (l + i <= m_game.levels()); i++) {
                if (m_game.checkerAt(c, l + i) == RED) {
                    red_counter++;
                }
                if (red_counter >= m_N) {
                    return RED;
                }
                
                if (m_game.checkerAt(c, l + i) == BLACK) {
                    black_counter++;
                }
                if (black_counter >= m_N) {
                    return BLACK;
                }
            }
            red_counter = 0;
            black_counter = 0;
        }
    }

    return -10;
}

bool GameImpl::completed(int& winner) const
{
    // Check if there is a winner in every direction
    if (checkHorizontalWinner() != -10) {winner = checkHorizontalWinner(); return true;}
    if (checkVerticalWinner() != -10) {winner = checkVerticalWinner(); return true;}
    if (checkDiagonalWinner() != -10) {winner = checkDiagonalWinner(); return true;}
    
    // If there are no empty spaces and a winner hasn't been found, it's a tie game
    if (m_game.numberEmpty() == 0) {
        winner = TIE_GAME;
        return true;
    }
    
    // Otherwise, the game isn't over
    return false;
}

bool GameImpl::takeTurn()
{
    
    // Before every turn, check if there's a winner
    int winner;
    if(completed(winner)) return false;
    
    // Make red's move and switch the turn to black
    if (m_redTurn) {
        m_game.makeMove(m_red->chooseMove(m_game, m_N, RED), RED);
        m_redTurn = false;
    }
    // Make black's move and switch the turn to red
    else {
        m_game.makeMove(m_black->chooseMove(m_game, m_N, BLACK), BLACK);
        m_redTurn = true;
    }
    
    // Return true if the game isn't over
    return true;
}

void GameImpl::play()
{
    // Display empty board
    m_game.display();
    int winner;
    
    // Take turns until the game ends
    while (!completed(winner)) {
        takeTurn();
        m_game.display();
        
        // If two computers are playing, press enter to advance to the next move
        if (!m_red->isInteractive() && !m_black->isInteractive()) {
            cout << "Press enter to continue." << endl;
            cin.ignore();
        }
    }
    
    if (winner == RED) cout << "The winner is red!" << endl;
    else if (winner == BLACK) cout << "The winner is black!" << endl;
    else cout << "The game ended in a tie." << endl;
}

int GameImpl::checkerAt(int c, int r) const
{
    return m_game.checkerAt(c, r);
}

//******************** Game functions *******************************

//  These functions simply delegate to GameImpl's functions.
//  You probably don't want to change any of this code.

Game::Game(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    m_impl = new GameImpl(nColumns, nLevels, N, red, black);
}
 
Game::~Game()
{
    delete m_impl;
}

bool Game::completed(int& winner) const
{
    return m_impl->completed(winner);
}

bool Game::takeTurn()
{
    return m_impl->takeTurn();
}

void Game::play()
{
    m_impl->play();
}
 
int Game::checkerAt(int c, int r) const
{
    return m_impl->checkerAt(c, r);
}
