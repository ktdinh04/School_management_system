#include "school_management.h"
#include <sys/stat.h>
#include <direct.h>

void addLecturer(Lecturer** head) {
    Lecturer* newLecturer = (Lecturer*)malloc(sizeof(Lecturer));
    if (!newLecturer) {
        printf("Loi cap phat bo nho!\n");
        return;
    }
    
    printf("\n=== THEM GIANG VIEN MOI ===\n");
    printf("Ma giang vien: ");
    scanf("%s", newLecturer->lecturerId);
    clearInputBuffer();
    
    printf("Ho ten: ");
    fgets(newLecturer->fullName, MAX_STRING, stdin);
    newLecturer->fullName[strcspn(newLecturer->fullName, "\n")] = 0;
    
    printf("Khoa: ");
    fgets(newLecturer->department, MAX_STRING, stdin);
    newLecturer->department[strcspn(newLecturer->department, "\n")] = 0;
    
    printf("Chuyen nganh: ");
    fgets(newLecturer->specialty, MAX_STRING, stdin);
    newLecturer->specialty[strcspn(newLecturer->specialty, "\n")] = 0;
    
    printf("Email: ");
    scanf("%s", newLecturer->email);
    clearInputBuffer();
    
    printf("So dien thoai: ");
    scanf("%s", newLecturer->phone);
    clearInputBuffer();
    
    newLecturer->next = *head;
    *head = newLecturer;
    
    printf("Them giang vien thanh cong!\n");
}

void displayLecturers(Lecturer* head) {
    if (!head) {
        printf("Danh sach giang vien trong!\n");
        return;
    }
    
    printf("\n=== DANH SACH GIANG VIEN ===\n");
    printf("%-10s %-25s %-20s %-20s %-25s %-15s\n", 
           "Ma GV", "Ho ten", "Khoa", "Chuyen nganh", "Email", "SDT");
    printf("=========================================================================================\n");
    
    Lecturer* current = head;
    while (current) {
        printf("%-10s %-25s %-20s %-20s %-25s %-15s\n",
               current->lecturerId, current->fullName, current->department,
               current->specialty, current->email, current->phone);
        current = current->next;
    }
}

Lecturer* findLecturer(Lecturer* head, char* lecturerId) {
    Lecturer* current = head;
    while (current) {
        if (strcmp(current->lecturerId, lecturerId) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void saveLecturersToFile(Lecturer* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Khong the mo file de ghi!\n");
        return;
    }
    Lecturer* current = head;
    while (current) {
        fprintf(file, "%s,%s,%s,%s,%s,%s\n", current->lecturerId, current->fullName, current->department, current->specialty, current->email, current->phone);
        current = current->next;
    }
    fclose(file);
}

void loadLecturersFromFile(Lecturer** head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return;
    char line[512];
    while (fgets(line, sizeof(line), file)) {
        Lecturer* newLecturer = (Lecturer*)malloc(sizeof(Lecturer));
        if (!newLecturer) continue;
        if (sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]", newLecturer->lecturerId, newLecturer->fullName, newLecturer->department, newLecturer->specialty, newLecturer->email, newLecturer->phone) == 6) {
            newLecturer->next = *head;
            *head = newLecturer;
        } else {
            free(newLecturer);
        }
    }
    fclose(file);
}

void updateLecturer(Lecturer* head, char* lecturerId) {
    Lecturer* lecturer = findLecturer(head, lecturerId);
    if (!lecturer) {
        printf("Khong tim thay giang vien co ma %s!\n", lecturerId);
        return;
    }
    
    printf("\n=== CAP NHAT THONG TIN GIANG VIEN ===\n");
    printf("Ma GV: %s\n", lecturer->lecturerId);
    printf("Ho ten: %s\n", lecturer->fullName);
    printf("Khoa: %s\n", lecturer->department);
    printf("Chuyen nganh: %s\n", lecturer->specialty);
    printf("Email: %s\n", lecturer->email);
    printf("So dien thoai: %s\n", lecturer->phone);
    
    char buffer[MAX_STRING];
    
    // Họ tên
    printf("Ho ten moi: ");
    fgets(buffer, MAX_STRING, stdin);
    if (strlen(buffer) > 1) {
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(lecturer->fullName, buffer);
    }
    
    // Khoa
    printf("Khoa moi: ");
    fgets(buffer, MAX_STRING, stdin);
    if (strlen(buffer) > 1) {
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(lecturer->department, buffer);
    }
    
    // Chuyên ngành
    printf("Chuyen nganh moi: ");
    fgets(buffer, MAX_STRING, stdin);
    if (strlen(buffer) > 1) {
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(lecturer->specialty, buffer);
    }
    
    // Email
    printf("Email moi: ");
    fgets(buffer, MAX_STRING, stdin);
    if (strlen(buffer) > 1) {
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(lecturer->email, buffer);
    }
    
    // Số điện thoại
    printf("So dien thoai moi: ");
    fgets(buffer, MAX_STRING, stdin);
    if (strlen(buffer) > 1) {
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(lecturer->phone, buffer);
    }
    
    printf("Cap nhat thong tin thanh cong!\n");
    saveLecturersToFile(head, "database/lecturers.csv");
}

void deleteLecturer(Lecturer** head, char* lecturerId) {
    Lecturer* current = *head;
    Lecturer* prev = NULL;
    while (current && strcmp(current->lecturerId, lecturerId) != 0) {
        prev = current;
        current = current->next;
    }
    if (!current) {
        printf("Khong tim thay giang vien co ma %s!\n", lecturerId);
        return;
    }
    if (prev) prev->next = current->next;
    else *head = current->next;
    free(current);
    saveLecturersToFile(*head, "database/lecturers.csv");
    printf("Xoa giang vien thanh cong!\n");
}