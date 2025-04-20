#include "Grade.h"
#include "Course.h"
#include "test_utilities.h"
#include "Semester.h"
#include "GradeSheet.h"

/**
 * List of tests, one for each function is usually a good thumb rule.
 */


static bool testCreateGradeSheet(){
    List sport_courses=listCreate(copyCourseWithNumber,freeCourseWithNumber);
    Set non_sport_courses=setCreate(copyCourseWithNumber,freeCourseWithNumber,compareCoursesInSet);
    GradeSheetResult result;
    ASSERT_TEST(createGradeSheet(NULL,sport_courses,&result)==NULL);
    ASSERT_TEST(result==GRADESHEET_NULL_ARGUMENT);
    ASSERT_TEST(createGradeSheet(non_sport_courses,NULL,&result)== NULL);
    listDestroy(sport_courses);
    setDestroy(non_sport_courses);
    return true;
}

static bool testCreateCourseWithNumber(){
    CourseResult result;
    List Grades=listCreate(copyGrade,freeGrade);
    Course course=createCourse("0.5",1,Grades,&result);
    ASSERT_TEST(createCourseWithNumber(NULL,1)==NULL);
    CourseWithNumber Course =createCourseWithNumber(course,1);
    ASSERT_TEST(returnCourseIdofCourseWithNumber(Course)==1);
    ASSERT_TEST(returnSemesterNumberOfCourseWithNumber(Course)==1);
    listDestroy(Grades);
    freeCourse(course);
    freeCourseWithNumber(Course);
    return true;
}

static bool testCompareCoursesWithNumber(){
    CourseResult result;
    List Grades=listCreate(copyGrade,freeGrade);
    Course course=createCourse("0.5",1,Grades,&result);
    Course course_two=createCourse("0.5",2,Grades,&result);
    CourseWithNumber Course=createCourseWithNumber(course,1);
    CourseWithNumber Course_two=createCourseWithNumber(course_two,1);
    ASSERT_TEST(compareCoursesWithNumber(Course_two,Course,0)==1);
    ASSERT_TEST(compareCoursesWithNumber(Course,Course_two,0)==-1);
    listDestroy(Grades);
    freeCourse(course);
    freeCourse(course_two);
    freeCourseWithNumber(Course_two);
    freeCourseWithNumber(Course);
    return true;

}

static bool testCompareCoursesHighGrades(){
    CourseResult result;
    GradeResult result_two;
    List Grades=listCreate(copyGrade,freeGrade);
    List Grades_two=listCreate(copyGrade,freeGrade);
    Grade grade_one=CreateGrade(50,&result_two);
    Grade grade_two=CreateGrade(60,&result_two);
    listInsertLast(Grades,grade_one);
    listInsertLast(Grades_two,grade_two);
    Course course=createCourse("0.5",1,Grades,&result);
    Course course_two=createCourse("0.5",2,Grades_two,&result);
    CourseWithNumber Course=createCourseWithNumber(course,1);
    CourseWithNumber Course_two=createCourseWithNumber(course_two,1);
    ASSERT_TEST(compareCoursesByHighGrades(Course_two,Course,0)==-1);
    ASSERT_TEST(compareCoursesByHighGrades(Course,Course_two,0)==1);
    listDestroy(Grades);
    listDestroy(Grades_two);
    freeGrade(grade_one);
    freeGrade(grade_two);
    freeCourse(course);
    freeCourse(course_two);
    freeCourseWithNumber(Course_two);
    freeCourseWithNumber(Course);
    return true;

}


static bool testAddSportCourseToGradeSheet(){
    List sport_courses=listCreate(copyCourseWithNumber,freeCourseWithNumber);
    Set non_sport_courses=setCreate(copyCourseWithNumber,freeCourseWithNumber,compareCoursesInSet);
    GradeSheetResult result;
    GradeSheet gradesheet=createGradeSheet(non_sport_courses,sport_courses,&result);
    CourseResult result_two;
    int semester_number=1;
    List Grades=listCreate(copyGrade,freeGrade);
    Course course=createCourse("0.5",1,Grades,&result_two);
    result=addSportCourseToGradeSheet(gradesheet,course,semester_number);
    ASSERT_TEST(result==GRADESHEET_SUCCESS);
    freeGradeSheet(gradesheet);
    setDestroy(non_sport_courses);
    listDestroy(sport_courses);
    listDestroy(Grades);
    freeCourse(course);
    return true;

}

static bool testAddNonSportCourse(){
    List sport_courses=listCreate(copyCourseWithNumber,freeCourseWithNumber);
    Set non_sport_courses=setCreate(copyCourseWithNumber,freeCourseWithNumber,compareCoursesInSet);
    GradeSheetResult result;
    GradeSheet gradesheet=createGradeSheet(non_sport_courses,sport_courses,&result);
    CourseResult result_two;
    int semester_number=1;
    List Grades=listCreate(copyGrade,freeGrade);
    Course course=createCourse("0.5",1,Grades,&result_two);
    result=addNonSportToGradeSheet(gradesheet,course,semester_number);
    ASSERT_TEST(result==GRADESHEET_SUCCESS);
    freeGradeSheet(gradesheet);
    setDestroy(non_sport_courses);
    listDestroy(sport_courses);
    listDestroy(Grades);
    freeCourse(course);
    return true;

}

static bool testCaculatesPointsInGradeSheet(){
    List sport_courses=listCreate(copyCourseWithNumber,freeCourseWithNumber);
    Set non_sport_courses=setCreate(copyCourseWithNumber,freeCourseWithNumber,compareCoursesInSet);
    GradeSheetResult result;
    CourseResult result_two;
    GradeSheet gradesheet=createGradeSheet(non_sport_courses,sport_courses,&result);
    int semester_number=1;
    List Grades=listCreate(copyGrade,freeGrade);
    Course course=createCourse("0.5",1,Grades,&result_two);
    addNonSportToGradeSheet(gradesheet,course,semester_number);
    addSportCourseToGradeSheet(gradesheet,course,semester_number);
    int number=caculatesPointsInGradeSheet(gradesheet);
    ASSERT_TEST(number==2);
    freeGradeSheet(gradesheet);
    setDestroy(non_sport_courses);
    listDestroy(sport_courses);
    listDestroy(Grades);
    freeCourse(course);
    return true;

}


static bool testSortGradeSheetByCourseId(){
    List sport_courses=listCreate(copyCourseWithNumber,freeCourseWithNumber);
    Set non_sport_courses=setCreate(copyCourseWithNumber,freeCourseWithNumber,compareCoursesInSet);
    GradeSheetResult result_three;
    GradeSheet gradesheet=createGradeSheet(non_sport_courses,sport_courses,&result_three);
    CourseResult result;
    GradeResult result_two;
    int semester_number=1;
    List Grades=listCreate(copyGrade,freeGrade);
    List Grades_two=listCreate(copyGrade,freeGrade);
    Grade grade_one=CreateGrade(50,&result_two);
    Grade grade_two=CreateGrade(60,&result_two);
    listInsertLast(Grades,grade_one);
    listInsertLast(Grades_two,grade_two);
    Course course=createCourse("0.5",1,Grades,&result);
    Course course_two=createCourse("0.5",2,Grades_two,&result);
    addNonSportToGradeSheet(gradesheet,course,semester_number);
    addSportCourseToGradeSheet(gradesheet,course,semester_number);
    addNonSportToGradeSheet(gradesheet,course_two,semester_number);
    addSportCourseToGradeSheet(gradesheet,course_two,semester_number);
    List sorted=sortGradeSheetByCourseId(gradesheet);
    Course check=listGetFirst(sorted);
    ASSERT_TEST(returnCourseId(check)==1);
    CourseWithNumber check_two=returnSportCourseFromGradeSheet(gradesheet);
    ASSERT_TEST(returnCourseIdofCourseWithNumber(check_two)==1);
    listDestroy(Grades);
    listDestroy(Grades_two);
    listDestroy(sorted);
    listDestroy(sport_courses);
    setDestroy(non_sport_courses);
    freeGrade(grade_one);
    freeGrade(grade_two);
    freeCourse(course);
    freeCourse(course_two);
    freeGradeSheet(gradesheet);
    return true;


}

int main(){


    RUN_TEST(testCreateGradeSheet);
    RUN_TEST(testCreateCourseWithNumber);
    RUN_TEST(testCompareCoursesWithNumber);
    RUN_TEST(testCompareCoursesHighGrades);
    RUN_TEST(testAddSportCourseToGradeSheet);
    RUN_TEST(testAddNonSportCourse);
    RUN_TEST(testCaculatesPointsInGradeSheet);
    RUN_TEST(testSortGradeSheetByCourseId);





}
