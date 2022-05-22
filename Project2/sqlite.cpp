#include"Start.h"
using namespace std;
Course courseOb;
Student studentOb;
string tableSelected;
Admin adminOb;
static vector<string> v;
static map< string, class Course> courseMap;
static map< string, class Admin> adminMap;
static map<int, class Student> studentMap;
sqlite::sqlite()
{

}

int sqlite::createDB(const char* dir)
{
	sqlite3* DB;

	int exit = 0;
	exit = sqlite3_open(dir, &DB);

	sqlite3_close(DB);

	return 0;
};
int sqlite::createTable(const char* dir, string sql)
{
	sqlite3* DB;
	char* messageError;

	try
	{
		int exit = 0;
		exit = sqlite3_open(dir, &DB);
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK) {
			cerr << "Error in createTable function." << endl;
			sqlite3_free(messageError);
		}
		else
			cout << "Table created Successfully" << endl;
		sqlite3_close(DB);
	}
	catch (const exception& e)
	{
		cerr << e.what();
	}

	return 0;
};
void sqlite::CreateAll(const char* dir)
{
	vector<string> tab;
	tab.push_back("CREATE TABLE IF NOT EXISTS COURSE("
		"CODE  TEXT PRIMARY KEY , "
		"NAME  TEXT NOT NULL, "
		"MAX_STUDENT  INT NOT NULL, "
		"HOURSE  INT NOT NULL,"
		"NUM_OF_CURRENT_STUDENT INT NOT NULL);");

	tab.push_back("CREATE TABLE IF NOT EXISTS STUDENT("
		"ID  INT PRIMARY KEY , "
		"NAME  TEXT NOT NULL, "
		"ACADEMIC_YEAR  TEXT NOT NULL, "
		"PASSWORD  TEXT NOT NULL );");

	tab.push_back("CREATE TABLE IF NOT EXISTS ADMIN("
		"PASSWORD  TEXT PRIMARY KEY , "
		"NAME  TEXT NOT NULL );");

	tab.push_back("CREATE TABLE IF NOT EXISTS Has_Course("
		" CODE TEXT FOREIGN_KEY REFERENCES COURSE(CODE) ,"
		" ID INT FOREIGN_KEY REFERENCES STUDENT(ID) ,"
		" PRIMARY KEY (CODE, ID) );");

	tab.push_back("CREATE TABLE IF NOT EXISTS Course_PreRequired("
		" CODE TEXT FOREIGN_KEY REFERENCES COURSE(CODE) ,"
		" PRE_REQUIRED TEXT ,"
		" PRIMARY KEY (CODE,PRE_REQUIRED) );");

	tab.push_back("CREATE TABLE IF NOT EXISTS Student_FinishedCourse("
		" ID INT FOREIGN_KEY REFERENCES STUDENT(ID) ,"
		" FINISHED_COURSE TEXT ,"
		" PRIMARY KEY (ID,FINISHED_COURSE) );");

	tab.push_back("CREATE TABLE IF NOT EXISTS Student_InProgress("
		" ID INT FOREIGN_KEY REFERENCES STUDENT(ID) ,"
		" IN_PROGRESS TEXT ,"
		" PRIMARY KEY (ID,IN_PROGRESS) );");

	for (int i = 0; i < tab.size(); i++)
	{
		createTable(dir, tab[i]);
	}
}
int sqlite::callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++)
	{
		// column name and value
		v.push_back(argv[i]);
	}
	return 0;
};
void sqlite::selectEditData(const char* dir, string sql, bool isVector, string tableName)
{
	studentMap.clear();
	v.clear();

	sqlite3* DB;
	char* messageError;
	int exit = sqlite3_open(dir, &DB);

	if (isVector == true) {
		exit = sqlite3_exec(DB, sql.c_str(), callback, NULL, &messageError);
	}
	else {
		tableSelected = tableName;
		exit = sqlite3_exec(DB, sql.c_str(), calledit, NULL, &messageError);
	}


	if (exit != SQLITE_OK) {
		cerr << "Error in selectData function." << endl;
		sqlite3_free(messageError);
	}
};
int sqlite::calledit(void* NotUsed, int argc, char** argv, char** azColName)
{
	//cout << endl;
	if (tableSelected == "STUDENT") {
		for (int i = 0; i < argc; i++)
		{
			if (i == 0)
			{
				studentOb.set_Id(stoi(argv[i]));
			}
			else if (i == 1)
			{
				studentOb.set_Name(argv[i]);
			}
			else if (i == 2)
			{
				studentOb.set_AcademicYear(argv[i]);
			}
			else
			{
				studentOb.set_Password(argv[i]);
			}
		}
		studentMap[studentOb.get_Id()] = studentOb;
	}

	else if (tableSelected == "COURSE") {

		for (int i = 0; i < argc; i++)
		{
			if (i == 0)
			{
				courseOb.setCode(argv[i]);
			}
			else if (i == 1)
			{
				courseOb.setName(argv[i]);
			}
			else if (i == 2)
			{
				courseOb.setMaxNumberOfStudents(stoi(argv[i]));
			}
			else if (i == 3)
			{
				courseOb.setHours(stoi(argv[i]));
			}
			else {
				courseOb.setNumOfCurrentStudent(stoi(argv[i]));
			}

		}
		courseMap[courseOb.getCode()] = courseOb;
	}
	else if (tableSelected == "ADMIN") {

		for (int i = 0; i < argc; i++)
		{
			if (i == 0)
			{
				adminOb.setPassword(argv[i]);
			}
			else
			{
				adminOb.setName(argv[i]);
			}

		}
		adminMap[adminOb.getPassword()] = adminOb;
	}
	return 0;
}
// string of function insert
int sqlite::insertData(const char* dir, string TableName, string ColumnName, string variables)
{
	sqlite3* DB;
	char* messageError;
	int exit = sqlite3_open(dir, &DB);
	string sql = "INSERT INTO " + TableName + " " + ColumnName + " VALUES " + variables + " ";
	exit = sqlite3_exec(DB, sql.c_str(), 0, 0, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error in insertData function." << endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Records inserted Successfully!" << endl;

	return 0;
};
int sqlite::DeleteData(const char* dir, string sql)
{
	sqlite3* DB;
	int exit = sqlite3_open(dir, &DB);
	sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);
	if (exit != SQLITE_OK)
	{
		cout << "Error in deleteData function." << endl;
	}
	else
	{
		cout << "the data deleted Successfully!" << endl;
	}
	return 0;
};
vector<string> sqlite::vectorOfData(const char* dir, string sql) {
	selectEditData(dir, sql, true, "");
	return v;
}
map<int, Student> sqlite::mapOfStudentData(const char* dir, string sql) {
	selectEditData(dir, sql, false, "STUDENT");
	return studentMap;
}
map<string, Course> sqlite::mapOfCourseData(const char* dir, string sql) {
	selectEditData(dir, sql, false, "COURSE");
	return courseMap;
}
map<string, Admin> sqlite::mapOfAdminData(const char* dir, string sql) {
	selectEditData(dir, sql, false, "ADMIN");
	return adminMap;
}