#include "school_management.h"
#include <sys/stat.h>
#include <direct.h>

void addLecturer(Lecturer** head) {
    (void)head;
    // Đảm bảo thư mục database tồn tại
    struct _stat st = {0};
    if (_stat("database", &st) == -1) _mkdir("database");
    Lecturer newLecturer;
    printf("\n=== THEM GIANG VIEN MOI ===\n");
    printf("Ma giang vien: ");
    scanf("%s", newLecturer.lecturerId);
    clearInputBuffer();
    printf("Ho ten: ");
    fgets(newLecturer.fullName, MAX_STRING, stdin);
    newLecturer.fullName[strcspn(newLecturer.fullName, "\n")] = 0;
    printf("Khoa: ");
    fgets(newLecturer.department, MAX_STRING, stdin);
    newLecturer.department[strcspn(newLecturer.department, "\n")] = 0;
    printf("Chuyen nganh: ");
    fgets(newLecturer.specialty, MAX_STRING, stdin);
    newLecturer.specialty[strcspn(newLecturer.specialty, "\n")] = 0;
    printf("Email: ");
    scanf("%s", newLecturer.email);
    clearInputBuffer();
    printf("So dien thoai: ");
    scanf("%s", newLecturer.phone);
    clearInputBuffer();
    FILE* file = fopen("database/lecturers.csv", "a");
    if (file) {
        fprintf(file, "%s,%s,%s,%s,%s,%s\n", newLecturer.lecturerId, newLecturer.fullName, newLecturer.department, newLecturer.specialty, newLecturer.email, newLecturer.phone);
        fclose(file);
        printf("Them giang vien thanh cong!\n");
    } else {
        printf("Khong the mo file database/lecturers.csv de ghi!\n");
    }
}

void displayLecturers(Lecturer* head) {
    (void)head;
    FILE* file = fopen("database/lecturers.csv", "r");
    if (!file) {
        printf("Khong the mo file database/lecturers.csv de doc hoac danh sach giang vien trong!\n");
        return;
    }
    printf("\n=== DANH SACH GIANG VIEN ===\n");
    printf("%-10s %-25s %-20s %-20s %-25s %-15s\n", "Ma GV", "Ho ten", "Khoa", "Chuyen nganh", "Email", "SDT");
    printf("========================================================================================\n");
    char line[512];
    while (fgets(line, sizeof(line), file)) {
        // Skip empty lines
        if (line[0] == '\n' || line[0] == '\0') continue;
        char lecturerId[MAX_ID], fullName[MAX_STRING], department[MAX_STRING], specialty[MAX_STRING], email[MAX_STRING], phone[MAX_STRING];
        int n = sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]", lecturerId, fullName, department, specialty, email, phone);
        if (n == 6) {
            // Remove leading/trailing spaces if any
            while (*fullName == ' ') memmove(fullName, fullName+1, strlen(fullName));
            while (*department == ' ') memmove(department, department+1, strlen(department));
            while (*specialty == ' ') memmove(specialty, specialty+1, strlen(specialty));
            while (*email == ' ') memmove(email, email+1, strlen(email));
            while (*phone == ' ') memmove(phone, phone+1, strlen(phone));
            printf("%-10s %-25s %-20s %-20s %-25s %-15s\n", lecturerId, fullName, department, specialty, email, phone);
        }
    }
    fclose(file);
}

Lecturer* findLecturer(Lecturer* head, char* lecturerId) {
    (void)head;
    FILE* file = fopen("database/lecturers.csv", "r");
    if (!file) return NULL;
    static Lecturer found;
    char line[512];
    while (fgets(line, sizeof(line), file)) {
        char id[MAX_ID], name[MAX_STRING], department[MAX_STRING], specialty[MAX_STRING], email[MAX_STRING], phone[MAX_STRING];
        int n = sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]", id, name, department, specialty, email, phone);
        if (n == 6 && strcmp(id, lecturerId) == 0) {
            strcpy(found.lecturerId, id);
            strcpy(found.fullName, name);
            strcpy(found.department, department);
            strcpy(found.specialty, specialty);
            strcpy(found.email, email);
            strcpy(found.phone, phone);
            fclose(file);
            return &found;
        }
    }
    fclose(file);
    return NULL;
}

void updateLecturer(Lecturer* head, char* lecturerId) {
    (void)head;
    FILE* file = fopen("database/lecturers.csv", "r");
    if (!file) { printf("Khong the mo file!\n"); return; }
    Lecturer list[1000]; int n = 0;
    char line[512]; int found = 0;
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]", list[n].lecturerId, list[n].fullName, list[n].department, list[n].specialty, list[n].email, list[n].phone);
        n++;
    }
    fclose(file);
    for (int i = 0; i < n; ++i) {
        if (strcmp(list[i].lecturerId, lecturerId) == 0) {
            found = 1;
            printf("\n=== CAP NHAT THONG TIN GIANG VIEN ===\n");
            printf("Ma GV: %s\n", list[i].lecturerId);
            printf("Ho ten: %s\n", list[i].fullName);
            printf("Khoa: %s\n", list[i].department);
            printf("Chuyen nganh: %s\n", list[i].specialty);
            printf("Email: %s\n", list[i].email);
            printf("So dien thoai: %s\n", list[i].phone);
            char buffer[MAX_STRING];
            printf("Ho ten moi: ");
            fgets(buffer, MAX_STRING, stdin);
            if (strlen(buffer) > 1) { buffer[strcspn(buffer, "\n")] = 0; strcpy(list[i].fullName, buffer); }
            printf("Khoa moi: ");
            fgets(buffer, MAX_STRING, stdin);
            if (strlen(buffer) > 1) { buffer[strcspn(buffer, "\n")] = 0; strcpy(list[i].department, buffer); }
            printf("Chuyen nganh moi: ");
            fgets(buffer, MAX_STRING, stdin);
            if (strlen(buffer) > 1) { buffer[strcspn(buffer, "\n")] = 0; strcpy(list[i].specialty, buffer); }
            printf("Email moi: ");
            fgets(buffer, MAX_STRING, stdin);
            if (strlen(buffer) > 1) { buffer[strcspn(buffer, "\n")] = 0; strcpy(list[i].email, buffer); }
            printf("So dien thoai moi: ");
            fgets(buffer, MAX_STRING, stdin);
            if (strlen(buffer) > 1) { buffer[strcspn(buffer, "\n")] = 0; strcpy(list[i].phone, buffer); }
            printf("Cap nhat thong tin thanh cong!\n");
            break;
        }
    }
    if (!found) { printf("Khong tim thay giang vien co ma %s!\n", lecturerId); return; }
    file = fopen("database/lecturers.csv", "w");
    for (int i = 0; i < n; ++i)
        fprintf(file, "%s,%s,%s,%s,%s,%s\n", list[i].lecturerId, list[i].fullName, list[i].department, list[i].specialty, list[i].email, list[i].phone);
    fclose(file);
}

void deleteLecturer(Lecturer** head, char* lecturerId) {
    (void)head;
    FILE* file = fopen("database/lecturers.csv", "r");
    if (!file) { printf("Khong the mo file!\n"); return; }
    Lecturer list[1000]; int n = 0, idx = -1;
    char line[512];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]", list[n].lecturerId, list[n].fullName, list[n].department, list[n].specialty, list[n].email, list[n].phone);
        if (strcmp(list[n].lecturerId, lecturerId) == 0) idx = n;
        n++;
    }
    fclose(file);
    if (idx == -1) { printf("Khong tim thay giang vien co ma %s!\n", lecturerId); return; }
    for (int i = idx; i < n - 1; ++i) list[i] = list[i + 1];
    n--;
    file = fopen("database/lecturers.csv", "w");
    for (int i = 0; i < n; ++i)
        fprintf(file, "%s,%s,%s,%s,%s,%s\n", list[i].lecturerId, list[i].fullName, list[i].department, list[i].specialty, list[i].email, list[i].phone);
    fclose(file);
    printf("Xoa giang vien thanh cong!\n");
}

void loadLecturersFromFile(Lecturer** head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return;
    char line[512];
    while (fgets(line, sizeof(line), file)) {
        Lecturer* newLecturer = (Lecturer*)malloc(sizeof(Lecturer));
        if (!newLecturer) continue;
        if (sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,\n]", newLecturer->lecturerId, newLecturer->fullName, newLecturer->department, newLecturer->specialty, newLecturer->email, newLecturer->phone) == 6) {
            newLecturer->next = *head;
            *head = newLecturer;
        } else {
            free(newLecturer);
        }
    }
    fclose(file);
}