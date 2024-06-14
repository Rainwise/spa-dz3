#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <thread>
#include <chrono>

using namespace std;

const int ROWS = 20;
const int COLS = 40;
const int WALL_COUNT = 10;
const int DELAY_MS = 100;
const int INF = numeric_limits<int>::max();

struct Point {
    int row, col;
    bool operator==(const Point& other) const {
        return row == other.row && col == other.col;
    }
};

struct Node {
    Point point;
    int distance;
    bool operator>(const Node& other) const {
        return distance > other.distance;
    }
};

vector<Point> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

bool isValid(Point p) {
    return p.row >= 0 && p.row < ROWS && p.col >= 0 && p.col < COLS;
}

vector<Point> dijkstra(vector<vector<char>>& grid, Point start, Point end) {
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    vector<vector<int>> dist(ROWS, vector<int>(COLS, INF));
    vector<vector<Point>> prev(ROWS, vector<Point>(COLS, { -1, -1 }));

    pq.push({ start, 0 });
    dist[start.row][start.col] = 0;

    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();

        Point p = node.point;
        if (p == end) break;

        for (const auto& dir : directions) {
            Point neighbor = { p.row + dir.row, p.col + dir.col };
            if (isValid(neighbor) && grid[neighbor.row][neighbor.col] != '#') {
                int newDist = dist[p.row][p.col] + 1;
                if (newDist < dist[neighbor.row][neighbor.col]) {
                    dist[neighbor.row][neighbor.col] = newDist;
                    prev[neighbor.row][neighbor.col] = p;
                    pq.push({ neighbor, newDist });
                }
            }
        }
    }

    vector<Point> path;
    for (Point at = end; at.row != -1; at = prev[at.row][at.col]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}

void printGrid(const vector<vector<char>>& grid) {
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            cout << cell;
        }
        cout << endl;
    }
}

void generateRandomWalls(vector<vector<char>>& grid, int count) {
    srand(time(0));
    for (int i = 0; i < count; ++i) {
        int row = rand() % ROWS;
        int col = rand() % COLS;
        if (grid[row][col] == '.') {
            grid[row][col] = '#';
        }
    }
}

int main() {
    cout << "Broj redova: " << ROWS << "," << "broj stupaca: " << COLS << ", " << "broj zidova: " << WALL_COUNT << endl;
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

    generateRandomWalls(grid, WALL_COUNT);

    grid[start.row][start.col] = 'A';
    grid[end.row][end.col] = 'B';

    vector<Point> path = dijkstra(grid, start, end);

    for (const auto& p : path) {
        if (p.row != start.row || p.col != start.col) grid[p.row][p.col] = '*';
        printGrid(grid);
        this_thread::sleep_for(chrono::milliseconds(DELAY_MS));
        system("cls");
    }

    printGrid(grid);

    return 0;
}