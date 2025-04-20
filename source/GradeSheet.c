#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "Semester.h"
#include "GradeSheet.h"
#include "Grade.h"
#include "Course.h"
#include "list.h"
#include "set.h"


struct course_with_number{
    Course course;
    int semester_number;
};

struct gradesheet{
    Set non_sport_courses;
    List sport_courses;
};

GradeSheet createGradeSheet(Set non_sport_courses,List sport_courses,
		GradeSheetResult* result){
    if(non_sport_courses==NULL || sport_courses==NULL){
        *result=GRADESHEET_NULL_ARGUMENT;
        return NULL;
    }
    GradeSheet new_grade_sheet=malloc(sizeof(*new_grade_sheet));
    if(new_grade_sheet==NULL){
        *result=GRADESHEET_OUT_OF_MEMORY;
        return NULL;
    }
    new_grade_sheet->non_sport_courses=setCopy(non_sport_courses);
    if(new_grade_sheet->non_sport_courses==NULL){
        free(new_grade_sheet);
        return NULL;
    }
    new_grade_sheet->sport_courses=listCopy(sport_courses);
    if(new_grade_sheet->sport_courses==NULL){
        setDestroy(new_grade_sheet->non_sport_courses);
        free(new_grade_sheet);
        *result=GRADESHEET_OUT_OF_MEMORY;
        return NULL;
    }
    return new_grade_sheet;
}

CourseWithNumber createCourseWithNumber(Course course, int semeter_number){
    if(course==NULL){
        return NULL;
    }
    CourseWithNumber course_with_number=malloc(sizeof(*course_with_number));
    assert(course_with_number!=NULL);
    course_with_number->course=copyCourse(course);
    assert(course_with_number->course!=NULL);
    course_with_number->semester_number=semeter_number;
    return course_with_number;
}

void freeCourseWithNumber(ListElement course){
    CourseWithNumber cast=( CourseWithNumber)course;
    freeCourse(cast->course);
    free(course);
}


ListElement copyCourseWithNumber(ListElement course_with_number){
    if(course_with_number==NULL){
        return NULL;
    }
    CourseWithNumber copy=malloc(sizeof(*copy));
    if(copy==NULL){
        return NULL;
    }
    CourseWithNumber cast=(CourseWithNumber)course_with_number;
    copy->course=copyCourse(cast->course);
    if(copy->course==NULL){
        free(copy);
        return NULL;
    }
    copy->semester_number=cast->semester_number;
    return copy;
}

int returnCourseIdofCourseWithNumber(CourseWithNumber course){
    int course_id=returnCourseId(course->course);
    return course_id;
}

int returnSemesterNumberOfCourseWithNumber(CourseWithNumber course){
    return course->semester_number;
}

int returnApplyGradeOfCourse(CourseWithNumber course) {
    int grade = returnEffectiveGradeOfCourse(course->course);
    return grade;
}

int compareCoursesWithNumber(SetElement course_one,ListElement course_two,
		ListSortKey key){
    (void)key;
    int course_id_one=returnCourseIdofCourseWithNumber(course_one);

    int course_id_two=returnCourseIdofCourseWithNumber(course_two);

    if(course_id_one>course_id_two){
        return 1;
    }
    if(course_id_two>course_id_one){
        return -1;
    }
    if(course_id_one==course_id_two){
        int number=returnSemesterNumberOfCourseWithNumber(course_one);
        int number_two=returnSemesterNumberOfCourseWithNumber(course_two);
        if(number<number_two){
            return -1;
        }
        else return 1;
    }
    return 0;
}


int compareCoursesInSet(SetElement course_one,SetElement course_two){
    int course_id_one=returnCourseIdofCourseWithNumber(course_one);

    int course_id_two=returnCourseIdofCourseWithNumber(course_two);

    if(course_id_one>course_id_two){
        return 1;
    }
    if(course_id_two>course_id_one){
        return -1;
    }
    else return 0;
}



int compareCoursesByHighGrades(ListElement course_one,ListElement course_two,
		ListSortKey key) {
    (void)key;
    int number = returnSemesterNumberOfCourseWithNumber(course_one);
    int number_two = returnSemesterNumberOfCourseWithNumber(course_two);
    int course_id_one = returnCourseIdofCourseWithNumber(course_one);
    int course_id_two = returnCourseIdofCourseWithNumber(course_two);
    int grade_one = returnApplyGradeOfCourse(course_one);
    int grade_two = returnApplyGradeOfCourse(course_two);
    if (grade_one > grade_two) {
        return -1;
    }
    if (grade_two > grade_one) {
        return 1;
    } else {
        if (number < number_two) {
            return -1;
        }
        if (number_two < number) {
            return 1;
        }
        if (course_id_one < course_id_two) {
            return -1;
        }
        if (course_id_two < course_id_one) {
            return 1;
        }
    }
    return 0;
}

int compareCoursesByLowerGrades(ListElement course_one,ListElement course_two,
		ListSortKey key) {
    (void)key;
    int number =returnSemesterNumberOfCourseWithNumber(course_one);
    int number_two = returnSemesterNumberOfCourseWithNumber(course_two);
    int course_id_one = returnCourseIdofCourseWithNumber(course_one);
    int course_id_two = returnCourseIdofCourseWithNumber(course_two);
    int grade_one = returnApplyGradeOfCourse(course_one);
    int grade_two = returnApplyGradeOfCourse(course_two);
    if (grade_one > grade_two) {
        return 1;
    }
    if (grade_two > grade_one) {
        return -1;
    } else {
        if (number < number_two) {
            return -1;
        }
        if (number_two < number) {
            return 1;
        }
        if (course_id_one < course_id_two) {
            return -1;
        }
        if (course_id_two < course_id_one) {
            return 1;
        }
    }
    return 0;
}


    ListElement copyGradeSheet(ListElement gradesheet){
    if(gradesheet==NULL){
        return NULL;
    }
    GradeSheet copy=malloc(sizeof(*copy));
    if(copy==NULL){
        return NULL;
    }
    GradeSheet cast=(GradeSheet)gradesheet;
    copy->non_sport_courses=setCopy(cast->non_sport_courses);
    if(copy->non_sport_courses==NULL){
        free(copy);
        return NULL;
    }
    copy->sport_courses=listCopy(cast->sport_courses);
    if(copy->sport_courses==NULL){
        setDestroy(copy->non_sport_courses);
        free(copy);
        return NULL;
    }
    return copy;
}

void freeGradeSheet(GradeSheet gradesheet){
    setDestroy(gradesheet->non_sport_courses);
    listDestroy(gradesheet->sport_courses);
    free(gradesheet);
}


GradeSheetResult addNonSportToGradeSheet(GradeSheet gradesheet,Course course,
		int semester_number){
    assert(gradesheet!=NULL && course!=NULL);
    CourseWithNumber non_sport_course=createCourseWithNumber(course,
    		semester_number);
    if(non_sport_course==NULL){
        return GRADESHEET_OUT_OF_MEMORY;
    }
    SetResult result;
    result = setAdd(gradesheet->non_sport_courses,(SetElement)non_sport_course);
    if (result != SET_SUCCESS) {
        freeCourseWithNumber(non_sport_course);
        return GRADESHEET_GRADE_EXISTS_ALREADY;
    }
    freeCourseWithNumber(non_sport_course);
    return GRADESHEET_SUCCESS;
}


GradeSheetResult addSportCourseToGradeSheet(GradeSheet gradesheet,Course course,
		int semester_number){
    assert(gradesheet!=NULL && course!=NULL);
    CourseWithNumber sport_course=createCourseWithNumber(course,
    		semester_number);
    if(sport_course==NULL){
        return GRADESHEET_OUT_OF_MEMORY;
    }
    listInsertLast(gradesheet->sport_courses,(ListElement)sport_course);
    freeCourseWithNumber(sport_course);
    return GRADESHEET_SUCCESS;
}


int caculatesPointsInGradeSheet(GradeSheet gradesheet){
    assert(gradesheet!=NULL);
    int non_sport_points=
    caculatesEffectivePointsInNonSportCourseSet(gradesheet->non_sport_courses);
    int sport_courses_points=
    	caculatesEffectivePointsInSportCourseList(gradesheet->sport_courses);
    return non_sport_points+sport_courses_points;
}

int caculatesEffectiveGradeSumInGradeSheet(GradeSheet gradesheet){
    assert(gradesheet!=NULL);
    int non_sport_grade_sum=
    caculatesEffectiveGradeSumInNonSportCourseSet(gradesheet->non_sport_courses);
    int sport_grade_Sum=
    	caculatesEffectiveGradeSumInSportCourseList(gradesheet->sport_courses);
    return non_sport_grade_sum+sport_grade_Sum;
}


CourseWithNumber returnSportCourseFromGradeSheet(GradeSheet gradesheet){
    LIST_FOREACH(CourseWithNumber,iterator,gradesheet->sport_courses){
        return iterator;
    }
    return NULL;
}

Course returnNonSportCourseFromGradeSheet(GradeSheet gradesheet){
    SET_FOREACH(Course,iterator,gradesheet->non_sport_courses){
        return iterator;
    }
    return NULL;
}


void printgradeSheetCourseId(GradeSheet gradesheet){
    LIST_FOREACH(CourseWithNumber,iterator,gradesheet->sport_courses){
        printf("sport course id is %d\n",
        		returnCourseIdofCourseWithNumber(iterator));
    }
    SET_FOREACH(CourseWithNumber ,iterator,gradesheet->non_sport_courses){
        printf("non sport course id is %d\n",
        		returnCourseIdofCourseWithNumber(iterator));
    }
}

List sortGradeSheetByCourseId(GradeSheet gradesheet){
    if(gradesheet==NULL){
        return NULL;
    }
    List sorted_non_sport_list=listCreate(copyCourseWithNumber,
    		freeCourseWithNumber);
    if(sorted_non_sport_list==NULL){
        return NULL;
    }
    ListSortKey key=0;
    listSort(gradesheet->sport_courses,compareCoursesInList,key);
    SET_FOREACH(CourseWithNumber,iterator,gradesheet->non_sport_courses){
        listInsertLast(sorted_non_sport_list,iterator);

    }
    listSort(sorted_non_sport_list,compareCoursesWithNumber,key);
    listSort(gradesheet->sport_courses,compareCoursesWithNumber,key);
    LIST_FOREACH(CourseWithNumber,iterator,gradesheet->sport_courses){
    }
    return sorted_non_sport_list;
}



List sortGradeSheetByHighGrades(GradeSheet gradesheet){
    if(gradesheet==NULL){
        return NULL;
    }
    List sorted_non_sport_list=listCreate(copyCourseWithNumber,
    		freeCourseWithNumber);
    if(sorted_non_sport_list==NULL){
        return NULL;
    }
    ListSortKey key=0;
    listSort(gradesheet->sport_courses,compareCoursesByHighGrades,key);


    SET_FOREACH(CourseWithNumber,iterator,gradesheet->non_sport_courses){
        listInsertLast(sorted_non_sport_list,iterator);
    }
    int size=listGetSize(sorted_non_sport_list);
    if(size<2){
        return sorted_non_sport_list;
    }
    listSort(sorted_non_sport_list,compareCoursesByHighGrades,key);
    return sorted_non_sport_list;
}


List sortGradeSheetByLowerGrades(GradeSheet gradesheet){
    if(gradesheet==NULL){
        return NULL;
    }
    List sorted_non_sport_list=listCreate(copyCourseWithNumber,
    		freeCourseWithNumber);
    if(sorted_non_sport_list==NULL){
        return NULL;
    }
    ListSortKey key=0;
    listSort(gradesheet->sport_courses,compareCoursesByLowerGrades,key);
    SET_FOREACH(CourseWithNumber,iterator,gradesheet->non_sport_courses){
        listInsertLast(sorted_non_sport_list,iterator);
    }
    int size=listGetSize(sorted_non_sport_list);
    if(size<2){
        return sorted_non_sport_list;
    }
    listSort(sorted_non_sport_list,compareCoursesByLowerGrades,key);
    return sorted_non_sport_list;
}



List returnSportList(GradeSheet gradesheet){
    assert(gradesheet!=NULL);
    return gradesheet->sport_courses;
}

void printCleanSheetGradesFromGradeSheet(List sport_list,List non_sport_list,
		FILE* output_channel){
    assert(output_channel!=NULL && sport_list!=NULL && non_sport_list!=NULL);
    CourseWithNumber iterator=NULL;
    CourseWithNumber iterator_two=NULL;
    iterator=listGetFirst(sport_list);
    iterator_two=listGetFirst(non_sport_list);
    while(iterator && iterator_two){
        int check=compareCoursesInList(iterator->course,iterator_two->course,0);
        if(check==-1){
            int points_number=returnNumberOfPoints(iterator->course);
            int grade=returnEffectiveGradeOfCourse(iterator->course);
            int course_id=returnCourseIdofCourseWithNumber(iterator);
            ex3PrintGradeInfo(output_channel,course_id,points_number,grade);
            iterator=listGetNext(sport_list);
        }
        if(check==1){
           int points_number=returnNumberOfPoints(iterator_two->course);
            int grade=returnEffectiveGradeOfCourse(iterator_two->course);
            int course_id=returnCourseId(iterator_two->course);
            ex3PrintGradeInfo(output_channel,course_id,points_number,grade);
            iterator_two=listGetNext(non_sport_list);
        }

    }
    if(iterator!=NULL) {
        while (iterator) {
            int points_number = returnNumberOfPoints(iterator->course);
            int grade = returnEffectiveGradeOfCourse(iterator->course);
            int course_id = returnCourseIdofCourseWithNumber(iterator);
            ex3PrintGradeInfo(output_channel, course_id, points_number, grade);
            iterator = listGetNext(sport_list);
        }
    }
    if(iterator_two!=NULL){
        while(iterator_two){
            int points_number=returnNumberOfPoints(iterator_two->course);
            int grade=returnEffectiveGradeOfCourse(iterator_two->course);
            int course_id=returnCourseId(iterator_two->course);
            ex3PrintGradeInfo(output_channel,course_id,points_number,grade);
            iterator_two=listGetNext(non_sport_list);
        }


    }
}




void printHighestGradesFromGradeSheet(List sport_list,List non_sport_list,
		FILE* output_channel,int amount){
    assert(output_channel!=NULL && sport_list!=NULL && non_sport_list!=NULL);
    CourseWithNumber iterator=NULL;
    CourseWithNumber iterator_two=NULL;
    iterator=listGetFirst(sport_list);
    iterator_two=listGetFirst(non_sport_list);
    while(iterator && iterator_two){
        int check=compareCoursesByHighGrades(iterator,iterator_two,0);
        if(check==-1){
            int points_number=returnNumberOfPoints(iterator->course);
            int grade=returnEffectiveGradeOfCourse(iterator->course);
            int course_id=returnCourseIdofCourseWithNumber(iterator);
            ex3PrintGradeInfo(output_channel,course_id,points_number,grade);
            iterator=listGetNext(sport_list);
            amount--;
            if(amount==0){
                return;
            }
        }
        if(check==1){
            int points_number=returnNumberOfPoints(iterator_two->course);
            int grade=returnEffectiveGradeOfCourse(iterator_two->course);
            int course_id=returnCourseIdofCourseWithNumber(iterator_two);
            ex3PrintGradeInfo(output_channel,course_id,points_number,grade);
            iterator_two=listGetNext(non_sport_list);
            amount--;
            if(amount==0){
                return;
            }
        }

    }
    if(iterator!=NULL) {
        while (iterator) {
            int points_number = returnNumberOfPoints(iterator->course);
            int grade = returnEffectiveGradeOfCourse(iterator->course);
            int course_id = returnCourseIdofCourseWithNumber(iterator);
            ex3PrintGradeInfo(output_channel, course_id, points_number, grade);
            iterator = listGetNext(sport_list);
            amount--;
            if(amount==0){
                return;
            }
        }
    }
    if(iterator_two!=NULL){
        while(iterator_two){
            int points_number=returnNumberOfPoints(iterator_two->course);
            int grade=returnEffectiveGradeOfCourse(iterator_two->course);
            int course_id=returnCourseIdofCourseWithNumber(iterator_two);
            ex3PrintGradeInfo(output_channel,course_id,points_number,grade);
            iterator_two=listGetNext(non_sport_list);
            amount--;
            if(amount==0){
                return;
            }
        }


    }
}


void printLowestGradesFromGradeSheet(List sport_list,List non_sport_list,
		FILE* output_channel,int amount){
    assert(output_channel!=NULL && sport_list!=NULL && non_sport_list!=NULL);
    CourseWithNumber iterator=NULL;
    CourseWithNumber iterator_two=NULL;
    iterator=listGetFirst(sport_list);
    iterator_two=listGetFirst(non_sport_list);
    while(iterator && iterator_two){
        int check=compareCoursesByLowerGrades(iterator,iterator_two,0);
        if(check==-1){
            int points_number=returnNumberOfPoints(iterator->course);
            int grade=returnEffectiveGradeOfCourse(iterator->course);
            int course_id=returnCourseIdofCourseWithNumber(iterator);
            ex3PrintGradeInfo(output_channel,course_id,points_number,grade);
            iterator=listGetNext(sport_list);
            amount--;
            if(amount==0){
                return;
            }
        }
        if(check==1){
            int points_number=returnNumberOfPoints(iterator_two->course);
            int grade=returnEffectiveGradeOfCourse(iterator_two->course);
            int course_id=returnCourseIdofCourseWithNumber(iterator_two);
            ex3PrintGradeInfo(output_channel,course_id,points_number,grade);
            iterator_two=listGetNext(non_sport_list);
            amount--;
            if(amount==0){
                return;
            }
        }

    }
    if(iterator!=NULL) {
        while (iterator) {
            int points_number = returnNumberOfPoints(iterator->course);
            int grade = returnEffectiveGradeOfCourse(iterator->course);
            int course_id = returnCourseIdofCourseWithNumber(iterator);
            ex3PrintGradeInfo(output_channel, course_id, points_number, grade);
            iterator = listGetNext(sport_list);
            amount--;
            if(amount==0){
                return;
            }
        }
    }
    if(iterator_two!=NULL){
        while(iterator_two){
            int points_number=returnNumberOfPoints(iterator_two->course);
            int grade=returnEffectiveGradeOfCourse(iterator_two->course);
            int course_id=returnCourseIdofCourseWithNumber(iterator_two);
            ex3PrintGradeInfo(output_channel,course_id,points_number,grade);
            iterator_two=listGetNext(non_sport_list);
            amount--;
            if(amount==0){
                return;
            }
        }


    }
}


Course returnCoursefromCourseWithNumber(CourseWithNumber course){
    assert(course!=NULL);
    return course->course;
}
