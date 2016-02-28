
























#include<fstream.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
class Directory
{
 char name[20];
 double num;
 char address[50];
 public:
 void enter()
  {
   cout<<"Enter name:"<<endl;
   gets(name);
   cout<<"Enter number:"<<endl;
   cin>>num;
   cout<<"Enter address:"<<endl;
   gets(address);
  }
 void show()
  {
   cout<<"Name - "<<name<<endl;
   cout<<"Number - "<<num<<endl;
   cout<<"Address - "<<address<<endl;
  }
 char *rname()
  {
   return name;
  }
 char *radd()//to return address
  {
   return address;
  }
};
void create()
 {
  fstream F;
  F.open("phonedirectory.dat",ios::binary|ios::app);
  Directory D; char ch;
  do
 {
    D.enter();
    F.write((char*)&D,sizeof(D));
    cout<<"Do you want to enter more(y/n)";
    cin>>ch;
   }while(ch=='y');
  F.close();
 }
void display()
 {
  fstream F;
  F.open("phonedirectory.dat",ios::binary|ios::in);
  Directory D;
  while(F.read((char*)&D,sizeof(D)))
   {
     D.show();
   }
   F.close();
}
char password()
{
char B[80];
char n;
int c=0;
while((long)n!=13)//13 is ascii for enter key
 {
  n=getch();
  B[c++]=n;
  cout<<"*";
 }
  B[c-1]='\0';
return *B;
}

void searchn()//search by name
{
 fstream F;
 Directory D;
 char name[20];
 int found=0;
 F.open("phonedirectory.dat",ios::binary|ios::in);
 cout<<"Enter name to be searched - ";
 gets(name);
 while(F.read((char*)&D,sizeof(D)))
  {
    if(strcmpi(name, D.rname())==0)
      {
      cout<<"Record Found"<<endl<<endl;
       D.show();
       found++;
      }
  }
 if(!found)
  {
   cout<<name<<endl<< "Not found "<<endl;
  }
 F.close();
}
void searchadd()//search by address
{
 fstream F;
 Directory D;
 char add[20];
 int found=0;
 F.open("phonedirectory.dat",ios::binary|ios::in);
 cout<<"Enter address to be searched - ";
 gets(add);
 while(F.read((char*)&D,sizeof(D)))
  {
    if(strcmpi(add, D.radd())==0)
      {
      cout<<"Record Found"<<endl<<endl;
       D.show();
       found++;
      }
  }
 if(!found)
  {
   cout<<add<<endl<< "Not found "<<endl;
  }
 F.close();
}
//int searchs()
void sortname()
{
  fstream F;
  F.open("phonedirectory.dat",ios::binary|ios::in);
   Directory D,newD;
  F.seekg(0,ios::end);
  int n=(F.tellg())/sizeof(D);//n=total records
   for(int i=0;i<n-1-i;i++)
    {
     for(int j=0;j<n-1-i;j++)
      {
       F.seekg(j*sizeof(D));
       F.read((char*)&D,sizeof(D));
       F.read((char*)&newD,sizeof(newD));
       if(strcmpi(D.rname(),newD.rname()))
	{
	 F.seekg(j*sizeof(D));
	 F.read((char*)&D,sizeof(D));
	 F.read((char*)&newD,sizeof(newD));
	}//if statement
       }//inner loop
     }//outer loop
  F.close();
}
void insrec()
{
  int choice;
 fstream F;
 F.open("phonedirectory.dat",ios::binary|ios::app);
 Directory D;
  do
   {
    cout<<"Enter the details for new record "<<endl;
     D.enter();
    F.write((char*)&D,sizeof(D));
    cout<<"Do you want to enter more records "<<endl;
    cout<<"1. Yes  "<<"2. No  "<<endl;
    cin>>choice;
   } while(choice==1);
  F.close();
 sortname();
}
void delrec()
{
 char delname[30];             //for checking the record to be deleted
 fstream F1,F2;
 F1.open("phonedirectory.dat",ios::binary|ios::in);
 F2.open("temp.dat",ios::binary|ios::app);
  Directory D;
  int del=0;//checking if name found
  cout<<"Enter the name of the record you want to enter";
  gets(delname);
  while(F1.read((char*)&D,sizeof(D))){
    {
      if((strcmpi(delname,D.rname()))!=0)
	{
	  F2.write((char*)&D,sizeof(D));
	}
       else
       del++;
    }
	 if(del)
	 cout<<"The record has been deleted";
	 F1.close();
	 F2.close();
	 remove("phonedirectory.dat");
	 rename("temp.dat","phonedirectory.dat");
	 sortname();
 }
void main()
{
clrscr();
int t;
int opt;
char pass[20];
cout<<"********* WELCOME *********"<<endl;
cout<<"********* TO *********"<<endl;
cout<<"********* YELLOW PAGES *********"<<endl;
cout<<"********* PHONE DIRECTORY *********"<<endl;
cout<<endl<<endl<<endl;
cout<<"SELECT YOUR IDENTITY"<<endl;
cout<<"1.VIEWER"<<endl;
cout<<"2.ADMINISTRATOR"<<endl;
cout<<"CHOICE - ";
cin>>opt;
if(opt==1)
{
 do
  {
    cout<<endl<<endl;
    cout<<"What would you like to do - "<<endl;
    cout<<"1.Search record"<<endl
	<<"2.Display record"<<endl
	<<"3.Exit"<<endl;
    cout<<"Enter choice - ";
    cin>>t;
    clrscr();
     switch(t)
      {
	case 1:searchn();
	break;
	case 2:display();
	cout<<endl<<endl<<endl;
	break;
	case 3: cout<<"Thank You"<<endl;
       }//for switch case
  }
 while(t!=3);//end of while
}
int choice;
else if(opt==2)
{
  cout<<"Enter Password - ";
  password();
  cout<<"What would you like to do - "<<endl;
    cout<<"1.Add"<<endl
	<<"2.Delete"<<endl
	<<"3.Edit"<<endl;
	<<"4.Search"<<endl;
	<<"5.Sort"<<endl;
	<<"6.Display"<<endl;
	<<"7.Exit"<<endl;
    cout<<"Enter choice - ";
    cin>>choice;
  clrscr();
     switch(choice)
      {
	case 1:insrec();
	break;
	case 2:delrec();
	cout<<endl<<endl<<endl;
	break;
	case 3:
	cout<<endl<<endl<<endl;
	break;
	case 4:searchn();
	cout<<endl<<endl<<endl;
	break;
	case 5:sortname();
	cout<<endl<<endl<<endl;
	break;
	case 6:display();
	cout<<endl<<endl<<endl;
	break;
	case 7: cout<<"Thank You"<<endl;
       }//for switch case
  }
 while(t!=3);//end of while
}
}

getch();
}