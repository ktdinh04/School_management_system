#include "school_management.h"

void addStudent(Student** head) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    if (!newStudent) {
        printf("Loi cap phat bo nho!\n");
        return;
    }
    
    printf("\n=== THEM SINH VIEN MOI ===\n");
    printf("Ma sinh vien: ");
    scanf("%s", newStudent->studentId);
    clearInputBuffer();
    
    printf("Ho ten: ");
    fgets(newStudent->fullName, MAX_STRING, stdin);
    newStudent->fullName[strcspn(newStudent->fullName, "\n")] = 0;
    
    printf("Ngay sinh (dd/mm/yyyy): ");
    newStudent->birthDate = inputDate();
    
    printf("Gioi tinh: ");
    scanf("%s", newStudent->gender);
    clearInputBuffer();
    
    printf("Khoa: ");
    fgets(newStudent->department, MAX_STRING, stdin);
    newStudent->department[strcspn(newStudent->department, "\n")] = 0;
    
    printf("Email: ");
    scanf("%s", newStudent->email);
    
    printf("So dien thoai: ");
    scanf("%s", newStudent->phone);
    
    newStudent->next = *head;
    *head = newStudent;
    
    printf("Them sinh vien thanh cong!\n");
}

void displayStudents(Student* head) {
    if (!head) {
        printf("Danh sach sinh vien trong!\n");
        return;
    }
    
    printf("\n=== DANH SACH SINH VIEN ===\n");
    printf("%-10s %-25s %-12s %-8s %-20s %-25s %-15s\n", 
           "Ma SV", "Ho ten", "Ngay sinh", "Gioi tinh", "Khoa", "Email", "SDT");
    printf("=====================================================================================================\n");
    
    Student* current = head;
    while (current) {
        printf("%-10s %-25s %02d/%02d/%04d %-8s %-20s %-25s %-15s\n",
               current->studentId, current->fullName,
               current->birthDate.day, current->birthDate.month, current->birthDate.year,
               current->gender, current->department, current->email, current->phone);
        current = current->next;
    }
}

Student* findStudent(Student* head, char* studentId) {
    Student* current = head;
    while (current) {
        if (strcmp(current->studentId, studentId) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void deleteStudent(Student** head, char* studentId) {
    if (!*head) {
        printf("Danh sach sinh vien trong!\n");
        return;
    }
    
    Student* current = *head;
    Student* prev = NULL;
    
    while (current && strcmp(current->studentId, studentId) != 0) {
        prev = current;
        current = current->next;
    }
    
    if (!current) {
        printf("Khong tim thay sinh vien co ma %s!\n", studentId);
        return;
    }
    
    if (prev) {
        prev->next = current->next;
    } else {
        *head = current->next;
    }
    
    free(current);
    printf("Xoa sinh vien thanh cong!\n");
}

void updateStudent(Student* head, char* studentId) {
    Student* student = findStudent(head, studentId);
    if (!student) {
        printf("Khong tim thay sinh vien co ma %s!\n", studentId);
        return;
    }
    
    printf("\n=== CAP NHAT THONG TIN SINH VIEN ===\n");
    printf("Thong tin hien tai:\n");
    printf("Ma SV: %s\n", student->studentId);
    printf("Ho ten: %s\n", student->fullName);
    
    printf("\nNhap thong tin moi (Enter de giu nguyen):\n");
    
    printf("Ho ten moi: ");
    char newName[MAX_STRING];
    fgets(newName, MAX_STRING, stdin);
    if (strlen(newName) > 1) {
        newName[strcspn(newName, "\n")] = 0;
        strcpy(student->fullName, newName);
    }
    
    printf("Email moi: ");
    char newEmail[MAX_STRING];
    fgets(newEmail, MAX_STRING, stdin);
    if (strlen(newEmail) > 1) {
        newEmail[strcspn(newEmail, "\n")] = 0;
        strcpy(student->email, newEmail);
    }
    
    printf("Cap nhat thong tin thanh cong!\n");
}

void saveStudentsToFile(Student* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Khong the mo file de ghi!\n");
        return;
    }
    
    Student* current = head;
    while (current) {
        fprintf(file, "%s|%s|%d/%d/%d|%s|%s|%s|%s\n",
                current->studentId, current->fullName,
                current->birthDate.day, current->birthDate.month, current->birthDate.year,
                current->gender, current->department, current->email, current->phone);
        current = current->next;
    }
    
    fclose(file);
    printf("Luu du lieu sinh vien thanh cong!\n");
}

void loadStudentsFromFile(Student** head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Khong the mo file de doc!\n");
        return;
    }
    
    char line[500];
    while (fgets(line, sizeof(line), file)) {
        Student* newStudent = (Student*)malloc(sizeof(Student));
        if (!newStudent) continue;
        
        char* token = strtok(line, "|");
        strcpy(newStudent->studentId, token);
        
        token = strtok(NULL, "|");
        strcpy(newStudent->fullName, token);
        
        token = strtok(NULL, "|");
        sscanf(token, "%d/%d/%d", &newStudent->birthDate.day, 
               &newStudent->birthDate.month, &newStudent->birthDate.year);
        
        token = strtok(NULL, "|");
        strcpy(newStudent->gender, token);
        
        token = strtok(NULL, "|");
        strcpy(newStudent->department, token);
        
        token = strtok(NULL, "|");
        strcpy(newStudent->email, token);
        
        token = strtok(NULL, "|\n");
        strcpy(newStudent->phone, token);
        
        newStudent->next = *head;
        *head = newStudent;
    }
    
    fclose(file);
    printf("Tai du lieu sinh vien thanh cong!\n");
}
