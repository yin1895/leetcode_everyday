#include<iostream>
#include<array>
#include<forward_list>
using namespace std;

int main(){
    array<int, 5>myArray = {1,2,3,4,5};

    for(const auto& value : myArray) {
        cout << value << " ";
    }
    cout << endl;
    cout << "Element at index 2:" << myArray.at(5) << endl;
    cout << "Array size: " << myArray.size() << endl;
    std::cout << "First element: " << myArray.front() << std::endl;
    std::cout << "Last element: " << myArray.back() << std::endl;
    myArray[3] = 10;
    for (const auto& value : myArray) {
        cout << value<<" ";
    }
    cout << endl;

    return 0;
}