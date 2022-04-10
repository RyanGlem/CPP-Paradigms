// Header file that deinfes the structure for course information

#ifndef COURSE_HEADER
#define COURSE_HEADER
#include <string>

using std::string;

struct CourseInfo
{

    int courseNo;
    int numberGrade;
    string emplID;
    string instructorID;
    string sectionID;
    string termID;
    string grade;

    int convert_grade()
    {

        const char *letterGrade = grade.c_str();

        switch (letterGrade[0])
        {

        case 'A':
            if (letterGrade[1] == '+')
                return numberGrade = 98;
            if (letterGrade[1] == '-')
                return numberGrade = 90;
            numberGrade = 93;
            break;

        case 'B':
            if (letterGrade[1] == '+')
                return numberGrade = 89;
            if (letterGrade[1] == '-')
                return numberGrade = 80;
            numberGrade = 83;
            break;

        case 'C':
            if (letterGrade[1] == '+')
                return numberGrade = 79;
            if (letterGrade[1] == '-')
                return numberGrade = 70;
            if (letterGrade[1] == 'R') {
                return numberGrade = 1;
            }
            numberGrade = 73;
            break;

        case 'D':
            if (letterGrade[1] == '+')
                return numberGrade = 69;
            numberGrade = 65;
            break;

        case 'F':
            numberGrade = 59;
            break;
        default:
            numberGrade = 0;
        }
        return 0;
    }
};

#endif