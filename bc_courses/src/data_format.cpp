#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>

#include "data_format.h"
#include "io.h"

using std::map;
using std::string;
using std::stringstream;
using std::vector;

vector<CourseInfo> build_course_data()
{
    string emplData, instructorData, termData, sectionData, courseNoData, gradeData;
    vector<CourseInfo> courseInfoVector;
    stringstream readDataStream(read_data());

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

    return courseInfoVector;
}

// Store all these keys in a class
KeyStorage extract_all_keys (vector <CourseInfo> infoVector)
{

    vector<CourseInfo> gCourseInfoVector = infoVector;

    map<string, vector<float>> gradesByInstructor;
    map<string, int> instructorFrequency;

    map<string, vector<float>> gradesByTerm;
    map<string, int> termFrequency;

    map<string, vector<float>> gradesBySection;
    map<string, int> sectionFrequency;

    for (int i = 0; i < gCourseInfoVector.size(); i++)
    {

        gradesByInstructor[gCourseInfoVector[i].instructorID].push_back(gCourseInfoVector[i].numberGrade);
        instructorFrequency[gCourseInfoVector[i].instructorID]++;

        gradesByTerm[gCourseInfoVector[i].termID].push_back(gCourseInfoVector[i].numberGrade);
        termFrequency[gCourseInfoVector[i].termID]++;

        gradesBySection[gCourseInfoVector[i].sectionID].push_back(gCourseInfoVector[i].numberGrade);
        sectionFrequency[gCourseInfoVector[i].sectionID]++;
    }

    KeyStorage keyStore (gradesByInstructor, instructorFrequency, gradesByTerm, termFrequency, gradesBySection, sectionFrequency);
    return keyStore;
}
