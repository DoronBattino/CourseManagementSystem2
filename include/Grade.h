#ifndef GRADE_H_
#define GRADE_H_
#include <stdbool.h>
#include <stdio.h>
#include "list.h"
/**
 * Grade list container type
 * implemented as a list using the functions according to list.h generic
 *  functions.
*/
/** type for defining the list of grades */

typedef struct grade *Grade;

/** Type used for returning error codes from list functions */

typedef enum GradeResult {
    GRADE_ILLEGAL_GRADE,
    GRADE_SUCCESS,
    GRADE_NULL_ARGUMENT,
    GRADE_OUT_OF_MEMORY,
    GRADE_INVALID_CURRENT,
} GradeResult;

/** Creates a new grade with the giving int
 *
 * @param grade - the grade we will put in the grade we create
 *        result - pointer to a place in the memory we will put the right error
 *         result if there is one.
 * @return NULL - memory problem with allocation.
 *         GRADE_IILEGAL_GRADE - grade is not in the right value, the return
 *          value is NULL, result will contain the right error
 *         other wise pointer to the new created grade.
 */
Grade CreateGrade(int grade,GradeResult* result);

/** function in charge of dynamically copying a giving grade (will do the
 *  casting from ListElement to Grade
 * withing the function.
 * * @return
 * if the copying fails from any reason return NULL
 * other wise return ListElement pointer.
*/

ListElement copyGrade(ListElement Grade);

/** function in charge of freeing all the memory related of a giving Grade
 * element **/

void freeGrade(ListElement Grade);

/** compare between two grades
 *
 * @param one, two - both are grades.
 * @return 0 - grades are equal.
 *         1 - grade one is bigger.
 *         2 - grade two is bigger.
 */

int CompareGrades(Grade one, Grade two, GradeResult* result);

/** checks if a grade is legal **/

bool checkGrade(int Grade);

/**Gets the grade*/
int getGrade(Grade);

/** remove the last Grade from a grade's list
 *
 * @param Grades - the list of grades we want to remove the last grade from
 * @return true - the grade has been successfully removed
 *         false - the grades hasent been removed.
 */

int removeLastGrade(List Grades);

/** updates the last grade in the list to the given new grade
 * if the list is empty we return false.
 * @param Grades - the list of grades we want to update
 * @param new_grade - the new grade we want to put as the last grade.
 * @return 2 - the grade has been succssfully removed, and the no other grades
 *  for that course
 *         1 - the last grade of the course has been removed and we have
 *          another grade for that course.\
 *         0 - the grade hasent been succssesfully removed.
 */

bool updateLastGrade(List Grades, int new_grade);


/** prints list of grades from the last grade to the first of a course with
 *  the given details into the output_channel
 *
 * @param Grades - the list of grades of the course
 * @param output_channel - where it should be print to
 * @param course_id - the id of the course
 * @param points_x2 - the number of points of the course multiplie by 2
 */

void printGradeListFromLastToFirst(List Grades,FILE* output_channel,
		int course_id, int points_x2);


void printGradeListFromFirstToLast(List Grades,FILE* output_channel,
		int course_id, int points_x2);


/** checks if a grades is a pass grade or a failed grade (below 55= failed ,
 *  above 55 (include) = pass)
 *
 * @param grade - the grade we check
 * @return true - pass, false=fail.
 */

bool checkIfPassed(Grade grade);

/** function that counts the number of failed grades in a list of grades
 *
 * @param Grades - the list of grades we check
 * @return number of failed grades
 */

int countFaildGrades(List Grades);

/** this function takes get a list of grades and return the last grade (the
 *  effective one)
 *
 * @param Grades - the list of grades we take the last grade from.
 * @return the last grade from the list. (int)
 */

int getEffectiveGrade(List Grades);





#endif /* GRADE_H_ */
