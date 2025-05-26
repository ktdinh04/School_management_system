#include "school_management.h"

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

void deleteSchedule(ClassSchedule** head, char* scheduleId) {
    if (!*head) {
        printf("Danh sach lich hoc trong!\n");
        return;
    }
    
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
    
    if (prev) {
        prev->next = current->next;
    } else {
        *head = current->next;
    }
    
    free(current);
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
