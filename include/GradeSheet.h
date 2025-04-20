#ifndef GRADESHEET_H_
#define GRADESHEET_H_
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "Semester.h"
#include "Course.h"
#include "Grade.h"
#include "list.h"
#include "set.h"

/**
 * GradeSheet ADT, contains all the grades that apply for a gradeSheet of a
 *  sturdent as a list of sport_courses
 * and a set of non_sport_courses.
 * implemented as just a simple struct
*/
/** typedef of a pointer to the struct **/

typedef struct gradesheet *GradeSheet;

/* forward declaration */
typedef struct course *Course;


/** a simple struct for adding the semester number to a course, contains all
 *  the course details as Course struct
 * and added int number, represents the number of the semester the course was
 *  taken.
 * typedef of a pointer to the struct
 * */

typedef struct course_with_number *CourseWithNumber;

/** Type used for returning error codes from list functions */

typedef enum GradeSheetResult {
    GRADESHEET_ILLEGAL_ARGUMENT,
    GRADESHEET_SUCCESS,
    GRADESHEET_NULL_ARGUMENT,
    GRADESHEET_OUT_OF_MEMORY,
    GRADESHEET_INVALID_CURRENT,
    GRADESHEET_GRADE_EXISTS_ALREADY,
} GradeSheetResult;

 /** function in charge of dynamically copying a giving grade sheet (will do
  *  the casting from ListElement to gradesheet
 * withing the function) with copying all its list of courses as well.
 * * @return
 * if the copying fails from any memory reason return NULL
 * other wise return ListElement pointer.
*/

ListElement copyGradeSheet(ListElement gradesheet);

/** Creates a new gradesheet with the giving parameters
 *
@param Set non_spot_courses - a set of non sport courses (Courses with Number)
 *        sport_courses - the list of sport courses of the grade sheet
 *        (Courses with Number).
 *        result - a pointer to a space that will contain the errors if we
 *         occured in such.
   @return NULL - in any case of error we return NULL, the right error result
    will be put inside result.
           GRADESHEET_NULL_ARGUMENT - one of the parmaters of the func is
            pointing to NULL
           GRADESHEET_OUT_OF_MEMORY - one of the allocations has failed
 */

GradeSheet createGradeSheet(Set non_sport_courses,List sport_courses,
		GradeSheetResult* result);

/** this function is creating a copy course_With_number, with the given
 *  details of the given course
 * and returning a pointer to the new created course_with_number (a casting
 * is done within the function).
 * @param course - the course with number we want his details for our new
 * created course.
 * @return - NULL - if any error occurred
 *           pointer to the new created course_with_number if we've succeseed.
 */

ListElement copyCourseWithNumber(ListElement course_with_number);

/** this function caculating the Effective grade sum of all the courses in a
 * grade sheet
 * @param gradesheet - the grade sheet we caculate its effective grade sum
 * @return - the effective grade sum (as an int)
 */

int caculatesEffectiveGradeSumInGradeSheet(GradeSheet gradesheet);

/** this function caculating the sum of all the points of all the courses in a
 *  grade sheet
 * @param gradesheet - the grade sheet we caculate its points
 * @return - the sum of all the points (as an int)
 */

int caculatesPointsInGradeSheet(GradeSheet gradesheet);


/** this function responsible of freeing all memory related to a given grade
 * sheet
 * @param gradesheet - the gradesheet we're freeing all its memory
 */

void freeGradeSheet(GradeSheet gradesheet);

/** this function creating a Course with  semester number (as the struct
 * course_with_number), with the
 * given course details and the given semester number.
 * @param course - the course we're taking its details for the course with
 *  number we're creating.
 * @param semeter_number - the semester number our new course will contain.
 * @return - a pointer to the new course with number we created, NULL in case
 *  we've failed from any reason.
 */

CourseWithNumber createCourseWithNumber(Course course, int semeter_number);

/** this function returns a pointer to  the first course with number in the
 *  sport_course list insde the grade sheet
 * @param gradesheet - the grade sheet we're returning the course from.
 * @return - a pointer to the first course in the sport_course list.
 */

CourseWithNumber returnSportCourseFromGradeSheet(GradeSheet gradesheet);

/** this function returns a pointer to  the first course with number in the
 *  non_sport_course set insde the grade sheet
 * @param gradesheet - the grade sheet we're returning the course from.
 * @return - a pointer to the first course in the non_sport_course set.
 */


Course returnNonSportCourseFromGradeSheet(GradeSheet gradesheet);

/** this function sorting the list of sport courses by the courses's
 *  course id(from the higher course_id
 * to the lower one, if the course's id is equal it will sort by their
 * semester number (from lowest semester number to the highest).
 * it creates a new list and move all the courses in the non_sport_courses
 *  set to that list, than
 * it sorts that new list also by the same method and returns a pointer to
 *  that list.
 * @param gradesheet- the gradesheet we're sorting.
 * @return - a pointer to the new created sorted list.
 */

List sortGradeSheetByCourseId(GradeSheet gradesheet);

/** this function sorting the list of sport courses by the courses's grades
 * (from the higher grade
 * to the lower one, if they're equal it will sort by the semester number,
 *  if they're equal as well it will sort by the course_id.
 * it creates a new list and move all the courses in the non_sport_courses set
 *  to that list, than
 * it sorts that new list also by the same method and returns a pointer to
 *  that list.
 * @param gradesheet- the gradesheet we're sorting.
 * @return - a pointer to the new created sorted list.
 */

List sortGradeSheetByHighGrades(GradeSheet gradesheet);

/** this function sorting the list of sport courses by the courses's grades
 * (from thelower grade
 * to the highest one, if they're equal it will sort by the semester number,
 *  if they're equal as well it will sort by the course_id.
 * it creates a new list and move all the courses in the non_sport_courses set
 *  to that list, than
 * it sorts that new list also by the same method and returns a pointer to
 *  that list.
 * @param gradesheet- the gradesheet we're sorting.
 * @return - a pointer to the new created sorted list.
 */

List sortGradeSheetByLowerGrades(GradeSheet gradesheet);

/** this function will return a pointer to a gradesheet's sport_course list
 * @param gradesheet - the grade sheet we return the list from
 * @return - a pointer to the gradesheet's sport_course list.
 */

List returnSportList(GradeSheet gradesheet);

/** this function returns the semester number of a give CourseWithNumber course
 * @param course - the course we want his semester number.
 * @return - the courses's semester number as an int.
 */

int returnSemesterNumberOfCourseWithNumber(CourseWithNumber course);

/** this function returns the course_id of a give CourseWithNumber course
 * @param course - the course we want his id.
 * @return - the courses's id number as an int.
 */

int returnCourseIdofCourseWithNumber(CourseWithNumber course);

/** this function returns a pointer to the course field of a given
 * CourseWithNumber course
 * @param course - the course we want his course field.
 * @return - pointer to the courses's course field.
 */

Course returnCoursefromCourseWithNumber(CourseWithNumber course);

/** this function responsible of freing all the momory regarding to a given
 *  CourseWithNumber element
 * @param course - the course we want to free all his memory.
 */

void freeCourseWithNumber(ListElement course);

/** this function creating a new CourseWithNumber with the given course's
 * details and semester number
 * than it adds a copy of the new created course to the sport_course list
 *  in the given gradesheet (it frees the
 * memory of the created one after it add a copy of it to the list
 * @param gradesheet - the gradesheet we want to add the new course to
 * @param course - the course containing the details of the course we want
 *  to add
 * @param semester_number - the semester number of the course we want to add
 * @return -GRADESHEET_OUT_OF_MEMORY - if memory problem occurs while creating
 *  the new course
 *          GRADESHEET_SUCCSESS- we successfully added the course to the
 *           sport_courses list inside the given gradesheet
 */

GradeSheetResult addSportCourseToGradeSheet(GradeSheet gradesheet,
		Course course, int semester_number);

/** this function creating a new CourseWithNumber with the given course's
 * details and semester number
 * than it adds a copy of the new created course to the non_sport_course list
 * in the given gradesheet (it frees the
 * memory of the created one after it add a copy of it to the list
 * @param gradesheet - the gradesheet we want to add the new course to
 * @param course - the course containing the details of the course we want
 *  to add
 * @param semester_number - the semester number of the course we want to add
 * @return -GRADESHEET_OUT_OF_MEMORY - if memory problem occurs while creating
 * the new course
 *          GRADESHEET_GRADE_EXISTS_ALREADY- if we already have a course with
 *           the same course id inside the set.
 *          GRADESHEET_SUCCSESS- we successfully added the course to the
 *          sport_courses list inside the given gradesheet
 */

GradeSheetResult addNonSportToGradeSheet(GradeSheet gradesheet,Course course,
		int semester_number);

/** this function printing into the given output_channel the courses that apply
 *  for clean gradesheet (by course_id,
 * and if the course id is equal, by the semester number), using
 * mtmPrintGradesInfo function.
 * @param spot_list - the gradesheet's sport_courses list
 * @param non_sport_list - the gradesheet's non_sport_courses list.
 * @param output_channel - the file where we print the details to
 */

void printCleanSheetGradesFromGradeSheet(List spot_list,List non_sport_list,
		FILE* output_channel);

/** this function printing into the given output_channel the courses with the
 *  highest grades from the given
 * list and set (that creatrs a gradesheet), the number of courses that will
 *  be printed equal to the given amount paramater
 , using mtmPrintGradesInfo function.
 * @param spot_list - the gradesheet's sport_courses list
 * @param non_sport_list - the gradesheet's non_sport_courses list.
 * @param amount - the amount of courses we should print.
 * @param output_channel - the file where we print the details to
 */

void printHighestGradesFromGradeSheet(List sport_list,List non_sport_list,
		FILE* output_channel,int amount);

/** this function printing into the given output_channel the courses with the
 *  lowest grades from the given
 * list and set (that creatrs a gradesheet), the number of courses that will
 *  be printed equal to the given amount paramater
 , using mtmPrintGradesInfo function.
 * @param spot_list - the gradesheet's sport_courses list
 * @param non_sport_list - the gradesheet's non_sport_courses list.
 * @param amount - the amount of courses we should print.
 * @param output_channel - the file where we print the details to
 */


void printLowestGradesFromGradeSheet(List sport_list,List non_sport_list,
		FILE* output_channel,int amount);

/** this function recives a course_with_number and returning the course's
 *  grade that apply for gradesheet.
 * @param course - the course we want his apply grade.
 * @return - the apply for gradesheet grade (as an int).
 */

int returnApplyGradeOfCourseWithNumber(CourseWithNumber course);

/** this function compares courses with number by their course_id, if their
 *  course id is equal,
 * it will compare them by the semester number they were taken.
 * @param course_one - the first course
 * @param course_two - the secoud course
 * @param key - a dummy paramter, has no use.
 * @return - 1 - the first semester course_id is bigger (or in case their
 * course id is equal the first course's semester
 * number is lower).
 *          -1 - the second semester course_id is bigger (or in case their
 *           course id is equal the second courses's
 *          semester number is lower).
 */

int compareCoursesWithNumber(SetElement course_one,SetElement course_two,
		ListSortKey key);

/** this function compares courses with number by their grades, in case their
 *  grades are equal by their semester nuber,
 * and in case that is equal as well, it will compare them by their course_id.
 * @param course_one - the first course
 * @param course_two - the second course
 * @param key - dummy parameter, has no use.
 * @return 1 - the first course grade is higher (or in case their grades are
 *  equal his semester number is lower,
 * or in case its equal as well, his course_id number is lower.
 *        -1 - the second course grade is higher (or in case their grades are
 *         equal his semester number is lower,
 * or in case its equal as well, his course_id number is lower.
 */

int compareCoursesByHighGrades(ListElement course_one,ListElement course_two,
		ListSortKey key);

/** this function compares courses with number by their grades, in case their
 *  grades are equal by their semester nuber,
 * and in case that is equal as well, it will compare them by their course_id.
 * @param course_one - the first course
 * @param course_two - the second course
 * @param key - dummy parameter, has no use.
 * @return 1 - the first course grade is lower (or in case their grades are
 *  equal his semester number is lower,
 * or in case its equal as well, his course_id number is lower.
 *        -1 - the second course grade is lower (or in case their grades are
 *         equal his semester number is lower,
 * or in case its equal as well, his course_id number is lower.
 */


int compareCoursesByLowerGrades(ListElement course_one,ListElement course_two,
		ListSortKey key);


/** this function compares two set elements (they're courses with number) by
 *  their course_id
 * @param course_one - the first course
 * @param course_two - the second course
 * @return 1 - the first course's id is bigger
 *         -1 - the second courses's id is bigger.
 *         0 - the course id of the courses is euqal.
 */

int compareCoursesInSet(SetElement course_one,SetElement course_two);
void printgradeSheetCourseId(GradeSheet gradesheet);
#endif /* GRADESHEET_H_ */
