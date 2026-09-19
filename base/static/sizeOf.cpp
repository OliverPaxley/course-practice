#include <iostream>
using namespace std ;

struct emp {
    int empNo;
    double empSalary;
};

struct task {
    // char = 1bytes
    // int = 4bytes
    // double = 8 bytes
    int task[6];
    char taskDetails;
};
int main() {
    emp p;
    int empNoSize = sizeof(p.empNo);
    int empSalarySize = sizeof(p.empSalary);

    cout << "Employee" << endl;
    cout << "empNo : " << empNoSize << endl;
    cout << "empSalary: " << empSalarySize << endl;
    task t;
    int taskSz = sizeof(t.task);
    int taskDtSz = sizeof(t.taskDetails);
    cout << "Emp Task: " << taskSz << endl;
    cout << "Task: " << taskDtSz << endl;
    return 0 ;
}