// Coded By Eric Buchanan
// 4/23/22

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;




class Course {

public:
	string course_number;
	string title;
	vector<string> prereqs;

	Course(string num, string ttl) : course_number(num), title(ttl) {}
};

vector<Course> readInput(string file)
{
	vector<Course> courses;
	ifstream inFile(file); // Use the 'file' parameter to open the file

	if (inFile.is_open()) {
		string line;
		while (getline(inFile, line)) {
			string course_number, title, prereqs;
			int firstComma = line.find_first_of(",");
			int secondComma = line.find_first_of(",", firstComma + 1);

			course_number = line.substr(0, firstComma);
			title = line.substr(firstComma + 1, secondComma - firstComma - 1);
			prereqs = line.substr(secondComma + 1);

			Course course(course_number, title); // Create a 'course' object instead of overwriting 'courses'

			int commaPos = prereqs.find_first_of(',');
			while (commaPos != string::npos) { // Use 'string::npos' instead of '-1'
				string prereq = prereqs.substr(0, commaPos);
				course.prereqs.push_back(prereq);
				prereqs = prereqs.substr(commaPos + 1);
				commaPos = prereqs.find_first_of(',');
			}
			if (!prereqs.empty()) {
				course.prereqs.push_back(prereqs);
			}

			courses.push_back(course); // Add the 'course' object to the 'courses' vector
		}
	}
	else {
		cout << "Error opening file " << file << endl;
	}
	inFile.close();
	return courses;

}

// Function to print course information
void printCourseInfo(vector<Course> courses, string courseNumber)
{
	const Course* course = nullptr;
	for (const Course& c : courses) {
		if (c.course_number == courseNumber) {
			course = &c;
			break;
		}
	}

	if (course != nullptr) {
		cout << "Course Title: " << course->title << endl;
		if (!course->prereqs.empty()) {
			cout << "Prerequisites: ";
			for (const string& prereq : course->prereqs) {
				cout << prereq << " ";
			}
			cout << endl;
		}
	}
	else {
		cout << "Course not found." << endl;
	}
}
void printCourseList(vector<Course> courses) {
	// Create a copy of the courses vector to sort without modifying the original
	vector<Course> sorted_courses = courses;

	sort(sorted_courses.begin(), sorted_courses.end(), [](const Course& a, const Course& b) {
		return a.course_number < b.course_number;
		});

	cout << "Course List:" << endl;
	for (const Course& course : sorted_courses) {
		cout << course.course_number << " " << course.title << endl;
	}
}

void displayMenu(vector<Course>& courses) // Pass 'courses' as a reference
{
	int input = 0;
	string search;
	while (input != 9) {

		cout << "1. Load Data Structure." << endl;
		cout << "2. Print Course List." << endl;
		cout << "3. Print Course." << endl;
		cout << "9. Exit" << endl;

		cout << "What would you like to do?" << endl;
		cin >> input;

		if (input == 1) {
			courses = readInput("ABCU_Advising_Program_Input.txt"); // Update 'courses' with the result of readInput
		}
		else if (input == 2) {
			printCourseList(courses);
		}
		else if (input == 3) {
			cout << "What course do you want to know about?";
			cin >> search;
			printCourseInfo(courses, search);
		}
		else if (input == 9) {
			break;
		}
		else {
			cout << input << " is not a valid option." << endl;
			cout << endl;
		}
	}
}

int main()
{

	vector<Course> courses;
	cout <<  "Welcome to the course planner." << endl ;
	displayMenu(courses);
	return 0;

}
