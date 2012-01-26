/******************************************************************************
Bradley Delaune
CSCE 315-501
Spring 2012
Dr. Keyser

Individual Assignment 1
Due: January 30, 2012 9:10am

Create a program that can be used for keeping track of course registrations.
You want to keep track of courses, enrollment lists in those courses, and
waitlists for the courses.
*******************************************************************************/
#include <iostream>
#include <sstream>
#include <string>
#include <list>
/*
S <Student Number> <Student Name> <Major>
-          Define a student.  <Student Number> will be a 9 digit ID number.  <Student Name> will consist of a First name, followed by a space, followed by a Last Name.  <Major> will be a set of 4 characters identifying the major. 
C <Course Number> <Maximum Enrollment> <Course Title>
-          Define a course.  <Course Number> will be a 5 digit ID number.  <Maximum Enrollment> will be an initial maximum enrollment for the course.  <Course Title> will be a string that extends to the end o f the line
L <Course Number> <New Maximum Enrollment>
-          Change the enrollment maximum for the course. 
A <Course Number> <Student Number>
-          Add a student to a course.
D <Course Number> <Student Number>
-          Drop a student from a course.
PS <Student Number>
-          Print a report showing the classes a student is signed up for.
PC <Course Number>
-          Print a report for the course, giving the students/majors in the course, as well as students on the waiting list.
*/
using namespace std;

class Student;
class Course;

list<Student*> list_of_students;
list<Course*> list_of_courses;

class Student {
	int student_id;
	string student_name;
	string major;
public:
	list<Course*> courses_enrolled;
	list<Course*> courses_waitlisted;

	Student(int id,string name, string maj){
		student_id = id;
		student_name = name;
		major = maj;
	}
	~Student(){
		
	}
	int returnStudentID(){
		return student_id;
	}
};

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
	void newMaxEnrollment(int new_enrollment){
		max_enrollment = new_enrollment;
	}
	int returnCourseID() {
		return course_id;
	}
	int returnMaxEnrollment() {
		return max_enrollment;
	}
};

void addStudent(string rest_of_line){
	istringstream iss(rest_of_line,istringstream::out);
	int student_id;
	string first_name, last_name, major;
	iss>>student_id>>first_name>>last_name>>major;
	list_of_students.push_back(new Student(student_id, first_name+" "+last_name, major));
	cout<<"========Student Created========"<<endl
		<<"= Student ID: "<<student_id<<endl
		<<"= Name: "<<last_name<<", "<<first_name<<endl
		<<"= Major: "<<major<<endl
		<<"==============================="<<endl;
}

void addCourse(string rest_of_line){
	istringstream iss(rest_of_line,istringstream::out);
	iss.seekg(0,ios_base::end);
	int line_length = iss.tellg();
	iss.seekg(0,ios_base::beg);
	int course_id, max_enrollment;
	iss>>course_id>>max_enrollment;
	int line_current_position = iss.tellg();
	int course_name_length = line_length-line_current_position;
	char temp_name[course_name_length];
	iss.seekg(1,ios_base::cur);
	iss.getline(temp_name,course_name_length);
	string course_name(temp_name);
	list_of_courses.push_back(new Course(course_id, max_enrollment, course_name));
	cout<<"=========Course Created========"<<endl
		<<"= Course ID: "<<course_id<<endl
		<<"= Max Enrollment: "<<max_enrollment<<endl
		<<"= Course Name: "<<course_name<<endl
		<<"==============================="<<endl;
}

void changeCourseMax(string rest_of_line){
	istringstream iss(rest_of_line,istringstream::out);
	int temp_course_id, temp_new_enrollment;
	iss>>temp_course_id>>temp_new_enrollment;
	for(list<Course*>::iterator it = list_of_courses.begin(); it != list_of_courses.end(); it++){
		if(temp_course_id == (*it)->returnCourseID()) {
			(*it)->newMaxEnrollment(temp_new_enrollment);
		}
	}
}

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
	if(temp_course_ptr->returnMaxEnrollment() > temp_course_ptr->students_enrolled.size()){
		temp_course_ptr->students_enrolled.push_back(temp_student_ptr);
		temp_student_ptr->courses_enrolled.push_back(temp_course_ptr);
	} else {
		temp_course_ptr->students_on_waitlist.push_back(temp_student_ptr);
		temp_student_ptr->courses_waitlisted.push_back(temp_course_ptr);
	}
}

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
			//dropStudentFromCourse(line);
		} else if (command_letter=="PS"){
			//printStudentCourses(line);
		} else if (command_letter=="PC"){
			//printCourseEnrollment(line);
		} else {
			return 1;
		}
	}
}
