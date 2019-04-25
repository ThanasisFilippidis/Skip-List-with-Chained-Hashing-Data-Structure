#include "hashtable.hpp"

using namespace std;


hnode::hnode(){
	ptr=NULL;
	next=NULL;
}

hnode::~hnode(){
	delete ptr;
}



hplist::hplist(int pc):postcode(pc){
	header=NULL;
	next=NULL;
	size=0;
}

hplist::~hplist(){
	hnode *tmp;
	hnode *tmp2;
	if (header!=NULL)
	{
		tmp=header;
		while((tmp->getnext())!=NULL){
			tmp2=tmp->getnext();
			delete tmp;
			tmp=tmp2;
		}
		delete tmp;
	}
}

void hplist::insert(student *st){
	hnode *newNode;
	hnode *tmp;

	newNode=new hnode();
	newNode->setstudent(st);

	if (header==NULL)		/*if its the first student to this post code set the header to point at him*/
	{
		header=newNode;
	}else{
		tmp=header;
		while((tmp->getnext())!=NULL){	/*traverse the list until you reach the end of it*/
			tmp=tmp->getnext();
		}
		tmp->setnext(newNode);		/*then add him*/
	}
	size++;
}

bool hplist::deletestud(int id, int pcode){
	hnode *tmp;
	hnode *tmp2;
	if (pcode == postcode)
	{
		if(header!=NULL){		/*if there are students in this postcode*/
			tmp=header;
			if (((tmp->getstudent())->getstudid()) == id) /*if the desired student is the first one the list*/
			{
				if((tmp->getnext()) == NULL){	/*if he is the only one too*/
					size--;
					delete tmp;
					header=NULL;
					return true;
				}else{
					header=header->getnext();
					delete tmp;
					size--;
					return true;
				}
			}
			
			tmp2=header;
			tmp=tmp->getnext();
			while(tmp!=NULL){		/*traverse until you find the desired student*/
				if (((tmp->getstudent())->getstudid()) == id) {
					tmp2->setnext(tmp->getnext());
					size--;
					delete tmp;
					return true;
				}
				tmp2=tmp;
				tmp=tmp->getnext();
			}
		}
		
	}
		return false;
}

void hplist::printlist(){
	hnode *tmp;
	tmp=header;
	while(tmp != NULL){
		(tmp->getstudent())->printall();
		tmp=tmp->getnext();
	}
}

float hplist::getavgpa(){
	hnode *tmp;
	float allgpa=0;
	tmp=header;
	while(tmp != NULL){
		allgpa=allgpa + (tmp->getstudent())->getgpa();
		tmp=tmp->getnext();
	}
	return (allgpa/size);
}


hlist::hlist(){
	header=NULL;
	size=0;
}

hlist::~hlist(){
	hplist *tmp;
	hplist *tmp2;
	if (header!=NULL)
	{
		tmp=header;
		while((tmp->getnext())!=NULL){
			tmp2=tmp->getnext();
			delete tmp;
			tmp=tmp2;
		}
		delete tmp;
	}
}

void hlist::insert(student *st){
	hplist *tmp;
	hplist *prevnode;
	tmp=header;
	if (tmp == NULL)		/*if there are no hplists on this hash table cell*/
	{
		header=new hplist(st->getpostcode());
		header->insert(st);
		size++;
	}else{
		while(tmp != NULL){		/*traverse list*/
			prevnode=tmp;
			if (tmp->getpostcode() == st->getpostcode())	/*to find an hplist with the students st postcode*/
			{
				tmp->insert(st);
				size++;
				break;
			}
			tmp=tmp->getnext();
		}
		if (tmp == NULL)		/*if didn't found the proper hplists create a new one*/
		{
			tmp=new hplist(st->getpostcode());
			tmp->insert(st);
			size++;
			prevnode->setnext(tmp);
		}
	}
}

void hlist::printlist(){
	hplist *tmp;
	tmp=header;
	while(tmp != NULL){
		tmp->printlist();
		tmp=tmp->getnext();
	}
}

bool hlist::deletestud(int id, int postcode){
	hplist *tmp;
	hplist *tmp2;
	hnode *tmp3;
	bool flag=false;
	
	if(header!=NULL){		/*if the list is not empty*/
		tmp2=header;
		tmp=header->getnext();		/*keep to the variable tmp the address of the second hplist*/
		flag=header->deletestud(id,postcode);	/*try deleting him from the first hplist*/
		tmp3=header->getheader();		/*and keep to variable tmp3 the address of the maybe deleted hplists header*/
		if (flag)		/*if deleted him from the hlists header*/
		{
			if (tmp3 == NULL)		/*and it was the only student in this post code*/
			{
				delete header;		/*delete this hplist*/
				header=tmp;		/*and set hlist's header to the second hplists of the hlist*/
			}
			return true;
		}

		while(tmp != NULL && !flag){		/*else traverse*/
			flag=tmp->deletestud(id, postcode);	/*and try deleting him in each hplist*/
			if (flag)
			{
				tmp3=tmp->getheader();
				if (tmp3 == NULL)		/*if he was the only one in this postcode*/
				{
					tmp2->setnext(tmp->getnext());
					delete tmp;		/*delete the hplists of this post code*/
				}
				return true;
			}
			tmp2=tmp;
			tmp=tmp->getnext();
		}
	}
	return false;
}

float hlist::getavgpa(int pcode){
	hplist *tmp;
	float avgpa=-1;
	tmp=header;
	while(tmp != NULL){
		if (tmp->getpostcode() == pcode)
		{
			avgpa=tmp->getavgpa();
			break;
		}
		tmp=tmp->getnext();
	}
	return avgpa;
}

void hlist::bubsort(int k, hplist *tmp){		/*typical implementation of bubble sort function*/
	int n,s;
	student *swap;
	student **sorted;
	hnode *node;
	node=tmp->getheader();
	s=tmp->getsize();
	sorted=new student *[s];
	for (int i = 0; i < s; ++i)
	{
		sorted[i]=node->getstudent();		/*get to a table name sorted all the students of tmp's postcode*/
		node=node->getnext();
	}
	for (int i = 0; i < s -1; ++i)
	{
		for (int j = 0; j < s - i -1; ++j)
		{
			if (sorted[j]->getgpa() < sorted[j+1]->getgpa())	/*sort them*/
			{
				swap=sorted[j];
				sorted[j]=sorted[j+1];
				sorted[j+1]=swap;
			}
		}
	}
	if (k <= s)		/*if students asked less than the table's size*/
	{
		for (int i = 0; i < k; ++i)
		{
			sorted[i]->printall();		/*print the amoun of top students asked*/
		}
	}else{
		cerr<<"Asked for more students than the available. All available will be printed."<<endl;
		for (int i = 0; i < s; ++i) /*print all the available students if this post code*/
		{
			sorted[i]->printall();
		}
	}
	delete sorted;
}


void hlist::taverage(int k, int pcode){
	hplist *tmp;
	student **sorted;
	tmp=header;
	while(tmp != NULL){		/*traverse throught the hlist to find the desirable hplist*/
		if (tmp->getpostcode() == pcode)
		{
			bubsort(k,tmp);
			break;
		}
		tmp=tmp->getnext();
	}
	if (tmp == NULL)		/*if reached the end of the hlist without founding the postcode*/
	{
		cerr<<"No students found on this postcode/postcode not found."<<endl;
	}
}

void hlist::ct(int pcode,char *dpt){
	hplist *tmp;
	hnode *node;
	bool flag=false;
	tmp=header;
	while(tmp != NULL){		/*traverse through hlist*/
		if (tmp->getpostcode() == pcode)	/*if found the proper postcode*/
		{
			node=tmp->getheader();
			while(node != NULL){		/*traverse through hplists*/
				if (!strcmp((node->getstudent())->getdeprt(),dpt))	/*if a student belong to the desired department*/
				{
					(node->getstudent())->printall();	/*print him*/
					flag=true;
				}
				node=node->getnext();
			}
			break;
		}
		tmp=tmp->getnext();
	}
	if (tmp == NULL || !flag)	/*if reached the end of the hlist and not found the postcode or didn't found*/
								/*any students of this department in this postcode*/
	{
		cerr<<"No students found on this "<<endl;
		cerr<<"postcode/department with this postcode or postcode not found."<<endl;
	}
}

float hlist::pcodesize(int pcode){
	hplist *tmp;
	tmp=header;
	while(tmp != NULL){		/*traverse through hlist*/
		if (tmp->getpostcode() == pcode)
		{
			return (float)tmp->getsize();
		}
		tmp=tmp->getnext();
	}
	if (tmp == NULL)	/*if not fount this postcode*/
	{
		cerr<<"No students found on this postcode/postcode not found."<<endl;
	}
	return 0;
}

void hlist::pe(float allsize){
	hplist *tmp;
	tmp=header;
	while(tmp != NULL){
		printf("The postcode %d hosts the %2.2f %% of the students.\n",tmp->getpostcode(), (tmp->getsize()*100)/allsize);
		tmp=tmp->getnext();
	}
}



htable::htable(int entr):entries(entr){
	lists=new hlist *[entries];
	for (int i = 0; i < entries; ++i)
	{
		lists[i]=new hlist();
	}
}

htable::~htable(){
	for (int i = 0; i < entries; ++i)
	{
		delete lists[i];
	}
	cout<<"Goodbye."<<endl;
	delete [] lists;
}

int htable::hashfunc(int postcode){		/*function to hash the postcodes*/
	return (postcode % entries);
}

void htable::insert(student *st){
	int position;
	position=hashfunc(st->getpostcode());	/*decide with the help of hash func in which cell to insert*/
	lists[position]->insert(st);
	size++;
}

void htable::printall(){
	for (int i = 0; i < entries; ++i)
	{
		if (lists[i] != NULL)
		{
			lists[i]->printlist();
		}
	}
}

bool htable::deletestud(int id, int postcode){
	int position;
	bool flag;
	position=hashfunc(postcode);
	flag=lists[position]->deletestud(id, postcode);
	if (flag)		/*if deleted with success decrease the size*/
	{
		size--;
	}
}

float htable::average(int pcode){
	hlist *tmp;
	int position;
	position=hashfunc(pcode);
	tmp=lists[position];
	return tmp->getavgpa(pcode);
}

void htable::taverage(int k, int pcode){
	hlist *tmp;
	int position;
	position=hashfunc(pcode);
	tmp=lists[position];
	tmp->taverage(k,pcode);
}

void htable::ct(int pcode,char *dpt){
	hlist *tmp;
	int position;
	position=hashfunc(pcode);
	tmp=lists[position];
	tmp->ct(pcode,dpt);
}

void htable::p(int pcode, float allsize){
	if (allsize)		/*if the size is not zero*/
	{
		hlist *tmp;
		float pcodesize;
		int position;
		position=hashfunc(pcode);
		tmp=lists[position];
		pcodesize=tmp->pcodesize(pcode);
		pcodesize=pcodesize*100;
		pcodesize=pcodesize/allsize;
		printf("In this postcode lives the %2.2f %% of students.\n",pcodesize );
	}else{
		cerr<<"Cannot find statistics with zero inputs."<<endl;
	}
	
}

void htable::pe(float allsize){
	if (allsize)		/*if the size is not zero*/
	{
		hlist *tmp;
		for (int i = 0; i < entries; ++i)
		{
			tmp=lists[i];
			tmp->pe(allsize);
		}
	}else{
		cerr<<"Cannot find statistics with zero inputs."<<endl;
	}
}