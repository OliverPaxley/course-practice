#include <iostream>
using namespace std;
bool (*cont)(int);
using Condition = bool(*)(int);
using namespace std;

int main() {

    return 0;
}

bool isEven(int x) {
    return x % 2 == 0;
}

size_t countIf(const int* arr, size_t n, Condition cond){
    size_t cnt{}; 
    for (size_t i = 0; i < n; i++){
        if(cond(arr[i])) cnt++;
    }
    return cnt;
}