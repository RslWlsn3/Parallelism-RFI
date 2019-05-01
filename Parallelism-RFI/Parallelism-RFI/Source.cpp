//RFI
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<thread>
#include<string>
#include<ctime>
#include<cstdlib>
#include<climits>
#include <vector>
#include <sstream>
#include <fstream>
#include <unordered_map>
using namespace std;

const int CSV_SIZE = 25038;



//TO DO: use this instead of namesArray and dateArray
class csv_data
{
public:
	string name;
	string donorStatus;
	string gradDate;
	int year;
	int month;
	int day;
	int date_value;
	string institution;
};

void convertGradDate(csv_data*);

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
//Function 2 of 2 for serial merge sort using strings
void serialMergeString(csv_data csv_data_array[], int low, int mid, int high, int size)
{
	int i = low, j = mid + 1, k = low;
	csv_data *Temp_array;
	Temp_array = new csv_data[size];

	while (i <= mid && j <= high)
	{
		if (csv_data_array[i].name < csv_data_array[j].name)
		{
			Temp_array[k] = csv_data_array[i];
			i++;
		}
		else if (csv_data_array[i].name == csv_data_array[j].name)	//names are the same, use date array
		{
			if (csv_data_array[i].date_value < csv_data_array[j].date_value)
			{
				Temp_array[k] = csv_data_array[i];
				i++;
			}
			else
			{
				Temp_array[k] = csv_data_array[j];
				j++;
			}
		}
		else
		{
			Temp_array[k] = csv_data_array[j];
			j++;
		}
		k++;
	}
	if (i > mid)
	{
		for (int h = j; h <= high; h++)
		{
			Temp_array[k] = csv_data_array[h];
			k++;
		}
	}
	else
		for (int h = i; h <= mid; h++)
		{
			Temp_array[k] = csv_data_array[h];
			k++;
		}
	for (int i = low; i <= high; i++)
	{
		csv_data_array[i] = Temp_array[i];
	}
}

//function 1 of 2 for serial merge sort using strings
void serialMergeSortString(csv_data csv_data_array[], int low, int high, int size)
{
	int mid = 0;

	if (low < high)
	{
		mid = ((low + high) / 2);
		serialMergeSortString(csv_data_array, low, mid, size);
		serialMergeSortString(csv_data_array, mid + 1, high, size);		//might enter threads here
		serialMergeString(csv_data_array, low, mid, high, size);
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
	int size = 3;
	csv_data data[3];
	data[0].name = "connor";
	data[1].name = "ann";
	data[2].name = "connor";
	data[0].date_value = 1239;
	data[1].date_value = 402;
	data[2].date_value = 200;

	serialMergeSortString(data, 0, size - 1, size);
	//print out results
	for (int i = 0; i < size; i++)
	{
		cout << data[i].name << data[i].date_value << endl;
	}
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
csv_data* readCSV(string fileName) {
	ifstream file;
	string temp;
	file.open(fileName);
	int i = -1;

	csv_data* alumni = new csv_data[CSV_SIZE];

	if (file.is_open()) {
		//read from the file

		//ignore the first line
		file.ignore(200, '\n');

		while (!file.eof()) {
			i++;
			//create new csv_data obj
			csv_data d;

			//trash
			getline(file, temp, '"');

			//get value
			getline(file, temp, '"');
			d.name = temp;

			//trash comma
			getline(file, temp, ',');

			//get value
			getline(file, temp, ',');
			d.donorStatus = temp;

			//trash
			getline(file, temp, ',');
			if (temp.empty()) {
				getline(file, temp, '\n');
			}
			else {
				//parse date
				temp.erase(0, 1);
				d.gradDate = temp;

				getline(file, temp, '"');
				d.gradDate = d.gradDate + "," + temp;

				//trash
				getline(file, temp, ',');
				//get inst
				getline(file, temp, '\n');
				d.institution = temp;
			}

			alumni[i] = d;
		}
	}
	else {
		std::cout << "\nThere was an error opening " << fileName;
	}
	convertGradDate(alumni);
	return alumni;

}

void convertGradDate(csv_data* data) {
	string value;

	unordered_map<string, int> MONTHS;
	MONTHS["Jan"] = 1;
	MONTHS["Feb"] = 2;
	MONTHS["Mar"] = 3;
	MONTHS["Apr"] = 4;
	MONTHS["May"] = 5;
	MONTHS["Jun"] = 6;
	MONTHS["Jul"] = 7;
	MONTHS["Aug"] = 8;
	MONTHS["Sep"] = 9;
	MONTHS["Oct"] = 10;
	MONTHS["Nov"] = 11;
	MONTHS["Dec"] = 12;


	for (int i = 0; i < CSV_SIZE; i++) {
		// Check if grad date field is populated
		if (data[i].gradDate.length() != 0) {
			// Parse grad date field to get individual numbers
			istringstream iss(data[i].gradDate);

			// Get month value
			iss >> value;

			data[i].month = MONTHS[value];

			// Get day value
			iss >> value;

			// Remove comma from end of string
			value.pop_back();
			data[i].day = stoi(value);

			// Get year value
			iss >> value;
			data[i].year = stoi(value);

			// Calculate days since graduation
			data[i].date_value = get_date_value(data[i].month, data[i].day, data[i].year);
		}

	}
}

void merge(vector<int>& vec, int start, int mid, int end)
{
	vector<int> one(vec.begin() + start, vec.begin() + mid + 1);
	vector<int> two(vec.begin() + mid + 1, vec.begin() + end + 1);

	int a = 0;
	int b = 0;
	int index = start;
	while (a < one.size() && b < two.size())
	{
		if (one[a] < two[b])
			vec[index++] = one[a++];
		else
			vec[index++] = two[b++];
	}

	// merge the left-over elements
	while (a < one.size())
		vec[index++] = one[a++];
	while (b < two.size())
		vec[index++] = two[b++];
}


void merge_sort(vector<int>& vec, int start, int end)
{
	if (start >= end)
		return;

	int mid = start + (end - start) / 2;

	// single-thread merge-sort
	merge_sort(vec, start, mid);
	merge_sort(vec, mid + 1, end);


	merge(vec, start, mid, end);
}


int driver(int numThreads)
{
	clock_t startTime = clock();

	int a[] = { 4, 2, 5, 9, 7, 1, 3, 8, 6};
	vector<int> vec(a, a + 9);

	int mid = (vec.size() - 1) / 2;

	thread first(merge_sort, std::ref(vec), 0, mid);
	thread second(merge_sort, std::ref(vec), mid + 1, (vec.size() - 1));
	first.join();
	second.join();
	merge(vec, 0, mid, (vec.size() - 1));


	for (int i = 0; i < vec.size(); i++)
		cout << vec[i] << endl;

	clock_t duration = clock() - startTime;

	cout << "Program is finished executing." << endl;
	double timeElapsed = (double)duration / CLOCKS_PER_SEC;
	cout << "Time Elapsed = " << timeElapsed << " seconds." << endl;

	return 0;
}


int main(int argc, char*argv[])
{
	driver(2);
	//test_merge_int_serial();
	//cout << get_date_value(10, 4, 1964);
	test_merge_string_serial();
	int numberOfThreads = stoi(argv[1]), numsToSort;
	bool readCSV = false, nameFirst = false;
	string CSVInput, output, sortedOutput;
	if (argv[2] == "a") {
		readCSV = true;
		if (argv[3] == "n") {
			nameFirst = true;
		}
		CSVInput = argv[4];
		output = argv[5];
	}
	else {
		numsToSort = stoi(argv[3]);
		output = argv[4];
		sortedOutput = argv[5];
	}
}
