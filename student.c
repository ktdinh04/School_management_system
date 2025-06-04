#include "school_management.h"

void addStudent(Student** head) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    if (!newStudent) {
        printf("Loi cap phat bo nho!\n");
        return;
    }
    
    printf("\n=== THEM SINH VIEN MOI ===\n");
    printf("MSSV: ");
    scanf("%s", newStudent->studentId);
    clearInputBuffer();
    
    printf("Ho ten: ");
    fgets(newStudent->fullName, MAX_STRING, stdin);
    newStudent->fullName[strcspn(newStudent->fullName, "\n")] = 0;
    
    printf("Ngay sinh (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &newStudent->birthDate.day, 
                      &newStudent->birthDate.month, 
                      &newStudent->birthDate.year);
    clearInputBuffer();
    
    printf("Gioi tinh: ");
    fgets(newStudent->gender, sizeof(newStudent->gender), stdin);
    newStudent->gender[strcspn(newStudent->gender, "\n")] = 0;
    
    printf("Khoa: ");
    fgets(newStudent->department, MAX_STRING, stdin);
    newStudent->department[strcspn(newStudent->department, "\n")] = 0;
    
    printf("Email: ");
    scanf("%s", newStudent->email);
    clearInputBuffer();
    
    printf("So dien thoai: ");
    scanf("%s", newStudent->phone);
    clearInputBuffer();
    
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
    printf("MSSV: %s\n", student->studentId);
    printf("Ho ten: %s\n", student->fullName);
    printf("Ngay sinh: %02d/%02d/%04d\n", student->birthDate.day, student->birthDate.month, student->birthDate.year);
    printf("Gioi tinh: %s\n", student->gender);
    printf("Khoa: %s\n", student->department);
    printf("Email: %s\n", student->email);
    printf("So dien thoai: %s\n", student->phone);

    printf("\nNhap thong tin moi (nhan Enter de giu nguyen):\n");

    char buffer[MAX_STRING];

    // Họ tên
    printf("Ho ten moi: ");
    fgets(buffer, MAX_STRING, stdin);
    if (strlen(buffer) > 1) {
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(student->fullName, buffer);
    }

    // Ngày sinh
    printf("Ngay sinh moi (dd/mm/yyyy): ");
    fgets(buffer, MAX_STRING, stdin);
    if (strlen(buffer) > 1) {
        int d, m, y;
        if (sscanf(buffer, "%d/%d/%d", &d, &m, &y) == 3) {
            // Validate date
            if (d >= 1 && d <= 31 && m >= 1 && m <= 12 && y >= 1900 && y <= 2025) {
                student->birthDate.day = d;
                student->birthDate.month = m;
                student->birthDate.year = y;
            } else {
                printf("Ngay sinh khong hop le, giu nguyen.\n");
            }
        } else {
            printf("Dinh dang ngay sinh khong hop le, giu nguyen.\n");
        }
    }

    // Giới tính
    printf("Gioi tinh moi: ");
    fgets(buffer, MAX_STRING, stdin);
    if (strlen(buffer) > 1) {
        buffer[strcspn(buffer, "\n")] = 0;
        if (strlen(buffer) < sizeof(student->gender)) {
            strcpy(student->gender, buffer);
        } else {
            printf("Gioi tinh qua dai, giu nguyen.\n");
        }
    }

    // Khoa
    printf("Khoa moi: ");
    fgets(buffer, MAX_STRING, stdin);
    if (strlen(buffer) > 1) {
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(student->department, buffer);
    }

    // Email
    printf("Email moi: ");
    fgets(buffer, MAX_STRING, stdin);
    if (strlen(buffer) > 1) {
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(student->email, buffer);
    }

    // Số điện thoại
    printf("So dien thoai moi: ");
    fgets(buffer, MAX_STRING, stdin);
    if (strlen(buffer) > 1) {
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(student->phone, buffer);
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
        
        int result = sscanf(line, "%[^|]|%[^|]|%d/%d/%d|%[^|]|%[^|]|%[^|]|%[^\n]",
                           newStudent->studentId,
                           newStudent->fullName,
                           &newStudent->birthDate.day,
                           &newStudent->birthDate.month,
                           &newStudent->birthDate.year,
                           newStudent->gender,
                           newStudent->department,
                           newStudent->email,
                           newStudent->phone);
        
        if (result != 9) {
            free(newStudent);
            continue;
        }
        
        newStudent->next = *head;
        *head = newStudent;
    }
    
    fclose(file);
    printf("Tai du lieu sinh vien thanh cong!\n");
}