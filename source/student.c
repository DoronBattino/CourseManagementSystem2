#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "friend.h"
#include "friend_request.h"

struct student_t{
	int ID;
	char* first_name;
	char* last_name;
	Set friend_request;
	FriendsSet friends;
	List semesters;
};
char* getFirstName(Student student){
	if(!student) return NULL;
	return student->first_name;
}

char* getLastName(Student student){
	if(!student) return NULL;
	return student->last_name;
}

SetElement copyStudent(SetElement student){
	if(!student) return NULL;
	return student;
}

List getSemesterList(Student student){
	if(!student) return NULL;
	return student->semesters;
}

int compareStudent(SetElement student1, SetElement student2){
	if(getID(student1)==getID(student2)) return 0;
	if(getID(student1)>getID(student2)) return 1;
	return -1;
}

int getID(Student student){
	if(!student) return -1;
	return student->ID;
}

Set getFriendRequestSet(Student student){
	if(!student) return NULL;
	return student->friend_request;
}

Student getStudentByID(Set set, int ID){
	if(ID<1 || ID>=MAX_ID) return NULL;
	SET_FOREACH(Student,iterator,set){
		if(getID(iterator)==ID) return iterator;
	}
	return NULL;
}

FriendsSet getFriends(Student student){
	if(!student) return NULL;
	return student->friends;
}

Student createStudent(int ID, char* first_name, char* last_name,
					  StudentResult* result){
	if(ID<1 || ID>=MAX_ID){
		*result = STUDENT_INVALID_ID;
		return NULL;
	}
	if(strlen(first_name)==0 || strlen(last_name)==0){
		*result = STUDENT_NULL_ARGUMENT;
		return NULL;
	}
	Student new_student = malloc(sizeof(*new_student));
	if(!new_student) return NULL;
	new_student->first_name = malloc(strlen(first_name)+1);
	if(!new_student->first_name){
		free(new_student);
		*result = STUDENT_MEMMORY_ERROR;
		return NULL;
	}
	new_student->last_name = malloc(strlen(last_name)+1);
	if(!new_student->last_name){
		free(new_student->first_name);
		free(new_student);
		*result = STUDENT_MEMMORY_ERROR;
		return NULL;
	}
	new_student->ID = ID;
	new_student->first_name = strcpy(new_student->first_name, first_name);
	new_student->last_name = strcpy(new_student->last_name, last_name);
	new_student->friends = createFriends(copyFriend,freeFriend,compareFriend);
	new_student->friend_request = setCreate(copyFriendRequest,freeFriendRequest,
											compareFriendRequest);
	new_student->semesters = listCreate(copySemester,freeSemester);
	*result = STUDENT_SUCCESS;
	return new_student;
}

static FriendResult fromSetResToFriendRes(SetResult sr){
	switch(sr){
		case SET_SUCCESS:
			return FRIEND_SUCCESS;
		case SET_ITEM_DOES_NOT_EXIST:
			return FRIEND_NOT_EXISTS;
		case SET_ITEM_ALREADY_EXISTS:
			return FRIEND_ALREADY_EXISTS;
		case SET_NULL_ARGUMENT:
			return FRIEND_NULL_ARGUMENT;
		default:
			return FRIEND_MEMMORY_ERROR;
	}
}

StudentResult unfriend(Student remover, Student to_remove){
	if(!remover || !to_remove) return STUDENT_NULL_ARGUMENT;
	FriendResult fr = fromSetResToFriendRes(setRemove(getFriendSetSet(getFriends(remover)),
								(Friend)to_remove));
	if(fr==FRIEND_NOT_EXISTS) return STUDENT_NOT_A_FRIEND;
	if(fr==FRIEND_NULL_ARGUMENT) return STUDENT_NOT_A_FRIEND;
	if(fr==FRIEND_MEMMORY_ERROR) return STUDENT_MEMMORY_ERROR;
	setRemove(getFriendSetSet(getFriends(to_remove)),(Friend)remover);
	return STUDENT_SUCCESS;
}

void studentDestroy(SetElement student){
	if(!student) return;
	listDestroy(((Student)student)->semesters);
	setDestroy(((Student)student)->friend_request);
	friendsDestroy(((Student)student)->friends);
	free(((Student)student)->first_name);
	((Student)student)->first_name = NULL;
	free(((Student)student)->last_name);
	((Student)student)->last_name = NULL;
	free(student);
}

Student addCourseToStudent(Student student, int semester_number, int course_id, char* points, int grade){
	if(addCourseToSemester(student->semesters,semester_number,course_id,points,grade)){
		return student;
	}
	else return NULL;

}

bool removeGradeFromStudent(Student student, int semester_num, int course_id){
	if(removeCoursefromSemester(student->semesters,semester_num,course_id)){
		return true;
	}
	else return false;
}




bool updateStudentCourseGrade(Student student,int course_id, int new_grade){
	if(updateCourseInSemester(student->semesters,course_id, new_grade)){
		return true;
	}
	else return false;
}

bool findIfStudentHaveCourse(Student student, int course_id){
	if(FindIfCourseInSemester(student->semesters,course_id)){
		return true;
	}
	return false;
}


void printStudentFullGradesAndInfo(Student student, FILE* output_channel) {
	assert(student != NULL);
	ListSortKey key = 0;
	listSort(student->semesters, compareSemesters, key);
	ex3PrintStudentInfo(output_channel, student->ID, student->first_name, student->last_name);
	LIST_FOREACH(Semester, iterator, student->semesters) {
		printGradesOfSemester(iterator, output_channel);
		printSemesterSummary(iterator, output_channel);
	}
	printGradeSheetSummary(student->semesters,output_channel);
}


void printStudentCleanGradeSheet(Student student, FILE* output_channel){
    ex3PrintStudentInfo(output_channel,student->ID,student->first_name,student->last_name);
	printStudentCleanGradesAndInfo(student->semesters,output_channel);
	printGradeSheetCleanSummary(student->semesters,output_channel);
}


void printStudentHighestGrades(int amount,Student student, FILE* output_channel){
	assert(student!=NULL);
	printHighestGradesFromList(amount,student->semesters,output_channel);

}

void printStudentLowestGrades(int amount,Student student, FILE* output_channel){
	assert(student!=NULL);
	printLowestGradesFromList(amount,student->semesters,output_channel);

}


