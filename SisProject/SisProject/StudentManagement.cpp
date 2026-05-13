#define _CRT_SECURE_NO_WARNINGS
#include "StudentManagement.h"
#include <iostream>
#include <ctime>
#include <cmath>
#include <fstream>
#include <string>
#include <chrono>
#include "Utils.h"
#include "GradesManagement.h"

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
	//Check for egypt phone codes
	if (num[2] != '0' && num[2] != '1' && num[2] != '2' && num[2] != '5'))
		return false;
	for (int i = 3; i < strlen(num); i++)
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


static void PrintStudent(const Student* s) {
	std::cout << "========================\n";
	std::cout << "ID           : " << s->Id << "\n";
	std::cout << "Name         : " << s->Name << "\n";
	std::cout << "National ID  : " << s->NationalId << "\n";
	std::cout << "Phone        : " << s->PhoneNumber << "\n";
	std::cout << "Gender       : " << s->Gender << "\n";
	std::cout << "Program      : " << ProgramsStr[s->Program - 1] << "\n";
	std::cout << "Level        : " << s->Level << "\n";
	std::cout << "GPA          : " << s->Gpa << "\n";
	std::cout << "Birthdate    : " << s->BirthDate << "\n";
	std::cout << "========================\n";
}


Programs GetProgram()
{
	std::cout << "Choose Program: \n";
	for (int i = 1; i <= (int)Programs::COMM; i++)
	{
		std::cout << i << ") " << ProgramsStr[i - 1] << '\n';
	}
	int choice = -1;
	while (!ValidateProgram(choice))
	{
		std::cout << "Program: ";
		std::cin >> choice;
	}

	return (Programs)choice;
}

static int GetIdDigits(const char* id)
{
	int start = 3;
	int amount = 0;
	int power = 4;
	for (int i = start; i < strlen(id); i++)
	{
		amount += atoi(&id[i]) * std::pow(10, power--);
	}
	return amount;
}

static void SortStudentsById(Student* students, int amount)
{
	bool hasSwapped = true;
	while (hasSwapped)
	{
		hasSwapped = false;
		for (int j = 0; j < amount - 1; j++)
		{
			if (strcmp(students[j].Id, students[j + 1].Id) > 0)
			{
				Student temp = students[j];
				students[j] = students[j + 1];
				students[j + 1] = temp;
				hasSwapped = true;
			}
		}
	}
}
static void SortStudentsByGpa(Student* students, int amount)
{
	bool hasSwapped = true;
	while (hasSwapped)
	{

		hasSwapped = false;
		for (int j = 0; j < amount - 1; j++)
		{

			if (students[j].Gpa < students[j + 1].Gpa)
			{
				Student temp = students[j];
				students[j] = students[j + 1];
				students[j + 1] = temp;
				hasSwapped = true;
			}
		}
	}
}
static void SortStudentsByName(Student* students, int amount)
{
	bool hasSwapped = true;
	while (hasSwapped)
	{
		hasSwapped = false;
		for (int j = 0; j < amount - 1; j++)
		{

			if (strcmp(students[j].Name, students[j + 1].Name) > 0)
			{
				Student temp = students[j];
				students[j] = students[j + 1];
				students[j + 1] = temp;
				hasSwapped = true;
			}
		}
	}
}

static void SortStudentsByNationalId(Student* students, int amount)
{
	bool hasSwapped = true;
	while (hasSwapped)
	{
		hasSwapped = false;
		for (int j = 0; j < amount - 1; j++)
		{

			if (strcmp(students[j].NationalId, students[j + 1].NationalId) > 0)
			{
				Student temp = students[j];
				students[j] = students[j + 1];
				students[j + 1] = temp;
				hasSwapped = true;
			}
		}
	}
}
void ListStudents(Student* students, int amount)
{
	if (amount == 0) {
		cout << endl << "No students registered. Press ENTER to continue... ";

		cin.ignore();
		cin.get();


		return;
	}
	DisplayTitle("Student List");
	std::cout << "Choose Sorting Method: \n";
	std::cout << "1) Id\n";
	std::cout << "2) Name\n";
	std::cout << "3) GPA\n";
	std::cout << "4) National Id\n";
	int choice = 0;

	int gradesCount = 0;
	Grade* grades = LoadGrades(&gradesCount);
	for (int i = 0; i < amount; i++)
	{
		students[i].Gpa = CalculateGpa(students[i].Id, grades, gradesCount);
	}
	do
	{
		std::cout << "Choice: ";
		std::cin >> choice;
	} while (choice < 1 || choice > 4);
	switch (choice)
	{
	case 2:
		SortStudentsByName(students, amount);
		break;
	case 3:
		SortStudentsByGpa(students, amount);
		break;
	case 4:
		SortStudentsByNationalId(students, amount);
		break;
	default:
		SortStudentsById(students, amount);
		break;
	}
	for (int i = 0; i < amount; i++)
	{
		PrintStudent(&students[i]);
	}
	std::cin.ignore();
	std::cout << "press enter to continue...";
	std::cin.get();

	delete[] grades;
}

void AddStudentMenu(Student* students, int amount)
{
	Student student{};

	std::string firstName = "";
	std::string secondName = "";
	std::string inputBuffer = "";


	std::cout << "Enter student first name: ";
	std::cin >> firstName;


	std::cout << "Enter student second name: ";
	std::cin >> secondName;
	RemoveSpaces(firstName);
	RemoveSpaces(secondName);
	std::string fullName = firstName + " " + secondName;
	strncpy_s(student.Name, fullName.c_str(), MAX_NAME_LENGTH);
	student.Name[MAX_NAME_LENGTH] = '\0';
	while (!ValidateName(student.Name))
	{
		std::cout << "Invalid Name [" << student.Name << "]. Enter in format [FirstName] [SecondName] or back to exit \n\n";
		std::cout << "Enter student first name: ";
		std::cin >> firstName;
		RemoveSpaces(firstName);
		if (firstName == "back")
		{
			std::cout << "Going back to menu...\n";
			PressEnterPause();
			return;
		}
		//std::cin.ignore();
		std::cout << "Enter student second name: ";
		std::cin >> secondName;
		RemoveSpaces(secondName);
		if (firstName == "back")
		{
			std::cout << "Going back to menu...\n";
			PressEnterPause();
			return;
		}

		std::string fullName = firstName + " " + secondName;
		strncpy_s(student.Name, fullName.c_str(), MAX_NAME_LENGTH);
		student.Name[MAX_NAME_LENGTH] = '\0';
		continue;
	}

	std::cout << '\n';

	std::cout << "Enter phone number: ";
	std::cin >> inputBuffer;
	RemoveSpaces(inputBuffer);
	while (!ValidatePhoneNumber(inputBuffer.c_str()))
	{
		std::cout << "Invalid PhoneNumber [" << inputBuffer << "]. format 01 + 9 digits or enter back to continue\n";
		std::cout << "Enter phone number: ";
		std::cin >> inputBuffer;
		RemoveSpaces(inputBuffer);
		if (inputBuffer == "back")
		{
			std::cout << "Going back to menu...\n";
			PressEnterPause();
			return;
		}
	}
	strncpy_s(student.PhoneNumber, inputBuffer.c_str(), PHONE_NUM_LENGTH);


	std::cout << "Enter national ID: ";
	std::cin >> inputBuffer;
	RemoveSpaces(inputBuffer);
	bool isDuplicateNationalId = false;
	for (int i = 0; i < amount; i++)
	{
		if (strcmp(student.NationalId, students[i].NationalId) == 0)
		{
			std::cout << "National Id Already exist!\n";
			std::cout << "Press enter to continue...";
			std::cin.get();
			isDuplicateNationalId = true;
			break;
		}
	}
	while (!ValidateNationalId(inputBuffer.c_str()) || isDuplicateNationalId)
	{
		std::cout << "Invalid NationalID [" << inputBuffer << "]. should be of " << NATIONAL_ID_LENGTH << " digits or back to exit \n";
		std::cin >> inputBuffer;
		RemoveSpaces(inputBuffer);
		if (inputBuffer == "back")
		{
			std::cout << "Going back to menu...\n";
			PressEnterPause();
			return;
		}
		bool isDuplicateNationalId = false;
		for (int i = 0; i < amount; i++)
		{
			if (strcmp(student.NationalId, students[i].NationalId) == 0)
			{
				std::cout << "National Id Already exist!\n";
				std::cout << "Press enter to continue...";
				std::cin.get();
				isDuplicateNationalId = true;
				break;
			}
		}
		continue;
	}
	strncpy_s(student.NationalId, inputBuffer.c_str(), NATIONAL_ID_LENGTH);



	std::cout << "Enter Gender(" << MALE_GENDER << " - " << FEMALE_GENDER << "): ";
	std::cin >> inputBuffer;
	RemoveSpaces(inputBuffer);
	while (!ValidateGender(inputBuffer[0]))
	{
		std::cout << "Invalid Gender [" << student.Gender << "]. should be (" << MALE_GENDER << " - " << FEMALE_GENDER << ") or back to continue\n";
		std::cin >> inputBuffer;
		RemoveSpaces(inputBuffer);
		if (inputBuffer == "back")
		{
			std::cout << "Going back to menu...\n";
			PressEnterPause();
			return;
		}
	}
	student.Gender = toupper(inputBuffer[0]);

	std::cout << "Enter student level: ";
	std::cin >> student.Level;
	while (!ValidateLevel(student.Level))
	{
		std::cout << "Invalid Level [" << student.Level << "]. (" << MIN_LEVEL << " , " << MAX_LEVEL << ")\n";
		std::cin >> student.Level;
	}

	student.Gpa = 0.0;

	student.Program = GetProgram();

	std::cout << "Enter birth (DD/MM/YYYY): ";
	std::cin >> inputBuffer;
	RemoveSpaces(inputBuffer);
	while (!ValidateAge(inputBuffer.c_str()))
	{
		std::cout << "Invalid BirthDate [" << inputBuffer << "]. Format DD/MM/YYYY or back to exit \n";
		std::cin >> inputBuffer;
		RemoveSpaces(inputBuffer);
		if (inputBuffer == "back")
		{
			std::cout << "Going back to menu...\n";
			PressEnterPause();
			return;
		}
	}
	strncpy_s(student.BirthDate, inputBuffer.c_str(), DATE_LENGTH);

	int maxId = 0;
	for (int i = 0; i < amount; i++)
	{
		//25p0000
		std::string idStr = std::string(students[i].Id);
		int id = stoi(idStr.substr(3, 4));
		if (id > maxId)
			maxId = id;
	}
	//To get next id in sequence;
	maxId++;
	if (maxId > 9999)
	{
		std::cout << "Reached maximum ID count.\n";
		PressEnterPause();
	}
	std::string newIdStr = std::to_string(maxId);
	int missingPaddingZeroes = 4 - newIdStr.length();
	for (int i = 0; i < missingPaddingZeroes; i++)
	{
		newIdStr = "0" + newIdStr;
	}
	std::string newId = "25P" + newIdStr;
	std::cout << "Student Id: " << newId << '\n';
	strncpy_s(student.Id, newId.c_str(), STUDENT_ID_LENGTH);
	PrintStudent(&student);
	PressEnterPause();
	AppendStudent(student);
}

void SearchStudents(Student* students, int amount)
{
	if (amount == 0) {
		cout << endl << "No students registered. Press ENTER to continue....";
		cin.ignore();
		cin.get();
		return;
	}
	std::string searchName;
	std::string searchId = "";
	std::string searchNationalId = "";
	std::string searchPhoneNumber = "";
	std::cin.ignore();
	std::cout << "Enter Name (enter 0 to ignore): \n";
	std::getline(std::cin, searchName, '\n');
	while (searchName != "0" && !ValidateName(searchName.c_str()))
	{
		std::cout << "Invalid NAME [" << searchName << "]. format [FirstName] [LastName] or enter back to continue\n";
		std::cout << "Enter Name: ";
		std::getline(std::cin, searchName, '\n');
		if (searchName == "back")
		{
			std::cout << "Going back to menu...\n";
			PressEnterPause();
			return;
		}
	}
	std::cout << "Enter ID (enter 0 to ignore): \n";
	std::cin >> searchId;
	RemoveSpaces(searchId);
	while (searchId != "0" && !ValidateStudentId(searchId.c_str()))
	{
		std::cout << "Invalid ID [" << searchId << "]. format 25PXXXX or enter back to continue\n";
		std::cout << "Enter ID: ";
		std::cin >> searchId;
		RemoveSpaces(searchId);
		if (searchId == "back")
		{
			std::cout << "Going back to menu...\n";
			PressEnterPause();
			return;
		}
	}
	toUpper(searchId.data());

	std::cout << "Enter NationalID (enter 0 to ignore): \n";
	std::cin >> searchNationalId;
	RemoveSpaces(searchNationalId);
	while (searchNationalId != "0" && !ValidateNationalId(searchNationalId.c_str()))
	{
		std::cout << "Invalid NationalID [" << searchNationalId << "].Enter " << NATIONAL_ID_LENGTH << " digits or enter back to continue\n";
		std::cout << "Enter NationalID: ";
		std::cin >> searchNationalId;
		RemoveSpaces(searchNationalId);
		if (searchNationalId == "back")
		{
			std::cout << "Going back to menu...\n";
			PressEnterPause();
			return;
		}
	}
	std::cout << "Enter phoneNumber (enter 0 to ignore): \n";
	std::cin >> searchPhoneNumber;
	RemoveSpaces(searchPhoneNumber);
	while (searchPhoneNumber != "0" && !ValidatePhoneNumber(searchPhoneNumber.c_str()))
	{
		std::cout << "Invalid PhoneNumber [" << searchPhoneNumber << "]. format 01 + 9 digits or enter back to continue\n";
		std::cout << "Enter phone number: ";
		std::cin >> searchPhoneNumber;
		RemoveSpaces(searchPhoneNumber);
		if (searchPhoneNumber == "back")
		{
			std::cout << "Going back to menu...\n";
			PressEnterPause();
			return;
		}
	}

	int countFound = 0;
	for (int i = 0; i < amount; i++)
	{
		bool nameFilter = (searchName == "0" || (searchName == students[i].Name));
		bool idFilter = (searchId == "0" || (searchId == students[i].Id));
		bool phoneFilter = (searchPhoneNumber == "0" || (searchPhoneNumber == students[i].PhoneNumber));
		bool nationalIdFilter = (searchNationalId == "0" || (searchNationalId == students[i].NationalId));
		if (nameFilter && idFilter && phoneFilter && nationalIdFilter) {
			PrintStudent(&students[i]);
			countFound++;
		}
	}
	if (countFound == 0)
	{
		std::cout << "No Students where found with criteria\n";
	}
	PressEnterPause();

}
void DeleteStudentMenu(Student* students, int* amount)

{
	if (*amount == 0) {
		cout << endl << "No students registered. Press ENTER to continue... ";

		cin.ignore();//it just fixes the glitch idk
		cin.get();


		return;
	}
	for (int i = 0; i < *amount; i++)
	{
		std::cout << (i + 1) << ") " << students[i].Id << " - " << students[i].Name << '\n';
	}
	std::string inputId = "";
	bool wasFound = false;
	int removeIndex = -1;
	do
	{
		std::cout << "Input ID (back to exit): ";
		std::cin >> inputId;
		if (inputId == "back")
			return;
		toUpper(inputId.data());
		if (!ValidateStudentId(inputId.c_str()))
		{
			std::cout << "Invalid input Id\n";
			continue;
		}
		wasFound = false;
		for (int i = 0; i < *amount; i++)
		{
			if (strcmp(students[i].Id, inputId.c_str()) == 0)
			{
				wasFound = true;
				removeIndex = i;
				break;
			}
		}
		if (!wasFound)
		{
			std::cout << "Student with ID " << inputId << " not found\n";
		}
	} while (!ValidateStudentId(inputId.c_str()) || !wasFound);
	cin.ignore(); //Modified this part to enable confirmation messages -Eyad
	cout << endl << "Are you sure you want to delete this student? (Y/N) ";

	if (tolower(cin.get()) == 'y') {
		int gradesCount = 0;
		Grade* grades = LoadGrades(&gradesCount);
		DeleteGradeByCourseId(grades, students[removeIndex].Id, &gradesCount);
		SaveGrades(grades, gradesCount);
		delete[] grades;

		DeleteStudent(removeIndex, students, amount);
	}
	else return;
}
void UpdateStudentMenu(Student* students, int amount)
{
	if (amount == 0) {
		cout << endl << "No students registered. Press ENTER to continue....";
		cin.ignore();
		cin.get();
		return;
	}
	for (int i = 0; i < amount; i++)
	{
		std::cout << (i + 1) << ") " << students[i].Id << " - " << students[i].Name << '\n';
	}
	int index = -1;
	std::string inputId = "";
	bool wasFound = false;
	do
	{
		std::cout << "Input ID (back to exit): ";
		std::cin >> inputId;
		if (inputId == "back")
			return;
		if (!ValidateStudentId(inputId.c_str()))
		{
			std::cout << "Invalid input Id\n";
			continue;
		}
		wasFound = false;
		//.data changes from std::string to normal char*
		toUpper(inputId.data());
		for (int i = 0; i < amount; i++)
		{
			if (strcmp(students[i].Id, inputId.c_str()) == 0)
			{
				wasFound = true;
				index = i;
				break;
			}
		}
		if (!wasFound)
			std::cout << "student with id " << inputId << " not found\n";
	} while (!ValidateStudentId(inputId.c_str()) || !wasFound);
	std::string newName;
	std::string newPhone;
	Programs program = MCTA;
	int level;


	std::cout << "Enter new name or 0 to skip: ";
	std::cin.ignore();
	std::getline(std::cin, newName);

	while (newName != "0" && !ValidateName(newName.c_str()))
	{
		std::cout << "Invalid NAME [" << newName << "]. format [FirstName] [LastName] or enter back to continue\n";
		std::cout << "Enter Name: ";
		std::getline(std::cin, newName);
		if (newName == "back")
		{
			std::cout << "Going back to menu...\n";
			PressEnterPause();
			return;
		}
	}
	if (newName == "0")
		newName = students[index].Name;
	std::cin.ignore();
	std::cout << "Enter new Phone number or 0 to skip: ";
	std::cin >> newPhone;
	RemoveSpaces(newPhone);
	while (newPhone != "0" && !ValidatePhoneNumber(newPhone.c_str()))
	{
		std::cout << "Invalid PhoneNumber [" << newPhone << "]. format 01 + 9 digits or enter back to continue\n";
		std::cout << "Enter phone number: ";
		std::cin >> newPhone;
		RemoveSpaces(newPhone);
		if (newPhone == "back")
		{
			std::cout << "Going back to menu...\n";
			PressEnterPause();
			return;
		}
	}
	if (newPhone == "0")
		newPhone = students[index].PhoneNumber;

	std::cin.ignore();
	std::cout << "do you want to change program(Y/N): ";
	if (tolower(std::cin.get()) == 'y')
		program = GetProgram();

	//std::cin.ignore();
	std::cout << "Enter new level or 0 to skip: ";
	std::cin >> level;



	UpdateStudent(&students[index], newName.c_str(), newPhone.c_str(), program, level);
}


int StudentManagementMenu() {//studmng menu


	int choice = -1;

	while (choice != 0) {
		ClearCmd();
		DisplayTitle("Student Management");
		
		cout << "1. List Students" << '\n' << "2. Search Student" << '\n' << "3. Add Student" << '\n' << "4. Update Student" << '\n';
		cout << "5. Delete Student" << '\n' << "0. Back to Main Menu";
		cout << '\n' << '\n';
		cout << "Enter your choice: ";
		std::string input;
		cin >> input;

		if (IsNumber(input.c_str()))
			choice = atoi(input.c_str());
		else 
		{
			choice = -1;
			std::cout << "Invalid input, please try again" << '\n'; 
			PressEnterPause();
			continue;
		}
		Student* students = nullptr;
		int amount = 0;

		students = LoadStudents(&amount);

		switch (choice) {
		case 1:
			ListStudents(students, amount);
			break;
		case 2:
			SearchStudents(students, amount);
			break;
		case 3:
			AddStudentMenu(students, amount);
			
			break;
		case 4:
			UpdateStudentMenu(students, amount);
			break;
		case 5: 
			DeleteStudentMenu(students, &amount);
			break;
		case 0:
			std::cout << "Going back to main menu.\n";
			break;

		default:
			std::cout << "Invalid input, please try again" << '\n';
			choice = -1;
		}
		if (choice != 3) {
			SortStudentsById(students, amount);
			SaveStudents(students, amount);
		}
		delete[] students;

	}

	return choice;
}