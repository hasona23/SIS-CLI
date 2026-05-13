#include "CourseManagement.h"
#include <fstream>
#include <iostream>
#include <string>
#include "Utils.h"
#include "GradesManagement.h"
using namespace std;



static void PrintCourse(const Course* s) {
	std::cout << "========================\n";
	std::cout << "ID           : " << s->Id << "\n";
	std::cout << "Title         : " << s->Title << "\n";
	std::cout << "Credit Hours  : " << s->CreditHours << "\n";
	std::cout << "========================\n";
}


static void SortCoursesById(Course* courses, int amount)
{
	bool hasSwapped = true;
	while (hasSwapped)
	{
		hasSwapped = false;
		for (int j = 0; j < amount - 1; j++)
		{
			if (strcmp(courses[j].Id, courses[j + 1].Id) > 0)
			{
				Course temp = courses[j];
				courses[j] = courses[j + 1];
				courses[j + 1] = temp;
				hasSwapped = true;
			}
		}
	}
}
static void SortCoursesByTitle(Course* courses, int amount)
{
	bool hasSwapped = true;
	while (hasSwapped)
	{
		hasSwapped = false;
		for (int j = 0; j < amount - 1; j++)
		{

			if (strcmp(courses[j].Title, courses[j + 1].Title) > 0)
			{
				Course temp = courses[j];
				courses[j] = courses[j + 1];
				courses[j + 1] = temp;
				hasSwapped = true;
			}
		}
	}
}
static void SortCoursesByCreditHrs(Course* courses, int amount)
{
	bool hasSwapped = true;
	while (hasSwapped)
	{

		hasSwapped = false;
		for (int j = 0; j < amount - 1; j++)
		{

			if (courses[j].CreditHours < courses[j + 1].CreditHours)
			{
				Course temp = courses[j];
				courses[j] = courses[j + 1];
				courses[j + 1] = temp;
				hasSwapped = true;
			}
		}
	}
}





void CreateCoursesFile()
{
	std::fstream file;
	//creates file
	file.open(COURSES_FILE_PATH, std::ios::app);

	if (!file.is_open())
	{
		std::cout << "FAILED TO CREATE COURSES FILE\n";
		PressEnterPause();
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
int ValidateCourseId(char* id) { //3 letters, 3 digits, unique
	RemoveSpaces(id);




	//will check by searching through the courses file, so I will need a search course func 
	//or use strcmp with other course names in the courses file which are marked by a specific line pattern in the courses.txt


	if (strlen(id) != 6) return -1;

	for (int i = 0; i < 3; i++) {
		if (id[i] >= 'a' && id[i] <= 'z') {
			id[i] -= 32;

		}
		if (id[i] < 'A' || id[i] > 'Z') return -2;
	}
	for (int i = 3; id[i] != '\0'; i++) {
		if (id[i] < '0' || id[i] > '9')return -3;
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
				if (strcmp(buffer, id) == 0) return -4;
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
	while (ValidateCourseId(course.Id) != 0) {
		switch (ValidateCourseId(course.Id)) {
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


void DeleteCourse(int index, Course* courses, int* amount) {

	if (index >= *amount)return;


	else {
		for (int i = index; i < (*amount - 1); i++)
			courses[i] = courses[i + 1];
		*amount = *amount - 1;
	}

}
void DeleteCourseMenu(Course* courses, int* amount)
{
	if (*amount == 0) {
		cout << endl << "No courses registered. Press ENTER to continue... ";


		cin.get();


		return;
	}
	for (int i = 0; i < *amount; i++)
	{
		std::cout << (i + 1) << ") " << courses[i].Id << " - " << courses[i].Title << '\n';
	}
	char inputId[256] = "";
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
		if (strcmp(tempCourse.Id, "BACK") == 0)
			return;
		if (!ValidateCourseId(tempCourse.Id))
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
	cout << endl << "Are you sure you want to delete this course? (Y/N)";
	if (tolower(cin.get()) == 'y') { //confirmation message
		int gradesCount = 0;
		Grade* grades = LoadGrades(&gradesCount);
		DeleteGradeByCourseId(grades,courses[removeIndex].Id,&gradesCount);
		SaveGrades(grades, gradesCount);
		delete[] grades;
		DeleteCourse(removeIndex, courses, amount);

	}
	else {
		return;
	}


}

void ListCourses(Course* courses, int amount)
{

	if (amount == 0) {
		cout << endl << "No courses registered. Press ENTER to continue... ";


		cin.get();


		return;
	}
	DisplayTitle("Course List");
	std::cout << "Choose Sorting Method: \n";
	std::cout << "1) Id\n";
	std::cout << "2) Title (A-Z) \n";
	std::cout << "3) Credit Hours\n";
	int choice = 0;
	do
	{
		std::cout << "Choice: ";
		std::cin >> choice;
	} while (choice < 1 || choice > 3);
	switch (choice)
	{
	case 2:
		SortCoursesByTitle(courses, amount);
		break;
	case 3:
		SortCoursesByCreditHrs(courses, amount);
		break;

	default:
		SortCoursesById(courses, amount);
		break;
	}
	for (int i = 0; i < amount; i++)
	{
		PrintCourse(&courses[i]);
	}
	PressEnterPause();
}

void UpdateCourse(Course* course, const char* Title, int CreditHours)
{


	strncpy_s(course->Title, Title, MAX_COURSE_TITLE_LENGTH);
	course->Title[MAX_COURSE_TITLE_LENGTH] = '\0';


	course[0].CreditHours = CreditHours;



}







void UpdateCourseMenu(Course* courses, int amount)
{
	if (amount == 0) {
		cout << endl << "No courses registered. Press ENTER to continue....";
		cin.ignore();
		cin.get();
		return;
	}
	for (int i = 0; i < amount; i++)
	{
		std::cout << (i + 1) << ") " << courses[i].Id << " - " << courses[i].Title << '\n';
	}
	int index = -1;
	char inputId[256] = "";
	bool wasFound = false;

	do
	{
		Course tempCourseSearch;
		std::cout << "Input ID (back to exit): ";
		cin.getline(inputId, 256);
		RemoveSpaces(inputId);
		toUpper(inputId);

		strcpy_s(tempCourseSearch.Id, inputId);
		if (strcmp(tempCourseSearch.Id, "BACK") == 0)
			return;
		if (!ValidateCourseId(tempCourseSearch.Id))
		{
			std::cout << "Invalid input Id\n";
			continue;
		}
		wasFound = false;
		for (int i = 0; i < amount; i++)
		{
			if (strcmp(courses[i].Id, tempCourseSearch.Id) == 0)
			{
				wasFound = true;
				index = i;
				break;
			}
		}
		if (!wasFound)
			std::cout << "Course with ID " << inputId << " was not found\n";
	} while (!wasFound);
	char newTitle[256] = "";
	int newCredit = 0;

	Course tempcourse;


	std::cout << "Enter new title or 0 to skip: ";
	//std::cin.ignore();
	cin.getline(newTitle, 256, '\n');
	strcpy_s(tempcourse.Title, newTitle);
	while (strcmp(tempcourse.Title, "0") != 0 && !validateCourseTitle(tempcourse))
	{
		std::cout << "Invalid Title, Course title cannot be empty.\n";
		std::cout << "Enter Title: ";
		cin.getline(newTitle, 256);
		strcpy_s(tempcourse.Title, newTitle);
		if (strcmp(tempcourse.Title, "back") == 0)
		{
			std::cout << "Going back to menu...\n";
			PressEnterPause();
			return;
		}
	}
	if (strcmp(newTitle, "0") == 0)
		strcpy_s(newTitle, courses[index].Title);
	std::cin.ignore();
	std::cout << "Enter new Credit Hours or 0 to skip: ";
	std::cin >> newCredit;
	tempcourse.CreditHours = newCredit;

	while (newCredit != 0 && !validateCreditHrs(tempcourse))
	{
		std::cout << "Invalid Credit Hours [" << newCredit << "]. Credit hours must be 1,2,3, or 4. You may enter -1 to go back or ENTER to continue\n";
		std::cout << "Enter Credit Hours: ";
		std::cin >> newCredit;
		tempcourse.CreditHours = newCredit;
		if (newCredit == -1)
		{
			std::cout << "Going back to menu...\n";
			PressEnterPause();
			return;
		}
	}
	if (newCredit == 0)
		newCredit = courses[index].CreditHours;


	UpdateCourse(&courses[index], newTitle, newCredit);
}

