#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void countingSort(vector<int>& arr) {
    if (arr.empty()) {
        return;
    }

    int max_val = *max_element(arr.begin(), arr.end());
    int n = arr.size();
    
    vector<int> output(n);
    vector<int> count(max_val + 1, 0); 
    
    for (int x : arr) {
        count[x]++;
    }
    
    for (int i = 1; i <= max_val; i++) {
        count[i] += count[i - 1];
    }
    
    for (int i = n - 1; i >= 0; i--) {
        int element = arr[i];
        output[count[element] - 1] = element;
        count[element]--;
    }
    
    arr = output;
}

void printVector(const vector<int>& arr) {
    for (int val : arr) {
        cout << val << " ";
    }
    cout << "\n";
}

int main() {
    vector<int> data = {9, 1, 5, 2, 7, 1, 9, 3};

    cout << "Original array: ";
    printVector(data);

    countingSort(data);

    cout << "Sorted array:   ";
    printVector(data);

    return 0;
}