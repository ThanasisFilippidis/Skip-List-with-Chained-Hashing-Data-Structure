#include "student.hpp"
#include "skiplist.hpp"
#include "hashtable.hpp"
#include <cstdio>
#include <cstdlib>

using namespace std;



int main(int argc, char const *argv[]){
	if (argc < 3)
	{
		cerr<<"Not enough arguments provided."<<endl;
		return -1;
	}
	FILE *fp;
	int entr=0;
	if (argc == 3)
	{
		if (argv[1][0] == '-')
		{
			if (argv[1][1] == 'b')
			{
				entr=atoi(&argv[2][0]);
				fp=NULL;
			}else{
				cerr<<"Number of hashentries must be provided."<<endl;
				return -1;
			}
		}else{
			cerr<<"Unexpected character."<<endl;
			return -1;
		}
	}else if (argc == 5)
	{
		if (argv[1][0] == '-')		/*first case: first flag given -b second -l*/
		{
			if (argv[1][1] == 'b')
			{
				entr=atoi(&argv[2][0]);
				if (argv[3][0] == '-')
				{
					if (argv[3][1] == 'l')
					{
						fp=fopen(&argv[4][0],"r");
						if (fp == NULL)
						{
							cerr<<"File couldn't be opened."<<endl;
							return -1;
						}
					}else{
						cerr<<"Unexpected character."<<endl;
						return -1;
					}
				}else{
					cerr<<"Unexpected character."<<endl;
					return -1;
				}
			}else if(argv[1][1] == 'l')		/*second case: first flag given -l second -b*/
			{
				fp=fopen(&argv[2][0],"r");
				if (fp == NULL)
				{
					cerr<<"File couldn't be opened."<<endl;
					return -1;
				}
				if (argv[3][0] == '-')
				{
					if (argv[3][1] == 'b')
					{
						entr=atoi(&argv[4][0]);
					}else{
						cerr<<"Unexpected character."<<endl;
						return -1;
					}
				}else{
					cerr<<"Unexpected character."<<endl;
					return -1;
				}
			}else{
				cerr<<"Unexpected character."<<endl;
				return -1;
			}
		}
		else{
			cerr<<"Unexpected character."<<endl;
			return -1;
		}
	}else{
		cerr<<"Not acceptable number of arguments."<<endl;
	}

	htable hasht(entr);
	slist skipl;


	char buff[260];

	if (argc == 5)		/*if there is a file input*/
	{
		while(!feof(fp)){		/*until the end of the file*/

			char buff2[260];
			char *func;
			float avg;
			char c[3];
			int stid;
			int stid2;
			char lname[30];
			char fname[30];
			float gp;
			char dprt[10];
			int numofcs;
			int pcode;
			int k;
			student *s;

			fgets(buff,sizeof(buff),fp);		/*get a line to the buffer*/
			strcpy(buff2,buff);		/*take a copy of that buffer*/
			func=strtok(buff," \n");		/*set to variable func the instruction given*/
			if (!strcmp(func,"i"))
			{
				sscanf(buff2,"%s %d %s %s %f %d %s %d",c,&stid,lname,fname,&gp,&numofcs,dprt,&pcode);
				//printf("%s %d %s %s %2.1f %d %s %d\n",c,stid,lname,fname,gp,numofcs,dprt,pcode);
				s=new student(stid,lname,fname,gp,numofcs,dprt,pcode);
				hasht.insert(s);
				skipl.insert(stid,s);
			}
			else if(!strcmp(func,"q")){
				sscanf(buff2,"%s %d",c,&stid);
				printf("%s %d\n",c,stid);
				s=skipl.search(stid);
				if (s != NULL)		/*if the returned pointer to the student is null it means he doesn't exist, so can't print*/
				{
					s->printall();
				}
			}
			else if(!strcmp(func,"m")){
				sscanf(buff2,"%s %d %f %d",c,&stid,&gp,&numofcs);
				printf("%s %d %2.1f %d\n",c,stid,gp,numofcs);
				s=skipl.search(stid);
				if (s != NULL)		/*if the returned pointer to the student is null it means he doesn't exist, so can't modify*/
				{
					s->gpamod(gp,numofcs);
				}
			}
			else if(!strcmp(func,"d")){
				sscanf(buff2,"%s %d",c,&stid);
				printf("%s %d\n",c,stid);
				pcode=-1;
				pcode=skipl.deletestud(stid);
				if (pcode != -1)		/*if returned postcode is -1 it means that no student with this id was found*/
				{						/*so cannot delete him either from the hash table*/
					hasht.deletestud(stid,pcode);
				}else{
					cerr<<"Student not found on SkipList."<<endl;
				}
			}
			else if(!strcmp(func,"ra")){
				sscanf(buff2,"%s %d %d",c,&stid,&stid2);
				printf("%s %d %d\n",c,stid,stid2);
				avg=skipl.raverege(stid,stid2);
				printf("Average gpa is %2.1f .\n",avg );
			}
			else if(!strcmp(func,"a")){
				sscanf(buff2,"%s %d",c,&pcode);
				printf("%s %d\n",c,pcode);
				avg=hasht.average(pcode);
				if (avg != -1)		/*if returned average gpa is -1 it means that no student with this postcode was found*/
				{
					printf("Average gpa is %2.1f .\n",avg );
				}else{
					cerr<<"Post code not found."<<endl;
				}
			}
			else if(!strcmp(func,"ta")){
				sscanf(buff2,"%s %d %d",c,&k,&pcode);
				printf("%s %d %d\n",c,k,pcode);
				hasht.taverage(k,pcode);
			}
			else if(!strcmp(func,"b")){
				sscanf(buff2,"%s %d",c,&k);
				printf("%s %d\n",c,k);
				skipl.bottom(k);
			}
			else if(!strcmp(func,"ct")){
				sscanf(buff2,"%s %d %s",c,&pcode,dprt);
				printf("%s %d %s\n",c,pcode,dprt);
				hasht.ct(pcode,dprt);
			}
			else if(!strcmp(func,"f")){
				sscanf(buff2,"%s %f",c,&gp);
				printf("%s %2.2f\n",c,gp);
				skipl.f(gp);
			}
			else if(!strcmp(func,"p")){
				sscanf(buff2,"%s %d",c,&pcode);
				printf("%s %d\n",c,pcode);
				hasht.p(pcode,skipl.getsize());
			}
			else if(!strcmp(func,"pe")){
				printf("pe\n");
				hasht.pe(skipl.getsize());
			}
			else if(!strcmp(func,"e")){
				printf("e\n");
				break;
			}else{
				cout<<"Function not found. Please try again"<<endl;
			}
		}
	fclose(fp);
	}
	/*Input file instructions if provided completed by this point. Handling control to the user*/
	/*Functions are exactly the same in both sections, for comments for each following function go to the first section,
	input by input file*/


	cout<<"Manual command insertion. If you want to exit type e."<<endl;


	fp=stdin;
	while(!feof(fp)){

		char buff2[260];
		char *func;
		float avg;
		char c[3];
		int stid;
		int stid2;
		char lname[30];
		char fname[30];
		float gp;
		char dprt[10];
		int numofcs;
		int pcode;
		int k;
		student *s;

		fgets(buff,sizeof(buff),fp);
		strcpy(buff2,buff);
		func=strtok(buff," \n");
		if (!strcmp(func,"i"))
		{
			sscanf(buff2,"%s %d %s %s %f %d %s %d",c,&stid,lname,fname,&gp,&numofcs,dprt,&pcode);
			//printf("%s %d %s %s %f %d %s %d\n",c,stid,lname,fname,gp,numofcs,dprt,pcode);
			s=new student(stid,lname,fname,gp,numofcs,dprt,pcode);
			hasht.insert(s);
			skipl.insert(stid,s);
		}
		else if(!strcmp(func,"q")){
			sscanf(buff2,"%s %d",c,&stid);
			printf("%s %d\n",c,stid);
			s=skipl.search(stid);
			if (s != NULL)
			{
				s->printall();
			}
		}
		else if(!strcmp(func,"m")){
			sscanf(buff2,"%s %d %f %d",c,&stid,&gp,&numofcs);
			printf("%s %d %f %d\n",c,stid,gp,numofcs);
			s=skipl.search(stid);
			if (s != NULL)
			{
				s->gpamod(gp,numofcs);
			}
		}
		else if(!strcmp(func,"d")){
			sscanf(buff2,"%s %d",c,&stid);
			printf("%s %d\n",c,stid);
			pcode=-1;
			pcode=skipl.deletestud(stid);
			if (pcode != -1)
			{
				hasht.deletestud(stid,pcode);
			}else{
				cerr<<"Student not found on SkipList."<<endl;
			}
		}
		else if(!strcmp(func,"ra")){
			sscanf(buff2,"%s %d %d",c,&stid,&stid2);
			printf("%s %d %d\n",c,stid,stid2);
			avg=skipl.raverege(stid,stid2);
			printf("Average gpa is %2.1f .\n",avg );
		}
		else if(!strcmp(func,"a")){
			sscanf(buff2,"%s %d",c,&pcode);
			printf("%s %d\n",c,pcode);
			avg=hasht.average(pcode);
			if (avg != -1)
			{
				printf("Average gpa is %2.1f .\n",avg );
			}else{
				cerr<<"Post code not found."<<endl;
			}
		}
		else if(!strcmp(func,"ta")){
			sscanf(buff2,"%s %d %d",c,&k,&pcode);
			printf("%s %d %d\n",c,k,pcode);
			hasht.taverage(k,pcode);
		}
		else if(!strcmp(func,"b")){
			sscanf(buff2,"%s %d",c,&k);
			printf("%s %d\n",c,k);
			skipl.bottom(k);
		}
		else if(!strcmp(func,"ct")){
			sscanf(buff2,"%s %d %s",c,&pcode,dprt);
			printf("%s %d %s\n",c,pcode,dprt);
			hasht.ct(pcode,dprt);
		}
		else if(!strcmp(func,"f")){
			sscanf(buff2,"%s %f",c,&gp);
			printf("%s %2.2f\n",c,gp);
			skipl.f(gp);
		}
		else if(!strcmp(func,"p")){
			sscanf(buff2,"%s %d",c,&pcode);
			printf("%s %d\n",c,pcode);
			hasht.p(pcode,skipl.getsize());
		}
		else if(!strcmp(func,"pe")){
			printf("pe\n");
			hasht.pe(skipl.getsize());
		}
		else if(!strcmp(func,"e")){
			printf("e\n");
			break;
		}else{
			cout<<"Function not found. Please try again"<<endl;
		}

	}
	return 0;
}