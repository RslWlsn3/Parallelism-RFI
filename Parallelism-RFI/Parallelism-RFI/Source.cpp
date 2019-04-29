//RFI
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<thread>
#include<string>
#include<ctime>   
#include<cstdlib> 
#include<climits> 
using namespace std;


//creates size amount of random integers in the range of 1 to max size of an int
int* create_random_nums(int size)
{
	srand(time(NULL));
	int * randNums;
	randNums = new int [size];

	for (int i = 0; i < size; i++)
	{
		int x = rand() % INT_MAX;  
		randNums[i] = x;
	}	
	return randNums;
}

void PrintArray(int *array, int n) {
	for (int i = 0; i < n; ++i)
		cout << array[i] << " " << flush<<endl;
	cout << endl;
}

//TO DO: sort by grad's date if they have the same name, dateArray has #days from current day(not currently being used)
//Function 1 of 2 for serial merge sort using strings
void serialMergeString(string namesArray[], int dateArray[], int low, int mid, int high, int size)
{
	int i = low, j = mid + 1, k = low;
	string *Temp;
	Temp = new string[size];

	while (i <= mid && j <= high)
	{
		if (namesArray[i] < namesArray[j])
		{
			Temp[k].assign(namesArray[i]);
			i++;
		}
		else
		{
			Temp[k].assign(namesArray[j]);
			j++;
		}
		k++;
	}
	if (i > mid)
	{
		for (int h = j; h <= high; h++)
		{
			Temp[k].assign(namesArray[h]);
			k++;
		}
	}
	else
		for (int h = i; h <= mid; h++)
		{
			Temp[k].assign(namesArray[h]);
			k++;
		}
	for (int i = low; i <= high; i++)
	{
		namesArray[i].assign(Temp[i]);
	}
}

//function 2 of 2 for serial merge sort using strings
void serialMergeSortString(string namesArray[], int dateArray[], int low, int high, int size)
{
	int mid = 0;
	
	if (low < high)
	{
		mid = ((low + high) / 2);
		serialMergeSortString(namesArray, dateArray, low, mid, size);
		serialMergeSortString(namesArray, dateArray, mid + 1, high, size);
		serialMergeString(namesArray, dateArray,  low, mid, high, size);
	}
}

//function 1 of 2 for serial merge sort using ints
void serialMergeint(int numArray[], int low, int  mid, int high) {
	int *temp = new int[high - low + 1];//temporary merger array
	int i = low, j = mid + 1;//i is for left-hand,j is for right-hand
	int k = 0;//k is for the temporary array
	while (i <= mid && j <= high) {
		if (numArray[i] <= numArray[j])
			temp[k++] = numArray[i++];
		else
			temp[k++] = numArray[j++];
	}
	//rest elements of left-half
	while (i <= mid)
		temp[k++] = numArray[i++];
	//rest elements of right-half
	while (j <= high)
		temp[k++] = numArray[j++];
	//copy the mergered temporary array to the original array
	for (k = 0, i = low; i <= high; ++i, ++k)
		numArray[i] = temp[k];

	delete[]temp;
}

//function 2 of 2 for serial merge sort using ints
void serialMergeSortint(int numArray[], int low, int high, int size)
{
	int mid = 0;
	if (low < high)
	{
		mid = ((low + high) / 2);
		serialMergeSortint(numArray, low, mid, size);
		serialMergeSortint(numArray, mid + 1, high, size);
		serialMergeint(numArray, low, mid, high);
	}
}

//creates 1 billion (currently only hundred million) random ints and then calls serialMergeSortint to sort them serialy or 
void test_merge_int_serial()
{
	//code to test merge sort with ints
	int size = 100000000;	//crashes when I add another 0
	int* arr = create_random_nums(size);

	serialMergeSortint(arr, 0, size - 1, size);

	//print out results
	for (int i = 0; i < size; i++)
		cout << arr[i] << endl;
}

void test_merge_string_serial()
{
	//code to test merge sort with strings
	int size= 3;
	string *nameArray;
	nameArray = new string[size]{ "John", "Connor", "bill" };
	int *dateArray;
	dateArray = new int[size] {1043, 356, 488};

	serialMergeSortString(nameArray, dateArray, 0, size - 1, size);
	//print out results
	for (int i = 0; i < size; i++)
		cout << nameArray[i] << endl;
}

int days_in_month(int year, int month)
{
	if (month == 4 || month == 6 || month == 9 || month == 11)
		return 30;

	else if (month == 2)
	{
		bool leapyear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

		if (!leapyear)
			return 28;
		else
			return 29;
	}
	else
		return 31;
}

//TO DO: calculate current date only once
//calclates and returns the number of days it has been since a date to now
int get_date_value(int month, int day, int year)
{
	time_t tt;
	time(&tt);
	tm TM = *localtime(&tt);

	int current_year = TM.tm_year + 1900;
	int current_month = TM.tm_mon + 1;
	int current_day = TM.tm_mday;
	
	int date_value = 0;
	date_value += (current_year - year) * 365;
	date_value += (current_month - month) * days_in_month(year, month);
	date_value += (current_day - day);
	return date_value;

}

int main()
{	
	//test_merge_int_serial();
	//cout << get_date_value(10, 4, 1964);
	test_merge_string_serial();
	
}