#ifndef EX3_H_
#define EX3_H_

// Updates:
// 02.12.2017: an example in the comments of ex3PrintSemesterInfo was fixed.
// 22.12.2017: reordered the values in EX3ErrorCode, and removed the unused MTM_FILE_ERROR.

#include <stdio.h> // For FILE*
// You should avoid including unnecessary header files
#include <stdbool.h>

/**
* Maximal input line length
*/
#define MAX_LEN 120

/**
* This type defines all errors for the system.
* These codes should be used for calling ex3PrintErrorMessage to report
* error messages.
*
* Notice that after calling ex3PrintErrorMessage with one of the first
* three messages you should abort the program according to the exercise
* rules.
*/
typedef enum {
	EX3_OUT_OF_MEMORY, // You should exit program after this error
	EX3_INVALID_COMMAND_LINE_PARAMETERS, // You should exit the program after this error
	EX3_CANNOT_OPEN_FILE, // You should exit program after this error
	EX3_NOT_LOGGED_IN = 4,
	EX3_ALREADY_LOGGED_IN,
	EX3_STUDENT_DOES_NOT_EXIST,
	EX3_STUDENT_ALREADY_EXISTS,
	EX3_NOT_FRIEND,
	EX3_ALREADY_FRIEND,
	EX3_NOT_REQUESTED,
	EX3_ALREADY_REQUESTED,
	EX3_COURSE_DOES_NOT_EXIST = 13,
	EX3_INVALID_PARAMETERS = 3
} EX3ErrorCode;

/**
* ex3PrintErrorMessage - Prints an error message into the given output channel.
*     Use the standard error channel to print error messages.
*
* @param error_channel - File descriptor for the error channel.
* @param code - Error code to print message for.
*/
void ex3PrintErrorMessage(FILE* error_channel, EX3ErrorCode code);

/**
* ex3PrintStudentName - Prints student's name.
*
* @param output_channel - File descriptor for the output channel.
* @param first_name - The student's first name.
* @param last_name - The student's last name.
*/
void ex3PrintStudentName(FILE* output_channel, const char* first_name,
	const char* last_name);

/**
* ex3PrintStudentInfo - Prints student details.
*
* @param output_channel - File descriptor for the output channel.
* @param id - The student's id.
* @param first_name - The student's first name.
* @param last_name - The student's last name.
*/
void ex3PrintStudentInfo(FILE* output_channel, int id, const char* first_name,
	const char* last_name);

/**
* ex3PrintGradeInfo - Prints grade details.
*
* @param output_channel - File descriptor for the output channel.
* @param course_id - The course id.
* @param points_x2 - The number of course points, multiplied by 2. For example,
*     if "Physics 1m" is 3.5 points, pass 7.
* @param grade - The course grade.
*/
void ex3PrintGradeInfo(FILE* output_channel, int course_id, int points_x2,
	int grade);

/**
* ex3PrintSemesterInfo - Prints a line containing semester details.
*
* @param output_channel - File descriptor for the output channel.
* @param semester - The semester number.
* @param total_points_x2 - The number of total course points, multiplied by 2.
*     Courses taken multiple times are counted multiple times.
* @param failed_points_x2 - The number of failed course points, multiplied by 2.
*     A failed course is a course with a grade lower than 55. Courses failed
*     multiple times are counted multiple times.
* @param effective_points_x2 - The number of total effective course points,
*     multiplied by 2. Effective points are points of courses whose grade counts.
*     A grade doesn't count if another grade of the same course id appears later
*     in the semester.
* @param effective_grade_sum_x2 - The sum of the effective course grades, when
*     each grade is multiplied by the number of course points, multiplied by 2.
*
* For example, for the following semester:
*     Course: 234122, points: 3.0, grade: 51
*     Course: 114071, points: 3.5, grade: 75
*     Course: 234122, points: 3.0, grade: 90
* The parameters are:
*     total_points_x2 = (3.0+3.5+3.0)*2 = 19
*     failed_points_x2 = 3.0*2 = 6
*     effective_points_x2 = (3.5+3.0)*2 = 13
*     effective_grade_sum_x2 = (3.5*75+3.0*90)*2 = 1065
*/
void ex3PrintSemesterInfo(FILE* output_channel, int semester,
	int total_points_x2, int failed_points_x2, int effective_points_x2,
	int effective_grade_sum_x2);

/**
* ex3PrintSummary - Prints the summary of all the grade sheet.
*     The parameters are similar to the ones of ex3PrintSemesterInfo,
*     but the sums are not limited to a single semester.
*
* @param output_channel - File descriptor for the output channel.
* @param total_points_x2 - The number of total course points, multiplied by 2.
*     Courses taken multiple times are counted multiple times.
* @param failed_points_x2 - The number of failed course points, multiplied by 2.
*     A failed course is a course with a grade lower than 55. Courses failed
*     multiple times are counted multiple times.
* @param effective_points_x2 - The number of total effective course points,
*     multiplied by 2. Effective points are points of courses whose grade counts.
*     A grade doesn't count if another grade of the same course id appears later
*     in the grade sheet. Sport courses are an exception (course id 39xxxx): a
*     sport grade doesn't count only if another grade of the same course id
*     appears later in the same semester (not the whole grade sheet).
* @param effective_grade_sum_x2 - The sum of the effective course grades, when
*     each grade is multiplied by the number of course points, multiplied by 2.
*/
void ex3PrintSummary(FILE* output_channel, int total_points_x2,
	int failed_points_x2, int effective_points_x2, int effective_grade_sum_x2);

/**
* ex3PrintCleanSummary - Prints the summary of all the grade sheet.
*     Just like ex3PrintSummary, but without the parameters to calculate
*     the amount of failed grades - they don't appear in the clean sheet.
*
* @param output_channel - File descriptor for the output channel.
* @param effective_points_x2 - The number of total effective course points,
*     multiplied by 2. Effective points are points of courses whose grade counts.
*     A grade doesn't count if another grade of the same course id appears later
*     in the grade sheet. Sport courses are an exception (course id 39xxxx): a
*     sport grade doesn't count only if another grade of the same course id
*     appears later in the same semester (not the whole grade sheet).
* @param effective_grade_sum_x2 - The sum of the effective course grades, when
*     each grade is multiplied by the number of course points, multiplied by 2.
*/
void ex3PrintCleanSummary(FILE* output_channel, int effective_points_x2,
	int effective_grade_sum_x2);

/**
* ex3FacultyResponse - Prints a response to a faculty request.
*
* @param output_channel - File descriptor for the output channel.
* @param response - The response.
*/
void ex3FacultyResponse(FILE* output_channel, const char* response);

#endif /* MTM_EX3_H_ */
