#include "GradesManagement.h"
#include <fstream>
#include <iostream>
#include <string>


void CreateGradesFile()
{
	std::fstream file;
	//creates file
	file.open(GRADES_FILE_PATH, std::ios::app);

	if (!file.is_open())
	{
		std::cout << "FAILED TO CREATE GRADES FILE\n";
		std::cout << "Press enter to exit...";
		std::cin.get();
		std::exit(1);
	}

}

void WriteGradeToFile(const Grade* grade, std::ofstream& file)
{
	file << "[----]\n";
	file << grade->StudentId << '\n';
	file << grade->CourseId << '\n';
	file << grade->MidTerm << '\n';
	file << grade->Final << '\n';
	file << "[----]\n";
}

void SaveGrades(const Grade* grades, int amount)
{
	std::ofstream file;
	file.open(GRADES_FILE_PATH, std::ios::trunc);
	if (file.is_open())
	{
		for (int i = 0; i < amount; i++)
			WriteGradeToFile(&grades[i], file);
		file.close();
	}
	else
	{
		std::cout << "Failed to open file. press enter to continue";
		std::cin.get();
	}
}
void AppendGrade(const Grade* grade)
{
	std::ofstream file;
	file.open(GRADES_FILE_PATH, std::ios::app);
	if (file.is_open()) {
		WriteGradeToFile(grade, file);
	}
	else
		std::cout << "Failed to write grade to file";
}
Grade* LoadGrades(int* amount)
{
	std::ifstream file;
	file.open(GRADES_FILE_PATH);

	char buffer[512 + 1];
	*amount = 0;
	bool IsReadingGrade = false;
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
		Grade* grades = new Grade[*amount];
		int i = 0;
		file.clear();
		file.seekg(0, std::ios::beg);
		while (file.getline(buffer, 512))
		{
			//std::cout << "BUFF: " << buffer << '\n';

			if (strcmp(buffer, "[----]") == 0)
			{
				IsReadingGrade = !IsReadingGrade;
			}
			if (IsReadingGrade)
			{
				file.getline(buffer, 512);

				strncpy_s(grades[i].StudentId, buffer,STUDENT_ID_LENGTH);
				//grades[i].StudentId[STUDENT_ID_LENGTH] = '\0';
				file.getline(buffer, 512);

				strncpy_s(grades[i].CourseId, buffer, COURSE_ID_LENGTH);
				//grades[i].CourseId[COURSE_ID_LENGTH] = '\0';
				file.getline(buffer, 512);

				grades[i].MidTerm = atoi(buffer);
				file.getline(buffer,512);

				grades[i].Final = atoi(buffer);

				i++;
			}
		}

		file.close();

		return grades;
	}
	else {
		std::cout << "Error Opening file to load\n";
		return nullptr;
	}
}