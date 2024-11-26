#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define MAX_STUDENTS 100

// ����ѧ���ṹ��
struct Student {
    int id;
    char name[20];
    double score, chinese, math, eng;
};

// ��������
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
    int numStudents = 0; // ��ǰѧ������
    loadFromFile(students, &numStudents);
    int choice;
    system("cls");
    while (1) {
        system("cls");
        printf("----------ѧ���ɼ�����ϵͳ------------------------------------\n");
		printf("1. ¼��ѧ���ɼ�\n2. ��ʾѧ���ɼ�\n3. ����ѧ���ɼ�\n4. ����\n5. ��ʾͳ��\n6. �޸�ѧ����Ϣ\n7. ɾ��ѧ����Ϣ\n0. �˳�\n");
		printf("-------------------------------------------------------------\n");
        printf("��ѡ�� (0-7): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // ¼��
                inputStudents(students, &numStudents);
                break;
            case 2: // ��ʾ
                displayStudents(students, numStudents);
                break;
            case 3: { // ����
                int searchChoice;
                printf("1. ��ѧ�Ų���\n2. ����������\n0. ����\n");
                printf("��ѡ��: ");
                scanf("%d", &searchChoice);

                if (searchChoice == 1) {
                    int id;
                    printf("������ѧ��: ");
                    scanf("%d", &id);
                    int index = findById(students, numStudents, id);
                    system("cls");
                    if (index != -1) {
                        printf("�ҵ�ѧ��: %d %s %.2f\n"
                        , students[index].id, students[index].name, students[index].score);
                    } else {
                        printf("δ�ҵ���ѧ�Ŷ�Ӧ��ѧ����\n");
                    }
                    system("pause");
                } else if (searchChoice == 2) {
                    char name[20];
                    printf("����������: ");
                    scanf("%s", name);
                    int index = findByName(students, numStudents, name);
                    system("cls");
                    if (index != -1) {
                        printf("�ҵ�ѧ��: %d %s %.2f\n"
                        , students[index].id, students[index].name, students[index].score);
                    } else {
                        printf("δ�ҵ���������Ӧ��ѧ����\n");
                    }
                    system("pause");
                }
                break;
            }
            case 4: { // ����
                int sortChoice;
                printf("1. ��ѧ������ (����)\n2. ���ɼ����� (����)\n0. ����\n");
                printf("��ѡ��: ");
                scanf("%d", &sortChoice);

                if (sortChoice == 1) {
                    sortById(students, numStudents);
                    system("cls");
                    printf("��ѧ��������ɡ�\n");
                    system("pause");
                } else if (sortChoice == 2) {
                    sortByScore(students, numStudents);
                    system("cls");
                    printf("���ɼ�������ɡ�\n");
                    system("pause");
                }
            
                break;
            }
            case 5: // ͳ��
                displayStatistics(students, numStudents);
                break;
            case 6:
                modifyStudent(students, numStudents);
                break;
            case 7:
                deleteStudent(students, &numStudents);
                break;
            case 0: // �˳�
                printf("�����˳���\n");
                saveToFile(students, numStudents);
                return 0;
            default:
                printf("��Ч��ѡ�����������롣\n");
                Sleep(1000);
                system("cls");
        }
    }
}

// ����ʵ��

// ¼��ѧ����Ϣ
void inputStudents(struct Student students[], int *num) {
    int count;
    printf("������������ѧ������: ");
    scanf("%d", &count);

    for (int i = 0; i < count; i++) {
        printf("����� %d ��ѧ����Ϣ:\n", *num + 1);

        int id;
        printf("ѧ��: ");
        scanf("%d", &id);
        while (isDuplicateId(students, id, *num)) {
            printf("ѧ���ظ�������������: ");
            scanf("%d", &id);
        }
        students[*num].id = id;

        printf("����: ");
        scanf("%s", students[*num].name);

        double score,chinese, math, eng;

        printf("���ĳɼ� (0-100): ");
        scanf("%lf", &chinese);
        while (chinese < 0 || chinese > 100) {
            printf("�ɼ���Ч������������: ");
            scanf("%lf", &chinese);
        }
        students[*num].chinese = chinese;

        printf("��ѧ�ɼ� (0-100): ");
        scanf("%lf", &math);
        while (math < 0 || math > 100) {
            printf("�ɼ���Ч������������: ");
            scanf("%lf", &math);
        }
        students[*num].math = math;

        printf("Ӣ��ɼ� (0-100): ");
        scanf("%lf", &eng);
        while (eng < 0 || eng > 100) {
            printf("�ɼ���Ч������������: ");
            scanf("%lf", &eng);
        }
        students[*num].eng = eng;

        score = eng + math + chinese;//�����ܷ�
        students[*num].score = score;
        
        (*num)++;
    }
    printf("¼����ɡ�\n");
    system("pause");
}

// ��ʾ����ѧ����Ϣ
void displayStudents(const struct Student students[], int num) {
    system("cls");
    printf("ѧ��\t����\t�ɼ�\n");
    for (int i = 0; i < num; i++) {
        printf("%d\t%s\t%.2f\n", 
        students[i].id, students[i].name, students[i].score);
    }
    system("pause");
}

// ��ѧ�Ų���
int findById(const struct Student students[], int num, int id) {
    for (int i = 0; i < num; i++) {
        if (students[i].id == id) {
            return i;
        }
    }
    return -1;
}

// ����������
int findByName(const struct Student students[], int num, const char name[]) {
    for (int i = 0; i < num; i++) {
        if (strcmp(students[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

// ��ѧ������ (����)
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

// ���ɼ����� (����)
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

// ��ʾͳ����Ϣ
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

    printf("������: %d\n", num);
    printf("��߷�: %.2f\n", max);
    printf("��ͷ�: %.2f\n", min);
    printf("ƽ����: %.2f\n", sum / num);
    printf("�ɼ��ֲ�:\n");
    printf("90-100: %d\n", gradeCount[0]);
    printf("80-89 : %d\n", gradeCount[1]);
    printf("70-79 : %d\n", gradeCount[2]);
    printf("60-69 : %d\n", gradeCount[3]);
    printf("0-59  : %d\n", gradeCount[4]);
    system("pause");
}

// ���ѧ���Ƿ��ظ�
int isDuplicateId(const struct Student students[], int id, int num) {
    for (int i = 0; i < num; i++) {
        if (students[i].id == id) {
            return 1;
        }
    }
    return 0;
}

//�޸�ѧ����Ϣ
void modifyStudent(struct Student students[], int num) {
    int id;
    printf("������Ҫ�޸ĵ�ѧ��ѧ��: ");
    scanf("%d", &id);

    // ����ѧ��
    int index = findById(students, num, id);
    if (index == -1) {
        printf("δ�ҵ�ѧ��Ϊ %d ��ѧ����\n", id);
        system("pause");
        return;
    }

    // ��ʾ��ǰ��Ϣ
    printf("��ǰѧ����Ϣ:\n");
    printf("ѧ��: %d\n����: %s\n���ĳɼ�: %.2f\n��ѧ�ɼ�: %.2f\nӢ��ɼ�: %.2f\n�ܷ�: %.2f\n",
           students[index].id, students[index].name,
           students[index].chinese, students[index].math,
           students[index].eng, students[index].score);

    // �޸���Ϣ
    printf("�������µ���Ϣ (ֱ�Ӱ��س������޸�ĳ��):\n");

    printf("���� (��ǰ: %s): ", students[index].name);
    char newName[20];
    getchar(); // ����������Ļ��з�
    fgets(newName, 20, stdin);
    if (newName[0] != '\n') { // ����û���������ֵ
        newName[strcspn(newName, "\n")] = '\0'; // ȥ�����з�
        strcpy(students[index].name, newName);
    }

    printf("���ĳɼ� (��ǰ: %.2f): ", students[index].chinese);
    double chinese;
    if (scanf("%lf", &chinese) == 1 && chinese >= 0 && chinese <= 100) {
        students[index].chinese = chinese;
    }

    printf("��ѧ�ɼ� (��ǰ: %.2f): ", students[index].math);
    double math;
    if (scanf("%lf", &math) == 1 && math >= 0 && math <= 100) {
        students[index].math = math;
    }

    printf("Ӣ��ɼ� (��ǰ: %.2f): ", students[index].eng);
    double eng;
    if (scanf("%lf", &eng) == 1 && eng >= 0 && eng <= 100) {
        students[index].eng = eng;
    }

    // �����ܷ�
    students[index].score = students[index].chinese + students[index].math + students[index].eng;

    printf("�޸ĳɹ���\n");
    system("pause");
}

//ɾ��ѧ����Ϣ
void deleteStudent(struct Student students[], int *num) {
    int id;
    printf("������Ҫɾ����ѧ��ѧ��: ");
    scanf("%d", &id);

    // ����ѧ��
    int index = findById(students, *num, id);
    if (index == -1) {
        printf("δ�ҵ�ѧ��Ϊ %d ��ѧ����\n", id);
        system("pause");
        return;
    }

    // ȷ��ɾ��
    char confirm;
    printf("ȷ��ɾ��ѧ��Ϊ %d ��ѧ�� (%s)? (Y/N): ", id, students[index].name);
    getchar(); // ����������Ļ��з�
    scanf("%c", &confirm);

    if (confirm == 'Y' || confirm == 'y') {
        // ɾ��ѧ����������ѧ����������ǰ��
        for (int i = index; i < *num - 1; i++) {
            students[i] = students[i + 1];
        }
        (*num)--; // ѧ��������1
        printf("ɾ���ɹ���\n");
    } else {
        printf("ɾ��������ȡ����\n");
    }

    system("pause");
}

//����ѧ���ɼ�Ϊ�ļ�
void saveToFile(struct Student students[], int num) {
    FILE *file = fopen("students.txt", "w");
    if (file == NULL) {
        printf("�޷����ļ����б��档\n");
        return;
    }

    for (int i = 0; i < num; i++) {
        fprintf(file, "%d %s %.2f %.2f %.2f %.2f\n", 
                students[i].id, students[i].name, 
                students[i].chinese, students[i].math, 
                students[i].eng, students[i].score);
    }

    fclose(file);
    printf("�����ѱ��档\n");
}

//���ļ���ȡѧ������
void loadFromFile(struct Student students[], int *num) {
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("û���ҵ�����������ļ��������Կ�����������\n");

        return;
    }

    while (fscanf(file, "%d %s %lf %lf %lf %lf", 
                   &students[*num].id, students[*num].name, 
                   &students[*num].chinese, &students[*num].math, 
                   &students[*num].eng, &students[*num].score) == 6) {
        (*num)++;
    }

    fclose(file);
    printf("�����Ѽ��ء�\n");
}
