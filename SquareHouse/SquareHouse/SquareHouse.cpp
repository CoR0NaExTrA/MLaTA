#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

const int MAX = 100;
int N, M;
bool grid[MAX][MAX];
bool visited[MAX][MAX];

int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };

int bfs(int sx, int sy) {
    queue<pair<int, int>> q;
    q.push({ sx, sy });
    visited[sx][sy] = true;
    int area = 1;

    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx >= 0 && nx < M && ny >= 0 && ny < M && grid[nx][ny] && !visited[nx][ny]) {
                visited[nx][ny] = true;
                q.push({ nx, ny });
                area++;
            }
        }
    }

    return area;
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    fin >> N >> M;

    for (int i = 0; i < M; ++i)
        for (int j = 0; j < M; ++j)
            grid[i][j] = true;

    for (int i = 0; i < N; ++i) {
        int D, X, Y;
        fin >> D >> X >> Y;
        for (int x = X; x < X + D; ++x)
            for (int y = Y; y < Y + D; ++y)
                grid[x][y] = false;
    }

    int max_area = 0;
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < M; ++j)
            if (grid[i][j] && !visited[i][j]) {
                max_area = max(max_area, bfs(i, j));
            }

    fout << max_area << endl;

    return 0;
}
