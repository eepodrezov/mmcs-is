#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;

int minOperations(int start, int target) {
    queue<int> q;
    unordered_map<int, int> dist; // для хранения минимального количества операций для каждого числа

    q.push(start);
    dist[start] = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        // Проверяем возможные операции
        int next1 = current + 3;
        int next2 = current * 2;

        // Если достигли целевого числа, возвращаем количество операций
        if (current == target) {
            return dist[current];
        }

        // Добавляем в очередь новые числа для обработки, если еще не обработаны
        if (dist.find(next1) == dist.end()) {
            q.push(next1);
            dist[next1] = dist[current] + 1;
        }
        if (dist.find(next2) == dist.end()) {
            q.push(next2);
            dist[next2] = dist[current] + 1;
        }
    }

    // Если не удалось достичь целевого числа (на всякий случай)
    return -1;
}

int testMinOperations(int testIndex, int start, int target, int result) {
    std::cout << "Тест " << testIndex << " для (" << start << ", " << target << ") "
              << (minOperations(start, target) == result ? "пройден!" : "не пройден!") << " Результат:" << result << std::endl;
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
