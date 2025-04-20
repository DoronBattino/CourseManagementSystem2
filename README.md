# CourseManagementSystem2
Next generation of course managment system

Overview:
This project simulates a Course Manager System that allows managing students, friendships, course grades, and generating various reports.
It reads commands from an input file and outputs results to an output file, or can be used interactively through standard input/output.
Features

    Student Management

        Add and remove students.

        Login and logout.

        Send and handle friend requests.

        Unfriend students.

    Grade Sheet Management

        Add, update, and remove course grades.

    Reports

        Print full or clean grade sheets.

        Print best or worst grades.

        Generate faculty-specific reports.

        Generate reference reports between students.

Input File Format

The input file consists of a series of commands.
Lines starting with # are treated as comments and ignored.
Example Commands:

# Add students
student add 1001 Alice CS
student add 1002 Bob EE

# Login as Alice
student login 1001

# Alice sends friend request
student friend_request 1002

# Alice adds grades
grade_sheet add 202102 234218 3.0 79

# Print Alice's full grade sheet
report full

# Alice logs out
student logout

How to Compile

gcc -std=c99 -Wall -Wextra -o main main.c course_manager.c ex3.c

Make sure all source (.c) and header (.h) files are in the same folder.
How to Run

Run with input and output files:

./main -i input.txt -o output.txt

Run interactively without files:

./main

Usage Examples
1. Input Example (input.txt)

# Adding Students
student add 1001 Alice CS
student add 1002 Bob EE

# Student Login
student login 1001

# Sending Friend Request
student friend_request 1002

# Adding Course Grades
grade_sheet add 202201 234123 3.5 85
grade_sheet add 202202 234124 4.0 92

# Logging Out
student logout

# Login as Bob
student login 1002

# Accepting Friend Request
student handle_request 1001 accept

# Printing Full Grade Sheet
report full

# Logging Out
student logout

2. Expected Output (output.txt)

Student 1002 - Bob
Friends:
- 1001 Alice
Grades:
- Semester 202201, Course 234123, Points 3.5, Grade 85
- Semester 202202, Course 234124, Points 4.0, Grade 92

Project Structure
File	Description
main.c	Manages files, reads input lines, and directs the system flow.
course_manager.c	Implements the logic for students, friends, courses, and reports.
ex3.c	Utility functions, error handling, and message printing.
course_manager.h	Declarations for course manager functions and structures.
ex3.h	Declarations for error codes and utility functions.
Notes

    If an invalid command or format is detected, an appropriate error message is printed.

    If memory allocation fails, the system exits gracefully with an error.

    Closing files and freeing memory are properly handled to prevent leaks.

🚀 Ready to Manage Courses Like a Pro!
