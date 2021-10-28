// Player.cpp

#include "provided.h"
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <climits>
using namespace std;

class HumanPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class BadPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class SmartPlayerImpl
{
  public:
    Scaffold copyScaffold(const Scaffold& s);
    bool checkWin(const Scaffold& s, int player, int m_N);
    int eval(int g, int b, int e, int m_N);
    int setScore(vector<int> v, int player, int m_N);
    int score(const Scaffold & s, int player, int m_N);
    vector<int> minMax(const Scaffold& s, int depth, int alpha, int beta, int player, int m_N, AlarmClock& ac);
    int chooseMove(const Scaffold& s, int N, int color);
    void setColors(int color);
private:
    int COMPUTER;
    int HUMAN;
};

int HumanPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    
    // If no spots are available to move to, do nothing
    if (s.numberEmpty() == 0) {
        return 0;
    }
    

    int l = s.levels();
    int input = -10;
    
    while (input <= 0 || input > s.cols()) {
        l = s.levels();
        cout << "Choose a column: ";
        cin >> input;
        
        // If the input is within the columns, check if there is a vacant spot
        if (input > 0 && input <= s.cols()) {
            while (l > 0) {
                // If a vacant spot is available, return the input
                if (s.checkerAt(input, l) == VACANT) return input;
                else l--;
            }
            // If the column is full, set input to an arbitrary negative number to go through the loop again
            if (l == 0) input = -10;
        }

    }
    
    return input;
}


int BadPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    // If no spots are available to move to, do nothing
    if (s.numberEmpty() == 0) return 0;
    
    // Find the first empty spot from left to right
    for (int c = 1; c <= s.cols(); c++) {
        // Return the first empty column
        if (s.checkerAt(c, s.levels()) == VACANT) return c;
    }
    return 0;
}

Scaffold SmartPlayerImpl::copyScaffold(const Scaffold& s) {
    
    // Create a new empty scaffold
    Scaffold newScaffold(s.cols(), s.levels());
    
    // Make the same moves in the new scaffold as on the current scaffold
    for (int c = 1; c <= s.cols(); c++) {
        for (int l = 1; l <= s.levels(); l++) {
            newScaffold.makeMove(c, s.checkerAt(c, l));
        }
    }
    return newScaffold;
}

bool SmartPlayerImpl::checkWin(const Scaffold& s, int player, int m_N) {
    
    // This implementation is very similar to the completed function in the game class, but it checks if a specific player has won
    
    int counter = 0;
    
    // Check for a winner horizontally
    for (int c = 1; c <= s.cols() - m_N + 1; c++) {
        for (int l = 1; l <= s.levels(); l++) {
            for (int i = 0; i < m_N && (c + i <= s.cols()); i++) {
                if (s.checkerAt(c + i, l) == player) {
                    counter++;
                }
                if (counter >= m_N) {
                    return true;
                }
            }
            counter = 0;
        }
    }
    
    // Check for a winner vertically
    for (int c = 1; c <= s.cols(); c++) {
        for (int l = 1; l <= s.levels() - m_N + 1; l++) {
            for (int i = 0; i < m_N && (l + i <= s.levels()); i++) {
                if (s.checkerAt(c, l + i) == player) {
                    counter++;
                }
                if (counter >= m_N) {
                    return true;
                }

            }
            counter = 0;
        }
    }
    
    // Check for a winner south-east
    for (int c = 1; c <= s.cols() - m_N + 1; c++) {
        for (int l = m_N - 1; l <= s.levels(); l++) {
            for (int i = 0; i < m_N && (c + i <= s.cols()) && (l - i > 0); i++) {
                if (s.checkerAt(c + i, l - i) == player) {
                    counter++;
                }
                if (counter >= m_N) {
                    return true;
                }

            }
            counter = 0;
            }
        }
    
    // Check for a winner north-east
    for (int c = 1; c <= s.cols() - m_N + 1; c++) {
        for (int l = 1; l <= s.levels() - m_N + 1; l++) {
            for (int i = 0; i < m_N && (c + i <= s.cols()) && (l + i <= s.levels()); i++) {
                if (s.checkerAt(c + i, l + i) == player) {
                    counter++;
                }
                if (counter >= m_N) {
                    return true;
                }
                
            }
            counter = 0;
            }
        }
    
    // If no winner, return false
    return false;
}



vector<int> SmartPlayerImpl::minMax(const Scaffold& s, int depth, int alpha, int beta, int player, int m_N, AlarmClock& ac) {
    
    // If there are no vacant spots, do nothing
    if (s.numberEmpty() == 0) return vector<int>{score(s, COMPUTER, m_N), 0};
    
    // Start off with the first open column from left to right
    int col = 0;
    for (int c = 1; c <= s.cols(); c++) {
        if (s.checkerAt(c, s.levels()) == VACANT) {col = c; break;}
    }
    
    // When the depth reaches 0, return the current score and the first open column (in case for some reason we can't find a better column)
    if (depth == 0) {
        return vector<int>{score(s, COMPUTER, m_N), col};
    }
    
    // If it's the computers turn
    if (player == COMPUTER) {
        
        // Start off with the lowest possible score since we want to maximize it
        vector<int> moves = {INT_MIN, col};
        
        // If the other player is going to win
        if (checkWin(s, HUMAN, m_N)) {
            // Return the worst score possible so we can avoid the move
            return moves;
        }
        if (ac.timedOut()) return moves;
        
        // Try each possible move
        for (int c = 1; c <= s.cols(); c++) {
            
            // We don't have to try a column that is full
            if (s.checkerAt(c, s.levels()) == VACANT) {
                
                // Create a copy of the board and try the move
                Scaffold temp = copyScaffold(s);
                temp.makeMove(c, player);
                if (ac.timedOut()) return moves;
                
                // Find the move based on the state of the new board
                int score = minMax(temp, depth - 1, alpha, beta, HUMAN, m_N, ac)[0];
                
                // If we find a better score, then replace it and set this move to be the new best move
                if (score > moves[0]) {
                    moves[0] = score;
                    moves[1] = c;
                }
                
                // Alpha-beta pruning, I am trying to get rid of moves that can't possibly be correct
                alpha = std::max(alpha, moves[0]);
                if (alpha >= beta) {
                    break;
                }
            }
        }
        
        // Return the best move
        return moves;
    }
    
    // If it's the other player's turn
    else {
        
        // Start off with the best possible score since we want to minimize it
        vector<int> moves = {INT_MAX, col};
        
        // If the computer is going to win
        if (checkWin(s, COMPUTER, m_N)) {
            // Return this as the best move
            return moves;
        }
        if (ac.timedOut()) return moves;
        for (int c = 1; c <= s.cols(); c++) {
            if (s.checkerAt(c, s.levels()) == VACANT) {
                Scaffold temp = copyScaffold(s);
                temp.makeMove(c, player);
                if (ac.timedOut()) return moves;
                int score = minMax(temp, depth - 1, alpha, beta, COMPUTER, m_N, ac)[0];
                
                // We are trying to find moves that make the score worse so we don't choose them
                if (score < moves[0]) {
                    moves[0] = score;
                    moves[1] = c;
                }
                beta = std::min(beta, moves[0]);
                if (alpha >= beta) {
                    break;
                }
            }
        }
        return moves;
    }
}

void SmartPlayerImpl::setColors(int color) {
    
    // Decide which color the computer is and which the other player is
    COMPUTER = color;
    if (COMPUTER == RED) {
        HUMAN = BLACK;
    }
    else {
        HUMAN = RED;
    }
}

int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    // Use minmax algorithm to determine the best move
    AlarmClock ac(9900);
    setColors(color);
    return minMax(s, 8, 0 - INT_MAX, INT_MAX, COMPUTER, N, ac)[1];

}
                
                
int SmartPlayerImpl::eval(int good, int bad, int empty, int m_N) {
    
    int score = 0;
    
    // If we need 2 in a row to win
    if (m_N == 2) {
        // Highest score when we can make 2 in a row and win
        if (good == m_N) {
            score += (5 * std::pow(10, m_N + 1) + 50); // +5050 /// the + 50 means it will prefer to win over blocking a win
        }
        // Second highest score when we can get 1 in a row and 1 empty
        else if (good == 1 && empty == 1) {
            score += (5 * std::pow(10, m_N)); // +500
        }
        
        // 2 enemy checkers in a row
        if (bad == m_N) {
            score -= (5 * std::pow(10, m_N + 1)); // -5000
        }
        // 1 enemy checker and 1 empty
        else if (bad == 1 && empty == 1) {
            score -= (5 * std::pow(10, m_N) + 50); // -550 /// the + 50 means if we can't win we want to block
        }
    }
    
    // If we need 3 in a row to win
    else if (m_N == 3) {
        if (good == m_N) {
            score += (5 * std::pow(10, m_N + 1) + 50); // +50050
        }
        else if (good == 2 && empty == 1) {
            score += (5 * std::pow(10, m_N)); // +5000
        }
        else if (good == 1 && empty == 2){
            score += (5 * std::pow(10, m_N - 1)); // +500
        }
        
        if (bad == m_N) {
            score -= (5 * std::pow(10, m_N + 1)); // -500000
        }
        else if (bad == 2 && empty == 1) {
            score -= (5 * std::pow(10, m_N) + 50); // -5050
        }
        else if (bad == 1 && empty == 2){
            score -= (5 * std::pow(10, m_N - 1) + 50); // -550
        }
    }
    
    else if (m_N >= 4) {
        for (int i = 0; i < m_N - 1; i++) {
            if (good == m_N - i && empty == i) {
                if (good == m_N) {
                    if ((5 * std::pow(10, m_N + 1)) > INT_MAX) {
                       score += INT_MAX;
                    }
                    else {
                        score += (5 * std::pow(10, m_N + 1) + 50); // +5*10^(m_N + 1) + 50
                    }
                }
                else if (good == m_N - 1 && empty == 1) {
                    if ((5 * std::pow(10, m_N)) > INT_MAX) {
                        score += INT_MAX;
                    }
                    else {
                        score += (5 * std::pow(10, m_N)); // +5*10^(m_N)
                    }
                }
                else {
                    if ((5 * std::pow(10, m_N - i)) > INT_MAX) {
                        score += INT_MAX;
                    }
                    else {
                        score += (5 * std::pow(10, m_N - i)); // +5*10^(m_N - i)
                    }
                }
            
            }
            if (bad == m_N - i && empty == i) {
                if (bad == m_N) {
                    if ((5 * std::pow(10, m_N + 1)) > INT_MAX) {
                        score -= INT_MAX;
                    }

                    else {
                        score -= (5 * std::pow(10, m_N + 1)); // -5*10^(m_N + 1)
                    }
                }
                else if (bad == m_N - 1 && empty == 1) {
                    if ((5 * std::pow(10, m_N)) > INT_MAX) {
                        score -= INT_MAX;
                    }
                    else {
                        score -= (5 * std::pow(10, m_N) + 50); // -(5*10^(m_N) + 50)
                    }
                }
                else {
                    if ((5 * std::pow(10, m_N - i)) > INT_MAX) {
                        score -= INT_MAX;
                    }
                    else {
                        score -= (5 * std::pow(10, m_N - i) + 50); // -(5*10^(m_N - i) + 50)
                    }
                }
            }
        }
    }
    
    
    return score;

    
}
                
                
int SmartPlayerImpl::setScore(vector<int> checkers, int player, int m_N) {
    int g = 0;
    int b = 0;
    int e = 0;
    
    // Loop through the set of checkers
    for (int i = 0; i < checkers.size(); i++) {
        
        // If we see the player's checker, increase the good checkers by 1
        if (checkers[i] == player) g += 1;
        else g += 0;
        
        // If we see either player's checker, increase the bad checkers by 1
        if (checkers[i] == HUMAN || checkers[i] == COMPUTER) b += 1;
        else b += 0;
        
        // If we see a vacant space, increase empty by 1
        if (checkers[i] == VACANT) e += 1;
        else e += 0;
        
    }
    
    // Since we know bad is bad + good, we need to subtract the good to get just the bad
    b -= g;
    
    // Evaluate the score of the set
    return eval(g, b, e, m_N);
}

int SmartPlayerImpl::score(const Scaffold &s, int player, int m_N) {
    int score = 0;
    vector<int> level_score(s.levels() + 1);
    vector<int> col_score(s.cols() + 1);
    vector<int> checkers(m_N);
    
    // In this function, we are finding every single possible set of m_N and scoring it
    
    
    // Horizontal check
    for (int l = 1; l <= s.levels(); l++) {
        
        // Put the entire level in the vector
        for (int c = 1; c <= s.cols(); c++) {
            level_score[c - 1] = s.checkerAt(c, l);
        }
        
        // Break up the vector into sets of m_N
        for (int c = 1; c <= s.cols() - m_N + 1; c++) {
            for (int i = 0; i < m_N; i++) {
                checkers[i] = level_score[c + i - 1];
            }
            
            // Find the score of each set
            score += setScore(checkers, player, m_N);
        }
    }
    
    // Vertical check
    for (int c = 1; c <= s.cols(); c++) {
        for (int l = 1; l <= s.levels(); l++) {
            col_score[l - 1] = s.checkerAt(c, l);
        }
        for (int l = 1; l <= s.levels() - m_N + 1; l++) {
            for (int i = 0; i < m_N; i++) {
                checkers[i] = col_score[l + i - 1];
            }
            score += setScore(checkers, player, m_N);
        }
    }
    
    // Diagonal check NE
    for (int l = 1; l <= s.levels() - m_N + 1; l++) {
        for (int c = 1; c <= s.cols(); c++) {
            level_score[c - 1] = s.checkerAt(c, l);
        }
        for (int c = 1; c <= s.cols() - m_N + 1; c++) {
            for (int i = 0; i < m_N; i++) {
                checkers[i] = s.checkerAt(c + i, l + i);
            }
            score += setScore(checkers, player, m_N);
        }
    }
    
    // Diagonal check SE
    for (int l = 1; l <= s.levels() - m_N + 1; l++) {
        for (int c = 1; c <= s.cols(); c++) {
            level_score[c - 1] = s.checkerAt(c, l);
        }
        for (int c = 1; c <= s.cols() - m_N + 1; c++) {
            for (int i = 0; i < m_N; i++) {
                checkers[i] = s.checkerAt(c + i, l + m_N - 1 - i);
            }
            score += setScore(checkers, player, m_N);
        }
    }
    
    return score;
    
}
                
                
//******************** Player derived class functions *************************

//  These functions simply delegate to the Impl classes' functions.
//  You probably don't want to change any of this code.

HumanPlayer::HumanPlayer(string nm)
 : Player(nm)
{
    m_impl = new HumanPlayerImpl;
}
 
HumanPlayer::~HumanPlayer()
{
    delete m_impl;
}
 
int HumanPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

BadPlayer::BadPlayer(string nm)
 : Player(nm)
{
    m_impl = new BadPlayerImpl;
}
 
BadPlayer::~BadPlayer()
{
    delete m_impl;
}
 
int BadPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

SmartPlayer::SmartPlayer(string nm)
 : Player(nm)
{
    m_impl = new SmartPlayerImpl;
}
 
SmartPlayer::~SmartPlayer()
{
    delete m_impl;
}
 
int SmartPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    
    return m_impl->chooseMove(s, N, color);
}
