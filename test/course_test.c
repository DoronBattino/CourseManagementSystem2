#include "Grade.h"
#include "Course.h"
#include "test_utilities.h"

/**
 * List of tests, one for each function is usually a good thumb rule.
 */
/*
static Course generateCourse(int x){
    CourseResult result;
    CourseResult *ptr = &result;
    Course check1=NULL;
    List Grade;
    switch (x) {
        case 0:
            Grade = listCreate(copyGrade, freeGrade);
            check1 = createCourse(NULL, 5, Grade, ptr);
            return check1;
            break;
    }
    return check1;
}
 */
static bool testCreateCourse(){
    CourseResult result;
    CourseResult* ptr=&result;
    List Grade=listCreate(copyGrade,freeGrade);
    ASSERT_TEST(createCourse("0.5",5,NULL,ptr)==NULL);
    ASSERT_TEST(result==COURSE_NULL_ARGUMENT);
    ASSERT_TEST(createCourse(NULL,5,Grade,ptr)==NULL);
    ASSERT_TEST(result==COURSE_NULL_ARGUMENT);
    ASSERT_TEST(createCourse("a", 5,Grade,ptr)==NULL);
    ASSERT_TEST(result==CORUSE_ILLEGAL_ARGUMENT);
    ASSERT_TEST(createCourse("0.4", 5,Grade,ptr)==NULL);
    ASSERT_TEST(result==CORUSE_ILLEGAL_ARGUMENT);
    ASSERT_TEST(createCourse("0.5", -3,Grade,ptr)==NULL);
    ASSERT_TEST(result==CORUSE_ILLEGAL_ARGUMENT);
    ASSERT_TEST(createCourse("0.5", 1000000,Grade,ptr)==NULL);
    ASSERT_TEST(result==CORUSE_ILLEGAL_ARGUMENT);
    listDestroy(Grade);
    return true;
}

static bool testCheckLegalPointNumber(){
    ASSERT_TEST(checkLegalPointNumber("0.5")==true);
    ASSERT_TEST(checkLegalPointNumber("a")==false);
    ASSERT_TEST(checkLegalPointNumber("0.4")==false);
    ASSERT_TEST(checkLegalPointNumber("0.54")==false);
    ASSERT_TEST(checkLegalPointNumber(NULL)==false);
    return true;
}
static bool testCopyCourse(){
    CourseResult result;
    CourseResult *ptr = &result;
    List Grade=listCreate(copyGrade,freeGrade);
    Course check1=createCourse(NULL,5,Grade,ptr);
    ASSERT_TEST(copyCourse((ListElement)check1)==NULL);
    listDestroy(Grade);
    return true;
}

static bool testAddCourse(){
    List courses=listCreate(copyCourse, freeCourse);
    CourseResult result;
    ASSERT_TEST(addCourse(NULL,10,"0.5", 70)==CORUSE_ILLEGAL_ARGUMENT);
    ASSERT_TEST(addCourse(courses,10,"0.5", 150)== CORUSE_ILLEGAL_ARGUMENT);
    ASSERT_TEST(addCourse(courses,-3,"0.5", 70)== CORUSE_ILLEGAL_ARGUMENT);
    ASSERT_TEST(addCourse(courses,10,"0.4", 70)== CORUSE_ILLEGAL_ARGUMENT);
    result=addCourse(courses,10,"0.5", 70);
    ASSERT_TEST(result==COURSE_SUCCESS);
    result=addCourse(courses,10,"2.5", 80);
    ASSERT_TEST(result==COURSE_SUCCESS);
    result=addCourse(courses,10,"1.5", 77);
    ASSERT_TEST(result==COURSE_SUCCESS);
    ASSERT_TEST(listGetSize(courses)==3);
    listDestroy(courses);
    return true;

}


static bool testFreeCourse() {
    CourseResult result;
    List Grades = listCreate(copyGrade, freeGrade);
    char* points="0.5";
    Course check = createCourse(points, 10, Grades, &result);
    freeCourse((ListElement) check);
    listDestroy(Grades);
    return true;
}

static bool testRemoveCourseFromList(){
    List Grades=listCreate(copyGrade,freeGrade);
    List Grades_two=listCreate(copyGrade,freeGrade);
    GradeResult result;
    CourseResult result_two;
    List courses=listCreate(copyCourse,freeCourse);
    Grade grade_one=CreateGrade(50,&result);
    listInsertFirst(Grades,(ListElement)grade_one);
    Course course=createCourse("0.5", 1,Grades,&result_two);
    Course course_two=createCourse("0.5",2,Grades_two,&result_two);
    listInsertFirst(courses,(ListElement)course);
    ASSERT_TEST(removeCourseFromList(courses,1)==2);
    listInsertLast(courses,(ListElement)course_two);
    ASSERT_TEST(removeCourseFromList(courses,2)==false);
    freeGrade(grade_one);
    listDestroy(Grades);
    listDestroy(Grades_two);
    freeCourse(course);
    freeCourse(course_two);
    listDestroy(courses);
    return true;
}

static bool testUpdateCourseInList(){
    GradeResult result;
    CourseResult result_two;
    List Grades=listCreate(copyGrade,freeGrade);
    List courses=listCreate(copyCourse,freeCourse);
    Grade grade_one=CreateGrade(50,&result);
    Course course=createCourse("0.5", 1,Grades,&result_two);
    listInsertFirst(courses,(ListElement)course);
    ASSERT_TEST(updateCourseInList(courses,1,80)==false);
    listInsertFirst(Grades,(ListElement)grade_one);
    Course course_two=createCourse("0.5",2,Grades,&result_two);
    listInsertFirst(courses,(ListElement)course_two);
    ASSERT_TEST(updateCourseInList(courses,2,80)==true);
    freeGrade(grade_one);
    listDestroy(Grades);
    freeCourse(course);
    freeCourse(course_two);
    listDestroy(courses);
    return true;
}

static bool testPrintCourseGradesFromLastToFirst(){
    FILE* output_channel=fopen("check","w");
    assert(output_channel != NULL);
    GradeResult result;
    CourseResult result_two;
    List Grades=listCreate(copyGrade,freeGrade);
    List Courses=listCreate(copyCourse,freeCourse);
    Grade grade_one=CreateGrade(50,&result);
    Grade grade_two=CreateGrade(60,&result);
    listInsertFirst(Grades,(ListElement)grade_one);
    listInsertFirst(Grades,(ListElement)grade_two);
    Course course_one=createCourse("4",3,Grades,&result_two);
    Course course_two=createCourse("0.5", 12,Grades,&result_two);
    listInsertFirst(Courses,course_one);
    listInsertLast(Courses,course_two);
    printCourseGradesFromLastToFirst(Courses,output_channel);
    freeGrade(grade_one);
    freeGrade(grade_two);
    listDestroy(Grades);
    freeCourse(course_one);
    freeCourse(course_two);
    listDestroy(Courses);
    fclose(output_channel);
    return true;
}

static bool testPointsToNumber(){
    int number=pointsToNumer("0.5");
     ASSERT_TEST(number==1);
    return true;
}

static bool testNumerOfTotalPoints(){
    GradeResult result;
    CourseResult result_two;
    List Grades=listCreate(copyGrade,freeGrade);
    List Courses=listCreate(copyCourse,freeCourse);
    Grade grade_one=CreateGrade(50,&result);
    Grade grade_two=CreateGrade(60,&result);
    listInsertFirst(Grades,(ListElement)grade_one);
    listInsertFirst(Grades,(ListElement)grade_two);
    Course course_one=createCourse("4",3,Grades,&result_two);
    Course course_two=createCourse("0.5", 12,Grades,&result_two);
    listInsertFirst(Courses,course_one);
    listInsertLast(Courses,course_two);
    ASSERT_TEST(numberOfTotalPoints(Courses)==18);
    freeGrade(grade_one);
    freeGrade(grade_two);
    listDestroy(Grades);
    freeCourse(course_one);
    freeCourse(course_two);
    listDestroy(Courses);
    return true;


}

static bool testNumberofFailedPoints(){
    GradeResult result;
    CourseResult result_two;
    List Grades=listCreate(copyGrade,freeGrade);
    List Courses=listCreate(copyCourse,freeCourse);
    Grade grade_one=CreateGrade(50,&result);
    Grade grade_two=CreateGrade(60,&result);
    listInsertFirst(Grades,(ListElement)grade_one);
    listInsertFirst(Grades,(ListElement)grade_two);
    Course course_one=createCourse("4",3,Grades,&result_two);
    Course course_two=createCourse("0.5", 12,Grades,&result_two);
    listInsertFirst(Courses,course_one);
    listInsertLast(Courses,course_two);
    ASSERT_TEST(numberOfFailedPoints(Courses)==9);
    freeGrade(grade_one);
    freeGrade(grade_two);
    listDestroy(Grades);
    freeCourse(course_one);
    freeCourse(course_two);
    listDestroy(Courses);
    return true;
}


static bool testNumberOfEffectivePoints(){
    GradeResult result;
    CourseResult result_two;
    List Grades=listCreate(copyGrade,freeGrade);
    List Courses=listCreate(copyCourse,freeCourse);
    Grade grade_one=CreateGrade(50,&result);
    Grade grade_two=CreateGrade(60,&result);
    listInsertFirst(Grades,(ListElement)grade_one);
    listInsertFirst(Grades,(ListElement)grade_two);
    Course course_one=createCourse("4",3,Grades,&result_two);
    Course course_two=createCourse("0.5", 12,Grades,&result_two);
    listInsertFirst(Courses,course_one);
    listInsertLast(Courses,course_two);
    ASSERT_TEST(numberOfEffectivePoints(Courses)==9);
    freeGrade(grade_one);
    freeGrade(grade_two);
    listDestroy(Grades);
    freeCourse(course_one);
    freeCourse(course_two);
    listDestroy(Courses);
    return true;
}

static bool testEffectiveGradeSum(){
    GradeResult result;
    CourseResult result_two;
    List Grades=listCreate(copyGrade,freeGrade);
    List Courses=listCreate(copyCourse,freeCourse);
    Grade grade_one=CreateGrade(50,&result);
    Grade grade_two=CreateGrade(60,&result);
    listInsertFirst(Grades,(ListElement)grade_one);
    listInsertFirst(Grades,(ListElement)grade_two);
    Course course_one=createCourse("4",3,Grades,&result_two);
    Course course_two=createCourse("0.5", 12,Grades,&result_two);
    listInsertFirst(Courses,course_one);
    listInsertLast(Courses,course_two);
    ASSERT_TEST(effectiveGradeSum(Courses)==450);
    freeGrade(grade_one);
    freeGrade(grade_two);
    listDestroy(Grades);
    freeCourse(course_one);
    freeCourse(course_two);
    listDestroy(Courses);
    return true;

}

static bool testCheckIfSport(){
    CourseResult result_two;
    List Grades=listCreate(copyGrade,freeGrade);
    Course check=createCourse("0.5", 399999,Grades,&result_two);
    Course check_two=createCourse("0.5", 45,Grades,&result_two);
    ASSERT_TEST(checksIfASportCourse(check)==true);
    ASSERT_TEST(checksIfASportCourse(check_two)==false);
    listDestroy(Grades);
    freeCourse(check);
    freeCourse(check_two);
    return true;
}

static bool testCompareCourses() {
    CourseResult result_two;
    List Grades = listCreate(copyGrade, freeGrade);
    Course check = createCourse("0.5", 399999, Grades, &result_two);
    Course check_two = createCourse("0.5", 45, Grades, &result_two);
    Course check_three = createCourse("0.5", 45, Grades, &result_two);
    ASSERT_TEST(compareCourses(check, check_two) == 1);
    ASSERT_TEST(compareCourses(check_two, check) == -1);
    ASSERT_TEST(compareCourses(check_three, check_two) == 0);
    listDestroy(Grades);
    freeCourse(check);
    freeCourse(check_two);
    freeCourse(check_three);
    return true;

}

static bool testCheckForLatestIdAppearance(){
    CourseResult result_two;
    List Grades = listCreate(copyGrade, freeGrade);
    List Courses=listCreate(copyCourse,freeCourse);
    Course check = createCourse("0.5", 399999, Grades, &result_two);
    Course check_two = createCourse("0.5", 45, Grades, &result_two);
    Course check_three = createCourse("1", 45, Grades, &result_two);
    listInsertFirst(Courses,check);
    listInsertFirst(Courses,check_two);
    listInsertLast(Courses,check_three);
    Course last_appearance=checkForLatestIdAppearence(Courses,45);
    ASSERT_TEST(compareCourses(last_appearance,check_three)==0);
    listDestroy(Grades);
    freeCourse(check);
    freeCourse(check_two);
    freeCourse(check_three);
    listDestroy(Courses);
    return true;

}


int main(){
    RUN_TEST(testCreateCourse);
    RUN_TEST(testCheckLegalPointNumber);
    RUN_TEST(testCopyCourse);
    RUN_TEST(testAddCourse);
    RUN_TEST(testFreeCourse);
    RUN_TEST(testRemoveCourseFromList);
    RUN_TEST(testUpdateCourseInList);
    RUN_TEST(testPointsToNumber);
    RUN_TEST(testPrintCourseGradesFromLastToFirst);
    RUN_TEST(testNumerOfTotalPoints);
    RUN_TEST(testNumberofFailedPoints);
    RUN_TEST(testNumberOfEffectivePoints);
    RUN_TEST(testEffectiveGradeSum);
    RUN_TEST(testCheckIfSport);
    RUN_TEST(testCompareCourses);
    RUN_TEST(testCheckForLatestIdAppearance);
}
