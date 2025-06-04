#include "school_management.h"
#include <sys/stat.h>
#include <direct.h>

void saveDepartmentsToFile(Department* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Khong the mo file de ghi!\n");
        return;
    }
    Department* current = head;
    while (current) {
        fprintf(file, "%s,%s,%s\n", current->departmentId, current->departmentName, current->headLecturerId);
        current = current->next;
    }
    fclose(file);
}

void loadDepartmentsFromFile(Department** head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return;
    char line[300];
    while (fgets(line, sizeof(line), file)) {
        Department* newDepartment = (Department*)malloc(sizeof(Department));
        if (!newDepartment) continue;
        if (sscanf(line, "%[^,],%[^,],%[^\n]", newDepartment->departmentId, newDepartment->departmentName, newDepartment->headLecturerId) == 3) {
            newDepartment->next = *head;
            *head = newDepartment;
        } else {
            free(newDepartment);
        }
    }
    fclose(file);
}

void addDepartment(Department** head) {
    // Đảm bảo thư mục database tồn tại
    struct _stat st = {0};
    if (_stat("database", &st) == -1) _mkdir("database");
    Department* newDepartment = (Department*)malloc(sizeof(Department));
    if (!newDepartment) {
        printf("Loi cap phat bo nho!\n");
        return;
    }
    printf("\n=== THEM KHOA MOI ===\n");
    printf("Ma khoa: ");
    scanf("%s", newDepartment->departmentId);
    clearInputBuffer();
    printf("Ten khoa: ");
    fgets(newDepartment->departmentName, MAX_STRING, stdin);
    newDepartment->departmentName[strcspn(newDepartment->departmentName, "\n")] = 0;
    printf("Ma truong khoa: ");
    scanf("%s", newDepartment->headLecturerId);
    newDepartment->next = *head;
    *head = newDepartment;
    // Ghi vào file CSV
    FILE* file = fopen("database/departments.csv", "a");
    if (file) {
        fprintf(file, "%s,%s,%s\n", newDepartment->departmentId, newDepartment->departmentName, newDepartment->headLecturerId);
        fclose(file);
    } else {
        printf("Khong the mo file database/departments.csv de ghi!\n");
    }
    printf("Them khoa thanh cong!\n");
}

void updateDepartment(Department* head, char* departmentId) {
    Department* current = head;
    while (current) {
        if (strcmp(current->departmentId, departmentId) == 0) {
            printf("\n=== CAP NHAT THONG TIN KHOA ===\n");
            printf("Ma khoa: %s\n", current->departmentId);
            printf("Ten khoa: %s\n", current->departmentName);
            printf("Ma truong khoa: %s\n", current->headLecturerId);
            char buffer[MAX_STRING];
            printf("Ten khoa moi (Enter de giu nguyen): ");
            fgets(buffer, MAX_STRING, stdin);
            if (strlen(buffer) > 1) {
                buffer[strcspn(buffer, "\n")] = 0;
                strcpy(current->departmentName, buffer);
            }
            printf("Ma truong khoa moi (Enter de giu nguyen): ");
            fgets(buffer, MAX_STRING, stdin);
            if (strlen(buffer) > 1) {
                buffer[strcspn(buffer, "\n")] = 0;
                strcpy(current->headLecturerId, buffer);
            }
            printf("Cap nhat khoa thanh cong!\n");
            saveDepartmentsToFile(head, "database/departments.csv");
            return;
        }
        current = current->next;
    }
    printf("Khong tim thay khoa co ma %s!\n", departmentId);
}

void deleteDepartment(Department** head, char* departmentId) {
    Department* current = *head;
    Department* prev = NULL;
    while (current && strcmp(current->departmentId, departmentId) != 0) {
        prev = current;
        current = current->next;
    }
    if (!current) {
        printf("Khong tim thay khoa co ma %s!\n", departmentId);
        return;
    }
    if (prev) prev->next = current->next;
    else *head = current->next;
    free(current);
    saveDepartmentsToFile(*head, "database/departments.csv");
    printf("Xoa khoa thanh cong!\n");
}

void displayDepartments(Department* head) {
    if (!head) {
        printf("Danh sach nganh trong!\n");
        return;
    }
    
    printf("\n=== DANH SACH NGANH ===\n");
    printf("%-10s %-30s %-15s\n", 
           "Ma nganh", "Ten nganh", "Ma giao vien truong nganh");
    printf("=========================================================\n");
    
    Department* current = head;
    while (current) {
        printf("%-10s %-30s %-15s\n",
               current->departmentId, current->departmentName, 
               current->headLecturerId);
        current = current->next;
    }
}