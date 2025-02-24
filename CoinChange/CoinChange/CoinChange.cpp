#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <fstream>
#include <map>

int main() {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    int L, N;
    fin >> L >> N;
    std::vector<int> coins(N);
    for (int i = 0; i < N; ++i) {
        fin >> coins[i];
    }

    sort(coins.rbegin(), coins.rend());

    std::vector<int> dp(L + 1, INT_MAX);
    std::vector<int> last_coin(L + 1, -1);
    dp[0] = 0;

    for (int coin : coins) {
        for (int j = coin; j <= L; ++j) {
            if (dp[j - coin] != INT_MAX && dp[j] > dp[j - coin] + 1) {
                dp[j] = dp[j - coin] + 1;
                last_coin[j] = coin;
            }
        }
    }

    if (dp[L] == INT_MAX) {
        fout << "No" << std::endl;
        return 0;
    }

    std::map<int, int> coin_count;
    int sum = L;
    while (sum > 0) {
        int coin = last_coin[sum];
        coin_count[coin]++;
        sum -= coin;
    }

    fout << coin_count.size() << " " << dp[L] << std::endl;
    for (auto it = coin_count.rbegin(); it != coin_count.rend(); ++it) {
        fout << it->first << " " << it->second << std::endl;
    }

    return 0;
}
