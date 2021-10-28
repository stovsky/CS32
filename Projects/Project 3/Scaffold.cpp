// Scaffold.cpp

#include "provided.h"
#include <vector>
#include <iostream>
#include <stack>
#include <cstdlib>
using namespace std;

class ScaffoldImpl
{
  public:
    ScaffoldImpl(int nColumns, int nLevels);
    int cols() const;
    int levels() const;
    int numberEmpty() const;
    int checkerAt(int column, int level) const;
    void display() const;
    bool makeMove(int column, int color);
    int undoMove();
private:
    int m_nColumns;
    int m_nLevels;
    stack<int> m_last;
    vector<vector<char>> m_scaffold;
};

ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels)
{
    
    if (nColumns < 1 || nLevels < 1) {
        exit(1);
    }
    
    m_nColumns = nColumns;
    m_nLevels = nLevels;
    
    // Create an m_NLevels x m_nColumns vector
    m_scaffold.resize(m_nLevels);
    for (int i = 0; i < m_nLevels; i++) {
        m_scaffold[i].resize(m_nColumns);
    }
    
    // Initialize every space to be empty
    for (int l = 0; l < m_nLevels; l++) {
        for (int c = 0; c < m_nColumns; c++) {
            m_scaffold[l][c] = ' ';
        }
    }
     
}

int ScaffoldImpl::cols() const
{
    return m_nColumns;
}

int ScaffoldImpl::levels() const
{
    return m_nLevels;
}

int ScaffoldImpl::numberEmpty() const
{
    int counter = 0;
    for (int l = 0; l < m_nLevels; l++) {
        for (int c = 0; c < m_nColumns; c++) {
            if (m_scaffold[l][c] == ' ') counter++; // Count the amount of empty spaces in the scaffold
        }
    }
    return counter;
}

int ScaffoldImpl::checkerAt(int column, int level) const
{
    
    if (column > 0 && column <= m_nColumns && level > 0 && level <= m_nLevels) {
        
        // Given a column and level, this will convert to its correct index value in the vector
        if (m_scaffold[m_nLevels - level][column - 1] == 'R') return RED;
        else if (m_scaffold[m_nLevels - level][column - 1] == 'B') return BLACK;
    }
    
    return VACANT;

}

void ScaffoldImpl::display() const
{
    
    // Display '|' every even index and the correct checker otherwise
    for (int l = 0; l < m_nLevels; l++) {
        for (int c = 0; c < 2 * m_nColumns + 1; c++) {
            if (c % 2 == 0) cout << '|';
            else cout << m_scaffold[l][(c - 1) / 2];
        }
        cout << endl;
    }
    
    // At the bottom, display '+' and '-' every other
    for (int i = 0; i < 2 * m_nColumns + 1; i++) {
        if (i % 2 == 0) cout << '+';
        else  cout << '-';
    }
    cout << endl;
     
    
}

bool ScaffoldImpl::makeMove(int column, int color)
{
    
    if (column > m_nColumns || column <= 0) return false;  // If column is invalid, return false
    if (color != RED && color != BLACK) return false; // If color is invalid, return false
    
    bool isVacant = false;
    if (checkerAt(column, levels()) == VACANT) isVacant = true; // Check if there is a vacant spot in the column
    
    if (!isVacant) return false; // If no vacant spot in the column, return false
    
    int c = column - 1;
    
    // Convert to the correct letter
    if (color == RED) color += 82;
    else color += 65;
    
    // Traverse up until we find the closest vacant spot to the bottom
    for (int i = m_nLevels - 1; i >= 0; i--) {
        if (m_scaffold[i][c] == ' ') {
            m_scaffold[i][c] = color; // Set the scaffold to the new color
            m_last.push(c); // Push the column and level on the stack so we can remember it if we need to undo
            m_last.push(i);
            break;
            
        }
    }

    return true;
}

int ScaffoldImpl::undoMove()
{
    
    if (numberEmpty() == m_nColumns * m_nLevels) return 0; // If the scaffold is empty, do nothing
    
    // Take the most recent column and level off the stack and store their values
    int lastL = m_last.top();
    m_last.pop();
    int lastC = m_last.top();
    m_last.pop();
    
    // Set that position back to vacant
    m_scaffold[lastL][lastC] = ' ';
    
    return lastC + 1;
    
}

//******************** Scaffold functions *******************************

//  These functions simply delegate to ScaffoldImpl's functions.
//  You probably don't want to change any of this code.

Scaffold::Scaffold(int nColumns, int nLevels)
{
    m_impl = new ScaffoldImpl(nColumns, nLevels);
}
 
Scaffold::~Scaffold()
{
    delete m_impl;
}
 
Scaffold::Scaffold(const Scaffold& other)
{
    m_impl = new ScaffoldImpl(*other.m_impl);
}
 
Scaffold& Scaffold::operator=(const Scaffold& rhs)
{
    if (this != &rhs)
    {
        Scaffold temp(rhs);
        swap(m_impl, temp.m_impl);
    }
    return *this;
}
 
int Scaffold::cols() const
{
    return m_impl->cols();
}

int Scaffold::levels() const
{
    return m_impl->levels();
}

int Scaffold::numberEmpty() const
{
    return m_impl->numberEmpty();
}

int Scaffold::checkerAt(int column, int level) const
{
    return m_impl->checkerAt(column, level);
}
 
void Scaffold::display() const
{
    m_impl->display();
}
 
bool Scaffold::makeMove(int column, int color)
{
    return m_impl->makeMove(column, color);
}
 
int Scaffold::undoMove()
{
    return m_impl->undoMove();
}
