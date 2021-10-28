#include <iostream>
#include <queue>
using namespace std;

class Coord
{
  public:
    Coord(int r, int c) : m_row(r), m_col(c) {}
    int r() const { return m_row; }
    int c() const { return m_col; }
  private:
    int m_row;
    int m_col;
};

bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
    
    
    queue<Coord> q;
    
    q.push(Coord(sr, sc));
    maze[sr][sc] = '+';
    
    while (!q.empty()) {
        
        Coord curr = q.front();
        q.pop();
        
        if (curr.r() == er && curr.c() == ec) return true;
        
        if (maze[curr.r() + 1][curr.c()] != 'X' && maze[curr.r() + 1][curr.c()] != '+') {
            q.push(Coord(curr.r() + 1, curr.c()));
            maze[curr.r() + 1][curr.c()] = '+';
        }
        
        if (maze[curr.r()][curr.c() - 1] != 'X' && maze[curr.r()][curr.c() - 1] != '+') {
            q.push(Coord(curr.r(), curr.c() - 1));
            maze[curr.r()][curr.c() - 1] = '+';
        }
        
        if (maze[curr.r() - 1][curr.c()] != 'X' && maze[curr.r() - 1][curr.c()] != '+') {
            q.push(Coord(curr.r() - 1, curr.c()));
            maze[curr.r() - 1][curr.c()] = '+';
        }
        
        if (maze[curr.r()][curr.c() + 1] != 'X' && maze[curr.r()][curr.c() + 1] != '+') {
            q.push(Coord(curr.r(), curr.c() + 1));
            maze[curr.r()][curr.c() + 1] = '+';
        }
        
    }
    
    return false;
}

int main()
{
    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X' },
        { 'X','.','.','.','.','X','.','.','X','X' },
        { 'X','.','X','X','.','X','X','.','.','X' },
        { 'X','X','X','.','.','.','.','X','.','X' },
        { 'X','.','X','X','X','.','X','X','X','X' },
        { 'X','.','X','.','.','.','X','.','.','X' },
        { 'X','.','.','.','X','.','X','.','.','X' },
        { 'X','X','X','X','X','.','X','.','X','X' },
        { 'X','.','.','.','.','.','.','.','.','X' },
        { 'X','X','X','X','X','X','X','X','X','X' }
    };

    if (pathExists(maze, 3,5, 8,8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}

