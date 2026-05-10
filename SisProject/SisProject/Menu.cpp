#include "Menu.h"
#include "GradesManagement.h"
#include <string>
#include "Utils.h"


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


	int choice = 0;

	while (choice != 6) {
		ClearCmd();
		for (int i = 0; i < 3; i++) cout << "=";
		cout << " " << "Student Management" << " ";
		for (int i = 0; i < 3; i++) cout << "=";
		cout << '\n' << '\n';
		cout << "1. Add New Student" << '\n' << "2. Search Student" << '\n' << "3. Update Student" << '\n' << "4. Delete Student" << '\n';
		cout << "5. List All Student" << '\n' << "6. Back to Main Menu";
		cout << '\n' << '\n';
		cout << "Enter your choice: ";
		cin >> choice;
		Student* students = nullptr;
		int amount = 0;

		students = LoadStudents(&amount);

		switch (choice) {
		case 1:
			AddStudentMenu(students, amount);
			break;
		case 2:
			SearchStudents(students, amount);
			break;
		case 3:UpdateStudentMenu(students, amount);
			break;
		case 4: DeleteStudentMenu(students, &amount);
			break;
		case 5: ListStudents(students, amount);
			break;
		case 6:
			std::cout << "Going back to main menu.\n";
			break;

		default:
			std::cout << "Invalid input, please try again" << '\n';
			choice = 0;
		}
		if (choice != 1) {
			SortStudentsById(students, amount);
			SaveStudents(students, amount);
		}
		delete[] students;

	}

	return choice;
}

int CourseManagementMenu() {//course management menu

	int choice = 0;

	while (choice != 5) {
		ClearCmd();
		for (int i = 0; i < 3; i++) cout << "=";
		cout << " " << "Course Management" << " ";
		for (int i = 0; i < 3; i++) cout << "=";
		cout << '\n' << '\n';
		cout << "1. Add New Course" << '\n' << "2. View All Courses" << '\n' << "3. Update Course" << '\n' << "4. Delete Course" << '\n';;
		cout << "5. Back to Main Menu";
		cout << '\n' << '\n';



		cout << "Enter your choice: ";

		Course* courses = nullptr;
		int amount = 0;

		courses = LoadCourses(&amount);
		cin >> choice;
		cin.ignore(); //eyad added this
		switch (choice) {
		case 1:addCourse();
			break;
		case 2:ListCourses(courses, amount);
			break;
		case 3:UpdateCourseMenu(courses, amount);
			break;
		case 4:  DeleteCourseMenu(courses, &amount);
			break;
		case 5: cout << "Going back to main menu.\n";

			break;
		default:choice = 0;
			cout << "Invalid input, please try again" << '\n';




		}if (choice != 1) {

			SaveCourses(courses, amount);
		}
		delete[] courses;
	}

	return choice;


}

static void HelpMenu()
{
	int choice = 0;

	while (choice != 5)
	{
		ClearCmd();
		DisplayTitle("Help");

		std::cout << "1. Student Management\n";
		std::cout << "2. Course Management\n";
		std::cout << "3. Grades Management\n";
		std::cout << "4. ID & Format Reference\n";
		std::cout << "5. Back to Main Menu\n\n";
		std::cout << "Enter your choice: ";
		std::cin >> choice;

		ClearCmd();

		switch (choice)
		{
		case 1:
			DisplayTitle("Help - Student Management");
			std::cout << "Add Student\n";
			std::cout << "  Registers a new student. You will be prompted for:\n";
			std::cout << "  - Name        : First and last name (letters only)\n";
			std::cout << "  - Phone       : 11 digits starting with 01\n";
			std::cout << "  - National ID : " << NATIONAL_ID_LENGTH << "-digit national ID (must be unique)\n";
			std::cout << "  - Gender      : " << MALE_GENDER << " or " << FEMALE_GENDER << "\n";
			std::cout << "  - Level       : Between " << MIN_LEVEL << " and " << MAX_LEVEL << "\n";
			std::cout << "  - Program     : Choose from the available programs list\n";
			std::cout << "  - Birthdate   : Format DD/MM/YYYY\n";
			std::cout << "  Student IDs are assigned automatically (e.g. 25P0001).\n";
			std::cout << "  Type 'back' at any prompt to cancel.\n\n";

			std::cout << "Search Student\n";
			std::cout << "  Search by Name, ID, National ID, and/or Phone Number.\n";
			std::cout << "  Enter 0 to skip any field. Results must match all filled fields.\n\n";

			std::cout << "Update Student\n";
			std::cout << "  Select a student by ID, then update Name, Phone, Program, or Level.\n";
			std::cout << "  Enter 0 to skip a field. Type 'back' to cancel.\n\n";

			std::cout << "Delete Student\n";
			std::cout << "  Select a student by ID. You will be asked to confirm before deletion.\n";
			std::cout << "  This action is permanent.\n\n";

			std::cout << "List All Students\n";
			std::cout << "  Displays all students sorted by your choice of:\n";
			std::cout << "  ID, Name, GPA, or National ID.\n";
			break;

		case 2:
			DisplayTitle("Help - Course Management");
			std::cout << "Add Course\n";
			std::cout << "  Registers a new course. You will be prompted for:\n";
			std::cout << "  - Course ID    : Exactly 6 characters: 3 letters then 3 digits (e.g. CSC101)\n";
			std::cout << "                   Must be unique. Letters are auto-uppercased.\n";
			std::cout << "  - Course Title : Any non-empty name\n";
			std::cout << "  - Credit Hours : Must be 1, 2, 3, or 4\n\n";

			std::cout << "View All Courses\n";
			std::cout << "  Lists all registered courses sorted by your choice of:\n";
			std::cout << "  ID, Title (A-Z), or Credit Hours.\n\n";

			std::cout << "Update Course\n";
			std::cout << "  Select a course by ID, then update its Title and/or Credit Hours.\n";
			std::cout << "  Enter 0 to skip a field. Type 'back' to cancel.\n\n";

			std::cout << "Delete Course\n";
			std::cout << "  Select a course by ID. You will be asked to confirm before deletion.\n";
			std::cout << "  This action is permanent.\n";
			break;

		case 3:
			DisplayTitle("Help - Grades Management");
			std::cout << "Enter Student Grades\n";
			std::cout << "  Records grades for a student in a specific course.\n";
			std::cout << "  - Student ID   : The student's assigned ID (e.g. 25P0001)\n";
			std::cout << "  - Course Code  : The course ID (e.g. CSC101)\n";
			std::cout << "  - Midterm      : Score out of 40\n";
			std::cout << "  - Final        : Score out of 60\n\n";

			std::cout << "View Student Grades / Generate Transcript\n";
			std::cout << "  Enter a student ID to display all their recorded courses,\n";
			std::cout << "  showing Midterm, Final, and Total for each, followed by GPA.\n\n";

			std::cout << "GPA Scale\n";
			std::cout << "  90 - 100  =>  4.0\n";
			std::cout << "  80 -  89  =>  3.0\n";
			std::cout << "  70 -  79  =>  2.0\n";
			std::cout << "  60 -  69  =>  1.0\n";
			std::cout << "  Below 60  =>  0.0\n";
			std::cout << "  GPA is the average points across all recorded courses.\n";
			break;

		case 4:
			DisplayTitle("Help - ID & Format Reference");
			std::cout << "Student ID  : 25P followed by 4 digits        (e.g. 25P0001)\n";
			std::cout << "Course ID   : 3 uppercase letters + 3 digits  (e.g. CSC101)\n";
			std::cout << "National ID : " << NATIONAL_ID_LENGTH << " digits                        \n";
			std::cout << "Phone       : 11 digits starting with 01      (e.g. 01012345678)\n";
			std::cout << "Birthdate   : DD/MM/YYYY                      (e.g. 15/06/2003)\n";
			std::cout << "Gender      : " << MALE_GENDER << " (Male) or " << FEMALE_GENDER << " (Female)\n";
			std::cout << "Credit Hrs  : 1, 2, 3, or 4\n";
			std::cout << "Level       : Between " << MIN_LEVEL << " and " << MAX_LEVEL << "\n";
			break;

		case 5:
			std::cout << "Going back to main menu.\n";
			break;

		default:
			std::cout << "Invalid input, please try again.\n";
			choice = 0;
			break;
		}

		if (choice >= 1 && choice <= 4)
		{
			PressEnterPause();
		}
	}
}

int MainMenu() {//main menu func
	int choice;
	bool valid = false;
	//int studmngout = studmng();

	//validation of choice starts here
	while (!valid) {
		ClearCmd();
		DisplayTitle("Student information system");
		cout << "1. Student Management" << '\n' << "2. Course Management" << '\n' << "3. Grades Management" << '\n' <<"4. Help"<<'\n' << "5. Exit";
		cout << '\n' << '\n';
		cout << "Enter your choice: ";
		cin >> choice;
		valid = true;
		
		switch (choice) {
		case 1:
			StudentManagementMenu();
			break;
		case 2:CourseManagementMenu();
			break;
		case 3:GradesManagementMenu();
			break;
		case 4:
			HelpMenu();
			break;
		case 5:
			cout << "Exiting, thank you for using the program." << '\n';
			return -1;
		default:choice = 0;
			cout << "Invalid input, please try again" << '\n';
			valid = false;

		}


	}


	return choice;
}
int GradesManagementMenu() {//grades mng menu
	for (int i = 0; i < 3; i++) cout << "=";
	cout << " " << "Grades Management" << " ";
	for (int i = 0; i < 3; i++) cout << "=";
	cout << '\n' << '\n';
	cout << "1. Enter Student Grades" << '\n' << "2. View Student Grades" << '\n' << "3. Calculate GPA" << '\n' << "4. Generate Transcript" << '\n';;
	cout << "5. Back to Main Menu";
	cout << '\n' << '\n';

	int choice = 0; bool valid = false;
	while (!valid) {
		cout << "Enter your choice: ";
		cin >> choice;
		switch (choice) {
		case 1:valid = true;
			break;
		case 2:valid = true;
			break;
		case 3:valid = true;
			break;
		case 4: valid = true; break;
		case 5: return -1;
		default:choice = 0;
			cout << "Invalid input, please try again" << '\n';
			valid = false;

		}

	}

	return choice;




}

int RunSis() {
	//should be the main func ultimately
	CreateStudentFile();
	CreateCoursesFile();
	CreateGradesFile();
	bool isrunning = true;

	while (isrunning) {
		int menuStatus = MainMenu();

		std::cout << '\n';
		if (menuStatus == -1) isrunning = false;




	}




	return 0;
}