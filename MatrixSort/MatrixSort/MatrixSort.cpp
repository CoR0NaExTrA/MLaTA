#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

void find_swaps(vector<int>& mapping, int& swaps) {
    int n = mapping.size();
    vector<bool> visited(n, false);

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            int cycle_size = 0;
            int j = i;
            while (!visited[j]) {
                visited[j] = true;
                j = mapping[j];
                cycle_size++;
            }
            if (cycle_size > 1) {
                swaps += (cycle_size - 1);
            }
        }
    }
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("OUTPUT.TXT");

    int n;
    fin >> n;

    vector<vector<int>> matrix(n, vector<int>(n));
    map<int, pair<int, int>> positions;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fin >> matrix[i][j];
            positions[matrix[i][j]] = { i, j };
        }
    }

    vector<int> row_map(n), col_map(n);

    for (int i = 1; i <= n * n; i++) {
        int sorted_row = (i - 1) / n;
        int sorted_col = (i - 1) % n;

        auto [cur_row, cur_col] = positions[i];

        row_map[cur_row] = sorted_row;
        col_map[cur_col] = sorted_col;
    }

    sort(row_map.begin(), row_map.end());
    sort(col_map.begin(), col_map.end());

    for (int i = 0; i < n; i++) {
        if (row_map[i] != i || col_map[i] != i) {
            fout << "No" << endl;
            return 0;
        }
    }

    fout << "Yes" << endl;

    vector<int> row_permutation(n), col_permutation(n);

    for (int i = 0; i < n; i++) {
        row_permutation[positions[i * n + 1].first] = i;
        col_permutation[positions[i + 1].second] = i;
    }

    int swaps = 0;
    find_swaps(row_permutation, swaps);
    find_swaps(col_permutation, swaps);

    fout << swaps << endl;

    return 0;
}
