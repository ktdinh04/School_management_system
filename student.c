#include "school_management.h"
#include <sys/stat.h>
#include <direct.h>

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
    // Đảm bảo thư mục database tồn tại
    struct _stat st = {0};
    if (_stat("database", &st) == -1) {
        _mkdir("database");
    }
    // Ghi vào file CSV
    FILE* file = fopen("database/students.csv", "a");
    if (file) {
        fprintf(file, "%s,%s,%02d/%02d/%04d,%s,%s,%s,%s\n",
            newStudent->studentId, newStudent->fullName,
            newStudent->birthDate.day, newStudent->birthDate.month, newStudent->birthDate.year,
            newStudent->gender, newStudent->department, newStudent->email, newStudent->phone);
        fclose(file);
    } else {
        printf("Khong the mo file database/students.csv de ghi!\n");
    }
    printf("Them sinh vien thanh cong!\n");
}

void displayStudents(Student* head) {
    (void)head;
    // Đọc từ file CSV và hiển thị
    FILE* file = fopen("database/students.csv", "r");
    if (!file) {
        printf("Khong the mo file database/students.csv de doc hoac danh sach sinh vien trong!\n");
        return;
    }
    printf("\n=== DANH SACH SINH VIEN ===\n");
    printf("%-10s %-25s %-12s %-8s %-20s %-25s %-15s\n",
           "Ma SV", "Ho ten", "Ngay sinh", "Gioi tinh", "Khoa", "Email", "SDT");
    printf("=====================================================================================================\n");
    char line[512];
    while (fgets(line, sizeof(line), file)) {
        char studentId[MAX_ID], fullName[MAX_STRING], birth[20], gender[10], department[MAX_STRING], email[MAX_STRING], phone[MAX_STRING];
        int n = sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",
            studentId, fullName, birth, gender, department, email, phone);
        if (n == 7) {
            printf("%-10s %-25s %-12s %-8s %-20s %-25s %-15s\n",
                studentId, fullName, birth, gender, department, email, phone);
        }
    }
    fclose(file);
}

Student* findStudent(Student* head, char* studentId) {
    (void)head;
    FILE* file = fopen("database/students.csv", "r");
    if (!file) return NULL;
    static Student found;
    char line[512];
    while (fgets(line, sizeof(line), file)) {
        int d, m, y;
        char gender[20], department[MAX_STRING], email[MAX_STRING], phone[MAX_STRING];
        char id[MAX_ID], name[MAX_STRING];
        int n = sscanf(line, "%[^,],%[^,],%d/%d/%d,%[^,],%[^,],%[^,],%[^\n]", id, name, &d, &m, &y, gender, department, email, phone);
        if (n >= 8 && strcmp(id, studentId) == 0) {
            strcpy(found.studentId, id);
            strcpy(found.fullName, name);
            found.birthDate.day = d;
            found.birthDate.month = m;
            found.birthDate.year = y;
            strcpy(found.gender, gender);
            strcpy(found.department, department);
            strcpy(found.email, email);
            strcpy(found.phone, phone);
            fclose(file);
            return &found;
        }
    }
    fclose(file);
    return NULL;
}

void deleteStudent(Student** head, char* studentId) {
    (void)head;
    FILE* file = fopen("database/students.csv", "r");
    if (!file) { 
        printf("Khong the mo file!\n"); 
        return; 
    }
    
    // Array to store all students except the one to delete
    char lines[1000][512];
    int n = 0, idx = -1;
    char line[512];
    
    while (fgets(line, sizeof(line), file)) {
        // Skip empty lines
        if (line[0] == '\n' || line[0] == '\0') continue;
        
        char id[MAX_ID];
        int result = sscanf(line, "%[^,]", id);
        if (result == 1 && strcmp(id, studentId) == 0) {
            idx = n; // Mark this line for deletion
        }
        strcpy(lines[n], line);
        n++;
    }
    fclose(file);
    
    if (idx == -1) { 
        printf("Khong tim thay sinh vien co ma %s!\n", studentId); 
        return; 
    }
    
    // Shift lines to remove the deleted one
    for (int i = idx; i < n - 1; ++i) 
        strcpy(lines[i], lines[i + 1]);
    n--;
    
    // Write back to file
    file = fopen("database/students.csv", "w");
    for (int i = 0; i < n; ++i)
        fputs(lines[i], file);
    fclose(file);
    printf("Xoa sinh vien thanh cong!\n");
}

void updateStudent(Student* head, char* studentId) {
    (void)head;
    FILE* file = fopen("database/students.csv", "r");
    if (!file) { 
        printf("Khong the mo file!\n"); 
        return; 
    }
    
    // Array to store all students
    char lines[1000][512];
    int n = 0, found = 0;
    char line[512];
    
    while (fgets(line, sizeof(line), file)) {
        // Skip empty lines
        if (line[0] == '\n' || line[0] == '\0') continue;
        
        strcpy(lines[n], line);
        n++;
    }
    fclose(file);
    
    // Find and update the student
    for (int i = 0; i < n; ++i) {
        char id[MAX_ID], fullName[MAX_STRING], birth[20], gender[10], department[MAX_STRING], email[MAX_STRING], phone[MAX_STRING];
        int result = sscanf(lines[i], "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",
                           id, fullName, birth, gender, department, email, phone);
        
        if (result == 7 && strcmp(id, studentId) == 0) {
            found = 1;
            printf("\n=== CAP NHAT THONG TIN SINH VIEN ===\n");
            printf("Thong tin hien tai:\n");
            printf("MSSV: %s\n", id);
            printf("Ho ten: %s\n", fullName);
            printf("Ngay sinh: %s\n", birth);
            printf("Gioi tinh: %s\n", gender);
            printf("Khoa: %s\n", department);
            printf("Email: %s\n", email);
            printf("So dien thoai: %s\n", phone);

            printf("\nNhap thong tin moi (nhan Enter de giu nguyen):\n");

            char buffer[MAX_STRING];

            // Họ tên
            printf("Ho ten moi: ");
            fgets(buffer, MAX_STRING, stdin);
            if (strlen(buffer) > 1) {
                buffer[strcspn(buffer, "\n")] = 0;
                strcpy(fullName, buffer);
            }

            // Ngày sinh
            printf("Ngay sinh moi (dd/mm/yyyy): ");
            fgets(buffer, MAX_STRING, stdin);
            if (strlen(buffer) > 1) {
                buffer[strcspn(buffer, "\n")] = 0;
                int d, m, y;
                if (sscanf(buffer, "%d/%d/%d", &d, &m, &y) == 3) {
                    if (d >= 1 && d <= 31 && m >= 1 && m <= 12 && y >= 1900 && y <= 2025) {
                        sprintf(birth, "%02d/%02d/%04d", d, m, y);
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
                strcpy(gender, buffer);
            }

            // Khoa
            printf("Khoa moi: ");
            fgets(buffer, MAX_STRING, stdin);
            if (strlen(buffer) > 1) {
                buffer[strcspn(buffer, "\n")] = 0;
                strcpy(department, buffer);
            }

            // Email
            printf("Email moi: ");
            fgets(buffer, MAX_STRING, stdin);
            if (strlen(buffer) > 1) {
                buffer[strcspn(buffer, "\n")] = 0;
                strcpy(email, buffer);
            }

            // Số điện thoại
            printf("So dien thoai moi: ");
            fgets(buffer, MAX_STRING, stdin);
            if (strlen(buffer) > 1) {
                buffer[strcspn(buffer, "\n")] = 0;
                strcpy(phone, buffer);
            }

            // Update the line with new data
            sprintf(lines[i], "%s,%s,%s,%s,%s,%s,%s\n",
                   id, fullName, birth, gender, department, email, phone);
            
            printf("Cap nhat thong tin thanh cong!\n");
            break;
        }
    }
    
    if (!found) { 
        printf("Khong tim thay sinh vien co ma %s!\n", studentId); 
        return; 
    }
    
    // Write back to file
    file = fopen("database/students.csv", "w");
    for (int i = 0; i < n; ++i)
        fputs(lines[i], file);
    fclose(file);
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
    // Giải phóng danh sách cũ nếu có
    Student* cur = *head;
    while (cur) {
        Student* tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    *head = NULL;
    FILE* file = fopen(filename, "r");
    if (!file) return;
    char line[512];
    while (fgets(line, sizeof(line), file)) {
        Student* newStudent = (Student*)malloc(sizeof(Student));
        if (!newStudent) continue;
        int d, m, y;
        if (sscanf(line, "%[^,],%[^,],%d/%d/%d,%[^,],%[^,],%[^,],%[^\n]",
            newStudent->studentId, newStudent->fullName, &d, &m, &y, newStudent->gender, newStudent->department, newStudent->email, newStudent->phone) >= 8) {
            newStudent->birthDate.day = d;
            newStudent->birthDate.month = m;
            newStudent->birthDate.year = y;
            newStudent->next = *head;
            *head = newStudent;
        } else {
            free(newStudent);
        }
    }
    fclose(file);
}
