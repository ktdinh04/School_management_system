#ifndef SCHOOL_MANAGEMENT_H
#define SCHOOL_MANAGEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STRING 100
#define MAX_ID 20

// Cấu trúc Date
typedef struct {
    int day, month, year;
} Date;

// Cấu trúc Student
typedef struct Student {
    char studentId[MAX_ID];
    char fullName[MAX_STRING];
    Date birthDate;
    char gender[10];
    char department[MAX_STRING];
    char email[MAX_STRING];
    char phone[MAX_STRING];
    struct Student* next;
} Student;

// Cấu trúc Lecturer
typedef struct Lecturer {
    char lecturerId[MAX_ID];
    char fullName[MAX_STRING];
    char department[MAX_STRING];
    char specialty[MAX_STRING];
    char email[MAX_STRING];
    char phone[MAX_STRING];
    struct Lecturer* next;
} Lecturer;

// Cấu trúc Course
typedef struct Course {
    char courseId[MAX_ID];
    char courseName[MAX_STRING];
    int credits;
    char lecturerId[MAX_ID];
    struct Course* next;
} Course;

// Cấu trúc ClassSchedule
typedef struct ClassSchedule {
    char scheduleId[MAX_ID];
    char courseId[MAX_ID];
    int dayOfWeek; // 2-8 (Thứ 2 đến Chủ nhật)
    int startHour;
    int endHour;
    char classroom[MAX_STRING];
    struct ClassSchedule* next;
} ClassSchedule;

// Cấu trúc Tuition
typedef struct Tuition {
    char tuitionId[MAX_ID];
    char studentId[MAX_ID];
    char semester[MAX_STRING];
    double totalAmount;
    double paidAmount;
    Date dueDate;
    char status[MAX_STRING]; // "Paid", "Unpaid", "Partial"
    struct Tuition* next;
} Tuition;

// Cấu trúc Department
typedef struct Department {
    char departmentId[MAX_ID];
    char departmentName[MAX_STRING];
    char headLecturerId[MAX_ID];
    struct Department* next;
} Department;

// Cấu trúc chứa tất cả danh sách
typedef struct {
    Student* students;
    Lecturer* lecturers;
    Course* courses;
    ClassSchedule* schedules;
    Tuition* tuitions;
    Department* departments;
} SchoolSystem;

// Function prototypes
void initializeSystem(SchoolSystem* system);
void displayMainMenu();
void displayStudentMenu();
void displayLecturerMenu();
void displayCourseMenu();
void displayScheduleMenu();
void displayTuitionMenu();
void displayReportMenu();
void handleMenuChoice(SchoolSystem* system, int choice);
void handleStudentMenu(SchoolSystem* system);
void handleLecturerMenu(SchoolSystem* system);
void handleCourseMenu(SchoolSystem* system);
void handleScheduleMenu(SchoolSystem* system);
void handleTuitionMenu(SchoolSystem* system);
void handleReportMenu(SchoolSystem* system);
void freeAllMemory(SchoolSystem* system);

// Student functions
void addStudent(Student** head);
void displayStudents(Student* head);
void deleteStudent(Student** head, char* studentId);
Student* findStudent(Student* head, char* studentId);
void updateStudent(Student* head, char* studentId);
void saveStudentsToFile(Student* head, const char* filename);
void loadStudentsFromFile(Student** head, const char* filename);

// Lecturer functions
void addLecturer(Lecturer** head);
void displayLecturers(Lecturer* head);
void deleteLecturer(Lecturer** head, char* lecturerId);
Lecturer* findLecturer(Lecturer* head, char* lecturerId);
void updateLecturer(Lecturer* head, char* lecturerId);
void saveLecturersToFile(Lecturer* head, const char* filename);
void loadLecturersFromFile(Lecturer** head, const char* filename);

// Course functions
void addCourse(Course** head);
void displayCourses(Course* head);
void deleteCourse(Course** head, char* courseId);
Course* findCourse(Course* head, char* courseId);
void updateCourse(Course* head, char* courseId);
void saveCoursesToFile(Course* head, const char* filename);
void loadCoursesFromFile(Course** head, const char* filename);

// Schedule functions
void addSchedule(ClassSchedule** head);
void displaySchedules(ClassSchedule* head);
void deleteSchedule(ClassSchedule** head, char* scheduleId);
ClassSchedule* findSchedule(ClassSchedule* head, char* scheduleId);
void displayLecturerSchedule(ClassSchedule* schedules, Course* courses, char* lecturerId);
void saveSchedulesToFile(ClassSchedule* head, const char* filename);
void loadSchedulesFromFile(ClassSchedule** head, const char* filename);

// Tuition functions
void addTuition(Tuition** head);
void displayTuitions(Tuition* head);
void updateTuitionPayment(Tuition* head, char* tuitionId);
void displayUnpaidTuitions(Tuition* head);
void calculateTuitionByCredits(Course* courses, char* studentId, int totalCredits, double pricePerCredit);

// Department functions
void addDepartment(Department** head);
void displayDepartments(Department* head);
void deleteDepartment(Department** head, char* departmentId);
Department* findDepartment(Department* head, char* departmentId);
void updateDepartment(Department* head, char* departmentId);
void saveDepartmentsToFile(Department* head, const char* filename);
void loadDepartmentsFromFile(Department** head, const char* filename);

// Utility functions
void clearInputBuffer();
Date inputDate();
void displayDate(Date date);

#endif
