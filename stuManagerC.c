#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define MAX_STUDENTS 100

// 定义学生结构体
struct Student {
    int id;
    char name[20];
    double score, chinese, math, eng;
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
void modifyStudent(struct Student students[], int num);
void deleteStudent(struct Student students[], int *num);
void saveToFile(struct Student students[], int num);
void loadFromFile(struct Student students[], int *num);

int main() {
    struct Student students[MAX_STUDENTS];
    int numStudents = 0; // 当前学生人数
    loadFromFile(students, &numStudents);
    int choice;
    system("cls");
    while (1) {
        system("cls");
        printf("----------学生成绩管理系统------------------------------------\n");
		printf("1. 录入学生成绩\n2. 显示学生成绩\n3. 查找学生成绩\n4. 排序\n5. 显示统计\n6. 修改学生信息\n7. 删除学生信息\n0. 退出\n");
		printf("-------------------------------------------------------------\n");
        printf("请选择 (0-7): ");
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
                    system("cls");
                    if (index != -1) {
                        printf("找到学生: %d %s %.2f\n"
                        , students[index].id, students[index].name, students[index].score);
                    } else {
                        printf("未找到该学号对应的学生。\n");
                    }
                    system("pause");
                } else if (searchChoice == 2) {
                    char name[20];
                    printf("请输入姓名: ");
                    scanf("%s", name);
                    int index = findByName(students, numStudents, name);
                    system("cls");
                    if (index != -1) {
                        printf("找到学生: %d %s %.2f\n"
                        , students[index].id, students[index].name, students[index].score);
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
                    system("cls");
                    printf("按学号排序完成。\n");
                    system("pause");
                } else if (sortChoice == 2) {
                    sortByScore(students, numStudents);
                    system("cls");
                    printf("按成绩排序完成。\n");
                    system("pause");
                }
            
                break;
            }
            case 5: // 统计
                displayStatistics(students, numStudents);
                break;
            case 6:
                modifyStudent(students, numStudents);
                break;
            case 7:
                deleteStudent(students, &numStudents);
                break;
            case 0: // 退出
                printf("程序退出。\n");
                saveToFile(students, numStudents);
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

        double score,chinese, math, eng;

        printf("语文成绩 (0-100): ");
        scanf("%lf", &chinese);
        while (chinese < 0 || chinese > 100) {
            printf("成绩无效，请重新输入: ");
            scanf("%lf", &chinese);
        }
        students[*num].chinese = chinese;

        printf("数学成绩 (0-100): ");
        scanf("%lf", &math);
        while (math < 0 || math > 100) {
            printf("成绩无效，请重新输入: ");
            scanf("%lf", &math);
        }
        students[*num].math = math;

        printf("英语成绩 (0-100): ");
        scanf("%lf", &eng);
        while (eng < 0 || eng > 100) {
            printf("成绩无效，请重新输入: ");
            scanf("%lf", &eng);
        }
        students[*num].eng = eng;

        score = eng + math + chinese;//计算总分
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
        printf("%d\t%s\t%.2f\n", 
        students[i].id, students[i].name, students[i].score);
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

//修改学生信息
void modifyStudent(struct Student students[], int num) {
    int id;
    printf("请输入要修改的学生学号: ");
    scanf("%d", &id);

    // 查找学生
    int index = findById(students, num, id);
    if (index == -1) {
        printf("未找到学号为 %d 的学生。\n", id);
        system("pause");
        return;
    }

    // 显示当前信息
    printf("当前学生信息:\n");
    printf("学号: %d\n姓名: %s\n语文成绩: %.2f\n数学成绩: %.2f\n英语成绩: %.2f\n总分: %.2f\n",
           students[index].id, students[index].name,
           students[index].chinese, students[index].math,
           students[index].eng, students[index].score);

    // 修改信息
    printf("请输入新的信息 (直接按回车跳过修改某项):\n");

    printf("姓名 (当前: %s): ", students[index].name);
    char newName[20];
    getchar(); // 清除缓冲区的换行符
    fgets(newName, 20, stdin);
    if (newName[0] != '\n') { // 如果用户输入了新值
        newName[strcspn(newName, "\n")] = '\0'; // 去掉换行符
        strcpy(students[index].name, newName);
    }

    printf("语文成绩 (当前: %.2f): ", students[index].chinese);
    double chinese;
    if (scanf("%lf", &chinese) == 1 && chinese >= 0 && chinese <= 100) {
        students[index].chinese = chinese;
    }

    printf("数学成绩 (当前: %.2f): ", students[index].math);
    double math;
    if (scanf("%lf", &math) == 1 && math >= 0 && math <= 100) {
        students[index].math = math;
    }

    printf("英语成绩 (当前: %.2f): ", students[index].eng);
    double eng;
    if (scanf("%lf", &eng) == 1 && eng >= 0 && eng <= 100) {
        students[index].eng = eng;
    }

    // 更新总分
    students[index].score = students[index].chinese + students[index].math + students[index].eng;

    printf("修改成功！\n");
    system("pause");
}

//删除学生信息
void deleteStudent(struct Student students[], int *num) {
    int id;
    printf("请输入要删除的学生学号: ");
    scanf("%d", &id);

    // 查找学生
    int index = findById(students, *num, id);
    if (index == -1) {
        printf("未找到学号为 %d 的学生。\n", id);
        system("pause");
        return;
    }

    // 确认删除
    char confirm;
    printf("确认删除学号为 %d 的学生 (%s)? (Y/N): ", id, students[index].name);
    getchar(); // 清除缓冲区的换行符
    scanf("%c", &confirm);

    if (confirm == 'Y' || confirm == 'y') {
        // 删除学生：将后续学生的数据往前移
        for (int i = index; i < *num - 1; i++) {
            students[i] = students[i + 1];
        }
        (*num)--; // 学生人数减1
        printf("删除成功！\n");
    } else {
        printf("删除操作已取消。\n");
    }

    system("pause");
}

//保存学生成绩为文件
void saveToFile(struct Student students[], int num) {
    FILE *file = fopen("students.txt", "w");
    if (file == NULL) {
        printf("无法打开文件进行保存。\n");
        return;
    }

    for (int i = 0; i < num; i++) {
        fprintf(file, "%d %s %.2f %.2f %.2f %.2f\n", 
                students[i].id, students[i].name, 
                students[i].chinese, students[i].math, 
                students[i].eng, students[i].score);
    }

    fclose(file);
    printf("数据已保存。\n");
}

//从文件读取学生数据
void loadFromFile(struct Student students[], int *num) {
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("没有找到保存的数据文件，程序将以空数据启动。\n");

        return;
    }

    while (fscanf(file, "%d %s %lf %lf %lf %lf", 
                   &students[*num].id, students[*num].name, 
                   &students[*num].chinese, &students[*num].math, 
                   &students[*num].eng, &students[*num].score) == 6) {
        (*num)++;
    }

    fclose(file);
    printf("数据已加载。\n");
}
