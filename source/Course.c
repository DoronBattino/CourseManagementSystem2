#include <stdio.h>
#include "Grade.h"
#include "list.h"
#include "Course.h"
#include "Semester.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>



struct course{
    char* points;
    int course_id;
    List grades;
};


int getCourseID(Course course){
    return course->course_id;
}

List getGradesList(Course course){
    if(!course) return NULL;
    return course->grades;
}


bool checkCourseId(int course_id) {
    return (course_id > 0 && course_id < 1000000) ? true : false;
}

bool checkLegalPointNumber(char* points){
    if(points==NULL){
        return false;
    }
    int i=0;
    for(;points[i]!='\0';i++) {
        if ((!(points[i] >= '0' && points[i] <= '9')) && !(points[i] == '.')){
            return false;
        }
        if (points[i] == '.') {
        	if(i==0){
        		return false;
        	}
            if ((points[i + 1] != '5' && points[i + 1] != '0')) {
                return false;
            }
            if(points[i+2]!='\0'){
                return false;
            }
            return true;
        }
    }
    return true;
}
ListElement createCourse(char* points, int course_id, List Grades,
		CourseResult* result){
    if(Grades==NULL || points==NULL){
        *result=COURSE_NULL_ARGUMENT;
        return NULL;
    }
    if(!(checkLegalPointNumber(points))){
        *result=CORUSE_ILLEGAL_ARGUMENT;
        return NULL;

    }
    if(course_id<0 || course_id>=1000000){
        *result=CORUSE_ILLEGAL_ARGUMENT;
        return NULL;
    }
    Course new_course=malloc(sizeof(*new_course));
    if(new_course==NULL){
        return NULL;
    }
    new_course->points=malloc(sizeof(char)*(strlen(points)+1));
    if(new_course->points==NULL) {
        free(new_course);
        return NULL;
    }
    new_course->grades=listCopy(Grades);
    if(new_course->grades==NULL){
        free(new_course->points);
        free(new_course);
        return NULL;
    }
    new_course->points=strcpy(new_course->points,points);
    new_course->course_id=course_id;
    return new_course;

}

ListElement copyCourse(ListElement course){
    if(course==NULL){
        return NULL;
    }
    Course copy=malloc(sizeof(*copy));
    if(copy==NULL){
        return NULL;
    }
    Course cast=(Course)course;
    copy->points=malloc(sizeof(strlen(cast->points)+1));
    if(copy->points==NULL) {
        free(copy);
        return NULL;
    }
    strcpy(copy->points,cast->points);
    copy->course_id=cast->course_id;
    copy->grades=listCopy(cast->grades);
    if(copy->grades==NULL){
        free(copy->points);
        free(copy);
        return NULL;
    }

    return copy;
}


int compareCourses(SetElement course,SetElement course_two){
    assert(course!=NULL && course_two!=NULL);
    Course cast_one=(Course)course;
    Course cast_two=(Course)course_two;
    if(cast_one->course_id>cast_two->course_id){
        return 1;
    }
    if(cast_one->course_id==cast_two->course_id){
        return 0;

    }
    return -1;
}


int compareCoursesInList(ListElement course,ListElement course_two,
		ListSortKey key){
    (void)key;
    assert(course!=NULL && course_two!=NULL);
    Course cast_one=(Course)course;
    Course cast_two=(Course)course_two;
    if(cast_one->course_id>cast_two->course_id){
        return 1;
    }
    if(cast_one->course_id==cast_two->course_id){
        return 0;

    }
    return -1;
}






CourseResult addCourse(List courses, int course_id, char* points, int grade){
    if(!checkLegalPointNumber(points) || !checkCourseId(course_id) ||
    		courses==NULL || !checkGrade(grade)){
        return CORUSE_ILLEGAL_ARGUMENT;
    }
    ListResult result;
    GradeResult result2;
    CourseResult result3;
    Grade new_grade=CreateGrade(grade,&result2);
    if(new_grade==NULL){
        return COURSE_OUT_OF_MEMORY;
    }

    List Grades=listCreate(copyGrade, freeGrade);
    if(Grades==NULL){
        freeGrade(new_grade);
        return COURSE_OUT_OF_MEMORY;
    }

    result=listInsertFirst(Grades,(ListElement)new_grade);
    if(result!=LIST_SUCCESS){
        freeGrade((ListElement )new_grade);
        listDestroy(Grades);
        return COURSE_OUT_OF_MEMORY;
    }
    Course new_course=createCourse(points,course_id,Grades,&result3);
    if(new_course==NULL){
        freeGrade((ListElement)new_grade);
        listDestroy(Grades);
        return COURSE_OUT_OF_MEMORY;
    }

    result=listInsertLast(courses,(ListElement)new_course);
    if(result!=LIST_SUCCESS){
        freeCourse(new_course);
        return COURSE_OUT_OF_MEMORY;
    }
    listDestroy(Grades);
    freeGrade(new_grade);
    freeCourse(new_course);
    return COURSE_SUCCESS;
}

int removeCourseFromList(List courses, int course_id){
    if(!checkCourseId(course_id)){
        return 0;
    }
    LIST_FOREACH(Course,iterator,courses){
        if(course_id==iterator->course_id){
            if(!listGetSize(iterator->grades)){
                    return 0;
            }
            int check=removeLastGrade(iterator->grades);
			if(check==2){
            	listRemoveCurrent(courses);
                return 2;

            }
			if(check==1){
				return 1;
			}
			else return 0;
        }
    }
    return 0;

}


bool updateCourseInList(List courses, int course_id, int new_grade){
    if(!checkCourseId(course_id)){
        return false;
    }
    LIST_FOREACH(Course,iterator,courses){
        if(course_id==iterator->course_id){
            if(!listGetSize(iterator->grades)){
                return false;
            }
            if(updateLastGrade(iterator->grades,new_grade)){
                return true;

            }
            return false;
        }
    }
    return false;

}

bool updateCourse(Course course, int new_grade){
	if(course==NULL) return false;
	if(!listGetSize(course->grades)){
	    return false;
	 }
    if(updateLastGrade(course->grades,new_grade)){
    	return true;
    }
    return false;
}

long int pointsToNumer(char* points){
	assert(points!=NULL);
    int add_if_dot=0;
    char* ptr;
    for(int i=0;points[i]!='\0';i++){
        if(points[i]=='.' && points[i+1]!='0'){
            add_if_dot++;

        }
    }
    long int number=strtol(points,&ptr,10);
    return number*2+add_if_dot;
}


void printCourseGradesFromLastToFirst(List courses, FILE* output_channel){
    assert(courses!=NULL);
    int size=listGetSize(courses);
    while(size>0){
        int number=1;
        LIST_FOREACH(Course,iterator,courses){
            if(number==size){
                int points_number=pointsToNumer(iterator->points);
                printGradeListFromLastToFirst(iterator->grades,output_channel,
                		iterator->course_id,points_number);
            }
            number++;
        }
        size--;
    }
}





void printCourseGradesFromFirstToLast(List courses, FILE* output_channel){
    assert(courses!=NULL);
        LIST_FOREACH(Course,iterator,courses){
            int points_number=pointsToNumer(iterator->points);
            printGradeListFromFirstToLast(iterator->grades,output_channel,
            		iterator->course_id,points_number);
        }
}


void printCleanSheetGradesFromFirstTolast(List courses, FILE* output_channel){
    assert(courses!=NULL);
        LIST_FOREACH(Course,iterator,courses){
                int points_number=pointsToNumer(iterator->points);
                int grade=getEffectiveGrade(iterator->grades);
                ex3PrintGradeInfo(output_channel,iterator->course_id,
                		points_number,grade);
        }
}




void freeCourse(ListElement course){
    Course cast=(Course)course;
    listDestroy(cast->grades);
    free(cast->points);
    free(cast);
}


int returnNumberOfPoints(Course course){
    int number=pointsToNumer(course->points);
    return number;
}

int returnEffectiveGradeOfCourse(Course course){
    int grade=getEffectiveGrade(course->grades);
    return grade;
}


int numberOfTotalPoints(List courses){
    assert(courses!=NULL);
    int size,course_total;
    int total_points=0;
    LIST_FOREACH(Course,iterator,courses){
        size=listGetSize(iterator->grades);
        course_total=size*pointsToNumer(iterator->points);
        total_points+=course_total;
    }
    return total_points;
}

int numberOfFailedPoints(List courses){
	assert(courses!=NULL);
    int failed_grades_number;
    int course_total;
    int total_points=0;
    LIST_FOREACH(Course,iterator,courses){
        failed_grades_number=countFaildGrades(iterator->grades);
        course_total=failed_grades_number*pointsToNumer(iterator->points);
        total_points+=course_total;
    }
    return total_points;
}

int numberOfEffectivePoints(List courses){
	int total_points=0;
	Set relevant_for_semester=setCreate(copyCourse,freeCourse,compareCourses);
	assert(relevant_for_semester!=NULL);
    LIST_FOREACH(Course,iterator,courses){
    	List copy=listCopy(courses);
    	Course check=checkForLatestCourseApperance(copy,iterator);
        setAdd(relevant_for_semester,(SetElement)check);
        listDestroy(copy);
    }
    SET_FOREACH(Course,iterator,relevant_for_semester){
    	total_points+=pointsToNumer(iterator->points);
    }
    setDestroy(relevant_for_semester);
    return total_points;
}

int effectiveGradeSum(List courses){
    int effective_grade=0;
    int effective_grade_sum=0;
	Set relevant_for_semester=setCreate(copyCourse,freeCourse,compareCourses);
	assert(relevant_for_semester!=NULL);
	LIST_FOREACH(Course,iterator,courses){
	    	List copy=listCopy(courses);
	    	Course check=checkForLatestCourseApperance(copy,iterator);
	        setAdd(relevant_for_semester,(SetElement)check);
	        listDestroy(copy);
	}
    SET_FOREACH(Course,iterator,relevant_for_semester){
    	effective_grade=getEffectiveGrade(iterator->grades);
    	effective_grade_sum+=effective_grade*pointsToNumer(iterator->points);
    }
    setDestroy(relevant_for_semester);
    return effective_grade_sum;
}


int caculatesEffectivePointsInNonSportCourseSet(Set courses){
    assert(courses!=NULL);
    int course_points;
    int total_points=0;
    SET_FOREACH(CourseWithNumber,iterator,courses){
        Course course=returnCoursefromCourseWithNumber(iterator);
        course_points=pointsToNumer(course->points);
        total_points+=course_points;
    }
    return total_points;

}

int caculatesEffectivePointsInSportCourseList(List sport_courses){
    assert(sport_courses!=NULL);
    int course_points;
    int total_points=0;
    LIST_FOREACH(CourseWithNumber ,iterator,sport_courses){
        Course course=returnCoursefromCourseWithNumber(iterator);
        course_points=pointsToNumer(course->points);
        total_points+=course_points;
    }
    return total_points;

}


int caculatesEffectiveGradeSumInNonSportCourseSet(Set courses){
    assert(courses!=NULL);
    int course_sum;
    int course_effective_grade;
    int course_points;
    int total_sum=0;
    SET_FOREACH(CourseWithNumber,iterator,courses){
        Course course=returnCoursefromCourseWithNumber(iterator);
        course_points=pointsToNumer(course->points);
        course_effective_grade=getEffectiveGrade(course->grades);
        course_sum=course_points*course_effective_grade;
        total_sum+=course_sum;
    }
    return total_sum;
}

int caculatesEffectiveGradeSumInNonSportCourseList(List courses){
    assert(courses!=NULL);
    int course_sum;
    int course_effective_grade;
    int course_points;
    int total_sum=0;
    LIST_FOREACH(CourseWithNumber,iterator,courses){
        Course course=returnCoursefromCourseWithNumber(iterator);
        course_points=pointsToNumer(course->points);
        course_effective_grade=getEffectiveGrade(course->grades);
        course_sum=course_points*course_effective_grade;
        total_sum+=course_sum;
    }
    return total_sum;
}



int caculatesEffectiveGradeSumInSportCourseList(List sport_courses){
    assert(sport_courses!=NULL);
    int course_sum;
    int course_effective_grade;
    int course_points;
    int total_sum=0;
    LIST_FOREACH(CourseWithNumber ,iterator,sport_courses){
        Course course=returnCoursefromCourseWithNumber(iterator);
        course_points=pointsToNumer(course->points);
        course_effective_grade=getEffectiveGrade(course->grades);
        course_sum=course_points*course_effective_grade;
        total_sum+=course_sum;
    }
    return total_sum;
}



bool checksIfASportCourse(Course course){
    if(course->course_id>=390000 && course->course_id<=399999){
        return true;
    }
    else return false;
}



Course checkForLatestCourseApperance(List courses, Course course) {
    assert(courses!=NULL && course!=NULL);
    Course latest_time = checkForLatestIdAppearence(courses, course->course_id);
    return latest_time;
}


Course checkForLatestIdAppearence(List courses,int course_id){
    assert(courses!=NULL);
    Course latest_time=NULL;
    LIST_FOREACH(Course,iterator,courses){
        if(iterator->course_id==course_id){
            latest_time=iterator;
        }
    }
    return latest_time;
}

int returnCourseId(Course course){
    return course->course_id;
}
