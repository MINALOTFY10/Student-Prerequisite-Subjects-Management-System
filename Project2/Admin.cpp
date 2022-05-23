#include"Start.h"
#include<string>
using namespace std;
Course courseObject;
Student studentObject;

Admin::Admin() {
	name = "";
	password = "";
}

void Admin::login(map< string, class Admin>& adminMap)
{
log:
	cout << "Enter Your Name : ";
	cin >> name;
	cout << "Enter Your Password : ";
	cin >> password;

	if (adminMap[password].name == name)
	{
		cout << "Login Successfully..." << endl;
	}
	else
	{
		cout << "Invalid Login ! please login again" << endl;
		goto log;
	}
}

void Admin::editCourse(map<string, class Course>& courseMap, map<int, vector<string>>& inProgressMap, map<int, vector<string>>& fininshedMap,
	map<string, vector<string>>& hasCourseMap, map<string, vector<string>>& prerequiredMap)
{
	string* courseCode = new string;
	string* newData = new string;
	int* check = new int;
	int* intData = new int;
	bool* found = new bool;
	string* oldData = new string;
	map<string, class Course>::iterator it = courseMap.begin();
	map<int, vector<string>>::iterator it1 = inProgressMap.begin();
	map<int, vector<string>>::iterator it2 = fininshedMap.begin();
	map<string, vector<string>>::iterator it3 = prerequiredMap.begin();
	cout << "Enter code of course : ";
	cin >> *courseCode;
	if (courseMap[*courseCode].getName().empty() == true)//courseMap.find(*courseCode)->first != *courseCode)
	{
		cout << "This course is not found." << endl;
	}
	else
	{
		while (true)
		{
			cout << "\n Current data is :" << endl;
			cout << "CODE:" << courseMap[*courseCode].getCode() << "\nNAME:" << courseMap[*courseCode].getName() << "\nHOURSE:" << courseMap[*courseCode].getHours() << "\nMAX NUMBER OF STUDENT:" << courseMap[*courseCode].getMaxNumberOfStudents() << endl;
			cout << "What do you want to edit ?\n1 for name.\n2 for code.\n3 for hours.\n4 for maximum number of student.\n5 to exit." << endl;
			cin >> *check;
			if (*check == 1)
			{
				cout << "Enter new name: ";
				cin >> *newData;
				while (it != courseMap.end())
				{
					if (it->second.getName() == *newData)
					{
						*found = true;
						break;
					}
					it++;
				}
				if (*found == true)
				{
					cout << "this name is found,please try again " << endl;
				}
				else
				{
					*oldData = courseMap[*courseCode].getName();
					courseMap[*courseCode].setName(*newData);
					while (it1 != inProgressMap.end())
					{
						for (int i = 0; i < it1->second.size(); i++)
						{
							if (it1->second.at(i) == *oldData)
							{
								it1->second.at(i) = *newData;
								break;
							}
						}
						it1++;
					}
					while (it3 != prerequiredMap.end())
					{
						for (int i = 0; i < it3->second.size(); i++)
						{
							if (it3->second.at(i) == *oldData)
							{
								it3->second.at(i) = *newData;
								break;
							}
						}
						it3++;
					}
					while (it2 != fininshedMap.end())
					{
						for (int i = 0; i < it2->second.size(); i++)
						{
							if (it2->second.at(i) == *oldData)
							{
								it2->second.at(i) = *newData;
								break;
							}
						}
						it2++;
					}
				}
			}
			else if (*check == 2)
			{
				cout << "Enter new code: ";
				cin >> *newData;
				while (it != courseMap.end())
				{
					if (it->second.getCode() == *newData)
					{
						*found = true;
						break;
					}
					it++;
				}
				if (*found == true)
				{
					cout << "this code is found,please try again " << endl;
				}
				else
				{
					*oldData = *courseCode;
					*courseCode = *newData;
					courseObject = courseMap[*oldData];
					courseObject.setCode(*newData);
					courseMap.erase(courseMap.find(*oldData));
					courseMap[*newData] = courseObject;

					vector<string>* oldvector = new vector<string>(prerequiredMap[*oldData]);
					prerequiredMap.erase(prerequiredMap.find(*oldData));
					if ((*oldvector).empty() == false)
						prerequiredMap[*newData] = *oldvector;

					*oldvector = hasCourseMap[*oldData];
					hasCourseMap.erase(hasCourseMap.find(*oldData));
					if ((*oldvector).empty() == false)
						hasCourseMap[*newData] = *oldvector;



				}
			}
			else if (*check == 3)
			{
				cout << "Enter new hours: ";
				cin >> *intData;
				courseMap[*courseCode].setHours(*intData);
			}
			else if (*check == 4)
			{
				cout << "Enter new maximum number of student: ";
				cin >> *intData;
				courseMap[*courseCode].setMaxNumberOfStudents(*intData);
			}
			else if (*check == 5)
			{
				break;
			}
			else
				cout << "Invalid number,please try again " << endl;
		}
	}
	delete courseCode, newData, oldData, intData, found, check;
}

void Admin::addStudent(map<int, class Student>& studentMap) {

	string* addStudentName = new string;
	string* addStudentPassword = new string;
	string* addStudentAcademicYear = new string;

	studentObject.set_Id(studentMap.size() + 1);

	cout << "Enter name of student :" << endl;

	getline(cin, *addStudentName);
	getline(cin, *addStudentName);
	studentObject.set_Name(*addStudentName);

	while (true)
	{
		cout << "Enter passward of student :" << endl;
		getline(cin, *addStudentPassword);

		if ((*addStudentPassword).find(' ') < (*addStudentPassword).length())
			cout << "Password with space is invalid ,try again." << endl;
		else
			break;
	}
	studentObject.set_Password(*addStudentPassword);

	cout << "Enter academic year of student :" << endl;
	getline(cin, *addStudentAcademicYear);
	studentObject.set_AcademicYear(*addStudentAcademicYear);

	studentMap[studentObject.get_Id()] = studentObject;
	cout << "\n\nCompleted sucssefully\n\n" << endl;

	delete addStudentName, addStudentPassword, addStudentAcademicYear;
}

void Admin::addNewCourse(map< string, class Admin>& adminMap, map<string, class Course>& courseMap, map<string, vector<string>>& prerequiredMap)
{
	Course c;
	int* option = new int;
	int* tmp2 = new int;
	bool* flag = new bool;
	bool* found = new bool;
	string* req = new string;
	string* sql = new string;
	string* tmp1 = new string;
	vector<string>* pre = new vector<string>;
start:
	*flag = true;
	cout << "Enter code of course : ";
	cin >> *tmp1;
	c.setCode(*tmp1);
	cout << "Enter name of course : ";
	cin >> *tmp1;
	c.setName(*tmp1);
	map<string, Course>::iterator it = (courseMap).begin();
	while (it != (courseMap).end())
	{
		if (it->first == c.getCode() || it->second.getName() == c.getName())
		{
			*flag = false;
			break;
		}
		it++;
	}
	if (*flag)
	{
		courseMap[c.getCode()].setCode(c.getCode());
		courseMap[c.getCode()].setName(c.getName());
	}
	else
	{
		cout << "Code or Name is already exist please enter data again" << endl;
		goto start;
	}

	cout << "Enter houres of course : ";
	cin >> *tmp2;
	c.setHours(*tmp2);
	courseMap[c.getCode()].setHours(c.getHours());
	cout << "Enter max number of student of course : ";
	cin >> *tmp2;
	c.setMaxNumberOfStudents(*tmp2);
	courseMap[c.getCode()].setMaxNumberOfStudents(c.getMaxNumberOfStudents());

	while (true)
	{
		*found = false;
		cout << "\nOptions: \n" <<
			"1. add pre_required \n" <<
			"2. Exit \n";
		cin >> *option;
		if (*option == 1)
		{
			cout << "Enter Course Name: ";
			cin >> *req;
			it = courseMap.begin();
			while (it != courseMap.end())
			{
				if (*req == it->second.getName() && *req != *tmp1)
				{
					*found = true;
					break;
				}
				it++;
			}
			if (*found)
				(*pre).push_back(*req);
			else {
				cout << "This course not found " << endl;
			}
		}
		else
		{
			break;
		}
	}
	prerequiredMap[c.getCode()] = *pre;
	delete req, sql, tmp1, option, tmp2, pre, flag, found;
}

void Admin::enterCoursePrerequist(map<string, class Course>& courseMap, map<string, vector<string>>& prerequiredMap)
{
	int* option = new int;
	bool* flag = new bool;
	bool* found = new bool;
	string* code = new string;
	string* sql = new string;
	string* req = new string;

start:
	*flag = false;
	cout << "Enter course code: ";
	cin >> *code;
	map<string, Course>::iterator it = (courseMap).begin();
	while (it != (courseMap).end())
	{
		if (it->first == *code)
		{
			*flag = true;
			break;
		}
		it++;
	}
	if (*flag)
	{
		vector<string>* pre = new vector<string>;
		while (true)
		{
			cout << "\nOptions: \n" <<
				"1. add pre_required \n" <<
				"2. Exit \n";
			cin >> *option;
			while (*option > 2 || *option < 1)
			{
				cout << "Invalid input please try again" << endl;
				cin >> *option;
			}
			if (*option == 1)
			{
				cout << "Enter course name: ";
				cin >> *req;
				it = courseMap.begin();
				while (it != courseMap.end())
				{
					if (*req == it->second.getName() && *req != courseMap[*code].getName())
					{
						*found = true;
						break;
					}
					it++;
				}
				if (*found)
					(*pre).push_back(*req);
				else {
					cout << "This course not found " << endl;
				}
			}
			else
			{
				break;
			}
		}
		prerequiredMap[*code] = *pre;
	}
	else
	{
		int* check = new int;
		cout << "invalid code!!!" << endl;
		cout << "\nOptions: \n" <<
			"1. Enter course pre-required \n" <<
			"2. Exit \n";
		cin >> *check;

		while (*check > 2 || *check < 1)
		{
			cout << "Invalid input please try again" << endl;
			cin >> *check;
		}
		if (*check == 1)
		{
			goto start;
		}
		else
		{
			return;
		}
		delete check;
	}
	delete option, flag, code, sql, req;
}

void Admin::viewStudentsOfCourse(map<string, class Course>& courseMap, map<int, vector<string>>& inProgressMap, map<int, class Student>& studentMap)
{
	string* courseCode = new string;
theStart:
	cout << "\nEnter the code of course :" << endl;
	cin >> *courseCode;
	cout << "\n";
	if (courseMap[*courseCode].getName().empty() == true) {
		cout << "No course has this code" << endl;
		goto theStart;
	}
	else {
		string* courseName = new string;
		*courseName = courseMap[*courseCode].getName();
		map<int, vector<string>>::iterator it = inProgressMap.begin();
		vector<string>* tmp = new vector<string>;
		while (it != inProgressMap.end()) {
			for (int i = 0; i < it->second.size(); i++) {
				if (it->second.at(i) == *courseName)
				{
					(*tmp).push_back(studentMap[it->first].get_Name());
					break;
				}
			}
			it++;
		}
		if ((*tmp).size() == 0) {
			cout << "No students in this course" << endl;
		}
		else {
			cout << "Names of students" << endl;
			for (int i = 0; i < (*tmp).size(); i++)
			{
				cout << "  " << (*tmp).at(i) << endl;
			}
		}
		delete tmp, courseCode, courseName;
	}
	cout << "\n\n";
}

void Admin::viewCoursesOfStudent(map<int, class Student>& studentMap, map<int, vector<string>>& inProgressMap, map<int, vector<string>>& fininshedMap) {//asale el mo3ed
	int* id = new int;
theBegin:
	cout << "\nEnter Id of Student : " << endl;
	cin >> *id;
	cout << "\n";
	if (studentMap[*id].get_Name().empty() == false)
	{
		if (inProgressMap[*id].size() != 0)
		{
			cout << "The inProgress Courses of student " << studentMap[*id].get_Name() << "" << endl;
			for (int i = 0; i < inProgressMap[*id].size(); i++)
			{
				cout << "	" << inProgressMap[*id].at(i) << endl;
			}
		}
		else {
			cout << "This student has not inProgress courses " << endl;
		}
		cout << "\n\n";
		if (fininshedMap[*id].size() != 0)
		{
			cout << "*The fininshed Courses of student " << studentMap[*id].get_Name() << " *" << endl;
			for (int i = 0; i < fininshedMap[*id].size(); i++)
			{
				cout << "	" << fininshedMap[*id].at(i) << endl;;
			}
			cout << endl;
		}
		else {
			cout << "This student has not fininshed courses " << endl;
		}
	}
	else {
		cout << "No student have this id " << endl;
		goto theBegin;
	}
	cout << "\n\n";
	delete id;
}

void Admin::addFinishedCourses(map<int, class Student>& studentMap, map<int, vector<string>>& inProgressMap, map<int, vector<string>>& finishedMap, map<string, class Course>& courseMap) {
	int* id = new int;
	int* tmp = new int;
	string* courseName = new string;
	bool* found = new bool;
theBegining:
	cout << "\nEnter id of student:";
	cin >> *id;
	if (studentMap[*id].get_Name().empty() == false)
	{
		vector<string>* finished = new vector<string>;
		cout << "Enter number of courses :" << endl;
		cin >> *tmp;
		cout << "Enter the fininshed courses that you want to add to the student " << endl;
		for (int i = 0; i < *tmp; i++) {
			cin >> *courseName;
			(*finished).push_back(*courseName);
		}
		vector<string>::iterator it1 = (*finished).begin();
		vector<string>::iterator it2;
		map<string, class Course>::iterator it3;
		while (it1 != (*finished).end())
		{
			*found = false;
			it2 = (inProgressMap[*id]).begin();
			while (it2 != (inProgressMap[*id]).end())
			{
				if (*it1 == *it2)
				{
					*found = true;
					finishedMap[*id].push_back(*it1);
					(inProgressMap[*id]).erase(it2);
					it3 = courseMap.begin();
					while (it3 != courseMap.end())
					{
						if (it3->second.getName() == *it1)
						{
							courseMap[it3->first].setNumOfCurrentStudent(courseMap[it3->first].getNumOfCurrentStudent() - 1);
						}
						it3++;
					}
					break;
				}
				it2++;
			}
			if (*found == false) {
				cout << "course of " << *it1 << " can't be added " << endl;
			}
			it1++;
		}
		if ((inProgressMap[*id]).size() == 0)
		{
			inProgressMap.erase(inProgressMap.find(*id));
		}
		delete finished;
	}
	else {
		cout << "No student has this id" << endl;
		goto theBegining;
	}
	delete id, tmp, courseName, found;
}
void Admin::setName(string name) {
	this->name = name;
}
void Admin::setPassword(string password) {
	this->password = password;
}
string Admin::getName() {
	return name;
}
string Admin::getPassword() {
	return password;
}
Admin::~Admin() {

}
