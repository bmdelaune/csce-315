/******************************************************************************
Bradley Delaune
CSCE 315-501
Spring 2012
Dr. Keyser

Individual Assignment 1
Due: January 30, 2012 9:10am

user_control.cpp

All functions used in the main() that control user input data manipulation
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

/***********************************
DECLARATIONS
***********************************/
list<Student*> list_of_students;
list<Course*> list_of_courses;

/***********************************
OPERATING FUNCTIONS
***********************************/
/*
straightforward input of a new student by adding to the list.
*/
void addStudent(string rest_of_line){
	istringstream iss(rest_of_line,istringstream::out);
	int student_id;
	string first_name, last_name, major;
	iss>>student_id>>first_name>>last_name>>major;
	
	list_of_students.push_back(new Student(student_id, first_name+" "+last_name, major));
}

/*
Because the course name extended to the end of the line, a special process 
was necessary to parse the line until the end.  Each line of this function is
necessary to get the correct input.  DO NOT DELETE OR CHANGE.
*/
void addCourse(string rest_of_line){
	istringstream iss(rest_of_line,istringstream::out);
	iss.seekg(0,ios_base::end);
	int line_length = iss.tellg();
	iss.seekg(0,ios_base::beg);
	int course_id, max_enrollment;
	iss>>course_id>>max_enrollment;
	
	int line_current_position = iss.tellg();
	//finds length of course name
	int course_name_length = line_length-line_current_position;
	char temp_name[course_name_length];
	iss.seekg(1,ios_base::cur);
	iss.getline(temp_name,course_name_length);
	string course_name(temp_name);
	
	list_of_courses.push_back(new Course(course_id, max_enrollment, course_name));
}

/*
Easiest way to update the Max Enrollment and change both student/course data.
*/
void changeCourseMax(string rest_of_line){
	istringstream iss(rest_of_line,istringstream::out);
	int temp_course_id, temp_new_enrollment;
	iss>>temp_course_id>>temp_new_enrollment;
	
	for(list<Course*>::iterator it = list_of_courses.begin(); it != list_of_courses.end(); it++){
		if(temp_course_id == (*it)->returnCourseID()) {
			(*it)->newMaxEnrollment(temp_new_enrollment);
			//checks if students need to be moved from the waitlist to the enrolled list
			while(!(*it)->students_on_waitlist.empty()
					&& ((*it)->returnMaxEnrollment() > (*it)->students_enrolled.size())) {
				Student * temp_student_ptr = (*it)->students_on_waitlist.front();
				(*it)->students_enrolled.push_back(temp_student_ptr);
				(*it)->students_on_waitlist.pop_front();
				for(list<Course*>::iterator cit = temp_student_ptr->courses_waitlisted.begin();
						cit!=temp_student_ptr->courses_waitlisted.end();
						cit++) {
					if(temp_course_id == (*cit)->returnCourseID()){
						temp_student_ptr->courses_enrolled.push_back(*cit);
						cit = temp_student_ptr->courses_waitlisted.erase(cit);
					}
				}
			}
		}
	}
}

/*
Adds student and Course information.
*/
void placeStudentInCourse(string rest_of_line){
	istringstream iss(rest_of_line,istringstream::out);
	int temp_course_id, temp_student_id;
	iss>>temp_course_id>>temp_student_id;
	
	Course * temp_course_ptr;
	Student * temp_student_ptr;
	
	for(list<Course*>::iterator it = list_of_courses.begin(); it != list_of_courses.end(); it++){
		if(temp_course_id == (*it)->returnCourseID()) {
			temp_course_ptr = (*it);
		}
	}
	for(list<Student*>::iterator it = list_of_students.begin(); it != list_of_students.end(); it++){
		if(temp_student_id == (*it)->returnStudentID()) {
			temp_student_ptr = (*it);
		}
	}
	//checks if the student should be enrolled or waitlisted
	if(temp_course_ptr->returnMaxEnrollment() > temp_course_ptr->students_enrolled.size()){
		temp_course_ptr->students_enrolled.push_back(temp_student_ptr);
		temp_student_ptr->courses_enrolled.push_back(temp_course_ptr);
	} else {
		temp_course_ptr->students_on_waitlist.push_back(temp_student_ptr);
		temp_student_ptr->courses_waitlisted.push_back(temp_course_ptr);
	}
}

/*
Must check all possible places the student's information is and remove from
all lists.
*/
void dropStudentFromCourse(string rest_of_line){
	istringstream iss(rest_of_line,istringstream::out);
	int temp_course_id, temp_student_id;
	iss>>temp_course_id>>temp_student_id;
	Course * temp_course_ptr;
	Student * temp_student_ptr;
	for(list<Course*>::iterator it = list_of_courses.begin();
			it != list_of_courses.end(); it++){
		if(temp_course_id == (*it)->returnCourseID()) {
			temp_course_ptr = (*it);
		}
	}
	for(list<Student*>::iterator it = list_of_students.begin();
			it != list_of_students.end(); it++){
		if(temp_student_id == (*it)->returnStudentID()) {
			temp_student_ptr = (*it);
		}
	}
	for(list<Student*>::iterator it = temp_course_ptr->students_enrolled.begin();
			it != temp_course_ptr->students_enrolled.end(); it++) {
		if((*it)->returnStudentID() == temp_student_id){
			temp_course_ptr->students_enrolled.erase(it);
		}
	}
	for(list<Student*>::iterator it = temp_course_ptr->students_on_waitlist.begin();
			it != temp_course_ptr->students_on_waitlist.end(); it++) {
		if((*it)->returnStudentID() == temp_student_id){
			temp_course_ptr->students_on_waitlist.erase(it);
		}
	}
	for(list<Course*>::iterator it = temp_student_ptr->courses_enrolled.begin();
			it != temp_student_ptr->courses_enrolled.end(); it++) {
		if((*it)->returnCourseID() == temp_course_id){
			temp_student_ptr->courses_enrolled.erase(it);
		}
	}
	for(list<Course*>::iterator it = temp_student_ptr->courses_waitlisted.begin();
			it != temp_student_ptr->courses_waitlisted.end(); it++) {
		if((*it)->returnCourseID() == temp_course_id){
			temp_student_ptr->courses_waitlisted.erase(it);
		}
	}
}

/*
finds the student and uses the ostream to output information
*/
void printStudentCourses(string rest_of_line){
	istringstream iss(rest_of_line,istringstream::out);
	int temp_student_id;
	iss>>temp_student_id;
	
	Student * temp_student_ptr;
	for(list<Student*>::iterator it = list_of_students.begin(); it != list_of_students.end(); it++){
		if(temp_student_id == (*it)->returnStudentID()) {
			temp_student_ptr = (*it);
		}
	}
	
	cout<<(*temp_student_ptr)<<endl;
}

/*
finds the course and uses the ostream to output information
*/
void printCourseEnrollment(string rest_of_line){
	istringstream iss(rest_of_line,istringstream::out);
	int temp_course_id;
	iss>>temp_course_id;
	
	Course * temp_course_ptr;
	for(list<Course*>::iterator it = list_of_courses.begin(); it != list_of_courses.end(); it++){
		if(temp_course_id == (*it)->returnCourseID()) {
			temp_course_ptr = (*it);
		}
	}
	
	cout<<(*temp_course_ptr)<<endl;
}