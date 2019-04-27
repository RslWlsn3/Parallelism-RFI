//RFI
#include<iostream>
#include<thread>
#include<string>
#include<ctime>   
#include<cstdlib> 
using namespace std;

int* create_random_nums(int size)
{
	srand(time(NULL));
	int * randNums;
	randNums = new int [size];

	for (int i = 0; i < size; i++)
	{
		int x = rand() % 10000;  
		randNums[i] = x;
	}
	
	return randNums;
}

void PrintArray(int *array, int n) {
	for (int i = 0; i < n; ++i)
		cout << array[i] << " " << flush<<endl;
	cout << endl;
}

void serialMerger(int arr[], int lo, int  mi, int hi) {
	int *temp = new int[hi - lo + 1];//temporary merger array
	int i = lo, j = mi + 1;//i is for left-hand,j is for right-hand
	int k = 0;//k is for the temporary array
	while (i <= mi && j <= hi) {
		if (arr[i] <= arr[j])
			temp[k++] = arr[i++];
		else
			temp[k++] = arr[j++];
	}
	//rest elements of left-half
	while (i <= mi)
		temp[k++] = arr[i++];
	//rest elements of right-half
	while (j <= hi)
		temp[k++] = arr[j++];
	//copy the mergered temporary array to the original array
	for (k = 0, i = lo; i <= hi; ++i, ++k)
		arr[i] = temp[k];

	delete[]temp;
}
void serialMergeSortHelper(int arr[], int lo, int hi) {
	int mid;
	if (lo < hi) {
		mid = (lo + hi) >> 1;
		serialMergeSortHelper(arr, lo, mid);
		serialMergeSortHelper(arr, mid + 1, hi);
		serialMerger(arr, lo, mid, hi);
	}
}
void serialMergeSort(int arr[], int arr_size) {
	serialMergeSortHelper(arr, 0, arr_size - 1);
}



int main()
{
	int size = 50;
	int* arr = create_random_nums(size);
	serialMergeSort(arr, size);
	PrintArray(arr, size);
}