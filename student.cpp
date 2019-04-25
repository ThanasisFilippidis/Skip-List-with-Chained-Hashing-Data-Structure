#include "student.hpp"

using namespace std;

student::student(int st, char *ln, char *fn, float gp, int nu, char *de, int po):studid(st),gpa(gp),numofcourses(nu),postcode(po){
			strcpy(lname,ln);
			strcpy(fname,fn);
			strcpy(deprt,de);
		}

	student::~student(){
	}

	void student::printall(){
		cout<<studid<<" "<<lname<<" "<<fname<<" "<<gpa<<" "<<numofcourses<<" "<<deprt<<" "<<postcode<<endl;
	}

	void student::gpamod(float newgpa, int newnumofcourses){
		gpa=newgpa;
		numofcourses=newnumofcourses;
		printall();
	}