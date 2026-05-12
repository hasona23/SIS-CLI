#include "Menu.h"
#include "GradesManagement.h"
#include <string>
#include "Utils.h"






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
		cout << "1. Student Management" << '\n' << "2. Course Management" << '\n' << "3. Grades Management" << '\n' << "4. User Manual" << '\n' << "0. Exit";
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
		valid = true;
		switch (choice) {
		case 1:
			StudentManagementMenu();
			break;
		case 2:
			CourseManagementMenu();
			break;
		case 3:
			GradesManagementMenu();
			break;
		case 4:
			HelpMenu();
			break;
		case 0:
			cout << "Exiting, thank you for using the program." << '\n';
			return -1;
		default:
			choice = -1;
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