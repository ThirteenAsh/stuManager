#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define MAX_STUDENTS 100

// 定义学生结构体
struct Student {
    int id;
    char name[20];
    double score;
};

// 函数声明
void inputStudents(struct Student students[], int *num);
void displayStudents(const struct Student students[], int num);
int findById(const struct Student students[], int num, int id);
int findByName(const struct Student students[], int num, const char name[]);
void sortById(struct Student students[], int num);
void sortByScore(struct Student students[], int num);
void displayStatistics(const struct Student students[], int num);
int isDuplicateId(const struct Student students[], int id, int num);

int main() {
    struct Student students[MAX_STUDENTS];
    int numStudents = 0; // 当前学生人数
    int choice;
    system("cls");
    while (1) {
        system("cls");
        printf("\n--------- 学生成绩管理系统 ---------\n");
        printf("1. 录入学生成绩\n2. 显示学生成绩\n3. 查找学生成绩\n4. 排序\n5. 显示统计\n0. 退出\n");
        printf("-------------------------------------\n");
        printf("请选择 (0-5): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // 录入
                inputStudents(students, &numStudents);
                break;
            case 2: // 显示
                displayStudents(students, numStudents);
                break;
            case 3: { // 查找
                int searchChoice;
                printf("1. 按学号查找\n2. 按姓名查找\n0. 返回\n");
                printf("请选择: ");
                scanf("%d", &searchChoice);

                if (searchChoice == 1) {
                    int id;
                    printf("请输入学号: ");
                    scanf("%d", &id);
                    int index = findById(students, numStudents, id);
                    if (index != -1) {
                        printf("找到学生: %d %s %.2f\n", students[index].id, students[index].name, students[index].score);
                    } else {
                        printf("未找到该学号对应的学生。\n");
                    }
                    system("pause");
                } else if (searchChoice == 2) {
                    char name[20];
                    printf("请输入姓名: ");
                    scanf("%s", name);
                    int index = findByName(students, numStudents, name);
                    if (index != -1) {
                        printf("找到学生: %d %s %.2f\n", students[index].id, students[index].name, students[index].score);
                    } else {
                        printf("未找到该姓名对应的学生。\n");
                    }
                    system("pause");
                }
                break;
            }
            case 4: { // 排序
                int sortChoice;
                printf("1. 按学号排序 (升序)\n2. 按成绩排序 (降序)\n0. 返回\n");
                printf("请选择: ");
                scanf("%d", &sortChoice);

                if (sortChoice == 1) {
                    sortById(students, numStudents);
                    printf("按学号排序完成。\n");
                    system("pause");
                } else if (sortChoice == 2) {
                    sortByScore(students, numStudents);
                    printf("按成绩排序完成。\n");
                    system("pause");
                }
            
                break;
            }
            case 5: // 统计
                displayStatistics(students, numStudents);
                break;
            case 0: // 退出
                printf("程序退出。\n");
                return 0;
            default:
                printf("无效的选择，请重新输入。\n");
                Sleep(1000);
                system("cls");
        }
    }
}

// 函数实现

// 录入学生信息
void inputStudents(struct Student students[], int *num) {
    int count;
    printf("请输入新增的学生人数: ");
    scanf("%d", &count);

    for (int i = 0; i < count; i++) {
        printf("输入第 %d 个学生信息:\n", *num + 1);

        int id;
        printf("学号: ");
        scanf("%d", &id);
        while (isDuplicateId(students, id, *num)) {
            printf("学号重复，请重新输入: ");
            scanf("%d", &id);
        }
        students[*num].id = id;

        printf("姓名: ");
        scanf("%s", students[*num].name);

        double score;
        printf("成绩 (0-100): ");
        scanf("%lf", &score);
        while (score < 0 || score > 100) {
            printf("成绩无效，请重新输入: ");
            scanf("%lf", &score);
        }
        students[*num].score = score;

        (*num)++;
    }
    printf("录入完成。\n");
    system("pause");
}

// 显示所有学生信息
void displayStudents(const struct Student students[], int num) {
    system("cls");
    printf("学号\t姓名\t成绩\n");
    for (int i = 0; i < num; i++) {
        printf("%d\t%s\t%.2f\n", students[i].id, students[i].name, students[i].score);
    }
    system("pause");
}

// 按学号查找
int findById(const struct Student students[], int num, int id) {
    for (int i = 0; i < num; i++) {
        if (students[i].id == id) {
            return i;
        }
    }
    return -1;
}

// 按姓名查找
int findByName(const struct Student students[], int num, const char name[]) {
    for (int i = 0; i < num; i++) {
        if (strcmp(students[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

// 按学号排序 (升序)
void sortById(struct Student students[], int num) {
    for (int i = 0; i < num - 1; i++) {
        for (int j = i + 1; j < num; j++) {
            if (students[i].id > students[j].id) {
                struct Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
}

// 按成绩排序 (降序)
void sortByScore(struct Student students[], int num) {
    for (int i = 0; i < num - 1; i++) {
        for (int j = i + 1; j < num; j++) {
            if (students[i].score < students[j].score) {
                struct Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
}

// 显示统计信息
void displayStatistics(const struct Student students[], int num) {
    system("cls");
    double sum = 0, max = students[0].score, min = students[0].score;
    int gradeCount[5] = {0};

    for (int i = 0; i < num; i++) {
        sum += students[i].score;
        if (students[i].score > max) max = students[i].score;
        if (students[i].score < min) min = students[i].score;

        if (students[i].score >= 90) gradeCount[0]++;
        else if (students[i].score >= 80) gradeCount[1]++;
        else if (students[i].score >= 70) gradeCount[2]++;
        else if (students[i].score >= 60) gradeCount[3]++;
        else gradeCount[4]++;
    }

    printf("总人数: %d\n", num);
    printf("最高分: %.2f\n", max);
    printf("最低分: %.2f\n", min);
    printf("平均分: %.2f\n", sum / num);
    printf("成绩分布:\n");
    printf("90-100: %d\n", gradeCount[0]);
    printf("80-89 : %d\n", gradeCount[1]);
    printf("70-79 : %d\n", gradeCount[2]);
    printf("60-69 : %d\n", gradeCount[3]);
    printf("0-59  : %d\n", gradeCount[4]);
    system("pause");
}

// 检查学号是否重复
int isDuplicateId(const struct Student students[], int id, int num) {
    for (int i = 0; i < num; i++) {
        if (students[i].id == id) {
            return 1;
        }
    }
    return 0;
}
