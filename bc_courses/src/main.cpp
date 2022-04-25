#include <iostream>
#include <vector>
#include <fstream>
#include <iostream>
#include "data_stats.h"
#include "data_format.h"
#include "io.h"

using std::cin;
using std::cout;
using std::string;
using std::vector;

int main()
{
    string dataChunk;
    string s;
    string courseNum;
    string studentString;
    string gradeString;
    string emplid;
    string answerString;
    string instructorID;
    string termID;
    string sectionID;
    string courses[3] = {"../data/1115.csv", "../data/3115.csv", "../data/3130.csv"};
    
    bool test = true;
    bool flag = true;
    int answer;
    int courseNo;
    char ans;
    char search;
    std::ifstream testInputs ("testinput.txt");

    printf ("Reading in data\n");
    dataChunk = read_data(courses[0]);
    dataChunk += read_data(courses[1]);
    dataChunk += read_data(courses[2]);
    build_course_data(dataChunk);

    do
    {
        printf("Enter in a course for information\n");
        printf("0 : Close\n");
        printf("1 : Course Statistics\n");
        printf("2 : Add student\n");
        printf("3 : Update student grade\n");
        printf("4 : Find Student\n");

        test ? getline (testInputs, answerString) : cin >> answerString;
        answer = stoi (answerString);
        switch (answer)
        {
        case 0:
            write_data(s);
            break;
        case 1:
            printf ("Enter in the course number to display statistics\n");

            test ? getline (testInputs, courseNum) : cin >> courseNum;
            courseNo = stoi (courseNum);

            if (courseNo != 1115 && courseNo != 3130 && courseNo != 3115)
            {
                if (test) {
                    s += "Invalid course number " + std::to_string (courseNo)+"\n";
                    //write_data(s);
                    break;
                } else {
                    printf("Invalid course number %d\n", courseNo);
                    break;
                }
            }

            if (test) {
                s += "The average for " + courseNum + "is " + std::to_string (course_average(courseNo)) + "\n";
                //write_data (s);

                s += "The pass rate for " + courseNum + "is %" + std::to_string (course_pass_rate(courseNo)) + "\n";
                //write_data (s);

                s += "The withdrawal rate for " + courseNum +"is %" + std::to_string (course_withdrawal_rate(courseNo)) + "\n\n";
                //write_data (s);
            } else {
                printf ("The average for %d is %.2f%%\n", courseNo, course_average(courseNo));
                printf ("The pass rate for %d is %.2f%%\n", courseNo, course_pass_rate(courseNo));
                printf ("The withdrawal rate for %d is %.2f%%\n", courseNo, course_withdrawal_rate(courseNo));
            }

            printf("Enter in a key for section, term, or instructor statistics\n");
            printf("n : Close\n");
            printf("i : Instructor Statistics\n");
            printf("t : Term Statistics\n");
            printf("s : Section Statistics\n");

            test ? getline(testInputs, answerString) : cin >> answerString;
            ans = answerString[0];
            switch (ans)
            {
            case 'i':
                printf("Search for specific instructor?\n");
                printf("Y / N\n");

                test ? getline(testInputs, answerString) : cin >> answerString;
                search = answerString[0];
                if (tolower(search) == 'y') {
                    printf ("Type in instructor ID\n");
                    test ? getline (testInputs, answerString) : cin >> answerString;
                    answerString.erase(answerString.size() - 1);
                    instructorID = answerString;
                    if (validate_instructorID(instructorID)) {
                        if (test) {
                            s += instructorStats (courseNo, instructorID);
                            break;
                        } else {
                            string temp = instructorStats (courseNo, instructorID);
                            printf ("%s", temp.c_str());
                            break;
                        }
                    } else {
                        s+= "Invalid instructor ID\n";
                    }
                } else if (tolower(search) == 'n') {
                    if (test) {
                     s += instructorStats(courseNo);
                     break;
                    } else {
                        string temp = instructorStats (courseNo);
                        printf ("%s", temp.c_str());
                        break;
                    }
                } else {
                    if (test) {
                        s += "Invalid response\n";
                        break;
                    } else {
                        printf ("Invalid response\n");
                        break;
                    }
                }
                break;
            case 't':
                printf("Search for specific term?\n");
                printf("Y / N\n");
                test ? getline(testInputs, answerString) : cin >> answerString;
                search = answerString[0];

                if (tolower(search) == 'y') {
                    printf ("Type in term ID\n");
                    test ? getline(testInputs, answerString) : cin >> answerString;
                    answerString.erase(answerString.size() - 1);
                    termID = answerString;
                    if (validate_termID(termID)) {
                        if (test) {
                            s += termStats (courseNo, termID);
                            break;
                        } else {
                            string temp = termStats (courseNo, termID);
                            printf ("%s", temp.c_str());
                            break;
                        }
                    } else {
                        s+="Term ID is invalid\n";
                        break;
                    }
                } else if (tolower(search) == 'n') {
                    if (test) {
                        s += termStats (courseNo);
                        break;
                    } else {
                        string temp = termStats(courseNo, termID);
                        printf ("%s", temp.c_str());
                        break;
                    }
                } else {
                    if (test) {
                        s += "Invalid response\n";
                        break;
                    } else {
                        printf ("Invalid response\n");
                        break;
                    }
                }
            case 's':
                printf("Search for specific section?\n");
                printf("Y / N\n");
                test ? getline(testInputs, answerString) : cin >> answerString;
                search = answerString[0];
                if (tolower(search) == 'y') {
                    printf ("Type in section ID\n");
                    test ? getline(testInputs, answerString) : cin >> answerString;
                    answerString.erase(answerString.size() - 1);
                    sectionID = answerString;
                    if (validate_sectionID(sectionID)) {

                        if (test) {
                            s +=sectionStats(courseNo, sectionID);
                            break;
                        } else {
                            string temp = sectionStats(courseNo, sectionID);
                            printf ("%s", temp.c_str());
                            break;
                        }
                    } else {
                        s+="Section ID is invalid\n";
                    }
                } else if (tolower(search) == 'n') {
                    if (test) {
                        s += sectionStats (courseNo);
                        break;
                    } else {
                        string temp = sectionStats(courseNo, termID);
                        printf ("%s", temp.c_str());
                        break;
                    }
                } else {
                    if (test) {
                        s += "Invalid response\n";
                        break;
                    } else {
                        printf ("Invalid response\n");
                        break;
                    }
                }
                break;
            case 'n':
                cin.clear();
                break;
            default:
                printf("Not a valid key\n");
                break;
            }
            break;
        case 2:
            printf("Enter student info with commas between each field\n");
            printf("EMPLID\t COURSE NUMBER\t INSTRUCTOR ID\t TERM ID \t SECTION ID\t GRADE\n ");
            test ? getline(testInputs, answerString) : cin >> answerString;
            if (test) {
                answerString.erase(answerString.size() - 1);
            }
            studentString = answerString;
            if (add_enrollment_record(studentString) == 0)
            {
                if (test) {
                    s += "The information is invalid\n";
                    break;
                } else {
                    printf ("The information is invalid\n");
                    break;
                }
            }

            if (test) {
                s+= "Student entry successful\n";
                break;
            } else {
                printf ("Student entry successful\n");
                break;
            }
        case 3:
            printf("Enter in a grade\n");
            test ? getline(testInputs, answerString) : cin >> answerString;
            gradeString = answerString;

            int grade;
            for (char digit : gradeString)
            {
                if (!isdigit(digit))
                {
                    if (test) {
                        s += "The grade isn't a number\n";
                        break;
                    } else {
                        printf ("The grade isn't a number\n");
                        break;
                    }
                }
            }

            grade = stoi (gradeString);
            if (grade > 100 || grade < 1)
            {
                if (test) {
                    s+= "Grade " + std::to_string(grade) + " isn't a valid number\n";
                    break;
                } else {
                   printf("Grade %d isn't a valid grade\n", grade);
                   break; 
                }
            }

            printf("Enter in course number\n");
            test ? getline (testInputs, answerString) : cin >> answerString;
            courseNo = stoi (answerString);
            if (courseNo != 1115 && courseNo != 3130 && courseNo != 3115)
            {
                if (test) {
                    s+= "Invalid course number " + std::to_string (courseNo) + "\n";
                    break;
                } else {
                    printf("Invalid course number %d", courseNo);
                    break;
                }
            }

            printf ("Enter in EMPLID #\n");
            test ? getline (testInputs, answerString) : cin >> answerString;
            emplid = answerString;
            if (!validate_string(emplid)) {
                if (test) {
                    s+= "Invalid emplid\n";
                    break;
                } else {
                    printf ("Invalid emplid\n");
                    break;
                }
            }
            if (test) {
                update_grade (emplid, courseNo, grade);
                s+= "Grade updated successful";
                break;
            } else {
                update_grade (emplid, courseNo, grade);
                printf ("Grade update succsefully");
                break;
            }
        case 4:
            printf ("Enter in valid EMPLID\n");
            test ? getline (testInputs, answerString) : cin >> emplid;

            if (test) {
                answerString.erase(answerString.size() - 1);
            }
            emplid = answerString;

            if (!validate_string(emplid)) {
                if (test) {
                    s+="Invalid emplid\n";
                    break;
                } else {
                    printf ("Invalid emplid\n");
                    break;
                }
            }

            if (test) {
                s += find_student(emplid);
                cin.clear();
                break;
            } else {
                string temp = find_student(emplid);
                printf ("%s", temp.c_str());
                cin.clear();
                break;
            }

        default:
            printf("Not a valid menu option\n");
            break;
        }

        if (answer == 0)
        {
            flag = false;
        }

    } while (flag);

    return 0;
}