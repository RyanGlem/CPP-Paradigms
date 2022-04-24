#ifndef DATA_STATISTICS
#define DATA_STATISTICS

float course_pass_rate(int course);
float course_withdrawal_rate(int course);
float course_average (int course);

std::string instructorStats(int course);
std::string termStats(int course);
std::string sectionStats(int course);

std::string instructorStats(int course, std::string ID);
std::string termStats(int course, std::string ID);
std::string sectionStats(int course, std::string ID);

#endif