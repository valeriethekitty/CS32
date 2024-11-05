#include <string>
#include <queue>
#include <iostream>
using namespace std;

class Coord
{
public:
    Coord(int r, int c) : m_r(r), m_c(c) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    // Return true if there is a path from (sr,sc) to (er,ec)
    // through the maze; return false otherwise

    queue<Coord> coordStack;
    Coord a(sr, sc);
    coordStack.push(a);
    maze[sr][sc] = '~';
    while (!coordStack.empty()) {
        Coord b = coordStack.front();
        int r = b.r();
        int c = b.c();
        if (r == er && c == ec) {
            return true;
        }
        coordStack.pop();
        if (r != 0) {
            if (maze[r - 1][c] == '.') {
                coordStack.push(Coord(r - 1, c));
                maze[r - 1][c] = '~';
            }
        }
        if (c != 0) {
            if (maze[r][c - 1] == '.') {
                coordStack.push(Coord(r, c - 1));
                maze[r][c - 1] = '~';
            }
        }
        if (r != nRows) {
            if (maze[r + 1][c] == '.') {
                coordStack.push(Coord(r + 1, c));
                maze[r + 1][c] = '~';
            }
        }
        if (c != nCols) {
            if (maze[r][c + 1] == '.') {
                coordStack.push(Coord(r, c + 1));
                maze[r][c + 1] = '~';
            }
        }

    }
    return false;
}

// 0,0          c
// 
// 
// 
// 
//r

int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X........X",
        "XXXXX.X.XX",
        "X...X.X..X",
        "X.X...X..X",
        "X.XXX.XXXX",
        "XXX....X.X",
        "X.XX.XXX.X",
        "X....X...X",
        "XXXXXXXXXX"
    };

    if (pathExists(maze, 10, 10, 6, 5, 1, 8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}