#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int getMax(const vector<int>& arr) {
    if (arr.empty()) return 0;
    return *max_element(arr.begin(), arr.end());
}

void countingSortByDigit(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n);
    vector<int> count(10, 0); 

    for (int x : arr) {
        count[(x / exp) % 10]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    arr = output;
}

void radixSort(vector<int>& arr) {
    if (arr.empty()) return;

    int m = getMax(arr);

    for (int exp = 1; m / exp > 0; exp *= 10) {
        countingSortByDigit(arr, exp);
    }
}

void printVector(const vector<int>& arr) {
    for (int val : arr) {
        cout << val << " ";
    }
    cout << "\n";
}

int main() {
    vector<int> data = {170, 45, 75, 90, 802, 24, 2, 66, 4000, 311};

    cout << "Original array: ";
    printVector(data);

    radixSort(data);

    cout << "Sorted array:   ";
    printVector(data);

    return 0;
}