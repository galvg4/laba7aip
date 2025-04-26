#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include "laba7aip.h"

const char* randomNames[] = {
    "������ ���� ��������", "������ ���� ��������",
    "������� ������� ����������", "������� ���� ���������",
    "������� ������� ������������", "�������� ��������� ���������"
};

const char* randomSports[] = {
    "������ ��������", "��������", "����������",
    "����", "���������", "������"
};

const char* randomRanks[] = {
    "���", "������ ������", "���",
    "1 ������", "2 ������", "3 ������"
};

void generate_random_athletes(Athlete* athletes, int count) {
    int names_count = sizeof(randomNames) / sizeof(randomNames[0]);
    int sports_count = sizeof(randomSports) / sizeof(randomSports[0]);
    int ranks_count = sizeof(randomRanks) / sizeof(randomRanks[0]);

    for (int i = 0; i < count; i++) {
        strcpy(athletes[i].name, randomNames[rand() % names_count]);
        athletes[i].age = 16 + rand() % 20; // 16-35 ���
        athletes[i].height = 150.0f + rand() % 50 + (float)rand() / RAND_MAX;
        athletes[i].weight = 50.0f + rand() % 50 + (float)rand() / RAND_MAX;
        strcpy(athletes[i].sport, randomSports[rand() % sports_count]);
        strcpy(athletes[i].rank, randomRanks[rand() % ranks_count]);
    }
}

int compare_athletes(const Athlete* a, const Athlete* b, int ascending) {
    // ��������� �� �����
    int result = strcmp(a->name, b->name);
    if (result != 0) return ascending ? result : -result;

    // ��������� �� ��������
    if (a->age != b->age)
        return ascending ? (a->age - b->age) : (b->age - a->age);

    // ��������� �� �����
    if (a->height != b->height)
        return (a->height > b->height) ? (ascending ? 1 : -1) : (ascending ? -1 : 1);

    // ��������� �� ����
    if (a->weight != b->weight)
        return (a->weight > b->weight) ? (ascending ? 1 : -1) : (ascending ? -1 : 1);

    // ��������� �� ���� ������
    result = strcmp(a->sport, b->sport);
    if (result != 0) return ascending ? result : -result;

    // ��������� �� ������
    result = strcmp(a->rank, b->rank);
    return ascending ? result : -result;
}

void bubble_sort(Athlete* array, int size, int ascending) {
    for (int i = size - 1; i >= 0; i--) {
        for (int j = 0; j < i; j++) {
            if (compare_athletes(&array[j], &array[j + 1], ascending) > 0) {
                Athlete temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void quick_sort(Athlete* array, int left, int right, int ascending) {
    if (left < right) {
        int i = left, j = right;
        Athlete pivot = array[(i + j) / 2];
        do {
            while (compare_athletes(&array[i], &pivot, ascending) < 0) i++;
            while (compare_athletes(&array[j], &pivot, ascending) > 0) j--;
            if (i <= j) {
                Athlete temp = array[i];
                array[i] = array[j];
                array[j] = temp;
                i++; j--;
            }
        } while (i <= j);
        quick_sort(array, left, j, ascending);
        quick_sort(array, i, right, ascending);
    }
}

void select_sort(Athlete* array, int size, int ascending) {
    for (int i = 0; i < size - 1; i++) {
        int ext = i;
        for (int j = i + 1; j < size; j++) {
            if (compare_athletes(&array[j], &array[ext], ascending) < 0) {
                ext = j;
            }
        }
        if (ext != i) {
            Athlete temp = array[i];
            array[i] = array[ext];
            array[ext] = temp;
        }
    }
}

void print_athletes_table(const Athlete* athletes, int count) {
    printf("\n%-25s %-4s %-6s %-6s %-20s %-15s\n",
        "���", "����", "����", "���", "��� ������", "������");
    puts("--------------------------------------------------------------"
        "-------------------");

    for (int i = 0; i < count; i++) {
        printf("%-25s %-4d %-6.1f %-6.1f %-20s %-15s\n",
            athletes[i].name,
            athletes[i].age,
            athletes[i].height,
            athletes[i].weight,
            athletes[i].sport,
            athletes[i].rank);
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    srand((unsigned int)time(NULL));

    // ����� ������ ��������
    int sizes[] = { 100, 1000, 10000, 50000, 100000, 200000, 300000 };
    int method = 0, dir = 0;

    // ����� ���������
    while (1) {
        printf("\n�������� �������� ����������:\n");
        printf("1. �����������\n2. �������\n3. �������\n4. �����\n> ");
        scanf("%d", &method);
        if (method == 4) return 0;
        if (method >= 1 && method <= 3) break;
        printf("������! ������� ����� �� 1 �� 4\n");
    }

    // ����� �����������
    while (1) {
        printf("\n�������� ����������� ����������:\n");
        printf("1. �� ����������\n2. �� �������������\n> ");
        scanf("%d", &dir);
        if (dir == 1 || dir == 2) break;
        printf("������! ������� 1 ��� 2\n");
    }

    const int ascending = (dir == 1);

    for (int i = 0; i < sizeof(sizes) / sizeof(sizes[0]); i++) {
        const int size = sizes[i];
        Athlete* team = (Athlete*)malloc(sizeof(Athlete) * size);
        generate_random_athletes(team, size);

        if (size == 100) {  // ����� ��� ������� ����������� 100, ������ 10
            printf("\n�������� ������ (%d �������):", size);
            print_athletes_table(team, size);
        }

        clock_t start = clock();
        switch (method) {
        case 1: bubble_sort(team, size, ascending); break;
        case 2: quick_sort(team, 0, size - 1, ascending); break;
        case 3: select_sort(team, size, ascending); break;
        }
        clock_t end = clock();

        if (size == 100) {
            printf("\n��������� ����������:");
            print_athletes_table(team, size);
        }

        printf("����� ���������� %d ���������: %.3f ���.\n",
            size, (double)(end - start) / CLOCKS_PER_SEC);
        free(team);
    }

    return 0;
}
