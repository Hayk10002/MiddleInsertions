#include <iostream>
#include <vector>
#include <list>
#include <chrono>
#include <random>
#include <format>

// Random number from 0 to max-1 inclusive
int getRandomNum(int max)
{
    static std::mt19937 engine{ std::random_device{}() };
    std::uniform_int_distribution<int> dist(0, max - 1);
    return dist(engine);
}

// Add number at the middle of the container
// Returns the time 
template<class Container>
auto AddNum(Container& cont, int n)
{
    auto start = std::chrono::system_clock::now();
    
    auto it = cont.begin();
    std::advance(it, cont.size() / 2);

    auto adv_time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - start);

    cont.insert(it, n);

    auto ins_time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - start) - adv_time;

    return std::pair{adv_time, ins_time};
}

template<class F>
auto time_ms(F f, int N)
{
    auto [adv_time, ins_time] = std::invoke_result_t<F>{0, 0};
    for (int i = 0; i < N; i++) 
    {
        auto [adv, ins] = f();
        adv_time += adv;
        ins_time += ins;
    }

    return std::pair{adv_time, ins_time};
}

int main() {
    int N;
    std::cout << "Enter number count: ";
    std::cin >> N;
    std::cout << std::endl;
    
    std::vector<int> v;
    std::list<int> l;
    
    AddNum(l, 10);
    auto [v_adv_time, v_ins_time] = time_ms([&v](){ return AddNum(v, getRandomNum(1000)); }, N);
    auto [l_add_time, l_ins_time] = time_ms([&l](){ return AddNum(l, getRandomNum(1000)); }, N);
    auto v_time = v_adv_time + v_ins_time;
    auto l_time = l_add_time + l_ins_time;
    
    std::cout << std::format(
        "         |  Advance  |  Insert  |   Sum   \n"
        "---------|-----------|----------|---------\n"
        "Vector   |   {0:>8}|  {1:>8}| {4:>8}\n"
        "---------|-----------|----------|---------\n"
        "List     |   {2:>8}|  {3:>8}| {5:>8}\n",
        std::chrono::duration_cast<std::chrono::milliseconds>(v_adv_time), 
        std::chrono::duration_cast<std::chrono::milliseconds>(v_ins_time), 
        std::chrono::duration_cast<std::chrono::milliseconds>(l_add_time), 
        std::chrono::duration_cast<std::chrono::milliseconds>(l_ins_time), 
        std::chrono::duration_cast<std::chrono::milliseconds>(v_time), 
        std::chrono::duration_cast<std::chrono::milliseconds>(l_time)
    );

    return 0;
}
