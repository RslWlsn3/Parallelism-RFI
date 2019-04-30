# Parallelism-RFI
Note - we may need to create a new repo since I'm using VS2015. 

call test_merge_string_serial() to test merge sort using name and a date value (# of days between date given and current date). To get a date value call get_date_value(month, day, year). 

call create_random_nums(size) with size being # of random numbers to be generated. I can only get to a 100 million before it breaks. 

calling test_merge_int_serial() creates 100 mil random ints and then sorts them 


code form Nathan to parse file:

 std::vector <csv_data> csvParser(const std::string fileName) {
    //local vars
    std::string temp;

    //create arr
    std::vector <csv_data> data;

    std::fstream file;
    file.open(fileName);

    if (file.is_open()) {
        //read from the file

        //ignore the first line
        file.ignore(200, '\n');

        while (!file.eof()) {
			//create new csv_data obj
			csv_data d;

			//trash
			getline(file, temp, '"');

			//get value
			getline(file, temp, '"');
			d.setName(temp);

			//trash comma
			getline(file, temp, ',');

			//get value
			getline(file, temp, ',');
			d.setDonorStatus(temp);

			//trash
			getline(file, temp, ',');
			if (temp.empty()) {
				getline(file, temp, '\n');
			} else {
				//parse date
				temp.erase(0, 1);
				d.setGradDate(temp);

				getline(file, temp, '"');
				d.setGradDate(d.getGradDate().toString() + "," + temp);

				//trash
				getline(file, temp, ',');
				//get inst
				getline(file, temp, '\n');
				d.setInstitution(temp);
			}

			data.push_back(d);
        }
	} else {
        std::cout << "\nThere was an error opening " << fileName;
    }

	return data;
}
