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

void serialMerge(string currentArray[], int low, int mid, int high, int size)
{
	int i = low, j = mid + 1, k = low;
	string *Temp;
	Temp = new string[size];

	while (i <= mid && j <= high)
	{
		if (currentArray[i] < currentArray[j])
		{
			Temp[k].assign(currentArray[i]);
			i++;
		}
		else
		{
			Temp[k].assign(currentArray[j]);
			j++;
		}
		k++;
	}
	if (i > mid)
	{
		for (int h = j; h <= high; h++)
		{
			Temp[k].assign(currentArray[h]);
			k++;
		}
	}
	else
		for (int h = i; h <= mid; h++)
		{
			Temp[k].assign(currentArray[h]);
			k++;
		}
	for (int i = low; i <= high; i++)
	{
		currentArray[i].assign(Temp[i]);
	}
}

void serialMergeSort(string currentArray[], int low, int high, int size)
{
	int mid = 0;
	if (low < high)
	{
		mid = ((low + high) / 2);
		serialMergeSort(currentArray, low, mid, size);
		serialMergeSort(currentArray, mid + 1, high, size);
		serialMerge(currentArray, low, mid, high, size);
	}
}

void serialMergeint(int arr[], int lo, int  mi, int hi) {
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
void serialMergeSortint(int currentArray[], int low, int high, int size)
{
	int mid = 0;
	if (low < high)
	{
		mid = ((low + high) / 2);
		serialMergeSortint(currentArray, low, mid, size);
		serialMergeSortint(currentArray, mid + 1, high, size);
		serialMergeint(currentArray, low, mid, high);
	}
}

int main()
{
	//code to test merge sort with ints
	int size = 50;
	int* arr = create_random_nums(size);

	serialMergeSortint(arr, 0, size - 1, size);
	
	//code to test merge sort with strings
	/*int size= 3;	
	string *arr;
	arr = new string[size]{ "John", "Connor", "bill" };	
	

	serialMergeSort(arr, 0, size - 1, size);*/
	
	//print out results
	for (int i = 0; i < size; i++)
		cout << arr[i] << endl;
}