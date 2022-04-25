Data summarization for CISC courses [1115] [3115] [3130]

The data most focused was withdrawal rate, pass rate, and average grades for each course, section, term, and instructor

There is also update methods for correct emplids and addition methods for adding to a roster

## Design

The entirity of each record in the CSV files are kept into a singular immutable struct and key extraction is done for the IDs (term id, section id, instructor id) seperately in a class

Everything else is sorted with methods that parse through the entirity of dictionary tables to make adding grades to each instructor easier.

The class [KeyStorage] is the container for all dictionary tables for readability. This was done because there was no way to get all instructor IDs to find crucial grade information and sort them properly without returning a cubersome multi-map.

The choice for a singular struct to keep all the records was also for ease of access and aggregation. Each students can be looked up and their grades and course information viewed

Data formatting, I/O, and data statistics are all handled seperately in different files. Data formatting is used to correctly parse data, validate strings, and build the struct and KeyStorage class. Data staticstics are for pass rate, withdrawal rate and course average methods.

**Why use multiple maps instead of vectors?**

The usage of maps to create dictionary tables were needed because there were 2 key components used for data summarization: The grades for each category and their frequency.

Using maps allows for the appending and manipulation of key-value pairs for each item. The program can easily find a specific instructor ID, grab the grades, aggregate it and divide by the frequency all using simple methods inside of the map data structure.

## A report is manually generated on make lab3 with test inputs. The test boolean must be switch manually inside the program for user input

### Usage

Clone down the repository

Cd into the local folder the repository is in

Run *make lab3* in the command line

There will be a command line menu prompt to fecth data and update information.

There is a *testinput.txt.* file to generate the report and an *coursedata.txt* file after the program is executed.


