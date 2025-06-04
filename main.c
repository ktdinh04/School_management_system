#include "school_management.h"

void initializeSystem(SchoolSystem* system) {
    system->students = NULL;
    system->lecturers = NULL;
    system->courses = NULL;
    system->schedules = NULL;
    system->tuitions = NULL;
    system->departments = NULL;
}

void displayMainMenu() {
    printf("\n=== HE THONG QUAN LY DAO TAO ===\n");
    printf("1. Quan ly sinh vien\n");
    printf("2. Quan ly giang vien\n");
    printf("3. Quan ly mon hoc\n");
    printf("4. Quan ly thoi khoa bieu\n");
    printf("5. Quan ly hoc phi\n");
    printf("6. Quan ly nganh\n");
    printf("7. Bao cao\n");
    printf("8. Luu du lieu\n");
    printf("9. Tai du lieu\n");
    printf("0. Thoat\n");
    printf("Chon chuc nang: ");
}

void displayStudentMenu() {
    printf("\n=== QUAN LY SINH VIEN ===\n");
    printf("1. Them sinh vien\n");
    printf("2. Hien thi danh sach sinh vien\n");
    printf("3. Tim kiem sinh vien\n");
    printf("4. Cap nhat thong tin sinh vien\n");
    printf("5. Xoa sinh vien\n");
    printf("0. Quay lai menu chinh\n");
    printf("Chon: ");
}

void displayLecturerMenu() {
    printf("\n=== QUAN LY GIANG VIEN ===\n");
    printf("1. Them giang vien\n");
    printf("2. Hien thi danh sach giang vien\n");
    printf("3. Tim kiem giang vien\n");
    printf("4. Cap nhat thong tin giang vien\n");
    printf("5. Xoa giang vien\n");
    printf("0. Quay lai menu chinh\n");
    printf("Chon: ");
}

void displayCourseMenu() {
    printf("\n=== QUAN LY MON HOC ===\n");
    printf("1. Them mon hoc\n");
    printf("2. Hien thi danh sach mon hoc\n");
    printf("3. Tim kiem mon hoc\n");
    printf("4. Cap nhat thong tin mon hoc\n");
    printf("5. Xoa mon hoc\n");
    printf("0. Quay lai menu chinh\n");
    printf("Chon: ");
}

void displayScheduleMenu() {
    printf("\n=== QUAN LY THOI KHOA BIEU ===\n");
    printf("1. Them lich hoc\n");
    printf("2. Hien thi tat ca lich hoc\n");
    printf("3. Xem lich giang day cua giang vien\n");
    printf("4. Xoa lich hoc\n");
    printf("0. Quay lai menu chinh\n");
    printf("Chon: ");
}

void displayTuitionMenu() {
    printf("\n=== QUAN LY HOC PHI ===\n");
    printf("1. Them hoc phi\n");
    printf("2. Hien thi tat ca hoc phi\n");
    printf("3. Cap nhat thanh toan hoc phi\n");
    printf("4. Xem hoc phi chua thanh toan\n");
    printf("0. Quay lai menu chinh\n");
    printf("Chon: ");
}

void displayReportMenu() {
    printf("\n=== BAO CAO ===\n");
    printf("1. Lich giang day cua giang vien\n");
    printf("2. Danh sach hoc phi chua thanh toan\n");
    printf("3. Thong ke so luong sinh vien theo khoa\n");
    printf("0. Quay lai menu chinh\n");
    printf("Chon: ");
}

void displayDepartmentMenu() {
    printf("\n=== QUAN LY KHOA ===\n");
    printf("1. Them khoa\n");
    printf("2. Hien thi danh sach khoa\n");
    printf("3. Cap nhat thong tin khoa\n");
    printf("4. Xoa khoa\n");
    printf("0. Quay lai menu chinh\n");
    printf("Chon: ");
}

void handleStudentMenu(SchoolSystem* system) {
    int choice;
    char id[MAX_ID];
    
    do {
        displayStudentMenu();
        scanf("%d", &choice);
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                addStudent(&system->students);
                break;
            case 2:
                displayStudents(system->students);
                break;
            case 3:
                printf("Nhap ma sinh vien can tim: ");
                scanf("%s", id);
                Student* found = findStudent(system->students, id);
                if (found) {
                    printf("Tim thay sinh vien: %s - %s\n", found->studentId, found->fullName);
                } else {
                    printf("Khong tim thay sinh vien!\n");
                }
                break;
            case 4:
                printf("Nhap ma sinh vien can cap nhat: ");
                scanf("%s", id);
                clearInputBuffer();
                updateStudent(system->students, id);
                break;
            case 5:
                printf("Nhap ma sinh vien can xoa: ");
                scanf("%s", id);
                deleteStudent(&system->students, id);
                break;
            case 0:
                return;
            default:
                printf("Lua chon khong hop le!\n");
        }
        
        if (choice != 0) {
            printf("\nNhan Enter de tiep tuc...");
            getchar();
        }
    } while (choice != 0);
}

void handleLecturerMenu(SchoolSystem* system) {
    int choice;
    char id[MAX_ID];
    
    do {
        displayLecturerMenu();
        scanf("%d", &choice);
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                addLecturer(&system->lecturers);
                break;
            case 2:
                displayLecturers(system->lecturers);
                break;
            case 3:
                printf("Nhap ma giang vien can tim: ");
                scanf("%s", id);
                Lecturer* found = findLecturer(system->lecturers, id);
                if (found) {
                    printf("Tim thay giang vien: %s - %s\n", found->lecturerId, found->fullName);
                } else {
                    printf("Khong tim thay giang vien!\n");
                }
                break;
            case 4:
                printf("Nhap ma giang vien can cap nhat: ");
                scanf("%s", id);
                clearInputBuffer();
                updateLecturer(system->lecturers, id);
                break;
            case 5:
                printf("Nhap ma giang vien can xoa: ");
                scanf("%s", id);
                deleteLecturer(&system->lecturers, id);
                break;
            case 0:
                return;
            default:
                printf("Lua chon khong hop le!\n");
        }
        
        if (choice != 0) {
            printf("\nNhan Enter de tiep tuc...");
            getchar();
        }
    } while (choice != 0);
}

void handleCourseMenu(SchoolSystem* system) {
    int choice;
    char id[MAX_ID];
    
    do {
        displayCourseMenu();
        scanf("%d", &choice);
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                addCourse(&system->courses);
                break;
            case 2:
                displayCourses(system->courses);
                break;
            case 3:
                printf("Nhap ma mon hoc can tim: ");
                scanf("%s", id);
                Course* found = findCourse(system->courses, id);
                if (found) {
                    printf("Tim thay mon hoc: %s - %s\n", found->courseId, found->courseName);
                } else {
                    printf("Khong tim thay mon hoc!\n");
                }
                break;
            case 4:
                printf("Nhap ma mon hoc can cap nhat: ");
                scanf("%s", id);
                clearInputBuffer();
                updateCourse(system->courses, id);
                break;
            case 5:
                printf("Nhap ma mon hoc can xoa: ");
                scanf("%s", id);
                deleteCourse(&system->courses, id);
                break;
            case 0:
                return;
            default:
                printf("Lua chon khong hop le!\n");
        }
        
        if (choice != 0) {
            printf("\nNhan Enter de tiep tuc...");
            getchar();
        }
    } while (choice != 0);
}

void handleScheduleMenu(SchoolSystem* system) {
    int choice;
    char id[MAX_ID];
    
    do {
        displayScheduleMenu();
        scanf("%d", &choice);
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                addSchedule(&system->schedules);
                break;
            case 2:
                displaySchedules(system->schedules);
                break;
            case 3:
                printf("Nhap ma giang vien: ");
                scanf("%s", id);
                displayLecturerSchedule(system->schedules, system->courses, id);
                break;
            case 4:
                printf("Nhap ma lich can xoa: ");
                scanf("%s", id);
                deleteSchedule(&system->schedules, id);
                break;
            case 0:
                return;
            default:
                printf("Lua chon khong hop le!\n");
        }
        
        if (choice != 0) {
            printf("\nNhan Enter de tiep tuc...");
            getchar();
        }
    } while (choice != 0);
}

void handleTuitionMenu(SchoolSystem* system) {
    int choice;
    char id[MAX_ID];
    
    do {
        displayTuitionMenu();
        scanf("%d", &choice);
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                addTuition(&system->tuitions);
                break;
            case 2:
                displayTuitions(system->tuitions);
                break;
            case 3:
                printf("Nhap ma hoc phi can cap nhat: ");
                scanf("%s", id);
                updateTuitionPayment(system->tuitions, id);
                break;
            case 4:
                displayUnpaidTuitions(system->tuitions);
                break;
            case 0:
                return;
            default:
                printf("Lua chon khong hop le!\n");
        }
        
        if (choice != 0) {
            printf("\nNhan Enter de tiep tuc...");
            getchar();
        }
    } while (choice != 0);
}

void handleReportMenu(SchoolSystem* system) {
    int choice;
    char id[MAX_ID];
    
    do {
        displayReportMenu();
        scanf("%d", &choice);
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                printf("Nhap ma giang vien: ");
                scanf("%s", id);
                displayLecturerSchedule(system->schedules, system->courses, id);
                break;
            case 2:
                displayUnpaidTuitions(system->tuitions);
                break;
            case 3:
                printf("Chuc nang thong ke dang duoc phat trien...\n");
                break;
            case 0:
                return;
            default:
                printf("Lua chon khong hop le!\n");
        }
        
        if (choice != 0) {
            printf("\nNhan Enter de tiep tuc...");
            getchar();
        }
    } while (choice != 0);
}

void handleDepartmentMenu(SchoolSystem* system) {
    int choice;
    char id[MAX_ID];
    do {
        displayDepartmentMenu();
        scanf("%d", &choice);
        clearInputBuffer();
        switch (choice) {
            case 1:
                addDepartment(&system->departments);
                break;
            case 2:
                displayDepartments(system->departments);
                break;
            case 3:
                printf("Nhap ma khoa can cap nhat: ");
                scanf("%s", id);
                clearInputBuffer();
                updateDepartment(system->departments, id);
                break;
            case 4:
                printf("Nhap ma khoa can xoa: ");
                scanf("%s", id);
                deleteDepartment(&system->departments, id);
                break;
            case 0:
                return;
            default:
                printf("Lua chon khong hop le!\n");
        }
        if (choice != 0) {
            printf("\nNhan Enter de tiep tuc...");
            getchar();
        }
    } while (choice != 0);
}

void handleMenuChoice(SchoolSystem* system, int choice) {
    switch (choice) {
        case 1:
            handleStudentMenu(system);
            break;
        case 2:
            handleLecturerMenu(system);
            break;
        case 3:
            handleCourseMenu(system);
            break;
        case 4:
            handleScheduleMenu(system);
            break;
        case 5:
            handleTuitionMenu(system);
            break;
        case 6:
            handleDepartmentMenu(system);
            break;
        case 7:
            handleReportMenu(system);
            break;
        case 8:
            saveStudentsToFile(system->students, "students.txt");
            saveLecturersToFile(system->lecturers, "lecturers.txt");
            saveCoursesToFile(system->courses, "courses.txt");
            saveDepartmentsToFile(system->departments, "database/departments.csv");
            printf("Luu tat ca du lieu thanh cong!\n");
            break;
        case 9:
            loadStudentsFromFile(&system->students, "students.txt");
            loadLecturersFromFile(&system->lecturers, "lecturers.txt");
            loadCoursesFromFile(&system->courses, "courses.txt");
            loadDepartmentsFromFile(&system->departments, "database/departments.csv");
            printf("Tai tat ca du lieu thanh cong!\n");
            break;
        case 0:
            printf("Thoat chuong trinh!\n");
            break;
        default:
            printf("Lua chon khong hop le!\n");
    }
}

void freeAllMemory(SchoolSystem* system) {
    // Free students
    Student* currentStudent = system->students;
    while (currentStudent) {
        Student* temp = currentStudent;
        currentStudent = currentStudent->next;
        free(temp);
    }
    
    // Free lecturers
    Lecturer* currentLecturer = system->lecturers;
    while (currentLecturer) {
        Lecturer* temp = currentLecturer;
        currentLecturer = currentLecturer->next;
        free(temp);
    }
    
    // Free courses
    Course* currentCourse = system->courses;
    while (currentCourse) {
        Course* temp = currentCourse;
        currentCourse = currentCourse->next;
        free(temp);
    }
    
    // Free schedules
    ClassSchedule* currentSchedule = system->schedules;
    while (currentSchedule) {
        ClassSchedule* temp = currentSchedule;
        currentSchedule = currentSchedule->next;
        free(temp);
    }
    
    // Free tuitions
    Tuition* currentTuition = system->tuitions;
    while (currentTuition) {
        Tuition* temp = currentTuition;
        currentTuition = currentTuition->next;
        free(temp);
    }
    
    // Free departments
    Department* currentDepartment = system->departments;
    while (currentDepartment) {
        Department* temp = currentDepartment;
        currentDepartment = currentDepartment->next;
        free(temp);
    }
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

Date inputDate() {
    Date date;
    scanf("%d/%d/%d", &date.day, &date.month, &date.year);
    return date;
}

void displayDate(Date date) {
    printf("%02d/%02d/%04d", date.day, date.month, date.year);
}

int main() {
    SchoolSystem system;
    initializeSystem(&system);
    
    int choice;
    
    printf("Chao mung den voi He thong Quan ly Dao tao!\n");
    
    do {
        displayMainMenu();
        scanf("%d", &choice);
        clearInputBuffer();
        
        handleMenuChoice(&system, choice);
        
        if (choice != 0) {
            printf("\nNhan Enter de tiep tuc...");
            getchar();
        }
        
    } while (choice != 0);
    
    freeAllMemory(&system);
    return 0;
}
