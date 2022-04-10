#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "data_stats.h"
#include "data_format.h"

using std::cout;
using std::string;
using std::map;
using std::stringstream;
using std::vector;

vector <CourseInfo> gCourseInfoVector = build_course_data();
KeyStorage keyStore = extract_all_keys (gCourseInfoVector);

void course_average()
{
    float count = 0;
    float sum = 0;
    float average = 0;
    for (int i = 0; i < gCourseInfoVector.size(); i++)
    {
        if (gCourseInfoVector[i].numberGrade != 0)
        {
            sum += gCourseInfoVector[i].numberGrade;
            count++;
        }
    }
    average = sum / count;

    printf ("The class average for %d is: %.1f \n", gCourseInfoVector[0].courseNo, average);
}

void course_pass_rate () {

    float count = 0;
    float passRate = 0;
    int max = gCourseInfoVector.size();

    for (int i = 0; i < max; i++) {

        if (gCourseInfoVector[i].numberGrade >= 73 || gCourseInfoVector[i].grade == "CR") {
            count++;
        }
    }

    passRate = (count/max) * 100;
    printf ("The pass rate of %d is: %.1f%% \n", gCourseInfoVector[0].courseNo, passRate);
}

void course_withdrawal_rate () {
    float count = 0;
    float passRate = 0;
    int max = gCourseInfoVector.size();

    for (int i = 0; i < max; i++) {

        if (gCourseInfoVector[i].numberGrade == 0) {
            count++;
        }
    }
    passRate = (count/max) * 100;
    printf ("The withdrawal rate of %d is: %.1f%% \n", gCourseInfoVector[0].courseNo, passRate);
}

void findAverage (string type, string idName, vector <float> grades, int frequency) {
    float sum = 0;

    for (float grade : grades) {
        sum+=grade;
    }
    cout << "The average grade for " << type << " " << idName << " is " << (sum/frequency) << "\n";
}

void findPassRate (string type, string idName, vector <float> grades, int frequency) {
    float count = 0;
    for (float grade : grades) {
        if (grade >= 73) {
            count++;
        }
    }
    cout << "The pass rate for " << type << " " << idName << " is " << (count/frequency) * 100 << "%" << "\n";
}

void extractStats (string type, vector <string> IDs, map <string, vector<float>> gradesByID, map <string, int> frequencyMap) {

    vector <float> grades;
    for (string id : IDs)  {
        grades = gradesByID[id];
        findAverage (type, id, grades, frequencyMap[id]);
        findPassRate (type, id, grades, frequencyMap[id]);
        printf ("\n");
    }
}

void instructorStats () {

    extractStats ("instructor", keyStore.getInstructorIDs(), keyStore.getInstructorGrades(), keyStore.getInstructorFrequency());
    printf("\n");
}

void termStats () {
    extractStats ("term", keyStore.getTermIDs(), keyStore.getTermGrades(), keyStore.getTermFrequency());
    printf("\n");
}

void sectionStats () {
    extractStats ("section", keyStore.getSectionIDs(), keyStore.getSectionGrades(), keyStore.getSectionFrequency());
    printf("\n");
}
