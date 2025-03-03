/* 4.6. Размен денег (6)
Требуется разменять заданную сумму денег минимальным количеством монет.
Ввод. Первая строка файла INPUT.TXT содержит сумму денег L (1 ≤ L ≤ 20000) и количество типов монет N (1 ≤ N ≤ 30). 
Вторая строка содержит N значений Ci через пробел: стоимости типов монет (1 ≤ Ci ≤ L).
Вывод. В первой строке выводится количество типов монет K, необходимое для размена, и общее минимальное количество монет M. 
В следующих K строках выводятся через пробел по 2 числа: стоимость монеты и количество экземпляров данной монеты. 
Эти K строк должны выводится в порядке убывания стоимости монет. 
Если имеется несколько вариантов решения, достаточно вывести любой из них. 
Если указанную сумму разменять невозможно, то выходной файл должен содержать No. */
//Трофимов Ярослав ПС-24
//Visual Studio 2022

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <fstream>
#include <map>

int main() {
    std::ifstream fin("input6.txt");
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
