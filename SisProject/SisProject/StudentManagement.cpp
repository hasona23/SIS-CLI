#define _CRT_SECURE_NO_WARNINGS
#include "StudentManagement.h"
#include <iostream>
#include <ctime>
#include <cmath>
#include <fstream>
#include <string>
#include <chrono>
#include "Utils.h"

//vALIDATION ===========================================================================================
static bool IsLeapYear(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
bool ValidateAge(const char* birthDateInput)
{
	static const int DYAS_OF_MONTH[] = {31,28,31,30,31,30,31,31,30,31,30,31};

	char birthDate[DATE_LENGTH+1];
	strncpy_s(birthDate, birthDateInput,DATE_LENGTH);
	birthDate[DATE_LENGTH] = '\0';

	for (int i = 0; birthDateInput[i] != '\0'; i++)
	{
		if(birthDate[i]=='\\' || birthDate[i]=='_' || birthDate[i]=='-' || birthDate[i]=='.')
			birthDate[i] = '/';
	}
	char* dayBuffer = strtok(birthDate, "/");
	if (dayBuffer == nullptr || !IsNumber(dayBuffer) || strlen(dayBuffer)>2)
		return false;
	std::cout << "DAY: " << dayBuffer << '\n';
	int birthDay = atoi(dayBuffer);
	
	char* monthBuffer = strtok(NULL,"/");
	if (monthBuffer == nullptr || !IsNumber(monthBuffer) || strlen(monthBuffer)>2)
		return false;
	std::cout << "MONTH: " << monthBuffer << '\n';
	int birthMonth = atoi(monthBuffer);

	char* yearBuffer = strtok(NULL,"/");
	if (yearBuffer == nullptr || !IsNumber(yearBuffer) || strlen(yearBuffer) != 4)
		return false;
	std::cout << "YEAR: " << yearBuffer << '\n';
	int birthYear = atoi(yearBuffer);

	//Check date is valid (EX: 31/2/2009)
	if (birthMonth < 1 || birthMonth>12)
		return false;
	if (birthMonth != 2)
	{
		if (birthDay > DYAS_OF_MONTH[birthMonth - 1])
			return false;

	}
	else {
		if (IsLeapYear(birthYear))
		{
			if (birthDay > 29)
				return false;
		}
		else {
			if (birthDay > 28)
				return false;
		}
	}
	std::cout << "Birthdate: " << birthDay << '/' << birthMonth << '/' << birthYear << '\n';
	time_t currentTime_t = time(0);
	tm* currentTime = localtime(&currentTime_t);

	//C stores time in years since 1900
	int currentYear = currentTime->tm_year + 1900;
	//C stores months from 0 to 11
	int currentMonth = currentTime->tm_mon + 1;
	int currentDay = currentTime->tm_mday;

	if (currentYear < birthYear)
		return false;
	else if (currentYear == birthYear)
	{
		if (currentMonth < birthMonth)
			return false;
		else if (currentMonth == birthMonth)
		{
			if (currentDay < birthDay)
				return false;
		}
	}
	
	return true;
}


bool ValidatePhoneNumber(const char* num)
{
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
	return level >= MIN_LEVEL && level <= MAX_LEVEL;
}

bool ValidateProgram(int program)
{
	return (program > 0 && program <= COMM);
}

bool ValidateGender(char gender)
{
	if (gender >= 'a' && gender <= 'z') {
		int diff = 'A' - 'a';
		gender += diff;
	}
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
	if (strlen(id) != STUDENT_ID_LENGTH)
	{
		return false;
	}
	if (id[0] == '0')
		return false;
	if (!isalnum(id[0]) || !isalnum(id[1]))
		return false;
	if (toupper(id[2]) != 'P')
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


//FILE IO ===========================================================================================
void CreateStudentFile()
{
	std::fstream file;
	//creates file
	file.open(STUDENT_FILE_PATH, std::ios::app);

	if (!file.is_open())
	{
		std::cout << "FAILED TO CREATE STUDENTS FILE\n";
		std::cout << "Press enter to exit...";
		std::cin.get();
		std::exit(1);
	}

}
void WriteStudentToFile(const Student student, std::ofstream& file)
{
	file << "[----]\n";
	file << student.Name << '\n';
	file << student.Id << '\n';
	file << student.NationalId << '\n';
	file << student.Gender << '\n';
	file << student.BirthDate << '\n';
	file << student.PhoneNumber << '\n';
	file << student.Gpa << '\n';

	file << student.Level << '\n';
	file << student.Program << '\n';


	file << "[----]\n";
}
void AppendStudent(const Student student)
{
	std::ofstream file;
	file.open(STUDENT_FILE_PATH, std::ios::app);
	if (file.is_open()) {
		WriteStudentToFile(student, file);
	}
	else
		std::cout << "Failed to write student to file";
}
void SaveStudents(const Student* students, int amount)
{
	std::ofstream file;
	file.open(STUDENT_FILE_PATH, std::ios::trunc);
	if (file.is_open())
	{
		for (int i = 0; i < amount; i++)
		{
			if (strlen(students[i].Name) != 0 && strlen(students[i].Id) != 0)
				WriteStudentToFile(students[i], file);
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

		*amount = separators;
		Student* students = new Student[*amount];
		int i = 0;
		file.clear();
		file.seekg(0, std::ios::beg);
		while (file.getline(buffer, 512))
		{
			//std::cout << "BUFF: " << buffer << '\n';

			if (strcmp(buffer, "[----]") == 0)
			{
				isReadingStudent = !isReadingStudent;
			}
			if (isReadingStudent)
			{
				file.getline(buffer, 512);
				strncpy_s(students[i].Name, buffer, MAX_NAME_LENGTH);

				file.getline(buffer, 512);
				strncpy_s(students[i].Id, buffer, STUDENT_ID_LENGTH);

				file.getline(buffer, 512);
				strncpy_s(students[i].NationalId, buffer, NATIONAL_ID_LENGTH);

				file.getline(buffer, 512);
				students[i].Gender = buffer[0];

				file.getline(buffer, 512);
				strncpy_s(students[i].BirthDate, buffer, DATE_LENGTH);

				file.getline(buffer, 512);
				strncpy_s(students[i].PhoneNumber, buffer, PHONE_NUM_LENGTH);

				file.getline(buffer, 512);
				students[i].Gpa = atof(buffer);

				file.getline(buffer, 512);
				students[i].Level = atoi(buffer);

				file.getline(buffer, 512);
				students[i].Program = (Programs)atoi(buffer);

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


void DeleteStudent(int index, Student* students, int* amount)
{
	if (index >= *amount)
		return;
	else {
		for (int i = index; i < (*amount - 1); i++)
			students[i] = students[i + 1];
		*amount = *amount - 1;
	}

}
void UpdateStudent(Student* student, const char* name, const char* phone, Programs program, int level)
{
	//strncpy_s(student->Id, id, ID_LENGTH);
	//student->Id[ID_LENGTH] = '\0';

	strncpy_s(student->Name, name, MAX_NAME_LENGTH);
	student->Name[MAX_NAME_LENGTH] = '\0';

	//strncpy_s(student->NationalId, nationalId, NATIONAL_ID_LENGTH);
	//student->NationalId[NATIONAL_ID_LENGTH] = '\0';

	strncpy_s(student->PhoneNumber, phone, PHONE_NUM_LENGTH);
	student->PhoneNumber[PHONE_NUM_LENGTH] = '\0';

	student->Program = program;
	student->Level = level;
	//student->Gpa = gpa;
}