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
    KeyStorage(map<string, vector<float>> instructorGrades, map<string, int> instructorFreq,
               map<string, vector<float>> termGrades, map<string, int> termFreq,
               map<string, vector<float>> sectionGrades, map<string, int> sectionFreq)
    {
        gradesByInstructor = instructorGrades;
        instructorFrequency = instructorFreq;

        gradesByTerm = termGrades;
        termFrequency = termFreq;

        gradesBySection = sectionGrades;
        sectionFrequency = sectionFreq;
    };

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

KeyStorage extract_all_keys(vector<CourseInfo> infoVector);
vector<CourseInfo> build_course_data();

#endif