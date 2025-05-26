#include "school_management.h"

void addDepartment(Department** head) {
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
    
    printf("Them khoa thanh cong!\n");
}

void displayDepartments(Department* head) {
    if (!head) {
        printf("Danh sach khoa trong!\n");
        return;
    }
    
    printf("\n=== DANH SACH KHOA ===\n");
    printf("%-10s %-30s %-15s\n", 
           "Ma khoa", "Ten khoa", "Ma truong khoa");
    printf("=========================================================\n");
    
    Department* current = head;
    while (current) {
        printf("%-10s %-30s %-15s\n",
               current->departmentId, current->departmentName, 
               current->headLecturerId);
        current = current->next;
    }
}
