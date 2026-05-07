#pragma once


static const char MALE_GENDER = 'M';
static const char FEMALE_GENDER = 'F';
static const int STUDENT_ID_LENGTH = 7;
static const int NATIONAL_ID_LENGTH = 14;
static const int PHONE_NUM_LENGTH = 11;
static const char* PHONE_NUM_PREFIX = "01";
static const int MIN_AGE = 17;
static const char* STUDENT_FILE_PATH = "./student.txt";
static const int MAX_NAME_LENGTH = 256;
static const int DATE_LENGTH = 10;

static const int MAX_LEVEL = 4;
static const int MIN_LEVEL = 1;
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
	char Id[STUDENT_ID_LENGTH + 1] = "";
	char Name[MAX_NAME_LENGTH + 1] = "";
	char NationalId[NATIONAL_ID_LENGTH + 1] = "";
	char PhoneNumber[PHONE_NUM_LENGTH + 1] = "";
	char Gender = MALE_GENDER;
	Programs Program = MCTA;
	int Level = 1; // 1-4
	float Gpa = 0.0;

	char BirthDate[DATE_LENGTH + 1] = "";
};


//Validation ==========================================
bool ValidateAge(const char* birthDate);
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
//MUST FREE MEMORY STUDENTS at the end
Student* LoadStudents(int* amount);
//STUDENT CRUD =======================================
void DeleteStudent(int index, Student* students,int *amount);
void UpdateStudent(Student* student,const char* name, const char* phone, Programs program, int level);
