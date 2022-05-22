#pragma once
#include<vector>
#include"Course.h"
#include<list>
#include<map>
class Admin
{
	string name;
	string password;
public:

	Admin();
	void login(map< string, class Admin>& adminMap);
	void addStudent(map<int, class Student>& studentMap);
	void addNewCourse(map< string, class Admin>& adminMap, map<string, class Course>& courseMap, map<string, vector<string>>& prerequiredMap);
	void enterCoursePrerequist(map<string, class Course>& courseMap, map<string, vector<string>>& prerequiredMap);
	void addFinishedCourses(map<int, class Student>& studentMap, map<int, vector<string>>& inProgressMap, map<int, vector<string>>& finishedMap, map<string, class Course>& courseMap);
	void viewStudentsOfCourse(map<string, class Course>& courseMap, map<int, vector<string>>& inProgressMap, map<int, class Student>& studentMap);  //the parameter is code of course
	void viewCoursesOfStudent(map<int, class Student>& studentMap, map<int, vector<string>>& inProgressMap, map<int, vector<string>>& fininshedMap);    //the parameter is id of the student
	void editCourse(map<string, class Course>& courseMap, map<int, vector<string>>& inProgressMap, map<int, vector<string>>& fininshedMap, map<string, vector<string>>& hasCourseMap, map<string, vector<string>>& prerequiredMap);
	void setName(string name);
	void setPassword(string password);
	string getName();
	string getPassword();
	~Admin();
};