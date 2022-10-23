//============================================================================
// Name        : Project3ABCU.cpp
// Author      : Chris Cole
// Date        : October 2022
// Version     : 1.0
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

// Define structure course
struct Course {
    //declare variables
    string courseNumber;
    string name;
    vector<string> prerequisites;
};

//Function to split string based on splits
vector<string> tokenize(string s, string split = ",") {

    vector<string> stringArray;
    int begin = 0;
    int end = s.find(split);

    while (end != -1) {
        stringArray.push_back(s.substr(begin, end - begin));
        begin = end + split.size();
        end = s.find(split, begin);
    }

    stringArray.push_back(s.substr(begin, end - begin));

    return stringArray;
}

// Function to load file and store the details into list of courses
vector<Course> InputData() {
    // use fstream to open .txt file
    fstream inputFile("abcu.txt");
    vector<Course> courses;
    string line;

    //while loop to iterate through data
    while (getline(inputFile, line)) {
        // course object to store course data
        Course course;
        // tokenize information to separate with commas
        vector<string> info = tokenize(line, ",");

        if (info.size() > 1) {
            // importing info to course struct
            course.courseNumber = info[0];
            course.name = info[1];

            // import prerequisites to course struct
            for (int i = 2; i < info.size(); i++) {
                course.prerequisites.push_back(info[i]);
            }

            // add course to list of courses
            courses.push_back(course);
        }
    }
    //close ifstream to save memory
    inputFile.close();

    cout << "Courses Loaded" << endl;
    

    //return course list
    return courses;
}

// function to print a course
void printCourse(Course course) {
    //declare and initialize variables
    string courseNumber = course.courseNumber;
    string name = course.name;
    vector<string> prerequisites = course.prerequisites;
    //print course details
    cout << endl;
    cout << "Course Number: " << courseNumber << endl;
    cout << "Course Name: " << name << endl;
    cout << "Prerequisites: ";
    cout << endl;
    //check for prerequisites
    for (int i = 0; i < prerequisites.size(); i++) {
        cout << prerequisites[i] << " ";
    }
    cout << endl;
}

// function to print the list of all courses
void PrintFullCourseList(vector<Course> courses)
{
    int tempSize = courses.size();

    // sorting the courses according the course number
    for (int i = 0; i < tempSize - 1; i++){
        for (int j = 0; j < tempSize - i - 1; j++){
            if (courses[j].courseNumber > courses[j + 1].courseNumber){
                swap(courses[j + 1], courses[j]);
            }
        }
    }

    // printing the list of all courses
    cout << "Course List: " << endl;
    for (int i = 0; i < tempSize; i++){
       cout << courses[i].courseNumber << ", " << courses[i].name << endl;
    }
}

// function to find a course with a course number
void searchCourse(vector<Course> courses){
    int tempSize = courses.size();
    string courseNumber;
    int temp = 0;

    cout << "What course do you want to know about?";
    cin >> courseNumber;
	
    std::transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);
	
    //show course details if available
    cout << "Course Details: " << endl;
    for (int i = 0; i < tempSize; i++) {
        //fixme find solution for strcmp for case
        if (strcmp(courses[i].courseNumber.c_str(), courseNumber.c_str()) == 0) {
            temp = 1;
            printCourse(courses[i]);
            break;
        }
    }
    //course not found
    if (temp == 0) {
        cout << "Course not found" << endl;
    }
}


int main(int argc, char** argv) {
    //vector
    vector<Course> courses;

    //display menu
    cout << "Welcome to the course planner." << endl;
    cout << endl;
   

    //store menu input
    int userInput;

    do {
        cout << endl;
        cout << "-----------------------" << endl;
        cout << "-----------------------" << endl;
        cout << "1. Load Data Structure" << endl;
        cout << "2. Print Course List" << endl;
        cout << "3. Print Course" << endl;
        cout << "9. Exit" << endl;
        cout << "-----------------------" << endl;
        cout << "-----------------------" << endl;
        cout << endl;
        cout << "What would you like to do?" << endl;
        cin >> userInput;

        //call function based on input
        switch (userInput) {
        case 1:
            courses = InputData();
            break;
        case 2:
            PrintFullCourseList(courses);
            break;
        case 3:
            searchCourse(courses);
            break;
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;
        default:
            cout << "********************" << endl;
            cout << userInput << " is not a valid option!" << endl;
            cout << "********************" << endl;
        }
    } 
    while (userInput != 9);

    return 0;
}