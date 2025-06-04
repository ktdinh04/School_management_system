#include "school_management.h"
#include <sys/stat.h>
#include <direct.h>

void addSchedule(ClassSchedule** head) {
    ClassSchedule* newSchedule = (ClassSchedule*)malloc(sizeof(ClassSchedule));
    if (!newSchedule) {
        printf("Loi cap phat bo nho!\n");
        return;
    }
    
    printf("\n=== THEM LICH HOC MOI ===\n");
    printf("Ma lich: ");
    scanf("%s", newSchedule->scheduleId);
    
    printf("Ma mon hoc: ");
    scanf("%s", newSchedule->courseId);
    
    printf("Thu (2-8): ");
    scanf("%d", &newSchedule->dayOfWeek);
    
    printf("Gio bat dau (0-23): ");
    scanf("%d", &newSchedule->startHour);
    
    printf("Gio ket thuc (0-23): ");
    scanf("%d", &newSchedule->endHour);
    
    printf("Phong hoc: ");
    scanf("%s", newSchedule->classroom);
    
    newSchedule->next = *head;
    *head = newSchedule;
    
    printf("Them lich hoc thanh cong!\n");
}

void displaySchedules(ClassSchedule* head) {
    if (!head) {
        printf("Danh sach lich hoc trong!\n");
        return;
    }
    
    printf("\n=== DANH SACH LICH HOC ===\n");
    printf("%-10s %-10s %-5s %-10s %-10s %-15s\n", 
           "Ma lich", "Ma MH", "Thu", "Gio BD", "Gio KT", "Phong");
    printf("================================================================\n");
    
    ClassSchedule* current = head;
    while (current) {
        printf("%-10s %-10s %-5d %-10d %-10d %-15s\n",
               current->scheduleId, current->courseId, current->dayOfWeek,
               current->startHour, current->endHour, current->classroom);
        current = current->next;
    }
}

void saveSchedulesToFile(ClassSchedule* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Khong the mo file de ghi!\n");
        return;
    }
    ClassSchedule* current = head;
    while (current) {
        fprintf(file, "%s,%s,%d,%d,%d,%s\n", current->scheduleId, current->courseId, current->dayOfWeek, current->startHour, current->endHour, current->classroom);
        current = current->next;
    }
    fclose(file);
}

void loadSchedulesFromFile(ClassSchedule** head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return;
    char line[512];
    while (fgets(line, sizeof(line), file)) {
        ClassSchedule* newSchedule = (ClassSchedule*)malloc(sizeof(ClassSchedule));
        if (!newSchedule) continue;
        if (sscanf(line, "%[^,],%[^,],%d,%d,%d,%[^\n]", newSchedule->scheduleId, newSchedule->courseId, &newSchedule->dayOfWeek, &newSchedule->startHour, &newSchedule->endHour, newSchedule->classroom) == 6) {
            newSchedule->next = *head;
            *head = newSchedule;
        } else {
            free(newSchedule);
        }
    }
    fclose(file);
}

void updateSchedule(ClassSchedule* head, char* scheduleId) {
    ClassSchedule* schedule = head;
    while (schedule) {
        if (strcmp(schedule->scheduleId, scheduleId) == 0) {
            printf("\n=== CAP NHAT THOI KHOA BIEU ===\n");
            printf("Ma lich: %s\n", schedule->scheduleId);
            printf("Ma mon hoc: %s\n", schedule->courseId);
            printf("Thu: %d\n", schedule->dayOfWeek);
            printf("Gio bat dau: %d\n", schedule->startHour);
            printf("Gio ket thuc: %d\n", schedule->endHour);
            printf("Phong hoc: %s\n", schedule->classroom);
            char buffer[MAX_STRING];
            printf("Ma mon hoc moi: ");
            fgets(buffer, MAX_STRING, stdin);
            if (strlen(buffer) > 1) { buffer[strcspn(buffer, "\n")] = 0; strcpy(schedule->courseId, buffer); }
            printf("Thu moi: ");
            fgets(buffer, MAX_STRING, stdin);
            if (strlen(buffer) > 1) { int d; if (sscanf(buffer, "%d", &d) == 1) schedule->dayOfWeek = d; }
            printf("Gio bat dau moi: ");
            fgets(buffer, MAX_STRING, stdin);
            if (strlen(buffer) > 1) { int s; if (sscanf(buffer, "%d", &s) == 1) schedule->startHour = s; }
            printf("Gio ket thuc moi: ");
            fgets(buffer, MAX_STRING, stdin);
            if (strlen(buffer) > 1) { int e; if (sscanf(buffer, "%d", &e) == 1) schedule->endHour = e; }
            printf("Phong hoc moi: ");
            fgets(buffer, MAX_STRING, stdin);
            if (strlen(buffer) > 1) { buffer[strcspn(buffer, "\n")] = 0; strcpy(schedule->classroom, buffer); }
            printf("Cap nhat thoi khoa bieu thanh cong!\n");
            saveSchedulesToFile(head, "database/schedules.csv");
            return;
        }
        schedule = schedule->next;
    }
    printf("Khong tim thay lich hoc co ma %s!\n", scheduleId);
}

void deleteSchedule(ClassSchedule** head, char* scheduleId) {
    ClassSchedule* current = *head;
    ClassSchedule* prev = NULL;
    while (current && strcmp(current->scheduleId, scheduleId) != 0) {
        prev = current;
        current = current->next;
    }
    if (!current) {
        printf("Khong tim thay lich hoc co ma %s!\n", scheduleId);
        return;
    }
    if (prev) prev->next = current->next;
    else *head = current->next;
    free(current);
    saveSchedulesToFile(*head, "database/schedules.csv");
    printf("Xoa lich hoc thanh cong!\n");
}

void displayLecturerSchedule(ClassSchedule* schedules, Course* courses, char* lecturerId) {
    printf("\n=== LICH GIANG DAY CUA GIANG VIEN %s ===\n", lecturerId);
    printf("%-10s %-30s %-5s %-10s %-10s %-15s\n", 
           "Ma MH", "Ten mon hoc", "Thu", "Gio BD", "Gio KT", "Phong");
    printf("====================================================================================\n");
    
    ClassSchedule* currentSchedule = schedules;
    int found = 0;
    
    while (currentSchedule) {
        // Tìm môn học tương ứng
        Course* currentCourse = courses;
        while (currentCourse) {
            if (strcmp(currentCourse->courseId, currentSchedule->courseId) == 0 &&
                strcmp(currentCourse->lecturerId, lecturerId) == 0) {
                printf("%-10s %-30s %-5d %-10d %-10d %-15s\n",
                       currentCourse->courseId, currentCourse->courseName,
                       currentSchedule->dayOfWeek, currentSchedule->startHour,
                       currentSchedule->endHour, currentSchedule->classroom);
                found = 1;
                break;
            }
            currentCourse = currentCourse->next;
        }
        currentSchedule = currentSchedule->next;
    }
    
    if (!found) {
        printf("Khong tim thay lich giang day cho giang vien nay!\n");
    }
}
