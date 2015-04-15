#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h> 

using namespace std;

void swap(int *arr, int x, int y){
	int temp = arr[x];
	arr[x] = arr[y];
	arr[y] = temp; 
}

void insertion(int *arr, int size, int &swapCount, int &compCount) {
	for (int i = 1; i < size; i++){
		for (int j = i; j > 0; j--){
			if (arr[j] < arr[j-1]){
				swap(arr, j, j-1);	
				swapCount++;
			}
			compCount++;
		}
	}
}

void bubble(int *arr, int size, int &swapCount, int &compCount) {
	for (int i = 0; i < size - 1; i++){
		for (int j = size-1; j > i; j--){
			if (arr[j] < arr[j-1]){
				swap(arr, j, j-1);
				swapCount++;
			}
			compCount++;
		}
	}
}

void selection(int *arr, int size, int &swapCount, int &compCount) { 
	for (int i = 0; i < size-1; i++) { 
		int lowindex = i; 
		for (int j = size-1; j > i; j--){ 
			if (arr[j] < arr[lowindex])
				lowindex = j; 
			compCount++;
		}
		swap(arr, i, lowindex);
		swapCount++;
	}
}

void mergesort(int arr[], int temp[], int left, int right) {
	if (left == right) return; 
	int mid = (left+right)/2;
	mergesort(arr, temp, left, mid);
	mergesort(arr, temp, mid+1, right);
	
	// Copy subarray to temp
	for(int i=left; i<=right; i++) 
		temp[i] = arr[i];
	
	// Do the merge operation back to arr
	int i1 = left; int i2 = mid + 1;
	for(int curr = left; curr <= right; curr++) {
		if (i1 == mid + 1) 		// Left sublist exhausted
			arr[curr] = temp[i2++];
		else if (i2 > right) 	// Right sublist exhausted
			arr[curr] = temp[i1++];
		else if (temp[i1] < temp[i2])
			arr[curr] = temp[i1++];
		else 
			arr[curr] = temp[i2++];
	}
}

inline int findpivot(int arr[], int i, int j) { return (i+j)/2; }

inline int partition(int arr[], int l, int r, int& pivot, int &swapCount, int &compCount) {
	do { // Move the bounds inward until they meet
		while (arr[++l] < pivot) compCount++; // Move l right and
		while ((l < r) && (pivot < arr[--r])) compCount++; // r left
		swap(arr, l, r); // Swap out-of-place values
		swapCount++;
	} while (l < r); // Stop when they cross
		return l; // Return first position in right partition
}

void quicksort(int arr[], int i, int j, int &swapCount, int &compCount) {
	if (j <= i) return;
	int pivotindex = findpivot(arr, i, j);
	swap(arr, pivotindex, j); 
	int k = partition(arr, i-1, j, arr[j], swapCount, compCount);
	swap(arr, k, j); 
	swapCount += 2; // Increment by two for the two different swaps taking place
	quicksort(arr, i, k-1, swapCount, compCount);
	quicksort(arr, k+1, j, swapCount, compCount);
}

void shuffle(int *arr, int size){
	for (int i = size - 1; i >= 1; i--){
		// Finding a random number that is 
		// within the boundry of 0 <= j <= i
		int j = rand() % i;
		swap(arr, i, j);
	}	
}

// Returns a pointer to an array that has 
// been dynamically allocated and intialized
// with random values from 0 to 10^i - 1
int* intialize(int i){
	int size = pow(10, i);
	int* arr = new int[size];

	for(int j = 0; j < size; j++){
		// Produces a random number from 1 to size
		arr[j] = rand() % size + 1;
	}

	return arr;
}

void viewArray(int *arr, int size){
	for (int i = 0; i < size; i++){
		cout << arr[i] << " ";
	}
	cout << endl;
}

int main(){
	// Output for the swap and compares
	int output[5][16];

	// Intializing random number generator
	srand(time(NULL));
	int* array = intialize(1);
	int temp[10];
	
	int swapCount = 0;
	int compCount = 0;

	cout << "Insertion" << endl;
	shuffle(array, 10);
	viewArray(array, 10);
	insertion(array, 10, swapCount, compCount);
	viewArray(array, 10);

	cout << "swaps: " << swapCount << endl;
	cout << "comps: " << compCount << endl;
	swapCount = 0; compCount = 0;


	cout << "Bubble" << endl;
	shuffle(array, 10);
	viewArray(array, 10);
	bubble(array, 10, swapCount, compCount);
	viewArray(array, 10);

	cout << "swaps: " << swapCount << endl;
	cout << "comps: " << compCount << endl;
	swapCount = 0; compCount = 0;

	cout << "Selection" << endl;
	shuffle(array, 10);
	viewArray(array, 10);
	selection(array, 10, swapCount, compCount);
	viewArray(array, 10);

	cout << "swaps: " << swapCount << endl;
	cout << "comps: " << compCount << endl;
	swapCount = 0; compCount = 0;

	cout << "Merge sort" << endl;
	shuffle(array, 10);
	viewArray(array, 10);
	mergesort(array, temp, 0, 9);
	viewArray(array, 10);

	cout << "Quick sort" << endl;
	shuffle(array, 10);
	viewArray(array, 10);
	quicksort(array, 0, 9, swapCount, compCount);
	viewArray(array, 10);

	cout << "swaps: " << swapCount << endl;
	cout << "comps: " << compCount << endl;
	swapCount = 0; compCount = 0;

	return 0;
}