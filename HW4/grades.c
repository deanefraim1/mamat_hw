#include <stdio.h>
#include "linked-list.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

#define FAIL -1
#define SUCCESS 0
#define MAX_GRADE 100
#define MIN_GRADE 0

struct grades {
    struct list* students_list;
};

typedef struct {
    int student_id;
    char* student_name;
    struct list* courses_list;
} student;

typedef struct {
    char* course_name;
    int grade;
} course;

static int student_clone(void *element, void **output);
static int course_clone(void *element, void **output);
static void student_destroy(void *element);
static void course_destroy(void *element);
struct grades* grades_init(void);
void grades_destroy(struct grades *grades);
static student* student_exist(struct grades *grades, int id);
int grades_add_student(struct grades *grades, const char *name, int id);
static student* course_exist(struct grades *grades, int id, const char *course_name);
int grades_add_grade(struct grades *grades, const char *name, int id, int grade);
float grades_calc_avg(struct grades *grades, int id, char **out);
int grades_print_student(struct grades *grades, int id);
int grades_print_all(struct grades *grades);

static int student_clone(void *element, void **output){
    printf("student_clone/n");
    student* new_student = (student*)malloc(sizeof(student));
    printf("student_clone/n");
    if(new_student == NULL) return FAIL;
    printf("student_clone/n");
    student* student_data = (student*)element;
    printf("student_clone/n");
    new_student->student_id = student_data->student_id;
    printf("student_clone/n");
    new_student->student_name = (char*)malloc((strlen(student_data->student_name)+1)*sizeof(char));
    printf("student_clone/n");
    if(new_student->student_name == NULL) return FAIL;
    printf("student_clone/n");
    strcpy(new_student->student_name, student_data->student_name);
    printf("student_clone/n");
    new_student->courses_list = list_init(course_clone, course_destroy);
    printf("student_clone/n");
    *output = (void*)new_student;
    printf("student_clone/n");
    return SUCCESS;
}

static int course_clone(void *element, void **output){
    printf("course_clone/n");
    course* new_course = (course*)malloc(sizeof(course));
    printf("course_clone/n");
    if(new_course == NULL) return FAIL;
    printf("course_clone/n");
    course* course_data = (course*)element;
    printf("course_clone/n");
    new_course->course_name = (char*)malloc((strlen(course_data->course_name)+1)*sizeof(char));
    printf("course_clone/n");
    if(new_course->course_name == NULL) return FAIL;
    printf("course_clone/n");
    strcpy(new_course->course_name, course_data->course_name);
    printf("course_clone/n");
    new_course->grade = course_data->grade;
    printf("course_clone/n");
    *output = (void*)new_course;
    printf("course_clone/n");
    return SUCCESS;
}

static void student_destroy(void *element){
    student* student_d = (student*)element;
    list_destroy(student_d->courses_list);
    free(student_d->student_name);
    free(student_d);
}

static void course_destroy(void *element){
    course* course_d = (course*)element;
    free(course_d->course_name);
    free(course_d);
}

struct grades* grades_init(void){
    printf("grades_init/n");
    struct grades* grades_p = (struct grades*)malloc(sizeof(struct grades));
    printf("grades_init/n");
    if(grades_p == NULL) return NULL;
    printf("grades_init/n");
    grades_p->students_list = list_init(student_clone, student_destroy);
    printf("grades_init/n");
    if(grades_p->students_list == NULL) return NULL;
    printf("grades_init/n");
    return grades_p;
}

void grades_destroy(struct grades *grades){
    list_destroy(grades->students_list);
    free(grades);
}

static student* student_exist(struct grades *grades, int id){
    printf("student_exist/n");
    struct iterator* students_it = (struct iterator*)list_begin(grades->students_list);
    printf("student_exist/n");
    if(students_it == NULL) return NULL;
    printf("student_exist/n");
    size_t students_num = list_size(grades->students_list);
    printf("student_exist/n");
    for(size_t i=0; i<students_num; i++){
        student* curr_student = (student*)list_get(students_it);
        if(curr_student == NULL) return NULL;
        if(curr_student->student_id == id) return curr_student;
        students_it = list_next(students_it);
        if(students_it == NULL) return NULL;
    }
    printf("student_exist/n");
    return NULL;
}

int grades_add_student(struct grades *grades, const char *name, int id){
    printf("grades_add_student/n");
    if(grades == NULL) return FAIL;
    printf("grades_add_student/n");
    if(student_exist(grades,id) != NULL) return FAIL;
    printf("grades_add_student/n");
    student* new_student = (student*)malloc(sizeof(student));
    printf("grades_add_student/n");
    if(new_student == NULL) return FAIL;
    printf("grades_add_student/n");
    char* new_name = (char*)malloc(sizeof(char)*(strlen(name)+1));
    printf("grades_add_student/n");
    if(new_name == NULL) return FAIL;
    printf("grades_add_student/n");
    strcpy(new_name, name);
    printf("grades_add_student/n");
    new_student->student_name = new_name;
    printf("grades_add_student/n");
    new_student->student_id = id;
    printf("grades_add_student/n");
    new_student->courses_list = list_init(course_clone, course_destroy);
    printf("grades_add_student/n");
    if(new_student->courses_list == NULL) return FAIL;
    printf("grades_add_student/n");
    if(list_push_back(grades->students_list, new_student) == SUCCESS) {
        printf("grades_add_student/n");
        student_destroy(new_student);
        printf("grades_add_student/n");
        return SUCCESS;
    }
    else {
        printf("grades_add_student/n");
        student_destroy(new_student);
        printf("grades_add_student/n");
        return FAIL;
    }
}

static student* course_exist(struct grades *grades, int id, const char *course_name){
    printf("course_exist/n");
    student* curr_student = student_exist(grades, id);
    printf("course_exist/n");
    if(curr_student == NULL) return NULL;
    printf("course_exist/n");
    struct iterator* courses_it = list_begin(curr_student->courses_list);
    printf("course_exist/n");
    if(courses_it == NULL) return NULL;
    printf("course_exist/n");
    size_t course_num = list_size(curr_student->courses_list);
    printf("course_exist/n");
    for(size_t i=0; i<course_num; i++){
        course* curr_course = (course*)list_get(courses_it);
        if(curr_course == NULL) return NULL;
        if(!strcmp(curr_course->course_name, course_name)) return NULL;
        courses_it = (struct iterator*)list_next(courses_it);
        if(courses_it == NULL) return NULL;
    }
    printf("course_exist/n");
    return curr_student;
}

int grades_add_grade(struct grades *grades, const char *name, int id, int grade){
    printf("grades_add_grade/n");
    if((grades == NULL) || (grade < MIN_GRADE) || (grade > MAX_GRADE)) return FAIL;
    printf("grades_add_grade/n");
    student* curr_student = course_exist(grades, id, name);
    printf("grades_add_grade/n");
    if(curr_student == NULL) return FAIL;
    printf("grades_add_grade/n");
    course* new_course = (course*)malloc(sizeof(course));
    printf("grades_add_grade/n");
    if(new_course == NULL) return FAIL;
    printf("grades_add_grade/n");
    char* new_name = (char*)malloc(sizeof(char)*(strlen(name)+1));
    printf("grades_add_grade/n");
    if(new_name == NULL) return FAIL;
    printf("grades_add_grade/n");
    strcpy(new_name, name);
    printf("grades_add_grade/n");
    new_course->course_name = new_name;
    printf("grades_add_grade/n");
    new_course->grade = grade;
    printf("grades_add_grade/n");
    if(list_push_back(curr_student->courses_list, new_course) == SUCCESS) {
        printf("grades_add_grade/n");
        course_destroy(new_course);
        printf("grades_add_grade/n");
        return SUCCESS;
    }
    else {
        printf("grades_add_grade/n");
        course_destroy(new_course);
        printf("grades_add_grade/n");
        return FAIL;
    }
}

float grades_calc_avg(struct grades *grades, int id, char **out){
    printf("grades_calc_avg/n");
    if(grades == NULL) return FAIL;
    printf("grades_calc_avg/n");
    student* curr_student = student_exist(grades, id);
    printf("grades_calc_avg/n");
    if(curr_student == NULL) return FAIL;
    printf("grades_calc_avg/n");
    *out = (char*)malloc(sizeof(char)*(strlen(curr_student->student_name)+1));
    printf("grades_calc_avg/n");
    if(*out == NULL) return FAIL;
    printf("grades_calc_avg/n");
    strcpy(*out, curr_student->student_name);
    printf("grades_calc_avg/n");
    int sum = 0;
    printf("grades_calc_avg/n");
    struct iterator* courses_it = list_begin(curr_student->courses_list);
    printf("grades_calc_avg/n");
    if(courses_it == NULL) return FAIL;
    printf("grades_calc_avg/n");
    size_t course_num = list_size(curr_student->courses_list);
    printf("grades_calc_avg/n");
    int counter = 0;
    printf("grades_calc_avg/n");
    for(size_t i=0; i<course_num; i++){
        course* curr_course = (course*)list_get(courses_it);
        if(curr_course == NULL) return FAIL;
        sum += curr_course->grade;
        courses_it = (struct iterator*)list_next(courses_it);
        if(courses_it == NULL) return FAIL;
        counter++;
    }
    printf("grades_calc_avg/n");
    return (float)sum/counter;
}

int grades_print_student(struct grades *grades, int id){
    printf("grades_print_student/n");
    if(grades == NULL) return FAIL;
    printf("grades_print_student/n");
    student* curr_student = student_exist(grades, id);
    printf("grades_print_student/n");
    if(curr_student == NULL) return FAIL;
    printf("grades_print_student/n");
    struct iterator* courses_it = list_begin(curr_student->courses_list);
    printf("grades_print_student/n");
    if(courses_it == NULL) return FAIL;
    printf("grades_print_student/n");
    size_t course_num = list_size(curr_student->courses_list);
    printf("grades_print_student/n");
    printf("%s %d: ", curr_student->student_name, curr_student->student_id);
    printf("grades_print_student/n");
    for(size_t i=0; i<course_num; i++){
        course* curr_course = (course*)list_get(courses_it);
        if(curr_course == NULL) return FAIL;
        printf("%s %d", curr_course->course_name, curr_course->grade);
        if(i != (course_num-1)) printf(", ");
        courses_it = (struct iterator*)list_next(courses_it);
        if(courses_it == NULL) return FAIL;
    }
    printf("grades_print_student/n");
    printf("/n");
    printf("grades_print_student/n");
    return SUCCESS;
}

int grades_print_all(struct grades *grades){
    printf("grades_print_all/n");
    if(grades == NULL) return FAIL;
    printf("grades_print_all/n");
    struct iterator* students_it = (struct iterator*)list_begin(grades->students_list);
    printf("grades_print_all/n");
    if(students_it == NULL) return FAIL;
    printf("grades_print_all/n");
    size_t students_num = list_size(grades->students_list);
    printf("grades_print_all/n");
    for(size_t i=0; i<students_num; i++){
        student* curr_student = (student*)list_get(students_it);
        if(curr_student == NULL) return FAIL;
        if(grades_print_student(grades, curr_student->student_id)) return FAIL;
        students_it = list_next(students_it);
        if(students_it == NULL) return FAIL;
    }
    printf("grades_print_all/n");
    return SUCCESS;
}
