#include "Grade.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "test_utilities.h"

static bool checkCopyGrade() {
    GradeResult result;
    ASSERT_TEST(copyGrade(NULL) == NULL);
    Grade check=CreateGrade(100,&result);
    ListElement check2=copyGrade((ListElement)check);
    ASSERT_TEST(CompareGrades(check,(Grade)check2,&result)==0);
    free(check);
    free(check2);
    return true;
}
static bool checkCompareGrades(){
    GradeResult result;
    GradeResult* ptr=&result;
    Grade check=CreateGrade(50,ptr);
    Grade checkNULL=NULL;
    Grade check3=CreateGrade(70,ptr);
    Grade check4=CreateGrade(70,ptr);
    ASSERT_TEST(CompareGrades(checkNULL,check,ptr)==-1);
    ASSERT_TEST(*ptr==GRADE_NULL_ARGUMENT);
    ASSERT_TEST(CompareGrades(check,checkNULL,ptr)==-1);
    ASSERT_TEST(*ptr==GRADE_NULL_ARGUMENT);
    ASSERT_TEST(CompareGrades(check3,check,ptr)==1);
    ASSERT_TEST(CompareGrades(check,check3,ptr)==2);
    ASSERT_TEST(CompareGrades(check3,check4,ptr)==0);
    free(check);
    free(check3);
    free(check4);
    return true;
}


static bool checkCreateGrade(){
    GradeResult result;
    ASSERT_TEST(CreateGrade(105,&result)==NULL);
    ASSERT_TEST(result==GRADE_ILLEGAL_GRADE);
    ASSERT_TEST(CreateGrade(-50,&result)==NULL);
    ASSERT_TEST(result==GRADE_ILLEGAL_GRADE);
    Grade check=CreateGrade(50,&result);
    ASSERT_TEST(check!=NULL);
    ASSERT_TEST(result==GRADE_SUCCESS);
    free(check);
    return true;
}

static bool checkRemoveLastGrade(){
    List Grades=listCreate(copyGrade,freeGrade);
    GradeResult result;
    Grade grade_one=CreateGrade(50,&result);
    ASSERT_TEST(removeLastGrade(Grades)==false);
    listInsertFirst(Grades,(ListElement)grade_one);
    ASSERT_TEST(removeLastGrade(Grades)==2);
    freeGrade(grade_one);
    listDestroy(Grades);
    return true;

}

static bool checkUpdateLastGrade(){
    List grades=listCreate(copyGrade,freeGrade);
    GradeResult result;
    Grade grade_one=CreateGrade(50,&result);
    ASSERT_TEST(updateLastGrade(grades,60)==false);
    listInsertFirst(grades,(ListElement)grade_one);
    ASSERT_TEST(updateLastGrade(grades,80)==true);
    listDestroy(grades);
    freeGrade(grade_one);
    return true;

}

static bool checkPrintGradeListFromLastToFirst(){
    FILE* output_channel=fopen("check_two","w");
    assert(output_channel != NULL);
    GradeResult result;
    List Grades=listCreate(copyGrade,freeGrade);
    Grade grade_one=CreateGrade(60,&result);
    Grade grade_two=CreateGrade(50,&result);
    Grade grade_three=CreateGrade(70,&result);
    printGradeListFromLastToFirst(Grades,output_channel,30000,7);
    listInsertFirst(Grades,(ListElement)grade_one);
    listInsertFirst(Grades,(ListElement)grade_two);
    listInsertLast(Grades,(ListElement)grade_three);
    printGradeListFromLastToFirst(Grades,output_channel,40000,7);
    freeGrade(grade_one);
    freeGrade(grade_two);
    freeGrade(grade_three);
    listDestroy(Grades);
    fclose(output_channel);
    return true;
}
static bool checkCheckIfPassed(){
    GradeResult result;
    Grade one=CreateGrade(55,&result);
    Grade two=CreateGrade(32,&result);
    ASSERT_TEST(checkIfPassed(one)==true);
    ASSERT_TEST(checkIfPassed(two)==false);
    freeGrade(one);
    freeGrade(two);
    return true;

}
static bool checkCountFailedGrades(){
    GradeResult result;
    Grade one=CreateGrade(55,&result);
    Grade two=CreateGrade(32,&result);
    List Grades=listCreate(copyGrade,freeGrade);
    listInsertFirst(Grades,(ListElement)one);
    listInsertFirst(Grades,(ListElement)two);
    int failed_grades=countFaildGrades(Grades);
    ASSERT_TEST(failed_grades==1);
    freeGrade(one);
    freeGrade(two);
    listDestroy(Grades);
    return true;

}

static bool checkGetEffectiveGrades(){
    GradeResult result;
    Grade one=CreateGrade(55,&result);
    Grade two=CreateGrade(32,&result);
    List Grades=listCreate(copyGrade,freeGrade);
    listInsertFirst(Grades,(ListElement)one);
    listInsertFirst(Grades,(ListElement)two);
    int effective_grade=getEffectiveGrade(Grades);
    ASSERT_TEST(effective_grade==55);
    freeGrade(one);
    freeGrade(two);
    listDestroy(Grades);
    return true;
}

int main(){

    RUN_TEST(checkCopyGrade);
    RUN_TEST(checkCompareGrades);
    RUN_TEST(checkCreateGrade);
    RUN_TEST(checkRemoveLastGrade);
    RUN_TEST(checkUpdateLastGrade);
    RUN_TEST(checkPrintGradeListFromLastToFirst);
    RUN_TEST(checkCheckIfPassed);
    RUN_TEST(checkCountFailedGrades);
    RUN_TEST(checkGetEffectiveGrades);
}
