//11.5.Клад(6)
//Кладоискатели обнаружили люк в подземелье с сокровищами, закрытый неподъемной квадратной чугунной плитой.
//К счастью, плита имеет сквозную трещину, разделяющую ее на две части, которые не лежат полностью одна внутри другой.
//Трещина представляет собой ломаную без самопересечений и самокасаний.В распоряжении кладоискателей имеется лебедка.
//Мощности лебедки хватает на то, чтобы двигать в определенном направлении без вращения каждую из частей, не поднимая ее, но не всю плиту целиком.
//Требуется по форме трещины определить, могут ли кладоискатели освободить люк.
//Ввод
//В первой строке находится число N, задающее количество вершин ломаной.
//Следующие N строк содержат пары целых чисел - координаты вершин(Xi, Yi).
//Ломаная получается путем последовательного соединения точек в данном порядке.
//Направление обхода вершин ломаной может быть произвольным.
//Точки(X1, Y1) и(XN, YN) лежат на одной или разных сторонах квадрата, остальные точки ломаной – внутри квадрата.
//Ограничения: 3 ≤ N ≤ 100; -100 ≤ Xi ≤ 100; -100 ≤ Yi ≤ 100.
//Вывод
//Выводится единственная строка со значением Yes или No – возможность либо невозможность разъединения квадрата путем перемещения его частей по плоскости без вращений.
//Трофимов Ярослав ПС-24
//Visual Studio 2022

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fout("OUTPUT.TXT");

    int N;
    fin >> N;
    vector<pair<int, int>> points(N);
    for (int i = 0; i < N; i++) {
        fin >> points[i].first >> points[i].second;
    }

    // Находим границы квадрата
    int min_x = 100, max_x = -100, min_y = 100, max_y = -100;
    for (int i = 0; i < N; i++) {
        min_x = min(min_x, points[i].first);
        max_x = max(max_x, points[i].first);
        min_y = min(min_y, points[i].second);
        max_y = max(max_y, points[i].second);
    }

    // Определяем стороны для начальной и конечной точек
    string start_side, end_side;
    if (points[0].first == min_x) start_side = "left";
    else if (points[0].first == max_x) start_side = "right";
    else if (points[0].second == min_y) start_side = "bottom";
    else if (points[0].second == max_y) start_side = "top";

    if (points[N - 1].first == min_x) end_side = "left";
    else if (points[N - 1].first == max_x) end_side = "right";
    else if (points[N - 1].second == min_y) end_side = "bottom";
    else if (points[N - 1].second == max_y) end_side = "top";

    // Проверяем, противоположные ли стороны
    bool can_separate = (start_side == "left" && end_side == "right") ||
        (start_side == "right" && end_side == "left") ||
        (start_side == "top" && end_side == "bottom") ||
        (start_side == "bottom" && end_side == "top");

    fout << (can_separate ? "Yes" : "No");

    fin.close();
    fout.close();
    return 0;
}