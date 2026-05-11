#include "GradesManagement.h"
#include "Utils.h"
using namespace std;


void CreateGradesFile()
{
	std::fstream file;
	//creates file
	file.open(GRADES_FILE_PATH, std::ios::app);

	if (!file.is_open())
	{
		std::cout << "FAILED TO CREATE GRADES FILE\n";
		std::cout << "Press enter to exit...";
		std::cin.get();
		std::exit(1);
	}

}

static void WriteGradeToFile(const Grade* grade, std::ofstream& file)
{
	file << "[----]\n";
	file << grade->StudentId << '\n';
	file << grade->CourseId << '\n';
	file << grade->MidTerm << '\n';
	file << grade->Final << '\n';
	file << "[----]\n";
}

void SaveGrades(const Grade* grades, int amount)
{
	std::ofstream file;
	file.open(GRADES_FILE_PATH, std::ios::trunc);
	if (file.is_open())
	{
		for (int i = 0; i < amount; i++)
			WriteGradeToFile(&grades[i], file);
		file.close();
	}
	else
	{
		std::cout << "Failed to open file. press enter to continue";
		std::cin.get();
	}
}
void AppendGrade(const Grade* grade)
{
	std::ofstream file;
	file.open(GRADES_FILE_PATH, std::ios::app);
	if (file.is_open()) {
		WriteGradeToFile(grade, file);
	}
	else
		std::cout << "Failed to write grade to file";
}
Grade* LoadGrades(int* amount)
{
	std::ifstream file;
	file.open(GRADES_FILE_PATH);

	char buffer[512 + 1];
	*amount = 0;
	bool IsReadingGrade = false;
	if (file.is_open())
	{

		int separators = 0;
		while (file.getline(buffer, 512))
		{
			if (strcmp("[----]", buffer) == 0) {
				separators++;

			}

		}

		//rests the file read pointer

		//seperators are double the amout of students
		separators /= 2;

		*amount = separators;
		Grade* grades = new Grade[*amount];
		int i = 0;
		
		file.clear();
		file.seekg(0, std::ios::beg);
		while (file.getline(buffer, 512))
		{
			//std::cout << "BUFF: " << buffer << '\n';

			if (strcmp(buffer, "[----]") == 0)
			{
				IsReadingGrade = !IsReadingGrade;
			}
			if (IsReadingGrade)
			{
				file.getline(buffer, 512);
				strncpy_s(grades[i].StudentId, buffer,STUDENT_ID_LENGTH);
				//grades[i].StudentId[STUDENT_ID_LENGTH] = '\0';
				
				file.getline(buffer, 512);
				strncpy_s(grades[i].CourseId, buffer, COURSE_ID_LENGTH);
				//grades[i].CourseId[COURSE_ID_LENGTH] = '\0';
				
				file.getline(buffer, 512);
				grades[i].MidTerm = atoi(buffer);
				
				file.getline(buffer,512);
				grades[i].Final = atoi(buffer);

				i++;
			}
		}

		file.close();

		return grades;
	}
	else {
		std::cout << "Error Opening file to load\n";
		return nullptr;
	}
}


static bool StudentExists(const char* studentId, Student* students, int amount)
{
	for (int i = 0; i < amount; i++)
	{
		if (strcmp(students[i].Id, studentId) == 0)
		{
			return true;
		}
	}
	return false;
}
static bool CourseExists(const char* courseId, Course* courses, int amount)
{
	for (int i = 0; i < amount; i++)
	{
		if (strcmp(courses[i].Id, courseId) == 0)
		{
			return true;
		}
	}
	return false;
}

void AddGrade(Grade* grades, int amount)
{
    Grade g;

    cout << "\n=======Enter Student Grades========\n";
	int studentsAmount = 0;
	Student* students = LoadStudents(&studentsAmount);

	int coursesAmount = 0;
	Course* courses = LoadCourses(&coursesAmount);
    cout << "Enter Student id: ";
    cin >> g.StudentId;
	toUpper(g.StudentId);
	while (!StudentExists(g.StudentId, students, studentsAmount))
	{
		cout << "Student with id " << g.StudentId << " not found. Please enter a valid student id.\n";
		cout << "Enter Student id (back to exit): ";
		cin >> g.StudentId;
		toUpper(g.StudentId);
		if (g.StudentId == "BACK")
		{
			cout << "Going back to menu...\n";
			return;
		}
	}
    cout << "Enter Course code: ";
    cin >> g.CourseId;
	toUpper(g.CourseId);
	while (!CourseExists(g.CourseId, courses, coursesAmount))
	{
		cout << "Course with code " << g.CourseId << " not found. Please enter a valid course code.\n";
		cout << "Enter Course code (back to exit): ";
		cin >> g.CourseId;
		toUpper(g.CourseId);
		if (g.CourseId == "BACK")
		{
			cout << "Going back to menu...\n";
			return;
		}
	}
	for (int i = 0; i < amount; i++)
	{
		if (strcmp(g.CourseId, grades[i].CourseId) == 0 && strcmp(g.StudentId, grades[i].StudentId) == 0)
		{
			cout << "Grades for student " << g.StudentId << " in course " << g.CourseId << " already exist. Please use update grade option to change the grade.\n";
			PressEnterPause();
			return;
		}
	}
    do
    {
        cout << "Enter Midterm Grade(0:40): ";
        cin >> g.MidTerm;

        if (g.MidTerm < 0 || g.MidTerm > 40)
        {
            cout << "Invalid Midterm Grade!\n";
        }

    } while (g.MidTerm < 0 || g.MidTerm > 40);

    do
    {
        cout << "Enter Final Grade(0:60): ";
        cin >> g.Final;

        if (g.Final < 0 || g.Final > 60)
        {
            cout << "Invalid Final Grade!\n";
        }

    } while (g.Final < 0 || g.Final > 60);

	AppendGrade(&g);

    int total = g.MidTerm + g.Final;
	cout << "\n=======Grade Summary========\n";
	cout << "Student ID = " << g.StudentId << '\n';
	cout << "Course ID = " << g.CourseId << '\n';
	cout << "Midterm = " << g.MidTerm << "/40 \n";
	cout << "Final = " << g.Final << "/60 \n";
	cout << "The Toltal = " << total << "/100 \n";
    cout << "Garde Added Successfully\n";
	PressEnterPause();
}

void UpdateGrade(Grade* grades,int amount) {
	std::string studentId, courseId;
	for (int i = 0; i < amount; i++)
	{
		std::cout << (i + 1) << ") " << grades[i].StudentId << " - " << grades[i].CourseId << " -> "<<grades[i].MidTerm<<" - "<<grades[i].Final << '\n';
	}

	cout << "Enter Student ID: ";
	cin >> studentId;
	toUpper(studentId.data());
	cout << "Enter Course ID: ";
	cin >> courseId;
	toUpper(courseId.data());

	bool found = false;

	for (int i = 0; i < amount; i++) {

		if (grades[i].StudentId == studentId &&grades[i].CourseId==courseId)
		{
			
			do {
				std::cout << "Enter New Midterm Grade (0 - 40): ";
				cin >> grades[i].MidTerm;
			} while (grades[i].MidTerm < 0 || grades[i].MidTerm > 40);

			do {
				std::cout << "Enter New Final Grade (0 - 60): ";
				cin >> grades[i].Final;
			} while (grades[i].Final < 0 || grades[i].Final > 60);
			

			found = true;
			break;
		}
	}

	if (!found) {
		std::cout << "Grade record not found." << '\n';
		PressEnterPause();
	}
}
void ShowGrades(Grade* grades, int amount) {
	if (amount == 0) {
		cout << endl << "No grades registered. Press ENTER to continue....";
		cin.ignore();
		cin.get();
		return;
	}
	std::string studentId, courseId;
	do {
		std::cout << "Enter Student ID to filter (or 0 to skip): ";
		std::cin >> studentId;
	} while (!ValidateStudentId(studentId.c_str()) && studentId != "0");
	do {
		std::cout << "Enter Course ID to filter (or 0 to skip): ";
		std::cin >> courseId;
	} while (!ValidateCourseId(courseId.data()) && courseId != "0");

	for (int i = 0; i < amount; i++)
	{
		bool matchesStudent = (studentId == "0" || grades[i].StudentId == studentId);
		bool matchesCourse = (courseId == "0" || grades[i].CourseId == courseId);
		if (matchesStudent && matchesCourse)
			std::cout << (i + 1) << ") " << grades[i].StudentId << " - " << grades[i].CourseId << " -> " << grades[i].MidTerm << " - " << grades[i].Final << '\n';
	}
	PressEnterPause();
}
static void DeleteGradeAtIndex(Grade* grades, int index, int* amount) {
	for (int i = index; i < *amount - 1; i++) {
		grades[i] = grades[i + 1];
	}
	(*amount)--;
}
void DeleteGradeByStudentId(Grade* grades, const char* studentId, int* amount) {
	for (int i = 0; i < *amount; i++) {
		if (strcmp(grades[i].StudentId, studentId) == 0) {
			DeleteGradeAtIndex(grades, i, amount);
			i--;
		}
	}
}
void DeleteGradeByCourseId(Grade* grades, const char* courseId, int* amount) {
	for (int i = 0; i < *amount; i++) {
		if (strcmp(grades[i].CourseId, courseId) == 0) {
			DeleteGradeAtIndex(grades, i, amount);
			i--;
		}
	}
}
void DeleteGrade(Grade* grades,int* amount) {
	std::string studentId, courseId;
	cout << "Enter Student ID to delete: ";
	cin >> studentId;
	toUpper(studentId.data());
	cout << "Enter Course ID to delete: ";
	cin >> courseId;
	toUpper(courseId.data());

	int foundIndex = -1;

	for (int i = 0; i < *amount; i++) {
		if (grades[i].StudentId == studentId && grades[i].CourseId == courseId) {
			foundIndex = i;
			break;
		}
	}

	if (foundIndex != -1) {

		DeleteGradeAtIndex(grades, foundIndex, amount);
		cout << "Grade deleted successfully." << endl;
	}
	else {
		cout << "Record not found." << endl;
	}
}

/////////////////////////////////////////////////////

double CalculateGpa(std::string studentId, Grade* grades, int amount)
{
    int coursesAmount = 0;

	double totalGrades = 0;
	double totalHours = 0;

	Course* courses = LoadCourses(&coursesAmount);

    for (int i = 0; i < amount; i++)
    {
        if (grades[i].StudentId == studentId)
        {
			Course* course = nullptr;
			for (int i = 0; i < coursesAmount; i++)
			{
				if (strcmp(courses[i].Id, grades[i].CourseId) == 0)
				{
					course = &courses[i];
					break;
				}
			}
			if (course == nullptr)
			{
				std::cout << "Error calculating GPA. Course with code " << grades[i].CourseId << " not found.\n";
				PressEnterPause();
				return -1;
			}
            int total = grades[i].MidTerm + grades[i].Final;
			totalGrades += total * course->CreditHours;
			totalHours += course->CreditHours;
        }
    }
    if (totalHours == 0)
    {
        return 0;
    }
    return totalGrades/totalHours;
}

/////////////////////////////////////////////////////////////

void GenerateTranscript(Grade* grades, int amount)
{
    std::string studentid;
	
    std::cout << "\nEnter Student ID: ";
    std::cin >> studentid;
	toUpper(studentid.data());
    std::cout << "\n====STUDENT TRANSCRIPT====\n";

    for (int i = 0; i < amount; i++)
    {
        if (grades[i].StudentId == studentid)
        {
            int total = grades[i].MidTerm + grades[i].Final;
			std::cout << "-------------------\n";
			std::cout << "course code: " << grades[i].CourseId<<'\n';
           std::cout << "Midterm: " << grades[i].MidTerm << '\n';
           std::cout << "Final exam: " << grades[i].Final << '\n';
           std::cout << "Total: " << total << '\n';
           std::cout << "--------------------\n";
        }
    }
	std::cout << "\nGPA = " << CalculateGpa(studentid,grades,amount) << '\n';
	PressEnterPause();
	
}


