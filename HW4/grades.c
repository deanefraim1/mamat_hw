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
} Student_t;

typedef struct {
    char* course_name;
    int grade;
} Course_t;

static int student_clone(void *element, void **output);
static int course_clone(void *element, void **output);
static void student_destroy(void *element);
static void course_destroy(void *element);
struct grades* grades_init(void);
void grades_destroy(struct grades *grades);
static Student_t* student_exist(struct grades *grades, int id);
int grades_add_student(struct grades *grades, const char *name, int id);
static Student_t* course_exist(struct grades *grades, int id,
                               const char *course_name);
int grades_add_grade(struct grades *grades, const char *name, int id,
                     int grade);
float grades_calc_avg(struct grades *grades, int id, char **out);
int grades_print_student(struct grades *grades, int id);
int grades_print_all(struct grades *grades);

static int student_clone(void *element, void **output){
    Student_t* new_student = (Student_t*)malloc(sizeof(Student_t));
    if(new_student == NULL) return FAIL;
    Student_t* student_data = (Student_t*)element;
    new_student->student_id = student_data->student_id;
    new_student->student_name =
        (char*)malloc((strlen(student_data->student_name)+1)*sizeof(char));
    if(new_student->student_name == NULL) return FAIL;
    strcpy(new_student->student_name, student_data->student_name);
    new_student->courses_list = list_init(course_clone, course_destroy);
    *output = (void*)new_student;
    return SUCCESS;
}

static int course_clone(void *element, void **output){
    Course_t* new_course = (Course_t*)malloc(sizeof(Course_t));
    if(new_course == NULL) return FAIL;
    Course_t* course_data = (Course_t*)element;
    new_course->course_name =
        (char*)malloc((strlen(course_data->course_name)+1)*sizeof(char));
    if(new_course->course_name == NULL) return FAIL;
    strcpy(new_course->course_name, course_data->course_name);
    new_course->grade = course_data->grade;
    *output = (void*)new_course;
    return SUCCESS;
}

static void student_destroy(void *element){
    Student_t* student_d = (Student_t*)element;
    list_destroy(student_d->courses_list);
    free(student_d->student_name);
    free(student_d);
}

static void course_destroy(void *element){
    Course_t* course_d = (Course_t*)element;
    free(course_d->course_name);
    free(course_d);
}

struct grades* grades_init(void){
    struct grades* grades_p = (struct grades*)malloc(sizeof(struct grades));
    if(grades_p == NULL) return NULL;
    grades_p->students_list = list_init(student_clone, student_destroy);
    if(grades_p->students_list == NULL) return NULL;
    return grades_p;
}

void grades_destroy(struct grades *grades){
    list_destroy(grades->students_list);
    free(grades);
}

static Student_t* student_exist(struct grades *grades, int id){
    struct iterator* students_it =
        (struct iterator*)list_begin(grades->students_list);
    size_t students_num = list_size(grades->students_list);
    if((students_it == NULL) && (students_num != 0)) return NULL;
    for(size_t i=0; i<students_num; i++){
        Student_t* curr_student = (Student_t*)list_get(students_it);
        if(curr_student == NULL) return NULL;
        if(curr_student->student_id == id) return curr_student;
        students_it = list_next(students_it);
    }
    return NULL;
}

int grades_add_student(struct grades *grades, const char *name, int id){
    if(grades == NULL) return FAIL;
    if(student_exist(grades,id) != NULL) return FAIL;
    Student_t* new_student = (Student_t*)malloc(sizeof(Student_t));
    if(new_student == NULL) return FAIL;
    char* new_name = (char*)malloc(sizeof(char)*(strlen(name)+1));
    if(new_name == NULL) return FAIL;
    strcpy(new_name, name);
    new_student->student_name = new_name;
    new_student->student_id = id;
    new_student->courses_list = list_init(course_clone, course_destroy);
    if(new_student->courses_list == NULL) return FAIL;
    if(list_push_back(grades->students_list, new_student) == SUCCESS) {
        student_destroy(new_student);
        return SUCCESS;
    }
    else {
        student_destroy(new_student);
        return FAIL;
    }
}

static Student_t* course_exist(struct grades *grades, int id,
                               const char *course_name){
    Student_t* curr_student = student_exist(grades, id);
    if(curr_student == NULL) return NULL;
    struct iterator* courses_it = list_begin(curr_student->courses_list);
    size_t course_num = list_size(curr_student->courses_list);
    if((courses_it == NULL) && (course_num != 0)) return NULL;
    for(size_t i=0; i<course_num; i++){
        Course_t* curr_course = (Course_t*)list_get(courses_it);
        if(curr_course == NULL) return NULL;
        if(!strcmp(curr_course->course_name, course_name)) return NULL;
        courses_it = (struct iterator*)list_next(courses_it);
    }
    return curr_student;
}

int grades_add_grade(struct grades *grades, const char *name, int id,
                     int grade){
    if((grades == NULL) || (grade < MIN_GRADE) || (grade > MAX_GRADE))
        return FAIL;
    Student_t* curr_student = course_exist(grades, id, name);
    if(curr_student == NULL) return FAIL;
    Course_t* new_course = (Course_t*)malloc(sizeof(Course_t));
    if(new_course == NULL) return FAIL;
    char* new_name = (char*)malloc(sizeof(char)*(strlen(name)+1));
    if(new_name == NULL) return FAIL;
    strcpy(new_name, name);
    new_course->course_name = new_name;
    new_course->grade = grade;
    if(list_push_back(curr_student->courses_list, new_course) == SUCCESS) {
        course_destroy(new_course);
        return SUCCESS;
    }
    else {
        course_destroy(new_course);
        return FAIL;
    }
}

float grades_calc_avg(struct grades *grades, int id, char **out){
    if(grades == NULL) return FAIL;
    Student_t* curr_student = student_exist(grades, id);
    if(curr_student == NULL) return FAIL;
    *out =
        (char*)malloc(sizeof(char)*(strlen(curr_student->student_name)+1));
    if(*out == NULL) return FAIL;
    strcpy(*out, curr_student->student_name);
    float sum = 0.0;
    struct iterator* courses_it = list_begin(curr_student->courses_list);
    size_t course_num = list_size(curr_student->courses_list);
    if((courses_it == NULL) && (course_num != 0)) return FAIL;
    int counter = 0;
    for(size_t i=0; i<course_num; i++){
        Course_t* curr_course = (Course_t*)list_get(courses_it);
        if(curr_course == NULL) return FAIL;
        sum += curr_course->grade;
        courses_it = (struct iterator*)list_next(courses_it);
        counter++;
    }
    if(counter == 0) return 0.0;
    else return (float)sum/counter;
}

int grades_print_student(struct grades *grades, int id){
    if(grades == NULL) return FAIL;
    Student_t* curr_student = student_exist(grades, id);
    if(curr_student == NULL) return FAIL;
    struct iterator* courses_it = list_begin(curr_student->courses_list);
    size_t course_num = list_size(curr_student->courses_list);
    if((courses_it == NULL) && (course_num != 0)) return FAIL;
    printf("%s %d:", curr_student->student_name, curr_student->student_id);
    for(size_t i=0; i<course_num; i++){
        Course_t* curr_course = (Course_t*)list_get(courses_it);
        if(curr_course == NULL) return FAIL;
        printf(" %s %d", curr_course->course_name, curr_course->grade);
        if(i != (course_num-1)) printf(",");
        courses_it = (struct iterator*)list_next(courses_it);
    }
    printf("\n");
    return SUCCESS;
}

int grades_print_all(struct grades *grades){
    if(grades == NULL) return FAIL;
    struct iterator* students_it =
        (struct iterator*)list_begin(grades->students_list);
    size_t students_num = list_size(grades->students_list);
    if((students_it == NULL) && (students_num != 0)) return FAIL;
    for(size_t i=0; i<students_num; i++){
        Student_t* curr_student = (Student_t*)list_get(students_it);
        if(curr_student == NULL) return FAIL;
        if(grades_print_student(grades, curr_student->student_id))
            return FAIL;
        students_it = list_next(students_it);
    }
    return SUCCESS;
}
