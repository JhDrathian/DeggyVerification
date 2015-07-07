#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <ctime>
using namespace std;

int find_shift(int input_hour);

int main()
{
	//char input_string[100];
	string input_string;
	string input_time;
	string AM = "AM";
	string PM = "PM";

	int input_sec = 00;
	int input_min = 00;
	int input_hour = 00;

	int day_var = 1;
	int shift_var = 1;
	int current_shift = 0;
	string output_file_name;

	fstream input_file;
	ofstream output_file;

	input_file.open("C:/Users/Jason/Documents/Visual Studio 2013/Projects/Deggy Verification/Collect.txt");
	cout << "Beginning File Splitting\n";
	//getline(input_file, input_string);
	while (getline(input_file, input_string))
	{
		vector <string> data_vector;
		stringstream s_stream(input_string);
		string stream_string_holder;
		while (s_stream >> stream_string_holder)
		{
			data_vector.push_back(stream_string_holder);
			if (s_stream.peek() == ';')
				s_stream.ignore();
		}
		input_time = data_vector[3];
	
		string time_of_day;
		time_of_day = data_vector[4].substr(0, 2);
		vector <int> data_vector2;
		stringstream s_stream2(input_time);
		int stream_string_holder_2;
		while (s_stream2 >> stream_string_holder_2)
		{
			data_vector2.push_back(stream_string_holder_2);
			if (s_stream2.peek() == ':')
				s_stream2.ignore();
		}
		input_hour = data_vector2[0];
		
		if (time_of_day.compare(PM) == 0)
			if (input_hour != 12)
			{
				input_hour += 12;
			}
			else
			{
				input_hour = input_hour;
			}
		else if (time_of_day.compare(AM) == 0)
			if (input_hour == 12)
			{
				input_hour -= 12;
			}
			else
				input_hour = input_hour;
				
		current_shift = find_shift(input_hour);
		output_file_name = to_string(day_var) + "-" + to_string(shift_var) + ".txt";
		if (!output_file.is_open())
		{
			if (shift_var == 1)
			{
				if (current_shift == shift_var)
				{
					output_file_name = to_string(day_var) + "-" + to_string(shift_var) + ".txt";
					ofstream output_file(output_file_name.c_str(), ios::out | ios::app);
					output_file << input_string << endl;
				}
				else
				{
					cout << "Finished shift: " << day_var << "-" << shift_var << endl;
					output_file.close();
					shift_var = 2;
					output_file_name = to_string(day_var) + "-" + to_string(shift_var) + ".txt";
					ofstream output_file(output_file_name.c_str(), ios::out | ios::app);
					output_file << input_string << endl;
				}
			}
			else if (shift_var == 2)
			{
				if (current_shift == shift_var)
				{
					output_file_name = to_string(day_var) + "-" + to_string(shift_var) + ".txt";
					ofstream output_file(output_file_name.c_str(), ios::out | ios::app);
					output_file << input_string << endl;
				}
				else
				{
					cout << "Finished shift: " << day_var << "-" << shift_var << endl;
					output_file.close();
					shift_var = 3;
					output_file_name = to_string(day_var) + "-" + to_string(shift_var) + ".txt";
					ofstream output_file(output_file_name.c_str(), ios::out | ios::app);
					output_file << input_string << endl;
				}
			}
			else if (shift_var == 3)
			{
				if (current_shift == shift_var)
				{
					output_file_name = to_string(day_var) + "-" + to_string(shift_var) + ".txt";
					ofstream output_file(output_file_name.c_str(), ios::out | ios::app);
					output_file << input_string << endl;
				}
				else
				{
					cout << "Finished shift: " << day_var << "-" << shift_var << endl;
					output_file.close();
					shift_var = 1;
					day_var += 1;
					output_file_name = to_string(day_var) + "-" + to_string(shift_var) + ".txt";
					ofstream output_file(output_file_name.c_str(), ios::out | ios::app);
					output_file << input_string << endl;
				}
			}
		}	
	}
	system("PAUSE");
}


int find_shift(int input_hour)
{
	int first_shift_start_hour = 7;
	int first_shift_end_hour = 14;
	int second_shift_start_hour = 15;
	int second_shift_end_hour = 22;
	int third_shift_start_hour_1 = 23;
	int third_shift_end_hour_1 = 23;
	int third_shift_start_hour_2 = 0;
	int third_shift_end_hour_2 = 6;
	
	
	

	int hour_query = input_hour;
	//int min_query = input_min;
	//int sec_query = input_sec;

	if (hour_query >= first_shift_start_hour && hour_query <= first_shift_end_hour)
	{
		//cout << "Hour_query is in first shift\n";
		//system("PAUSE");
		return 1;
	}
	else if (hour_query >= second_shift_start_hour && hour_query <= second_shift_end_hour)
	{
		//cout << "Hour_query is in second shift\n";
		//system("PAUSE");
		return 2;
	}
	else if (hour_query == third_shift_start_hour_1 || (hour_query >= third_shift_start_hour_2 && hour_query <= third_shift_end_hour_2))
	{
		//cout << "Hour_query is in third shift\n";
		//system("PAUSE");
		return 3;
	}
	else
		//cout << "Did not find compatible shift\n";
		//system("PAUSE");
		return 0;
}
