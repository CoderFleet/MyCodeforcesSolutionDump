#include <bits/stdc++.h>
using namespace std;

int main() {
	// Read the number of steps the robot will take
	int n;
	cin >> n;

	// Calculate half of the steps
	int k = n / 2;

	// Variable to store the number of different possible locations
	long long int ans = 0;

	// If n is even, calculate the number of locations using (k+1)*(k+1)
	if (n % 2 == 0) {
		ans = (k + 1) * (k + 1);
	} else {
		// If n is odd, calculate the number of locations using 2*(k+1)*(k+2)
		ans = 2 * (k + 1) * (k + 2);
	}

	// Output the result
	cout << ans << endl;

	return 0;
}

// Time Complexity (TC): O(1)
// Space Complexity (SC): O(1)