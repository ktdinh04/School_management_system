#include "school_management.h"

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

void deleteCourse(Course** head, char* courseId) {
    if (!*head) {
        printf("Danh sach mon hoc trong!\n");
        return;
    }
    
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
    
    if (prev) {
        prev->next = current->next;
    } else {
        *head = current->next;
    }
    
    free(current);
    printf("Xoa mon hoc thanh cong!\n");
}

void updateCourse(Course* head, char* courseId) {
    Course* course = findCourse(head, courseId);
    if (!course) {
        printf("Khong tim thay mon hoc co ma %s!\n", courseId);
        return;
    }
    
    printf("\n=== CAP NHAT THONG TIN MON HOC ===\n");
    printf("Thong tin hien tai:\n");
    printf("Ma MH: %s\n", course->courseId);
    printf("Ten mon hoc: %s\n", course->courseName);
    printf("So tin chi: %d\n", course->credits);
    
    printf("\nNhap thong tin moi (Enter de giu nguyen):\n");
    
    printf("Ten mon hoc moi: ");
    char newName[MAX_STRING];
    fgets(newName, MAX_STRING, stdin);
    if (strlen(newName) > 1) {
        newName[strcspn(newName, "\n")] = 0;
        strcpy(course->courseName, newName);
    }
    
    printf("So tin chi moi (0 de giu nguyen): ");
    int newCredits;
    scanf("%d", &newCredits);
    if (newCredits > 0) {
        course->credits = newCredits;
    }
    
    printf("Ma giang vien moi: ");
    char newLecturerId[MAX_ID];
    scanf("%s", newLecturerId);
    if (strlen(newLecturerId) > 0) {
        strcpy(course->lecturerId, newLecturerId);
    }
    
    printf("Cap nhat thong tin thanh cong!\n");
}

void saveCoursesToFile(Course* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Khong the mo file de ghi!\n");
        return;
    }
    
    Course* current = head;
    while (current) {
        fprintf(file, "%s|%s|%d|%s\n",
                current->courseId, current->courseName,
                current->credits, current->lecturerId);
        current = current->next;
    }
    
    fclose(file);
    printf("Luu du lieu mon hoc thanh cong!\n");
}

void loadCoursesFromFile(Course** head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Khong the mo file de doc!\n");
        return;
    }
    
    char line[300];
    while (fgets(line, sizeof(line), file)) {
        Course* newCourse = (Course*)malloc(sizeof(Course));
        if (!newCourse) continue;
        
        char* token = strtok(line, "|");
        strcpy(newCourse->courseId, token);
        
        token = strtok(NULL, "|");
        strcpy(newCourse->courseName, token);
        
        token = strtok(NULL, "|");
        newCourse->credits = atoi(token);
        
        token = strtok(NULL, "|\n");
        strcpy(newCourse->lecturerId, token);
        
        newCourse->next = *head;
        *head = newCourse;
    }
    
    fclose(file);
    printf("Tai du lieu mon hoc thanh cong!\n");
}
