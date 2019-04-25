#include "skiplist.hpp"

using namespace std;

snode::snode(int st):key(st){
	ptr=NULL;		/*student record will be inserted by the insert function*/
	next=new snode *[MaxLevel];
	for (int i = 0; i < MaxLevel; ++i)
	{
		next[i]=NULL;		/*initialize the array of pointers to next nodes, value will be given by insert function*/
	}
}

snode::~snode(){
	delete next;
}




slist::slist(){
	termnode=new snode(MaxValue);		/*initialize the last node with the biggest available value*/
	header=new snode(-1);		/*initialize the first node with a non available value(not going to be used anyway)*/
	for (int i = 0; i < MaxLevel; ++i)
	{
		header->setnext(i,termnode);		/*set pointer of level i to point to the last node*/
	}
	curlvl=1;
	size=0;
}

slist::~slist(){
	snode *tmp;
	snode *tmp2;
	tmp=header->getnext(0);
	while(tmp!=NULL){		/*start deletin from the start of the list to the last node*/
		tmp2=tmp;
		tmp=tmp->getnext(0);
		delete tmp2;
	}
	delete header;
}

int slist::randomlvl(){		/*provides random level for a new node when constructed*/
	srand (time(NULL));
	int lvl=1;
	while(((rand()%100) < 25)&&(lvl < MaxLevel)){
		lvl++;
	}
	return lvl;
}

student* slist::search(int searchKey){
	snode *tmp;
	tmp=header;
	for (int i = MaxLevel - 1; i >= 0; --i)		/*traverse through the list until node before the searching node is found*/
	{	while ((tmp->getnext(i))->getkey() < searchKey){
			tmp=tmp->getnext(i);
		}
	}
	tmp=tmp->getnext(0);
	if (tmp->getkey() == searchKey){		/*if next node is the node we were searching for*/
		return tmp->getstudent();
	}else{
		cerr<<"Student not found."<<endl;
		return NULL;
	}
}

void slist::insert(int searchKey,student *newValue){
	snode **update;
	int newlvl;
	snode *tmp;
	tmp=header;
	update=new snode *[MaxLevel];
	for (int i = MaxLevel -1; i >=0 ; --i)		/*traverse through the list until node before the searching node is found*/
	{
		while ((tmp->getnext(i))->getkey() < searchKey){
			tmp=tmp->getnext(i);
		}
		update[i]=tmp;		/*and keep in an array the pointers that may need a change later*/
	}

	tmp=tmp->getnext(0);
	if(tmp->getkey() == searchKey){		/*if the student that we try to insert exists already*/
		cerr<<"This student id already exists."<<endl;
	}else{
		newlvl=randomlvl();
		if (newlvl > curlvl){
			curlvl=newlvl;
		}
		tmp=new snode(newValue->getstudid());		/*create a new skip list node*/
		tmp->setstudent(newValue);		/*and initialize it*/
		for (int i = 0; i <= newlvl; ++i)		/*then make the necessary changes to the pointers*/
		{
			tmp->setnext(i,update[i]->getnext(i));
			update[i]->setnext(i,tmp);
		}
		size++;
	}
	delete update;
}

int slist::deletestud(int searchKey){
	snode **update;
	snode *tmp;
	int pcode=-1;

	tmp=header;
	update=new snode *[MaxLevel];
	for (int i = MaxLevel -1; i >=0 ; --i)		/*traverse through the list until node before the searching node is found*/
	{
		while ((tmp->getnext(i))->getkey() < searchKey){
			tmp=tmp->getnext(i);
		}
		update[i]=tmp;		/*and keep in an array the pointers that may need a change later*/
	}

	tmp=tmp->getnext(0);
	if (tmp->getkey() == searchKey)		/*if searching node found*/
	{
		pcode=(tmp->getstudent())->getpostcode();		/*save its postcode for future use*/
		for (int i = 0; i < MaxLevel; ++i)		/*start fixing the node pointers from the bottom*/
		{
			if (update[i]->getnext(i) != tmp)		/*if the update[i] pointer doesn't point to deleted node we don't have*/
			{										/*anything else to fix, stop*/
				break;
			}
			update[i]->setnext(i,tmp->getnext(i));	/*set to the pointers poiting to the deleted node the new address to point*/
		}
		delete tmp;		/*delete the node*/
		size--;
	}
	return pcode;
}

void slist::printlist(){
	snode *tmp;
	tmp=header->getnext(0);
	if (tmp == termnode)
	{
		cerr<<"Skip List is empty."<<endl;
	}else{
		while(tmp!=termnode){
			tmp->printall();
			tmp=tmp->getnext(0);
		}
	}
}

float slist::raverege(int from, int to){
	snode *tmp;
	tmp=header;
	float allgpa=0;
	float counter=0;
	for (int i = MaxLevel -1; i >=0 ; --i)		/*traverse through the list until node before the node "from" is found*/
	{
		while ((tmp->getnext(i))->getkey() < from){
			tmp=tmp->getnext(i);
		}
	}
	tmp=tmp->getnext(0);
	while(tmp->getkey() <= to && tmp->getnext(0) != NULL){		/*while we havent reached the "to" nor the termnode*/
		allgpa=allgpa + (tmp->getstudent())->getgpa();		/*get all students gpa to a counter*/
		counter++;
		tmp=tmp->getnext(0);
	}
	if (counter)		/*if there is at least one*/
	{
		return (allgpa/counter);
	}else{
		cerr<<"No students in that range."<<endl;
		return 0;
	}
}

void slist::bottom(int k){
	student **stable;
	snode *tmp;
	int max=0;
	int position=0;

	tmp=header->getnext(0);
	if (k > size)
	{
		cerr<<"Asked for more students than the available. All available will be printed."<<endl;
		k=size;
	}
	stable=new student *[k];	/*stable is the table we will have by the end of the function with all the proper students inside*/
	for (int i = 0; i < k; ++i)			/*get the k first students found on the list*/
	{
		stable[i]=tmp->getstudent();
		if (stable[i]->getgpa() > max)
		{
			position=i;		/*and keep the position of the one with the bigger gpa*/
			max=stable[i]->getgpa();		/*and his gpa*/
		}
		tmp=tmp->getnext(0);
	}
	if (k <= size)		/*if there are more than k in the list*/
	{
		for (int i = k; i < size; ++i)		/*continue from where stopped inserting to the table*/
		{
			if ((tmp->getstudent())->getgpa() < max)	/*and if a smaller gpa found than the greatest existing in the table*/
			{
				stable[position]=tmp->getstudent();		/*exchange the smaller gpa studend with the table's max one*/
				max=0;
				for (int j = 0; j < k; ++j)		/*and traverse through the table to find the greatest and his position again*/
				{
					if (stable[j]->getgpa() > max)
					{
						max=stable[j]->getgpa();
						position=j;
					}
				}
			}
			tmp=tmp->getnext(0);
		}
	}
	for (int i = 0; i < k; ++i)
		{
			stable[i]->printall();
		}
	delete stable;
}

void slist::f(float gp){
	snode *tmp;
	int max=0;
	bool flag=false;
	tmp=header->getnext(0);
	while(tmp->getnext(0) != NULL){		/*traverse through the list to find the students with the greatest number of courses*/
		if ((tmp->getstudent())->getnumofcourses() > max)
		{
			max=(tmp->getstudent())->getnumofcourses();
		}
		tmp=tmp->getnext(0);
	}
	tmp=header->getnext(0);
	while(tmp->getnext(0) != NULL){		/*traverse through list*/
		/*to find those who have the greatest number of courses and their gpa is above gp*/
		if ((tmp->getstudent())->getnumofcourses() == max && (tmp->getstudent())->getgpa() > gp)
		{
			(tmp->getstudent())->printall();	/*each time one is found print him*/
			flag=true;
		}
		tmp=tmp->getnext(0);
	}
	if (!flag)		/*if none was printed*/
	{
		cerr<<"No students found above this gpa."<<endl;
	}
}