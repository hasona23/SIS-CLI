#pragma once


static const char MALE_GENDER = 'M';
static const char FEMALE_GENDER = 'F';
static const int ID_LENGTH = 7;
static const int NATIONAL_ID_LENGTH = 14;
static const int PHONE_NUM_LENGTH = 11;
static const char* PHONE_NUM_PREFIX = "01";
static const int MIN_AGE = 17;
static const char* STUDENT_FILE_PATH = "./stduent.txt";
static const int MAX_NAME_LENGTH = 256;

enum Programs
{
	MCTA = 1,
	CSE,
	CCE,
	ENRGY,
	COMM
};



struct Student
{
public:
	char Id[ID_LENGTH + 1];
	char Name[MAX_NAME_LENGTH + 1];
	char NationalId[NATIONAL_ID_LENGTH + 1];
	char PhoneNumber[PHONE_NUM_LENGTH + 1];
	char Gender;
	Programs Program;
	int Level; // 1-4
	float Gpa;



	int YearBirth;
	int DayBirth;
	int MonthBirth;
};


//Validation ==========================================
bool ValidateAge(int day, int month, int year);
bool ValidatePhoneNumber(const char* num);
bool ValidateGpa(double gpa);
bool ValidateLevel(int level);
bool ValidateProgram(int program);
bool ValidateGender(char gender);
bool ValidateNationalId(const char* id);
bool ValidateStudentId(const char* id);
bool ValidateName(const char* name);

bool ValidateStudent(Student student);

//FILE IO ============================================

void SaveStudents(const Student* students, int amount);
void AppendStudent(const Student student);
void CreateStudentFile();
Student* LoadStudents(int* amount);
//STUDENT CRUD =======================================
void AddStudent(const Student student);

void DeleteStudent(int index,const Student* students,int amount);
void UpdateStudent(Student* student,const char* name, const char* phone, Programs program, int level);
