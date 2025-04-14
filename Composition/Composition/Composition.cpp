#include <fstream>
#include <vector>

int main() {
    std::ifstream fin("input.txt");
    std::ofstream fout("OUTPUT.TXT");

    int N;
    fin >> N;

    std::vector<int> result;
    int current_sum = 0;
    int next_num = 2;

    while (current_sum + next_num <= N) {
        result.push_back(next_num);
        current_sum += next_num;
        next_num++;
    }

    int diff = N - current_sum;
    if (diff > 0) {
        for (int i = result.size() - 1; i >= 0 && diff > 0; --i) {
            result[i]++;
            diff--;
        }
        if (diff > 0) {
            result.back() += diff;
        }
    }

    for (int num : result) {
        fout << num << " ";
    }

    fin.close();
    fout.close();
    return 0;
}