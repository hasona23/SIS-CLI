#include "CourseManagement.h"
#include <fstream>
#include <iostream>
#include <string>
#include "Utils.h"
using namespace std;




void CreateCoursesFile()
{
	std::fstream file;
	//creates file
	file.open(COURSES_FILE_PATH, std::ios::app);

	if (!file.is_open())
	{
		std::cout << "FAILED TO CREATE COURSES FILE\n";
		std::cout << "Press enter to exit...";
		std::cin.get();
		std::exit(1);
	}

}

void WriteCourseToFile(const Course* course, std::ofstream& file)
{
	file << "[----]\n";
	file << course->Id << '\n';
	file << course->Title << '\n';
	file << course->CreditHours << '\n';
	file << "[----]\n";
}

void SaveCourses(const Course* courses, int amount)
{
	std::ofstream file;
	file.open(COURSES_FILE_PATH, std::ios::trunc);
	if (file.is_open())
	{
		for (int i = 0; i < amount; i++)
			WriteCourseToFile(&courses[i], file);
		file.close();
	}
	else
	{
		std::cout << "Failed to open file. press enter to continue";
		std::cin.get();
	}
}
void AppendCourse(const Course* course)
{
	std::ofstream file;
	file.open(COURSES_FILE_PATH, std::ios::app);
	if (file.is_open()) {
		WriteCourseToFile(course, file);
	}
	else
		std::cout << "Failed to write course to file";
}
Course* LoadCourses(int* amount)
{
	fstream file;
	file.open(COURSES_FILE_PATH);

	char buffer[512 + 1];
	*amount = 0;
	bool IsReadingCourse = false;
	if (file.is_open())
	{

		int separators = 0;
		while (file.getline(buffer, 512))
		{
			if (strcmp("[----]", buffer) == 0) {
				separators++;
			}
		}
		//rests the file read pointer

		//seperators are double the amout of students
		separators /= 2;
		*amount = separators;
		Course* courses = new Course[*amount];
		int i = 0;
		file.clear();
		file.seekg(0, std::ios::beg);
		while (file.getline(buffer, 512))
		{


			if (strcmp(buffer, "[----]") == 0)
			{
				IsReadingCourse = !IsReadingCourse;
			}
			if (IsReadingCourse)
			{
				file.getline(buffer, 512);

				strncpy_s(courses[i].Id, buffer, COURSE_ID_LENGTH);
				//courses[i].ID[COURSE_ID_LENGTH] = '\0';
				file.getline(buffer, 512);

				strncpy_s(courses[i].Title, buffer, MAX_COURSE_TITLE_LENGTH);
				//courses[i].Title[MAX_COURSE_TITLE_LENGTH] = '\0';
				file.getline(buffer, 512);

				courses[i].CreditHours = atoi(buffer);
				i++;
			}
		}

		file.close();

		return courses;
	}
	else {
		std::cout << "Error Opening file to load\n";
		return nullptr;
	}
}




//All below this point was created by eyad, saying that to distinguish pieces of code

//receive input of courses
int validateCourseId(Course* course) { //3 letters, 3 digits, unique
	RemoveSpaces(course[0].Id);




	//will check by searching through the courses file, so I will need a search course func 
	//or use strcmp with other course names in the courses file which are marked by a specific line pattern in the courses.txt


	if (strlen(course[0].Id) != 6) return -1;

	for (int i = 0; i < 3; i++) {
		if (course[0].Id[i] >= 'a' && course[0].Id[i] <= 'z') {
			course[0].Id[i] -= 32;

		}
		if (course[0].Id[i] < 'A' || course[0].Id[i] > 'Z') return -2;
	}
	for (int i = 3; course[0].Id[i] != '\0'; i++) {
		if (course[0].Id[i] < '0' || course[0].Id[i] > '9')return -3;
	}
	fstream file;
	file.open(COURSES_FILE_PATH);
	char buffer[512 + 1];
	if (file.is_open()) {
		int separatorDist = 0;
		while (file.getline(buffer, 512)) {
			if (strcmp("[----]", buffer) == 0) separatorDist = 0;
			else separatorDist++;
			if (separatorDist == 1) {
				if (strcmp(buffer, course[0].Id) == 0) return -4;
			}
		}
	}

	return 0;
}
bool validateCourseTitle(const Course course) {

	if (strlen(course.Title) == 0)return false;
}

bool validateCreditHrs(const Course course) {
	if (course.CreditHours != 1 && course.CreditHours != 2 && course.CreditHours != 3 && course.CreditHours != 4) return false;
	return true;
}


void addCourse() {//will ultimately be called add course and then will be given to the func that writes into files
	Course course;
	std::cout << "Enter course Id: ";
	cin.getline(course.Id, 256);
	while (validateCourseId(&course) != 0) {
		switch (validateCourseId(&course)) {
		case -1: cout << "Invalid course ID length, must only be 6 characters." << endl << "Enter course ID: ";
			break;
		case -2:cout << "Invalid course ID format, must be 3 letters then 3 digits." << endl << "Enter course ID: ";
			break;
		case -3:cout << "Invalid courseId format, must be 3 letters then 3 digits." << endl << "Enter course ID: ";
			break;
		case -4: cout << "A course with this code already exists.Please try again." << endl << "Enter course ID: ";
			break;
		}cin.getline(course.Id, 256);
		cout << endl;
	}
	cout << endl << "Enter course name: ";
	cin.getline(course.Title, 256); cout << endl;
	while (!validateCourseTitle(course)) {
		cout << "Course Name cannot be empty. Please try again." << endl << "Enter course name: ";
		cin.getline(course.Title, 256);
		cout << endl;
	}
	cout << "Enter credit hrs (1 - 4): ";
	cin >> course.CreditHours;
	while (!validateCreditHrs(course)) {
		cout << "Invalid Credit Hours. Credit hours are 1,2,3,or 4" << endl << "Enter credit hrs: ";
		cin >> course.CreditHours;
		cout << endl;
	}
	AppendCourse(&course);



}


void DeleteCourse(int index, Course* courses, int* amount)
{
	if (index >= *amount)
		return;
	else {
		for (int i = index; i < (*amount - 1); i++)
			courses[i] = courses[i + 1];
		*amount = *amount - 1;
	}

}
void DeleteCourseMenu(Course* courses, int* amount)
{
	for (int i = 0; i < *amount; i++)
	{
		std::cout << (i + 1) << ") " << courses[i].Id << " - " << courses[i].Title << '\n';
	}
	char inputId[256]="";
	bool wasFound = false;
	int removeIndex = -1;
	do
	{
		Course tempCourse;
	

		std::cout << "Input ID (back to exit): ";
		cin.getline(inputId, 256);
		RemoveSpaces(inputId);
		toUpper(inputId);
		
		strcpy_s(tempCourse.Id, inputId);
		if (strcmp(tempCourse.Id,"BACK") ==0)
			return;
		if (!validateCourseId(&tempCourse))
		{
			std::cout << "Invalid input Id\n";
			continue;
		}
		wasFound = false;
		for (int i = 0; i < *amount; i++)
		{
			if (strcmp(courses[i].Id, tempCourse.Id) == 0)
			{
				wasFound = true;
				removeIndex = i;
				break;
			}
		}
		if (!wasFound)
		{
			std::cout << "Course with id " << inputId << " was not found\n";
		}
	} while (!wasFound);


	DeleteCourse(removeIndex, courses, amount);

}
