#include "Grid.h"


int factorial(std::future<int>& f);
void FactorialAsync();
void SetupGrid();

int main()
{
    SetupGrid();
    return 0;
}

int factorial(std::future<int>& f)
{
    int res = 1;
    
    int N = f.get();
    for (int i = N; i > 1; i--)
    {
        res *= i;
    }

    std::cout << "Result is: " << res << std::endl;
    return res;
}

void FactorialAsync()
{
    int x;

    std::promise<int> p;
    std::future<int> f = p.get_future();

    std::future<int> fu = std::async(std::launch::async, factorial, std::ref(f));

    p.set_value(15);

    x = fu.get();
    std::cout << "Get from child: " << x << std::endl;

    return;
}

void SetupGrid()
{
    Grid grid = Grid();
    // "dfsadafsdfsadsafadsfaasdf"
    grid.RefreshLockFiles();
    grid.InputLetters("a2igfjueedgveyixfttaolvnbb", 'n');
    grid.RefreshLockFiles();
    std::chrono::steady_clock::time_point clock_begin = std::chrono::steady_clock::now();
    grid.CreateGrid();

    grid.HashAdjacent();
    grid.Display();

    grid.HashWords();

    grid.TraverseGraph();
    std::chrono::steady_clock::time_point clock_end = std::chrono::steady_clock::now();

    std::chrono::steady_clock::duration time_span = clock_end - clock_begin;
    double nseconds = double(time_span.count()) * std::chrono::steady_clock::period::num / std::chrono::steady_clock::period::den;

    grid.LinkPoints();
    std::cout << "It took me " << nseconds << " seconds." << std::endl << std::endl;
}

