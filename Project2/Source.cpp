#include <iostream>
#include <algorithm>
#include <vector>
#include <sqlite3.h>
#include <stdio.h>
#include<string>
#include "Student.h"
#include "sqlite.h"
using namespace std;

int main() {
	sqlite sq;
	Student s(8, "cosa ", " mnc", "nisa");
	sq.createTable("New.db", sq.Student);
	sq.createDB("New.db");
	string c = sq.Insert_STUDENT(s.id, s.name, s.AcademicYear, s.password);
	sq.insertData("New.db", c);
	sq.selectData("New.db", sq.se);
	/*vector<int> v;
	v.push_back(5);
	v.push_back(2);
	v.push_back(3);
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i];
	}*/
}