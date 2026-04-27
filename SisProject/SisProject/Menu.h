#pragma once

# include <iostream>,<conio.h>,<cstring>,<iomanip>
using namespace std;
/* strlen() char centered + a tab on both sides which is 14*/
inline int mainMenu();
inline void Indent(int amount)
{
	for (int i = 0; i < amount; i++)
		std::cout << ' ';
}
inline void menuTitleBig(const char title[]) { //main menu title +box function
	char tlc = 201, trc = 187, vl = 186, hl = 205, blc = 200, brc = 188;
	int space = 7;
	int length = strlen(title);
	Indent(40);
	cout << tlc;
	for (int i = 0; i < 14 + length; i++) 
		cout << hl;
	cout << trc << endl;
	Indent(40);
	std::cout << vl;
	for (int i = 0; i < 7; i++)
		cout << " ";
	cout << title;
	for (int i = 0; i < 7; i++) 
		cout << " ";
	cout << vl << endl;
	Indent(40);
	std::cout<<	blc;
	for (int i = 0; i < 14 + length; i++) 
		cout << hl;
	cout << brc << endl << endl;
}

inline int studmng() {//studmng menu
	for (int i = 0; i < 3; i++) cout << "=";
	cout << " " << "Student Management" << " ";
	for (int i = 0; i < 3; i++) cout << "=";
	cout << endl << endl;
	cout << "1. Add New Student" << endl << "2. Search Student" << endl << "3. Update Student" << endl << "4. Delete Student" << endl;
	cout << "5. List All Student" << endl << "6. Back to Main Menu";
	cout << endl << endl;

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
		case 5: valid = true; break;
		case 6: return -1;
		default:cout << "Invalid input, please try again" << endl;
			valid = false;
			choice = 0;
		}

	}

	return choice;
}
inline int coursemng() {//course management menu
	for (int i = 0; i < 3; i++) cout << "=";
	cout << " " << "Course Management" << " ";
	for (int i = 0; i < 3; i++) cout << "=";
	cout << endl << endl;
	cout << "1. Add New Course" << endl << "2. View All Courses" << endl << "3. Update Course" << endl << "4. Delete Course" << endl;;
	cout << "5. Back to Main Menu";
	cout << endl << endl;

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
			cout << "Invalid input, please try again" << endl;
			valid = false;

		}

	}

	return choice;


}
inline int main2() {//grades mng menu
	for (int i = 0; i < 3; i++) cout << "=";
	cout << " " << "Grades Management" << " ";
	for (int i = 0; i < 3; i++) cout << "=";
	cout << endl << endl;
	cout << "1. Enter Student Grades" << endl << "2. View Student Grades" << endl << "3. Calculate GPA" << endl << "4. Generate Transcript" << endl;;
	cout << "5. Back to Main Menu";
	cout << endl << endl;

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
			cout << "Invalid input, please try again" << endl;
			valid = false;

		}

	}

	return choice;




}



inline int mainMenu() {//main menu func
	int choice;
	bool valid = false;
	//int studmngout = studmng();
	menuTitleBig("Student information system");
	cout << "1. Student Management" << endl << "2. Course Management" << endl << "3. Grades Management" << endl << "4. Exit";
	cout << endl << endl;
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
		case 4:cout << "Exiting, thank you for using the program." << endl;
			return 0;
		default:choice = 0;
			cout << "Invalid input, please try again" << endl;
			valid = false;

		}

	}


	return choice;
}
inline int wmain() { //should be the main func ultimately
	int mainmenuout = mainMenu();
	//studmng();
	if (mainmenuout == 0) return 0;
	if (mainmenuout == 1) {

	}
	return 0;
}

/*Thoughts:
we must call submenus within the mainmenu func in order to ensure that we can switch among menus easily, this will probably need recursion*/