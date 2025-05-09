#include <iostream>
#include <thread>
#include <vector>

int main() {
    std::vector<std::thread> threads;

    for (int i = 1; i <= 3; ++i) {
        threads.emplace_back([i]() {
            int result = i * i;
            std::cout << "Thread " << i << ": " << i << "^2 = " << result << std::endl;
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
