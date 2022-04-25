#ifndef DATA_FORMAT
#define DATA_FORMAT

#include <vector>
#include <string>
#include <map>
#include "courseStruct.h"

using std::map;
using std::string;
using std::vector;

class KeyStorage
{
private:
    map<string, vector<float>> gradesByInstructor;
    map<string, int> instructorFrequency;

    map<string, vector<float>> gradesByTerm;
    map<string, int> termFrequency;

    map<string, vector<float>> gradesBySection;
    map<string, int> sectionFrequency;

public:
    KeyStorage ();

    KeyStorage(vector <CourseInfo> infoVector) {

        for (int i = 0; i < infoVector.size(); i++)
        {
            gradesByInstructor[infoVector[i].instructorID].push_back(infoVector[i].numberGrade);
            instructorFrequency[infoVector[i].instructorID]++;

            gradesByTerm[infoVector[i].termID].push_back(infoVector[i].numberGrade);
            termFrequency[infoVector[i].termID]++;

            gradesBySection[infoVector[i].sectionID].push_back(infoVector[i].numberGrade);
            sectionFrequency[infoVector[i].sectionID]++;
        }
    }

    map<string, vector<float>> getInstructorGrades()
    {

        return gradesByInstructor;
    }

    map<string, vector<float>> getTermGrades()
    {

        return gradesByTerm;
    }

    map<string, vector<float>> getSectionGrades()
    {
        return gradesBySection;
    }

    map<string, int> getInstructorFrequency()
    {
        return instructorFrequency;
    }

    map<string, int> getTermFrequency()
    {
        return termFrequency;
    }

    map<string, int> getSectionFrequency()
    {
        return sectionFrequency;
    }

    vector<string> getInstructorIDs()
    {

        vector<string> IDs;

        for (map<string, int>::iterator it = instructorFrequency.begin(); it != instructorFrequency.end(); it++)
        {
            IDs.push_back(it->first);
        }

        return IDs;
    }

    vector<string> getTermIDs()
    {

        vector<string> IDs;

        for (map<string, int>::iterator it = termFrequency.begin(); it != termFrequency.end(); it++)
        {
            IDs.push_back(it->first);
        }

        return IDs;
    }

    vector<string> getSectionIDs()
    {

        vector<string> IDs;

        for (map<string, int>::iterator it = sectionFrequency.begin(); it != sectionFrequency.end(); it++)
        {
            IDs.push_back(it->first);
        }

        return IDs;
    }
};

vector <CourseInfo> build_course_data (string path);
extern vector <CourseInfo> gCourseInfoVector;
int add_enrollment_record (string data);
string update_grade (string emplid, int courseNo, int grade);
string find_student (string emplid);
bool validate_string (string emplid);
bool validate_instructorID (string str);
bool validate_sectionID (string str);
bool validate_termID (string str);

#endif