# Library Management System Using Linked Lists

**Course:** Data Structures and Algorithmic Problem Solving  
**Assignment:** 1 – Linked Lists  

## Project Overview  
This project implements a console-based library management system in C++ using singly linked lists. It allows you to:

- **Read** student records from a file into a linked list, avoiding duplicates.  
- **Insert** book-borrowing records, calculate overdue fines, and attach them to the correct student.  
- **Delete** student records by ID.  
- **Search** for a student by ID and display their information.  
- **Display** student and book information to screen or file, with optional detail levels.  
- **Compute** and display statistics (number of students, books borrowed, overdue books, total fines) grouped by course.  
- **Find** all students who borrowed a specific book (by call number).  
- **Warn** students based on two criteria:  
  1. More than two books overdue ≥10 days.  
  2. Total fine > RM50 and all borrowed books are overdue.  
- **Present** a menu interface (`menu()`) for interactive operation.

## Input Files  
- **`students.txt`**  
  - Contains one student record per line, with fields:  
    ```
    id name course phone_no
    ```  
    Example:  
    ```
    1300345 John_Doe CS 123-4567
    ```  
- **`book.txt`**  
  - Contains one borrowed‐book record per line, with fields:  
    ```
    student_id author1[/author2…] title publisher ISBN yearPublished callNum date_borrow date_due
    ```  
    Example:  
    ```
    1300345 Tony_Gaddis/Godfrey_Muganda Starting_Out_with_Java Addison-Wesley 0321545869 2011 QA76.73.C153S26 11/1/2014 25/1/2014
    ```  
- **Assumptions:**  
  - Every month has 30 days.  
  - Overdue fine: RM 0.50 per day.  
  - “Current date” for fine calculations: 29/3/2020.

## Technical Details  
- **Language & Environment:**  
  - C++ (Visual Studio 2022)  
- **Dependencies:**  
  - Standard C++ libraries (`<iostream>`, `<fstream>`, `<string>`, `<vector>`, etc.)  
- **Error Handling:**  
  - Detects and reports missing input files.  
  - Ignores duplicate student IDs when reading.  
  - Validates search/delete operations and reports if not found.  

## Project Structure  
- **`app.cpp`**  
  - Entry point (`main()`), menu loop, and user‐interaction routines.  
- **`LibStudent.h` / `LibStudent.cpp`**  
  - `LibStudent` struct (ID, name, course, phone number, fine totals, borrowed‐book array)  
  - Member functions: constructor, `compareName1`, `compareName2`, `print`, `calculateTotalFine`.  
- **`LibBook.h` / `LibBook.cpp`**  
  - `LibBook` struct (title, authors[], publisher, ISBN, year, call number, fine, borrow/due dates)  
  - Member functions: constructor, `compareTitle`, `compareCallNum`, `print`.  
- **`Date.h` / `Date.cpp`**  
  - `Date` struct (day, month, year) and `print`.  
- **`List.h` / `List.cpp`**  
  - Singly linked list implementation managing `LibStudent` nodes.  

## Core Functions  
1. **`bool ReadFile(string filename, List *list)`**  
   Read students from file into `list`.  
2. **`bool DeleteRecord(List *list, const char *id)`**  
   Remove a student node by ID.  
3. **`bool SearchStudent(List *list, const char *id, LibStudent &stu)`**  
   Find a student by ID, return their data.  
4. **`bool InsertBook(string filename, List *list)`**  
   Read book assignments, compute fines, and append to the matching student’s book array.  
5. **`bool Display(List *list, int source, int detail)`**  
   Output data to screen or file, with optional detail (student only or student+books).  
6. **`bool computeAndDisplayStatistics(List *list)`**  
   Tabulate and display per‐course statistics (students, books, overdue counts, total fines).  
7. **`bool printStuWithSameBook(List *list, const char *callNum)`**  
   List all students borrowing a given call number, with borrow and due dates.  
8. **`bool displayWarnedStudent(List *list, List *type1, List *type2)`**  
   Identify and display students to warn under two defined misdemeanor types.  
9. **`int menu()`**  
   Display the interactive menu, accept and validate user choices.  

## Usage  
1. **Build:** Open the Visual Studio solution and **Build** all.  
2. **Run:** Ensure `students.txt` and `book.txt` are in the executable’s working directory.  
3. **Interact:** Follow on‐screen menu to perform tasks 1–9.  

## Testing  
- Verified correct handling of:  
  - File‐not‐found errors.  
  - Duplicate student IDs.  
  - Invalid delete/search requests.  
  - Overdue fine calculations under various due dates.  
  - Warning criteria for both misdemeanor types.  
