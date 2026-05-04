#pragma once

static const int COURSE_ID_LENGTH = 6;
static const int MAX_COURSE_TITLE_LENGTH = 128;
static const char* COURSES_FILE_PATH = "./courses.txt";

struct Course
{
public:
	char ID[6 + 1] = "";
	char Title[MAX_COURSE_TITLE_LENGTH + 1] = "";
	int CreditHours = 1;
};



//FILE IO =====================================================
void SaveCourses(const Course* courses, int amount);
void AppendCourse(const Course* course);
void CreateCoursesFile();
Course* LoadCourses(int* amount);