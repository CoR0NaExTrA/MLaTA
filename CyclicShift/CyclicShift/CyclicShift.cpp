#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
    std::ifstream fin("input.txt");
    std::ofstream fout("OUTPUT.TXT");

    int n;
    std::string s;
    fin >> n >> s;

    std::vector<int> balance(2 * n + 1, 0);
    int total = 0;

    for (int i = 0; i < 2 * n; ++i) {
        total += (s[i % n] == '(' ? 1 : -1);
        balance[i + 1] = total;
    }

    if (total != 0) {
        fout << "No\n";
        return 0;
    }

    int min_pos = -1;
    for (int i = 0; i < n; ++i) {
        bool valid = true;
        int base = balance[i];
        for (int j = i + 1; j <= i + n; ++j) {
            if (balance[j] - base < 0) {
                valid = false;
                break;
            }
        }
        if (valid) {
            min_pos = i + 1;
            break;
        }
    }

    if (min_pos != -1)
        fout << min_pos << "\n";
    else
        fout << "No\n";

    return 0;
}
