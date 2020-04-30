 # Computer Science Advisor

The Computer Science Advisor is an evolving artificial intelligence application that creates a smart class schedule based on input received from a student.
The smart schedules are based on the preferences from the previous student input and it will take into newly discovered preferences.

### Clone or Download
* Clone the repo to your local machine using 'https://github.com/thetower1080/ComputerScienceAdvisor.git'
or  
Downlad as a zip from github

### Directory Structure
* ComputerScienceAdvisor-master/
    * Readme.md
    * ComputerScienceAdvisor.sln
    * ComputerScienceAdvisor/  
        * ClassList.txt  
        * prereqs.txt  
        * Studentinfo.txt  
        * ComputerScienceAdvisor.cpp  
        * ComputerScienceAdvisor.vcxproj  
        * ComputerScienceAdvisor.vcxproj.filters  
        * ComputerScienceAdvisor.vcxproj.user 
 * Note: ClassList.txt, prereqs.txt and Studentinfo.txt should remain in the ComputerScienceAdvisor directory

### Installation and Usage
Verify you have the following:
* For Windows: Microsoft Visual Studio 2019
    * Version: 16.0.29519.87
    * Minimum Version: 10.0.40219.1
    * Microsoft Visual C++ 2015-2019  
* For Linux: Gnu Compiler Collection(GCC) version 10.0.1


For Windows:
* Open the cloned repo in Visual Studio
    1. Go into cloned repo and double click on ComputerScienceAdvisor.sln, or
    2. Use File, Open, Project Solution and locating the repo, then selecting ComputerScienceAdvisor.sln
* Once the solution is loads, click on Run local windows debugger
* A console window should appear displaying the following
```
Welcome to Computer Science Advisor.

Please input your First Name:
```
For Linux:
* Open a terminal
* change directories into  the cloned repository
    > cd ComputerScienceAdvisor
* Compile using g++
    > g++ -o outfile_name file.cpp
    >Ex: g++ -o ComputerScienceAdvisor ComputerScienceAdvisor.cpp
* run executable
    > ./_Executable Name_
    >Ex: ./ComputerScienceAdvisor
* The terminal window should display the following
```
Welcome to Computer Science Advisor.
Please input your First Name:
```

### Using the program
* Once a console window is displayed, follow the prompts
1. Enter students first name
```
Welcome to Computer Science Advisor.
Please input your First Name:
```
2. Enter students last name
```
Welcome to Computer Science Advisor.
Please input your First Name:
Please input your Last Name:
```
3. Enter students CWID
```
Welcome to Computer Science Advisor.
Please input your First Name:
Please input your Last Name:
Please input your CWID:
```
4. If student is not found int Studentinfo.txt, a prompt asking if the student is new will appear
```
Welcome to Computer Science Advisor.
Please input your First Name:
Please input your Last Name:
Please input your CWID:

Hello Name
I can't find your information are you a new student?(y/n)
```
5. Next it will prompt for the amount of classes the student wants to take
```
Welcome to Computer Science Advisor.
Please input your First Name:
Please input your Last Name:
Please input your CWID:

Hello Name
I can't find your information are you a new student?(y/n)

How many classes do you want to take?(1-6)
```
6. The program will then print a list of classes schedules and prompt the student for input on which schedule is best.
7. The program will prompt if the student wants to end the program or generate more schedules based on the preference input.

### Project Files:
* ClassList.txt: Contains a list of all the computer science courses that are offered.
  
* prereqs.txt: Contains a list of all the prerequisite courses needed to take a computer science course.
  
* Studentinfo.txt: Used to contain student information. Consists of the students first name, last name, CWID, major, and class schedule preferences.
  
* ComputScienceAdisor.cpp:  Contains the artificial intelligence application.
    * Obtains student id to load the student preferences file or make a new student preferences file if no id is found,
    * Loads the data of the classes, 
    * Finds the classes required by the student based on sub-major, 
    * Makes a class schedule from student preferences file and required courses,
    * Alters the student preferences file based on whether the student likes the class schedule created
    * Repeats the program if they dislike it or exiting if they do.

### Libraries
* Used only libraries packaged with Microsoft Visual Studio or Gnu Compiler Collection

### Team Members
    Trenton Jansen
    Balwinder Hayer
    Laura Solorio
    Rene Ortiz
