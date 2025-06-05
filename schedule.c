#include "school_management.h"
#include <sys/stat.h>
#include <direct.h>

void addSchedule(ClassSchedule** head) {
    (void)head;
    struct _stat st = {0};
    if (_stat("database", &st) == -1) _mkdir("database");
    
    ClassSchedule newSchedule;
    printf("\n=== THEM LICH HOC MOI ===\n");
    printf("Ma lich: ");
    scanf("%s", newSchedule.scheduleId);
    
    printf("Ma mon hoc: ");
    scanf("%s", newSchedule.courseId);
    
    printf("Thu (2-8): ");
    scanf("%d", &newSchedule.dayOfWeek);
    
    printf("Gio bat dau (0-23): ");
    scanf("%d", &newSchedule.startHour);
    
    printf("Gio ket thuc (0-23): ");
    scanf("%d", &newSchedule.endHour);
    
    printf("Phong hoc: ");
    scanf("%s", newSchedule.classroom);
    
    FILE* file = fopen("database/schedules.csv", "a");
    if (file) {
        fprintf(file, "%s,%s,%d,%d,%d,%s\n", 
                newSchedule.scheduleId, newSchedule.courseId, 
                newSchedule.dayOfWeek, newSchedule.startHour, 
                newSchedule.endHour, newSchedule.classroom);
        fclose(file);
        printf("Them lich hoc thanh cong!\n");
    } else {
        printf("Khong the mo file database/schedules.csv de ghi!\n");
    }
}

void displaySchedules(ClassSchedule* head) {
    (void)head;
    FILE* file = fopen("database/schedules.csv", "r");
    if (!file) {
        printf("Khong the mo file database/schedules.csv de doc hoac danh sach lich hoc trong!\n");
        return;
    }
    
    printf("\n=== DANH SACH LICH HOC ===\n");
    printf("%-10s %-10s %-5s %-10s %-10s %-15s\n", 
           "Ma lich", "Ma MH", "Thu", "Gio BD", "Gio KT", "Phong");
    printf("================================================================\n");
    
    char line[512];
    while (fgets(line, sizeof(line), file)) {
        // Skip empty lines
        if (line[0] == '\n' || line[0] == '\0') continue;
        
        char scheduleId[MAX_ID], courseId[MAX_ID], classroom[MAX_STRING];
        int dayOfWeek, startHour, endHour;
        int n = sscanf(line, "%[^,],%[^,],%d,%d,%d,%[^\n]", 
                      scheduleId, courseId, &dayOfWeek, &startHour, &endHour, classroom);
        if (n == 6) {
            // Remove leading/trailing spaces if any
            while (*classroom == ' ') memmove(classroom, classroom+1, strlen(classroom));
            printf("%-10s %-10s %-5d %-10d %-10d %-15s\n",
                   scheduleId, courseId, dayOfWeek, startHour, endHour, classroom);
        }
    }
    fclose(file);
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
    // Free old list if any
    ClassSchedule* cur = *head;
    while (cur) {
        ClassSchedule* tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    *head = NULL;
    
    FILE* file = fopen(filename, "r");
    if (!file) return;
    char line[512];
    while (fgets(line, sizeof(line), file)) {
        // Skip empty lines
        if (line[0] == '\n' || line[0] == '\0') continue;
        
        ClassSchedule* newSchedule = (ClassSchedule*)malloc(sizeof(ClassSchedule));
        if (!newSchedule) continue;
        if (sscanf(line, "%[^,],%[^,],%d,%d,%d,%[^\n]", newSchedule->scheduleId, newSchedule->courseId, &newSchedule->dayOfWeek, &newSchedule->startHour, &newSchedule->endHour, newSchedule->classroom) == 6) {
            newSchedule->next = *head;
            *head = newSchedule;
        } else {
            free(newSchedule);
        }
    }    fclose(file);
}

ClassSchedule* findSchedule(ClassSchedule* head, char* scheduleId) {
    (void)head;
    FILE* file = fopen("database/schedules.csv", "r");
    if (!file) return NULL;
    
    static ClassSchedule found;
    char line[512];
    while (fgets(line, sizeof(line), file)) {
        char id[MAX_ID], courseId[MAX_ID], classroom[MAX_STRING];
        int dayOfWeek, startHour, endHour;
        int n = sscanf(line, "%[^,],%[^,],%d,%d,%d,%[^\n]", 
                      id, courseId, &dayOfWeek, &startHour, &endHour, classroom);
        if (n == 6 && strcmp(id, scheduleId) == 0) {
            strcpy(found.scheduleId, id);
            strcpy(found.courseId, courseId);
            found.dayOfWeek = dayOfWeek;
            found.startHour = startHour;
            found.endHour = endHour;
            strcpy(found.classroom, classroom);
            fclose(file);
            return &found;
        }
    }
    fclose(file);
    return NULL;
}

void updateSchedule(ClassSchedule* head, char* scheduleId) {
    (void)head;
    FILE* file = fopen("database/schedules.csv", "r");
    if (!file) { 
        printf("Khong the mo file!\n"); 
        return; 
    }
    
    ClassSchedule list[1000]; 
    int n = 0;
    char line[512]; 
    int found = 0;
    
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%[^,],%d,%d,%d,%[^\n]", 
               list[n].scheduleId, list[n].courseId, 
               &list[n].dayOfWeek, &list[n].startHour, 
               &list[n].endHour, list[n].classroom);
        n++;
    }
    fclose(file);
    
    for (int i = 0; i < n; ++i) {
        if (strcmp(list[i].scheduleId, scheduleId) == 0) {
            found = 1;
            printf("\n=== CAP NHAT THOI KHOA BIEU ===\n");
            printf("Ma lich: %s\n", list[i].scheduleId);
            printf("Ma mon hoc: %s\n", list[i].courseId);
            printf("Thu: %d\n", list[i].dayOfWeek);
            printf("Gio bat dau: %d\n", list[i].startHour);
            printf("Gio ket thuc: %d\n", list[i].endHour);
            printf("Phong hoc: %s\n", list[i].classroom);
            
            char buffer[MAX_STRING];
            printf("Ma mon hoc moi: ");
            fgets(buffer, MAX_STRING, stdin);
            if (strlen(buffer) > 1) { 
                buffer[strcspn(buffer, "\n")] = 0; 
                strcpy(list[i].courseId, buffer); 
            }
            
            printf("Thu moi: ");
            fgets(buffer, MAX_STRING, stdin);
            if (strlen(buffer) > 1) { 
                int d; 
                if (sscanf(buffer, "%d", &d) == 1) 
                    list[i].dayOfWeek = d; 
            }
            
            printf("Gio bat dau moi: ");
            fgets(buffer, MAX_STRING, stdin);
            if (strlen(buffer) > 1) { 
                int s; 
                if (sscanf(buffer, "%d", &s) == 1) 
                    list[i].startHour = s; 
            }
            
            printf("Gio ket thuc moi: ");
            fgets(buffer, MAX_STRING, stdin);
            if (strlen(buffer) > 1) { 
                int e; 
                if (sscanf(buffer, "%d", &e) == 1) 
                    list[i].endHour = e; 
            }
            
            printf("Phong hoc moi: ");
            fgets(buffer, MAX_STRING, stdin);
            if (strlen(buffer) > 1) { 
                buffer[strcspn(buffer, "\n")] = 0; 
                strcpy(list[i].classroom, buffer); 
            }
            
            printf("Cap nhat thoi khoa bieu thanh cong!\n");
            break;
        }
    }
    
    if (!found) { 
        printf("Khong tim thay lich hoc co ma %s!\n", scheduleId); 
        return; 
    }
    
    file = fopen("database/schedules.csv", "w");
    for (int i = 0; i < n; ++i)
        fprintf(file, "%s,%s,%d,%d,%d,%s\n", 
                list[i].scheduleId, list[i].courseId, 
                list[i].dayOfWeek, list[i].startHour, 
                list[i].endHour, list[i].classroom);
    fclose(file);
}

void deleteSchedule(ClassSchedule** head, char* scheduleId) {
    (void)head;
    FILE* file = fopen("database/schedules.csv", "r");
    if (!file) { 
        printf("Khong the mo file!\n"); 
        return; 
    }
    
    ClassSchedule list[1000]; 
    int n = 0, idx = -1;
    char line[512];
    
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%[^,],%d,%d,%d,%[^\n]", 
               list[n].scheduleId, list[n].courseId, 
               &list[n].dayOfWeek, &list[n].startHour, 
               &list[n].endHour, list[n].classroom);
        if (strcmp(list[n].scheduleId, scheduleId) == 0) 
            idx = n;
        n++;
    }
    fclose(file);
    
    if (idx == -1) { 
        printf("Khong tim thay lich hoc co ma %s!\n", scheduleId); 
        return; 
    }
    
    for (int i = idx; i < n - 1; ++i) 
        list[i] = list[i + 1];
    n--;
    
    file = fopen("database/schedules.csv", "w");
    for (int i = 0; i < n; ++i)
        fprintf(file, "%s,%s,%d,%d,%d,%s\n", 
                list[i].scheduleId, list[i].courseId, 
                list[i].dayOfWeek, list[i].startHour, 
                list[i].endHour, list[i].classroom);
    fclose(file);
    printf("Xoa lich hoc thanh cong!\n");
}

void displayLecturerSchedule(ClassSchedule* schedules, Course* courses, char* lecturerId) {
    (void)schedules;
    (void)courses;
    
    printf("\n=== LICH GIANG DAY CUA GIANG VIEN %s ===\n", lecturerId);
    printf("%-10s %-30s %-5s %-10s %-10s %-15s\n", 
           "Ma MH", "Ten mon hoc", "Thu", "Gio BD", "Gio KT", "Phong");
    printf("====================================================================================\n");
    
    FILE* scheduleFile = fopen("database/schedules.csv", "r");
    FILE* courseFile = fopen("database/courses.csv", "r");
    
    if (!scheduleFile || !courseFile) {
        if (scheduleFile) fclose(scheduleFile);
        if (courseFile) fclose(courseFile);
        printf("Khong the mo file du lieu!\n");
        return;
    }
    
    int found = 0;
    char scheduleLine[512];
    
    while (fgets(scheduleLine, sizeof(scheduleLine), scheduleFile)) {
        // Skip empty lines
        if (scheduleLine[0] == '\n' || scheduleLine[0] == '\0') continue;
        
        char scheduleId[MAX_ID], courseId[MAX_ID], classroom[MAX_STRING];
        int dayOfWeek, startHour, endHour;
        int n = sscanf(scheduleLine, "%[^,],%[^,],%d,%d,%d,%[^\n]", 
                      scheduleId, courseId, &dayOfWeek, &startHour, &endHour, classroom);
        
        if (n == 6) {
            // Tìm môn học tương ứng
            rewind(courseFile);
            char courseLine[512];
            while (fgets(courseLine, sizeof(courseLine), courseFile)) {
                if (courseLine[0] == '\n' || courseLine[0] == '\0') continue;
                
                char cId[MAX_ID], courseName[MAX_STRING], cLecturerId[MAX_ID];
                int credits;
                int m = sscanf(courseLine, "%[^,],%[^,],%d,%[^\n]", 
                              cId, courseName, &credits, cLecturerId);
                
                if (m == 4 && strcmp(cId, courseId) == 0 && strcmp(cLecturerId, lecturerId) == 0) {
                    // Remove leading/trailing spaces if any
                    while (*courseName == ' ') memmove(courseName, courseName+1, strlen(courseName));
                    while (*classroom == ' ') memmove(classroom, classroom+1, strlen(classroom));
                    
                    printf("%-10s %-30s %-5d %-10d %-10d %-15s\n",
                           courseId, courseName, dayOfWeek, startHour, endHour, classroom);
                    found = 1;
                    break;
                }
            }
        }
    }
    
    fclose(scheduleFile);
    fclose(courseFile);
    
    if (!found) {
        printf("Khong tim thay lich giang day cho giang vien nay!\n");
    }
}
