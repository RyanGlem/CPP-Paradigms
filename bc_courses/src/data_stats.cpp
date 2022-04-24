#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "data_stats.h"
#include "data_format.h"
#include "io.h"

using std::cout;
using std::map;
using std::string;
using std::stringstream;
using std::vector;

vector <CourseInfo> gCourseInfoVector;

float course_average (int course)
{
    float count = 0;
    float sum = 0;
    float average = 0;

    int index;

    for (int i = 0; i < gCourseInfoVector.size(); i++)
    {
        if (gCourseInfoVector[i].numberGrade != 0 && gCourseInfoVector[i].courseNo == course)
        {
            sum += gCourseInfoVector[i].numberGrade;
            count++;
            index = i;
        }
    }
    average = sum / count;
    return average;
}

float course_pass_rate(int course)
{

    float count = 0;
    float passRate = 0;
    int max = gCourseInfoVector.size();
    int index;

    for (int i = 0; i < max; i++)
    {

        if ((gCourseInfoVector[i].numberGrade >= 73 || gCourseInfoVector[i].grade == "CR") && gCourseInfoVector[i].courseNo == course)
        {
            count++;
            index = i;
        }
    }

    passRate = (count / max) * 100;
    return passRate;
}

float course_withdrawal_rate(int course)
{
    float count = 0;
    float passRate = 0;
    int max = gCourseInfoVector.size();
    int index;

    for (int i = 0; i < max; i++)
    {

        if (gCourseInfoVector[i].numberGrade == 0 && gCourseInfoVector[i].courseNo == course)
        {
            count++;
            index = i;
        }
    }
    passRate = (count / max) * 100;
    return passRate;
}

float findAverage (string type, string idName, vector<float> grades, int frequency)
{
    float sum = 0;
    float precision = 0;

    for (float grade : grades)
    {
        if (grade != 1)
        {
            sum += grade;
        }
    }
    sum = sum / frequency;
    return sum;
}

float findPassRate(string type, string idName, vector<float> grades, int frequency)
{
    float count = 0;
    float pass_rate = 0;
    for (float grade : grades)
    {
        if (grade >= 73 || grade == 1)
        {
            count++;
        }
    }

    pass_rate = (count / frequency) * 100; 
    return pass_rate;
}

float findWithdrawalRate(string type, string idName, vector<float> grades, int frequency)
{
    float count = 0;
    float withdrawal_rate = 0;
    for (float grade : grades)
    {
        if (grade == 0)
        {
            count++;
        }
    }

    withdrawal_rate = (count / frequency) * 100;
    return withdrawal_rate;
}

int find_index(int course)
{
    for (int i = 0; i < gCourseInfoVector.size(); i++)
    {
        if (gCourseInfoVector[i].courseNo == course) {
            return i;
        }
    }
    return 0;
}

string statFormat (float average, float pass_rate, float withdrawal_rate, string id, string type) {

    string form;
    form = "The average grade for " + type + " " + id + " is " + std::to_string(average) + "\n";
    
    form += "The pass rate for " + type + " " + id + " is " + std::to_string(pass_rate) + "%\n";

    form += "The withdrawal rate for " + type + " " + id + " is " + std::to_string(withdrawal_rate) + "%\n\n";

    return form;
}

string extractStats(string type, vector<string> IDs, map<string, vector<float>> gradesByID, map<string, int> frequencyMap, int course, string ID)
{
    vector<float> grades;
    string report;
    int count = 0;
    int index = find_index(course);
    for (string id : IDs)
    {
        //id.erase(id.begin());
        if (gCourseInfoVector[index].courseNo == course && ID == id)
        {
            grades = gradesByID[id];
            report += statFormat (
                findAverage(type, id, grades, frequencyMap[id]), 
                findPassRate(type, id, grades, frequencyMap[id]),
                findWithdrawalRate(type, id, grades, frequencyMap[id]),
                id,
                type);
            count++;
        }
        index++;
    }

    if (count == 0) {
        return "The ID doesn't exist";
    }

    return report;
}

string extractStats (string type, vector<string> IDs, map<string, vector<float>> gradesByID, map<string, int> frequencyMap, int course)
{
    vector<float> grades;

    string report;
    int count = 0;
    int index = find_index(course);
    for (string id : IDs) {
        //id.erase(id.begin());
        if (gCourseInfoVector[index].courseNo == course)
        {
            grades = gradesByID[id];
            report += statFormat (
                findAverage(type, id, grades, frequencyMap[id]), 
                findPassRate(type, id, grades, frequencyMap[id]),
                findWithdrawalRate(type, id, grades, frequencyMap[id]),
                id,
                type);
            count++;
        }
        index++;
    }

    if (count == 0) {
        return "The ID doesn't exist";
    }

    return report;
}

string instructorStats (int course)
{

    KeyStorage keyStore(gCourseInfoVector);
    string report = extractStats("instructor", keyStore.getInstructorIDs(), keyStore.getInstructorGrades(), keyStore.getInstructorFrequency(), course);
    return report;
}

string instructorStats(int course, string ID)
{

    KeyStorage keyStore(gCourseInfoVector);
    string report = extractStats("instructor", keyStore.getInstructorIDs(), keyStore.getInstructorGrades(), keyStore.getInstructorFrequency(), course, ID);
    return report;
}

string termStats(int course)
{

    KeyStorage keyStore (gCourseInfoVector);
    string report = extractStats("term", keyStore.getTermIDs(), keyStore.getTermGrades(), keyStore.getTermFrequency(), course);
    return report;
}

string termStats(int course, string ID)
{

    KeyStorage keyStore(gCourseInfoVector);
    string report = extractStats("term", keyStore.getTermIDs(), keyStore.getTermGrades(), keyStore.getTermFrequency(), course, ID);
    return report;
}

string sectionStats(int course)
{

    KeyStorage keyStore(gCourseInfoVector);
    string report = extractStats("section", keyStore.getSectionIDs(), keyStore.getSectionGrades(), keyStore.getSectionFrequency(), course);
    return report;
}

string sectionStats(int course, string ID)
{

    KeyStorage keyStore(gCourseInfoVector);
    string report = extractStats("section", keyStore.getSectionIDs(), keyStore.getSectionGrades(), keyStore.getSectionFrequency(), course, ID);
    return report;
}
