#include "SeedData.h"
#include "StudentManagement.h"
#include "CourseManagement.h"
#include "GradesManagement.h"
#include <fstream>
#include <cstring>

static bool IsFileEmpty(const char* path)
{
    std::ifstream file(path, std::ios::ate);
    if (!file.is_open()) return true;
    return file.tellg() == 0;
}

// ---------------------------------------------------------------------------
// Seeders
// ---------------------------------------------------------------------------

static void SeedStudents()
{
    Student student;

    strncpy_s(student.Id, "25P0001", STUDENT_ID_LENGTH);
    strncpy_s(student.Name, "Ahmed Hassan", MAX_NAME_LENGTH);
    strncpy_s(student.NationalId, "30001011234567", NATIONAL_ID_LENGTH);
    strncpy_s(student.PhoneNumber, "01012345678", PHONE_NUM_LENGTH);
    strncpy_s(student.BirthDate, "01/01/2001", DATE_LENGTH);
    student.Gender = MALE_GENDER; student.Gpa = 0.0f; student.Level = 1; student.Program = CSE;
    AppendStudent(student);

    strncpy_s(student.Id, "25P0002", STUDENT_ID_LENGTH);
    strncpy_s(student.Name, "Sara Mohamed", MAX_NAME_LENGTH);
    strncpy_s(student.NationalId, "30002021234568", NATIONAL_ID_LENGTH);
    strncpy_s(student.PhoneNumber, "01123456789", PHONE_NUM_LENGTH);
    strncpy_s(student.BirthDate, "15/03/2002", DATE_LENGTH);
    student.Gender = FEMALE_GENDER; student.Gpa = 0.0f; student.Level = 2; student.Program = CCE;
    AppendStudent(student);

    strncpy_s(student.Id, "25P0003", STUDENT_ID_LENGTH);
    strncpy_s(student.Name, "Omar Khaled", MAX_NAME_LENGTH);
    strncpy_s(student.NationalId, "29901011234569", NATIONAL_ID_LENGTH);
    strncpy_s(student.PhoneNumber, "01234567890", PHONE_NUM_LENGTH);
    strncpy_s(student.BirthDate, "20/06/2000", DATE_LENGTH);
    student.Gender = MALE_GENDER; student.Gpa = 0.0f; student.Level = 3; student.Program = MCTA;
    AppendStudent(student);

    strncpy_s(student.Id, "25P0004", STUDENT_ID_LENGTH);
    strncpy_s(student.Name, "Nour Ibrahim", MAX_NAME_LENGTH);
    strncpy_s(student.NationalId, "30003031234560", NATIONAL_ID_LENGTH);
    strncpy_s(student.PhoneNumber, "01056789012", PHONE_NUM_LENGTH);
    strncpy_s(student.BirthDate, "10/09/2003", DATE_LENGTH);
    student.Gender = FEMALE_GENDER; student.Gpa = 0.0f; student.Level = 2; student.Program = CSE;
    AppendStudent(student);

    strncpy_s(student.Id, "25P0005", STUDENT_ID_LENGTH);
    strncpy_s(student.Name, "Youssef Tarek", MAX_NAME_LENGTH);
    strncpy_s(student.NationalId, "30004041234561", NATIONAL_ID_LENGTH);
    strncpy_s(student.PhoneNumber, "01112345678", PHONE_NUM_LENGTH);
    strncpy_s(student.BirthDate, "05/12/2001", DATE_LENGTH);
    student.Gender = MALE_GENDER; student.Gpa = 0.0f; student.Level = 1; student.Program = COMM;
    AppendStudent(student);

    strncpy_s(student.Id, "25P0006", STUDENT_ID_LENGTH);
    strncpy_s(student.Name, "Layla Samir", MAX_NAME_LENGTH);
    strncpy_s(student.NationalId, "30005051234562", NATIONAL_ID_LENGTH);
    strncpy_s(student.PhoneNumber, "01212345678", PHONE_NUM_LENGTH);
    strncpy_s(student.BirthDate, "22/04/2002", DATE_LENGTH);
    student.Gender = FEMALE_GENDER; student.Gpa = 0.0f; student.Level = 4; student.Program = ENRGY;
    AppendStudent(student);

    strncpy_s(student.Id, "25P0007", STUDENT_ID_LENGTH);
    strncpy_s(student.Name, "Karim Adel", MAX_NAME_LENGTH);
    strncpy_s(student.NationalId, "30006061234563", NATIONAL_ID_LENGTH);
    strncpy_s(student.PhoneNumber, "01512345678", PHONE_NUM_LENGTH);
    strncpy_s(student.BirthDate, "07/07/2003", DATE_LENGTH);
    student.Gender = MALE_GENDER; student.Gpa = 0.0f; student.Level = 1; student.Program = CCE;
    AppendStudent(student);
}

static void SeedCourses()
{
    Course courses;

    strncpy_s(courses.Id, "CSE101", COURSE_ID_LENGTH); strncpy_s(courses.Title, "Intro to Programming", MAX_COURSE_TITLE_LENGTH); courses.CreditHours = 3;
    AppendCourse(&courses);

    strncpy_s(courses.Id, "CSE201", COURSE_ID_LENGTH); strncpy_s(courses.Title, "Data Structures", MAX_COURSE_TITLE_LENGTH); courses.CreditHours = 3;
    AppendCourse(&courses);

    strncpy_s(courses.Id, "MTH101", COURSE_ID_LENGTH); strncpy_s(courses.Title, "Calculus I", MAX_COURSE_TITLE_LENGTH); courses.CreditHours = 4;
    AppendCourse(&courses);

    strncpy_s(courses.Id, "ENG101", COURSE_ID_LENGTH); strncpy_s(courses.Title, "Technical Writing", MAX_COURSE_TITLE_LENGTH); courses.CreditHours = 2;
    AppendCourse(&courses);

    strncpy_s(courses.Id, "PHY101", COURSE_ID_LENGTH); strncpy_s(courses.Title, "Physics I", MAX_COURSE_TITLE_LENGTH); courses.CreditHours = 3;
    AppendCourse(&courses);

    strncpy_s(courses.Id, "NET101", COURSE_ID_LENGTH); strncpy_s(courses.Title, "Computer Networks", MAX_COURSE_TITLE_LENGTH); courses.CreditHours = 1;
    AppendCourse(&courses);
}

static void SeedGrades()
{
    Grade grade;

    strncpy_s(grade.StudentId, "25P0001", STUDENT_ID_LENGTH); strncpy_s(grade.CourseId, "CSE101", COURSE_ID_LENGTH); grade.MidTerm = 35; grade.Final = 55;
    AppendGrade(&grade);

    strncpy_s(grade.StudentId, "25P0001", STUDENT_ID_LENGTH); strncpy_s(grade.CourseId, "MTH101", COURSE_ID_LENGTH); grade.MidTerm = 30; grade.Final = 50;
    AppendGrade(&grade);

    strncpy_s(grade.StudentId, "25P0002", STUDENT_ID_LENGTH); strncpy_s(grade.CourseId, "CSE101", COURSE_ID_LENGTH); grade.MidTerm = 38; grade.Final = 58;
    AppendGrade(&grade);

    strncpy_s(grade.StudentId, "25P0002", STUDENT_ID_LENGTH); strncpy_s(grade.CourseId, "ENG101", COURSE_ID_LENGTH); grade.MidTerm = 32; grade.Final = 48;
    AppendGrade(&grade);

    strncpy_s(grade.StudentId, "25P0003", STUDENT_ID_LENGTH); strncpy_s(grade.CourseId, "CSE201", COURSE_ID_LENGTH); grade.MidTerm = 28; grade.Final = 45;
    AppendGrade(&grade);

    strncpy_s(grade.StudentId, "25P0003", STUDENT_ID_LENGTH); strncpy_s(grade.CourseId, "PHY101", COURSE_ID_LENGTH); grade.MidTerm = 22; grade.Final = 38;
    AppendGrade(&grade);

    strncpy_s(grade.StudentId, "25P0004", STUDENT_ID_LENGTH); strncpy_s(grade.CourseId, "CSE101", COURSE_ID_LENGTH); grade.MidTerm = 40; grade.Final = 60;
    AppendGrade(&grade);

    strncpy_s(grade.StudentId, "25P0004", STUDENT_ID_LENGTH); strncpy_s(grade.CourseId, "PHY101", COURSE_ID_LENGTH); grade.MidTerm = 36; grade.Final = 52;
    AppendGrade(&grade);

    strncpy_s(grade.StudentId, "25P0005", STUDENT_ID_LENGTH); strncpy_s(grade.CourseId, "NET101", COURSE_ID_LENGTH); grade.MidTerm = 25; grade.Final = 40;
    AppendGrade(&grade);

    strncpy_s(grade.StudentId, "25P0006", STUDENT_ID_LENGTH); strncpy_s(grade.CourseId, "MTH101", COURSE_ID_LENGTH); grade.MidTerm = 37; grade.Final = 57;
    AppendGrade(&grade);

    strncpy_s(grade.StudentId, "25P0006", STUDENT_ID_LENGTH); strncpy_s(grade.CourseId, "ENG101", COURSE_ID_LENGTH); grade.MidTerm = 34; grade.Final = 50;
    AppendGrade(&grade);

    strncpy_s(grade.StudentId, "25P0007", STUDENT_ID_LENGTH); strncpy_s(grade.CourseId, "CSE101", COURSE_ID_LENGTH); grade.MidTerm = 20; grade.Final = 35;
    AppendGrade(&grade);
}

// ---------------------------------------------------------------------------
// Public entry point
// ---------------------------------------------------------------------------

void SeedIfEmpty()
{
    const bool studentsEmpty = IsFileEmpty(STUDENT_FILE_PATH);
    const bool coursesEmpty = IsFileEmpty(COURSES_FILE_PATH);
    const bool gradesEmpty = IsFileEmpty(GRADES_FILE_PATH);

    if (!studentsEmpty || !coursesEmpty || !gradesEmpty)
        return;

    std::cout << "No data found. Seeding sample data...\n";
	std::cout << "Do you want to load sample data? (Y/N): ";
	if (tolower(std::cin.get()) != 'y')
	{
		std::cout << "Skipping data seeding. Press Enter to continue...\n";
		std::cin.get();
		return;
	}
    SeedStudents();
    SeedCourses();
    SeedGrades();

    std::cout << "Sample data loaded. Press Enter to continue...\n";
    std::cin.get();
}