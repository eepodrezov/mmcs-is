#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <map>

using namespace std;
using namespace std::chrono;

const int N = 4; // Размер поля 4x4
const string goal = "123456789ABCDEF0"; // Целевая позиция

// Функция для вычисления манхэттенского расстояния
int manhattanDistance(const string& state) {
    int dist = 0;
    for (int i = 0; i < N * N; ++i) {
        if (state[i] == '0') continue; // Пустая клетка
        int value = state[i] >= 'A' ? state[i] - 'A' + 10 : state[i] - '1' + 1;
        int goal_x = (value - 1) % N, goal_y = (value - 1) / N;
        int x = i % N, y = i / N;
        dist += abs(x - goal_x) + abs(y - goal_y);
    }
    return dist;
}

// Проверка на решаемость позиции
bool isSolvable(const string& state) {
    int inversions = 0;
    vector<int> tiles;
    
    for (size_t i = 0; i < state.size(); ++i) {
        char c = state[i];
        if (c != '0') {
            tiles.push_back(c >= 'A' ? c - 'A' + 10 : c - '1' + 1);
        }
    }

    for (size_t i = 0; i < tiles.size(); ++i) {
        for (size_t j = i + 1; j < tiles.size(); ++j) {
            if (tiles[i] > tiles[j]) ++inversions;
        }
    }

    int zero_row = state.find('0') / N;
    return (inversions + zero_row) % 2 == 0; // Чётность суммы инверсий и строки с пустой ячейкой
}

// Поиск A* с использованием манхэттенского расстояния
vector<string> aStarSearch(const string& start) {
    if (!isSolvable(start)) return {}; // Если не решаемая позиция, возвращаем пустой результат

    auto cmp = [](pair<string, int>& a, pair<string, int>& b) {
        return a.second > b.second;
    };
    priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp)> pq(cmp);
    set<string> visited;
    map<string, string> parent;
    map<string, int> g_score;

    pq.push({start, manhattanDistance(start)});
    g_score[start] = 0;
    parent[start] = "";

    vector<string> directions = {"L", "R", "U", "D"};
    vector<int> drow = {0, 0, -1, 1};
    vector<int> dcol = {-1, 1, 0, 0};

    while (!pq.empty()) {
        auto [current, f_score] = pq.top(); pq.pop();

        if (current == goal) {
            vector<string> path;
            while (current != "") {
                path.push_back(current);
                current = parent[current];
            }
            reverse(path.begin(), path.end());
            return path;
        }

        if (visited.find(current) != visited.end()) continue;
        visited.insert(current);

        int zero_pos = current.find('0');
        int row = zero_pos / N, col = zero_pos % N;

        for (int i = 0; i < 4; ++i) {
            int new_row = row + drow[i], new_col = col + dcol[i];
            if (new_row < 0 || new_row >= N || new_col < 0 || new_col >= N) continue;

            string next_state = current;
            swap(next_state[zero_pos], next_state[new_row * N + new_col]);

            int tentative_g_score = g_score[current] + 1;
            if (g_score.find(next_state) == g_score.end() || tentative_g_score < g_score[next_state]) {
                g_score[next_state] = tentative_g_score;
                parent[next_state] = current;
                pq.push({next_state, tentative_g_score + manhattanDistance(next_state)});
            }
        }
    }
    return {};
}

// Функция для выполнения теста на одном наборе данных
void runTest(const string& start, int expectedSteps) {
    auto start_time = high_resolution_clock::now();
    vector<string> solution = aStarSearch(start);
    auto end_time = high_resolution_clock::now();

    if (solution.empty()) {
        cout << "Исходное положение: " << start << endl;
        cout << "Решения нет (нерешаемая позиция)" << endl;
    } else {
        int calculatedSteps = solution.size() - 1;
        auto duration = duration_cast<milliseconds>(end_time - start_time);

        cout << "Исходное положение: " << start << endl;
        cout << "Ожидаемое количество шагов: " << expectedSteps << endl;
        cout << "Рассчитанное количество шагов: " << calculatedSteps << endl;
        cout << (calculatedSteps == expectedSteps ? "Тест пройден" : "Тест не пройден") << endl;
        cout << "Время выполнения: " << duration.count() << " ms\n" << endl;
    }
}

// Тестовая функция для нескольких наборов данных
void runTests(const vector<pair<string, int>>& testCases) {
    for (size_t i = 0; i < testCases.size(); ++i) {
        runTest(testCases[i].first, testCases[i].second);
    }
}

int main() {
    vector<pair<string, int>> testCases = {
        {"123456789AFB0EDC", -1},
        {"F2345678A0BE91CD", -1},
        {"123456789ABCDEF0", 0},
        {"1234067859ACDEBF", 5},
        {"5134207896ACDEBF", 8},
        {"16245A3709C8DEBF", 10},
        {"1723068459ACDEBF", 13},
        {"12345678A0BE9FCD", 19},
        {"51247308A6BE9FCD", 27},
        {"F2345678A0BE91DC", 33},
        {"75123804A6BE9FCD", 35},
        {"75AB2C416D389F0E", 45},
        {"04582E1DF79BCA36", 48},
        {"FE169B4C0A73D852", 52},
        {"D79F2E8A45106C3B", 55},
        {"DBE87A2C91F65034", 58},
        {"BAC0F478E19623D5", 61}
    };

    runTests(testCases);

    return 0;
}
