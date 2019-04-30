//RFI
#define _CRT_SECURE_NO_WARNINGS
const int CSV_SIZE = 25038;
#include<iostream>
#include<thread>
#include<string>
#include<ctime>   
#include<cstdlib> 
#include<climits> 
#include<fstream>
using namespace std;

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
	string *Temp_name;
	Temp_name = new string[size];
	int *Temp_date;
	Temp_date = new int[size];

	while (i <= mid && j <= high)
	{
		if (csv_data_array[i].name < csv_data_array[j].name)
		{
			Temp_name[k].assign(csv_data_array[i].name);
			Temp_date[k] = csv_data_array[i].date_value;
			i++;
		}
		else if (csv_data_array[i].name == csv_data_array[j].name)	//names are the same, use date array
		{
			if (csv_data_array[i] < csv_data_array[j])
			{
				Temp_name[k].assign(csv_data_array[i].name);
				Temp_date[k] = csv_data_array[i].date_value;
				i++;
			}
			else
			{
				Temp_name[k].assign(csv_data_array[j].name);
				Temp_date[k] = csv_data_array[j].date_value;
				j++;
			}
		}
		else
		{
			Temp_name[k].assign(csv_data_array[j].name);
			Temp_date[k] = csv_data_array[j].date_value;
			j++;
		}
		k++;
	}
	if (i > mid)
	{
		for (int h = j; h <= high; h++)
		{
			Temp_name[k].assign(csv_data_array[h].name);
			Temp_date[k] = csv_data_array[h].date_value;
			k++;
		}
	}
	else
		for (int h = i; h <= mid; h++)
		{
			Temp_name[k].assign(csv_data_array[h].name);
			Temp_date[k] = csv_data_array[h].date_value;
			k++;
		}
	for (int i = low; i <= high; i++)
	{
		csv_data_array[i].name.assign(Temp_name[i]);
		csv_data_array[i].date_value = Temp_date[i];
	}
}

//function 1 of 2 for serial merge sort using strings
void serialMergeSortString(string namesArray[], int dateArray[], int low, int high, int size)
{
	int mid = 0;
	
	if (low < high)
	{
		mid = ((low + high) / 2);
		serialMergeSortString(namesArray, dateArray, low, mid, size);
		serialMergeSortString(namesArray, dateArray, mid + 1, high, size);		//might enter threads here
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
	nameArray = new string[size]{ "connor", "ann", "connor" }; //need to make all inputs lower or upercase
	int *dateArray;
	dateArray = new int[size] {1043, 456, 388};

	serialMergeSortString(nameArray, dateArray, 0, size - 1, size);
	//print out results
	for (int i = 0; i < size; i++)
	{
		cout << nameArray[i] << "\n date value(# days from current):"<< dateArray[i] << endl;
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

	return alumni;

}

int main(int argc, char*argv[])
{	
	//test_merge_int_serial();
	//cout << get_date_value(10, 4, 1964);
	//test_merge_string_serial();	
	csv_data* data;
	data = readCSV(argv[1]);
}