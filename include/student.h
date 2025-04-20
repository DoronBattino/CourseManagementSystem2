#ifndef STUDENT_H_
#define STUDENT_H_

#include <stdbool.h>
#include "friend.h"
#include "set.h"
#include "Grade.h"
#include "Course.h"
#include "Semester.h"
#include "list.h"
#define MAX_ID 1000000000

/*Type for defining the student*/
typedef struct student_t *Student;


/**Error codes for student*/
typedef enum{
    STUDENT_INVALID_ID,
    STUDENT_NULL_ARGUMENT,
    STUDENT_MEMMORY_ERROR,
    STUDENT_NOT_A_FRIEND,
    STUDENT_SUCCESS
}StudentResult;

/*Gets student ID*/
int getID(Student);

/**Gets student first name
 * @param Student- the student
 * @return
 * string of the first name*/
char* getFirstName(Student);

/**Gets student last name
 * @param Student- the student
 * @return
 * string of the last name*/
char* getLastName(Student);

/**Gets the student semester list
 * @param Student- the student*/
List getSemesterList(Student);

/**Gets the student by his ID
 * @param set- the set to search in.
 * @param ID- the ID of the requested student.
 * @return
 * NULL if not found or the student in case of success.*/
Student getStudentByID(Set set, int ID);

/**Gets the friends of the student*/
FriendsSet getFriends(Student);

/**Copy a student for the set*/
SetElement copyStudent(SetElement);

/**Compare students for the set*/
int compareStudent(SetElement, SetElement);

/**Creates a new student
 * @param ID - the ID of the new student (9 digits only).
 * @param first_name - for student first name.
 * @param last_name - for student last name.
 * @return
 * NULL if there is an error or the new student in case of success*/
Student createStudent(int ID, char* first_name, char* last_name,
                      StudentResult *result);

/**Gets the student's friend request set
 * @param student the relevant student*/
Set getFriendRequestSet(Student);

/**Removes a student from being a friend
 * @param Student- the remover.
 * @param Student- the student who needs to be removed
 * @return
 * STUDENT_NULL_ARGUMENT if a null was sent.
 * STUDENT_NOT_EXISTE if there is no one to remove
 * STUDENT_SUCCESS in case of removing successfully*/
StudentResult unfriend(Student, Student);

/**Deallocates student
 * @param student - the student to be removed*/
void studentDestroy(SetElement);

/** function that creates a course with the given paramaters (related to course) and adds it as the last course
 * of the semester with the matching number as semester_num, from the given semesters list.
 * @param student - the student we add him the course
 * @param semester_number - the number of the semester we want to add the course to
 * @param course_id - the id of the course we create and add
 * @param points - number of points of the course we're creating and adding.
 * @param grade - the grade of the course we create and add.
 * @return true- the course has been successfully created and added as the last course of the semester.
 *          false - the course hasent been successfully created and added.
 *          */

Student addCourseToStudent(Student student, int semester_number, int course_id, char* points, int grade);



/** function that remove the last grade from the course with the course_id, in the semester with the
 * number as semester_num, from the given student .
 * @param student - the student we want to remove his last grade from the given course.
 * @param semester_num - the number of the semester we want to remove the course's last grade.
 * @param course_id - the id of the course we want to remove the last grade from.
 * @return true - the course's last grade has been successfully removed.
 *         false - the course dosent have any grade in it.
 */
bool removeGradeFromStudent(Student student, int semester_num, int course_id);

/** function that updates the last grade of the course with the course_id, in the first
 * semester this course has grade in it from the given semesters list the given student have.
 * @param student - the student we want to update his last grade from the given course.
 * @param course_id - the id of the course we want to remove the last grade from.
 * @return true - the course's last grade has been successfully updated.
 *         false - the course dosent have any grade in any of the student's semesters.
  **/

bool updateStudentCourseGrade(Student student,int course_id, int new_grade);


/** this function checks if the given student has a course with the given course id
 * @param student - the student we want to check if he did the course
 * @param course_id - the id of the course we want to see if the student has done.
 * return true - the student has done the given course
 * 		  false - the student hasent done the given course.
 */

bool findIfStudentHaveCourse(Student student, int course_id);


/** prints the student info with the given printStudentInfo function into the given file.
 * and than prints all the students grades from all his semesters into the file, after printing all
 * the grades from a given semester a semester summary will be printed with the mtmPrintSemesterSummary function,
 * after printing all the semester's grades and summarys a total grade sheet summary will be printed with the given
 * mtm printSummary function, this function will print the Full Grade sheet of a student
 * @param student - the student which we want to print his details and grades
 * @param output_channel - the file to where we want to print the details.
 */


void printStudentFullGradesAndInfo(Student student, FILE* output_channel);

/** prints the student info with the given printStudentInfo function into the given file.
 * and than prints all the students grades from all his semesters that apply for the grade sheet into the file
 * sorted by the course id of each course, courses with the same id will be sorted by the semester number which they belong.
  * @param student - the student which we want to print his details and grades
 * @param output_channel - the file to where we want to print the details.
 */


void printStudentCleanGradeSheet(Student student, FILE* output_channel);

/** this function prints the given student's highest grades, the amount of grades that will be printed into
 * the file pointed by output_channel will be as the given amout parameter
 * @param amount - the amount of grades that will be printed
 * @param student - the student that we will print his highetst grades
 * @param output_channel- a pointer to the file we gonna print the grades into
 */


void printStudentHighestGrades(int amount,Student student, FILE* output_channel);


/** this function prints the given student's lowest grades, the amount of grades that will be printed into
 * the file pointed by output_channel will be as the given amout parameter
 * @param amount - the amount of grades that will be printed
 * @param student - the student that we will print his lowest grades
 * @param output_channel- a pointer to the file we gonna print the grades into
 */


void printStudentLowestGrades(int amount,Student student, FILE* output_channel);

#endif /* STUDENT_H_ */
