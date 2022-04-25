#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include "data_format.h"

using std::map;
using std::string;
using std::stringstream;
using std::vector;

vector<CourseInfo> build_course_data(string data)
{
    string emplData, instructorData, termData, sectionData, courseNoData, gradeData;
    vector<CourseInfo> courseInfoVector;
    stringstream readDataStream(data);

    while (getline(readDataStream, emplData, ','))
    {

        CourseInfo courseInfo;
        courseInfo.emplID = emplData;

        getline(readDataStream, courseNoData, ',');
        courseInfo.courseNo = stoi(courseNoData);

        getline(readDataStream, instructorData, ',');
        courseInfo.instructorID = instructorData;

        getline(readDataStream, termData, ',');
        courseInfo.termID = termData;

        getline(readDataStream, sectionData, ',');
        courseInfo.sectionID = sectionData;

        readDataStream >> gradeData;
        courseInfo.grade = gradeData;

        courseInfo.convert_grade();

        courseInfoVector.push_back(courseInfo);
    }

    gCourseInfoVector = courseInfoVector;
    return courseInfoVector;
}

string remove_white_space(string str)
{

    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

bool validate_termID (string str) {
    string temp = str;
    temp.erase(temp.begin());
    int num = stoi(temp);

    if (str.size() != 3)
    {
        printf("Invalid size of term ID\n");
        return false;
    }

    if (str[0] != 'T')
    {
        printf("Term ID doesn't start with T\n");
        return false;
    }

    if (num < 1 || num > 99)
    {
        printf("Invalid term ID #\n");
        return false;
    }

    return true;

}

bool validate_sectionID (string str) {
    string temp = str;
    temp.erase(temp.begin());
    int num = stoi(temp);

    if (str.size() != 3)
    {
        printf("Invalid size of section ID\n");
        return false;
    }

    if (str[0] != 'S')
    {
        printf("Instructor ID doesn't start with S\n");
        return false;
    }

    if (num < 1 || num > 99)
    {
        printf("Invalid section ID #\n");
        return false;
    }

    return true;
}

bool validate_instructorID (string str) {

    string temp = str;
    temp.erase(temp.begin());
    int num = stoi(temp);

    if (str.size() != 3)
    {
        printf("Invalid size of instructor ID\n");
        std::cout << "ID size: " << str.size();
        return false;
    }

    if (str[0] != 'I')
    {
        printf("Instructor ID doesn't start with I\n");
        return false;
    }

    if (num < 1 || num > 99)
    {
        printf("Invalid instructor ID #\n");
        return false;
    }

    return true;

}

bool validate_string(string emplid)
{
    string temp = emplid;
    temp.erase(temp.begin());
    int num = stoi(temp);

    // EMPLID validation
    if (emplid.size() != 5)
    {
        printf("Invalid size of EMPLID\n");
        return false;
    }

    if (num < 1 || num > 9999)
    {
        printf("Invalid EMPLID #: %d \n", num);
        return false;
    }

    if (emplid[0] != 'E')
    {
        printf("EMPLID doesn't start with E\n");
        return false;
    }

    return true;
}

bool validate_string(vector<string> str)
{

    int courseNo = stoi(str[1]);
    int num;
    string temp;
    if (str.size() != 6)
    {
        printf("Invalid amount of fields\n");
        return false;
    }

    temp = str[0];
    temp.erase(temp.begin());
    num = stoi(temp);

    // EMPLID validation
    if (str[0].size() != 5)
    {
        printf("Invalid size of EMPLID\n");
        return false;
    }

    if (num < 1 || num > 9999)
    {
        printf("Invalid EMPLID # \n");
        return false;
    }

    if (str[0][0] != 'E')
    {
        printf("EMPLID doesn't start with E\n");
        return false;
    }

    // Instructor ID validation
    temp = str[2];
    temp.erase(temp.begin());
    num = stoi(temp);

    if (str[2].size() != 3)
    {
        printf("Invalid size of instructor ID\n");
        return false;
    }

    if (str[2][0] != 'I')
    {
        printf("Instructor ID doesn't start with I\n");
        return false;
    }

    if (num < 1 || num > 99)
    {
        printf("Invalid instructor ID #\n");
        return false;
    }

    // Term ID validation
    temp = str[3];
    temp.erase(temp.begin());
    num = stoi(temp);

    if (str[3].size() != 3)
    {
        printf("Invalid size of term ID\n");
        return false;
    }

    if (str[3][0] != 'T')
    {
        printf("Term ID doesn't start with T\n");
        return false;
    }

    if (num < 1 || num > 99)
    {
        printf("Invalid term ID #\n");
        return false;
    }

    // Section ID validation
    temp = str[4];
    temp.erase(temp.begin());
    num = stoi(temp);

    if (str[4].size() != 3)
    {
        printf("Invalid size of term ID\n");
        return false;
    }

    if (str[4][0] != 'S')
    {
        printf("Section ID doesn't start with S\n");
        return false;
    }

    if (num < 1 || num > 99)
    {
        printf("Invalid section ID #\n");
        return false;
    }

    if (courseNo != 1115 && courseNo != 3130 && courseNo != 3115)
    {
        printf("Course doesn't exist\n");
        return false;
    }
    char letter = str[5][0];

    if (str[5].size() > 2)
    {
        printf("Invalid size of grade\n");
        printf ("Size of grade: %ld\n", str[5].size());
        //std::cout << str[5];
        return false;
    }

    if (letter < 65 || letter > 68 && (letter != 70 && letter != 87))
    {
        printf("The grade is invalid\n");
        return false;
    }
    return true;
}

int add_enrollment_record(string data)
{
    string trimmedData;
    bool valid;
    trimmedData = remove_white_space(data);
    stringstream readDataStream(trimmedData);
    string str;

    vector<string> courseString;

    while (getline(readDataStream, str, ','))
    {
        courseString.push_back(str);
    }

    if (!validate_string(courseString))
    {
        return 0;
    }

    CourseInfo courseInfo;
    string temp;

    courseInfo.emplID = courseString[0];

    courseInfo.courseNo = stoi(courseString[1]);

    courseInfo.instructorID = courseString[2];

    courseInfo.termID = courseString[3];

    courseInfo.sectionID = courseString[4];

    courseInfo.grade = courseString[5];

    courseInfo.convert_grade();

    gCourseInfoVector.push_back(courseInfo);

    return 1;
}

string update_grade (string emplid, int courseNo, int grade)
{
    string id;
    for (int i = 0; i < gCourseInfoVector.size(); i++)
    {
        id = gCourseInfoVector[i].emplID;
        id.erase(id.begin());

        if (id == emplid && gCourseInfoVector[i].courseNo == courseNo)
        {
            gCourseInfoVector[i].numberGrade = grade;
            return "Student grade updated successfully\n";
            break;
        }
    }
    return "The student doesn't exist\n";
}

string find_student (string emplid) {

    string id;
    string rec;
    int count = 0;

    emplid = remove_white_space(emplid);

    for (int i = 0; i < gCourseInfoVector.size(); i++)
    {
        id = remove_white_space (gCourseInfoVector[i].emplID);
        if (id[0] == 13) {
            id.erase(id.begin());
        }

        if (id == emplid) {
            rec += id + " " + std::to_string(gCourseInfoVector[i].courseNo) + " " + std::to_string(gCourseInfoVector[i].numberGrade) + "\n"; 
            count++; 
        }
    }

    if (count == 0) {
        return ("Student doesn't exist\n");
    }

    return rec;
}
