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
	bool Classtaken[36];

public:
	void setname(string, string);
	string getFname();
	string getLname();
	void setCWID(string);
	string getCWID();
	void setSPreferences(bool[10], int);
	void getSPreferences(bool[10], int);
	void setupbools();
	void setClasstaken(bool[36]);
	void getClasstaken(bool[36]);
};

void Welcome();
void InputId(Student&);
bool LoadFile(Student&);
bool NewFile(Student&);
void SaveNewFile(Student&);
void SaveOldFile(Student&);
bool NewClassSchedule(Student&,int);
void MutatePreferences(Student&);
bool preferncechecker(string, bool[10]);





int main()
{
	srand(time(NULL));
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
	int answer = 0;
	cout << endl << "How many classes do you want to take?(1-6) ";
	cin >> answer;
	while (Repeat)
		Repeat = NewClassSchedule(S, answer);
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
	bool Classtaken[36];
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
		for (int j = 0; j < 36; j++)
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
	bool Classtaken[36];
	S.getClasstaken(Classtaken);
	ofstream outfile;
	outfile.open("Studentinfo.txt", ios::app); // append instead of overwrite
	outfile << Fname<<","<<Lname<<","<<CWID;
	for (int i = 0; i < 10; i++)
		outfile << "," << SPreferences[i];
	for (int i = 0; i < 36; i++)
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
	bool Classtaken[36];
	S.getClasstaken(Classtaken);
	inputline = Fname + "," + Lname + "," + CWID;
	for (int i = 0; i < 10; i++)
	{
	if (SPreferences[i])
		inputline += ",1";
	else
		inputline += ",0";
}
	for (int i = 0; i < 36; i++)
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
bool NewClassSchedule(Student& S,int answer)//will return true if the program needs to repeat
{
	MutatePreferences(S);
	bool SPreferences[10], Classtaken[36];
	string classtime[2][6] = {"","", "", "", "", "", "", "", "", "", 
	"", ""}, tempclasstimestart = "", tempclasstimeend = "";
	string classdate[4][6] = { "","", "", "", "", "","","", "", "", "", "","","", "", "", "", "", "", "", "", "",
	"", "" }, tempclassdate[4] = { "","","","" };
	S.getClasstaken(Classtaken);
	int electives = 0;
	for (int q = 21; q < 36; q++)
		if (Classtaken[q])
			electives++;
	int num = 0, r = 0, c = 0;
	string ClassSchedule = "";
	string CSUFClasses[40], SubClasses[21][40];
	int i = 0, j = 0;
	for (i = 0; i < 40; i++)
	{
		CSUFClasses[i] = "~";
		for (int j = 0; j < 21; j++)
		{
			SubClasses[j][i] = "~";
		}
	}
	i = 0;
	ifstream readfile;
	readfile.open("ClassList.txt");
	string line;
	while (getline(readfile, line))
	{
		CSUFClasses[i] = line;
		//cout << "CSUFClasses[" << i << "]: " << CSUFClasses[i] << endl;
		j = 0;
		getline(readfile, line);
		while (line != ";")
		{
			SubClasses[j][i] = line;
			//cout << "SubClasses[" << j << "][" << i << "]: " << SubClasses[j][i] << endl;
			j++;
			getline(readfile, line);
		}
		i++;
	}
	readfile.close();
	for (i = 0; i < 5; i++)
	{

		if (!ClassSchedule.empty())
		{
			cout << endl<< "Class Schedule #" << i << endl;
			cout << ClassSchedule;
		}
		ClassSchedule = "";
		num = 0;
		S.getSPreferences(SPreferences, i);
		if (num == answer)
			continue;

		if (!Classtaken[0])//CPSC120
		{
			c = 5;//CPSC120
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d/2]+= SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate){
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{ 
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for(int g=0;g<3;g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++) 
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;
		if (!Classtaken[16])//Math 150A
		{
			c = 0;//Math 150A
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;
		if (!Classtaken[18])//Math270A
		{
			c = 2;//Math270A
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;
		if (!Classtaken[1] && Classtaken[0])//CPSC121
		{
			c = 6;//CPSC121
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;

				
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;
		if (!Classtaken[17] && Classtaken[16])//MATH150B
		{
			c = 1;//MATH150B
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;
		if (!Classtaken[19] && Classtaken[18])//MATH270B
		{
			c = 3;//MATH270B
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;
		if (!Classtaken[2] && Classtaken[1])//CPSC131
		{
			c = 7;//CPSC131
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;
		if (!Classtaken[20] && Classtaken[17])//MATH 338
		{
			c = 4;//MATH 338
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;
		if (!Classtaken[5] && Classtaken[2])//CPSC301
		{
			c = 13;//CPSC131
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;
		r = rand() % 2;
		if (!Classtaken[3] && Classtaken[2] && r == 0)//CPSC223C
		{
			c = 8;//CPSC223C
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		else if (!Classtaken[3] && Classtaken[2] && r == 1)//CPSC223P
		{
			c = 9;//CPSC223P
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;
		if (!Classtaken[4] && Classtaken[2] && Classtaken[18])//CPSC240
		{
			c = 10;//CPSC240
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;
		if (!Classtaken[6] && Classtaken[2])//CPSC311
		{
			c = 14;//CPSC311
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;
		if (!Classtaken[7] && Classtaken[6])//CPSC315
		{
			c = 15;//CPSC315
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;
		if (!Classtaken[8] && Classtaken[5])//CPSC323
		{
			c = 16;//CPSC323
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;
		if (!Classtaken[9] && Classtaken[2])//CPSC332
		{
			c = 17;//CPSC332
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;
		if (!Classtaken[10] && Classtaken[5])//CPSC335
		{
			c = 18;//CPSC335
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;
		if (!Classtaken[11] && Classtaken[2])//CPSC351
		{
			c = 19;//CPSC351
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;
		if (!Classtaken[12] && Classtaken[5])//CPSC362
		{
			c = 21;//CPSC362
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;
		if (!Classtaken[13] && Classtaken[4])//CPSC440
		{
			c = 26;//CPSC440
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;
		if (!Classtaken[14] && Classtaken[11])//CPSC471
		{
			c = 33;//CPSC471
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;
		if (!Classtaken[15] && Classtaken[10] && Classtaken[20])//CPSC481
		{
			c = 35;//CPSC481
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;
		int tempelectives = electives;
		if (tempelectives < 6 && !Classtaken[21] && Classtaken[2])//CPSC254
		{
			c = 12;//CPSC254
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				tempelectives++;
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;
		if (tempelectives < 6 && !Classtaken[22] && Classtaken[2])//CPSC353
		{
			c = 20;//CPSC353
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				tempelectives++;
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;
		if (tempelectives < 6 && !Classtaken[23] && Classtaken[2])//CPSC386
		{
			c = 22;//CPSC386
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				tempelectives++;
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;
		if (tempelectives < 6 && !Classtaken[24] && Classtaken[5])//CPSC411
		{
			c = 23;//CPSC411
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				tempelectives++;
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;
		if (tempelectives < 6 && !Classtaken[25] && Classtaken[9])//CPSC431
		{
			c = 24;//CPSC431
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				tempelectives++;
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;
		if (tempelectives < 6 && !Classtaken[26] && Classtaken[1] && Classtaken[19])//CPSC439
		{
			c = 25;//CPSC439
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				tempelectives++;
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;
		if (tempelectives < 6 && !Classtaken[27] && Classtaken[5] && Classtaken[19])//CPSC452
		{
			c = 27;//CPSC452
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				tempelectives++;
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;
		if (tempelectives < 6 && !Classtaken[28] && Classtaken[11])//CPSC456
		{
			c = 28;//CPSC456
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				tempelectives++;
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;
		if (tempelectives < 6 && !Classtaken[29] && Classtaken[12])//CPSC462
		{
			c = 29;//CPSC462
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				tempelectives++;
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;
		if (tempelectives < 6 && !Classtaken[30] && Classtaken[12])//CPSC463
		{
			c = 30;//CPSC463
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				tempelectives++;
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;
		if (tempelectives < 6 && !Classtaken[31] && Classtaken[12])//CPSC464
		{
			c = 31;//CPSC464
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				tempelectives++;
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;
		if (tempelectives < 6 && !Classtaken[32] && Classtaken[12])//CPSC466
		{
			c = 32;//CPSC466
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				tempelectives++;
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;
		if (tempelectives < 6 && !Classtaken[33] && Classtaken[11])//CPSC479
		{
			c = 34;//CPSC479
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				tempelectives++;
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;
		if (tempelectives < 6 && !Classtaken[34] && Classtaken[10] && Classtaken[20])//CPSC483
		{
			c = 36;//CPSC483
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				tempelectives++;
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;
		if (tempelectives < 6 && !Classtaken[35] && Classtaken[5] && Classtaken[17] && Classtaken[19])//CPSC484
		{
			c = 37;//CPSC484
			j = 0;
			while (SubClasses[j][c][0] != '~')
				j++;
			bool temp = true;
			int count = 0;
			bool broke = false;
			while (temp)
			{
				temp = false;
				r = rand() % j;
				temp = preferncechecker(SubClasses[r][c], SPreferences);
				int k = 0;
				while (SubClasses[r][c][k] != '\t')
					k++;
				k++;
				int d = 0;
				tempclassdate[0] = "";
				tempclassdate[1] = "";
				tempclassdate[2] = "";
				tempclassdate[3] = "";
				while (SubClasses[r][c][k] != ' ')
				{
					tempclassdate[d / 2] += SubClasses[r][c][k];
					d++;
					k++;
				}
				k++;
				tempclasstimestart = "";
				while (SubClasses[r][c][k] != '-')
				{
					tempclasstimestart += SubClasses[r][c][k];
					k++;
				}
				k++;
				tempclasstimeend = "";
				while (SubClasses[r][c][k] != '\t')
				{
					tempclasstimeend += SubClasses[r][c][k];
					k++;
				}
				for (int m = 0; m < 6; m++)
				{
					if (classtime[0][m].empty())
					{
						break;
					}
					bool trdate = false;
					for (int g = 0; g < 3; g++)
					{
						if (classdate[g][m].empty())
							break;
						if (classdate[g][m] == tempclassdate[g])
						{
							trdate = true;
						}
					}
					if (trdate) {
						if (classtime[0][m] == tempclasstimestart)
							temp = true;
						else if (classtime[1][m] == tempclasstimeend)
							temp = true;
						else if (tempclasstimestart > classtime[0][m] && tempclasstimestart < classtime[1][m])
							temp = true;
						else if (tempclasstimeend > classtime[0][m] && tempclasstimeend < classtime[1][m])
							temp = true;
					}
				}
				k++;
				count++;
				if (count > 100)
				{
					broke = true;
					break;
				}
			}
			if (!broke)
			{
				tempelectives++;
				ClassSchedule = ClassSchedule + CSUFClasses[c] + "\n" + SubClasses[r][c] + "\n";
				for (int g = 0; g < 3; g++)
					classdate[g][num] = tempclassdate[g];
				classtime[0][num] = tempclasstimestart;
				classtime[1][num] = tempclasstimeend;
			}
			for (int g = 0; g < 3; g++)
			{
				tempclassdate[g] = "";
			}
			tempclasstimestart = "";
			tempclasstimeend = "";
			num++;
		}
		if (num == answer)
			continue;

		if (ClassSchedule.empty())
		{
			i--;
			MutatePreferences(S);
		}
	}
	cout << endl << "Class Schedule #5" << endl;
	cout << ClassSchedule << endl;
	cout << "Which Class Schedule do you like the best?(1-5) ";
	int numb;
	cin >> numb;
	S.getSPreferences(SPreferences, numb-1);
	S.setSPreferences(SPreferences, 0);
	cout << "Do you want to stop now?(y/n) ";
	string st;
	cin >> st;
	return st!="y";
}
void MutatePreferences(Student &S)
{
	bool SPreferences[10];
	int r[5] = {0,0,0,0,0};
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
bool preferncechecker(string SubClasses, bool SPreferences[10])
{
	int k = 0;
	while (SubClasses[k] != '\t')
		k++;
	k++;
	if (SubClasses[k] == 'M' && SPreferences[2] == 1)//no Mondays
		return true;
	if (SubClasses[k] == 'T' && SubClasses[k + 1] == 'u' && SPreferences[3] == 1)//no Tuesdays
		return true;
	if (SubClasses[k] == 'W' && SPreferences[4] == 1)//no Wednesdays
		return true;
	if (SubClasses[k] == 'T' && SubClasses[k + 1] == 'h' && SPreferences[5] == 1)//no Thursdays
		return true;
	if (SubClasses[k] == 'F' && SPreferences[6] == 1)//no Fridays
		return true;
	if (SubClasses[k] == 'S' && SubClasses[k + 1] == 'a' && SPreferences[7] == 1)//no Sat
		return true;
	if (SubClasses[k] == 'S' && SubClasses[k + 1] == 'u' && SPreferences[8] == 1)//no Sun
		return true;
	while (SubClasses[k] != ' ')
		k++;
	k++;
	if ((SubClasses[k + 1] != '2' && (SubClasses[k + 4] != 'A' || SubClasses[k + 5] != 'A')) && SPreferences[0] == 1)//no mornings
		return true;
	if (((SubClasses[k] != '2'|| SubClasses[k] != '1' ) && (SubClasses[k + 4] != 'P' || SubClasses[k + 5] != 'P')) && SPreferences[1] == 1)//no Evenings
		return true;
	while (SubClasses[k] != '\t')
		k++;
	k++;
	if (SubClasses[k] == 'I' && SPreferences[9] == 1)//no off campus
		return true;
	return false;
}

// Student functions
void Student::setupbools()
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 10; j++)
			SPreferences[i][j] = 0;
	for (int i = 0; i < 36; i++)
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
void Student::setClasstaken(bool CT[36])
{
	for (int j = 0; j < 36; j++)
		Classtaken[j] = CT[j];
}
void Student::getClasstaken(bool CT[36])
{
	for (int j = 0; j < 36; j++)
		CT[j] = Classtaken[j];
}