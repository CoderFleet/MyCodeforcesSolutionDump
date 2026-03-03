#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include<iostream>
using namespace std;

int main() {
    pid_t pid1 = fork();
    if (pid1 < 0) perror("First fork failed");
    
    if (pid1 && (!fork())) {
        if ((!fork()) || fork()) {
            fork();
            fork();
        }
    }
    // Added \n to force the buffer to flush
    cout << "Hi!" << endl;
    return 0;
}