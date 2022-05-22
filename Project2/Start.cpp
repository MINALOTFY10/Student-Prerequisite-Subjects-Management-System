#include "Start.h"
Course courseObj;
Student studentObj;
Admin adminObj;
sqlite sql;
static vector<string> tmp1;
static vector<string> tmp2;

void Start::return_data()
{
	(*studentMap) = sql.mapOfStudentData(sql.address, "SELECT * FROM STUDENT;");
	(*courseMap) = sql.mapOfCourseData(sql.address, "SELECT * FROM COURSE;");
	(*adminMap) = sql.mapOfAdminData(sql.address, "SELECT * FROM ADMIN;");
	mapOfFinishedData();
	mapOfHasCourseData();
	mapOfInProgressData();
	mapOfPrerequiredData();
}
void Start::start_program()
{
	return_data();
	displayMaps();
begin:
	cout << "will you login as Admin or Student ? (a ,s)" << endl;
	cin >> tmp;
	if (tmp == "a")
	{
		adminObj.login(*adminMap);
		while (true)
		{
			cout << "Enter: \n1:add new course \n2:add new student \n3:enter course prerequist \n4:view courses of student \n5:view students of course \n6:edit data of course \n7:add finished course for any student \n";
			cout << "8:finish program \n9:refresh the program\n";

			cin >> selectFunction;
			if (selectFunction == 1)
				adminObj.addNewCourse(*adminMap, *courseMap, *prerequiredMap);
			else if (selectFunction == 2)
				adminObj.addStudent(*studentMap);
			else if (selectFunction == 3)
				adminObj.enterCoursePrerequist(*courseMap, *prerequiredMap);
			else if (selectFunction == 4)
				adminObj.viewCoursesOfStudent(*studentMap, *inProgrssMap, *finishedMap);
			else if (selectFunction == 5)
				adminObj.viewStudentsOfCourse(*courseMap, *inProgrssMap, *studentMap);
			else if (selectFunction == 6)
				adminObj.editCourse(*courseMap, *inProgrssMap, *finishedMap, *hasCourseMap, *prerequiredMap);
			else if (selectFunction == 7)
				adminObj.addFinishedCourses(*studentMap, *inProgrssMap, *finishedMap, *courseMap);
			else if (selectFunction == 8)
			{
				Store_data();
				break;
			}
			else if (selectFunction == 9)
			{
				displayMaps();
				goto begin;
			}
			else
				cout << "Invalid number " << endl;
		}
	}
	else if (tmp == "s")
	{
		studentObj.login(*studentMap);
		while (true)
		{
			cout << "Enter:\n1:view list of all courses \n2:view details of course \n3:register for acourse \n4:view all your courses \n5:edit your data \n";
			cout << "6:finish program \n7:refresh the program\n";
			cin >> selectFunction;
			if (selectFunction == 1)
			{
				studentObj.viewAvailableCourses(*courseMap, *finishedMap, *inProgrssMap);
			}
			else if (selectFunction == 2)
			{
				studentObj.viewSpecificCourseDetails(*courseMap);
			}
			else if (selectFunction == 3)
			{
				studentObj.registerForCourse(*prerequiredMap, *finishedMap, *courseMap, *hasCourseMap, *inProgrssMap);
			}
			else if (selectFunction == 4)
			{
				studentObj.viewStudentCourses(*inProgrssMap, *finishedMap);
			}
			else if (selectFunction == 5)
			{
				studentObj.editData(*studentMap);
			}
			else if (selectFunction == 6)
			{
				Store_data();
				break;
			}
			else if (selectFunction == 7)
			{
				displayMaps();
				goto begin;
			}
			else
				cout << "Invalid number " << endl;
		}
	}
	else {
		cout << "Invalid choice ,try again" << endl;
		goto begin;
	}
}
void Start::Store_data()
{
	string insertData;
	map<string, Course>::iterator it1 = (*courseMap).begin();
	map<int, Student>::iterator it2 = (*studentMap).begin();
	map<string, class Admin>::iterator it3 = (*adminMap).begin();
	map<int, vector<string>>::iterator it4 = (*inProgrssMap).begin();
	map<string, vector<string>>::iterator it5 = (*hasCourseMap).begin();

	sql.DeleteData(sql.address, "DELETE FROM COURSE ;");
	sql.DeleteData(sql.address, "DELETE FROM STUDENT ;");
	sql.DeleteData(sql.address, "DELETE FROM Has_Course ;");
	sql.DeleteData(sql.address, "DELETE FROM ADMIN ;");
	sql.DeleteData(sql.address, "DELETE FROM Course_PreRequired ;");
	sql.DeleteData(sql.address, "DELETE FROM Student_FinishedCourse ;");
	sql.DeleteData(sql.address, "DELETE FROM Student_InProgress ;");


	while (it1 != (*courseMap).end())
	{
		insertData = "('" + it1->first + "','" + it1->second.getName() + "'," + to_string(it1->second.getMaxNumberOfStudents()) + "," + to_string(it1->second.getHours()) + "," + to_string(it1->second.getNumOfCurrentStudent()) + ");";
		sql.insertData(sql.address, "COURSE", "(CODE,NAME,MAX_STUDENT,HOURSE,NUM_OF_CURRENT_STUDENT)", insertData);
		it1++;
	}

	while (it2 != (*studentMap).end())
	{
		insertData = "('" + to_string(it2->first) + "','" + it2->second.get_Name() + "','" + it2->second.get_AcademicYear() + "','" + it2->second.get_Password() + "');";
		sql.insertData(sql.address, "STUDENT", "(ID,NAME,ACADEMIC_YEAR,PASSWORD)", insertData);
		it2++;
	}
	while (it3 != (*adminMap).end())
	{
		insertData = "('" + it3->second.getPassword() + "','" + it3->second.getName() + "');";
		sql.insertData(sql.address, "ADMIN", "(PASSWORD,NAME)", insertData);
		it3++;
	}
	while (it5 != (*hasCourseMap).end()) {
		for (int i = 0; i < it5->second.size(); i++) {
			insertData = "('" + it5->first + "'," + it5->second.at(i) + ");";
			sql.insertData(sql.address, "Has_Course", "(CODE,ID)", insertData);
		}
		it5++;
	}
	it5 = (*prerequiredMap).begin();
	while (it5 != (*prerequiredMap).end()) {
		for (int i = 0; i < it5->second.size(); i++) {
			insertData = "('" + it5->first + "','" + it5->second.at(i) + "');";
			sql.insertData(sql.address, "Course_PreRequired", "(CODE,PRE_REQUIRED)", insertData);
		}
		it5++;
	}
	while (it4 != (*inProgrssMap).end()) {
		for (int i = 0; i < it4->second.size(); i++) {
			insertData = "(" + to_string(it4->first) + ",'" + it4->second.at(i) + "');";
			sql.insertData(sql.address, "Student_InProgress", "(ID,IN_PROGRESS)", insertData);
		}
		it4++;
	}
	it4 = (*finishedMap).begin();
	while (it4 != (*finishedMap).end()) {
		for (int i = 0; i < it4->second.size(); i++) {
			insertData = "(" + to_string(it4->first) + ",'" + it4->second.at(i) + "');";
			sql.insertData(sql.address, "Student_FinishedCourse", "(ID,FINISHED_COURSE)", insertData);
		}
		it4++;
	}

}
void Start::mapOfInProgressData() {
	tmp1.clear();
	tmp2.clear();
	tmp1 = sql.vectorOfData(sql.address, "SELECT ID FROM Student_InProgress;");
	tmp2 = sql.vectorOfData(sql.address, "SELECT IN_PROGRESS FROM Student_InProgress;");
	for (int i = 0; i < tmp1.size(); i++) {
		(*inProgrssMap)[stoi(tmp1.at(i))].push_back(tmp2.at(i));
	}

}
void Start::mapOfFinishedData() {
	tmp1.clear();
	tmp2.clear();
	tmp1 = sql.vectorOfData(sql.address, "SELECT ID FROM Student_FinishedCourse;");
	tmp2 = sql.vectorOfData(sql.address, "SELECT FINISHED_COURSE FROM Student_FinishedCourse;");

	for (int i = 0; i < tmp1.size(); i++) {
		(*finishedMap)[stoi(tmp1.at(i))].push_back(tmp2.at(i));
	}

}
void Start::mapOfHasCourseData() {
	tmp1.clear();
	tmp2.clear();
	tmp1 = sql.vectorOfData(sql.address, "SELECT CODE FROM Has_Course;");
	tmp2 = sql.vectorOfData(sql.address, "SELECT ID FROM Has_Course;");

	for (int i = 0; i < tmp1.size(); i++) {
		(*hasCourseMap)[tmp1.at(i)].push_back(tmp2.at(i));
	}
}
void Start::mapOfPrerequiredData() {
	tmp1.clear();
	tmp2.clear();
	tmp1 = sql.vectorOfData(sql.address, "SELECT CODE FROM Course_PreRequired;");
	tmp2 = sql.vectorOfData(sql.address, "SELECT PRE_REQUIRED FROM Course_PreRequired;");

	for (int i = 0; i < tmp1.size(); i++) {
		(*prerequiredMap)[tmp1.at(i)].push_back(tmp2.at(i));
	}
}
void Start::displayMaps() {
	cout << "\n\n------------------inProgressMap------------------" << endl;
	map<int, vector<string>>::iterator it1 = (*inProgrssMap).begin();
	while (it1 != (*inProgrssMap).end())
	{
		cout << it1->first << " : ";

		for (int i = 0; i < it1->second.size(); i++)
			cout << it1->second.at(i) << "	";
		cout << endl;
		cout << "------------------------------------------------" << endl;
		it1++;
	}
	it1 = (*finishedMap).begin();
	cout << "\n\n------------------finishedMap------------------" << endl;
	while (it1 != (*finishedMap).end())
	{
		cout << it1->first << " : ";

		for (int i = 0; i < it1->second.size(); i++)
			cout << it1->second.at(i) << "	";
		cout << endl;
		cout << "------------------------------------------------" << endl;
		it1++;
	}
	cout << "\n\n------------------hasCourseMap------------------" << endl;
	map<string, vector<string>>::iterator it2 = (*hasCourseMap).begin();
	while (it2 != (*hasCourseMap).end())
	{
		cout << it2->first << " : ";

		for (int i = 0; i < it2->second.size(); i++)
			cout << it2->second.at(i) << "  ";
		cout << endl;
		cout << "------------------------------------------------" << endl;
		it2++;
	}
	it2 = (*prerequiredMap).begin();
	cout << "\n\n------------------prerequiredMap------------------" << endl;
	while (it2 != (*prerequiredMap).end())
	{
		cout << it2->first << " : ";

		for (int i = 0; i < it2->second.size(); i++)
			cout << it2->second.at(i) << "	";
		cout << endl;
		cout << "------------------------------------------------" << endl;
		it2++;
	}
	cout << "\n\n------------------studentMap------------------" << endl;
	map<int, class Student>::iterator it3 = (*studentMap).begin();
	while (it3 != (*studentMap).end()) {
		cout << it3->first << " : " << it3->second.get_Name() << "  " << it3->second.get_AcademicYear() << "  " << it3->second.get_Password() << endl;
		cout << "------------------------------------------------" << endl;
		it3++;
	}
	cout << "\n\n------------------courseMap------------------" << endl;
	map<string, class Course>::iterator it4 = (*courseMap).begin();
	while (it4 != (*courseMap).end()) {
		cout << it4->first << " : " << it4->second.getName() << "  " << it4->second.getHours() << "  " << it4->second.getMaxNumberOfStudents() << "  " << it4->second.getNumOfCurrentStudent() << endl;//esale fatma
		cout << "------------------------------------------------" << endl;

		it4++;
	}
	cout << "\n\n------------------adminMap------------------" << endl;
	map<string, class Admin>::iterator it5 = (*adminMap).begin();
	while (it5 != (*adminMap).end()) {
		cout << it5->first << "  " << it5->second.getName() << endl;
		cout << "------------------------------------------------" << endl;
		it5++;
	}
}