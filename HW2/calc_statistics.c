#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FAIL 55
#define SIZE 10

int num_of_students(FILE *fp_grades);
float grades_avg(int grades_arr[], int students_num);
void grades_arr_build(FILE *fp_grades, int students_num, int grades_arr[]);
void swap(int* pointer_a, int* pointer_b);
void bubble_sort_recursion(int a[], int n);
int bubble(int a[], int n);
float pass_prec(int grades_arr[], int students_num);
void build_hist(int grades_arr[], int students_num, int hist[SIZE][SIZE]);
void print(FILE *fp_stats, int students_num, float avg, int medain,
           int max_grade, int min_grade,  float pass_rate,
           int hist[SIZE][SIZE]);


int main(int argc, char *argv[]) {
    if (argc < 1) {
        fprintf(stderr, "Error\n");
        return 1;
    }
    FILE *fp_stats = NULL;
    FILE *fp_grades = NULL;
    fp_stats = fopen(argv[1], "w");
    fp_grades = fopen(argv[2], "r");
    if((fp_stats == NULL) || (fp_grades == NULL)) {
        fprintf(stderr, "Error\n");
        return 1;
    }
    int students_num = num_of_students(fp_grades);
    int *grades_arr = NULL;
    grades_arr = malloc(sizeof(int)*students_num);
    if(grades_arr == NULL) {
        fprintf(stderr, "Error\n");
        return 1;
    }
    grades_arr_build(fp_grades, students_num, grades_arr);
    bubble_sort_recursion(grades_arr, students_num);
    float avg = grades_avg(grades_arr, students_num);
    int median = grades_arr[(students_num+1)/2];
    int max_grade = grades_arr[students_num-1];
    int min_grade = grades_arr[0];
    float pass_rate = pass_prec(grades_arr, students_num);
    int hist[SIZE][SIZE] = { 0 };
    build_hist(grades_arr, students_num, hist);
    print(fp_stats, students_num, avg, median, max_grade,
          min_grade, pass_rate, hist);
    free(grades_arr);
    fclose(fp_stats);
    fclose(fp_grades);
    return 0;
}

int num_of_students(FILE *fp_grades) {
    int line_counter = 0;
    char c;
    do {
        c = fgetc(fp_grades);
        if (c == '\n') {
            line_counter++;
        }
    } while (c != EOF);
    fseek(fp_grades, 0, SEEK_SET);
    return line_counter;
}

void grades_arr_build(FILE *fp_grades, int students_num, int grades_arr[]) {
    int curr_student = 0;
    while((!feof(fp_grades)) && (curr_student < students_num)) {
        fscanf(fp_grades, "%d", &grades_arr[curr_student++]);
    }
}

float grades_avg(int grades_arr[], int students_num) {
    float sum = 0;
    for(int i=0; i<students_num; i++) {
        sum += grades_arr[i];
    }
    return (sum/students_num);
}

void swap(int* pointer_a, int* pointer_b)
{
    int temp = *pointer_b;
    *pointer_b = *pointer_a;
    *pointer_a = temp;
}

int bubble(int a[], int n)
{
    int swapped = 0;
    for (int i = 0; i < n-1; i++)
    {
        if (a[i] > a[i + 1])
        {
            swap(&a[i], &a[i + 1]);
            swapped = 1;
        }
    }
    return swapped;
}

void bubble_sort_recursion(int a[], int n)
{
    if ((n == 1) || !(bubble(a, n))) return;
    bubble_sort_recursion(a, n - 1);
}

float pass_prec(int grades_arr[], int students_num) {
    int counter = 0;
    while(grades_arr[counter]<FAIL) {
        counter++;
    }
    return (((float)(students_num-counter)/(float)students_num)*100);
}

void build_hist(int grades_arr[], int students_num, int hist[SIZE][SIZE]) {
    for(int i=0; i<students_num; i++) {
        hist[(grades_arr[i]-1)/10][(grades_arr[i]-1)%10]++;
    }
}

void print(FILE *fp_stats, int students_num, float avg, int median,
           int max_grade, int min_grade,  float pass_rate,
           int hist[SIZE][SIZE]) {
    fprintf(fp_stats, "num of students = %d\n", students_num);
    fprintf(fp_stats, "avg = %0.3f\n", avg);
    fprintf(fp_stats, "the median is - %d\n", median);
    fprintf(fp_stats, "max grade = %d, min grade = %d\n", max_grade, min_grade);
    fprintf(fp_stats, "pass rate = %0.2f%%\n", pass_rate);
    for(int i=0; i<SIZE; i++) {
        for(int j=0; j<SIZE; j++) {
            fprintf(fp_stats, "%d ", hist[i][j]);
        }
        fprintf(fp_stats, "\n");
    }
}
