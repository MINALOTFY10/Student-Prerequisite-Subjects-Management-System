#include <map>

class Student {

    int id;
    string name;
    string password;
    string academicYear;

public:
    Student();
    Student(int, string, string, string);
    void login(map<int, class Student>& ptr);
    void viewAvailableCourses(map<string, class Course>& ptr1, map<int, vector<string>>& ptr2,
        map<int, vector<string>>& ptr3);

    void viewSpecificCourseDetails(map<string, class Course>& ptr);
    void viewStudentCourses(map<int, vector<string>>& ptr1, map<int, vector<string>>& ptr2);
    void registerForCourse(map <string, vector<string>> ptr1, map<int, vector<string>>& ptr2,
        map<string, class Course>& ptr3, map <string, vector<string>>& ptr4,
        map<int, vector<string>>& ptr5);

    void editData(map<int, class Student>& ptr);
    int get_Id();
    string get_Name();
    string get_Password();
    string get_AcademicYear();
    void set_Id(int);
    void set_Name(string);
    void set_Password(string);
    void set_AcademicYear(string);
    vector<string> listAvailableCourse;
};