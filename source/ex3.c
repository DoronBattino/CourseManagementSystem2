#include <assert.h>
#include <stdio.h>

#include "ex3.h"


void ex3PrintErrorMessage(FILE* error_channel, EX3ErrorCode code) {
    const char* messages[] = {
        "Out of memory",
        "Invalid command line parameters",
        "Cannot open file",
        "Not logged in",
        "Already logged in",
        "Student does not exist",
        "Student already exists",
        "Not friend",
        "Already friend",
        "Not requested",
        "Already requested",
        "Course does not exist",
        "Invalid parameters"
    };
    if (code < 0 || code >= sizeof(messages)/sizeof(messages[0])) {
        fprintf(error_channel, "Unknown error code %d\n", code);
        return;
    }
    fprintf(error_channel, "Error: %s\n", messages[code]);
}

void ex3PrintStudentName(FILE* output_channel, const char* first_name, const char* last_name) {
    fprintf(output_channel, "%s %s\n", first_name, last_name);
}

void ex3PrintStudentInfo(FILE* output_channel, int id, const char* first_name, const char* last_name) {
    fprintf(output_channel, "ID: %d, Name: %s %s\n", id, first_name, last_name);
}

void ex3PrintGradeInfo(FILE* output_channel, int course_id, int points_x2, int grade) {
    fprintf(output_channel, "Course ID: %d, Points: %.1f, Grade: %d\n", course_id, points_x2 / 2.0, grade);
}

void ex3PrintSemesterInfo(FILE* output_channel, int semester,
                           int total_points_x2, int failed_points_x2,
                           int effective_points_x2, int effective_grade_sum_x2) {
    fprintf(output_channel, "Semester %d:\n", semester);
    fprintf(output_channel, "  Total Points: %.1f\n", total_points_x2 / 2.0);
    fprintf(output_channel, "  Failed Points: %.1f\n", failed_points_x2 / 2.0);
    fprintf(output_channel, "  Effective Points: %.1f\n", effective_points_x2 / 2.0);
    fprintf(output_channel, "  Effective Grade Sum: %.1f\n", effective_grade_sum_x2 / 2.0);
}

void ex3PrintSummary(FILE* output_channel,
                     int total_points_x2, int failed_points_x2,
                     int effective_points_x2, int effective_grade_sum_x2) {
    fprintf(output_channel, "Summary:\n");
    fprintf(output_channel, "  Total Points: %.1f\n", total_points_x2 / 2.0);
    fprintf(output_channel, "  Failed Points: %.1f\n", failed_points_x2 / 2.0);
    fprintf(output_channel, "  Effective Points: %.1f\n", effective_points_x2 / 2.0);
    fprintf(output_channel, "  Effective Grade Sum: %.1f\n", effective_grade_sum_x2 / 2.0);
}

void ex3PrintCleanSummary(FILE* output_channel,
                           int effective_points_x2, int effective_grade_sum_x2) {
    fprintf(output_channel, "Clean Summary:\n");
    fprintf(output_channel, "  Effective Points: %.1f\n", effective_points_x2 / 2.0);
    fprintf(output_channel, "  Effective Grade Sum: %.1f\n", effective_grade_sum_x2 / 2.0);
}

void ex3FacultyResponse(FILE* output_channel, const char* response) {
    fprintf(output_channel, "Faculty Response: %s\n", response);
}