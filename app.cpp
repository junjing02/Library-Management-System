#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <iomanip>
#include "List.h"
#include "LibStudent.h"
#include "LibBook.h"

using namespace std;

bool ReadFile(string, List*);
bool DeleteRecord(List*, char*);
bool Display(List*, int, int);
bool InsertBook(string, List*);
bool SearchStudent(List*, char* id, LibStudent&);
bool computeAndDisplayStatistics(List*);
bool printStuWithSameBook(List*, char*);
bool displayWarnedStudent(List*, List*, List*);
int menu();

//for displayWarnedStudent function
bool printWarnedList(Node*, List*, ostream&);
bool checkRepeatWarned(Node*, List*);

//check for repetition
bool RedundantStudent(List*, LibStudent);
bool RedundantBook(List*, LibBook, char[]);

//functions to calculate days between 2 dates
int totalDays(Date);
int daysBetween(Date, Date);


//statistics according to course
struct Stats
{
    char course[3];
    int numStudents = 0;
    int bookBorrowed = 0;
    int totalOverdue = 0;
    double totalFine = 0.0;
};






int main()
{
    List* list1 = new List();

    string filename1 = "student.txt";
    string filename2 = "book.txt";
    LibStudent tmp;
    char id[10];
    int choice;
    int source, detail;
    char callNum[20];
    bool exit = false;

    while (!exit)
    {
        choice = menu();

        switch (choice)
        {
        case 1:
        {
            if (!ReadFile(filename1, list1))
            {
                cout << endl << "Error reading the file." << endl;
            }
            break;
        }

        case 2:
        {
            cout << endl << "-------------" << endl;
            cout << "DELETE RECORD" << endl;
            cout << "-------------" << endl;

            cout << endl << "Enter ID of student to REMOVE: ";
            cin.getline(id, 10);

            if (DeleteRecord(list1, id))
            {
                cout << endl << "Student " << id << " removed successfully" << endl;
            }
            else
            {
                cout << endl << "Student " << id << " was not found" << endl;
            }
            break;
        }

        case 3:
        {
            cout << endl << "-------------" << endl;
            cout << "SEARCH RECORD" << endl;
            cout << "-------------" << endl;

            cout << endl << "Enter ID of student to SEARCH: ";
            cin.getline(id, 10);

            if (!SearchStudent(list1, id, tmp))
            {
                cout << endl << "Student " << id << " was not found" << endl;
            }
            break;
        }

        case 4:
        {
            if (InsertBook(filename2, list1))
            {
                cout << endl << "Books successfully inserted" << endl;
            }
            else
            {
                cout << endl << "Failed to insert books" << endl;
            }
            break;
        }

        case 5:
        {
            cout << endl << "--------------" << endl;
            cout << "DISPLAY OUTPUT" << endl;
            cout << "--------------" << endl;
            do
            {
                cout << endl << "Where do you want to display the output? (1-File / 2-Screen): ";
                cin >> source;
                cin.ignore();

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid input" << endl;
                    main();
                }
                else if (source < 1 || source > 2)
                {
                    cout << "Invalid input" << endl;
                    main();
                }

                do
                {
                    cout << endl << "Do you want to display book list for every student? (1-YES / 2-NO): ";
                    cin >> detail;
                    cin.ignore();

                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "Invalid input" << endl;
                    }
                    else if (detail < 1 || detail > 2)
                    {
                        cout << "Invalid input" << endl;
                    }

                } while (detail < 1 || detail > 2);

            } while (source < 1 || source > 2);

            cout << endl << endl;

            if (!Display(list1, source, detail))
            {
                cout << endl << "Failed to display" << endl;
            }
            else
            {
                cout << endl << "Display successful" << endl;
            }
            break;
        }

        case 6:
        {
            if (!computeAndDisplayStatistics(list1))
            {
                cout << endl << "Failed to display statistics" << endl;
            }
            else
            {
                cout << endl << "Successfully display statistics" << endl;
            }
            break;
        }

        case 7:
        {
            cout << endl << "------------" << endl;
            cout << "SEARCH BOOK" << endl;
            cout << "------------" << endl;

            cout << endl << "Please enter call number of the book: ";
            cin.getline(callNum, 20);

            if (!printStuWithSameBook(list1, callNum))
            {
                cout << endl << "Failed to display" << endl;
            }
            break;
        }

        case 8:
        {
            List* type1 = new List();
            List* type2 = new List();

            if (!displayWarnedStudent(list1, type1, type2))
            {
                cout << endl << "Failed to display warned student" << endl;
            }
            break;
        }


        case 9:
        {
            cout << endl << "Exiting..." << endl;
            exit = true;
            break;
        }

        default:
        {
            cout << endl << "Invalid input" << endl;
            continue;
        }
        }
    }

    cout << "\n\n";
    system("pause");
    return 0;
}

bool ReadFile(string filename, List* list)
{
    ifstream infile(filename);
    string s;
    LibStudent student;
    int count = 0;

    if (!infile.is_open())
    {
        cout << "Error opening file \"" << filename << "\"" << endl;
        return false;
    }
    else
    {
        cout << endl << "---------" << endl;
        cout << "READ FILE" << endl;
        cout << "---------" << endl;
        while (!infile.eof())
        {
            //get rid of the words in front
            for (int i = 0; i < 3; i++)
            {
                infile >> s;
            }
            infile >> student.id;

            //get rid of the words in front
            for (int i = 0; i < 2; i++)
            {
                infile >> s;
            }
            infile.ignore(1);
            infile.getline(student.name, 30);

            //get rid of the words in front
            for (int i = 0; i < 2; i++)
            {
                infile >> s;
            }
            infile >> student.course;

            //get rid of the words in front
            for (int i = 0; i < 3; i++)
            {
                infile >> s;
            }
            infile >> student.phone_no;

            //check whether student existed or not
            if (!RedundantStudent(list, student))
            {
                //insert alphabeltically
                list->insert(student);
                count++;
            }
        }
        cout << endl << count << " new records have been successfully read" << endl;
    }
    infile.close();
    return true;
}

bool DeleteRecord(List* list, char* id)
{
    LibStudent tmp;
    Node* cur;
    int i = 1;

    if (list->empty())
    {
        cout << endl << "The list is empty" << endl;
        return false;
    }
    cur = list->head;

    while (cur != NULL)
    {
        //if found, remove it
        if (strcmp(cur->item.id, id) == 0)
        {
            list->remove(i);
            return true;
        }
        cur = cur->next;
        i++;
    }
    return false;
}

bool SearchStudent(List* list, char* id, LibStudent& stu)
{
    Node* cur;
    if (list->empty())
    {
        cout << endl << "The list is empty" << endl;
        return false;
    }
    cur = list->head;

    while (cur != NULL)
    {
        //if found, print it
        if (strcmp(cur->item.id, id) == 0)
        {
            cur->item.print(cout);
            return true;
        }
        cur = cur->next;
    }
    return false;
}

bool InsertBook(string filename, List* list)
{
    ifstream infile(filename);
    char id[10];
    string str, num;
    Node* cur;
    int count;


    //current date
    Date today;
    today.day = 29;
    today.month = 3;
    today.year = 2020;


    cout << endl << "-----------" << endl;
    cout << "INSERT BOOK" << endl;
    cout << "-----------" << endl;

    if (list->empty())
    {
        cout << endl << "List is empty" << endl;
        return false;
    }

    if (!infile.is_open())
    {
        cout << endl << "Error opening file \"" << filename << "\"" << endl;
        return false;
    }
    else
    {
        while (!infile.eof())
        {
            LibBook tmp;

            infile >> id;
            infile >> str;  //store all authors in a string first

            //breakdown str into each author
            stringstream ss(str);
            string person;
            int i = 0;

            while (getline(ss, person, '/'))
            {
                tmp.author[i] = new char[person.size() + 1];
                strcpy(tmp.author[i], person.c_str());
                i++;
            }

            infile >> tmp.title;
            infile >> tmp.publisher;
            infile >> tmp.ISBN;
            infile >> tmp.yearPublished;
            infile >> tmp.callNum;

            //borrow date
            getline(infile, num, '/');
            tmp.borrow.day = stoi(num);
            getline(infile, num, '/');
            tmp.borrow.month = stoi(num);
            infile >> num;
            tmp.borrow.year = stoi(num);

            //due date
            getline(infile, num, '/');
            tmp.due.day = stoi(num);
            getline(infile, num, '/');
            tmp.due.month = stoi(num);
            infile >> num;
            tmp.due.year = stoi(num);
            infile.ignore();

            //calculate number of days from due date
            int days = daysBetween(tmp.due, today);
            if (days > 0)
            {
                tmp.fine += days * 0.5;
            }
            else
            {
                tmp.fine = 0;
            }

            //if the book is new, insert it
            if (!RedundantBook(list, tmp, id))
            {
                bool found = false;

                cur = list->head;
                while (cur != NULL)
                {
                    if (strcmp(cur->item.id, id) == 0)
                    {
                        count = cur->item.totalbook;
                        cur->item.book[count] = tmp;
                        cur->item.totalbook++;
                        cur->item.calculateTotalFine();
                        found = true;
                        break;
                    }
                    cur = cur->next;
                }
                //if student id is not existed
                if (!found)
                {
                    cout << endl << "Student " << id << " was not found" << endl;
                    cout << "\"" << tmp.title << "\" failed to insert" << endl;
                }
            }
        }
    }
    infile.close();
    return true;
}

bool Display(List* list, int source, int detail)
{
    Node* cur = list->head;
    int i = 1;

    if (list->empty())
    {
        cout << endl << "List is empty" << endl;
        return false;
    }

    //display in FILE
    if (source == 1)
    {
        //withtout book list
        if (detail == 2)
        {
            ofstream outfile1("student_info.txt");
            if (!outfile1)
            {
                cout << "Error opening file \"student_info.txt\"" << endl;
                return false;
            }
            else
            {
                while (cur != NULL)
                {
                    outfile1 << endl << "STUDENT " << i;
                    cur->item.print(outfile1);
                    outfile1 << endl;
                    outfile1 << "************************************************************************************" << endl;
                    cur = cur->next;
                    i++;
                }
                outfile1.close();
                cout << "Saved in \"student_info.txt\"" << endl;
                return true;
            }

        }
        //with book list
        else
        {
            ofstream outfile2("student_booklist.txt");
            if (!outfile2)
            {
                cout << "Error opening file \"student_booklist.txt\"" << endl;
                return false;
            }
            else
            {
                while (cur != NULL)
                {
                    outfile2 << endl << "STUDENT " << i;
                    cur->item.print(outfile2);
                    outfile2 << endl << endl << "BOOK LIST:" << endl;
                    for (int j = 0; j < cur->item.totalbook; j++)
                    {
                        outfile2 << endl << "Book " << j + 1 << endl;
                        cur->item.book[j].print(outfile2);
                    }
                    outfile2 << endl << endl;
                    outfile2 << "************************************************************************************" << endl;
                    cur = cur->next;
                    i++;
                }
                outfile2.close();
                cout << "Saved in \"student_booklist.txt\"" << endl;
                return true;
            }
        }
    }
    //display on SCREEN
    else
    {
        //without book list
        if (detail == 2)
        {
            while (cur != NULL)
            {
                cout << endl << "STUDENT " << i;
                cur->item.print(cout);
                cout << endl;
                cout << "************************************************************************************" << endl;
                cur = cur->next;
                i++;
            }
            return true;
        }
        //with book list
        else
        {
            while (cur != NULL)
            {
                cout << endl << "STUDENT " << i;
                cur->item.print(cout);
                cout << endl << endl << "BOOK LIST:" << endl;
                for (int j = 0; j < cur->item.totalbook; j++)
                {
                    cout << endl << "Book " << j + 1 << endl;
                    cur->item.book[j].print(cout);
                }
                cout << endl << endl;
                cout << "************************************************************************************" << endl;
                cur = cur->next;
                i++;
            }
            return true;
        }
    }
    return false;
}

bool computeAndDisplayStatistics(List* list)
{
    Node* cur;
    Stats stat[20];
    int count = 0, days;
    bool found = false;

    //current date
    Date today;
    today.day = 29;
    today.month = 3;
    today.year = 2020;

    cout << endl << "------------------" << endl;
    cout << "DISPLAY STATISTICS" << endl;
    cout << "------------------" << endl;

    if (list->empty())
    {
        cout << endl << "List is empty" << endl;
        return false;
    }
    cur = list->head;

    for (; cur != NULL;)
    {
        //if array stat[] is empty
        if (count == 0)
        {
            strcpy(stat[count].course, cur->item.course);
            stat[count].numStudents++;
            stat[count].bookBorrowed += cur->item.totalbook;

            for (int i = 0; i < cur->item.totalbook; i++)
            {
                //calculate days between due date
                days = daysBetween(cur->item.book[i].due, today);
                if (days > 0)
                {
                    stat[count].totalOverdue++;
                }
            }
            stat[count].totalFine += cur->item.total_fine;
            count++;
        }
        else
        {
            for (int i = 0; i < count; i++)
            {
                //if course already existed in stat[]
                if (strcmp(cur->item.course, stat[i].course) == 0)
                {
                    stat[i].numStudents++;
                    stat[i].bookBorrowed += cur->item.totalbook;

                    for (int j = 0; j < cur->item.totalbook; j++)
                    {
                        //calculate days between due date
                        days = daysBetween(cur->item.book[j].due, today);
                        if (days > 0)
                        {
                            stat[i].totalOverdue++;
                        }
                    }
                    stat[i].totalFine += cur->item.total_fine;
                    found = true;
                    break;
                }
            }
            //if course is new to stat[]
            if (!found)
            {
                strcpy(stat[count].course, cur->item.course);
                stat[count].numStudents++;
                stat[count].bookBorrowed += cur->item.totalbook;

                for (int i = 0; i < cur->item.totalbook; i++)
                {
                    //calculate days between due date
                    days = daysBetween(cur->item.book[i].due, today);
                    if (days > 0)
                    {
                        stat[count].totalOverdue++;
                    }
                }
                stat[count].totalFine += cur->item.total_fine;
                count++;
            }
        }
        cur = cur->next;
        found = false;
    }
    cout << endl;
    cout << "Course\tNumber of Students\tTotal Books Borrowed\tTotal Overdue Books\tTotal Overdue Fine(RM)" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < count; i++)
    {
        cout << stat[i].course << "\t" << stat[i].numStudents << "\t\t\t" << stat[i].bookBorrowed << "\t\t\t" << stat[i].totalOverdue << "\t\t\t" << fixed << setprecision(2) << stat[i].totalFine << endl;
    }
    return true;
}

bool printStuWithSameBook(List* list, char* callNum)
{
    Node* cur = list->head;
    int index = 0;

    if (list->empty())
    {
        cout << endl << "List is empty" << endl;
        return false;
    }

    //find student that have borrowed the book
    while (cur != NULL)
    {
        for (int i = 0; i < cur->item.totalbook; i++)
        {
            if (strcmp(cur->item.book[i].callNum, callNum) == 0)
            {
                index++;
            }
        }
        cur = cur->next;
    }
    //book was not found
    if (index == 0)
    {
        cout << endl << "Book was not found" << endl;
        return false;
    }

    cout << endl << "There are " << index << " students that borrow the book with call number " << callNum << " as shown below: " << endl << endl;

    cur = list->head;
    while (cur != NULL)
    {
        for (int i = 0; i < cur->item.totalbook; i++)
        {
            if (strcmp(cur->item.book[i].callNum, callNum) == 0)
            {
                cout << "Student ID = " << cur->item.id << endl;
                cout << "Name = " << cur->item.name << endl;
                cout << "Course = " << cur->item.course << endl;
                cout << "Phone Number = " << cur->item.phone_no << endl;
                cout << "Borrow Date = ";
                cur->item.book[i].borrow.print(cout);
                cout << endl << "Due Date = ";
                cur->item.book[i].due.print(cout);
                cout << endl;
                cout << endl << endl;
                break;
            }
        }
        cur = cur->next;
    }
    return true;
}

bool displayWarnedStudent(List* list, List* type1, List* type2)
{
    Node* cur = list->head;
    int days;

    //current date
    Date today;
    today.day = 29;
    today.month = 3;
    today.year = 2020;


    if (list->empty())
    {
        return false;
    }

    while (cur != NULL)
    {
        int bookOverdue = 0;

        //overdue more than 10 days
        for (int i = 0; i < cur->item.totalbook; i++)
        {
            //call out function calculate day overdue
            days = daysBetween(cur->item.book[i].due, today);
            if (days >= 10)
            {
                bookOverdue++;
            }
        }

        //more than 2 books overdue
        if (bookOverdue > 2)
        {
            //avoid second time call add again in list
            if (checkRepeatWarned(cur, type1))
            {
                type1->insert(cur->item);
            }
        }

        //every books are overdue and total fine more than 50
        if (bookOverdue == cur->item.totalbook && cur->item.total_fine > 50)
        {
            if (checkRepeatWarned(cur, type2))
            {
                type2->insert(cur->item);
            }
        }

        cur = cur->next;
    }

    //pointer for list type 1 and 2
    Node* curt1 = type1->head;
    Node* curt2 = type2->head;

    cout << endl << "-----------------------" << endl;
    cout << "List of Warned Student" << endl;
    cout << "-----------------------" << endl;
    cout << "Today:  ";

    //tell overdue calculate by this date
    today.print(cout);
    cout << endl << endl;

    cout << "Type 1 List: Student has more than 2 books that overdue >= 10 days" << endl << endl;

    //call out function for display
    if (!printWarnedList(curt1, type1, cout))
    {
        cout << "No student in warned list" << endl << endl;
    }

    cout << endl << "Type 2 List: Student has every books are overdue and total fine > 50" << endl << endl;

    if (!printWarnedList(curt2, type2, cout))
    {
        cout << "No student in warned list" << endl << endl;
    }

    return true;
}

int menu()
{
    bool valid = false;
    int choice;

    do
    {
        cout << endl << endl;
        cout << "----" << endl;
        cout << "MENU" << endl;
        cout << "----" << endl << endl;
        cout << "1. Read File" << endl;
        cout << "2. Delete Record" << endl;
        cout << "3. Search Student" << endl;
        cout << "4. Insert Book" << endl;
        cout << "5. Display Output" << endl;
        cout << "6. Compute and Display Statistics" << endl;
        cout << "7. Student with Same Book" << endl;
        cout << "8. Display Warned Student" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice (1-9): ";
        cin >> choice;
        cin.ignore();

        //if input is not integer
        if (cin.fail())
        {
            cout << "Invalid Input." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else if (choice < 1 || choice > 9)
        {
            cout << "Invalid Input." << endl;
        }
        else
        {
            valid = true;
        }

    } while (!valid);
    return choice;
}






bool RedundantStudent(List* list, LibStudent student)
{
    Node* cur;
    cur = list->head;

    while (cur != NULL)
    {
        if (cur->item.compareName2(student))
        {
            return true;
        }
        cur = cur->next;
    }
    return false;
}

bool RedundantBook(List* list, LibBook book, char id[])
{
    Node* cur;
    if (list->empty())
    {
        cout << endl << "The list is empty" << endl;
        return false;
    }
    cur = list->head;

    while (cur != NULL)
    {
        if (strcmp(cur->item.id, id) == 0)
        {
            for (int i = 0; i < cur->item.totalbook; i++)
            {
                if (cur->item.book[i].compareCallNum(book))
                {
                    return true;
                }
            }
        }

        cur = cur->next;
    }
    return false;
}

int totalDays(Date date)
{
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int total = date.year * 365 + date.day;

    for (int i = 0; i < date.month - 1; i++)
    {
        total += daysInMonth[i];
    }

    if (date.month > 2 && (date.year % 4) == 0)
    {
        total += 1; // Add an extra day for leap year
    }

    return total;
}

int daysBetween(Date start, Date end)
{
    int Start = totalDays(start);
    int End = totalDays(end);

    int daysDiff = End - Start;

    return daysDiff;
}

bool printWarnedList(Node* cur, List* type, ostream& out)
{
    int count = 1;

    if (type->empty())
    {
        return false;
    }

    while (cur != NULL)
    {
        out << "Student " << count;
        cur->item.print(cout);
        out << endl << "Book List:" << endl << endl;
        for (int i = 0; i < cur->item.totalbook; i++)
        {
            out << "Book " << i + 1 << endl;
            cur->item.book[i].print(cout);
            out << endl;
        }
        out << endl << "************************************************************************************" << endl;

        count++;
        cur = cur->next;
    }
    return true;
}

bool checkRepeatWarned(Node* cur, List* type)
{
    Node* tmp;
    tmp = type->head;

    if (type->empty())
    {
        return true;
    }
    else
    {
        for (int i = 0; i < type->size(); i++)
        {
            if (strcmp(cur->item.name, tmp->item.name) == 0)
            {
                return false;
            }
            tmp = tmp->next;
        }
    }
    return true;
}