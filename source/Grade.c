#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "list.h"
#include "Grade.h"
#include "ex3.h"


struct grade{
    int grade;
};


Grade CreateGrade(int grade, GradeResult* result){
    if(grade<0 || grade>100){
        *result=GRADE_ILLEGAL_GRADE;
        return NULL;
    }
    Grade new_grade=malloc(sizeof(*new_grade));
    if(new_grade==NULL){
        *result=GRADE_OUT_OF_MEMORY;
        return NULL;
    }
    new_grade->grade=grade;
    *result=GRADE_SUCCESS;
    return new_grade;
}

int CompareGrades(Grade one, Grade two, GradeResult* result){
    if(one== NULL || two == NULL){
        *result=GRADE_NULL_ARGUMENT;
        return -1;
    }
    if(one->grade==two->grade){
        return 0;
    }
    else return one->grade>two->grade ? 1 : 2;
}

ListElement copyGrade(ListElement Grades){
    if(Grades==NULL){
        return NULL;
    }
    Grade newGrade=malloc(sizeof(*newGrade));
    if(newGrade==NULL){
        return NULL;
    }
    Grade cast;
    cast=(Grade)Grades;
    newGrade->grade=cast->grade;
    return newGrade;
}
void freeGrade(ListElement Grade){
    free(Grade);
}

bool checkGrade(int grade){
    return (grade>=0 && grade<=100) ? true : false;
}

int removeLastGrade(List Grades){
    int size=listGetSize(Grades);
    LIST_FOREACH(Grade,iterator,Grades){
        if(size==1){
           ListResult result=listRemoveCurrent(Grades);
           if(result==LIST_SUCCESS) {
        	   size=listGetSize(Grades);
        	   if(size==0){
        		   return 2;
        	   }
               return 1;
           }
           return 0;
        }
        size--;
    }
    return 0;
}

bool updateLastGrade(List Grades, int new_grade){
	if(!Grades) return false;
    int size=listGetSize(Grades);
    LIST_FOREACH(Grade,iterator,Grades){
        if(size==1) {
            Grade newGrade = listGetCurrent(Grades);
            newGrade->grade = new_grade;
            return true;
        }
        size--;
    }
    return false;
}

bool checkIfPassed(Grade grade){
    return (grade->grade>=55) ? true : false;
}


int returnGrade(Grade grade){
    return (grade->grade);
}

void printGradeListFromLastToFirst(List Grades,FILE* output_channel,
		int course_id, int points_x2){
    assert(Grades!=NULL);
    int size=listGetSize(Grades);
    while(size>0){
        int number=1;
        LIST_FOREACH(Grade,iterator,Grades){

            if(number==size){
                ex3PrintGradeInfo(output_channel,course_id,points_x2,
                		iterator->grade);
            }
            number++;
        }
        size--;
    }
}


void printGradeListFromFirstToLast(List Grades,FILE* output_channel,
		int course_id, int points_x2){
    assert(Grades!=NULL);
    LIST_FOREACH(Grade,iterator,Grades){
        ex3PrintGradeInfo(output_channel,course_id,points_x2,iterator->grade);
    }
}

int countFaildGrades(List Grades){
    assert(Grades!=NULL);
    int failed_grades=0;
    LIST_FOREACH(Grade,iterator,Grades){
        if(!checkIfPassed(iterator)){
            failed_grades++;
        }
    }
    return failed_grades;
}

int getEffectiveGrade(List Grades){
    assert(Grades!=NULL);
    int size=listGetSize(Grades);
    int effective_grade=0;
    LIST_FOREACH(Grade,iterator,Grades){
        effective_grade=iterator->grade;
        if(size==1){
            return effective_grade;
        }
        size--;
    }
    return effective_grade;
}


int getGrade(Grade grade){
    return grade->grade;
}
