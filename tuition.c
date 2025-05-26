#include "school_management.h"

void addTuition(Tuition** head) {
    Tuition* newTuition = (Tuition*)malloc(sizeof(Tuition));
    if (!newTuition) {
        printf("Loi cap phat bo nho!\n");
        return;
    }
    
    printf("\n=== THEM HOC PHI MOI ===\n");
    printf("Ma hoc phi: ");
    scanf("%s", newTuition->tuitionId);
    
    printf("Ma sinh vien: ");
    scanf("%s", newTuition->studentId);
    clearInputBuffer();
    
    printf("Hoc ky: ");
    fgets(newTuition->semester, MAX_STRING, stdin);
    newTuition->semester[strcspn(newTuition->semester, "\n")] = 0;
    
    printf("Tong so tien: ");
    scanf("%lf", &newTuition->totalAmount);
    
    printf("So tien da nop: ");
    scanf("%lf", &newTuition->paidAmount);
    
    printf("Han nop (dd/mm/yyyy): ");
    newTuition->dueDate = inputDate();
    
    // Tự động xác định trạng thái
    if (newTuition->paidAmount >= newTuition->totalAmount) {
        strcpy(newTuition->status, "Paid");
    } else if (newTuition->paidAmount > 0) {
        strcpy(newTuition->status, "Partial");
    } else {
        strcpy(newTuition->status, "Unpaid");
    }
    
    newTuition->next = *head;
    *head = newTuition;
    
    printf("Them hoc phi thanh cong!\n");
}

void displayTuitions(Tuition* head) {
    if (!head) {
        printf("Danh sach hoc phi trong!\n");
        return;
    }
    
    printf("\n=== DANH SACH HOC PHI ===\n");
    printf("%-10s %-10s %-15s %-12s %-12s %-12s %-10s\n", 
           "Ma HP", "Ma SV", "Hoc ky", "Tong tien", "Da nop", "Han nop", "Trang thai");
    printf("===================================================================================\n");
    
    Tuition* current = head;
    while (current) {
        printf("%-10s %-10s %-15s %-12.0f %-12.0f %02d/%02d/%04d %-10s\n",
               current->tuitionId, current->studentId, current->semester,
               current->totalAmount, current->paidAmount,
               current->dueDate.day, current->dueDate.month, current->dueDate.year,
               current->status);
        current = current->next;
    }
}

void updateTuitionPayment(Tuition* head, char* tuitionId) {
    Tuition* current = head;
    while (current) {
        if (strcmp(current->tuitionId, tuitionId) == 0) {
            printf("\n=== CAP NHAT THANH TOAN HOC PHI ===\n");
            printf("Thong tin hien tai:\n");
            printf("Ma hoc phi: %s\n", current->tuitionId);
            printf("Tong tien: %.0f\n", current->totalAmount);
            printf("Da nop: %.0f\n", current->paidAmount);
            printf("Con lai: %.0f\n", current->totalAmount - current->paidAmount);
            
            printf("\nSo tien thanh toan them: ");
            double payment;
            scanf("%lf", &payment);
            
            current->paidAmount += payment;
            
            // Cập nhật trạng thái
            if (current->paidAmount >= current->totalAmount) {
                strcpy(current->status, "Paid");
                printf("Hoc phi da duoc thanh toan day du!\n");
            } else if (current->paidAmount > 0) {
                strcpy(current->status, "Partial");
                printf("Con lai: %.0f\n", current->totalAmount - current->paidAmount);
            }
            
            return;
        }
        current = current->next;
    }
    printf("Khong tim thay hoc phi co ma %s!\n", tuitionId);
}

void displayUnpaidTuitions(Tuition* head) {
    printf("\n=== DANH SACH HOC PHI CHUA THANH TOAN ===\n");
    printf("%-10s %-10s %-15s %-12s %-12s %-12s %-10s\n", 
           "Ma HP", "Ma SV", "Hoc ky", "Tong tien", "Da nop", "Han nop", "Trang thai");
    printf("===================================================================================\n");
    
    Tuition* current = head;
    int found = 0;
    
    while (current) {
        if (strcmp(current->status, "Unpaid") == 0 || strcmp(current->status, "Partial") == 0) {
            printf("%-10s %-10s %-15s %-12.0f %-12.0f %02d/%02d/%04d %-10s\n",
                   current->tuitionId, current->studentId, current->semester,
                   current->totalAmount, current->paidAmount,
                   current->dueDate.day, current->dueDate.month, current->dueDate.year,
                   current->status);
            found = 1;
        }
        current = current->next;
    }
    
    if (!found) {
        printf("Tat ca hoc phi da duoc thanh toan!\n");
    }
}

void calculateTuitionByCredits(Course* courses, char* studentId, int totalCredits, double pricePerCredit) {
    printf("\n=== TINH HOC PHI THEO TIN CHI ===\n");
    printf("Ma sinh vien: %s\n", studentId);
    printf("Tong so tin chi: %d\n", totalCredits);
    printf("Gia moi tin chi: %.0f\n", pricePerCredit);
    printf("Tong hoc phi: %.0f\n", totalCredits * pricePerCredit);
}
