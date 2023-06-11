#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
struct ADDRESS{
	int h_no;
	char street[20];
	char area[30];
	char city[30];
	char country[30];
};
struct STUDENTS{
	int RollNo;
	char fname[30];
	char lname[30];
	int Age;
	float marks;
	char sports;
	char team[20];
	struct ADDRESS Address;
}stud;
void main()
{
	int del,f,i=0,ex=0,n;
	printf("\t\t\t\t-----------------------------------------\n");
	printf("\t\t\t\t--------Student Management System--------\n");
	printf("\t\t\t\t-----------------------------------------\n");
	while(!ex)
	{
		
		printf("---------------------------------------------------------------------------------\n");
		printf("\n\n\n1. Add a student's record\n2. Delete a student's record\n3. View all students' record\n4. Search student by roll no.\n5. View list of high achievers\n6. View students in sports teams\n7. Display total number of students\n8. Exit\n");
		printf("\nSelect a function (1,2,3...):  ");
		scanf("%d",&f);
		if(f==1)
		{
		    add_record(&stud);
		}
		else if(f==2)
		{
			del=delete_record();
			if(del)
			{
				printf("\nRecord deleted");
				getch();
			}
			else
			{
				printf("\nRoll number doesn't exist");
				getch();
			}
		}
		else if(f==3)
		all_records();
		else if(f==4)
		search_student();
		else if(f==5)
		high_achievers();
		else if(f==6)
		sports_team_students();
		else if(f==7)
		{
			n=total_students();
			printf("\n\nTotal number of students: %d",n);
			getch();
		}
		else if(f==8)
		{
			ex=1;
		}
		else
		{
    		printf("Invalid function selected\n");
    		getch();
    		system("cls");
		}
		system("cls");
	}
}
int add_record(struct STUDENTS *ptr)
{
	system("cls");
	int i=0,roll_no=0,sports=0;
	char new_record='Y',c,d;
	FILE *fptr,*fptr2;
	fptr=fopen("TEMP.txt","w");
	if(fptr==NULL)
	{
		printf("File not opened");
		exit(1);
	}
	fptr2=fopen("Students.txt","r");
	if(fptr2!=NULL)
	{
		while((c=fgetc(fptr2))!=EOF)
		{
			fputc(c,fptr);
			if(c=='\n')
			{
				d=fgetc(fptr2);
				if(d!=EOF)
				{
					fseek(fptr2,-sizeof(char),SEEK_CUR);
					fscanf(fptr2,"%d",&roll_no);
					fprintf(fptr,"%d",roll_no);
				}
			}
		}
	}
	while(new_record=='Y')
	{
		printf("---------------------------------------------------------------------------------\n");
		printf("\t\t\t\tADD RECORD\n\n");
		printf("\nEnter the information in BLOCK CAPITAL LETTERS\n\n");
		roll_no++;
		(ptr)->RollNo=roll_no;
		fprintf(fptr,"\n%d\t",(ptr)->RollNo);
		printf("First name: ");
		fflush(stdin);
		gets((ptr)->fname);
		fputs((ptr)->fname,fptr);
		fprintf(fptr,"\t");
		printf("Last name: ");
		fflush(stdin);
		gets((ptr)->lname);
		fputs((ptr)->lname,fptr);
		fprintf(fptr,"\t");
		printf("\nAge: ");
		fflush(stdin);
		scanf("%d",&(ptr)->Age);
		fprintf(fptr,"%d\t",(ptr)->Age);
		printf("\nMarks: ");
		fflush(stdin);
		scanf("%f",&(ptr)->marks);
		fprintf(fptr,"%.2f\t",(ptr)->marks);
		printf("Sports team (Y/N): ");
		fflush(stdin);
		scanf("%c",&(ptr)->sports);
		fprintf(fptr,"%c\t",(ptr)->sports);
		while(sports==0)
		{
			if((ptr)->sports=='Y')
			{
				printf("Team: ");
		    	fflush(stdin);
				scanf("%s",&(ptr)->team);
				fprintf(fptr,"%s\t",(ptr)->team);
				sports=1;
			}
			else if((ptr)->sports=='N')
			{
				fprintf(fptr,"None\t");
				sports=1;
			}
			else
			{
				printf("\nInvalid input. Write 'Y' or 'N'\n");
			}
		}
		printf("\nAddress");
		printf("\nHouse number: ");
		fflush(stdin);
		scanf("%d",&(ptr)->Address.h_no);
		fprintf(fptr,"%d\t",(ptr)->Address.h_no);
		printf("\nStreet: ");
		fflush(stdin);
		gets((ptr)->Address.street);
		fputs((ptr)->Address.street,fptr);
		fprintf(fptr,"\t");
		printf("Area: ");
		fflush(stdin);
		gets((ptr)->Address.area);
		fputs((ptr)->Address.area,fptr);
		fprintf(fptr,"\t");
		printf("City: ");
		fflush(stdin);
		gets((ptr)->Address.city);
		fputs((ptr)->Address.city,fptr);
		fprintf(fptr,"\t");
		printf("Country: ");
		fflush(stdin);
		gets((ptr)->Address.country);
		fputs((ptr)->Address.country,fptr);
	    printf("\n\nAdd another record?(Y/N): ");
	    scanf("%c",&new_record);
    }
    fclose(fptr);
    fclose(fptr2);
    remove("Students.txt");
	rename("TEMP.txt","Students.txt");
}
int delete_record()
{
	system("cls");
	int del_no,r_no,found=0,size=0;
	char c;
	FILE *fptr,*fptr2;
	printf("---------------------------------------------------------------------------------\n");
	printf("\t\t\t\tDELETE RECORD\n\n");
	printf("\nEnter roll number of student you want to delete: ");
	scanf("%d",&del_no);
	fptr=fopen("Students.txt","r");
	if(fptr==NULL)
	{
		printf("\nFile doesn't exist");
		exit(2);
	}
	fptr2=fopen("TEMP.txt","w");
	if(fptr2==NULL)
	{
		printf("File not opened");
		exit(3);
	}
	while((c=fgetc(fptr))!=EOF)
	{
		fputc(c,fptr2);
		if(c=='\n')
		{
			fscanf(fptr,"%d",&r_no);
			if(feof(fptr))
			{
				fseek(fptr,-sizeof(char),SEEK_CUR);
				break;
			}
			if(r_no==del_no)
			{
				found=1;
				while((c=fgetc(fptr))!='\n'&&c!=EOF)
				{
				}
			}
			else if(r_no!=del_no)
			{
				fprintf(fptr2,"%d",r_no);
			}
		}
	}
    fclose(fptr);
    fclose(fptr2);
    remove("Students.txt");
	rename("TEMP.txt","Students.txt");
	
	fptr=fopen("Students.txt","r");
	if(fptr==NULL)
	{
		printf("File not opened");
		exit(4);
	}
	while((c=fgetc(fptr))!=EOF)
	{
		size++;
	}
	fclose(fptr);
	if(size<=1)
	{
		remove("Students.txt");
	}
	if(found)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int all_records()
{
	system("cls");
	FILE *fptr;
	char c,h1[]="Roll no.",h2[]="First name",h3[]="Last name",h4[]="Age",h5[]="Sports(Y/N)",h6[]="Team",h7[]="House number",h8[]="Street",h9[]="Area",h10[]="City",h11[]="Country";
	printf("\nThe records are in the following order: \n%s-%s-%s-%s-%s-%s-%s-%s-%s-%s-%s\n----------------------------------------------------------------------------------------------------------\n",h1,h2,h3,h4,h5,h6,h7,h8,h9,h10,h11);
	fptr=fopen("Students.txt","r");
	if(fptr==NULL)
	{
		printf("\nNo records available");
		exit(7);
	}
	while((c=fgetc(fptr))!=EOF)
	{
		printf("%c",c);
	}
	fclose(fptr);
	getch();
}
int search_student()
{
	system("cls");
	int srch,roll_no,found=0;
	char c;
	FILE *fptr;
	printf("\n\nEnter roll number of student you want to find: ");
	scanf("%d",&srch);
	fptr=fopen("Students.txt","r");
	if(fptr==NULL)
	{
		printf("\nNo records available");
		exit(8);
	}
	printf("\n\n");
	while((c=fgetc(fptr))!=EOF)
	{
		if(c=='\n')
		{
			fscanf(fptr,"%d",&roll_no);
			{
				if(roll_no==srch)
				{
					found=1;
					printf("%d",roll_no);
					while((c=fgetc(fptr))!='\n'&&c!=EOF)
					{
						printf("%c",c);
					}
					break;
				}
			}
		}
	}
	if(!found)
	{
		printf("Roll number %d doesn't exist",srch);
	}
	fclose(fptr);
	getch();
}
int high_achievers()
{
	system("cls");
	FILE *fptr;
	char c;
	float marks;
	int roll_no,no_t=0,i=0,*ptr,n;
	n=total_students();
	fptr=fopen("Students.txt","r");
	if(fptr==NULL)
	{
		printf("NO reords exist");
		exit(9);
	}
	ptr=(int*) calloc(n,sizeof(int));
	while((c=fgetc(fptr))!=EOF)
	{
		if(c=='\n')
		{
			fscanf(fptr,"%d",&roll_no);
			no_t=0;
		}
		else if(c=='\t')
		{
			no_t++;
			if(no_t==4)
			{
				fscanf(fptr,"%f",&marks);
				if(marks>=90)
				{
					*(ptr+i)=roll_no;
					i++;
				}
			}
		}
	}
	rewind(fptr);
	printf("\nStudents with marks 90 or above are:\n\n");
	printf("\tFirst name-Last name-Marks\n--------------------------------------------------------------------------\n");
	while((c=fgetc(fptr))!=EOF)
	{
		if(c=='\n')
		{
			fscanf(fptr,"%d",&roll_no);
			for(i=0;i<n;i++)
			{
				if(roll_no==*(ptr+i))
				{
					no_t=0;
					while((c=fgetc(fptr))!='\n'&&c!=EOF)
					{
						if(c=='\t')
						{
							no_t++;
						}
						if(no_t<3||no_t==4)
						{
							printf("%c",c);
						}
					}
					if(c=='\n')
					{
						printf("\n");
						fseek(fptr,-sizeof(char),SEEK_CUR);
					}
				}
			}
		}
	}
	free(ptr);
	fclose(fptr);
	getch();
}
int sports_team_students()
{
	system("cls");
	int roll_no,no_t,*ptr,i=0,n;
	n=total_students();
	char c,y_n;
	FILE *fptr;
	fptr=fopen("Students.txt","r");
	if(fptr==NULL)
	{
		printf("NO reords exist");
		exit(10);
	}
	ptr=(int*) calloc(n,sizeof(int));
	while((c=fgetc(fptr))!=EOF)
	{
		if(c=='\n')
		{
			fscanf(fptr,"%d",&roll_no);
			no_t=0;
		}
		else if(c=='\t')
		{
			no_t++;
			if(no_t==5)
			{
				fscanf(fptr,"%c",&y_n);
				if(y_n=='Y'||y_n=='y')
				{
					*(ptr+i)=roll_no;
					i++;
				}
			}
		}
	}
	rewind(fptr);
	printf("\n\nRoll number - First name - Last name - Team\n----------------------------------------------------------------------------------------\n");
	while((c=fgetc(fptr))!=EOF)
	{
		if(c=='\n')
		{
			fscanf(fptr,"%d",&roll_no);
			no_t=0;
		}
		for(i=0;i<n;i++)
		{
			if(roll_no==*(ptr+i))
			{
				printf("%d",roll_no);
				while((c=fgetc(fptr))!='\n'&&c!=EOF)
				{
					if(c=='\t')
					{
						no_t++;
					}
					if(no_t<=2||no_t==6)
					{
						printf("%c",c);
					}
					
				}
				if(c=='\n')
				{
					printf("\n");
					fseek(fptr,-sizeof(char),SEEK_CUR);
				}
			}
		}
	}
	free(ptr);
	fclose(fptr);
	getch();
}
int total_students()
{
	system("cls");
	FILE *fptr;
	char c;
	int no=0;
	fptr=fopen("Students.txt","r");
	if(fptr==NULL)
	{
		printf("No records available");
		exit(6);
	}
	while((c=fgetc(fptr))!=EOF)
	{
		if(c=='\n')
		{
			no++;
		}
	}
	fclose(fptr);
	return no;
	
}
