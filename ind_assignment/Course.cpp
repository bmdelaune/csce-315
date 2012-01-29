/******************************************************************************
Bradley Delaune
CSCE 315-501
Spring 2012
Dr. Keyser

Individual Assignment 1
Due: January 30, 2012 9:10am

Course.cpp

All Course class member function definitions
*******************************************************************************/
#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include "Student.h"
#include "Course.h"

using namespace std;

void Course::newMaxEnrollment(int new_enrollment){
	max_enrollment = new_enrollment;
}

int Course::returnCourseID() {
	return course_id;
}

string Course::returnCourseName() {
	return course_name;
}

int Course::returnMaxEnrollment() {
	return max_enrollment;
}

ostream &operator<<(ostream &stream, Course output) {
	stream<<"=========Courses Information========"<<endl
		<<"= Student ID: "<<output.course_id<<endl
		<<"= Name: "<<output.course_name<<endl
		<<"= Max Enrollment: "<<output.max_enrollment<<endl
		<<"------------------------------"<<endl
		<<"Students:"<<endl;
	for(list<Student*>::iterator it = output.students_enrolled.begin(); it != output.students_enrolled.end(); it++){
		stream<<(*it)->returnStudentID()<<": "<<(*it)->returnStudentMajor()<<" "<<(*it)->returnStudentName()<<endl;
	}
	stream<<"------------------------------"<<endl
		<<"Wait-list:"<<endl;
	for(list<Student*>::iterator it = output.students_on_waitlist.begin(); it != output.students_on_waitlist.end(); it++){
		stream<<(*it)->returnStudentID()<<": "<<(*it)->returnStudentName()<<endl;
	}
	stream<<"==================================="<<endl;
	return stream; 
}

