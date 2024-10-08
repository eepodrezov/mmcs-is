#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int bidirectionalSearch(int start, int target) {
    if (start == target) {
        return 0;
    }

    queue<int> q_start, q_target;
    unordered_map<int, int> dist_start, dist_target;

    q_start.push(start);
    dist_start[start] = 0;
    q_target.push(target);
    dist_target[target] = 0;

    while (!q_start.empty() && !q_target.empty()) {
        // Поиск из начального состояния
        int current_start = q_start.front();
        q_start.pop();
        int dist_start_current = dist_start[current_start];

        // Проверяем возможные операции
        int next1_start = current_start + 3;
        int next2_start = current_start * 2;

        if (dist_target.find(next1_start) != dist_target.end()) {
            return dist_start_current + 1 + dist_target[next1_start];
        }
        if (dist_target.find(next2_start) != dist_target.end()) {
            return dist_start_current + 1 + dist_target[next2_start];
        }

        if (dist_start.find(next1_start) == dist_start.end()) {
            q_start.push(next1_start);
            dist_start[next1_start] = dist_start_current + 1;
        }
        if (dist_start.find(next2_start) == dist_start.end()) {
            q_start.push(next2_start);
            dist_start[next2_start] = dist_start_current + 1;
        }

        // Поиск из целевого состояния
        int current_target = q_target.front();
        q_target.pop();
        int dist_target_current = dist_target[current_target];

        // Проверяем возможные операции в обратном порядке
        if (current_target % 2 == 0) {
            int next1_target = current_target / 2;
            if (dist_start.find(next1_target) != dist_start.end()) {
                return dist_target_current + 1 + dist_start[next1_target];
            }
            if (dist_target.find(next1_target) == dist_target.end()) {
                q_target.push(next1_target);
                dist_target[next1_target] = dist_target_current + 1;
            }
        }

        int next2_target = current_target - 3;
        if (next2_target >= 0) {
            if (dist_start.find(next2_target) != dist_start.end()) {
                return dist_target_current + 1 + dist_start[next2_target];
            }
            if (dist_target.find(next2_target) == dist_target.end()) {
                q_target.push(next2_target);
                dist_target[next2_target] = dist_target_current + 1;
            }
        }
    }

    return -1; // В случае, если не удалось достичь целевого числа
}

int testMinOperations(int testIndex, int start, int target, int result) {
    std::cout << "Тест " << testIndex << " для (" << start << ", " << target << ") "
              << (bidirectionalSearch(start, target) == result ? "пройден!" : "не пройден!") << " Результат:" << result << std::endl;
    return 0;
}

int main() {
    // Примеры тестов
    testMinOperations(1, 1, 100, 7);
    testMinOperations(2, 2, 55, 6);
    testMinOperations(3, 2, 100, 7);
    testMinOperations(4, 1, 97, 8);
    testMinOperations(5, 2, 1000, 12);
    testMinOperations(6, 2, 10000001, 30);

    return 0;
}
