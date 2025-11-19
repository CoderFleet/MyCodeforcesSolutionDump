#include <iostream>
#include <vector>
#include <algorithm> // Not strictly needed, but good practice

using namespace std;

// --- 1. The Merge Function ---
// Merges two sorted subarrays into a single sorted array.
void merge(vector<int>& arr, int left, int mid, int right) {
    // Determine the size of the two halves
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays (vectors in this case)
    vector<int> L(n1);
    vector<int> R(n2);

    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    // Merge the temp arrays back into arr[left..right]
    int i = 0; // Initial index of first subarray
    int j = 0; // Initial index of second subarray
    int k = left; // Initial index of merged subarray

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// --- 2. The Merge Sort Function ---
// Divides the array and calls the merge function.
void mergeSort(vector<int>& arr, int left, int right) {
    
    if(left < right) {
        // Find the middle point
        int mid = left + (right - left) / 2; // Prevents overflow for very large l and r

        // Recursively sort the first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}