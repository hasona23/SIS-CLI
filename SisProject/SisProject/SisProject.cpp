// SisProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <ctime>
#include <cmath>
#include <fstream>
#include <string>


const char MALE_GENDER = 'M';
const char FEMALE_GENDER = 'F';
const int ID_LENGTH = 7;
const int NATIONAL_ID_LENGTH = 14;
const int PHONE_NUM_LENGTH = 11;
const char* PHONE_NUM_PREFIX = "01";
const int MIN_AGE = 17;
const char* STUDENT_FILE_PATH = "./stduent.txt";
const int MAX_NAME_LENGTH = 256;

enum Programs
{
	MCTA = 1,
	CSE,
	CCE,
	ENRGY,
	COMM
};
/*
	Student:
		string ID
		string name
		string NationalId
		char Gender

		int yearBirth
		int dayBirth
		int monthBirth
		//CHECK AGE >= 17
		string Phone 01 + 9 nums
		enum PROGRAM
		int level
		int gpa

*/
struct Student
{
public:
	char Id[ID_LENGTH + 1];
	char Name[MAX_NAME_LENGTH + 1];
	char NationalId[NATIONAL_ID_LENGTH + 1];
	char PhoneNumber[PHONE_NUM_LENGTH + 1];
	char Gender;
	Programs Program;
	int Level; // 1-4
	float Gpa;



	int yearBirth;
	int dayBirth;
	int monthBirth;
};
void PrintStudent(const Student& s) {
	std::cout << "========================\n";
	std::cout << "ID           : " << s.Id << "\n";
	std::cout << "Name         : " << s.Name << "\n";
	std::cout << "National ID  : " << s.NationalId << "\n";
	std::cout << "Phone        : " << s.PhoneNumber << "\n";
	std::cout << "Gender       : " << s.Gender << "\n";
	std::cout << "Program      : " << s.Program << "\n";
	std::cout << "Level        : " << s.Level << "\n";
	std::cout << "GPA          : " << s.Gpa << "\n";
	std::cout << "Birthdate    : " << s.dayBirth << "/" << s.monthBirth << "/" << s.yearBirth << "\n";
	std::cout << "========================\n";
}


bool ValidateAge(int day, int month, int year)
{
	time_t currentTime = time(0);
	struct tm* current = localtime(&currentTime);

	int currentYear = current->tm_year + 1900;
	int currentMonth = current->tm_mon + 1;
	int currentDay = current->tm_mday;

	if (currentYear - year < MIN_AGE)
		return false;
	else if (currentYear - year > MIN_AGE)
		return true;

	if (currentMonth < month)
		return false;
	else if (currentMonth > month)
		return true;

	if (currentDay < day)
		return false;

	delete current;

	return true;
}


bool ValidatePhoneNumber(const char* num)
{
	time_t t = time(0);

	if (strlen(num) != PHONE_NUM_LENGTH)
		return false;
	for (int i = 0; i < strlen(PHONE_NUM_PREFIX); i++)
	{
		if (num[i] != PHONE_NUM_PREFIX[i])
			return false;
	}
	for (int i = 2; i < strlen(num); i++)
	{
		if (!isalnum(num[i]))
			return false;
	}
	return true;
}
bool ValidateGpa(double gpa)
{
	return gpa >= 0 && gpa <= 4;
}
bool ValidateLevel(int level)
{
	return level >= 1 && level <= 4;
}

bool ValidateProgram(int program)
{
	return (program > 0 && program <= COMM);
}

bool ValidateGender(char gender)
{
	return gender == MALE_GENDER || gender == FEMALE_GENDER;
}
bool ValidateNationalId(const char* id)
{
	if (strlen(id) != NATIONAL_ID_LENGTH)
		return false;
	for (int i = 0; i < strlen(id); i++)
	{
		if (!isalnum(id[i]))
			return false;
	}
	return true;
}
bool ValidateStudentId(const char* id)
{
	if (strlen(id) != ID_LENGTH)
	{
		return false;
	}
	if (id[0] == '0')
		return false;
	if (!isalnum(id[0]) || !isalnum(id[1]))
		return false;
	if (id[2] != 'P')
		return false;

	for (int i = 3; i < strlen(id); i++)
	{
		if (!isalnum(id[i]))
			return false;
	}

	return true;
}
bool ValidateName(const char* name)
{
	bool consistOfTwo = false;
	if (name[0] == ' ' || name[strlen(name) - 1] == ' ')
		return false;

	for (int i = 0; i < strlen(name); i++)
	{

		if (name[i] == ' ')
		{
			if (!consistOfTwo)
				consistOfTwo = true;
			else
				return false;
		}
		else if (!isalpha(name[i]))
		{
			return false;
		}
	}
	return consistOfTwo;
}
bool ValidateStudent(Student student)
{

	return ValidateStudentId(student.Id) && ValidateGender(student.Gender) &&
		ValidateName(student.Name) && ValidatePhoneNumber(student.PhoneNumber)
		&& ValidateProgram(student.Program) && ValidateNationalId(student.NationalId)
		&& ValidateLevel(student.Level) && ValidateGpa(student.Gpa);
}



void SaveStudents(const Student* students, int amount)
{
	std::ofstream file;
	file.open(STUDENT_FILE_PATH);
	if (file.is_open())
	{
		file.clear();

		for (int i = 0; i < amount; i++)
		{
			file << "[----]\n";
			file << students[i].Name << '\n';
			file << students[i].Id << '\n';
			file << students[i].NationalId << '\n';
			file << students[i].Gender << '\n';
			if (students[i].dayBirth < 10)
				file << '0';
			file << students[i].dayBirth << '/';
			if (students[i].monthBirth < 10)
				file << '0';
			file << students[i].monthBirth << '/' << students[i].yearBirth << '\n';
			file << students[i].PhoneNumber << '\n';
			file << students[i].Gpa << '\n';

			file << students[i].Level << '\n';
			file << students[i].Program << '\n';
			file << "[----]\n";
		}
		file.close();
	}
	else {
		std::cout << "Error Opening file to save\n";
	}

}
Student* LoadStudents(int* amount)
{
	std::ifstream file;
	file.open(STUDENT_FILE_PATH);
	char buffer[512 + 1];
	*amount = 0;
	bool isReadingStudent = false;
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
		std::cout << "Separators" << separators << '\n';
		*amount = separators;
		Student* students = new Student[*amount];
		int i = 0;
		file.clear();
		file.seekg(0,std::ios::beg);
		while (file.getline(buffer, 512))
		{
			//std::cout << "BUFF: " << buffer << '\n';
			
			if (strcmp(buffer, "[----]") == 0)
			{
				isReadingStudent = !isReadingStudent;
				std::cout << "BUF:"<<buffer<< isReadingStudent<<'\n';
			}
			if (isReadingStudent)
			{
				file.getline(buffer, 512);
				std::cout << "buffer" << buffer<<'\n';
				strncpy(students[i].Name, buffer,MAX_NAME_LENGTH);
				students[i].Name[MAX_NAME_LENGTH] = '\0';
				file.getline(buffer, 512);
				std::cout << "buffer" << buffer << '\n';
				strncpy(students[i].Id, buffer, ID_LENGTH);
				students[i].Id[ID_LENGTH] = '\0';
				file.getline(buffer, 512);
				std::cout << "buffer" << buffer << '\n';
				strncpy(students[i].NationalId, buffer, NATIONAL_ID_LENGTH);
				students[i].NationalId[NATIONAL_ID_LENGTH] = '\0';
				file.getline(buffer, 512);
				std::cout << "buffer" << buffer << '\n';
				students[i].Gender = buffer[0];
				file.getline(buffer, 512);
				std::cout << "buffer" << buffer << '\n';
				char dateBuffer[5];
				strncpy(dateBuffer, buffer, 2);
				dateBuffer[2] = '\0';
				
				students[i].dayBirth = atoi(dateBuffer);
				strncpy(dateBuffer, &buffer[3], 2);
				
				dateBuffer[2] = '\0';
				students[i].monthBirth = atoi(dateBuffer);
				strncpy(dateBuffer, &buffer[6], 4);
				dateBuffer[4] = '\0';
				
				students[i].yearBirth = atoi(dateBuffer);
				file.getline(buffer, 512);
				std::cout << "buffer" << buffer << '\n';
				strncpy(students[i].PhoneNumber, buffer, PHONE_NUM_LENGTH);
				students[i].PhoneNumber[PHONE_NUM_LENGTH] = '\0';
				file.getline(buffer, 512);
				std::cout << "buffer" << buffer << '\n';
				
				students[i].Gpa = std::stof(buffer);
				file.getline(buffer, 512);
				std::cout << "buffer" << buffer << '\n';
				students[i].Level = atoi(buffer);
				file.getline(buffer, 512);
				std::cout << "buffer" << buffer << '\n';
				students[i].Program = (Programs)atoi(buffer);
				

				//PrintStudent(students[i]);
				i++;
			}
		}
		
		file.close();
		
		return students;
	}
	else {
		std::cout << "Error Opening file to load\n";
		return nullptr;
	}
	
}


int main()
{
	std::cout << "===========================================================\n";
	std::cout << "================= Welcome To SIS Project ==================\n";
	std::cout << "===========================================================\n";
	Student s[] = {
	{
		.Id = "25P0111",
		.Name = "Mahmoud Mohamed",
		.NationalId = "20302030101234",
		.PhoneNumber = "01001400400",
		.Gender = MALE_GENDER,
		.Program = Programs::MCTA,
		.Level = 2,
		.Gpa = 3.235,
		.yearBirth = 2009,

		.dayBirth = 12,
		.monthBirth = 4,
	}
	,
	{
		.Id = "25P0111",
		.Name = "Mahmoud Mohamed",
		.NationalId = "20302030101234",
		.PhoneNumber = "01001400400",
		.Gender = MALE_GENDER,
		.Program = Programs::MCTA,
		.Level = 2,
		.Gpa = 3.235,
		.yearBirth = 2009,

		.dayBirth = 12,
		.monthBirth = 4,
	}
	,
	{
		.Id = "25P0111",
		.Name = "Mahmoud Mohamed",
		.NationalId = "20302030101234",
		.PhoneNumber = "01001400400",
		.Gender = MALE_GENDER,
		.Program = Programs::MCTA,
		.Level = 2,
		.Gpa = 3.235,
		.yearBirth = 2009,

		.dayBirth = 12,
		.monthBirth = 4,
	} };
	//std::cout << (ValidateStudent(s) ? "YES" : "NO") << '\n';

	//SaveStudents(s, 3);
	int amount = 0;
	Student* students = LoadStudents(&amount);
	std::cout <<'\n' << amount << '\n';
	for (int i = 0; i < amount; i++)
	{
		PrintStudent(students[i]);
	}
	delete[] students;
	//MENU:=======================================
	//STUDENTS
	//  1- ADD
	//  2- SEARCH (ID, NAME, NATIONAL_ID) Keep empty if not needed
	//  3- UPDATE
	//  4- DELETE
	//  5- LIST (SORT BY ID/NAME/GPA)
	//
	//COURSES
	//  1- ADD
	//  2- VIEW
	//  3- UPDATE
	//  4- DELETE
	//
	//GRADES
	//  1- ENTER GRADE
	//  2- VIEW
	//  3- CALC GPA
	//  4- GENERATE TRANSCRIPT  LIKE A DOCUMENT/TABLE WITH NAME, GRADE , COURSE CODE, GRADE AS LETTER
	//
	//
	//VALIDATION:=============================
	// 1- STUDENT_ID => YYPXXXX FORMAT + UNIQUE
	// 2- NATIONAL_ID => 14 DIGITS + NO LEADING ZEROS (0....) + UNIQUE  
	// 3- STUDENT_NAME => EXACTLY 2 WORDS
	// 4- STUDENT_PHONE => 11 DIGITS STARTING WITH 01
	// 5- COURSE_CODE => (3-LETTERS + 3-DIGITS) + UNIQUE
	//
	//
	// FILES:=====================================
	// 1- students.txt
	// 2- courses.txt
	// 3- grades.txt

	//FUNCTION REGIONS: 
	//  FILES=================
	//  WRITE STUDENTS
	//  READ STUDENTS
	//  WRITE COURSES
	//  READ COURSES
	//  WRITE GRADES
	//  READ GRADES
}