#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
using namespace std;
class sqlite {
public:
	sqlite();
	string se = "SELECT * FROM STUDENT ;";

	sqlite3_stmt* stmt;
	const char* address = "Data.db";
	int createDB(const char* dir);
	int createTable(const char* dir, string sql);
	int insertData(const char* dir, string TableName, string ColumnName, string variables);
	void selectEditData(const char* dir, string sql, bool isVector, string tableName);
	static int callback(void* NotUsed, int argc, char** argv, char** azColName);
	static int calledit(void* NotUsed, int argc, char** argv, char** azColName);
	int DeleteData(const char* dir, string sql);
	vector<string> vectorOfData(const char* dir, string sql);
	void CreateAll(const char* dir);
	map<int, Student> mapOfStudentData(const char* dir, string sql);
	map<string, Course> mapOfCourseData(const char* dir, string sql);
	map<string, Admin> mapOfAdminData(const char* dir, string sql);

};