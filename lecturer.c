#include "school_management.h"

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
    
    printf("So dien thoai: ");
    scanf("%s", newLecturer->phone);
    
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

void deleteLecturer(Lecturer** head, char* lecturerId) {
    if (!*head) {
        printf("Danh sach giang vien trong!\n");
        return;
    }
    
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
    
    if (prev) {
        prev->next = current->next;
    } else {
        *head = current->next;
    }
    
    free(current);
    printf("Xoa giang vien thanh cong!\n");
}

void updateLecturer(Lecturer* head, char* lecturerId) {
    Lecturer* lecturer = findLecturer(head, lecturerId);
    if (!lecturer) {
        printf("Khong tim thay giang vien co ma %s!\n", lecturerId);
        return;
    }
    
    printf("\n=== CAP NHAT THONG TIN GIANG VIEN ===\n");
    printf("Thong tin hien tai:\n");
    printf("Ma GV: %s\n", lecturer->lecturerId);
    printf("Ho ten: %s\n", lecturer->fullName);
    
    printf("\nNhap thong tin moi (Enter de giu nguyen):\n");
    
    printf("Ho ten moi: ");
    char newName[MAX_STRING];
    fgets(newName, MAX_STRING, stdin);
    if (strlen(newName) > 1) {
        newName[strcspn(newName, "\n")] = 0;
        strcpy(lecturer->fullName, newName);
    }
    
    printf("Email moi: ");
    char newEmail[MAX_STRING];
    fgets(newEmail, MAX_STRING, stdin);
    if (strlen(newEmail) > 1) {
        newEmail[strcspn(newEmail, "\n")] = 0;
        strcpy(lecturer->email, newEmail);
    }
    
    printf("Cap nhat thong tin thanh cong!\n");
}

void saveLecturersToFile(Lecturer* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Khong the mo file de ghi!\n");
        return;
    }
    
    Lecturer* current = head;
    while (current) {
        fprintf(file, "%s|%s|%s|%s|%s|%s\n",
                current->lecturerId, current->fullName, current->department,
                current->specialty, current->email, current->phone);
        current = current->next;
    }
    
    fclose(file);
    printf("Luu du lieu giang vien thanh cong!\n");
}

void loadLecturersFromFile(Lecturer** head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Khong the mo file de doc!\n");
        return;
    }
    
    char line[500];
    while (fgets(line, sizeof(line), file)) {
        Lecturer* newLecturer = (Lecturer*)malloc(sizeof(Lecturer));
        if (!newLecturer) continue;
        
        char* token = strtok(line, "|");
        strcpy(newLecturer->lecturerId, token);
        
        token = strtok(NULL, "|");
        strcpy(newLecturer->fullName, token);
        
        token = strtok(NULL, "|");
        strcpy(newLecturer->department, token);
        
        token = strtok(NULL, "|");
        strcpy(newLecturer->specialty, token);
        
        token = strtok(NULL, "|");
        strcpy(newLecturer->email, token);
        
        token = strtok(NULL, "|\n");
        strcpy(newLecturer->phone, token);
        
        newLecturer->next = *head;
        *head = newLecturer;
    }
    
    fclose(file);
    printf("Tai du lieu giang vien thanh cong!\n");
}
