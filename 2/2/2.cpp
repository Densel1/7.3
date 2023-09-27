


#include <iostream>
#include <vector>       // std::vector
#include <future>
#include <algorithm>


using namespace std;


template<class InputIterator, class Function>
Function parallel_for_each(InputIterator first, InputIterator last, Function fn)
{
    const unsigned long length = distance(first, last);
    const unsigned long interval = 3;
    if (length <= interval) return for_each(first, last, fn);
    auto middle = first;
    advance(middle, length / 2);
    std::future<Function> f_result = std::async(parallel_for_each<InputIterator, Function>, middle, last, fn);
    Function l_result = parallel_for_each(first, middle, fn);
    f_result.wait();
    return  move(fn);
}



void myfunction(int i) {  // function:
    std::cout << ' ' << i;
}

struct myclass {           // function object type:
    void operator() (int i) { std::cout << ' ' << i; }
} myobject;

int main() {
    std::vector<int> myvector;
    myvector.push_back(10);
    myvector.push_back(20);
    myvector.push_back(30);
    myvector.push_back(40);
    myvector.push_back(50);
    myvector.push_back(60);
    myvector.push_back(70);
    myvector.push_back(80);
    myvector.push_back(90);

    std::cout << "myvector contains:";
    parallel_for_each(myvector.begin(), myvector.end(), myfunction);
    std::cout << '\n';

    // or:
    std::cout << "myvector contains:";
    parallel_for_each(myvector.begin(), myvector.end(), myobject);
    std::cout << '\n';

    return 0;
}