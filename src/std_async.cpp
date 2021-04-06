#include <chrono>
#include <future>
#include <iostream>
#include <thread>
#include <vector>

#include "common/prime.h"

int calc_nth_prime(int n)
{
    return nth_prime(n);
}

int main()
{
    const auto t1 = std::chrono::high_resolution_clock::now();

    std::vector<std::future<int>> futures;
    int sum_of_primes = 0;

    for (int n = 30000; n <= 30010; ++n)
        futures.emplace_back(std::async(std::launch::async, calc_nth_prime, n));

    for (auto& f : futures)
        sum_of_primes += f.get();

    const auto t2 = std::chrono::high_resolution_clock::now();
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

    std::cout << "sum of primes = " << sum_of_primes << '\n';
    std::cout << "duration: " << ms.count() << "ms\n";
}
