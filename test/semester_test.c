#include "Grade.h"
#include "Course.h"
#include "test_utilities.h"
#include "Semester.h"
#include "GradeSheet.h"

/**
 * List of tests, one for each function is usually a good thumb rule.
 */

static bool testCreateSemester(){
    SemesterResult result;

    List Courses=listCreate(copyCourse,freeCourse);
    ASSERT_TEST(createSemester(4,NULL,&result)==NULL);
    ASSERT_TEST(result==SEMESTER_NULL_ARGUMENT);
    ASSERT_TEST(createSemester(-1,Courses,&result)==NULL);
    ASSERT_TEST(result==SEMESTER_ILLEGAL_ARGUMENT);
    Semester check=createSemester(4,Courses,&result);
    ASSERT_TEST(result==SEMESTER_SUCCESS);
    freeSemester(check);
    listDestroy(Courses);
    return true;
}



static bool testCopySemester(){
    SemesterResult result;
    List Courses=listCreate(copyCourse,freeCourse);
    Semester check1=createSemester(5,Courses,&result);
    ASSERT_TEST(copySemester(NULL)==NULL);
    Semester copy=copySemester((ListElement)check1);
    ASSERT_TEST(copy!=NULL);
    listDestroy(Courses);
    freeSemester(check1);
    freeSemester(copy);
    return true;
}


static bool testAddCourseToSemester(){
    ASSERT_TEST(addCourseToSemester(NULL,5,5,"0.5",70)==false);
    SemesterResult result;
    List semesters=listCreate(copySemester,freeSemester);
    ASSERT_TEST(addCourseToSemester(semesters,-4,5,"0.5",70)==false);
    List courses=listCreate(copyCourse,freeCourse);
    Semester check=createSemester(2,courses,&result);
    listInsertFirst(semesters,(ListElement)check);
    ASSERT_TEST(addCourseToSemester(semesters,2,8,"0.4",70)==false);
    ASSERT_TEST(addCourseToSemester(semesters,2,5,"0.5",70)==true);
    listDestroy(semesters);
    listDestroy(courses);
    freeSemester(check);
    return true;
}

static bool testRemoveCourseFromSemester(){
    Semester semester=NULL;
    List Semesters=listCreate(copySemester,freeSemester);
    List Grades=listCreate(copyGrade,freeGrade);
    List Grades_two=listCreate(copyGrade,freeGrade);
    GradeResult result;
    CourseResult result_two;
    SemesterResult result_three;
    List courses=listCreate(copyCourse,freeCourse);
    Grade grade_one=CreateGrade(50,&result);
    listInsertFirst(Grades,(ListElement)grade_one);
    Course course=createCourse("0.5", 1,Grades,&result_two);
    Course course_two=createCourse("0.5",2,Grades_two,&result_two);
    listInsertLast(courses,(ListElement)course);
    listInsertAfterCurrent(courses,(ListElement)course_two);
    semester=createSemester(1,courses,&result_three);
    listInsertLast(Semesters,(ListElement)semester);
    ASSERT_TEST(removeCoursefromSemester(Semesters,1,1)==true);
    ASSERT_TEST(removeCoursefromSemester(Semesters,1,2)==false);
    freeGrade(grade_one);
    listDestroy(Grades);
    listDestroy(Grades_two);
    freeCourse(course);
    freeCourse(course_two);
    listDestroy(courses);
    freeSemester(semester);
    listDestroy(Semesters);
    return true;
}
/*
static bool testRemoveCourseFromSemester(){
    GradeResult result;
    CourseResult result_two;
    SemesterResult result_three;
    List Semesters=listCreate(copySemester,freeSemester);
    List Grades=listCreate(copyGrade,freeGrade);
    List courses=listCreate(copyCourse,freeCourse);
    Grade grade_one=CreateGrade(50,&result);
    Course course=createCourse("0.5", 1,Grades,&result_two);
    listInsertLast(courses,(ListElement)course);
    Semester semester=createSemester(1,courses,&result_three);
    listInsertLast(Semesters,(ListElement)semester);
    ASSERT_TEST(removeCoursefromSemester(Semesters,1,4)==false);
    listInsertFirst(Grades,(ListElement)grade_one);
    Course course_two=createCourse("0.5",2,Grades,&result_two);
    listInsertFirst(courses,(ListElement)course_two);
    Semester semester_two=createSemester(2,courses,&result_three);
    listInsertFirst(Semesters,(ListElement)semester_two);
    ASSERT_TEST(removeCoursefromSemester(Semesters,2,2)==true);
    freeGrade(grade_one);
    listDestroy(Grades);
    freeCourse(course);
    freeCourse(course_two);
    listDestroy(courses);
    freeSemester(semester);
    freeSemester(semester_two);
    listDestroy(Semesters);
    return true;


}
*/
static bool testUpdateCourseInSemester() {
    GradeResult result;
    CourseResult result_two;
    SemesterResult result_three;
    List Semesters = listCreate(copySemester, freeSemester);
    List Grades = listCreate(copyGrade, freeGrade);
    List courses = listCreate(copyCourse, freeCourse);
    Grade grade_one = CreateGrade(50, &result);
    Course course = createCourse("0.5", 1, Grades, &result_two);
    listInsertLast(courses, (ListElement) course);
    Semester semester = createSemester(1, courses, &result_three);
    listInsertLast(Semesters, (ListElement) semester);
    ASSERT_TEST(updateCourseInSemester(Semesters, 1, 70) == false);
    listInsertFirst(Grades, (ListElement) grade_one);
    Course course_two = createCourse("0.5", 2, Grades, &result_two);
    listInsertFirst(courses, (ListElement) course_two);
    Semester semester_two = createSemester(2, courses, &result_three);
    listInsertFirst(Semesters, (ListElement) semester_two);
    ASSERT_TEST(updateCourseInSemester(Semesters, 2, 65) == true);
    freeGrade(grade_one);
    listDestroy(Grades);
    freeCourse(course);
    freeCourse(course_two);
    listDestroy(courses);
    freeSemester(semester);
    freeSemester(semester_two);
    listDestroy(Semesters);
    return true;


}

static bool testPrintGradesOfSemester(){
    FILE* output_channel=fopen("amitz.txt", "w");
    assert(output_channel != NULL);
    GradeResult result;
    CourseResult result_two;
    SemesterResult result_three;
    List Grades=listCreate(copyGrade,freeGrade);
    List Courses=listCreate(copyCourse,freeCourse);
    List Courses_two=listCreate(copyCourse,freeCourse);
    Grade grade_one=CreateGrade(50,&result);
    Grade grade_two=CreateGrade(60,&result);
    listInsertFirst(Grades,(ListElement)grade_one);
    listInsertFirst(Grades,(ListElement)grade_two);
    Course course_one=createCourse("4",3,Grades,&result_two);
    Course course_two=createCourse("0.5", 12,Grades,&result_two);
    listInsertFirst(Courses,course_one);
    listInsertLast(Courses,course_two);
    Semester first=createSemester(1,Courses,&result_three);
    printGradesOfSemester(first,output_channel);
    freeGrade(grade_one);
    freeGrade(grade_two);
    listDestroy(Grades);
    freeCourse(course_one);
    freeCourse(course_two);
    freeSemester(first);
    listDestroy(Courses);
    listDestroy(Courses_two);
    fclose(output_channel);
    return true;
}

static bool testPrintSemesterSummary(){
    FILE* output_channel=fopen("tatam","w");
    assert(output_channel != NULL);
    GradeResult result;
    CourseResult result_two;
    SemesterResult result_three;
    List Grades=listCreate(copyGrade,freeGrade);
    List Courses=listCreate(copyCourse,freeCourse);
    List Courses_two=listCreate(copyCourse,freeCourse);
    Grade grade_one=CreateGrade(50,&result);
    Grade grade_two=CreateGrade(60,&result);
    listInsertFirst(Grades,(ListElement)grade_one);
    listInsertFirst(Grades,(ListElement)grade_two);
    Course course_one=createCourse("4",3,Grades,&result_two);
    Course course_two=createCourse("0.5", 12,Grades,&result_two);
    listInsertFirst(Courses,course_one);
    listInsertLast(Courses,course_two);
    Semester first=createSemester(1,Courses,&result_three);
    printSemesterSummary(first,output_channel);
    freeGrade(grade_one);
    freeGrade(grade_two);
    listDestroy(Grades);
    freeCourse(course_one);
    freeCourse(course_two);
    freeSemester(first);
    listDestroy(Courses);
    listDestroy(Courses_two);
    fclose(output_channel);
    return true;
}


static bool testAddRelevantCoursesToGradeSheet(){
    GradeResult result;
    CourseResult result_two;
    SemesterResult result_three;
    GradeSheetResult result_four;
    List Grades=listCreate(copyGrade,freeGrade);
    List sport_courses=listCreate(copyCourseWithNumber,freeCourseWithNumber);
    List Courses_one=listCreate(copyCourse,freeCourse);
    List Courses_two=listCreate(copyCourse,freeCourse);
    Set non_sport_courses =setCreate(copyCourseWithNumber,freeCourseWithNumber,compareCourses);
    GradeSheet gradesheet=createGradeSheet(non_sport_courses,sport_courses, &result_four);
    List Semesters=listCreate(copySemester,freeSemester);
    Grade grade_one=CreateGrade(50,&result);
    Grade grade_two=CreateGrade(60,&result);
    listInsertFirst(Grades,(ListElement)grade_one);
    listInsertFirst(Grades,(ListElement)grade_two);
    Course course_one=createCourse("3",399999,Grades,&result_two);
    Course course_two=createCourse("0.5", 2,Grades,&result_two);
    Course course_three=createCourse("4",2,Grades,&result_two);
    listInsertFirst(Courses_one,course_one);
    listInsertLast(Courses_one,course_two);
    listInsertLast(Courses_two,course_three);
    Semester second=createSemester(2,Courses_two,&result_three);
    Semester first=createSemester(1,Courses_one,&result_three);
    listInsertFirst(Semesters,(ListElement)first);
    listInsertLast(Semesters,(ListElement)second);
    addRelevantCoursesToGradeSheet(Semesters,gradesheet);
    CourseWithNumber check=returnSportCourseFromGradeSheet(gradesheet);
    int id_one=returnCourseId(course_one);
    int id_two=returnCourseIdofCourseWithNumber(check);
    ASSERT_TEST(id_one==id_two);
    Course check_two=returnNonSportCourseFromGradeSheet(gradesheet);
    ASSERT_TEST(compareCourses(check_two,course_three)==0);
    freeGrade(grade_one);
    freeGrade(grade_two);
    listDestroy(Grades);
    freeCourse(course_one);
    freeCourse(course_two);
    freeCourse(course_three);
    freeSemester(first);
    freeSemester(second);
    listDestroy(Semesters);
    listDestroy(Courses_one);
    listDestroy(Courses_two);
    freeGradeSheet(gradesheet);
    listDestroy(sport_courses);
    setDestroy(non_sport_courses);
    return true;
}



static bool testCheckForLatestGradeSheetAppearance(){
    GradeResult result;
    CourseResult result_two;
    SemesterResult result_three;
    List Grades=listCreate(copyGrade,freeGrade);
    List Grades_two=listCreate(copyGrade,freeGrade);
    List Courses_one=listCreate(copyCourse,freeCourse);
    List Courses_two=listCreate(copyCourse,freeCourse);
    List Semesters=listCreate(copySemester,freeSemester);
    Grade grade_one=CreateGrade(50,&result);
    Grade grade_two=CreateGrade(60,&result);
    Grade grade_three=CreateGrade(70,&result);
    listInsertFirst(Grades,(ListElement)grade_one);
    listInsertLast(Grades,(ListElement)grade_two);
    listInsertFirst(Grades_two,(ListElement)grade_three);
    Course course_one=createCourse("2",399999,Grades,&result_two);
    Course course_two=createCourse("0.5", 2,Grades,&result_two);
    Course course_three=createCourse("4",2,Grades,&result_two);
    Course course_four=createCourse("3",399999,Grades_two,&result_two);
    listInsertFirst(Courses_one,course_one);
    listInsertLast(Courses_one,course_two);
    listInsertFirst(Courses_two,course_four);
    listInsertLast(Courses_two,course_three);
    Semester second=createSemester(2,Courses_two,&result_three);
    Semester first=createSemester(1,Courses_one,&result_three);
    listInsertFirst(Semesters,(ListElement)first);
    listInsertLast(Semesters,(ListElement)second);
    Course check=checkForLatestGradeSheetApperance(Semesters,course_one);
    ASSERT_TEST(compareCourses(check,course_one)==0);
    check=checkForLatestGradeSheetApperance(Semesters,course_two);
    ASSERT_TEST(compareCourses(check,course_two)==0);
    freeGrade(grade_one);
    freeGrade(grade_two);
    freeGrade(grade_three);
    listDestroy(Grades_two);
    listDestroy(Grades);
    freeCourse(course_one);
    freeCourse(course_two);
    freeCourse(course_three);
    freeCourse(course_four);
    freeSemester(first);
    freeSemester(second);
    listDestroy(Semesters);
    listDestroy(Courses_one);
    listDestroy(Courses_two);


    return true;

}

static bool testPrintGradeSheetSummary(){
    FILE* output_channel=fopen("dor","w");
    assert(output_channel != NULL);
    GradeResult result;
    CourseResult result_two;
    SemesterResult result_three;
    List Grades=listCreate(copyGrade,freeGrade);
    List Courses_one=listCreate(copyCourse,freeCourse);
    List Courses_two=listCreate(copyCourse,freeCourse);
    List Semesters=listCreate(copySemester,freeSemester);
    Grade grade_one=CreateGrade(50,&result);
    Grade grade_two=CreateGrade(60,&result);
    listInsertFirst(Grades,(ListElement)grade_one);
    listInsertFirst(Grades,(ListElement)grade_two);
    Course course_one=createCourse("3",399999,Grades,&result_two);
    Course course_two=createCourse("0.5", 2,Grades,&result_two);
    Course course_three=createCourse("4",2,Grades,&result_two);
    listInsertFirst(Courses_one,course_one);
    listInsertLast(Courses_one,course_two);
    listInsertLast(Courses_two,course_three);
    Semester second=createSemester(2,Courses_two,&result_three);
    Semester first=createSemester(1,Courses_one,&result_three);
    listInsertFirst(Semesters,(ListElement)first);
    listInsertLast(Semesters,(ListElement)second);
    printGradeSheetSummary(Semesters,output_channel);
    freeGrade(grade_one);
    freeGrade(grade_two);
    listDestroy(Grades);
    freeCourse(course_one);
    freeCourse(course_two);
    freeCourse(course_three);
    freeSemester(first);
    freeSemester(second);
    listDestroy(Semesters);
    listDestroy(Courses_one);
    listDestroy(Courses_two);
    fclose(output_channel);

    return true;
}

static bool testPrintStudentCleanGradesAndInfo(){
    FILE* output_channel=fopen("Rmit","w");
    assert(output_channel != NULL);
    GradeResult result;
    CourseResult result_two;
    SemesterResult result_three;
    List Grades=listCreate(copyGrade,freeGrade);
    List Grades_two=listCreate(copyGrade,freeGrade);
    List Courses_one=listCreate(copyCourse,freeCourse);
    List Courses_two=listCreate(copyCourse,freeCourse);
    List Semesters=listCreate(copySemester,freeSemester);
    Grade grade_one=CreateGrade(50,&result);
    Grade grade_two=CreateGrade(60,&result);
    Grade grade_three=CreateGrade(70,&result);
    listInsertFirst(Grades,(ListElement)grade_one);
    listInsertLast(Grades,(ListElement)grade_two);
    listInsertFirst(Grades_two,(ListElement)grade_three);
    Course course_one=createCourse("3",399999,Grades,&result_two);
    Course course_two=createCourse("0.5", 2,Grades,&result_two);
    Course course_three=createCourse("4",2,Grades,&result_two);
    Course course_four=createCourse("4",399999,Grades_two,&result_two);
    listInsertFirst(Courses_one,course_one);
    listInsertLast(Courses_one,course_two);
    listInsertFirst(Courses_two,course_three);
    listInsertLast(Courses_two,course_four);
    Semester second=createSemester(2,Courses_two,&result_three);
    Semester first=createSemester(1,Courses_one,&result_three);
    listInsertFirst(Semesters,(ListElement)first);
    listInsertLast(Semesters,(ListElement)second);
    ListSortKey key=0;
    listSort(Semesters,compareSemesters,key);
    printStudentCleanGradesAndInfo(Semesters,output_channel);
    freeGrade(grade_one);
    freeGrade(grade_two);
    freeGrade(grade_three);
    listDestroy(Grades_two);
    listDestroy(Grades);
    freeCourse(course_one);
    freeCourse(course_two);
    freeCourse(course_three);
    freeCourse(course_four);
    freeSemester(first);
    freeSemester(second);
    listDestroy(Semesters);
    listDestroy(Courses_one);
    listDestroy(Courses_two);
    fclose(output_channel);
    return true;

}

static bool testPrintHighestGradeFromList(){
    FILE* output_channel=fopen("Highest2","w");
    assert(output_channel != NULL);
    int amount=3;
    GradeResult result;
    CourseResult result_two;
    SemesterResult result_three;
    List Grades=listCreate(copyGrade,freeGrade);
    List Grades_two=listCreate(copyGrade,freeGrade);
    List Courses_one=listCreate(copyCourse,freeCourse);
    List Courses_two=listCreate(copyCourse,freeCourse);
    List Semesters=listCreate(copySemester,freeSemester);
    Grade grade_one=CreateGrade(50,&result);
    Grade grade_two=CreateGrade(60,&result);
    Grade grade_three=CreateGrade(70,&result);
    listInsertFirst(Grades,(ListElement)grade_one);
    listInsertLast(Grades,(ListElement)grade_two);
    listInsertFirst(Grades_two,(ListElement)grade_three);
    Course course_one=createCourse("3",399999,Grades,&result_two);
    Course course_two=createCourse("0.5", 2,Grades,&result_two);
    Course course_three=createCourse("4",2,Grades,&result_two);
    Course course_four=createCourse("4",399999,Grades_two,&result_two);
    listInsertFirst(Courses_one,course_one);
    listInsertLast(Courses_one,course_two);
    listInsertFirst(Courses_two,course_three);
    listInsertLast(Courses_two,course_four);
    Semester second=createSemester(2,Courses_two,&result_three);
    Semester first=createSemester(1,Courses_one,&result_three);
    listInsertFirst(Semesters,(ListElement)first);
    listInsertLast(Semesters,(ListElement)second);
    ListSortKey key=0;
    listSort(Semesters,compareSemesters,key);
    printHighestGradesFromList(amount,Semesters,output_channel);
    freeGrade(grade_one);
    freeGrade(grade_two);
    freeGrade(grade_three);
    listDestroy(Grades_two);
    listDestroy(Grades);
    freeCourse(course_one);
    freeCourse(course_two);
    freeCourse(course_three);
    freeCourse(course_four);
    freeSemester(first);
    freeSemester(second);
    listDestroy(Semesters);
    listDestroy(Courses_one);
    listDestroy(Courses_two);
    fclose(output_channel);
    return true;

}


static bool testPrintLowestGradeFromList(){
    FILE* output_channel=fopen("Lowest","w");
    assert(output_channel != NULL);
    int amount=3;
    GradeResult result;
    CourseResult result_two;
    SemesterResult result_three;
    List Grades=listCreate(copyGrade,freeGrade);
    List Grades_two=listCreate(copyGrade,freeGrade);
    List Grades_three=listCreate(copyGrade,freeGrade);
    List Courses_one=listCreate(copyCourse,freeCourse);
    List Courses_two=listCreate(copyCourse,freeCourse);
    List Semesters=listCreate(copySemester,freeSemester);
    Grade grade_one=CreateGrade(40,&result);
    Grade grade_two=CreateGrade(60,&result);
    Grade grade_three=CreateGrade(70,&result);
    listInsertFirst(Grades,(ListElement)grade_one);
    listInsertLast(Grades_two,(ListElement)grade_two);
    listInsertFirst(Grades_three,(ListElement)grade_three);
    Course course_one=createCourse("3",399999,Grades_three,&result_two);
    Course course_two=createCourse("0.5", 2,Grades_two,&result_two);
    Course course_three=createCourse("4",2,Grades_three,&result_two);
    Course course_four=createCourse("4",399999,Grades,&result_two);
    listInsertFirst(Courses_one,course_one);
    listInsertLast(Courses_one,course_two);
    listInsertFirst(Courses_two,course_three);
    listInsertLast(Courses_two,course_four);
    Semester second=createSemester(2,Courses_two,&result_three);
    Semester first=createSemester(1,Courses_one,&result_three);
    listInsertFirst(Semesters,(ListElement)first);
    listInsertLast(Semesters,(ListElement)second);
    ListSortKey key=0;
    listSort(Semesters,compareSemesters,key);
    printLowestGradesFromList(amount,Semesters,output_channel);
    freeGrade(grade_one);
    freeGrade(grade_two);
    freeGrade(grade_three);
    listDestroy(Grades_two);
    listDestroy(Grades);
    listDestroy(Grades_three);
    freeCourse(course_one);
    freeCourse(course_two);
    freeCourse(course_three);
    freeCourse(course_four);
    freeSemester(first);
    freeSemester(second);
    listDestroy(Semesters);
    listDestroy(Courses_one);
    listDestroy(Courses_two);
    fclose(output_channel);
    return true;

}

/*
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


bool static testAddSportCourseToGradeSheet(){
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
*/

int main(){

    RUN_TEST(testCreateSemester);
    RUN_TEST(testCopySemester);
    /*
    RUN_TEST(testFreeSemester);
*/
    RUN_TEST(testAddCourseToSemester);
    RUN_TEST(testRemoveCourseFromSemester);
    RUN_TEST(testUpdateCourseInSemester);
    RUN_TEST(testPrintGradesOfSemester);
    RUN_TEST(testPrintSemesterSummary);
    RUN_TEST(testCheckForLatestGradeSheetAppearance);
    RUN_TEST(testAddRelevantCoursesToGradeSheet);
    RUN_TEST(testPrintGradeSheetSummary);
    RUN_TEST(testPrintStudentCleanGradesAndInfo);
    RUN_TEST(testPrintHighestGradeFromList);
    RUN_TEST(testPrintLowestGradeFromList);

}






