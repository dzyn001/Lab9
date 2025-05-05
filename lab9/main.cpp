#include <iostream>
#include <thread>

int main()
{
    std::thread t1([](int x) { std::cout << "Square of " << x << " = " << x * x << std::endl; }, 2);
    std::thread t2([](int x) { std::cout << "Square of " << x << " = " << x * x << std::endl; }, 3);
    std::thread t3([](int x) { std::cout << "Square of " << x << " = " << x * x << std::endl; }, 4);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
