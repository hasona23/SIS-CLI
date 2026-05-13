#include "GradesManagement.h"
#include "Utils.h"

using namespace std;

std::string GetGpaLetter(int totalGrade)
{
	if (totalGrade >= 97)
		return "A+";
	else if (totalGrade >= 93)
		return "A";
	else if (totalGrade >= 90)
		return "A-";
	else if (totalGrade >= 87)
		return "B+";
	else if (totalGrade >= 83)
		return "B";
	else if (totalGrade >= 80)
		return "B-";
	else if (totalGrade >= 77)
		return "C+";
	else if (totalGrade >= 73)
		return "C";
	else if (totalGrade >= 70)
		return "C-";
	else if (totalGrade >= 67)
		return "D+";
	else if (totalGrade >= 65)
		return "D";
	else
		return "F";
}
float GetGpaGrade(int totalGrade)
{
	return (totalGrade / 100.0) * 4.0;
}

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
				strncpy_s(grades[i].StudentId, buffer, STUDENT_ID_LENGTH);
				//grades[i].StudentId[STUDENT_ID_LENGTH] = '\0';

				file.getline(buffer, 512);
				strncpy_s(grades[i].CourseId, buffer, COURSE_ID_LENGTH);
				//grades[i].CourseId[COURSE_ID_LENGTH] = '\0';

				file.getline(buffer, 512);
				grades[i].MidTerm = atoi(buffer);

				file.getline(buffer, 512);
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
	Grade grade;

	cout << "\n=======Enter Student Grades========\n";
	int studentsAmount = 0;
	Student* students = LoadStudents(&studentsAmount);
	if (studentsAmount == 0)
	{
		std::cout << "No students registered. Please add students before adding grades.\n";
		PressEnterPause();
		delete[] students;
	}
	int coursesAmount = 0;
	Course* courses = LoadCourses(&coursesAmount);
	if (coursesAmount == 0)
	{
		std::cout << "No courses registered. Please add courses before adding grades.\n";
		PressEnterPause();
		delete[] students;
		delete[] courses;
		return;
	}
	cout << "Enter Student id: ";
	cin >> grade.StudentId;
	RemoveSpaces(grade.StudentId);
	toUpper(grade.StudentId);
	while (!StudentExists(grade.StudentId, students, studentsAmount))
	{
		cout << "Student with id " << grade.StudentId << " not found. Please enter a valid student id.\n";
		cout << "Enter Student id (back to exit): ";
		cin >> grade.StudentId;
		RemoveSpaces(grade.StudentId);
		toUpper(grade.StudentId);
		if (strcmp(grade.StudentId, "BACK") == 0)
		{
			cout << "Going back to menu...\n";
			delete[] students;
			delete[] courses;
			return;
		}
	}
	cout << "Enter Course code: ";
	cin >> grade.CourseId;
	RemoveSpaces(grade.CourseId);
	toUpper(grade.CourseId);
	while (!CourseExists(grade.CourseId, courses, coursesAmount))
	{
		cout << "Course with code " << grade.CourseId << " not found. Please enter a valid course code.\n";
		cout << "Enter Course code (back to exit): ";
		cin >> grade.CourseId;
		RemoveSpaces(grade.CourseId);
		toUpper(grade.CourseId);
		if (strcmp(grade.CourseId, "BACK") == 0)
		{
			cout << "Going back to menu...\n";
			delete[] courses;
			delete[] students;
			return;
		}
	}
	for (int i = 0; i < amount; i++)
	{
		if (strcmp(grade.CourseId, grades[i].CourseId) == 0 && strcmp(grade.StudentId, grades[i].StudentId) == 0)
		{
			cout << "Grades for student " << grade.StudentId << " in course " << grade.CourseId << " already exist. Please use update grade option to change the grade.\n";
			PressEnterPause();
			delete[] students;
			delete[] courses;
			return;
		}
	}
	do
	{
		cout << "Enter Midterm Grade(0:40): ";
		cin >> grade.MidTerm;

		if (grade.MidTerm < 0 || grade.MidTerm > 40)
		{
			cout << "Invalid Midterm Grade!\n";
		}

	} while (grade.MidTerm < 0 || grade.MidTerm > 40);

	do
	{
		cout << "Enter Final Grade(0:60): ";
		cin >> grade.Final;

		if (grade.Final < 0 || grade.Final > 60)
		{
			cout << "Invalid Final Grade!\n";
		}

	} while (grade.Final < 0 || grade.Final > 60);

	AppendGrade(&grade);

	int total = grade.MidTerm + grade.Final;
	cout << "\n=======Grade Summary========\n";
	cout << "Student ID = " << grade.StudentId << '\n';
	cout << "Course ID = " << grade.CourseId << '\n';
	cout << "Midterm = " << grade.MidTerm << "/40 \n";
	cout << "Final = " << grade.Final << "/60 \n";
	cout << "The Toltal = " << total << "/100 \n";
	std::cout << "GPA = " << GetGpaGrade(total) << " / 4.0 \n";
	cout << "Grade = " << GetGpaLetter(total) << '\n';
	cout << "Garde Added Successfully\n";
	PressEnterPause();
	delete[] students;
	delete[] courses;
}

void UpdateGrade(Grade* grades, int amount) {
	if (amount == 0)
	{
		cout << endl << "No grades registered. Press ENTER to continue....";
		cin.ignore();
		cin.get();
		return;
	}
	std::string studentId, courseId;
	for (int i = 0; i < amount; i++)
	{
		std::cout << (i + 1) << ") " << grades[i].StudentId << " - " << grades[i].CourseId << " -> " << grades[i].MidTerm << " - " << grades[i].Final << '\n';
	}

	cout << "Enter Student ID: ";
	cin >> studentId;
	RemoveSpaces(studentId.data());
	toUpper(studentId.data());

	int studentsCount = 0;
	Student* students = LoadStudents(&studentsCount);
	while (!StudentExists(studentId.c_str(), students, studentsCount))
	{
		std::cout << "Student Id " << studentId << " Not found. Please enter valid student ID or back to exit: ";
		cin >> studentId;
		RemoveSpaces(studentId.data());
		toUpper(studentId.data());
		if (studentId == "BACK")
		{
			std::cout << "Going back to menu...\n";
			delete[] students;
			return;
		}
	}
	delete[] students;
	cout << "Enter Course ID: ";
	cin >> courseId;
	RemoveSpaces(courseId.data());
	toUpper(courseId.data());
	int coursesCount = 0;
	Course* courses = LoadCourses(&coursesCount);
	while (!CourseExists(courseId.c_str(), courses, coursesCount))
	{
		std::cout << "Course ID " << courseId << " doesnt exist. Enter valid course ID or back to exit: ";
		cin >> courseId;
		RemoveSpaces(courseId.data());
		toUpper(courseId.data());
		if (courseId == "BACK")
		{
			std::cout << "Going back to menu...\n";
			delete[] courses;
			return;
		}
	}
	delete[] courses;
	bool found = false;

	for (int i = 0; i < amount; i++) {

		if (grades[i].StudentId == studentId && grades[i].CourseId == courseId)
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

	std::cout << "Enter Student ID to filter (or 0 to skip): ";
	std::cin >> studentId;
	RemoveSpaces(studentId.data());
	toUpper(studentId.data());
	int studentsAmount = 0;
	Student* students = LoadStudents(&studentsAmount);
	while (!StudentExists(studentId.c_str(), students, studentsAmount) && studentId != "0")
	{
		std::cout << "Student Id " << studentId << " Not found. Please enter valid student ID or 0 to skip: ";

		std::cin >> studentId;
		RemoveSpaces(studentId.data());
		toUpper(studentId.data());
	}
	delete[] students;
	std::cout << "Enter Course ID to filter (or 0 to skip): ";
	std::cin >> courseId;
	RemoveSpaces(courseId.data());
	toUpper(courseId.data());
	int coursesAmount = 0;
	Course* courses = LoadCourses(&coursesAmount);
	while (!CourseExists(courseId.c_str(), courses, coursesAmount) && courseId != "0")
	{

		std::cout << "Course ID " << courseId << " doesnt exist. Enter valid course ID or press 0 to skip: ";
		std::cin >> courseId;
		RemoveSpaces(courseId.data());
		toUpper(courseId.data());
	}
	delete[] courses;
	bool foundGrades = false;
	for (int i = 0; i < amount; i++)
	{
		bool matchesStudent = (studentId == "0" || grades[i].StudentId == studentId);
		bool matchesCourse = (courseId == "0" || grades[i].CourseId == courseId);
		if (matchesStudent && matchesCourse) {
			std::cout << (i + 1) << ") " << grades[i].StudentId << " - " << grades[i].CourseId << " => " << grades[i].MidTerm << ", "
				<< grades[i].Final << ", " << GetGpaLetter(grades[i].MidTerm + grades[i].Final) << '\n';
			foundGrades = true;
		}
	}
	if (!foundGrades)
		std::cout << "No grades found";
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
void DeleteGrade(Grade* grades, int* amount) {
	if (amount == 0) {
		cout << endl << "No grades registered. Press ENTER to continue....";
		cin.ignore();
		cin.get();
		return;
	}
	std::string studentId, courseId;
	cout << "Enter Student ID to delete: ";
	cin >> studentId;
	RemoveSpaces(studentId.data());
	toUpper(studentId.data());
	int studentsAmount = 0;
	Student* students = LoadStudents(&studentsAmount);
	while (!StudentExists(studentId.c_str(), students, studentsAmount))
	{
		std::cout << "Student Id " << studentId << " Not found. Please enter valid student ID or back to exit: ";
		cin >> studentId;
		RemoveSpaces(studentId.data());
		toUpper(studentId.data());
		if (studentId == "BACK")
		{
			std::cout << "Going back to menu...\n";
			delete[] students;
			return;
		}
	}
	delete[] students;
	cout << "Enter Course ID to delete: ";
	cin >> courseId;
	RemoveSpaces(courseId.data());
	toUpper(courseId.data());
	int coursesAmount = 0;
	Course* courses = LoadCourses(&coursesAmount);
	while (!CourseExists(courseId.c_str(), courses, coursesAmount))
	{
		std::cout << "Course ID " << courseId << " doesnt exist. Enter valid course ID or back to exit: ";
		cin >> courseId;
		RemoveSpaces(courseId.data());
		toUpper(courseId.data());
		if (courseId == "BACK")
		{
			std::cout << "Going back to menu...\n";
			delete[] courses;
			return;
		}
	}
	delete[] courses;
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
	PressEnterPause();
}

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
			for (int j = 0; j < coursesAmount; j++)
			{
				if (strcmp(courses[j].Id, grades[i].CourseId) == 0)
				{
					course = &courses[i];
					break;
				}
			}
			if (course == nullptr)
			{
				std::cout << "Error calculating GPA. Course with code " << grades[i].CourseId << " not found.\n";
				PressEnterPause();
				delete[] courses;
				return -1;
			}
			int total = grades[i].MidTerm + grades[i].Final;
			totalGrades += total * course->CreditHours;
			totalHours += course->CreditHours;
		}
	}
	delete[] courses;
	if (totalHours == 0)
	{
		return 0;
	}
	//GPA is out of 4
	return totalGrades / totalHours * (4.0 / 100);
}
void GenerateTranscript(Grade* grades, int amount)
{
	int studentsAmount = 0;
	Student* students = LoadStudents(&studentsAmount);
	if (studentsAmount == 0)
	{
		std::cout << "No students registered.\n";
		PressEnterPause();
		delete[] students;
		return;
	}
	std::string studentid;

	std::cout << "\nEnter Student ID: ";
	std::cin >> studentid;
	toUpper(studentid.data());
	RemoveSpaces(studentid.data());


	while (!StudentExists(studentid.c_str(), students, studentsAmount))
	{
		std::cout << "Student Id " << studentid << " Not found. Please enter valid student ID or back to exit: ";
		std::cin >> studentid;
		toUpper(studentid.data());
		RemoveSpaces(studentid.data());
		if (studentid == "BACK")
		{
			std::cout << "Going back to menu...\n";
			delete[] students;
			return;
		}
	}
	delete[] students;
	DisplayTitle(std::string("Transcript - " + studentid).c_str());
	bool hasGrades = false;
	const static int LINE_LENGTH = 50;
	int coursesAmount = 0;
	Course* courses = LoadCourses(&coursesAmount);
	for (int i = 0; i < amount; i++)
	{
		if (grades[i].StudentId == studentid)
		{
			Course* course = nullptr;
			for (int j = 0; j < coursesAmount; j++)
			{
				if (strcmp(courses[j].Id, grades[i].CourseId) == 0)
				{
					course = &courses[j];
					break;
				}
			}
			if (course == nullptr)
			{
				std::cout << "Error generating transcript. Course with code " << grades[i].CourseId << " not found.\n";
				PressEnterPause();
				delete[] courses;
				return;
			}
			int total = grades[i].MidTerm + grades[i].Final;
			for (int x = 0; x < LINE_LENGTH; x++)
				cout << ASCII_HORIZONTAL_LINE;
			cout << '\n';
			std::cout << "Course       : " << grades[i].CourseId << " - " << course->Title << '\n';
			std::cout << "Credit Hours : " << course->CreditHours << '\n';
			std::cout << "Midterm      : " << grades[i].MidTerm << "/40" << '\n';
			std::cout << "Final exam   : " << grades[i].Final << "/60" << '\n';
			std::cout << "The Toltal   : " << total << "/100 \n";
			std::cout << "GPA          : " << GetGpaGrade(total) << " / 4.0 \n";
			std::cout << "Grade        : " << GetGpaLetter(total) << '\n';

			for (int x = 0; x < LINE_LENGTH; x++)
				cout << ASCII_HORIZONTAL_LINE;
			cout << '\n';
			hasGrades = true;
		}
	}

	if (hasGrades)
	{

		std::cout << "\nSummary\n";
		std::cout << "GPA          : " << CalculateGpa(studentid, grades, amount) << '\n';
		std::cout << "Grade        : " << GetGpaLetter(CalculateGpa(studentid, grades, amount) * 100 / 4.0) << '\n';

		int totalHours = 0;
		for (int i = 0; i < amount; i++)
		{
			if (grades[i].StudentId == studentid)
			{
				for (int j = 0; j < coursesAmount; j++)
				{
					if (strcmp(courses[j].Id, grades[i].CourseId) == 0)
					{
						totalHours += courses[j].CreditHours;
						break;
					}
				}
			}
		}

		std::cout << "Total Credit Hours: " << totalHours << "\n\n\n";
	}

	else
	{
		std::cout << "No grades found for student with ID " << studentid << '\n';
	}
	PressEnterPause();
	delete[] courses;
}