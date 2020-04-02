/*
The name of the program is The Computer Science Advisor.  
It will be an innovative, evolving C++ console artificial intelligence application.  
Its job is to receive input of a student id and load in that student’s information such as classes taken, classes they need to take, the time of currently available classes, 
the instructors teaching those classes, and finally the student’s preference that were discovered via previous runnings of the application and make a smart class schedule.  
This smart class schedule will be based on the preferences of the student whose id was inputted in due to past runnings such as time, teachers, and classes, 
assuming the class is not required to graduate.  It will also only suggest classes that are open and then if there are not enough open classes fill in classes that are waitlist.
*/
/*
This program will be split up into: welcome menu to input student id to loading the student preferences file or making a new student preferences file if no id is found,
loading the data of the classes, finding the classes required by the student based on sub-major, making a class schedule from student preferences file and required courses,
to finally altering the student preferences file based on whether the student likes the class schedule created, repeating the program if they dislike it or exiting if they do.
*/
#include <iostream>
#include <string>
using namespace std;

void Welcome();
void InputId(Student);
bool LoadFile(Student);
void NewFile(Student);
bool NewClassSchedule(Student);
void MutatePreferences(Student);

class Student {
	string Fname, Lname, CWID;
	// I don't know how many preferences there will be so I put 10 here but using char for storage of it instead of binary will help store things better since 1 char is 8 binary preferences.
	// In this case 80 total binary preferences.
	// I have 10 different preferences of length 10 so we can mutate the other 9 preferences based on the first one.
	// I initialised it to  0000000000 for now but it will not likely stay that number since we need a preference number for newly made preferences.
	char SPreferences[10][10] = { {0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0} };
	
public:
	void setname(string, string);
	string getFname();
	string getLname();
	void setCWID(string);
	string getCWID();
	void setSPreferences(char[10], int);
	void getSPreferences(char[10], int);
};


int main()
{
	Student S;
	Welcome();
	InputId(S);
	if (!LoadFile(S))
		NewFile(S);
	bool Repeat = true;
	while (Repeat)
		Repeat = NewClassSchedule(S);
	system("pause");
}

void Welcome()
{
	cout << "Hello World";//not done lol
}
void InputId(Student S)
{
	string Fname, Lname, CWID;
	cout << "Please input your First Name: ";
	cin >> Fname;
	cout << "Please input your Last Name: ";
	cin >> Lname;
	cout << "Please input your CWID: ";
	cin >> CWID;
	S.setname(Fname, Lname);
	S.setCWID(CWID);
}
bool LoadFile(Student S)// will return true if name is found, else false
{

}
void NewFile(Student S)
{

}
bool NewClassSchedule(Student S)//will return true if the program needs to repeat
{
	MutatePreferences(S);
}
void MutatePreferences(Student S)
{

}

// Student functions

void Student::setname(string F, string L)
{
	Fname = F;
	Lname = L;
}
string Student::getFname()
{
	return Fname;
}
string Student::getLname()
{
	return Lname;
}
void Student::setCWID(string C)
{
	CWID = C;
}
string Student::getCWID()
{
	return CWID;
}
void Student::setSPreferences(char SP[10], int i)
{
	for (int j = 0; j < 10; j++)
		SPreferences[i][j] = SP[j];
}
void Student::getSPreferences(char SP[10], int i)
{
	for (int j = 0; j < 10; j++)
		SP[j] = SPreferences[i][j];
}