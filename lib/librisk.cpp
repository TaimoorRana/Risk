#include <iostream>
using namespace std;

void librisk_print_todo() {
	cout << "TODO\n";
    int s = 5;
    int *p = &s;
    *p = 45;
    cout << p << "test";
}
