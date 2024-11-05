bool pathExists(string maze[10], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    if (sr < 0 || sr >= nRows || sc < 0 || sc >= nCols || er < 0 || er >= nRows || ec < 0 || ec >= nCols || maze[sr][sc] != '.' || maze[er][ec] != '.') {
        return false;
    }
    if (sr == er && sc == ec) {
        return true;
    }
   
    maze[sr][sc] = 'Q';

    if (pathExists(maze, nRows, nCols, sr - 1, sc, er, ec)) {
        return true;
    }
    if (pathExists(maze, nRows, nCols, sr, sc - 1, er, ec)) {
        return true;
    }
    if (pathExists(maze, nRows, nCols, sr + 1, sc, er, ec)) {
            return true;
        }
    if (pathExists(maze, nRows, nCols, sr, sc + 1, er, ec)) {
            return true;
    }
    return false;
}