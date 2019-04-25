#ifndef __SKIPLIST__
#define __SKIPLIST__

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "student.hpp"

#ifndef MaxLevel
#define MaxLevel 16
#endif

#ifndef MaxValue
#define MaxValue 100000000
#endif

class snode
{
private:
	int key;		/*the student id of each node*/
	student *ptr;		/*a pointer to the student record of each node*/
	snode **next;		/*an array of pointers to the next nodes according to the skiplist implementation*/
public:
	snode(int st);
	~snode();
	inline void printall();
	inline int getkey();
	inline student* getstudent();
	inline void setstudent(student *st);
	inline snode *getnext(int i);
	inline void setnext(int i, snode *s);
};

inline void snode::printall(){
		ptr->printall();
}

inline int snode::getkey(){
	return key;
}

inline student* snode::getstudent(){
	return ptr;
}

inline void snode::setstudent(student *st){
	ptr=st;
}

inline snode *snode::getnext(int i){
	return next[i];
}

inline void snode::setnext(int i, snode *s){
	next[i]=s;
}



class slist
{
private:
	snode* header;		/*pointer to the first node of the list(doesn't include record, implementation functions use)*/
	snode* termnode;		/*pointer to the last node of the list(doesn't include record, implementation functions use)*/
	int curlvl;		/*current level of the "highest" list node*/
	int size;		/*current amount of nodes in the list WITHOUT THE HEADER AND TERMNODE*/
public:
	slist();
	~slist();
	int randomlvl();
	student* search(int searchKey);
	void insert(int searchKey,student *newValue);
	int deletestud(int searchKey);
	void printlist();
	inline float getsize();
	float raverege(int from, int to);
	void bottom(int k);
	void f(float gp);
};

inline float slist::getsize(){
	return size;
}

#endif