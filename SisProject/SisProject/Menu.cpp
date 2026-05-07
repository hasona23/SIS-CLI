#include "Menu.h"
#include <string>

void PressEnterPause()
{
	std::cout << "Press Enter to Continue...";
	std::cin.ignore();
	std::cin.get();
}

void PrintStudent(const Student s) {
	std::cout << "========================\n";
	std::cout << "ID           : " << s.Id << "\n";
	std::cout << "Name         : " << s.Name << "\n";
	std::cout << "National ID  : " << s.NationalId << "\n";
	std::cout << "Phone        : " << s.PhoneNumber << "\n";
	std::cout << "Gender       : " << s.Gender << "\n";
	std::cout << "Program      : " << s.Program << "\n";
	std::cout << "Level        : " << s.Level << "\n";
	std::cout << "GPA          : " << s.Gpa << "\n";
	std::cout << "Birthdate    : " << s.BirthDate << "\n";
	std::cout << "========================\n";
}

void DisplayTitle(const char title[]) {
	int space = 7;
	int length = strlen(title);
	cout << ASCII_TOP_LEFT_CORNER;
	for (int i = 0; i < 14 + length; i++) cout << ASCII_HORIZONTAL_LINE;
	cout << ASCII_TOP_RIGHT_CORNER << '\n' << ASCII_VERTICAL_LINE;
	for (int i = 0; i < 7; i++) cout << " ";
	cout << title;
	for (int i = 0; i < 7; i++) cout << " ";
	cout << ASCII_VERTICAL_LINE << '\n' << ASCII_BOTTOM_LEFT_CORNER;
	for (int i = 0; i < 14 + length; i++) cout << ASCII_HORIZONTAL_LINE;
	cout << ASCII_BOTTOM_RIGHT_CORNER << '\n' << '\n';

}

Programs GetProgram()
{
	static const char* ProgramsStr[] = { "MCTA" ,"CSE","CCE","ENRGY","COMM" };

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

void ListStudents(Student* students, int amount)
{
	for (int i = 0; i < amount; i++)
	{
		PrintStudent(students[i]);
	}
	std::cin.ignore();
	std::cout << "press enter to continue...";
	std::cin.get();
}

void AddNewStudent(Student* students, int amount)
{
	Student student{};

	std::string firstName = "";
	std::string secondName = "";
	std::string inputBuffer = "";


	std::cout << "Enter student first name: ";
	std::cin >> firstName;


	std::cout << "Enter student second name: ";
	std::cin >> secondName;

	std::string fullName = firstName + " " + secondName;
	strncpy_s(student.Name, fullName.c_str(), MAX_NAME_LENGTH);
	student.Name[MAX_NAME_LENGTH] = '\0';
	while (!ValidateName(student.Name))
	{
		std::cout << "Invalid Name [" << student.Name << "]. Enter in format [FirstName] [SecondName] or back to exit \n\n";
		std::cout << "Enter student first name: ";
		std::cin >> firstName;
		if (firstName == "back")
		{
			std::cout << "Going back to menu...\n";
			PressEnterPause();
			return;
		}
		//std::cin.ignore();
		std::cout << "Enter student second name: ";
		std::cin >> secondName;
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
	while (!ValidatePhoneNumber(inputBuffer.c_str()))
	{
		std::cout << "Invalid PhoneNumber [" << inputBuffer << "]. format 01 + 9 digits or enter back to continue\n";
		std::cout << "Enter phone number: ";
		std::cin >> inputBuffer;
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
	while (!ValidateGender(inputBuffer[0]))
	{
		std::cout << "Invalid Gender [" << student.Gender << "]. should be (" << MALE_GENDER << " - " << FEMALE_GENDER << ") or back to continue\n";
		std::cin >> inputBuffer;
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
	while (!ValidateAge(inputBuffer.c_str()))
	{
		std::cout << "Invalid BirthDate [" << inputBuffer << "]. Format DD/MM/YYYY or back to exit \n";
		std::cin >> inputBuffer;
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
	int missingPaddingZeroes = 4 - newIdStr.length() ;
	for (int i = 0; i < missingPaddingZeroes; i++)
	{
		newIdStr = "0" + newIdStr;
	}
	std::string newId = "25P" + newIdStr;
	std::cout << newId << '\n';
	strncpy_s(student.Id, newId.c_str(), STUDENT_ID_LENGTH);
	PrintStudent(student);

	AppendStudent(student);
}

void SearchStudents(Student* students, int amount)
{
	std::string searchName;
	std::string searchId = "";
	std::string searchNationalId = "";
	std::string searchPhoneNumber = "";
	std::cin.ignore();
	std::cout << "Enter Name (enter 0 to ignore): \n";
	std::getline(std::cin,searchName,'\n');
	while (searchName != "0" && !ValidateName(searchName.c_str()))
	{
		std::cout << "Invalid NAME [" << searchName << "]. format [FirstName] [LastName] or enter back to continue\n";
		std::cout << "Enter Name: ";
		std::getline(std::cin,searchName,'\n');
		if (searchName == "back")
		{
			std::cout << "Going back to menu...\n";
			PressEnterPause();
			return;
		}
	}
	std::cout << "Enter ID (enter 0 to ignore): \n";
	std::cin >> searchId;
	while (searchId != "0" && !ValidateStudentId(searchId.c_str()))
	{
		std::cout << "Invalid ID [" << searchId << "]. format 25PXXXX or enter back to continue\n";
		std::cout << "Enter ID: ";
		std::cin >> searchId;
		if (searchId == "back")
		{
			std::cout << "Going back to menu...\n";
			PressEnterPause();
			return;
		}
	}
	
	std::cout << "Enter NationalID (enter 0 to ignore): \n";
	std::cin >> searchNationalId;
	while (searchNationalId != "0" && !ValidateNationalId(searchNationalId.c_str()))
	{
		std::cout << "Invalid NationalID [" << searchNationalId << "].Enter "<<NATIONAL_ID_LENGTH<<" digits or enter back to continue\n";
		std::cout << "Enter NationalID: ";
		std::cin >> searchNationalId;
		if (searchNationalId == "back")
		{
			std::cout << "Going back to menu...\n";
			PressEnterPause();
			return;
		}
	}
	std::cout << "Enter phoneNumber (enter 0 to ignore): \n";
	std::cin >> searchPhoneNumber;
	while (searchPhoneNumber != "0" && !ValidatePhoneNumber(searchPhoneNumber.c_str()))
	{
		std::cout << "Invalid PhoneNumber [" << searchPhoneNumber << "]. format 01 + 9 digits or enter back to continue\n";
		std::cout << "Enter phone number: ";
		std::cin >> searchPhoneNumber;
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
			PrintStudent(students[i]);
			countFound++;
		}
	}
	if (countFound == 0)
	{
		std::cout << "No Students where found with criteria\n";
	}
	PressEnterPause();
	
}
void DeleteStudent(Student* students, int* amount)
{
	for (int i = 0; i < *amount; i++)
	{
		std::cout << (i + 1) << ") " << students[i].Id << " - " << students[i].Name << '\n';
	}
	int index = -1;
	while (index < 0 || index > *amount)
	{
		std::cout << "Enter index(" << 1 << "-" << *amount << ") or zero to exit: ";
		std::cin >> index;
	}
	index--;
	if (index >= 0)
	{
		DeleteStudent(index, students, amount);
	}
}
void UpdateStudent(Student* students, int amount)
{
	for (int i = 0; i < amount; i++)
	{
		std::cout << (i + 1) << ") " << students[i].Id << " - " << students[i].Name << '\n';
	}
	int index = -1;
	while (index < 0 || index > amount)
	{
		std::cout << "Enter index(" << 1 << "-" << amount << ") or zero to exit: ";
		std::cin >> index;
	}
	index--;
	std::string newName;
	std::string newPhone;
	Programs program = MCTA;
	int level;

	std::cin.ignore();
	std::cout << "Enter new name or 0 to skip: ";
	std::getline(std::cin, newName);

	if (newName == "0")
		newName = students[index].Name;
	std::cin.ignore();
	std::cout << "Enter new Phone number or 0 to skip: ";
	std::cin >> newPhone;

	if (newPhone == "0")
		newPhone = students[index].PhoneNumber;

	std::cin.ignore();
	std::cout << "do you want to change program(Y/N): ";
	if (tolower(std::cin.get()) == 'y')
		program = GetProgram();

	std::cin.ignore();
	std::cout << "Enter new level or 0 to skip: ";
	std::cin >> level;


	if (index >= 0)
		UpdateStudent(&students[index], newName.c_str(), newPhone.c_str(), program, level);
}
int StudentManagementMenu() {//studmng menu


	int choice = 0;

	while (choice != 6) {
		system("cls");
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
			AddNewStudent(students, amount);
			break;
		case 2:
			SearchStudents(students, amount);
			break;
		case 3:UpdateStudent(students, amount);
			break;
		case 4: DeleteStudent(students, &amount);
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
			SaveStudents(students, amount);
		}delete[] students;

	}

	return choice;
}

int CourseManagementMenu() {//course management menu
	for (int i = 0; i < 3; i++) cout << "=";
	cout << " " << "Course Management" << " ";
	for (int i = 0; i < 3; i++) cout << "=";
	cout << '\n' << '\n';
	cout << "1. Add New Course" << '\n' << "2. View All Courses" << '\n' << "3. Update Course" << '\n' << "4. Delete Course" << '\n';;
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

int MainMenu() {//main menu func
	int choice;
	bool valid = false;
	//int studmngout = studmng();

	//validation of choice starts here
	while (!valid) {
		DisplayTitle("Student information system");
		cout << "1. Student Management" << '\n' << "2. Course Management" << '\n' << "3. Grades Management" << '\n' << "4. Exit";
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
		case 4:cout << "Exiting, thank you for using the program." << '\n';
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
	bool isrunning = true;

	while (isrunning) {
		int menuStatus = MainMenu();

		std::cout << '\n';
		if (menuStatus == -1) isrunning = false;




	}




	return 0;
}
