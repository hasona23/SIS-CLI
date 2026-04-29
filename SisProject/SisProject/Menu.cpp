#include "Menu.h"

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
	std::cout << "Birthdate    : " << s.DayBirth << "/" << s.MonthBirth << "/" << s.YearBirth << "\n";
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
}

void AddNewStudent(Student* students, int amount)
{
	Student student{};
	while (!ValidateStudent(student))
	{
		std::string firstName = "";
		std::string secondName = "";
		std::cin.ignore();
		std::cout << "Enter student first name: ";
		std::cin >> firstName;
		std::cin.ignore();
		std::cout << "Enter student second name: ";
		std::cin >> secondName;

		std::string fullName = firstName + " " + secondName;
		strncpy(student.Name, fullName.c_str(), MAX_NAME_LENGTH);
		student.Name[MAX_NAME_LENGTH] = '\0';
		std::cout << std::endl;
		std::cout << "Enter Student Id: ";
		std::cin >> setw(ID_LENGTH+1) >> student.Id;
		bool returnToLoop = false;
		for (int i = 0; i < amount; i++)
		{
			if (strcmp(student.Id, students[i].Id) == 0)
			{
				std::cout << "ID Already exist!\n";
				returnToLoop = true;
				break;
			}
		}
		if (returnToLoop)
			continue;
		std::cin.ignore();
		std::cout << "Enter phone number: ";
		std::cin >>std::setw(PHONE_NUM_LENGTH+1) >> student.PhoneNumber;
		std::cin.ignore();
		std::cout << "Enter national ID: ";
		std::cin >> std::setw(NATIONAL_ID_LENGTH+1) >> student.NationalId;
		
		for (int i = 0; i < amount; i++)
		{
			if (strcmp(student.NationalId, students[i].NationalId) == 0)
			{
				std::cout << "National Id Already exist!\n";
				returnToLoop = true;
				break;
			}
		}
		if (returnToLoop)
			continue;
		std::cin.ignore();
		std::cout << "Enter Gender(" << MALE_GENDER << " - " << FEMALE_GENDER << "): ";
		std::cin >> std::setw(1) >> student.Gender;

		std::cout << "Enter student level: ";
		std::cin >> student.Level;

		student.Gpa = 0.0;

		student.Program = GetProgram();

		std::cout << "Enter birth date day , month , year";
		std::cin >> student.DayBirth >> student.MonthBirth >> student.YearBirth;
		std::cin.ignore();
	}
	AppendStudent(student);
}

void SearchStudents(Student* students, int amount)
{
	std::string searchName = "";
	std::string searchId = "";
	std::string searchNationalId = "";
	std::string searchPhoneNumber = "";

	std::cout << "Enter Id (enter 0 to ignore): \n";
	std::cin >> searchId;
	std::cout << "Enter name (enter 0 to ignore): \n";
	std::cin >> searchName;
	std::cout << "Enter NationalId (enter 0 to ignore): \n";
	std::cin >> searchNationalId;
	std::cout << "Enter phoneNumber (enter 0 to ignore): \n";
	std::cin >> searchPhoneNumber;
	std::cout << "Amount: " << amount << '\n';
	for (int i = 0; i < amount; i++)
	{
		bool nameFilter = (searchName=="0" || (searchName == students[i].Name));
		bool idFilter = (searchId=="0" || (searchId == students[i].Id));
		bool phoneFilter = (searchPhoneNumber == "0"  || (searchPhoneNumber == students[i].PhoneNumber));
		bool nationalIdFilter = (searchNationalId=="0" || (searchNationalId == students[i].NationalId));
		if (nameFilter && idFilter && phoneFilter && nationalIdFilter)
			PrintStudent(students[i]);
	}
	std::cout << "Press Enter to conitnue..";
	while(std::cin.get()!='\n')
	{
	}
	std::cin.ignore();
}
void DeleteStudent(Student* students, int amount)
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
	if (index >= 0)
		DeleteStudent(index, students, amount);
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
	Programs program;
	int level;

	std::cin.ignore();
	std::cout << "Enter new name or 0 to skip: ";
	std::cin >> newName;

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
	for (int i = 0; i < 3; i++) cout << "=";
	cout << " " << "Student Management" << " ";
	for (int i = 0; i < 3; i++) cout << "=";
	cout << '\n' << '\n';
	cout << "1. Add New Student" << '\n' << "2. Search Student" << '\n' << "3. Update Student" << '\n' << "4. Delete Student" << '\n';
	cout << "5. List All Student" << '\n' << "6. Back to Main Menu";
	cout << '\n' << '\n';

	int choice = 0;

	while (choice != 6) {
		cout << "Enter your choice: ";
		cin >> choice;
		Student* students;
		int amount = 0;
		if (choice >= 1 && choice <= 5)
		{
			students = LoadStudents(&amount);
		}
		switch (choice) {
		case 1:
			AddNewStudent(students,amount);
			break;
		case 2:
			SearchStudents(students, amount);
			break;
		case 3:UpdateStudent(students, amount);
			break;
		case 4: DeleteStudent(students, amount);
			break;
		case 5: ListStudents(students, amount); 
			break;
	
		default:cout << "Invalid input, please try again" << '\n';
			choice = 0;
		}
		if (choice >= 1 && choice <= 5)
		{
			SaveStudents(students,amount);
			delete[] students;
		}
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
	DisplayTitle("Student information system");
	cout << "1. Student Management" << '\n' << "2. Course Management" << '\n' << "3. Grades Management" << '\n' << "4. Exit";
	cout << '\n' << '\n';
	//validation of choice starts here
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

int RunSis() { //should be the main func ultimately
	int mmchoice = 0; int smchoice = 0; int cmchoice = 0; int gmchoice = 0; bool isrunning = true;

	while (isrunning) {
		mmchoice = MainMenu();
		std::cout << '\n';
		if (mmchoice == -1) return 0;
		if (mmchoice == 1) {
			smchoice = StudentManagementMenu();


		}
		else if (mmchoice == 2) {
			cmchoice = CourseManagementMenu();
		}
		else if (mmchoice == 3) { gmchoice = GradesManagementMenu(); }


		system("cls");
	}




	return 0;
}
