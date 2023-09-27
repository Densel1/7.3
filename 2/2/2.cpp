


#include <iostream>
#include <vector>       // std::vector
#include <future>


using namespace std;


template<class InputIterator, class Function>
Function for_each1(InputIterator first, InputIterator last, Function fn)
{
    if (first == last) return move(fn);
    std::future<Function> result = std::async(for_each<InputIterator, Function>, first, last, fn);
    ++first;
    return move(fn);  
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

    std::cout << "myvector contains:";
    for_each1(myvector.begin(), myvector.end(), myfunction);
    std::cout << '\n';

    // or:
    std::cout << "myvector contains:";
    for_each1(myvector.begin(), myvector.end(), myobject);
    std::cout << '\n';

    return 0;
}