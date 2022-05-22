#include"Start.h"

Course::Course(string code, string name, int maxNumberOfStudents, int hours, int numOfCurrentStudent)
{
	this->name = name;
	this->code = code;
	this->maxNumberOfStudents = maxNumberOfStudents;
	this->hours = hours;
	this->numOfCurrentStudent = numOfCurrentStudent;
};
Course::Course() {

}
void Course::setMaxNumberOfStudents(int maxNumberOfStudents) {
	this->maxNumberOfStudents = maxNumberOfStudents;
}
void Course::setHours(int hours) {
	this->hours = hours;
}
void Course::setName(string name) {
	this->name = name;
}
void Course::setCode(string code) {
	this->code = code;
}
void Course::setNumOfCurrentStudent(int numOfCurrentStudent)
{
	this->numOfCurrentStudent = numOfCurrentStudent;
}

int Course::getMaxNumberOfStudents() {
	return maxNumberOfStudents;
}
int Course::getHours() {
	return hours;
}
int Course::getNumOfCurrentStudent()
{
	return numOfCurrentStudent;
}
string Course::getName() {
	return name;
}
string Course::getCode() {
	return code;
}