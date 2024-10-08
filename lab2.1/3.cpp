#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;

int minOperationsReverse(int start, int target) {
    queue<int> q;
    unordered_map<int, int> dist;

    q.push(target);
    dist[target] = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        // Если достигли начального числа, возвращаем количество операций
        if (current == start) {
            return dist[current];
        }

        // Проверяем возможные операции в обратном порядке
        if (current % 2 == 0) {
            int next1 = current / 2;
            if (dist.find(next1) == dist.end()) {
                q.push(next1);
                dist[next1] = dist[current] + 1;
            }
        }

        int next2 = current - 3;
        if (next2 >= 0 && dist.find(next2) == dist.end()) {
            q.push(next2);
            dist[next2] = dist[current] + 1;
        }
    }

    // Если не удалось достичь начального числа (на всякий случай)
    return -1;
}

int testMinOperations(int testIndex, int start, int target, int result) {
    std::cout << "Тест " << testIndex << " для (" << start << ", " << target << ") "
              << (minOperationsReverse(start, target) == result ? "пройден!" : "не пройден!") << " Результат:" << result << std::endl;
    return 0;
}

int main() {
    // Примеры тестов
    testMinOperations(1, 1, 100, 7);
    testMinOperations(2, 2, 55, 6);
    testMinOperations(3, 2, 100, 7);
    testMinOperations(4, 1, 97, 8);
    testMinOperations(5, 2, 1000, 11);
    testMinOperations(6, 3, 1001, 13);
    testMinOperations(7, 2, 3001, 14);
    testMinOperations(8, 2, 10000001, 30);

    return 0;
}
