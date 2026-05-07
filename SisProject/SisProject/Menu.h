#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>,<conio.h>,<cstring>
#include <iomanip>
#include "StudentManagement.h"
#include "CourseManagement.h"
using namespace std;
/* strlen() char centered + a tab on both sides which is 14*/




//Displays the bordered title using ASCII Art

Programs GetProgram();
int MainMenu();
void PrintStudent(const Student* s);

void ListStudents(Student* students, int amount);
void AddStudentMenu(Student* students, int amount);
void SearchStudents(Student* students, int amount);
void DeleteStudentMenu(Student* students, int *amount);
void UpdateStudentMenu(Student*students,int amount);
int StudentManagementMenu();
int CourseManagementMenu();
int GradesManagementMenu();
void addCourse();
int RunSis();
void DeleteCourseMenu(Course* courses, int* amount);
void DeleteCourse(int index, Course* courses, int* amount);











/*
Thoughts:
we must call submenus within the mainmenu func in order to ensure that we can switch among menus easily,
this will probably need recursion
go back to main menu---- initiate mainmenu func
main menu func should have the ability to call all submenu func within it
calling based on choice value
program terminates only with the exit command in main menu ****
after each operation, you're sent back to main menu by default (cancelled, would've been a nightmare on the memory)

Logic reworked:
Call each function within a while loop, once the option for a function is chosen, initiate that function.
if go back to main menu is chosen, terminate the submenu function. This will instantly make the code hop back
to the while loop. Make sure a new iteration starts whenever you terminate a submenu function, so as to ensure
that the while loop restarts and prints the main menu again

*/