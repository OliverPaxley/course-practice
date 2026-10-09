#include "int.h"
using namespace std;
bool validateAge(int val, string& errorMessage) {
    bool res = false;
    if (val < 19) errorMessage = "Too young to drink"; 
    else if (val > 100) errorMessage = "Don't lie about your age nigga";
    else errorMessage = "Perfect, you're good to go", res = true;
    return res;
}
bool validateMark(int val, string& errorMessage) {
    bool res =true; 
    if (val < 0 || val > 100) {
        errorMessage = "invalid marks"; 
        res = false;
    }
    return res;
}

int main() {

    return 0;
}
