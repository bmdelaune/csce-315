/******************************************************************************
Bradley Delaune
CSCE 315-501
Spring 2012
Dr. Keyser

Individual Assignment 1
Due: January 30, 2012 9:10am

Student.cpp

Member functions of the Student Class
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
MEMBER FUNCTIONS
***********************************/
/*
return information for public use
*/
int Student::returnStudentID(){
	return student_id;
}
string Student::returnStudentName(){
	return student_name;
}
string Student::returnStudentMajor(){
	return student_major;
}

/*
makes student information output uniform
*/
ostream &operator<<(ostream &stream, Student output) {
	stream<<"========Student Information========"<<endl
		<<"= Student ID: "<<output.student_id<<endl
		<<"= Name: "<<output.student_name<<endl
		<<"= Major: "<<output.student_major<<endl
		<<"------------------------------"<<endl
		<<"Courses:"<<endl;
	for(list<Course*>::iterator it = output.courses_enrolled.begin(); it != output.courses_enrolled.end(); it++){
		stream<<(*it)->returnCourseID()<<": "<<(*it)->returnCourseName()<<endl;
	}
	stream<<"------------------------------"<<endl
		<<"Wait-listed for these:"<<endl;
	for(list<Course*>::iterator it = output.courses_waitlisted.begin(); it != output.courses_waitlisted.end(); it++){
		stream<<(*it)->returnCourseID()<<": "<<(*it)->returnCourseName()<<endl;
	}
	stream<<"==================================="<<endl;
	return stream; 
}

