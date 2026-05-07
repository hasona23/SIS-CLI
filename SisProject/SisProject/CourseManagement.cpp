#include "CourseManagement.h"
#include <fstream>
#include <iostream>
#include <string>


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

void WriteCourseToFile(const Course* course,std::ofstream& file)
{
	file << "[----]\n";
	file << course->ID << '\n';
	file << course->Title << '\n';
	file << course->CreditHours<<'\n';
	file << "[----]\n";
}

void SaveCourses(const Course* courses, int amount)
{
	std::ofstream file;
	file.open(COURSES_FILE_PATH,std::ios::trunc);
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
	std::ifstream file;
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

				strncpy_s(courses[i].ID, buffer, COURSE_ID_LENGTH);
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