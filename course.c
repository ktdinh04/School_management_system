#include "school_management.h"
#include <sys/stat.h>
#include <direct.h>

void addCourse(Course** head) {
    (void)head;
    struct _stat st = {0};
    if (_stat("database", &st) == -1) _mkdir("database");
    Course newCourse;
    printf("\n=== THEM MON HOC MOI ===\n");
    printf("Ma mon hoc: ");
    scanf("%s", newCourse.courseId);
    clearInputBuffer();
    printf("Ten mon hoc: ");
    fgets(newCourse.courseName, MAX_STRING, stdin);
    newCourse.courseName[strcspn(newCourse.courseName, "\n")] = 0;
    printf("So tin chi: ");
    scanf("%d", &newCourse.credits);
    printf("Ma giang vien phu trach: ");
    scanf("%s", newCourse.lecturerId);
    FILE* file = fopen("database/courses.csv", "a");
    if (file) {
        fprintf(file, "%s,%s,%d,%s\n", newCourse.courseId, newCourse.courseName, newCourse.credits, newCourse.lecturerId);
        fclose(file);
        printf("Them mon hoc thanh cong!\n");
    } else {
        printf("Khong the mo file database/courses.csv de ghi!\n");
    }
}

void displayCourses(Course* head) {
    (void)head;
    FILE* file = fopen("database/courses.csv", "r");
    if (!file) {
        printf("Khong the mo file database/courses.csv de doc hoac danh sach mon hoc trong!\n");
        return;
    }
    printf("\n=== DANH SACH MON HOC ===\n");
    printf("%-10s %-30s %-10s %-15s\n", "Ma MH", "Ten mon hoc", "Tin chi", "Ma GV");
    printf("===============================================================\n");
    char line[512];
    while (fgets(line, sizeof(line), file)) {
        // Skip empty lines
        if (line[0] == '\n' || line[0] == '\0') continue;
        char courseId[MAX_ID], courseName[MAX_STRING], lecturerId[MAX_ID];
        int credits;
        int n = sscanf(line, "%[^,],%[^,],%d,%[^\n]", courseId, courseName, &credits, lecturerId);
        if (n == 4) {
            // Remove leading/trailing spaces if any
            while (*courseName == ' ') memmove(courseName, courseName+1, strlen(courseName));
            while (*lecturerId == ' ') memmove(lecturerId, lecturerId+1, strlen(lecturerId));
            printf("%-10s %-30s %-10d %-15s\n", courseId, courseName, credits, lecturerId);
        }
    }
    fclose(file);
}

Course* findCourse(Course* head, char* courseId) {
    (void)head;
    FILE* file = fopen("database/courses.csv", "r");
    if (!file) return NULL;
    static Course found;
    char line[512];
    while (fgets(line, sizeof(line), file)) {
        char id[MAX_ID], name[MAX_STRING], lecturerId[MAX_ID];
        int credits;
        int n = sscanf(line, "%[^,],%[^,],%d,%[^\n]", id, name, &credits, lecturerId);
        if (n == 4 && strcmp(id, courseId) == 0) {
            strcpy(found.courseId, id);
            strcpy(found.courseName, name);
            found.credits = credits;
            strcpy(found.lecturerId, lecturerId);
            fclose(file);
            return &found;
        }
    }
    fclose(file);
    return NULL;
}

void updateCourse(Course* head, char* courseId) {
    (void)head;
    FILE* file = fopen("database/courses.csv", "r");
    if (!file) { printf("Khong the mo file!\n"); return; }
    Course list[1000]; int n = 0;
    char line[512]; int found = 0;
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%[^,],%d,%[^\n]", list[n].courseId, list[n].courseName, &list[n].credits, list[n].lecturerId);
        n++;
    }
    fclose(file);
    for (int i = 0; i < n; ++i) {
        if (strcmp(list[i].courseId, courseId) == 0) {
            found = 1;
            printf("\n=== CAP NHAT THONG TIN MON HOC ===\n");
            printf("Ma MH: %s\n", list[i].courseId);
            printf("Ten MH: %s\n", list[i].courseName);
            printf("So tin chi: %d\n", list[i].credits);
            printf("Ma GV phu trach: %s\n", list[i].lecturerId);
            char buffer[MAX_STRING];
            printf("Ten MH moi: ");
            fgets(buffer, MAX_STRING, stdin);
            if (strlen(buffer) > 1) { buffer[strcspn(buffer, "\n")] = 0; strcpy(list[i].courseName, buffer); }
            printf("So tin chi moi: ");
            fgets(buffer, MAX_STRING, stdin);
            if (strlen(buffer) > 1) { int c; if (sscanf(buffer, "%d", &c) == 1) list[i].credits = c; }
            printf("Ma GV phu trach moi: ");
            fgets(buffer, MAX_STRING, stdin);
            if (strlen(buffer) > 1) { buffer[strcspn(buffer, "\n")] = 0; strcpy(list[i].lecturerId, buffer); }
            printf("Cap nhat mon hoc thanh cong!\n");
            break;
        }
    }
    if (!found) { printf("Khong tim thay mon hoc co ma %s!\n", courseId); return; }
    file = fopen("database/courses.csv", "w");
    for (int i = 0; i < n; ++i)
        fprintf(file, "%s,%s,%d,%s\n", list[i].courseId, list[i].courseName, list[i].credits, list[i].lecturerId);
    fclose(file);
}

void deleteCourse(Course** head, char* courseId) {
    (void)head;
    FILE* file = fopen("database/courses.csv", "r");
    if (!file) { printf("Khong the mo file!\n"); return; }
    Course list[1000]; int n = 0, idx = -1;
    char line[512];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%[^,],%d,%[^\n]", list[n].courseId, list[n].courseName, &list[n].credits, list[n].lecturerId);
        if (strcmp(list[n].courseId, courseId) == 0) idx = n;
        n++;
    }
    fclose(file);
    if (idx == -1) { printf("Khong tim thay mon hoc co ma %s!\n", courseId); return; }
    for (int i = idx; i < n - 1; ++i) list[i] = list[i + 1];
    n--;
    file = fopen("database/courses.csv", "w");
    for (int i = 0; i < n; ++i)
        fprintf(file, "%s,%s,%d,%s\n", list[i].courseId, list[i].courseName, list[i].credits, list[i].lecturerId);
    fclose(file);
    printf("Xoa mon hoc thanh cong!\n");
}

void loadCoursesFromFile(Course** head, const char* filename) {
    // Free old list if any
    Course* cur = *head;
    while (cur) {
        Course* tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    *head = NULL;
    FILE* file = fopen(filename, "r");
    if (!file) return;
    char line[512];
    while (fgets(line, sizeof(line), file)) {
        Course* newCourse = (Course*)malloc(sizeof(Course));
        if (!newCourse) continue;
        if (sscanf(line, "%[^,],%[^,],%d,%[^,\n]", newCourse->courseId, newCourse->courseName, &newCourse->credits, newCourse->lecturerId) == 4) {
            newCourse->next = *head;
            *head = newCourse;
        } else {
            free(newCourse);
        }
    }
    fclose(file);
}
