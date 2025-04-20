#ifndef COURSE_MANAGER_H_
#define COURSE_MANAGER_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "student.h"
#include "Semester.h"
#include "ex3.h"
#include "friend_request.h"


/**Defining a type for course manager.*/
typedef struct course_manager *CourseManager;

/**Defining error codes*/
typedef enum{
	CM_OUT_OF_MEMORY,
	CM_CANNOT_OPEN_FILE,
	CM_NOT_LOGGED_IN,
	CM_ALREADY_LOGGED_IN,
	CM_STUDENT_DOES_NOT_EXIST,
	CM_STUDENT_ALREADY_EXISTS,
	CM_NOT_FRIEND,
	CM_ALREADY_FRIEND,
	CM_NOT_REQUESTED,
	CM_ALREADY_REQUESTED,
	CM_COURSE_DOES_NOT_EXIST,
	CM_INVALID_PARAMETERS,
	CM_SUCCESS
}CMResult;

/**Creating a new system*/
CourseManager createCourseManager();

/**Gets the student set from the system*/
Set getStudentsSet(CourseManager);

/**Gets the student who logged in
 * @param CourseManager- the system to check*/
Student getLogin(CourseManager);

/**Adds a new student to the system
 * @param CourseManager- the system to add to.
 * @param ID- student's ID
 * @param first_name- student's first name
 * @param last_name- student's last name
 * @return
 * EX3_INVALID_PARAMETERS- if invalid ID or empty strings was sent
 * EX3_OUT_OF_MEMORY- if there is a memory problem.
 * EX3_STUDENT_ALREADY_EXISTS- if student already in the system.
 * EX3_SUCCESS- if student added successfully.*/
CMResult studentAdd(CourseManager,int, char*, char*);

/**Removes student from the system
 * @param ID- the ID of the student who needs to be removed
 * @param CourseManager- the system to remove from.
 * @return
 * EX3_INVALID_PARAMETERS- if invalid ID or a null system was sent.
 * EX3_STUDENT_DOES_NOT_EXISTS- if student not in the system.
 * EX3_SUCCESS- if student removed successfully. */
CMResult studentRemove(CourseManager, int);

/**Sends a friend request from one student to another
 * @param CourseManager- the system witch the students belong to.
 * @param int- the sender ID.
 * @param int- the receiver ID.
 * @return
 * EX3_INVALID_PARAMETERS- if a null was sent.
 * EX3_NOT_LOGGED_IN- if the sender is not logged in.
 * EX3_STUDENT_DOES_NOT_EXISTS- if the receiver not in the system
 * EX3_ALREADY_FRIEND- is the receiver and the sender already friends.
 * EX3_ALREADY_REQUESTED- if the receiver already have a request from sender.*/
CMResult studentSendFriendRequest(CourseManager,int,int);

/**Handle a friend request.
 * @param CourseManager- the system.
 * @param receiver- the student who needs to answer the request.
 * @param senderID- the ID of the student who sent the request.
 * @param answer- the answer to the request.
 * @return
 * EX3_NOT_LOGGED_IN- if no student logged in to the system.
 * EX3_STUDENT_DOES_NOT_EXISTS- if the sender does not in the system.
 * EX3_ALREADY_FRIEND- if receiver and sender are already friends.
 * EX3_NOT_REQUESTED- if no such request.
 * EX3_INVALID_PARAMETERS- if answer is illegal.*/
CMResult studentHandleRequest(CourseManager,int receiver,int sender,
		char*);

/**Removes a student from being a friend
 * @param CourseManager- the system.
 * @param Student- the remover.
 * @param ID- ID of student to be removed as a friend.
 * @return
 * EX3_NOT_LOGGED_IN- if no student is logged in to the system.
 * EX3_STUDENT_DOES_NOT_EXISTS- if the student to be removed not exist in the
 * system.
 * EX3_NOT_FRIEND- the student to be removed is not a friend or the remover
 * tries to unfriend him self.*/
CMResult studentUnfriend(CourseManager, int, int ID);

/**Log a student by his ID
 * @param CourseManager- the system to log in to
 * @param ID- the ID of the student who wants to log in
 * @return
 * EX3_ALREADY_LOGGED_IN- if the student already logged.
 * EX3_STUDENT_DOES_NOT_EXSISTS- if the student not in the system.*/
CMResult studentLogin(CourseManager,int);

/**Logs the current student who logged in out
 * @param CourseManeger- the system to logout.
 * @return
 * EX3_NOT_LOGGED_IN- if no student logged in.
 * EX3_SUCCESS- if a student successfully logged out.*/
CMResult studentLogout(CourseManager);

/**Enables the student to ask the faculty to remove course, cancel course or
 * to register to a course.
 * @param CourseManager- the system.
 * @param ID - the ID of the requesting student.
 * @param int- the course ID.
 * @param char*- the request to be sent.
 * @param FILE*- the output channel.
 * @return
 * EX3_NOT_LOGGED_IN- if theres no student logged in.
 * EX3_COURSE_DOES_NOT_EXIST- if remove course requested and the course does
 * not exist.
 * EX3_INVALID_PARAMETERS- if the request is none of the above. */
CMResult reportFacultyRequest(CourseManager,int,int,char*,
		FILE*);

/**Prints the student's friends names, only those who can give him reference
 * to the course (did the course).
 * @param CourseManager- the system.
 * @param int ID- the ID of the student who looks for reference.
 * @param int - course_id - the course to get reference for.
 * @param int - amount - the amount of friends to print. (those with the highest
 * 						will be printed.)
 * @param FILE*- the output channel.
 * @return
 * EX3_NOT_LOGGED_IN - if the student not logged in to the system.
 * EX3_INVALID_PARAMETERS- if the amount is an illegal number, null system,
 * illegal ID or illegal course id.*/
CMResult reportReference(CourseManager,int,int,int,FILE*);



CMResult gradeSheetAdd(CourseManager system,int semester_num, int course_id,
		char* points, int grade);
CMResult gradeSheetRemove(CourseManager system,int semester_num,int course_id);
CMResult gradeSheetUpdate(CourseManager system, int course_id, int new_grade);
CMResult printFullGradeSheet(CourseManager system,FILE* output_channel);
CMResult printCleanGradeSheet(CourseManager system, FILE* output_channel);
CMResult PrintHighestGrades(CourseManager system, int amount,
		FILE* output_channel);
CMResult PrintLowestGrades(CourseManager system,int amount,
		FILE* output_channel);



/**Deallocates course manager system*/
void destroyCourseManager(CourseManager);

#endif /* COURSE_MANAGER_H_ */
