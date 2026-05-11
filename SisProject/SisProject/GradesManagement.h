#pragma once
#include "StudentManagement.h"
#include "CourseManagement.h"

#include <fstream>
#include <iostream>
#include <string>
using namespace std;


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
void AppendGrade(const Grade* grade);
void CreateGradesFile();
//MUST FREE MEMORY Grades at the end
Grade* LoadGrades(int* amount);


void AddGrade(Grade* grades,int amount);
void UpdateGrade(Grade* grades, int amount);
void DeleteGrade(Grade* grades, int* amount);
void ShowGrades(Grade* grades, int amount);

double CalculateGpa(std::string studentid, Grade* grades, int amount);
void GenerateTranscript(Grade* grades, int amount);

void DeleteGradeByStudentId(Grade* grades, const char* studentId, int* amount);
void DeleteGradeByCourseId(Grade* grades, const char* courseId, int* amount);
