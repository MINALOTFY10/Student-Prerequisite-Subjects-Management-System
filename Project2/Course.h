#pragma once
#include<string>

using namespace std;
class Course
{
	int maxNumberOfStudents;
	int hours;
	int numOfCurrentStudent = 0;
	string name;
	string code;
public:
	Course();
	Course(string Code, string Name, int MaxNumberOfStudents, int Hours, int NumOfCurrentStudent);
	void setMaxNumberOfStudents(int maxNumberOfStudents);
	void setHours(int hours);
	void setNumOfCurrentStudent(int numOfCurrentStudent);
	void setName(string name);
	void setCode(string code);

	int getMaxNumberOfStudents();
	int getHours();
	int getNumOfCurrentStudent();

	string getName();
	string getCode();
};