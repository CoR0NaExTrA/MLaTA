#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

const int MAX_N = 1000;

// Функция для подсчёта минимальных перестановок
void find_swaps(vector<int>& mapping, int& swaps) {
    int n = mapping.size();
    bitset<MAX_N> visited;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            int cycle_size = 0, j = i;
            while (!visited[j]) {
                visited[j] = 1;
                j = mapping[j];
                cycle_size++;
            }
            if (cycle_size > 1) swaps += (cycle_size - 1);
        }
    }
}

int main() {
    ifstream fin("input2.txt");
    ofstream fout("OUTPUT.TXT");

    int n;
    fin >> n;

    vector<vector<int>> matrix(n, vector<int>(n));
    vector<pair<int, int>> positions(n * n + 1);

    for (int i = 0, value; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fin >> value;
            positions[value] = { i, j };
        }
    }

    vector<int> row_map(n, -1), col_map(n, -1);
    bool is_possible = true;

    for (int i = 1; i <= n * n; i++) {
        int sorted_row = (i - 1) / n;
        int sorted_col = (i - 1) % n;
        auto [cur_row, cur_col] = positions[i];

        if (row_map[cur_row] == -1) {
            row_map[cur_row] = sorted_row;
        }
        else if (row_map[cur_row] != sorted_row) {
            is_possible = false;
            break;
        }

        if (col_map[cur_col] == -1) {
            col_map[cur_col] = sorted_col;
        }
        else if (col_map[cur_col] != sorted_col) {
            is_possible = false;
            break;
        }
    }

    if (!is_possible) {
        fout << "No\n";
        return 0;
    }

    fout << "Yes\n";

    vector<int> row_permutation(n), col_permutation(n);
    for (int i = 0; i < n; i++) {
        row_permutation[row_map[i]] = i;
        col_permutation[col_map[i]] = i;
    }

    int swaps = 0;
    find_swaps(row_permutation, swaps);
    find_swaps(col_permutation, swaps);

    fout << swaps << '\n';

    return 0;
}
