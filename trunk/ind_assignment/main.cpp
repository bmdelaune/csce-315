/******************************************************************************
Bradley Delaune
CSCE 315-501
Spring 2012
Dr. Keyser

Individual Assignment 1
Due: January 30, 2012 9:10am

main.cpp

Contains the main() as well as well as global definitions.
*******************************************************************************/
/***********************************
INCLUDES
***********************************/
#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include "Student.h"
#include "Course.h"

using namespace std;

/***********************************
DECLARATIONS
***********************************/
extern list<Student*> list_of_students;
extern list<Course*> list_of_courses;

void addStudent(string);
void addCourse(string);
void changeCourseMax(string);
void placeStudentInCourse(string);
void dropStudentFromCourse(string);
void printStudentCourses(string);
void printCourseEnrollment(string);

/***********************************
MAIN
-easiest way to pull in commands was getline()
-"else if" worked better than "switch case"
-each action has a function to perform that action
***********************************/
int main(){
	string command_letter;
	string line;
	while(cin>>command_letter){
		getline(cin, line);
		line = line.substr(1);
		if(command_letter=="S"){
			addStudent(line);
		} else if (command_letter=="C"){
			addCourse(line);
		} else if (command_letter=="L"){
			changeCourseMax(line);
		} else if (command_letter=="A"){
			placeStudentInCourse(line);
		} else if (command_letter=="D"){
			dropStudentFromCourse(line);
		} else if (command_letter=="PS"){
			printStudentCourses(line);
		} else if (command_letter=="PC"){
			printCourseEnrollment(line);
		} else {
			return 1;
		}
	}
}
