/*
Prilikom pokretanja
aplikacije korisnik unosi redak i stupac početne točke A i redak i stupac krajnje točke B (broj retka ide od 1
do 20, a broj stupca od 1 do 40). Nakon toga, aplikacija treba osmisliti put od točke A do točke B i svakih
100 milisekundi iscrtati gdje se trenutno nalazimo. Točka A i točka B se mogu nalaziti na bilo kojem
dopuštenom mjestu (isprobajte kako radi aplikacija u prilogu s A = 1, 1 i B = 20, 40, te kako radi s A = 20,
20 i B = 10, 10).
*/
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

const int ROWS = 20;
const int COLS = 40;
const int DELAY_MS = 100;

struct Point {
    int row, col;
};

void printGrid(const vector<vector<char>>& grid) {
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            cout << cell;
        }
        cout << endl;
    }
}

vector<Point> findPath(Point start, Point end) {
    vector<Point> path;
    Point current = start;

    while (current.row != end.row || current.col != end.col) {
        path.push_back(current);
        if (current.row < end.row) current.row++;
        else if (current.row > end.row) current.row--;
        else if (current.col < end.col) current.col++;
        else if (current.col > end.col) current.col--;
    }
    path.push_back(end);

    return path;
}

int main() {
    cout << "Broj redova: " << ROWS << "," << "broj stupaca: " << COLS << ", " << endl;
    int startRow, startCol, endRow, endCol;
    cout << "Unesite redak pocetne tocke (A): ";
    cin >> startRow;
    cout << "Unesite stupac pocetne tocke (A): ";
    cin >> startCol;
    cout << "Unesite redak krajnje tocke (B): ";
    cin >> endRow;
    cout << "Unesite stupac krajnje tocke (B): ";
    cin >> endCol;

    Point start = { startRow - 1, startCol - 1 };
    Point end = { endRow - 1, endCol - 1 };

    vector<vector<char>> grid(ROWS, vector<char>(COLS, '.'));
    grid[start.row][start.col] = 'A';
    grid[end.row][end.col] = 'B';

    vector<Point> path = findPath(start, end);

    for (const auto& p : path) {
        if (p.row != start.row || p.col != start.col) grid[p.row][p.col] = '*';
        printGrid(grid);
        this_thread::sleep_for(chrono::milliseconds(DELAY_MS));
        system("cls");
    }

    printGrid(grid);

    return 0;
}