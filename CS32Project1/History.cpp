#include <iostream>
#include "globals.h"
#include "History.h"
using namespace std;

History::History(int nRows, int nCols) {
	rows = nRows;
	cols = nCols;
	for (int i = 0; i < MAXROWS; i++) {
		for (int j = 0; j < MAXCOLS; j++) {
			total[i][j] = 0;
		}
	}
}

bool History::record(int r, int c) {
	if (r > rows || r < 1 || c > cols || c < 1) {
		return false;
	}
	total[r - 1][c - 1]++;
	return true;
}

void History::display() const {
	clearScreen();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (total[i][j] == 0) {
				cout << ".";
			}
			else if (total[i][j] >= 26) {
				cout << "Z";
			}
			else {
				char temp = 64 + total[i][j];
				cout << temp;
			}
		}
		cout << endl;
	}
	cout << endl;
}