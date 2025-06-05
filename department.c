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
    (void)head;
    struct _stat st = {0};
    if (_stat("database", &st) == -1) _mkdir("database");
    Department newDepartment;
    printf("\n=== THEM KHOA MOI ===\n");
    printf("Ma khoa: ");
    scanf("%s", newDepartment.departmentId);
    clearInputBuffer();
    printf("Ten khoa: ");
    fgets(newDepartment.departmentName, MAX_STRING, stdin);
    newDepartment.departmentName[strcspn(newDepartment.departmentName, "\n")] = 0;
    printf("Ma truong khoa: ");
    scanf("%s", newDepartment.headLecturerId);
    FILE* file = fopen("database/departments.csv", "a");
    if (file) {
        fprintf(file, "%s,%s,%s\n", newDepartment.departmentId, newDepartment.departmentName, newDepartment.headLecturerId);
        fclose(file);
        printf("Them khoa thanh cong!\n");
    } else {
        printf("Khong the mo file database/departments.csv de ghi!\n");
    }
}

void displayDepartments(Department* head) {
    (void)head;
    FILE* file = fopen("database/departments.csv", "r");
    if (!file) {
        printf("Khong the mo file database/departments.csv de doc hoac danh sach khoa trong!\n");
        return;
    }
    printf("\n=== DANH SACH KHOA ===\n");
    printf("%-10s %-30s %-15s\n", "Ma khoa", "Ten khoa", "Ma truong khoa");
    printf("========================================================\n");
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char departmentId[MAX_ID], departmentName[MAX_STRING], headLecturerId[MAX_ID];
        int n = sscanf(line, "%[^,],%[^,],%[^\n]", departmentId, departmentName, headLecturerId);
        if (n == 3) {
            printf("%-10s %-30s %-15s\n", departmentId, departmentName, headLecturerId);
        }
    }
    fclose(file);
}

Department* findDepartment(Department* head, char* departmentId) {
    (void)head;
    FILE* file = fopen("database/departments.csv", "r");
    if (!file) return NULL;
    static Department found;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char id[MAX_ID], name[MAX_STRING], headId[MAX_ID];
        int n = sscanf(line, "%[^,],%[^,],%[^\n]", id, name, headId);
        if (n == 3 && strcmp(id, departmentId) == 0) {
            strcpy(found.departmentId, id);
            strcpy(found.departmentName, name);
            strcpy(found.headLecturerId, headId);
            fclose(file);
            return &found;
        }
    }
    fclose(file);
    return NULL;
}

void updateDepartment(Department* head, char* departmentId) {
    (void)head;
    FILE* file = fopen("database/departments.csv", "r");
    if (!file) { printf("Khong the mo file!\n"); return; }
    Department list[1000]; int n = 0;
    char line[256]; int found = 0;
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%[^,],%[^\n]", list[n].departmentId, list[n].departmentName, list[n].headLecturerId);
        n++;
    }
    fclose(file);
    for (int i = 0; i < n; ++i) {
        if (strcmp(list[i].departmentId, departmentId) == 0) {
            found = 1;
            printf("\n=== CAP NHAT THONG TIN KHOA ===\n");
            printf("Ma khoa: %s\n", list[i].departmentId);
            printf("Ten khoa: %s\n", list[i].departmentName);
            printf("Ma truong khoa: %s\n", list[i].headLecturerId);
            char buffer[MAX_STRING];
            printf("Ten khoa moi: ");
            fgets(buffer, MAX_STRING, stdin);
            if (strlen(buffer) > 1) { buffer[strcspn(buffer, "\n")] = 0; strcpy(list[i].departmentName, buffer); }
            printf("Ma truong khoa moi: ");
            fgets(buffer, MAX_STRING, stdin);
            if (strlen(buffer) > 1) { buffer[strcspn(buffer, "\n")] = 0; strcpy(list[i].headLecturerId, buffer); }
            printf("Cap nhat khoa thanh cong!\n");
            break;
        }
    }
    if (!found) { printf("Khong tim thay khoa co ma %s!\n", departmentId); return; }
    file = fopen("database/departments.csv", "w");
    for (int i = 0; i < n; ++i)
        fprintf(file, "%s,%s,%s\n", list[i].departmentId, list[i].departmentName, list[i].headLecturerId);
    fclose(file);
}

void deleteDepartment(Department** head, char* departmentId) {
    (void)head;
    FILE* file = fopen("database/departments.csv", "r");
    if (!file) { printf("Khong the mo file!\n"); return; }
    Department list[1000]; int n = 0, idx = -1;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%[^,],%[^\n]", list[n].departmentId, list[n].departmentName, list[n].headLecturerId);
        if (strcmp(list[n].departmentId, departmentId) == 0) idx = n;
        n++;
    }
    fclose(file);
    if (idx == -1) { printf("Khong tim thay khoa co ma %s!\n", departmentId); return; }
    for (int i = idx; i < n - 1; ++i) list[i] = list[i + 1];
    n--;
    file = fopen("database/departments.csv", "w");
    for (int i = 0; i < n; ++i)
        fprintf(file, "%s,%s,%s\n", list[i].departmentId, list[i].departmentName, list[i].headLecturerId);
    fclose(file);
    printf("Xoa khoa thanh cong!\n");
}