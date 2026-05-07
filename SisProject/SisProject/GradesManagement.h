#pragma once
#include "StudentManagement.h"
#include "CourseManagement.h"

static const char* GRADES_FILE_PATH = "./grades.txt";

struct Grade
{
	char StudentId[STUDENT_ID_LENGTH + 1] = "";
	char CourseId[COURSE_ID_LENGTH + 1] = "";
	//Midterm out of 40
	int MidTerm = 0;
	//Final out of 60
	int Final = 0;
};


//FILE IO =====================================================
void SaveGrades(const Grade* grades, int amount);
void AppendGrade(const Grade* grades);
void CreateGradesFile();
//MUST FREE MEMORY Grades at the end
Grade* LoadGrades(int* amount);