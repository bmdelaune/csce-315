/******************************************************************************
Bradley Delaune
CSCE 315-501
Spring 2012
Dr. Keyser

Individual Assignment 1
Due: January 30, 2012 9:10am

Course.h

Course class used to define courses and hold their enrollment information
*******************************************************************************/
#ifndef _COURSE_H
#define _COURSE_H

#include "Student.h"
#include <list>
#include <string>

using namespace std;

class Student;

class Course {
	int course_id;
	int max_enrollment;
	string course_name;
public:
	list<Student*> students_enrolled;
	list<Student*> students_on_waitlist;

	Course(int id, int max, string name){
		course_id = id;
		course_name = name;
		max_enrollment = max;
	}
	~Course(){
		
	}
	void newMaxEnrollment(int new_enrollment);
	int returnCourseID();
	string returnCourseName();
	int returnMaxEnrollment();
	friend ostream& operator<<(ostream& stream,Course output);
};

#endif
