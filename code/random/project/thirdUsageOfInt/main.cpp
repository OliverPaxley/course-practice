#include "int.h"
using namespace std;
bool validateAge(int val, string& errorMessage) {
    bool res = false;
    if (val < 19) errorMessage = "Too young to drink: "; 
    else if (val > 100) errorMessage = "Don't lie about your age nigga: ";
    else errorMessage = "Perfect, you're good to go", res = true;
    return res;
}
bool validMark(int val, string& errorMessage) {
    bool res =true; 
    if (val < 0 || val > 100) {
        errorMessage = "invalid mark, enter again [1-100]: "; 
        res = false;
    }
    return res;
}

int main() {
    Int val(0, validateAge);
    cout << "Age Please: ";
    cin >> val;
    cout << "Good you are : " << val << ", what drinks do you want." << endl;
    cout << "..............." << endl;
    val.set(validMark);
    cout << "Enter marks: ";
    cin >> val;
    cout << "Your mark is: " << val << endl;
    return 0;
}
