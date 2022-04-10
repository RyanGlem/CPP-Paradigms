#include <iostream>
#include "data_stats.h"

using std::cout; 
using std::endl;

int main () {

    //Chooses which data to load
    printf ("Entry Main \n");

    printf ("Instructor Statistics\n");
    instructorStats();
    printf("\n");

    printf ("Term Statistics \n");
    termStats();
    printf("\n");

    printf ("Section Statistics\n");
    sectionStats();
}