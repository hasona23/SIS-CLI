#include "GradesManagement.h"



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

void AddGrade()
{
    Grade g;

    cout << "\n=======Enter Student Grades========\n";

    cout << "Enter Student id: ";
    cin >> g.StudentId;

    cout << "Enter Course code: ";
    cin >> g.CourseId;
    do
    {
        cout << "Enter Midterm Grade(0:40): ";
        cin >> g.MidTerm;

        if (g.MidTerm < 0 || g.MidTerm > 40)
        {
            cout << "Invalid Midterm Grade!\n";
        }

    } while (g.MidTerm > 0 || g.MidTerm < 40);

    do
    {
        cout << "Enter Final Grade(0:60): ";
        cin >> g.Final;

        if (g.Final < 0 || g.Final > 60)
        {
            cout << "Invalid Final Grade!\n";
        }

    } while (g.Final > 0 || g.Final < 60);

	AppendGrade(&g);

    int total = g.MidTerm + g.Final;
    cout << "The Toltal = " << total << "/100 \n";
    cout << "Garde Added Successfully\n";
}

/////////////////////////////////////////////////////

float CalculateGpa(std::string studentid,Grade* grades,int amount)
{
    float totalpoints = 0;
    int courses = 0;

    for (int i = 0; i < amount; i++)
    {
        if (grades[i].StudentId == studentid)
        {
            int total = grades[i].MidTerm + grades[i].Final;
            if (total >= 90)
            {
                totalpoints += 4.0;
            }
            else if (total >= 80)
            {
                totalpoints += 3.0;
            }
            else if (total >= 70)
            {
                totalpoints += 2.0;
            }
            else if (total >= 60)
            {
                totalpoints += 1;
            }
            else
            {
                totalpoints += 0;
            }
            courses++;
        }
    }
    if (courses == 0)
    {
        return 0;
    }
    return totalpoints / courses;
}

/////////////////////////////////////////////////////////////

void GenerateTranscript(Grade* grades, int amount)
{
    std::string studentid;

    std::cout << "\nEnter Student ID: ";
    std::cin >> studentid;

    std::cout << "\n====STUDENT TRANSCRIPT====\n";

    for (int i = 0; i < amount; i++)
    {
        if (grades[i].StudentId == studentid)
        {
            int total = grades[i].MidTerm + grades[i].Final;

			std::cout << "\ncourse code: " << grades[i].CourseId;
           std::cout << "\nMidterm: " << grades[i].MidTerm;
           std::cout << "\nFinal exam: " << grades[i].Final;
           std::cout << "\nTotal: " << total;
           std::cout << "\n--------------------\n";
        }
    }
	std::cout << "\nGPA = " << CalculateGpa(studentid,grades,amount) << '\n';
}


