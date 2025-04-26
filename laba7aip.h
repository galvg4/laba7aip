#ifndef LABA7_H
#define LABA7_H

typedef struct {
    char name[100];
    int age;
    float height;
    float weight;
    char sport[50];
    char rank[50];
} Athlete;

void generate_random_athletes(Athlete* athletes, int count);
int compare_athletes(const Athlete* a, const Athlete* b, int ascending);
void bubble_sort(Athlete* array, int size, int ascending);
void quick_sort(Athlete* array, int left, int right, int ascending);
void select_sort(Athlete* array, int size, int ascending);
void print_athletes_table(const Athlete* athletes, int count);

#endif