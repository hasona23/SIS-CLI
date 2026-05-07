#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>,<conio.h>,<cstring>
#include <iomanip>
#include "StudentManagement.h"

using namespace std;
/* strlen() char centered + a tab on both sides which is 14*/


static const char ASCII_BOTTOM_RIGHT_CORNER = 188;
static const char ASCII_TOP_LEFT_CORNER = 201;
static const char ASCII_TOP_RIGHT_CORNER = 187;
static const char ASCII_VERTICAL_LINE = 186;
static const char ASCII_HORIZONTAL_LINE = 205;
static const char ASCII_BOTTOM_LEFT_CORNER = 200;

//Displays the bordered title using ASCII Art
void DisplayTitle(const char title[]);

Programs GetProgram();
int MainMenu();
void PrintStudent(const Student s);

void ListStudents(Student* students, int amount);
void AddNewStudent(Student* students, int amount);
void SearchStudents(Student* students, int amount);
void DeleteStudent(Student* students, int *amount);
void UpdateStudent(Student*students,int amount);
int StudentManagementMenu();
int CourseManagementMenu();
int GradesManagementMenu();

int RunSis();













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