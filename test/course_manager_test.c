#include "course_manager.h"
#include "test_utilities.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool createCourseManagerTest(){
	CourseManager system = createCourseManager();
    studentAdd(system,1,"Doron","Battino");
    studentAdd(system, 2,"Assaf","Regev");
    studentAdd(system,3,"Amit","Weil");
    studentAdd(system,4,"Maor","Baruch");

    CMResult mec = studentAdd(system,3,"Amit","Weil");
    ASSERT_TEST(mec==CM_STUDENT_ALREADY_EXISTS);
    ASSERT_TEST(setGetSize(getStudentsSet(system)));

    destroyCourseManager(system);
    return true;
}

static bool studentLoginTest(){
	CourseManager system = createCourseManager();
    studentAdd(system,1,"Doron","Battino");

    studentLogin(system,1);
    ASSERT_TEST(getID(getLogin(system))==1);
    studentLogout(system);
    ASSERT_TEST(!getLogin(system));

    destroyCourseManager(system);
    return true;
}

static bool friendRequestTest(){
	CourseManager system = createCourseManager();
    studentAdd(system,1,"Doron","Battino");
    studentAdd(system, 2,"Assaf","Regev");
    studentAdd(system,3,"Amit","Weil");

    studentLogin(system,1);
    studentSendFriendRequest(system,1,2);
    studentSendFriendRequest(system,1,3);
    ASSERT_TEST(setGetSize(getFriendRequestSet(getStudentByID(getStudentsSet(system),2)))==1);
    ASSERT_TEST(setGetSize(getFriendRequestSet(getStudentByID(getStudentsSet(system),3)))==1);
    studentLogout(system);
    studentLogin(system,2);
    studentHandleRequest(system,2,1,"reject");
    ASSERT_TEST(setGetSize(getFriendRequestSet(getStudentByID(getStudentsSet(system),2)))==0);
    ASSERT_TEST(setGetSize(getFriendSetSet(getFriends(getStudentByID(getStudentsSet(system),2))))==0);
    CMResult mec = studentHandleRequest(system,3,1,"accept");
    ASSERT_TEST(mec==CM_NOT_LOGGED_IN);
    studentLogout(system);
    studentLogin(system,3);
    studentHandleRequest(system,3,1,"accept");
    ASSERT_TEST(setGetSize(getFriendRequestSet(getStudentByID(getStudentsSet(system),3)))==0);
    ASSERT_TEST(setGetSize(getFriendSetSet(getFriends(getStudentByID(getStudentsSet(system),3))))==1);
    mec = studentUnfriend(system,1,3);
    ASSERT_TEST(mec==CM_NOT_LOGGED_IN);
    studentUnfriend(system,3,1);
    ASSERT_TEST(setGetSize(getFriendSetSet(getFriends(getStudentByID(getStudentsSet(system),3))))==0);

    destroyCourseManager(system);
    return true;
}

static bool studentRemoveTest(){
	CourseManager system = createCourseManager();
    studentAdd(system,1,"Doron","Battino");
    studentAdd(system, 2,"Assaf","Regev");
    studentAdd(system,3,"Amit","Weil");

    studentLogin(system,1);
    studentSendFriendRequest(system,1,2);
    studentLogin(system,2);
    studentHandleRequest(system,2,1,"accept");
    studentRemove(system,1);
    ASSERT_TEST(setGetSize(getFriendSetSet(getFriends(getStudentByID(getStudentsSet(system),2))))==0);
    CMResult mec = studentRemove(system,1);
    ASSERT_TEST(mec==CM_STUDENT_DOES_NOT_EXIST);


    destroyCourseManager(system);
    return true;
}

static bool reportFacultyRequestTest(){
	FILE* output_channel;
	CourseManager system = createCourseManager();
	studentAdd(system,1,"Doron","Battino");
	studentAdd(system, 2,"Assaf","Regev");
	studentAdd(system,3,"Amit","Weil");
	studentLogin(system,1);
	studentSendFriendRequest(system,1,3);
	studentSendFriendRequest(system,2,3);
	studentLogin(system,3);
	studentHandleRequest(system,3,1,"accept");
	studentHandleRequest(system,3,2,"accept");
	addCourseToStudent(getStudentByID(getStudentsSet(system),1),1,234122,"3.5",90);
	addCourseToStudent(getStudentByID(getStudentsSet(system),2),1,234122,"3.5",55);
	addCourseToStudent(getStudentByID(getStudentsSet(system),3),1,234122,"3.5",75);

	studentLogin(system,1);
	output_channel = fopen("textTester","a");
	if(!output_channel) return false;
	reportFacultyRequest(system,1,234122,"register_course",output_channel);
	fclose(output_channel);

	destroyCourseManager(system);
	return true;
}

static bool reportReferenceTest(){
	FILE* output_channel;
	SemesterResult sr = SEMESTER_SUCCESS;
	SemesterResult* result = &sr;
	CourseManager system = createCourseManager();
	studentAdd(system,1,"Doron","Battino");
	studentAdd(system, 2,"Assaf","Regev");
	studentAdd(system,3,"Amit","Weil");
	studentAdd(system,5,"Liran","Tomer");
	studentAdd(system,4,"Matan","Biton");
	studentLogin(system,1);
	studentSendFriendRequest(system,1,3);
    studentLogout(system);
	studentLogin(system,2);
	studentSendFriendRequest(system,2,3);
    studentLogout(system);
	studentLogin(system,4);
	studentSendFriendRequest(system,4,3);
    studentLogout(system);
	studentLogin(system,5);
	studentSendFriendRequest(system,5,3);
    studentLogout(system);
	studentLogin(system,3);
	studentHandleRequest(system,3,1,"accept");
	studentHandleRequest(system,3,2,"accept");
	studentHandleRequest(system,3,4,"accept");
	studentHandleRequest(system,3,5,"accept");
	ASSERT_TEST(setGetSize(getFriendSetSet(getFriends(getStudentByID(getStudentsSet(system),3))))==4);

	List list = listCreate(copyCourse,freeCourse);
	Semester semester1 = createSemester(1,list,result);
	listInsertFirst(getSemesterList(getStudentByID(getStudentsSet(system),1)),semester1);
	ASSERT_TEST((listGetSize(getSemesterList(getStudentByID(getStudentsSet(system),1))))==1);
	listInsertFirst(getSemesterList(getStudentByID(getStudentsSet(system),2)),semester1);
	listInsertFirst(getSemesterList(getStudentByID(getStudentsSet(system),3)),semester1);
	listInsertFirst(getSemesterList(getStudentByID(getStudentsSet(system),4)),semester1);
	listInsertFirst(getSemesterList(getStudentByID(getStudentsSet(system),5)),semester1);
	listDestroy(list);
	freeSemester(semester1);
    
	addCourseToStudent(getStudentByID(getStudentsSet(system),1),1,234122,"3.5",90);
	addCourseToStudent(getStudentByID(getStudentsSet(system),2),1,234122,"3.5",75);
	addCourseToStudent(getStudentByID(getStudentsSet(system),3),1,234122,"3.5",75);
	addCourseToStudent(getStudentByID(getStudentsSet(system),4),1,234122,"3.5",75);
	addCourseToStudent(getStudentByID(getStudentsSet(system),5),1,234122,"3.5",70);

	output_channel = fopen("outputTester","a");
	if(!output_channel) return false;
	reportReference(system,3,234122,5,output_channel);
	fclose(output_channel);


	destroyCourseManager(system);
	return true;
}
/**
 * List of tests, one for each function is usually a good thumb rule.
 */

static bool testGradeSheetAdd(){
    SemesterResult result_semester;
    CourseManager system=createCourseManager();
    List courses=listCreate(copyCourse,freeCourse);
    Semester semester=createSemester(1,courses,&result_semester);
    ASSERT_TEST(gradeSheetAdd(system,1,1,"0.5",90)==CM_NOT_LOGGED_IN);
    studentAdd(system,203996715,"amit","weil");
    ASSERT_TEST(gradeSheetAdd(system,1,1,"0.5",90)==CM_NOT_LOGGED_IN);
    studentLogin(system,203996715);
    List semesters=getSemesterList(getLogin(system));
    listInsertFirst(semesters,semester);
    ASSERT_TEST(gradeSheetAdd(system,0,-1,"0.5",90)==CM_INVALID_PARAMETERS);
    ASSERT_TEST(gradeSheetAdd(system,3,1,"0.4",90)==CM_INVALID_PARAMETERS);
    ASSERT_TEST(gradeSheetAdd(system,0,1,"0.5",205)==CM_INVALID_PARAMETERS);
    ASSERT_TEST(gradeSheetAdd(system,1,493,"0.5",95)==CM_SUCCESS);
    LIST_FOREACH(Semester,iterator,semesters){
        if(returnSemeserNumber(iterator)==1){
            LIST_FOREACH(Course,iterator_two,returnCourseList(iterator)){
                if(returnCourseId(iterator_two)==493){
                    ASSERT_TEST(returnEffectiveGradeOfCourse(iterator_two)==95);
                }
            }
        }
    }
    ASSERT_TEST(gradeSheetAdd(system,1,493,"0.5",85)==CM_SUCCESS);
    LIST_FOREACH(Semester,iterator,semesters){
        if(returnSemeserNumber(iterator)==1){
            ASSERT_TEST(listGetSize(returnCourseList(iterator))==2);
        }
    }
    destroyCourseManager(system);
    freeSemester(semester);
    listDestroy(courses);
    return true;
}



static bool testGradeSheetRemove(){
    SemesterResult result_semester;
    CourseManager system=createCourseManager();
    List courses=listCreate(copyCourse,freeCourse);
    Semester semester=createSemester(1,courses,&result_semester);
    ASSERT_TEST(gradeSheetRemove(system,1,1)==CM_NOT_LOGGED_IN);
    studentAdd(system,203996715,"amit","weil");
    studentLogin(system,203996715);
    List semesters=getSemesterList(getLogin(system));
    listInsertFirst(semesters,semester);
    ASSERT_TEST(gradeSheetRemove(system,1,15)==CM_COURSE_DOES_NOT_EXIST);
    ASSERT_TEST(gradeSheetAdd(system,1,493,"0.5",95)==CM_SUCCESS);
    ASSERT_TEST(gradeSheetRemove(system,1,493)==CM_SUCCESS);
    ASSERT_TEST(gradeSheetAdd(system,1,493,"0.5",85)==CM_SUCCESS);
    ASSERT_TEST(gradeSheetAdd(system,1,493,"0.5",95)==CM_SUCCESS);
    ASSERT_TEST(gradeSheetRemove(system,1,493)==CM_SUCCESS);
    LIST_FOREACH(Semester,iterator,semesters){
        if(returnSemeserNumber(iterator)==1){
            ASSERT_TEST(listGetSize(returnCourseList(iterator))==1);
        }
    }
    destroyCourseManager(system);
    freeSemester(semester);
    listDestroy(courses);
    return true;
}



static bool testGradeSheetUpdate(){
    SemesterResult result_semester;
    CourseManager system=createCourseManager();
    List courses=listCreate(copyCourse,freeCourse);
    Semester semester=createSemester(1,courses,&result_semester);
    ASSERT_TEST(gradeSheetUpdate(system,1,1)==CM_NOT_LOGGED_IN);
    studentAdd(system,203996715,"amit","weil");
    studentLogin(system,203996715);
    List semesters=getSemesterList(getLogin(system));
    listInsertFirst(semesters,semester);
    ASSERT_TEST(gradeSheetUpdate(NULL,1,1)==CM_INVALID_PARAMETERS);
    ASSERT_TEST(gradeSheetUpdate(NULL,1,105)==CM_INVALID_PARAMETERS);
    ASSERT_TEST(gradeSheetUpdate(NULL,-1,1)==CM_INVALID_PARAMETERS);
    ASSERT_TEST(gradeSheetAdd(system,1,493,"0.5",95)==CM_SUCCESS);
    ASSERT_TEST(gradeSheetRemove(system,1,493)==CM_SUCCESS);
    ASSERT_TEST(gradeSheetUpdate(system,493,50)==CM_COURSE_DOES_NOT_EXIST);
    ASSERT_TEST(gradeSheetAdd(system,1,493,"0.5",95)==CM_SUCCESS);
    ASSERT_TEST(gradeSheetUpdate(system,493,75)==CM_SUCCESS);
    LIST_FOREACH(Semester,iterator,semesters){
        if(returnSemeserNumber(iterator)==1){
            LIST_FOREACH(Course,iterator_two,returnCourseList(iterator)){
                if(returnCourseId(iterator_two)==493){
                    ASSERT_TEST(returnEffectiveGradeOfCourse(iterator_two)==75);
                }
            }
        }
    }
    destroyCourseManager(system);
    freeSemester(semester);
    listDestroy(courses);
    return true;

}



static bool testPrintFullGradeSheet(){
    FILE* output_channel=fopen("testFullGradeSheet","w");
    assert(output_channel != NULL);
    SemesterResult result_semester;
    CourseManager system=createCourseManager();
    List courses=listCreate(copyCourse,freeCourse);
    List courses_two=listCreate(copyCourse,freeCourse);
    Semester semester=createSemester(1,courses,&result_semester);
    Semester semester_two=createSemester(2,courses_two,&result_semester);
    ASSERT_TEST(printFullGradeSheet(system,output_channel)==CM_NOT_LOGGED_IN);
    studentAdd(system,203996715,"amit","weil");
    studentLogin(system,203996715);
    List semesters=getSemesterList(getLogin(system));
    listInsertFirst(semesters,semester);
    listInsertLast(semesters,semester_two);
    ASSERT_TEST(gradeSheetAdd(system,1,5000,"0.5",75)==CM_SUCCESS);
    ASSERT_TEST(gradeSheetAdd(system,1,5000,"0.5",65)==CM_SUCCESS);
    ASSERT_TEST(gradeSheetAdd(system,1,6000,"3",95)==CM_SUCCESS);
    ASSERT_TEST(gradeSheetAdd(system,2,4000,"2",80)==CM_SUCCESS);
    ASSERT_TEST(gradeSheetAdd(system,2,3000,"1",45)==CM_SUCCESS);
    ASSERT_TEST(printFullGradeSheet(system,output_channel)==CM_SUCCESS);
    destroyCourseManager(system);
    freeSemester(semester);
    freeSemester(semester_two);
    listDestroy(courses);
    listDestroy(courses_two);
    fclose(output_channel);
    return true;

}

static bool testPrintCleanGradeSheet(){
    FILE* output_channel=fopen("testCleanGradeSheet","w");
    assert(output_channel != NULL);
    SemesterResult result_semester;
    CourseManager system=createCourseManager();
    List courses=listCreate(copyCourse,freeCourse);
    List courses_two=listCreate(copyCourse,freeCourse);
    Semester semester=createSemester(1,courses,&result_semester);
    Semester semester_two=createSemester(2,courses_two,&result_semester);
    ASSERT_TEST(printCleanGradeSheet(NULL,output_channel)==CM_INVALID_PARAMETERS);
    ASSERT_TEST(printCleanGradeSheet(system,output_channel)==CM_NOT_LOGGED_IN);
    studentAdd(system,203996715,"amit","weil");
    studentLogin(system,203996715);
    List semesters=getSemesterList(getLogin(system));
    listInsertFirst(semesters,semester);
    listInsertLast(semesters,semester_two);
    ASSERT_TEST(gradeSheetAdd(system,1,5000,"0.5",75)==CM_SUCCESS);
    ASSERT_TEST(gradeSheetAdd(system,1,5000,"0.5",65)==CM_SUCCESS);
    ASSERT_TEST(gradeSheetAdd(system,1,6000,"3",70)==CM_SUCCESS);
    ASSERT_TEST(gradeSheetAdd(system,1,399998,"3.5",70)==CM_SUCCESS);
    ASSERT_TEST(gradeSheetAdd(system,2,399998,"3.5",93)==CM_SUCCESS);
    ASSERT_TEST(gradeSheetAdd(system,1,6000,"3",95)==CM_SUCCESS);
    ASSERT_TEST(gradeSheetAdd(system,2,4000,"2",80)==CM_SUCCESS);
    ASSERT_TEST(gradeSheetAdd(system,2,3000,"1",45)==CM_SUCCESS);
    ASSERT_TEST(printCleanGradeSheet(system,output_channel)==CM_SUCCESS);
    destroyCourseManager(system);
    freeSemester(semester);
    freeSemester(semester_two);
    listDestroy(courses);
    listDestroy(courses_two);
    fclose(output_channel);
    return true;

}


static bool testPrintHighestGrades(){
    FILE* output_channel=fopen("testHighGrades","w");
    assert(output_channel != NULL);
    SemesterResult result_semester;
    CourseManager system=createCourseManager();
    List courses=listCreate(copyCourse,freeCourse);
    List courses_two=listCreate(copyCourse,freeCourse);
    Semester semester=createSemester(1,courses,&result_semester);
    Semester semester_two=createSemester(2,courses_two,&result_semester);
    ASSERT_TEST(PrintHighestGrades(NULL,3,output_channel)==CM_INVALID_PARAMETERS);
    ASSERT_TEST(PrintHighestGrades(system,-4,output_channel)==CM_INVALID_PARAMETERS);
    ASSERT_TEST(PrintHighestGrades(system,3,output_channel)==CM_NOT_LOGGED_IN);
    studentAdd(system,203996715,"amit","weil");
    studentLogin(system,203996715);
    List semesters=getSemesterList(getLogin(system));
    listInsertFirst(semesters,semester);
    listInsertLast(semesters,semester_two);
    ASSERT_TEST(gradeSheetAdd(system,1,5000,"0.5",75)==CM_SUCCESS);
    ASSERT_TEST(gradeSheetAdd(system,1,5000,"0.5",65)==CM_SUCCESS);
    ASSERT_TEST(gradeSheetAdd(system,1,8000,"0.5",65)==CM_SUCCESS);
    ASSERT_TEST(gradeSheetAdd(system,1,6000,"3",70)==CM_SUCCESS);
    ASSERT_TEST(gradeSheetAdd(system,1,399998,"3.5",93)==CM_SUCCESS);
    ASSERT_TEST(gradeSheetAdd(system,2,399998,"3",93)==CM_SUCCESS);
    ASSERT_TEST(gradeSheetAdd(system,1,6000,"3",65)==CM_SUCCESS);
    ASSERT_TEST(gradeSheetAdd(system,2,4000,"2",80)==CM_SUCCESS);
    ASSERT_TEST(gradeSheetAdd(system,2,3000,"1",45)==CM_SUCCESS);
    ASSERT_TEST(PrintHighestGrades(system,15,output_channel)==CM_SUCCESS);
    destroyCourseManager(system);
    freeSemester(semester);
    freeSemester(semester_two);
    listDestroy(courses);
    listDestroy(courses_two);
    fclose(output_channel);
    return true;


}

static bool testPrintLowestGrades(){
    FILE* output_channel=fopen("testLowGrades","w");
    assert(output_channel != NULL);
    SemesterResult result_semester;
    CourseManager system=createCourseManager();
    List courses=listCreate(copyCourse,freeCourse);
    List courses_two=listCreate(copyCourse,freeCourse);
    Semester semester=createSemester(1,courses,&result_semester);
    Semester semester_two=createSemester(2,courses_two,&result_semester);
    ASSERT_TEST(PrintLowestGrades(NULL,3,output_channel)==CM_INVALID_PARAMETERS);
    ASSERT_TEST(PrintLowestGrades(system,-4,output_channel)==CM_INVALID_PARAMETERS);
    ASSERT_TEST(PrintLowestGrades(system,3,output_channel)==CM_NOT_LOGGED_IN);
    studentAdd(system,203996715,"amit","weil");
    studentLogin(system,203996715);
    List semesters=getSemesterList(getLogin(system));
    listInsertFirst(semesters,semester);
    listInsertLast(semesters,semester_two);
    ASSERT_TEST(gradeSheetAdd(system,1,5000,"0.5",75)==CM_SUCCESS);
    ASSERT_TEST(gradeSheetAdd(system,1,5000,"0.5",65)==CM_SUCCESS);
    ASSERT_TEST(gradeSheetAdd(system,1,8000,"0.5",65)==CM_SUCCESS);
    ASSERT_TEST(gradeSheetAdd(system,1,6000,"3",70)==CM_SUCCESS);
    ASSERT_TEST(gradeSheetAdd(system,1,399998,"3.5",93)==CM_SUCCESS);
    ASSERT_TEST(gradeSheetAdd(system,2,399998,"3",93)==CM_SUCCESS);
    ASSERT_TEST(gradeSheetAdd(system,1,6000,"3",65)==CM_SUCCESS);
    ASSERT_TEST(gradeSheetAdd(system,2,4000,"2",80)==CM_SUCCESS);
    ASSERT_TEST(gradeSheetAdd(system,2,3000,"1",45)==CM_SUCCESS);
    ASSERT_TEST(PrintLowestGrades(system,5,output_channel)==CM_SUCCESS);
    destroyCourseManager(system);
    freeSemester(semester);
    freeSemester(semester_two);
    listDestroy(courses);
    listDestroy(courses_two);
    fclose(output_channel);
    return true;


}

int main(){
	RUN_TEST(createCourseManagerTest);
	RUN_TEST(studentLoginTest);
	RUN_TEST(friendRequestTest);
	RUN_TEST(studentRemoveTest);
	RUN_TEST(reportFacultyRequestTest);
	RUN_TEST(reportReferenceTest);
    RUN_TEST(testGradeSheetAdd);
    RUN_TEST(testGradeSheetRemove);
    RUN_TEST(testGradeSheetUpdate);
    RUN_TEST(testPrintFullGradeSheet);
    RUN_TEST(testPrintCleanGradeSheet);
    RUN_TEST(testPrintHighestGrades);
    RUN_TEST(testPrintLowestGrades);
	return 0;
}

