#ifndef SEMESTER_H_
#define SEMESTER_H_
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "GradeSheet.h"
#include "Course.h"
#include "Grade.h"
#include "ex3.h"
#include "list.h"
#include "set.h"
/**
 * Semesters list container type
 * implemented as a list using the functions according to list.h generic
 * functions.
*/

/** type for defining the list of Semesters */

typedef struct semester *Semester;

/* forward declaration */
typedef struct course *Course;


/** Type used for returning error codes from list functions */

typedef enum SemesterResult {
    SEMESTER_ILLEGAL_ARGUMENT,
    SEMESTER_SUCCESS,
    SEMESTER_NULL_ARGUMENT,
    SEMESTER_OUT_OF_MEMORY,
    SEMESTER_INVALID_CURRENT,
} SemesterResult;

/** Creates a new semester with the giving parameters
 *
@param points - string with number of points of the course we create.
 *        number - the number of the semester we're creating.
 *        courses - the list of courses of the semester we're creating.
 *
   @return NULL - in any case of error we return NULL, the right error result
    will be put inside result.
           SEMESTER_NULL_ARGUMENT - one of the parmaters of the func is
            pointing to NULL
           SEMESTER_ILLEGAL_ARGUMENT - the number paramater is not a positive
            number (which defined in the excersice)
 */

Semester createSemester( int number, List Courses, SemesterResult* result);

/** function in charge of dynamically copying a giving semester (will do the
 *  casting from ListElement to course
 * withing the function) with copying all its list of courses as well.
 * * @return
 * if the copying fails from any memory reason return NULL
 * other wise return ListElement pointer.
*/


/**Gets the course list of the semester
 * @param Semester- the semester to get its course list*/
List getCourseList(Semester);

/**Gets the semester number*/
int getSemesterNumber(Semester);


ListElement copySemester(ListElement semester);


/** compare fuction comparing between two semesters according to their number
 *
 * @param semester - the first semester
 * @param semester_two - second semester
 * @param key - dummy paramater dosent have any influence
 * @return 1 - the first semester's number is greater
 *         0 - their number are equal.
 *         -1 - the second semester number is greater than the first one's.
 */

int compareSemesters(ListElement semester,ListElement semester_two,
		ListSortKey key);


/** function in charge of freeing all the memory related of a giving semester
 *  element **/

void freeSemester(ListElement semester);

/** function that creates a course with the given paramaters
 * (related to course) and adds it as the last course
 * of the semester with the matching number as semester_num, from the given
 *  semesters list.
 * @param semesters - list of semesters
 * @param semester_number - the number of the semester we want to add the
 *  course to
 * @param course_id - the id of the course we create and add
 * @param points - number of points of the course we're creating and adding.
 * @param grade - the grade of the course we create and add.
 * @return true- the course has been successfully created and added as the
 *  last course of the semester.
 *          false - the course hasent been successfully created and added.
 */

bool addCourseToSemester(List semesters, int semester_number, int course_id,
		char* points, int grade);

/** fuction that removes the last grade from the course with course_id that is
 *  given, from the semester with the matching
 * semester number to the one thats given from the semester's list.
 * @param Semesters - list of semesters
 * @param semester_num - the number of the semester we want to find from the
 * semester list
 * @param course_id - the id of the course, from the semester we found, we want
 *  to remove the last grade from.
 * @return true - we've successfully removed the course.
 *         false - the course dosent have any grade in it.
 */

bool removeCoursefromSemester(List Semesters, int semester_num, int course_id);


/** fuction that updates the last grade from the course with course_id that is
 *  given in the first semester
 * that the course we want to update has a grade in it, from the semester's
 *  list.
 * @param Semesters - list of semesters
 * @param course_id - the id of the course we want to update his last grade
 * @return true - we've successfully updated the last grade from the course.
 *         false - we didn't found any semester where the course with the same
 *          id as course_id has grade in it.
 */


bool updateCourseInSemester(List Semesters, int course_id, int new_grade);

/* thois function is finding if a given course with the given course id is in the
 * given semester list
 * @param semesters- list of semesters
 * @param course_id - the id of the course we want to find if exists
 * return true - the course exists
 * 		  false - the course dosent exists
 */

bool FindIfCourseInSemester(List Semesters, int course_id);

/** this function returs a pointer to the course list of a given semester
 * @param semester - the semester we want it's courses's list.
 * @return a pointer to the courses's list.
 */

List returnCourseList(Semester semester);

/** this function returns the semester number of a given semester
 * @param semester - the semester we want it's number
 * @return - the number of the given semeseter.
 */

int returnSemeserNumber(Semester semester);

/** fuction that prints all the grades of the given semester.
 *
 * @param Semesters - the semester we're going to print it's grades.
 * @param output_channel - the file we will print the grads into.
 */

void printGradesOfSemester(Semester semester, FILE* output_channel);

/** this function responsible for printing a semester summary of the given
 *  semester with the printing function
 * called mtmPrintSummary.
 * @param semester - the semester we're printing his summary
 * @param output_channel - the file we're going to pring the summary to.
 */

void printSemesterSummary(Semester semester, FILE* output_channel);


/** this function is responsible of checking the last apperance of course with
 *  a grade in a list of semesters,
 * the apperance that will apply for the gradesheet.
 * if the course is a sport course the function will return the latest
 *  appearance of the course in the first semester
 * the course has grade in it.
 * if the course is not a sport course the function will return a pointer to
 *  the latest appearance of the course
 * in all the semesters.
 * @param Semesters - list of semesters with all the courses and grades of a
 *  student.
 * @param course - the course we're checking his last appearance in the given
 *  list.
 * @return - a pointer to the last appearance of the course from the given
 * list if exists, NULL if it dosent exists
 *           in a case of non sport course.
 *           in a case of sport course the function will return a pointer to
 *            the last appearance of the course
 *           in the first semester it appearce on.
 */

Course checkForLatestGradeSheetApperance(List Semesters,Course course);


/** this function is responsible of checking the last apperance of course with
 *  a grade in a list of semesters,
 * the apperance that will apply for the gradesheet, after it finds it it
 *  return the number of semester the course
 * appears at.
 * if the course is a sport course the function will return the number of the
 *  first semester the course appears in.
 * if the course is not a sport course the function will return the number
 *  of the last semester the course appears in.

 * @param Semesters - list of semesters with all the courses and grades of a
 *  student.
 * @param course - the course we're checking his last appearance in the
 *  given list.
 * @return -  the number of the last semester the course appears in (in case
 *  of non sport course)
 *            the number of the first semester the course appears in (in case
 *             of sport course).
 *            0 - if the course dosent exist in the list at all.
 */

int checkForLatestSemesterNumber(List Semesters, Course course);

/*** this function is responsible for adding all the courses that apply for a
 *  given gradesheet from a given list of semesters.
 * @param Semesters - the list of semesters we want to add the courses from.
 * @param gradesheet - the grade sheet we want to add the courses to.
 */

void addRelevantCoursesToGradeSheet(List Semesters,GradeSheet gradesheet);


/** this function prints a grade sheet summary of the given list of courses
 *  with the printing function mtmPrintSummary
 *
 * @param semesters - the list of semesters which the grade sheet is
 *  created from
 * @param output_channel - the ouput to where we're going to print the
 *  summary to.
 */

void printGradeSheetSummary(List semesters,FILE* output_channel);

/** this function prints a clean grade sheet summary of the given list of
 *  courses with the printing function mtmPrintCleanSummary
 *
 * @param semesters - the list of semesters which the grade sheet is
 *  created from
 * @param output_channel - the ouput to where we're going to print
 *  the summary to.
 */


void printGradeSheetCleanSummary(List semesters, FILE* output_channel);



/** this function prints all the grades from the given semester list that
 *  applys for a clean grade sheet, into the
 * given output channel.
 * @param semesters - the list of semesters we're printing the grades from.
 * @param output_channel - the file to which we're going to print the grades to.
 */

void printStudentCleanGradesAndInfo(List semesters, FILE* output_channel);

/** this function will print the highest grades from the given semester list
 *  into the given output_channel, using mtm print
 * the amount of grades that will be printed will be as the given amount
 *  parameter.
 * @param amount - the maount of grades we gonna print
 * @param Semesters - the list of semesters we're printing its highest
 * course grades.
 * @param output_channel - a pointer to the file to which we gonna print the
 *  grades
 */

void printHighestGradesFromList(int amount,List Semesters,FILE* output_channel);

/** this function will print the highest grades from the given semester list
 *  into the given output_channel, using mtm print
 * the amount of grades that will be printed will be as the given amount
 *  parameter.
 * @param amount - the maount of grades we gonna print
 * @param Semesters - thelist of semesters we're printing its highest course
 *  grades.
 * @param output_channel - a pointer to the file to which we gonna print the
 *  grades
 */



void printLowestGradesFromList(int amount,List semesters, FILE* output_channel);


#endif /*SEMESTER_H_*/
