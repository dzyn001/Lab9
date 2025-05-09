#include <iostream>
#include <thread>
#include <vector>

int counter = 0;

int main() {
    std::vector<std::thread> threads;

    for (int i = 1; i <= 3; ++i) {
        threads.emplace_back([i]() {
            counter += i;
            std::cout << "Thread " << i << ": counter = " << counter << std::endl;
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}

