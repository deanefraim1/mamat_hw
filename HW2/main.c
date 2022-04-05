#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#define YOYO 1.22
#define DOLL 2.75
#define DUCK 1.85
#define TRACKTOR 5.97
#define PLANE 6.47
#define BALL 2.16
#define RACE_CAR 7.13
#define DOG 4.57
#define ROPE 1.46
#define CAR 5.18
#define ELEPHANT 3.16
#define BEAR 4.89
#define KSILO 7.11
#define TANK 6.45
#define CHESS 4.77
#define BOAT 8.04
#define TRAIN 6.71
#define CUBES 2.31
#define TRUCK 6.21
#define WHISTLE 0.98
#define SHAVSHEVET 0.87
#define TOYS_NUM 21
#define MONEY 43.94
#define MAX_NUM 13

int toys_recursion(double prices[], int amount, double money_left, int index);

int main() {
    double prices[TOYS_NUM] = {YOYO , DOLL , DUCK , TRACKTOR , PLANE , BALL ,
                         RACE_CAR , ROPE , CAR , ELEPHANT , BEAR , KSILO ,
                         TANK , CHESS , BOAT , TRAIN , CUBES , TRUCK ,
                         WHISTLE , SHAVSHEVET};
    int result = toys_recursion(prices, 0, MONEY, 0);
    printf("%d\n", result);
    return 0;
}

int toys_recursion(double prices[], int amount, double money_left, int index) {
    if((amount == MAX_NUM) && (money_left == 0)) {
        return 1;
    }
    else if((amount >= MAX_NUM) || (money_left <= 0) || index >= TOYS_NUM) {
        return 0;
    }
    return (toys_recursion(prices, amount+1, money_left - prices[index], index+1) +
            toys_recursion(prices, amount, money_left, index+1));

}
