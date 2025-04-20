#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Semester.h"
#include "GradeSheet.h"
#include "Course.h"
#include "Grade.h"
#include "list.h"
#include "set.h"



struct semester{
    int number;
    List courses;
};

Semester createSemester(int number,List Courses, SemesterResult* result) {
    if(Courses==NULL){
        *result=SEMESTER_NULL_ARGUMENT;
        return NULL;
    }
    if(number<0){
        *result=SEMESTER_ILLEGAL_ARGUMENT;
        return NULL;
    }
    Semester new_semester=malloc(sizeof(*new_semester));
    if(new_semester==NULL){
        *result=SEMESTER_OUT_OF_MEMORY;
        return NULL;
    }
    new_semester->courses=listCopy(Courses);
    if(new_semester->courses==NULL){
        free(new_semester);
        *result=SEMESTER_OUT_OF_MEMORY;
    }

    new_semester->number=number;
    *result=SEMESTER_SUCCESS;
    return  new_semester;

}

ListElement copySemester(ListElement semester){
    if(semester==NULL){
        return NULL;
    }
    Semester copy=malloc(sizeof(*copy));
    if(copy==NULL){
        return NULL;
    }
    Semester cast=(Semester)semester;
    copy->number=cast->number;
    copy->courses=listCopy(cast->courses);
    if(copy->courses==NULL){
        free(copy);
        return NULL;
    }
    return copy;
}

List getCourseList(Semester semester){
    if(!semester) return NULL;
    return semester->courses;
}

int getSemesterNumber(Semester semester){
    return semester->number;
}

bool addCourseToSemester(List semesters, int semester_number, int course_id,
		char* points, int grade) {
    if (semesters == NULL || semester_number <= 0) return false;
    LIST_FOREACH(Semester,iterator,semesters){
        if(iterator->number==semester_number){
            CourseResult check=addCourse(iterator->courses, course_id, points,
            		grade);
            if(check==COURSE_SUCCESS){
                return true;
            }
            return false;
        }
    }
    List Courses=listCreate(copyCourse,freeCourse);
    SemesterResult result;
    Semester new_created_semester=createSemester(semester_number,Courses,
    		&result);
    if(!new_created_semester){
    	return false;
    }
    listInsertLast(semesters,(ListElement)new_created_semester);
    LIST_FOREACH(Semester,iterator,semesters){
           if(iterator->number==semester_number){
               CourseResult check=addCourse(iterator->courses, course_id,points,
               		grade);
               if(check==COURSE_SUCCESS){
            	   freeSemester(new_created_semester);
            	      listDestroy(Courses);
                   return true;
               }
               freeSemester(new_created_semester);
                  listDestroy(Courses);
               return false;
           }
       }
    freeSemester(new_created_semester);
    listDestroy(Courses);
    return true;
}

bool removeCoursefromSemester(List Semesters, int semester_num, int course_id){
    if(Semesters==NULL){
        return false;
    }
    LIST_FOREACH(Semester,iterator,Semesters){
        if(iterator->number==semester_num){
            int check=removeCourseFromList(iterator->courses,course_id);
            if(check==2){
            	listRemoveCurrent(iterator->courses);
                return true;
            }
            if(check==1){
            	return true;
            }
            else return false;
        }
    }
    return false;
}


int compareSemesters(ListElement semester,ListElement semester_two,
		ListSortKey key){
    (void)key;
    Semester cast_one=(Semester)semester;
    Semester cast_two=(Semester)semester_two;
    if(cast_one->number>cast_two->number){
        return 1;
    }
    if(cast_one->number==cast_two->number){
        return 0;
    }
    return -1;
}

bool updateCourseInSemester(List Semesters, int course_id, int new_grade){
	Course last_appearance=NULL;
	Course curr_appearance=NULL;
    LIST_FOREACH(Semester,iterator,Semesters) {
    	curr_appearance=checkForLatestIdAppearence(iterator->courses,course_id);
    	if(curr_appearance!=NULL){
    		last_appearance=curr_appearance;
    	}
    }
   if(updateCourse(last_appearance,new_grade)){
    	return true;
    }
    return false;
}

bool FindIfCourseInSemester(List Semesters, int course_id){
	Course appearance=NULL;
    LIST_FOREACH(Semester,iterator,Semesters) {
    	appearance=checkForLatestIdAppearence(iterator->courses,course_id);
    	if(appearance!=NULL){
    		return true;
    	}
    }
    return false;
}


void addRelevantCoursesToGradeSheet(List Semesters,GradeSheet gradesheet) {
    assert(Semesters != NULL && gradesheet != NULL);
    LIST_FOREACH(Semester,iterator,Semesters){
    	Set relevant_for_semester=setCreate(copyCourse,freeCourse,compareCourses);
    	    SetResult result;
    	    	assert(relevant_for_semester!=NULL);
        LIST_FOREACH(Course,iterator_two,iterator->courses) {
            if (checksIfASportCourse(iterator_two)){
                Semester copy_semester = copySemester(iterator);
                Course sport_for_grade_sheet =
                		checkForLatestCourseApperance(copy_semester->courses,
                				iterator_two);
                int semester_number=iterator->number;
                result=setAdd(relevant_for_semester,(SetElement)sport_for_grade_sheet);
                if(result==SET_SUCCESS){
                	addSportCourseToGradeSheet(gradesheet,sport_for_grade_sheet,
                		semester_number);
                }
                freeSemester(copy_semester);
            }
            if (!checksIfASportCourse(iterator_two)) {
                List copy=listCopy(Semesters);
                assert(copy!=NULL);
                Course apply_for_grade_sheet =
                		checkForLatestGradeSheetApperance(copy, iterator_two);
                int semester_number=checkForLatestSemesterNumber(copy,
                		iterator_two);
                addNonSportToGradeSheet(gradesheet, apply_for_grade_sheet,
                		semester_number);
                listDestroy(copy);
            }

        }
        setDestroy(relevant_for_semester);
    }
}


Course checkForLatestGradeSheetApperance(List Semesters,Course course) {
    assert(Semesters != NULL && course != NULL);
    Course latest_sport_in_semester = NULL;
    Course latest_non_sport_in_semester = NULL;
    Course latest_non_sport_in_grade_sheet = NULL;
    if (checksIfASportCourse(course)) {
        LIST_FOREACH(Semester, iterator, Semesters) {
            latest_sport_in_semester =
            		checkForLatestCourseApperance(iterator->courses, course);
            if (latest_sport_in_semester != NULL) {
                listGetFirst(Semesters);
                return latest_sport_in_semester;
            }
        }
    }
    LIST_FOREACH(Semester, iterator, Semesters) {
        latest_non_sport_in_semester =
        		checkForLatestCourseApperance(iterator->courses, course);
        if (latest_non_sport_in_semester != NULL) {
            latest_non_sport_in_grade_sheet = latest_non_sport_in_semester;
        }
    }
    return latest_non_sport_in_grade_sheet;
}

int checkForLatestSemesterNumber(List Semesters, Course course){
    assert(Semesters != NULL && course != NULL);
    Course latest_sport_in_semester = NULL;
    Course latest_non_sport_in_semester = NULL;
    int number=0;
    int number_two=0;
    if (checksIfASportCourse(course)) {
        LIST_FOREACH(Semester, iterator, Semesters) {
            latest_sport_in_semester =
            		checkForLatestCourseApperance(iterator->courses, course);
            if (latest_sport_in_semester != NULL) {
                number_two=iterator->number;
                listGetFirst(Semesters);
                return number_two;
            }
        }
    }
    LIST_FOREACH(Semester, iterator, Semesters) {
        latest_non_sport_in_semester =
        		checkForLatestCourseApperance(iterator->courses, course);

        if (latest_non_sport_in_semester != NULL) {
             number=iterator->number;
        }
    }
    return number;
}


void freeSemester(ListElement semester){
    Semester cast=(Semester)semester;
    listDestroy(cast->courses);
    free(semester);
}



void printGradesOfSemester(Semester semester, FILE* output_channel){
    printCourseGradesFromFirstToLast(semester->courses,output_channel);
}


void printSemesterSummary(Semester semester, FILE* output_channel){
    assert(semester!=NULL);
   if(listGetSize(semester->courses)!=0){
    	int total_points=0;
    	int failed_points=0;
    	int effective_points=0;
    	int effective_sum=0;
    	total_points=numberOfTotalPoints(semester->courses);
    	failed_points=numberOfFailedPoints(semester->courses);
    	effective_points=numberOfEffectivePoints(semester->courses);
    	effective_sum=effectiveGradeSum(semester->courses);
    	ex3PrintSemesterInfo(output_channel,semester->number,total_points,
    			failed_points,effective_points,effective_sum);
    }
    return;
}




void printGradeSheetSummary(List semesters, FILE* output_channel){
    assert(semesters!=NULL);
    GradeSheetResult result;
    Set non_sport_courses=setCreate(copyCourseWithNumber,freeCourseWithNumber,
    		compareCoursesInSet);
    if(non_sport_courses==NULL){
        return;
    }
    List sport_courses=listCreate(copyCourseWithNumber,freeCourseWithNumber);
    if(sport_courses==NULL){
        setDestroy(non_sport_courses);
        return;
    }
    GradeSheet gradesheet=createGradeSheet(non_sport_courses,sport_courses,
    		&result);
    if(gradesheet==NULL){
        setDestroy(non_sport_courses);
        listDestroy(sport_courses);
    }
    int total_semester_points=0;
    int failed_semester_points=0;
    int gradeSheet_total_points=0;
    int gradeSheet_failed_points=0;
    int gradeSheet_effective_points=0;
    int gradeSheet_effective_sum=0;
    LIST_FOREACH(Semester,iterator,semesters){
        total_semester_points=numberOfTotalPoints(iterator->courses);
        failed_semester_points=numberOfFailedPoints(iterator->courses);
        gradeSheet_total_points+=total_semester_points;
        gradeSheet_failed_points+=failed_semester_points;
    }
    addRelevantCoursesToGradeSheet(semesters,gradesheet);
    gradeSheet_effective_points=caculatesPointsInGradeSheet(gradesheet);
    gradeSheet_effective_sum=caculatesEffectiveGradeSumInGradeSheet(gradesheet);
    ex3PrintSummary(output_channel,gradeSheet_total_points,
    		gradeSheet_failed_points,gradeSheet_effective_points,
                    gradeSheet_effective_sum);
    setDestroy(non_sport_courses);
    listDestroy(sport_courses);
    freeGradeSheet(gradesheet);
}



void printGradeSheetCleanSummary(List semesters, FILE* output_channel){
    assert(semesters!=NULL);
    GradeSheetResult result;
    Set non_sport_courses=setCreate(copyCourseWithNumber,freeCourseWithNumber,
    		compareCoursesInSet);
    if(non_sport_courses==NULL){
        return;
    }
    List sport_courses=listCreate(copyCourseWithNumber,freeCourseWithNumber);
    if(sport_courses==NULL){
        setDestroy(non_sport_courses);
        return;
    }
    GradeSheet gradesheet=createGradeSheet(non_sport_courses,sport_courses,
    		&result);
    if(gradesheet==NULL){
        setDestroy(non_sport_courses);
        listDestroy(sport_courses);
    }
    int gradeSheet_effective_points=0;
    int gradeSheet_effective_sum=0;
    addRelevantCoursesToGradeSheet(semesters,gradesheet);
    gradeSheet_effective_points=caculatesPointsInGradeSheet(gradesheet);
    gradeSheet_effective_sum=caculatesEffectiveGradeSumInGradeSheet(gradesheet);
     ex3PrintCleanSummary( output_channel, gradeSheet_effective_points,
    	 gradeSheet_effective_sum);
    setDestroy(non_sport_courses);
    listDestroy(sport_courses);
    freeGradeSheet(gradesheet);
}




void printStudentCleanGradesAndInfo(List semesters, FILE* output_channel){
    assert(semesters != NULL);
    GradeSheetResult result_two;
    List sport_courses=listCreate(copyCourseWithNumber,freeCourseWithNumber);
    assert(sport_courses!=NULL);
    Set non_sport_courses=setCreate(copyCourseWithNumber,freeCourseWithNumber,
    		compareCoursesInSet);
    assert(non_sport_courses!=NULL);
    GradeSheet gradesheet=createGradeSheet(non_sport_courses,sport_courses,
    		&result_two);
    assert(gradesheet!=NULL);
    addRelevantCoursesToGradeSheet(semesters,gradesheet);
    List non_sport_list=sortGradeSheetByCourseId(gradesheet);
    List sport_list=returnSportList(gradesheet);
    printCleanSheetGradesFromGradeSheet(sport_list,non_sport_list,
    		output_channel);
    listDestroy(non_sport_list);
    listDestroy(sport_courses);
    setDestroy(non_sport_courses);
    freeGradeSheet(gradesheet);
}


List returnCourseList(Semester semester){
    return semester->courses;
}

int returnSemeserNumber(Semester semester){
    assert(semester!=NULL);
    return semester->number;
}


void printHighestGradesFromList(int amount,List semesters,FILE* output_channel){
    assert(semesters != NULL);
    GradeSheetResult result_two;
    List sport_courses=listCreate(copyCourseWithNumber,freeCourseWithNumber);
    assert(sport_courses!=NULL);
    Set non_sport_courses=setCreate(copyCourseWithNumber,freeCourseWithNumber,
    		compareCoursesInSet);
    assert(non_sport_courses!=NULL);
    GradeSheet gradesheet=createGradeSheet(non_sport_courses,sport_courses,
    		&result_two);
    assert(gradesheet!=NULL);
    addRelevantCoursesToGradeSheet(semesters,gradesheet);
    List non_sport_list=sortGradeSheetByHighGrades(gradesheet);
    List sport_list=returnSportList(gradesheet);
    printHighestGradesFromGradeSheet(sport_list,non_sport_list,output_channel,
    		amount);
    listDestroy(non_sport_list);
    listDestroy(sport_courses);
    setDestroy(non_sport_courses);
    freeGradeSheet(gradesheet);
}


void printLowestGradesFromList(int amount,List semesters, FILE* output_channel){
    assert(semesters != NULL);
    GradeSheetResult result_two;
    List sport_courses=listCreate(copyCourseWithNumber,freeCourseWithNumber);
    assert(sport_courses!=NULL);
    Set non_sport_courses=setCreate(copyCourseWithNumber,freeCourseWithNumber,
    		compareCoursesInSet);
    assert(non_sport_courses!=NULL);
    GradeSheet gradesheet=createGradeSheet(non_sport_courses,sport_courses,
    		&result_two);
    assert(gradesheet!=NULL);
    addRelevantCoursesToGradeSheet(semesters,gradesheet);
    List non_sport_list=sortGradeSheetByLowerGrades(gradesheet);
    List sport_list=returnSportList(gradesheet);
    printLowestGradesFromGradeSheet(sport_list,non_sport_list,output_channel,
    		amount);
    listDestroy(non_sport_list);
    listDestroy(sport_courses);
    setDestroy(non_sport_courses);
    freeGradeSheet(gradesheet);
}


