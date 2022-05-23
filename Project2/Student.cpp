#include"Start.h"
#include <algorithm>
using namespace std;

sqlite sq;

Student::Student() {
    id = 0;
    name = password = academicYear = "";
};

Student::Student(int id, string name, string academicYear, string password) {
    this->name = name;
    this->id = id;
    this->password = password;
    this->academicYear = academicYear;
};

void Student::login(map<int, class Student>& studentMap) {
    int* loginId = new int;
    string* loginPassword = new string;

    map<int, class Student>::iterator it = studentMap.begin();
    while (it != studentMap.end()) {
        cout << "ID: " << it->first << "  " << "Password: " << it->second.password << endl;
        it++;
    }
    while (true) {

        cout << "Enter Your ID: ";
        cin >> *loginId;
        cout << "Enter Your password: ";
        cin >> *loginPassword;


        if (studentMap[*loginId].password == *loginPassword)
        {
            id = *loginId;
            password = *loginPassword;
            cout << "\n\t**Login Successfull" << endl;
            break;
        }
        else {
            cout << "\n*Incorrect ID or password! please try again*" << endl;
        }
    }
    delete loginId, loginPassword;
}
void Student::editData(map<int, class Student>& studentMap) //Edited
{
    int* choice = new int;
    string* newValue = new string;

    do {
        cout << "\n= Your Current Data =\n" <<
            "---------------------\n" <<
            "ID:  " << id <<
            "\nNAME:  " << studentMap[id].name <<
            "\nPassword:  " << studentMap[id].password <<
            "\nACADEMIC_YEAR:  " << studentMap[id].academicYear << "\n\n";

        cout << "= Choose what you Want to Edit =\n" <<
            "--------------------------------\n" <<
            "Options: \n" <<
            "1. Name \n" <<
            "2. Password \n";

        cin >> *choice;

        while (*choice > 3 || *choice < 0)
        {
            cout << "Invalid input please try again" << endl;
            cin >> *choice;
        }
        if (*choice == 1)                            //Editing the Name
        {
            cout << "Enter the New Name: ";
            cin >> *newValue;
            cout << endl;
            if (studentMap[id].name != *newValue)
            {
                studentMap[id].name = *newValue;
                cout << "You Edited the Name successfully!";
            }
            else
            {
                cout << "You entered the same name!!" << endl;
            }
        }
        else if (*choice == 2)                         //Editing the Password
        {
            cout << "Enter the New Password: ";
            cin >> *newValue;
            cout << endl;
            if (studentMap[id].password != *newValue)
            {
                studentMap[id].password = *newValue;
                cout << "You Edited the password successfully!";
            }
            else
            {
                cout << "You entered the same Password!!" << endl;
            }
        }

        cout << "\nOptions: \n" <<
            "1. Continue editing \n" <<
            "2. Exit \n";
        cin >> *choice;

    } while (*choice != 2);
    delete choice, newValue;

}
void Student::viewSpecificCourseDetails(map<string, class Course>& courseMap) // edited
{
    string* courseName = new string;
    bool* found = new bool;
    *found = false;
    int* check = new int;
    do {
        cout << "Enter the Name of the Course: ";
        cin >> *courseName;
        map<string, class Course>::iterator it = courseMap.begin();

        while (it != courseMap.end())
        {
            if (*courseName == it->second.getName())
            {
                *found = true;
                break;
            }
            it++;
        }
        if (!*found)
        {
            cout << "The Course Not found!" << endl;
        }
        else
        {
            cout << "\n----------------------------------------------------" << endl;
            cout << "** " << "The Details of " << *courseName << " Course **" << "" << endl;
            cout << "Code: " << it->first << endl;
            cout << "Name: " << it->second.getName() << endl;
            cout << "Maximum Student: " << it->second.getMaxNumberOfStudents() << endl;
            cout << "Number of Hours: " << it->second.getHours() << endl;
            cout << "----------------------------------------------------\n" << endl;
        }

        cout << "\nOptions: \n" <<
            "1. view details of course \n" <<
            "2. Exit \n";
        cin >> *check;
    } while (*check == 1);
    delete courseName, found, check;
}
void Student::viewStudentCourses(map<int, vector<string>>& inProgrssMap,
    map<int, vector<string>>& finishedMap) {

    if (inProgrssMap[id].size() != 0)        //Viewing the In-Progress courses 
    {
        cout << "= Your In-Progress Courses =\n" << "----------------------------" << endl;
        for (int i = 0; i < inProgrssMap[id].size(); i++)
        {
            cout << "Course Name: " << inProgrssMap[id][i] << endl;
        }
        cout << "\n";
    }
    else
    {
        cout << "\nyou doesn't have In-Progress Courses!" << endl;
        cout << "==========================================" << endl;
    }


    if (finishedMap[id].size() != 0)           //Viewing the finished courses 
    {
        cout << "= Your Finished Courses =\n" << "-------------------------" << endl;
        for (int i = 0; i < finishedMap[id].size(); i++)
        {
            cout << "Course Name: " << finishedMap[id][i] << endl;
        }
        cout << "\n";
    }
    else {
        cout << "you doesn't have Finished Courses!\n" << endl;
    }

};
void Student::viewAvailableCourses(map<string, class Course>& courseMap,
    map<int, vector<string>>& finishedMap,
    map<int, vector<string>>& inProgrssMap) //Edited 
{
    int x = 0;
    int* tmp1 = new int;
    int* tmp2 = new int;
    *tmp1 = *tmp2 = 0;
    int* inProgressVectorSize = new int;
    *inProgressVectorSize = inProgrssMap[id].size();

    int* finishedVectorSize = new int;
    *finishedVectorSize = finishedMap[id].size();

    bool* findFirstItem = new bool;
    *findFirstItem = false;
    vector<string>* avaliableCourses = new vector<string>;
    map<string, class Course>::iterator it = courseMap.begin();

    cout << "\n----------------------------------------------------" << endl;

    while (it != courseMap.end())
    {
        if (it->second.getNumOfCurrentStudent() < it->second.getMaxNumberOfStudents()) {
            (*avaliableCourses).push_back(it->second.getName());
        }
        it++;
    }

    sort(inProgrssMap[id].begin(), inProgrssMap[id].end());
    sort(finishedMap[id].begin(), finishedMap[id].end());
    sort((*avaliableCourses).begin(), (*avaliableCourses).end());

    for (int i = 0; i < (*avaliableCourses).size(); i++)
    {
        if (!inProgrssMap[id].empty() && (*inProgressVectorSize) > *tmp1 && (*avaliableCourses)[i] == inProgrssMap[id][*tmp1])
        {
            (*tmp1)++;
        }
        else if (!finishedMap[id].empty() && (*finishedVectorSize) > (*tmp2) && (*avaliableCourses)[i] == finishedMap[id][*tmp2])
        {
            (*tmp2)++;
        }
        else
        {

            if (!*findFirstItem)
            {
                cout << "The List of Available Courses" << endl;
                *findFirstItem = true;
            }
            cout << "Name: " << (*avaliableCourses)[i] << endl;
            listAvailableCourse.push_back((*avaliableCourses)[i]);

        }
    }

    if (!*findFirstItem)
    {
        cout << "There is No Available Course!!\n";
    }
    cout << "----------------------------------------------------\n" << endl;
    delete tmp1, tmp2, inProgressVectorSize, finishedVectorSize, findFirstItem, avaliableCourses;
}

void Student::registerForCourse(map <string, vector<string>> prerequiredMap,
    map<int, vector<string>>& finishedMap,
    map<string, class Course>& courseMap,
    map <string, vector<string>>& hasCourseMap,
    map<int, vector<string>>& inProgrssMap) {

    string* courseName = new string;
    string* courseCode = new string;
 
    bool* found = new bool;
    bool* noPreRequiredProblem = new bool;
    *found = *noPreRequiredProblem = false;

    cout << "you can register in one of these courses" << endl;
    viewAvailableCourses(courseMap, finishedMap, inProgrssMap);

    cout << "Enter the Name of Course You Want To Register" << endl;
    cin >> *courseName;
    for (int i = 0; i < listAvailableCourse.size(); i++) {
        if (*courseName == listAvailableCourse[i]) {
            *found = true;
        }
    }
    if (*found)
    {
        map<string, class Course>::iterator it = courseMap.begin();
        cout << "------------------------------------------------------------------" << endl;
        while (it != courseMap.end()) {
            if (it->second.getName() == *courseName)
            {
                *courseCode = it->first;
                break;
            }
            it++;
        }
        sort(prerequiredMap[*courseCode].begin(), prerequiredMap[*courseCode].end());
        sort(finishedMap[id].begin(), finishedMap[id].end());

        if (prerequiredMap[*courseCode].empty())      //check Student's pre-required courses 
        {
            *noPreRequiredProblem = true;
        }
        else
        {
            int j = prerequiredMap[*courseCode].size() - 1;
            for (int i = finishedMap[id].size() - 1; i >= 0; i--)
            {
                if (finishedMap[id][i] == prerequiredMap[*courseCode][j])
                {
                    prerequiredMap[*courseCode].pop_back();
                    j--;
                }
                if (prerequiredMap[*courseCode].empty())
                {
                    *noPreRequiredProblem = true;
                    break;
                }
            }
        }

        if (*noPreRequiredProblem) {
            courseMap[*courseCode].setNumOfCurrentStudent(courseMap[*courseCode].getNumOfCurrentStudent() + 1);
            hasCourseMap[*courseCode].push_back(to_string(id));
            inProgrssMap[id].push_back(*courseName);
            cout << "\nThe Course is Registred successfully" << endl;
        }
        else {
            cout << "\nYou Can't Register For The Course Due to The Pre-required Courses!!" << endl;
        }

    }
    else {
        cout << "\nWrong! This Course is not available" << endl;;
    }
    delete courseName, courseCode, found, noPreRequiredProblem;
}


int Student::get_Id() {
    return id;
}
string Student::get_Name() {
    return name;
}
string Student::get_Password() {
    return password;
}
string Student::get_AcademicYear() {
    return academicYear;
}
void Student::set_Id(int id) {
    this->id = id;
}
void Student::set_Name(string name) {
    this->name = name;
}
void Student::set_Password(string password) {
    this->password = password;
}
void Student::set_AcademicYear(string AcademicYear) {
    this->academicYear = AcademicYear;
}
