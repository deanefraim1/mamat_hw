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
    printf("student_clone       ");
    student* new_student = (student*)malloc(sizeof(student));
    printf("student_clone       ");
    if(new_student == NULL) return FAIL;
    printf("student_clone       ");
    student* student_data = (student*)element;
    printf("student_clone       ");
    new_student->student_id = student_data->student_id;
    printf("student_clone       ");
    new_student->student_name = (char*)malloc((strlen(student_data->student_name)+1)*sizeof(char));
    printf("student_clone       ");
    if(new_student->student_name == NULL) return FAIL;
    printf("student_clone       ");
    strcpy(new_student->student_name, student_data->student_name);
    printf("student_clone       ");
    new_student->courses_list = list_init(course_clone, course_destroy);
    printf("student_clone       ");
    *output = (void*)new_student;
    printf("student_clone       ");
    return SUCCESS;
}

static int course_clone(void *element, void **output){
    printf("course_clone       ");
    course* new_course = (course*)malloc(sizeof(course));
    printf("course_clone       ");
    if(new_course == NULL) return FAIL;
    printf("course_clone       ");
    course* course_data = (course*)element;
    printf("course_clone       ");
    new_course->course_name = (char*)malloc((strlen(course_data->course_name)+1)*sizeof(char));
    printf("course_clone       ");
    if(new_course->course_name == NULL) return FAIL;
    printf("course_clone       ");
    strcpy(new_course->course_name, course_data->course_name);
    printf("course_clone       ");
    new_course->grade = course_data->grade;
    printf("course_clone       ");
    *output = (void*)new_course;
    printf("course_clone       ");
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
    printf("grades_init       ");
    struct grades* grades_p = (struct grades*)malloc(sizeof(struct grades));
    printf("grades_init       ");
    if(grades_p == NULL) return NULL;
    printf("grades_init       ");
    grades_p->students_list = list_init(student_clone, student_destroy);
    printf("grades_init       ");
    if(grades_p->students_list == NULL) return NULL;
    printf("grades_init       ");
    return grades_p;
}

void grades_destroy(struct grades *grades){
    list_destroy(grades->students_list);
    free(grades);
}

static student* student_exist(struct grades *grades, int id){
    printf("student_exist       ");
    struct iterator* students_it = (struct iterator*)list_begin(grades->students_list);
    printf("student_exist       ");
    if(students_it == NULL) return NULL;
    printf("student_exist       ");
    size_t students_num = list_size(grades->students_list);
    printf("student_exist       ");
    for(size_t i=0; i<students_num; i++){
        student* curr_student = (student*)list_get(students_it);
        if(curr_student == NULL) return NULL;
        if(curr_student->student_id == id) return curr_student;
        students_it = list_next(students_it);
        if(students_it == NULL) return NULL;
    }
    printf("student_exist       ");
    return NULL;
}

int grades_add_student(struct grades *grades, const char *name, int id){
    printf("grades_add_student       ");
    if(grades == NULL) return FAIL;
    printf("grades_add_student       ");
    if(student_exist(grades,id) != NULL) return FAIL;
    printf("grades_add_student       ");
    student* new_student = (student*)malloc(sizeof(student));
    printf("grades_add_student       ");
    if(new_student == NULL) return FAIL;
    printf("grades_add_student       ");
    char* new_name = (char*)malloc(sizeof(char)*(strlen(name)+1));
    printf("grades_add_student       ");
    if(new_name == NULL) return FAIL;
    printf("grades_add_student       ");
    strcpy(new_name, name);
    printf("grades_add_student       ");
    new_student->student_name = new_name;
    printf("grades_add_student       ");
    new_student->student_id = id;
    printf("grades_add_student       ");
    new_student->courses_list = list_init(course_clone, course_destroy);
    printf("grades_add_student       ");
    if(new_student->courses_list == NULL) return FAIL;
    printf("grades_add_student       ");
    if(list_push_back(grades->students_list, new_student) == SUCCESS) {
        printf("grades_add_student       ");
        student_destroy(new_student);
        printf("grades_add_student       ");
        return SUCCESS;
    }
    else {
        printf("grades_add_student       ");
        student_destroy(new_student);
        printf("grades_add_student       ");
        return FAIL;
    }
}

static student* course_exist(struct grades *grades, int id, const char *course_name){
    printf("course_exist       ");
    student* curr_student = student_exist(grades, id);
    printf("course_exist       ");
    if(curr_student == NULL) return NULL;
    printf("course_exist       ");
    struct iterator* courses_it = list_begin(curr_student->courses_list);
    printf("course_exist       ");
    if(courses_it == NULL) return NULL;
    printf("course_exist       ");
    size_t course_num = list_size(curr_student->courses_list);
    printf("course_exist       ");
    for(size_t i=0; i<course_num; i++){
        course* curr_course = (course*)list_get(courses_it);
        if(curr_course == NULL) return NULL;
        if(!strcmp(curr_course->course_name, course_name)) return NULL;
        courses_it = (struct iterator*)list_next(courses_it);
        if(courses_it == NULL) return NULL;
    }
    printf("course_exist       ");
    return curr_student;
}

int grades_add_grade(struct grades *grades, const char *name, int id, int grade){
    printf("grades_add_grade       ");
    if((grades == NULL) || (grade < MIN_GRADE) || (grade > MAX_GRADE)) return FAIL;
    printf("grades_add_grade/n");
    student* curr_student = course_exist(grades, id, name);
    printf("grades_add_grade       ");
    if(curr_student == NULL) return FAIL;
    printf("grades_add_grade       ");
    course* new_course = (course*)malloc(sizeof(course));
    printf("grades_add_grade       ");
    if(new_course == NULL) return FAIL;
    printf("grades_add_grade       ");
    char* new_name = (char*)malloc(sizeof(char)*(strlen(name)+1));
    printf("grades_add_grade       ");
    if(new_name == NULL) return FAIL;
    printf("grades_add_grade       ");
    strcpy(new_name, name);
    printf("grades_add_grade       ");
    new_course->course_name = new_name;
    printf("grades_add_grade       ");
    new_course->grade = grade;
    printf("grades_add_grade       ");
    if(list_push_back(curr_student->courses_list, new_course) == SUCCESS) {
        printf("grades_add_grade       ");
        course_destroy(new_course);
        printf("grades_add_grade       ");
        return SUCCESS;
    }
    else {
        printf("grades_add_grade       ");
        course_destroy(new_course);
        printf("grades_add_grade       ");
        return FAIL;
    }
}

float grades_calc_avg(struct grades *grades, int id, char **out){
    printf("grades_calc_avg       ");
    if(grades == NULL) return FAIL;
    printf("grades_calc_avg       ");
    student* curr_student = student_exist(grades, id);
    printf("grades_calc_avg       ");
    if(curr_student == NULL) return FAIL;
    printf("grades_calc_avg       ");
    *out = (char*)malloc(sizeof(char)*(strlen(curr_student->student_name)+1));
    printf("grades_calc_avg       ");
    if(*out == NULL) return FAIL;
    printf("grades_calc_avg       ");
    strcpy(*out, curr_student->student_name);
    printf("grades_calc_avg       ");
    int sum = 0;
    printf("grades_calc_avg       ");
    struct iterator* courses_it = list_begin(curr_student->courses_list);
    printf("grades_calc_avg       ");
    if(courses_it == NULL) return FAIL;
    printf("grades_calc_avg       ");
    size_t course_num = list_size(curr_student->courses_list);
    printf("grades_calc_avg       ");
    int counter = 0;
    printf("grades_calc_avg       ");
    for(size_t i=0; i<course_num; i++){
        course* curr_course = (course*)list_get(courses_it);
        if(curr_course == NULL) return FAIL;
        sum += curr_course->grade;
        courses_it = (struct iterator*)list_next(courses_it);
        if(courses_it == NULL) return FAIL;
        counter++;
    }
    printf("grades_calc_avg       ");
    return (float)sum/counter;
}

int grades_print_student(struct grades *grades, int id){
    printf("grades_print_student       ");
    if(grades == NULL) return FAIL;
    printf("grades_print_student       ");
    student* curr_student = student_exist(grades, id);
    printf("grades_print_student       ");
    if(curr_student == NULL) return FAIL;
    printf("grades_print_student       ");
    struct iterator* courses_it = list_begin(curr_student->courses_list);
    printf("grades_print_student       ");
    if(courses_it == NULL) return FAIL;
    printf("grades_print_student       ");
    size_t course_num = list_size(curr_student->courses_list);
    printf("grades_print_student       ");
    printf("%s %d: ", curr_student->student_name, curr_student->student_id);
    printf("grades_print_student       ");
    for(size_t i=0; i<course_num; i++){
        course* curr_course = (course*)list_get(courses_it);
        if(curr_course == NULL) return FAIL;
        printf("%s %d", curr_course->course_name, curr_course->grade);
        if(i != (course_num-1)) printf(", ");
        courses_it = (struct iterator*)list_next(courses_it);
        if(courses_it == NULL) return FAIL;
    }
    printf("grades_print_student       ");
    printf("/n");
    printf("grades_print_student       ");
    return SUCCESS;
}

int grades_print_all(struct grades *grades){
    printf("grades_print_all       ");
    if(grades == NULL) return FAIL;
    printf("grades_print_all       ");
    struct iterator* students_it = (struct iterator*)list_begin(grades->students_list);
    printf("grades_print_all       ");
    if(students_it == NULL) return FAIL;
    printf("grades_print_all       ");
    size_t students_num = list_size(grades->students_list);
    printf("grades_print_all       ");
    for(size_t i=0; i<students_num; i++){
        student* curr_student = (student*)list_get(students_it);
        if(curr_student == NULL) return FAIL;
        if(grades_print_student(grades, curr_student->student_id)) return FAIL;
        students_it = list_next(students_it);
        if(students_it == NULL) return FAIL;
    }
    printf("grades_print_all       ");
    return SUCCESS;
}
