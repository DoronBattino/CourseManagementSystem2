#ifndef COURSE_H
#define COURSE_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "Semester.h"
#include "GradeSheet.h"
#include "Grade.h"
#include "list.h"
#include "set.h"

/**
 * Course list container type
 * implemented as a list using the functions according to list.h
 * generic functions.
*/

/** type for defining the list of Courses */

typedef struct course *Course;

/** Type used for returning error codes from list functions */

typedef enum CourseResult {
    CORUSE_ILLEGAL_ARGUMENT,
    COURSE_SUCCESS,
    COURSE_NULL_ARGUMENT,
    COURSE_OUT_OF_MEMORY,
    COURSE_INVALID_CURRENT,
} CourseResult;

/** Creates a new grade with the giving parameters
 *
@param points - string with number of points of the course we create.
 *        course_id - the id of the course we're creating.
 *        Grades - the list of grades of the course we're creating.
 *        result - a pointer to a place we will put the right result error.
   @return NULL - in any case of error we return NULL, the right error result
    will be put inside result.
           COURSE_NULL_ARGUMENT - one of the parmaters of the func is pointing
            to NULL
           COURSE_ILLEGAL_ARGUMENT - the points paramater is not from the right
            pattern (which defined in the excersice)
 */

ListElement createCourse(char* points, int course_id, List Grades,
		CourseResult* result);

/** function in charge of dynamically copying a giving course (will do the
 * casting from ListElement to course
 * withing the function) with copying all its list of grades as well.
 * * @return
 * if the copying fails from any memory reason return NULL
 * other wise return ListElement pointer.
*/

ListElement copyCourse(ListElement course);

/** compare fuction comparing between two courses according to their course_id
 *  in a set.
 *
 * @param course - the first course
 * @param course_two - second course
 * @param key - dummy paramater dosent have any influence
 * @return 1 - the first course's id is greater
 *         0 - their ids are equal.
 *         -1 - the second course's id is greater than the first one's.
 */

int compareCourses(SetElement course,SetElement course_two);


/** compare fuction comparing between two courses according to their course_id
 * in a list.
 *
 * @param course - the first course
 * @param course_two - second course
 * @param key - dummy paramater dosent have any influence
 * @return 1 - the first course's id is greater
 *         0 - their ids are equal.
 *         -1 - the second course's id is greater than the first one's.
 */
int compareCoursesInList(ListElement course,ListElement course_two,ListSortKey
		key);

/**Gets the course ID
 * @param Course- the course to take ID from*/
int getCourseID(Course);

/**Gets the course grades list
 * @param Course- the course to take the list from*/
List getGradesList(Course);



/** function in charge of checking the points number of a course is in the right
 * pattern */

bool checkLegalPointNumber(char* points);

/** check if the id of a course is legal **/

bool checkCourseId(int course_id);


/** this function checks for the latest appreance of a course with the given
 * course id in the given courses list.
 *
 * @param courses - the list of courses we check
 * @param course_id - the given course id we want to check if exists
 * @return NULL - if there isnt any course in the list with given course_id
 *         pointer to the course with the given course id, with the latest
 *          appreance in the list.
 */


/** function checking for the last appearance of a course matching the given
 * course id out of the given course list.
 *
 * @param courses - the list of courses we check the last appearance of the course in.
 * @param course_id - the id of the course we want to check his las appearance
 * @return NULL - none of the courses in the list has a matching id as the given course id.
 *         pointer to the last appearance of the matching course from the given course list.
 */

Course checkForLatestIdAppearence(List courses, int course_id);

/** function doing exactly the same thing as the above one, the only diffrence
 * it recives a pointer to the course
 * itself and not the actual course id.
 * @param courses -the list of courses we check the last appearance of the
 * course in.
 * @param course - the course we're checking his last appearance in the given
 *  list
 * @return NULL - we didnt found the course in the list.
 *          pointer to the last place in the list that the course appear.
 */

Course checkForLatestCourseApperance(List courses, Course course);

/** funtion getting a pointer to a course and returning his number of points as
 *  an int
 * @param course - the course we want to get his number of points
 * @return int, the number of points of the course.
 */

int returnNumberOfPoints(Course course);

/** function returning the effective grade of a course (the last grade from his
 *  grade's list.)
 * @param course - the course we want his effective grade
 * @return the course's last grade (as an int).
 */

int returnEffectiveGradeOfCourse(Course course);

/** function in charge of creating a course with the giving details and adding
 *  it to a given course list, as the last course
 * @param points- number of points of the course we create and add
 *        course_id - the id number of the course we add and create
 *        courses - the list of courses we add the course to
 *        grade - the grade we put in the grade list of the course we create
 * @return pointer to the new created and added course if it succeed
 *         NULL - the course has not been created and added succssfully
 *
 */

CourseResult addCourse(List courses, int course_id, char* points, int grade);

/** function in charge of freeing all the memory related of a giving Course
 *  element **/

void freeCourse(ListElement course);

/** this function recives a course and returning it's course_i
 * @param course - the course we want his id.
 * @return the given course's id.
 */

int returnCourseId(Course course);

/** function responsible of removing the last grade of the course with the
 *  matching course id as the given id.
 *
 * @param courses - the list of courses we have
 * @param course_id - the id of the course we want to remove the last grade
 *  from.
 * @return - 2 - we've removed the course.
 * 			1- we've removed the course's last grade
 *          0 - the course doesnt have any grade in it.
 */
int removeCourseFromList(List courses, int course_id);

/** fuction responsible of updating the last grade of the course with the
 *  matching course id as the given course id
 * @param courses - the list of courses we have
 * @param course_id - the id of the course we want to update his last grade.
 * @param new_grade - the grade we will put as the new last grade of the course.
 * @return true - we've updated the course last grade.
 *           false - the course doesnt have any grade in it.
 */

bool updateCourseInList(List courses, int course_id, int new_grade);


/** fuction responsible of updating the last grade of the given course
 * @param course - the list of course we have
 * @param new_grade - the grade we will put as the new last grade of the course.
 * @return true - we've updated the course last grade.
 *           false - the course doesnt have any grade in it.
 */


bool updateCourse(Course course, int new_grade);



/** this function gets a string of points and return it as the vaule of the
 * string as an long it multiplie by 2
 * (such as point_x2)
 * @param points - the string of points
 * @return number- vaule of points multiplie by 2.
 */

long int pointsToNumer(char* points);

/** this function gets a list of courses and prints  all the grades of each
 *  course from the list from last grade to the
 * first grade, from the last course in the list to the first course in the
 *  list using the printing functions given
 * in mtm_ex3 (printing in the format of those functions)
 * @param courses - lis of courses
 * @param output_channel - the file it should print the course grades to.
 */

void printCourseGradesFromLastToFirst(List courses, FILE* output_channel);

void printCourseGradesFromFirstToLast(List courses, FILE* output_channel);

/** this function gets a list of courses and prints  all the grades of each
 * course from the list from the first grade to the
 * last grade, from the first in the list to the last course in the list using
 *  the printing functions given
 * in mtm_ex3 (printing in the format of those functions)
 * @param courses - lis of courses
 * @param output_channel - the file it should print the course grades to.
 */

void printCleanSheetGradesFromFirstTolast(List courses, FILE* output_channel);

/** this function resposible of returning how many points a student took in a
 *  semester by counting all the points
 * of the courses with grades from the given list.
 * @param courses - the list of courses we're counting the points from.
 * @return - the number of total points taken in the semester (list of courses)
 *  multipie by two.
 */

int numberOfTotalPoints(List courses);

/** this function resposible of returning how many failed points a student have
 *  in a semester by counting all the points
 * of the courses with failed grades (below 55) from the given list.
 * @param courses - the list of courses we're counting the points from.
 * @return - the number of total failed points taken in the semester (list of
 *  courses) multipie by two.
 * */

int numberOfFailedPoints(List courses);


/** this function resposible of returning how many  effective points a student
 * have in a semester by counting all the points
 * of the courses with grades from the given list, but referring only to the
 * last grade of each course, which means
 * we dont count anycours twice and the last grade determine the actual result
 *  (failure or not).
 * @param courses - the list of courses we're counting the points from.
 * @return - the number of total effective points taken in the semester
 * (list of courses) multipie by two.
*/
int numberOfEffectivePoints(List courses);


/** this function responsible of returning the effective grade sum of a student
 *   a semester by multipling the effective
 *  grade of the courses (the last grade of the course in the semester) with the
 *   number of points of the course.
 *  we will do it for each course in the list and sum it all together.
 * @param courses - the list of courses we're counting the effective grade sum
 *  from.
 * @return - the total effective grade sum  in the semester (list of courses)
 *  multipie by two.
*/
int effectiveGradeSum(List courses);

/** this function getting a set of courses the gradeSheet contains and caculates
 *  the effective points in the set
 * @param courses - the set of courses we're caculating the effective points of
 *  it.
 * @return the number of effective points in the set.
 */

int caculatesEffectivePointsInNonSportCourseSet(Set courses);//TODO


/** this function getting a list of courses the gradeSheet contains and
 *  caculates the effective points of all the courses
 * in the list.
 * @param courses - the set of courses we're caculating the effective points of
 * it.
 * @return the number of effective points in the set.
 */


int caculatesEffectivePointsInSportCourseList(List courses);//TODO

/** this function getting a set of courses the gradeSheet contains and caculates
 *  the effective grades sum
 * of all the courses in the set.
 * @param courses - the set of courses we're caculating the effective grade sum
 *  of it.
 * @return the effective grade sum of the set.
 */


int caculatesEffectiveGradeSumInNonSportCourseSet(Set courses);//TODO

/** this function getting a list of courses the gradeSheet contains and
 * caculates the effective grades sum
 * of all the courses in the list
 * @param courses - the set of courses we're caculating the effective grade sum
 *  of it.
 * @return the effective grade sum of the set.
 */

int caculatesEffectiveGradeSumInSportCourseList(List sport_courses);//TODO



/** this function is checking if a course is a sport course or not according to
 *  the course's course id.
 (between 390000 to 399999 include == sport, other wise no).
 * @param course - the course we're checking
 * @return true - the course is a sport course.
 *         false - the course is not a sport course.
 */

bool checksIfASportCourse(Course course);


#endif /* COURSE_H_ */
