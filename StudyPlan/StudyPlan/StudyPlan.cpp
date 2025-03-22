//12.8.Учебный план(5)
//Учебный план включает перечень дисциплин.Задан список пар дисциплин.
//Отдельная пара показывает, что вторая дисциплина должна изучаться после  первой.
//Составить список дисциплин учебного плана в порядке их изучения.
//В том случае, когда задание некорректно, т.е.в списке пар имеются циклы, выдать хотя бы один из них.
//Ввод
//В первой строке задается число пар дисциплин N(1 ≤ N ≤ 300).
//В каждой из следующих N строк указываются через пробел  два  натуральных  числа  Xi, Yi(Xi, Yi ≤ 1000), определяющих номера дисциплин.
//Первая дисциплина должна изучаться раньше второй.
//Вывод.
//В первой строке вывести Yes  либо No – возможность расположения в списке дисциплин в порядке их изучения.
//При наличии такой возможности во второй строке выводится через пробел искомый список.
//Если задание некорректно, т.е.имеется цикл, то во второй строке выдается список номеров, образующих цикл.
//Первый и последний номера в этом списке должны совпадать.
//Трофимов Ярослав ПС-24
//Visual Studio 2022

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <fstream>

using namespace std;

bool FindCycle(int node, unordered_map<int, vector<int>>& graph, unordered_set<int>& visited, unordered_set<int>& recStack, vector<int>& path, vector<int>& cycle) {
    visited.insert(node);
    recStack.insert(node);
    path.push_back(node);

    for (int neighbor : graph[node]) {
        if (recStack.count(neighbor)) {
            cycle.push_back(neighbor);
            for (int i = path.size() - 1; i >= 0; --i) {
                cycle.push_back(path[i]);
                if (path[i] == neighbor) break;
            }
            reverse(cycle.begin(), cycle.end());
            return true;
        }
        if (!visited.count(neighbor) && FindCycle(neighbor, graph, visited, recStack, path, cycle)) {
            return true;
        }
    }

    recStack.erase(node);
    path.pop_back();
    return false;
}

vector<int> DetectCycle(unordered_map<int, vector<int>>& graph, unordered_set<int>& nodes) {
    unordered_set<int> visited, recStack;
    vector<int> path, cycle;
    for (int node : nodes) {
        if (!visited.count(node) && FindCycle(node, graph, visited, recStack, path, cycle)) {
            return cycle;
        }
    }
    return {};
}

vector<int> TopologicalSort(unordered_map<int, vector<int>>& graph, unordered_set<int>& nodes) {
    unordered_map<int, int> inDegree;
    for (int node : nodes) inDegree[node] = 0;
    for (const auto& [key, neighbors] : graph) {
        for (int neighbor : neighbors) {
            inDegree[neighbor]++;
        }
    }

    queue<int> q;
    for (const auto& [node, degree] : inDegree) {
        if (degree == 0) q.push(node);
    }

    vector<int> order;
    while (!q.empty()) {
        int node = q.front(); q.pop();
        order.push_back(node);
        for (int neighbor : graph[node]) {
            if (--inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }
    return (order.size() == nodes.size()) ? order : vector<int>{};
}

int main() {
    ifstream in("input.txt");
    ofstream out("OUTPUT.TXT");

    int n;
    in >> n;
    unordered_map<int, vector<int>> graph;
    unordered_set<int> nodes;

    for (int i = 0; i < n; ++i) {
        int x, y;
        in >> x >> y;
        graph[x].push_back(y);
        nodes.insert(x);
        nodes.insert(y);
    }

    vector<int> cycle = DetectCycle(graph, nodes);
    if (!cycle.empty()) {
        out << "No\n";
        for (int num : cycle) out << num << " ";
        out << "\n";
    }
    else {
        vector<int> order = TopologicalSort(graph, nodes);
        out << "Yes\n";
        for (int num : order) out << num << " ";
        out << "\n";
    }

    return 0;
}
