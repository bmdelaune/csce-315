/******************************************************************************
Bradley Delaune
CSCE 315-501
Spring 2012
Dr. Keyser

Individual Assignment 1
Due: January 30, 2012 9:10am

Student.h

Student Class for holding student and enrollment information.
*******************************************************************************/
#ifndef _STUDENT_H 
#define _STUDENT_H 

/***********************************
INCLUDES
***********************************/
#include "Course.h"
#include <list>
#include <string>

using namespace std;

/***********************************
DECLARATIONS
***********************************/
class Course;

/***********************************
STUDENT CLASS
Easiest way to store student information all together.
Uses variables for basic information and has two lists to keep track of
courses in which the student is enrolled and those which he is waitlisted for.
***********************************/
class Student {
	int student_id;
	string student_name;
	string student_major;
public:
	list<Course*> courses_enrolled;
	list<Course*> courses_waitlisted;

	Student(int id,string name, string maj){
		student_id = id;
		student_name = name;
		student_major = maj;
	}
	~Student(){
		
	}
	int returnStudentID();
	string returnStudentName();
	string returnStudentMajor();
	friend ostream& operator<<(ostream& stream,Student output);
};

#endif
