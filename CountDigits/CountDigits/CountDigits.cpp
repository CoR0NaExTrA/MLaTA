#include <iostream>
#include <fstream>
#include <cmath>

long long countDigits(long long x) {
    if (x == 0) return 0;
    long long count = 0;
    long long power = 1;
    int length = 1;

    while (power * 10 <= x) {
        count += (power * 9) * length;
        power *= 10;
        length++;
    }
    count += (x - power + 1) * length;
    return count;
}

int main() {
    std::ifstream fin("INPUT.TXT");
    std::ofstream fout("OUTPUT.TXT");

    long long M, N;
    fin >> M >> N;

    long long result = countDigits(N) - countDigits(M - 1);
    fout << result << std::endl;

    return 0;
}