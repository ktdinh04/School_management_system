#include "school_management.h"
#include <sys/stat.h>
#include <direct.h>

void addCourse(Course** head) {
    Course* newCourse = (Course*)malloc(sizeof(Course));
    if (!newCourse) {
        printf("Loi cap phat bo nho!\n");
        return;
    }
    
    printf("\n=== THEM MON HOC MOI ===\n");
    printf("Ma mon hoc: ");
    scanf("%s", newCourse->courseId);
    clearInputBuffer();
    
    printf("Ten mon hoc: ");
    fgets(newCourse->courseName, MAX_STRING, stdin);
    newCourse->courseName[strcspn(newCourse->courseName, "\n")] = 0;
    
    printf("So tin chi: ");
    scanf("%d", &newCourse->credits);
    
    printf("Ma giang vien phu trach: ");
    scanf("%s", newCourse->lecturerId);
    
    newCourse->next = *head;
    *head = newCourse;
    
    printf("Them mon hoc thanh cong!\n");
}

void displayCourses(Course* head) {
    if (!head) {
        printf("Danh sach mon hoc trong!\n");
        return;
    }
    
    printf("\n=== DANH SACH MON HOC ===\n");
    printf("%-10s %-30s %-10s %-15s\n", 
           "Ma MH", "Ten mon hoc", "Tin chi", "Ma GV");
    printf("================================================================\n");
    
    Course* current = head;
    while (current) {
        printf("%-10s %-30s %-10d %-15s\n",
               current->courseId, current->courseName, 
               current->credits, current->lecturerId);
        current = current->next;
    }
}

Course* findCourse(Course* head, char* courseId) {
    Course* current = head;
    while (current) {
        if (strcmp(current->courseId, courseId) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void saveCoursesToFile(Course* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Khong the mo file de ghi!\n");
        return;
    }
    Course* current = head;
    while (current) {
        fprintf(file, "%s,%s,%d,%s\n", current->courseId, current->courseName, current->credits, current->lecturerId);
        current = current->next;
    }
    fclose(file);
}

void loadCoursesFromFile(Course** head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return;
    char line[512];
    while (fgets(line, sizeof(line), file)) {
        Course* newCourse = (Course*)malloc(sizeof(Course));
        if (!newCourse) continue;
        if (sscanf(line, "%[^,],%[^,],%d,%[^\n]", newCourse->courseId, newCourse->courseName, &newCourse->credits, newCourse->lecturerId) == 4) {
            newCourse->next = *head;
            *head = newCourse;
        } else {
            free(newCourse);
        }
    }
    fclose(file);
}

void updateCourse(Course* head, char* courseId) {
    Course* course = findCourse(head, courseId);
    if (!course) {
        printf("Khong tim thay mon hoc co ma %s!\n", courseId);
        return;
    }
    
    printf("\n=== CAP NHAT THONG TIN MON HOC ===\n");
    printf("Ma MH: %s\n", course->courseId);
    printf("Ten MH: %s\n", course->courseName);
    printf("So tin chi: %d\n", course->credits);
    printf("Ma GV phu trach: %s\n", course->lecturerId);
    char buffer[MAX_STRING];
    printf("Ten MH moi: ");
    fgets(buffer, MAX_STRING, stdin);
    if (strlen(buffer) > 1) { buffer[strcspn(buffer, "\n")] = 0; strcpy(course->courseName, buffer); }
    printf("So tin chi moi: ");
    fgets(buffer, MAX_STRING, stdin);
    if (strlen(buffer) > 1) { int c; if (sscanf(buffer, "%d", &c) == 1) course->credits = c; }
    printf("Ma GV phu trach moi: ");
    fgets(buffer, MAX_STRING, stdin);
    if (strlen(buffer) > 1) { buffer[strcspn(buffer, "\n")] = 0; strcpy(course->lecturerId, buffer); }
    printf("Cap nhat mon hoc thanh cong!\n");
    saveCoursesToFile(head, "database/courses.csv");
}

void deleteCourse(Course** head, char* courseId) {
    Course* current = *head;
    Course* prev = NULL;
    while (current && strcmp(current->courseId, courseId) != 0) {
        prev = current;
        current = current->next;
    }
    if (!current) {
        printf("Khong tim thay mon hoc co ma %s!\n", courseId);
        return;
    }
    if (prev) prev->next = current->next;
    else *head = current->next;
    free(current);
    saveCoursesToFile(*head, "database/courses.csv");
    printf("Xoa mon hoc thanh cong!\n");
}
