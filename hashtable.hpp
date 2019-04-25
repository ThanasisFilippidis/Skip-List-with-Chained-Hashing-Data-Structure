#ifndef __HASHTABLE__
#define __HASHTABLE__

#include <iostream>
#include <cstring>
#include <cstdio>
#include "student.hpp"

class hnode		/*one hnode is one student*/
{
private:
	student *ptr;
	hnode *next;
public:
	hnode();
	~hnode();
	inline void setstudent(student *st);
	inline student *getstudent();
	inline void setnext(hnode *n);
	inline hnode *getnext();
};

inline void hnode::setstudent(student *st){
	ptr=st;
}

inline student *hnode::getstudent(){
	return ptr;
}

inline void hnode::setnext(hnode *n){
	next=n;
}

inline hnode *hnode::getnext(){
	return next;
}


class hplist		/*one hplist is a list containing many students of the same post code*/
{
private:
	hnode *header;
	hplist *next;
	int postcode;
	int size;
public:
	hplist(int pc);
	~hplist();
	void insert(student *st);
	bool deletestud(int id, int pcode);
	void printlist();
	inline hplist *getnext();
	inline int getpostcode();
	inline void setnext(hplist *l);
	inline hnode *getheader();
	float getavgpa();
	inline int getsize();
};

inline int hplist::getpostcode(){
		return postcode;
}

inline hplist *hplist::getnext(){
		return next;
}

inline void hplist::setnext(hplist *l){
		next=l;
}

inline hnode *hplist::getheader(){
		return header;
}

inline int hplist::getsize(){
		return size;
}



class hlist 		/*one hlist is a list of hplists that hash to the same hashtable cell*/
{
private:
	hplist *header;
	int size;
public:
	hlist();
	~hlist();
	void insert(student *st);
	void printlist();
	bool deletestud(int id, int postcode);
	float getavgpa(int pcode);
	void bubsort(int k, hplist *tmp);
	void taverage(int k, int pcode);
	void ct(int pcode,char *dpt);
	float pcodesize(int pcode);
	void pe(float allsize);
};


class htable
{
private:
	hlist **lists;
	int entries;
	int size;
public:
	htable(int entr);
	~htable();
	int hashfunc(int postcode);
	void insert(student *st);
	void printall();
	bool deletestud(int id, int postcode);
	float average(int pcode);
	void taverage(int k, int pcode);
	void ct(int pcode,char *dpt);
	void p(int pcode, float allsize);
	void pe(float allsize);
};
#endif