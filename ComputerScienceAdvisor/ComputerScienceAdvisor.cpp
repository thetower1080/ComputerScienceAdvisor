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
#include <fstream>
#include <time.h>
#include <stdlib.h> 
using namespace std;

class Student {
	string Fname, Lname, CWID;
	bool SPreferences[5][10];
	bool Classtaken[26];

public:
	void setname(string, string);
	string getFname();
	string getLname();
	void setCWID(string);
	string getCWID();
	void setSPreferences(bool[10], int);
	void getSPreferences(bool[10], int);
	void setupbools();
	void setClasstaken(bool[26]);
	void getClasstaken(bool[26]);
};

void Welcome();
void InputId(Student&);
bool LoadFile(Student&);
bool NewFile(Student&);
void SaveNewFile(Student&);
void SaveOldFile(Student&);
bool NewClassSchedule(Student&);
void MutatePreferences(Student&);





int main()
{
	bool infile, newst = true;
	Student S;
	Welcome();
	while (newst)
	{
		InputId(S);
		infile = LoadFile(S);
		if (!infile)
			newst = NewFile(S);
		else 
			newst = false;
	}
	bool Repeat = true;
	while (Repeat)
		Repeat = NewClassSchedule(S);
	if (infile)
		SaveOldFile(S);
	else 
		SaveNewFile(S);
}

void Welcome()
{
	cout << "Welcome to Computer Scinece Class Advisor."<<endl<<endl;
}
void InputId(Student& S)
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

bool LoadFile(Student& S)// will return true if name is found, else false
{
	string Fname, Lname, CWID;
	bool check=false;
	bool f = false;
	bool SPreferences[10];
	bool Classtaken[26];
	Fname = S.getFname();
	Lname = S.getLname();
	CWID = S.getCWID();
	ifstream readfile;
	readfile.open("Studentinfo.txt");
	string line;

	while (getline(readfile, line))
	{
		int i = 0;
		int j = 0;
		while (line[i] != ',')
		{
			f = true;
			if (j >= Fname.length() || Fname[j] != line[i])
			{
				f = false;
				break;
			}
			i++;
			j++;

		}
		if (!f)
			continue;
		i++;
		j = 0;
		while (line[i] != ',')
		{
			f = true;
			if (j >= Lname.length() || Lname[j] != line[i])
			{
				f = false;
				break;
			}
			i++;
			j++;
		}
		if (!f)
			continue;
		i++;
		j = 0;
		while (line[i] != ',')
		{
			f = true;
			if (j >= CWID.length() || CWID[j] != line[i])
			{
				f = false;
				break;
			}
			i++;
			j++;
		}
		if (!f)
			continue;
		i++;
		for (int j = 0; j < 10; j++)
		{
			SPreferences[j] = (line[i + j] == '1');
			i++;
		}
		S.setSPreferences(SPreferences, 0);
		i += 10;
		for (int j = 0; j < 26; j++)
		{
			Classtaken[j] = (line[i + j] == '1');
			i++;
		}
		S.setClasstaken(Classtaken);
		check = true;
		break;
	}
	readfile.close();
	return check;
}
bool NewFile(Student &S)
{
	string Fname, Lname, CWID,answer;
	Fname = S.getFname();
	Lname = S.getLname();
	CWID = S.getCWID();
	cout <<endl<< "Hello " << Fname << " " << Lname <<endl  << "I can't find your information are you a new student?(y/n)"<<endl;
	cin >> answer;
	if (answer[0] == 'y')
	{
		S.setupbools();
		return false;
	}
	else
	{
		cout << endl << "You may have enter your information incorectly. Please try again." << endl;
		return true;
	}
	
}
void SaveNewFile(Student& S)
{
	string Fname, Lname, CWID;
	Fname = S.getFname();
	Lname = S.getLname();
	CWID = S.getCWID();
	bool SPreferences[10];
	S.getSPreferences(SPreferences, 0);
	bool Classtaken[26];
	S.getClasstaken(Classtaken);
	ofstream outfile;
	outfile.open("Studentinfo.txt", ios::app); // append instead of overwrite
	outfile << Fname<<","<<Lname<<","<<CWID;
	for (int i = 0; i < 10; i++)
		outfile << "," << SPreferences[i];
	for (int i = 0; i < 26; i++)
		outfile << "," << Classtaken[i];
	outfile << endl;
	outfile.close();
}

void SaveOldFile(Student& S)
{
	string totalfile, line, inputline;
	string Fname, Lname, CWID;
	bool check;
	Fname = S.getFname();
	Lname = S.getLname();
	CWID = S.getCWID();
	bool SPreferences[10];
	S.getSPreferences(SPreferences, 0);
	bool Classtaken[26];
	S.getClasstaken(Classtaken);
	inputline = Fname + "," + Lname + "," + CWID;
	for (int i = 0; i < 10; i++)
	{
	if (SPreferences[i])
		inputline += ",1";
	else
		inputline += ",0";
}
	for (int i = 0; i < 26; i++)
		if (Classtaken[i])
			inputline = inputline + ",1";
		else
			inputline = inputline + ",0";
	ifstream file;
	file.open("Studentinfo.txt");
	getline(file, line);
	int i = 0;
	while (line[i] != ',')
	{
		i++;
	}
	i++;
	while (line[i] != ',')
	{
		i++;
	}
	i++;
	int j = 0;
	check = true;
	while (line[i] != ',')
	{
		check = true;
		if (j >= CWID.length() || CWID[j] != line[i])
		{
			check = false;
			break;
		}
		i++;
		j++;
	}
	if (check)
	{

		totalfile = inputline;
	}
	else
	{
		totalfile = line;
	}
	
	while (getline(file, line))
	{
		i = 0;
		check = "";
		while (line[i] != ',')
			i++;
		i++;
		while (line[i] != ',')
			i++;
		i++;
		while (line[i] != ',')
		{
			check = true;
			if (j >= CWID.length()||CWID[j] != line[i])
			{
				check = false;
				break;
			}
			i++;
			j++;
		}
		totalfile += "\n";
		if (check)
			totalfile += inputline;
		else
			totalfile += line;
	}
	file.close();
	ofstream outfile;
	outfile.open("Studentinfo.txt", ios::trunc);
	outfile << totalfile;
	file.close();
}
bool NewClassSchedule(Student &S)//will return true if the program needs to repeat
{
	MutatePreferences(S);

	return false;
}
void MutatePreferences(Student &S)
{
	bool SPreferences[10];
	int r[5] = {0,0,0,0,0};
	srand(time(NULL));
	for (int i = 1; i < 5; i++)
	{
		S.getSPreferences(SPreferences, 0);
		bool temp=true;
		while (temp)
		{
			temp = false;
			r[i] = rand() % 10;
			for (int j = 1; j < i; j++)
				if (r[j] == r[i])
					temp = true;
		}
		SPreferences[r[i]] = !SPreferences[r[i]];
		S.setSPreferences(SPreferences, i);
	}
}

// Student functions
void Student::setupbools()
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 10; j++)
			SPreferences[i][j] = 0;
	for (int i = 0; i < 26; i++)
		Classtaken[i] = 0;
}
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
void Student::setSPreferences(bool SP[10], int i)
{
	for (int j = 0; j < 10; j++)
	{
		SPreferences[i][j] = SP[j];
	}
}
void Student::getSPreferences(bool SP[10], int i)
{
	for (int j = 0; j < 10; j++)
	{
		SP[j] = SPreferences[i][j];
	}
}
void Student::setClasstaken(bool CT[26])
{
	for (int j = 0; j < 26; j++)
		Classtaken[j] = CT[j];
}
void Student::getClasstaken(bool CT[26])
{
	for (int j = 0; j < 26; j++)
		CT[j] = Classtaken[j];
}