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

#include "Course.h"
#include <list>
#include <string>

using namespace std;

class Course;

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
