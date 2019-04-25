#ifndef __STUDENT__
#define __STUDENT__

#include <iostream>
#include <cstring>

class student
	{
	private:
		int studid;
		char lname[30];
		char fname[30];
		float gpa;
		int numofcourses;
		char deprt[10];
		int postcode;
	public:
		student(int st, char ln[30], char fn[30], float gp, int nu, char de[10], int po);
		~student();
		inline int getstudid();
		void printall();
		void gpamod(float newgpa, int newnumofcourses);
		inline float getgpa();
		inline char *getdeprt();
		inline int getnumofcourses();
		inline int getpostcode();
	};

	inline int student::getstudid(){
		return studid;
	}

	inline float student::getgpa(){
		return gpa;
	}

	inline char *student::getdeprt(){
		return deprt;
	}

	inline int student::getnumofcourses(){
		return numofcourses;
	}

	inline int student::getpostcode(){
		return postcode;
	}

#endif