

#include <algorithm>
#include <chrono>
#include <exception>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>
#include <random>
#include <iterator>
#include <functional>
#include <algorithm>


using namespace std;


void findSmallestPosition(std::vector<int>& arr, int startPosition, promise<int> pr)
{


    int smallestPosition = startPosition;

    for (int i = startPosition; i < arr.size(); i++)
    {
        if (arr[i] < arr[smallestPosition])
            smallestPosition = i;
    }
    pr.set_value(smallestPosition);

}


void selection_sort(std::vector<int>& arr, int i) {

    promise<int> pr;
    future<int> fut = pr.get_future();
    auto smallestPosition =  async(findSmallestPosition, ref(arr) ,i , move(pr));
    swap(arr[i], arr[fut.get()]);
    return;
}



int main()
{
    int element_num = 100;
    vector<int> arr(element_num);
    mt19937 gen;
    uniform_int_distribution<int> dis(0, element_num);
    auto rand_num([=]() mutable {return dis(gen); });
    generate(arr.begin(), arr.end(), rand_num);
//    std::vector<int> arr = { 4, 3, 7, 1, 2, 6 };

    // Запуск сортировки выбором
    for (int num = 0; num < arr.size();num++) {
      selection_sort(arr,num);
    }

    cout << endl;
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
