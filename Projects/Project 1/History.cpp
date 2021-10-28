#include <iostream>
#include "History.h"
using namespace std;

History::History(int nRows, int nCols) : m_rows(nRows), m_cols(nCols)
{
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            m_city[i][j] = 0;
        }
    }
}

bool History::record(int r, int c) {
    
    if (r < 1 || r > m_rows || c < 1 || c > m_cols) return false;
    m_city[r - 1][c - 1]++;
    return true;

}

void History::display() const {
    clearScreen();
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            if (m_city[i][j] == 0) cout << '.';
            else if (m_city[i][j] <= 26) {char ch = m_city[i][j] + 64; cout << ch;}
            else if (m_city[i][j] > 26) cout << 'Z';
        }
        cout << endl;
    }
    cout << endl;
}
