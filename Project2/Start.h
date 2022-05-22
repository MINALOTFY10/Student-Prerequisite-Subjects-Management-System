#pragma once
#include<iostream>
#include"Admin.h"
#include"Student.h"
#include"Course.h"
#include"sqlite.h"
#include <vector>
#include <string>
#include<set>
#include<map>
#include<list>
#include <queue>
#include <algorithm>
#include <list>
using namespace std;
class Start
{
	string tmp;
	int selectFunction;
public:
	map<string, class Course>* courseMap = new map<string, class Course>();
	map<int, class Student>* studentMap = new map<int, class Student>();
	map<string, class Admin>* adminMap = new map<string, class Admin>();
	map<int, vector<string>>* inProgrssMap = new map<int, vector<string>>();//the key of map is the id of student and the value is vector of all his inProgress courses
	map<int, vector<string>>* finishedMap = new map<int, vector<string>>();//the key of map is the id of student and the value is vector of all his fininshed courses
	map<string, vector<string>>* hasCourseMap = new map<string, vector<string>>();//the key of map is the code of course and the value is vector of all ids of students who has registered on this course
	map<string, vector<string>>* prerequiredMap = new map<string, vector<string>>();//the key of map is the code of course and the value is vector of all its prerequired courses
	void return_data();//to return data from database
	void start_program();//to call function returnData and call function login from student or admin
	void Store_data();//to store data in the tables again
	void mapOfInProgressData();
	void mapOfFinishedData();
	void mapOfHasCourseData();
	void mapOfPrerequiredData();
	void displayMaps();
};