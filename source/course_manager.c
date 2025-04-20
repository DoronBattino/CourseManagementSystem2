#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "course_manager.h"

struct course_manager{
	void* logged_in;
	Set student;
};

/**Defining a type for reference*/
typedef struct temp *Temp;

struct temp{
	int grade;
	int ID;
	int semester;
};

CMResult gradeSheetAdd(CourseManager system,int semester_num, int course_id,
		char* points, int grade){
	if(system==NULL){
		return CM_INVALID_PARAMETERS;
	}
	if(!system->logged_in){
		return CM_NOT_LOGGED_IN;
	}
	if(!checkCourseId(course_id) || !checkGrade(grade) ||
			!checkLegalPointNumber(points) || semester_num<=0){
		return CM_INVALID_PARAMETERS;
	}
	addCourseToStudent(system->logged_in,semester_num,course_id,points,grade);
	return CM_SUCCESS;
}

CMResult gradeSheetRemove(CourseManager system, int semester_num,
		int course_id){
	if(system==NULL){
		return CM_OUT_OF_MEMORY;
	}
	if(!system->logged_in){
			return CM_NOT_LOGGED_IN;
		}

	if(!removeGradeFromStudent(system->logged_in,semester_num,course_id)){
		return CM_COURSE_DOES_NOT_EXIST;
	}

	return CM_SUCCESS;
}

CMResult gradeSheetUpdate(CourseManager system, int course_id, int new_grade){
	if(system==NULL){
		return CM_INVALID_PARAMETERS;
	}
	if(!system->logged_in){
			return CM_NOT_LOGGED_IN;
	}
	if(!findIfStudentHaveCourse(system->logged_in,course_id)){
		return CM_COURSE_DOES_NOT_EXIST;
	}

	if(!checkGrade(new_grade) || !checkCourseId(course_id)){
			return CM_INVALID_PARAMETERS;
	}
	updateStudentCourseGrade(system->logged_in,course_id,new_grade);

	return CM_SUCCESS;

}

// Print Functions //

CMResult printFullGradeSheet(CourseManager system,FILE* output_channel){
	if(system==NULL){
		return CM_INVALID_PARAMETERS;
	}
	if(!system->logged_in){
		return CM_NOT_LOGGED_IN;
	}

	printStudentFullGradesAndInfo(system->logged_in,output_channel);
	return CM_SUCCESS;
}

CMResult printCleanGradeSheet(CourseManager system, FILE* output_channel){
	if(system==NULL){
		return CM_INVALID_PARAMETERS;
	}
	if(!system->logged_in){
		return CM_NOT_LOGGED_IN;
	}
	printStudentCleanGradeSheet(system->logged_in,output_channel);
	return CM_SUCCESS;

}

CMResult PrintHighestGrades(CourseManager system, int amount,
		FILE* output_channel){
	if(system==NULL || amount<=0){
		return CM_INVALID_PARAMETERS;
	}
	if(!system->logged_in){
		return CM_NOT_LOGGED_IN;
	}

	printStudentHighestGrades(amount,system->logged_in,output_channel);
	return CM_SUCCESS;
}

CMResult PrintLowestGrades(CourseManager system, int amount,
		FILE* output_channel) {
	if(system==NULL || amount<=0){
		return CM_INVALID_PARAMETERS;
	}
	if(!system->logged_in) {
		return CM_NOT_LOGGED_IN;
	}

	printStudentLowestGrades(amount, system->logged_in, output_channel);
	return CM_SUCCESS;
}

CourseManager createCourseManager(){
	CourseManager new_system = malloc(sizeof(*new_system));
	if(!new_system) return NULL;
	new_system->student = setCreate(copyStudent,studentDestroy,compareStudent);
	if(!new_system->student){
		free(new_system);
		return NULL;
	}
	new_system->logged_in=NULL;
	return new_system;
}



Student getLogin(CourseManager system){
	return system->logged_in;
}

CMResult studentAdd(CourseManager system, int ID, char* first_name,
					char* last_name){
	if(!system || !first_name || !last_name) return CM_INVALID_PARAMETERS;
	StudentResult r = STUDENT_SUCCESS;
	StudentResult* result = &r;
	Student new_student = createStudent(ID,first_name,last_name,result);
	if(*result==STUDENT_INVALID_ID) return CM_INVALID_PARAMETERS;
	if(*result==STUDENT_MEMMORY_ERROR || *result==STUDENT_NULL_ARGUMENT)
		return CM_OUT_OF_MEMORY;
	SetResult sr = setAdd(system->student,new_student);
	if(sr==SET_OUT_OF_MEMORY) return CM_OUT_OF_MEMORY;
	if(sr==SET_ITEM_ALREADY_EXISTS){
		studentDestroy(new_student);
		return CM_STUDENT_ALREADY_EXISTS;
	}
	return CM_SUCCESS;
}

CMResult studentLogin(CourseManager system, int ID){
	if(!system) return CM_INVALID_PARAMETERS;
	if(system->logged_in) return CM_ALREADY_LOGGED_IN;
	else{
		SET_FOREACH(Student,iterator,system->student){
			if(getID(iterator)==ID){
				if(system->logged_in==NULL){
					system->logged_in=iterator;
					return CM_SUCCESS;
				}
				if(getID(system->logged_in)==ID) return CM_ALREADY_LOGGED_IN;
				system->logged_in = iterator;
				return CM_SUCCESS;
			}
		}
		return CM_STUDENT_DOES_NOT_EXIST;
	}
	return CM_INVALID_PARAMETERS;
}


void destroyCourseManager(CourseManager system){
	setDestroy(system->student);
	free(system);
}

static int getTempID(Temp reference){
	return reference->ID;
}

static Temp createTemp(int grade,int ID, int semester){
	Temp new_temp = malloc(sizeof(*new_temp));
	if(!new_temp) return NULL;
	new_temp->semester=semester;
	new_temp->ID=ID;
	new_temp->grade=grade;
	return new_temp;
}

static bool isLoggedIn(CourseManager system, int ID){
	if(!system->logged_in || getID(system->logged_in)!=ID) return false;
	return true;
}

/**In this case we want to sort list by the distance from 100 (Grades)
 * so we can get the highest grades first.*/

static int gradesCloserTo(ListElement temp1, ListElement temp2,
		ListSortKey value) {
   int distance1 = abs(getGrade(temp1) - *(int*)value);
   int distance2 = abs(getGrade(temp2) - *(int*)value);
   return distance1 - distance2;
}

static ListElement copyTemp(ListElement temp){
	Temp new_temp = malloc(sizeof(*new_temp));
	if(!new_temp) return NULL;
	new_temp->ID = ((Temp)temp)->ID;
	new_temp->grade = ((Temp)temp)->grade;
	new_temp->semester = ((Temp)temp)->semester;
	return new_temp;
}

static void freeTemp(ListElement temp){
	free(temp);
}

Set getStudentsSet(CourseManager system){
	if(!system) return NULL;
	return system->student;
}

CMResult studentRemove(CourseManager system, int ID){
	if(!system) return CM_INVALID_PARAMETERS;
	if(getID(system->logged_in)==ID){
		system->logged_in = NULL;
	}
	SET_FOREACH(Student,iterator,system->student){
		removeFriend(getFriends(iterator),
				getFriendByID(getFriendSet(getFriends(iterator)),ID));
		setRemove(getFriendRequestSet(iterator),
				getFriendRequestByID(getFriendRequestSet(iterator),ID));
	}
	SET_FOREACH(Student,iterator,system->student){
		if(getID(iterator)==ID){
			SetResult sr = setRemove(system->student,iterator);
			if(sr==SET_NULL_ARGUMENT || sr==SET_ITEM_DOES_NOT_EXIST){
				return CM_STUDENT_DOES_NOT_EXIST;
			}
			return CM_SUCCESS;
		}
	}
	return CM_STUDENT_DOES_NOT_EXIST;
}

CMResult studentSendFriendRequest(CourseManager system, int sender,
		int receiver){
	if(!getLogin(system)) return CM_NOT_LOGGED_IN;
	if(!isLoggedIn(system,sender)) return CM_NOT_LOGGED_IN;
	if(!setIsIn(getStudentsSet(system),getStudentByID(getStudentsSet(system),
			sender))){
		return CM_STUDENT_DOES_NOT_EXIST;
	}
	if(!setIsIn(getStudentsSet(system),getStudentByID(getStudentsSet(system),
			receiver))){
		return CM_STUDENT_DOES_NOT_EXIST;
	}
	if(setIsIn(getFriendSetSet(getFriends(getStudentByID(system->student,
			sender))),
			((Friend)getStudentByID(system->student,receiver)))){
		return CM_ALREADY_FRIEND;
	}
	FriendRequestResult frr =
			createFriendRequest(getStudentByID(system->student,sender),
			getStudentByID(system->student,receiver));
	if(frr==FRIEND_REQUEST_NO_SELF_REQUEST) return CM_ALREADY_FRIEND;
	if(frr==FRIEND_REQUEST_MEMORY_ERROR) return CM_OUT_OF_MEMORY;
	if(frr==FRIEND_REQUEST_ALREADY_SENT) return CM_ALREADY_REQUESTED;
	if(!system || sender<1 || sender>=MAX_ID || receiver<1 || receiver>=MAX_ID){
		return CM_INVALID_PARAMETERS;
	}
	return CM_SUCCESS;
}

CMResult studentHandleRequest(CourseManager system,int receiver,
		int sender, char* answer){
	if(!getLogin(system)) return CM_NOT_LOGGED_IN;
	if(!isLoggedIn(system,receiver)) return CM_NOT_LOGGED_IN;
	if(!setIsIn(system->student,getStudentByID(system->student,sender))){
		return CM_STUDENT_DOES_NOT_EXIST;
	}
	if(strcmp("accept",answer)==0){
		FriendRequestResult frr =
				acceptFriendRequest(getStudentByID(system->student,receiver),
				getStudentByID(system->student,sender));
		if(frr==FRIEND_REQUEST_MEMORY_ERROR) return CM_OUT_OF_MEMORY;
		if(frr==FRIEND_REQUEST_ALREADY_REQUESTED) return CM_ALREADY_FRIEND;
		if(frr==FRIEND_REQUEST_NOT_EXISTE) return CM_NOT_REQUESTED;
		if(setIsIn(getFriendRequestSet(getStudentByID(system->student,sender)),
		getFriendRequestByID(getFriendRequestSet(getStudentByID(system->student,
				sender)),receiver))){
			setRemove(getFriendRequestSet(getStudentByID(system->student,
					sender)),
		getFriendRequestByID(getFriendRequestSet(getStudentByID(system->student,
				sender)),receiver));
		}
		return CM_SUCCESS;
	}
	if(strcmp("reject",answer)==0){
		FriendRequestResult frr =
				rejectFriendRequest(getStudentByID(system->student,receiver),
						getStudentByID(system->student,sender));
		if(frr==FRIEND_REQUEST_NOT_EXISTE) return CM_NOT_REQUESTED;
		return CM_SUCCESS;
	}
	if(setIsIn(getFriendSetSet(getFriends(getStudentByID(system->student,
				receiver))),
		((Friend)getStudentByID(system->student,sender)))){
		return CM_ALREADY_FRIEND;
	}
	if(!setIsIn(getFriendRequestSet(getStudentByID(system->student,receiver)),
		getFriendRequestByID(getFriendRequestSet(getStudentByID(system->student,
				receiver)),sender))){
		return CM_NOT_REQUESTED;
	}
	if(!system || (!strcmp("accept",answer)==0 && !strcmp("reject",answer)==0)){
		return CM_INVALID_PARAMETERS;
	}
	return CM_SUCCESS;
}

CMResult studentUnfriend(CourseManager system, int remover, int ID){
	if(!getLogin(system)) return CM_NOT_LOGGED_IN;
	if(!isLoggedIn(system,remover)) return CM_NOT_LOGGED_IN;
	if(!setIsIn(system->student,getStudentByID(system->student,remover))||
			!setIsIn(system->student,getStudentByID(system->student,ID))){
		return CM_STUDENT_DOES_NOT_EXIST;
	}
	if(!system || remover<1 || remover>=MAX_ID || ID<1 || ID>=MAX_ID){
		return CM_INVALID_PARAMETERS;
	}
	StudentResult sr = unfriend(getStudentByID(system->student,remover),
			getStudentByID(system->student,ID));
	if(sr==STUDENT_NOT_A_FRIEND) return CM_NOT_FRIEND;
	return CM_SUCCESS;
}

CMResult studentLogout(CourseManager system){
	if(!system) return CM_INVALID_PARAMETERS;
	if(!system->logged_in){
		return CM_NOT_LOGGED_IN;
	}
	system->logged_in = NULL;
	return CM_SUCCESS;
}

/**In this case we want to sort list by the distance from 100 (Grades)
 * so we can get the highest grades first.*/
static int highestFirst(ListElement Grade1, ListElement Grade2, ListSortKey k){
	int distance1 = abs(*(int*)Grade1 - *(int*)k);
	int distance2 = abs(*(int*)Grade2 - *(int*)k);
	return distance1 - distance2;
}

static int compareID(ListElement temp1, ListElement temp2, ListFilterKey keyID){
	int distance1 = abs(((Temp)temp1)->ID - *(int*)keyID);
	int distance2 = abs(((Temp)temp2)->ID - *(int*)keyID);
	return distance1 - distance2;
}

static bool isGradeEqualTo(ListElement element, ListFilterKey key){
	if(((Temp)element)->grade == ((Temp)key)->grade) return true;
	return false;
}

static void sortAndPrint(CourseManager system, List tempList, int amount,
		FILE* output_channel){
	int current_amount = amount;
	int to_jump = 0;
	LIST_FOREACH(Temp,temp,tempList){
		if(!current_amount) break;
		if(to_jump>0){
			to_jump--;
			continue;
		}
		List to_sort = listFilter(tempList,isGradeEqualTo,temp);
		if(!to_sort) break;
		if(listGetSize(to_sort)==1){
			ex3PrintStudentName(output_channel,
					getFirstName(getStudentByID(system->student,
							getTempID(listGetFirst(to_sort)))),
							getLastName(getStudentByID(system->student,
									getTempID(listGetFirst(to_sort)))));
			current_amount--;
			listDestroy(to_sort);
		}else{
		int keyID=0;
		to_jump=1;
		listSort(to_sort,compareID,&keyID);
		LIST_FOREACH(Temp,temp,to_sort){
			if(!current_amount) break;
			ex3PrintStudentName(output_channel,
					getFirstName(getStudentByID(system->student,
							getTempID(listGetCurrent(to_sort)))),
							getLastName(getStudentByID(system->student,
									getTempID(listGetCurrent(to_sort)))));
			current_amount--;
			to_jump++;
		}
		listDestroy(to_sort);
	  }
	}
}

static void printReferenceList(CourseManager system, List tempList,
		int amount, int key ,FILE* output_channel){
	if(listGetSize(tempList)==1){
		ex3PrintStudentName(output_channel,
				getFirstName(getStudentByID(system->student,
						getTempID(listGetFirst(tempList)))),
						getLastName(getStudentByID(system->student,
								getTempID(listGetFirst(tempList)))));
	}
	if(listGetSize(tempList)>1){
		listSort(tempList,gradesCloserTo,&key);
		sortAndPrint(system,tempList,amount,output_channel);
	}

}

CMResult reportReference(CourseManager system, int ID, int course_id, int
		amount, FILE* output_channel){
	if(!getLogin(system)) return CM_NOT_LOGGED_IN;
	if(!system || ID<1 || ID>=MAX_ID || !checkCourseId(course_id) ||
			output_channel==NULL || amount<0){
		return CM_INVALID_PARAMETERS;
	}
	if(!isLoggedIn(system,ID)) return CM_NOT_LOGGED_IN;
	List tempList = listCreate(copyTemp,freeTemp);
	if(!tempList) return CM_OUT_OF_MEMORY;
	int key = 100;
	SET_FOREACH(Friend,friend,
			getFriendSetSet(getFriends(getStudentByID(system->student,ID)))){
		LIST_FOREACH(Semester,semester,
						getSemesterList(getStudentByID(system->student,
								getFriendID(friend)))){
					LIST_FOREACH(Course,course,getCourseList(semester)){
						if(getCourseID(course)==course_id){
							if(getGradesList(course)){
								listSort(getGradesList(course),
										highestFirst, &key);
								int grade = getGrade(listGetFirst(
										getGradesList(course)));
								int id = getFriendID(friend);
								Temp temp = createTemp(grade,id,-1);
								if(!temp) return CM_OUT_OF_MEMORY;
								listInsertFirst(tempList,temp);
								free(temp);
							}
						}
					}
		}
	}
	printReferenceList(system,tempList,amount,key,output_channel);
	listDestroy(tempList);
	return CM_SUCCESS;
}

CMResult reportFacultyRequest(CourseManager system, int ID,int course_id,
		char* request, FILE* output_channel){
	if(!getLogin(system)) return CM_NOT_LOGGED_IN;
	if(!isLoggedIn(system,ID)) return CM_NOT_LOGGED_IN;
	if(strcmp(request,"remove_course")==0){
		bool found = false;
		LIST_FOREACH(Semester,semester,
				getSemesterList(getStudentByID(system->student,ID))){
			LIST_FOREACH(Course,course,getCourseList(semester)){
				if(getCourseID(course)==course_id){
					if(listGetSize(getGradesList(course))==0) continue;
					found = true;
				}
			}
		}
		if(!found) return CM_COURSE_DOES_NOT_EXIST;
	}
	if(ID<1 || ID>=MAX_ID || !checkCourseId(course_id) || output_channel==NULL
			|| (strcmp(request,"cancel_course")!=0 &&
			strcmp(request,"register_course")!=0 &&
			strcmp(request,"remove_course")!=0)){
		return CM_INVALID_PARAMETERS;
	}
	ex3FacultyResponse(output_channel, "your request was rejected");
	return CM_SUCCESS;
}


