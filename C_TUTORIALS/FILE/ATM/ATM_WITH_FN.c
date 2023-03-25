#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char name_db[100][50],pass_db[100][50];
int i=0;
void display_names()
{
	int j;
	for(j=1;j<=i;j++)
	{
		printf("name%d: %s\n",j,name_db[j]);
	}
}
void display_passes()
{
	int j;
	for(j=1;j<=i;j++)
	{
		printf("pass%d: %s\n",j,pass_db[j]);
	}
}

void create()
{
	static int k=0;
	i++;
	char u_name[50],u_pass[50],u_pass1[50];															//printf("inside create");
	printf("ENTER USERNAME:");
	scanf("%s",u_name);
	strcpy(name_db[i],u_name);
	printf("ENTER PASSWORD:");
	scanf("%s",u_pass);
	printf("ENTER PASSWORD AGAIN:");
	scanf("%s",u_pass1);
	if(strcmp(u_pass1,u_pass)!=0)
	{
			printf("\n  PASSWORD MISMATCH \n\n");
			create();
	}
	strcpy(pass_db[i],u_pass);
	printf("\n  USER CREATED SUCCESSFULLY \n\n");
	admin();
}

void delete()
{
																//printf("inside delete");
}
void admin()
{
	int ch;														
	printf("1.CREATE USER\n");
	printf("2.DELETE USER \n");
	printf("3.DISPLAY DETAILS\n");
	printf("4.BACK\n");
	printf("Enter Your Choice:");
	scanf("%d",&ch);
	if(ch==1)
		{
			create();
		}
		else if(ch==2)
		{
			delete();
		}
		else if(ch==3)
		{
			display_names();
			display_passes();
		}
		else if(ch==4)
		{
			main();
		}
		else
		{
			printf("INVALID SELECTION\n");
			admin();
		}
}
int validation(int index,char *u_pass)
{
	int pass_stat=strcmp(u_pass,pass_db[index]);
	if(pass_stat==0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void user_display()
{
printf("1.VIEW BALANCE\n");
printf("2.DEPOSIT CASH");
printf("3.WITHDRAW CASH");
printf("4.BACK");																					
																					//printf("inside user_display");
}
void user()
{
	int index=0,j,stat,match,name_stat;
	char u_name[50],u_pass[50];															//	printf("inside user");
	printf("Username:");
	scanf("%s",u_name);
	printf("Password:");
	scanf("%s",u_pass);
	for(j=1;j<=i;j++)
	{
		name_stat=strcmp(name_db[j],u_name);
		if(name_stat==0)
		{
			index=j;
			match=validation(index,u_pass);
			if(match==1)
			{
				user_display();
			}
			else
			{
				printf("\n Incorrect Password\n\n");
			}
			user();
		}
		else
		{
			name_stat=1;       //----
		}

	}
	if(name_stat==1)
		{
			printf("\n Username Not Found\n\n");	
		}
}
	void main()
	{
		int ch;
		while(1)
		{
		printf("WHO DO YOU WANT TO LOGIN AS:\n");
		printf("1.ADMIN\n");
		printf("2.USER\n");
		printf("3.EXIT\n");
		printf("Enter Your Choice:");
		scanf("%d",&ch);
		if(ch==1)
		{
			admin();
		}
		else if(ch==2)
		{
			user();
		}
		else if(ch==3)
		{
			exit(0);
		}
		else
		{
			printf("Invalid Selection");
		}
	}
	}

