#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 100
#define PHONE_LEN 24
#define EMAIL_LEN 120
#define LINE_LEN 256

typedef struct {
    long long sapId;
    int rollNo;
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    char email[EMAIL_LEN];
    int year;
    int semester;
    double sgpa[8]; 
} Student;

static Student students[MAX_STUDENTS];
static int studentCount;

static void readLine(const char *prompt, char *buffer, size_t size) {
    for (;;) {
        printf("%s", prompt);
        if (!fgets(buffer, (int)size, stdin)) {
            puts("\nInput ended. Exiting.");
            exit(0);
        }
        if (strchr(buffer, '\n') || feof(stdin)) {
            buffer[strcspn(buffer, "\r\n")] = '\0';
            return;
        }
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        puts("Input too long. Please try again.");
    }
}

static double readDouble(const char *prompt, double min, double max) {
    char line[LINE_LEN], *end;
    for (;;) {
        readLine(prompt, line, sizeof line);
        errno = 0;
        double value = strtod(line, &end);
        while (isspace((unsigned char)*end)) end++;
        if (end != line && *end == '\0' && errno == 0 && value >= min && value <= max)
            return value;
        printf("Enter a number from %.1f to %.1f.\n", min, max);
    }
}

static long long readLongLong(const char *prompt, long long min, long long max) {
    char line[LINE_LEN], *end;
    for (;;) {
        readLine(prompt, line, sizeof line);
        errno = 0;
        long long value = strtoll(line, &end, 10);
        while (isspace((unsigned char)*end)) end++;
        if (end != line && *end == '\0' && errno == 0 && value >= min && value <= max)
            return value;
        printf("Enter a whole number from %lld to %lld.\n", min, max);
    }
}

static int findStudentIndex(long long sapId) {
    for (int i = 0; i < studentCount; i++)
        if (students[i].sapId == sapId) return i;
    return -1;
}

static double calculateCgpa(const Student *s) {
    double total = 0.0;
    int count = 0;
    for (int i = 0; i < 8; i++) {
        if (s->sgpa[i] > 0.0) { total += s->sgpa[i]; count++; }
    }
    return count ? total / count : 0.0;
}

static void academicAdvisor(const Student *s) {
    double cgpa = calculateCgpa(s);
    printf("Academic Advisor for %s (CGPA %.2f): ", s->name, cgpa);
    if (cgpa >= 9.0)
        puts("Excellent performance - maintain your current study pattern.");
    else if (cgpa >= 7.5)
        puts("Good performance - keep a steady routine and review challenging topics.");
    else if (cgpa >= 6.0)
        puts("Needs improvement - focus more on subjects with lower SGPA.");
    else
        puts("Requires immediate attention - meet your faculty advisor and make a study plan.");
}

static void displayStudent(const Student *s) {
    printf("\nSAP ID: %lld\nRoll No.: %d\nName: %s\nPhone: %s\nEmail: %s\nYear: %d\nCurrent semester: %d\n",
           s->sapId, s->rollNo, s->name, s->phone, s->email, s->year, s->semester);
    puts("Semester SGPA:");
    for (int i = 0; i < 8; i++) {
        if (s->sgpa[i] > 0.0) printf("  Sem %d: %.2f\n", i + 1, s->sgpa[i]);
        else printf("  Sem %d: Not entered\n", i + 1);
    }
    printf("CGPA (average of available SGPAs): %.2f\n", calculateCgpa(s));
}

static void addStudent(void) {
    if (studentCount >= MAX_STUDENTS) { puts("Record limit reached."); return; }
    Student s = {0};
    s.sapId = readLongLong("SAP ID: ", 1, 999999999999LL);
    if (findStudentIndex(s.sapId) >= 0) { puts("That SAP ID already exists."); return; }
    s.rollNo = (int)readLongLong("Roll No.: ", 1, 1000000);
    readLine("Name: ", s.name, sizeof s.name);
    readLine("Phone No.: ", s.phone, sizeof s.phone);
    readLine("Email ID: ", s.email, sizeof s.email);
    s.year = (int)readLongLong("Year (1=1st, 2=2nd, 3=3rd, 4=4th): ", 1, 4);
    s.semester = (int)readLongLong("Current semester (1-8): ", 1, 8);
    puts("Enter SGPA for completed semesters (0 if not available).");
    for (int i = 0; i < 8; i++) {
        char prompt[64];
        snprintf(prompt, sizeof prompt, "Semester %d SGPA (0-10): ", i + 1);
        s.sgpa[i] = readDouble(prompt, 0.0, 10.0);
    }
    students[studentCount++] = s;
    puts("Student record added.");
}

static void searchStudent(void) {
    long long id = readLongLong("Enter SAP ID to search: ", 1, 999999999999LL);
    int index = findStudentIndex(id);
    if (index < 0) puts("No student found with that SAP ID.");
    else displayStudent(&students[index]);
}

static void displayAll(void) {
    if (!studentCount) { puts("No student records available."); return; }
    for (int i = 0; i < studentCount; i++) displayStudent(&students[i]);
}

static void deleteStudent(void) {
    long long id = readLongLong("Enter SAP ID to delete: ", 1, 999999999999LL);
    int index = findStudentIndex(id);
    if (index < 0) { puts("No student found with that SAP ID."); return; }
    for (int i = index; i < studentCount - 1; i++) students[i] = students[i + 1];
    studentCount--;
    puts("Student record deleted.");
}

static void sortAndDisplay(int byName) {
    if (!studentCount) { puts("No student records available."); return; }
    Student sorted[MAX_STUDENTS];
    memcpy(sorted, students, (size_t)studentCount * sizeof(Student));
    for (int i = 0; i < studentCount - 1; i++)
        for (int j = 0; j < studentCount - i - 1; j++) {
            int swap = byName ? (strcmp(sorted[j].name, sorted[j + 1].name) > 0)
                              : (sorted[j].sapId > sorted[j + 1].sapId);
            if (swap) { Student temp = sorted[j]; sorted[j] = sorted[j + 1]; sorted[j + 1] = temp; }
        }
    for (int i = 0; i < studentCount; i++) displayStudent(&sorted[i]);
}

static void averageCgpaByYear(void) {
    for (int year = 1; year <= 4; year++) {
        double total = 0.0;
        int count = 0;
        for (int i = 0; i < studentCount; i++)
            if (students[i].year == year) { total += calculateCgpa(&students[i]); count++; }
        if (count) printf("Year %d average CGPA: %.2f (%d student%s)\n", year, total / count, count, count == 1 ? "" : "s");
        else printf("Year %d average CGPA: no students\n", year);
    }
}

static void adviseStudent(void) {
    long long id = readLongLong("Enter SAP ID for advice: ", 1, 999999999999LL);
    int index = findStudentIndex(id);
    if (index < 0) puts("No student found with that SAP ID.");
    else academicAdvisor(&students[index]);
}

int main(void) {
    for (;;) {
        puts("\n=== Student Record and Result Management System ===");
        puts("1. Add student\n2. Search/display by SAP ID\n3. Calculate CGPA and academic advice\n4. Average CGPA by year\n5. Display all records\n6. Delete a record\n7. Display by SAP ID (increasing)\n8. Display by name (increasing)\n0. Exit");
        int choice = (int)readLongLong("Choose an option: ", 0, 8);
        switch (choice) {
            case 1: addStudent(); break;
            case 2: searchStudent(); break;
            case 3: adviseStudent(); break;
            case 4: averageCgpaByYear(); break;
            case 5: displayAll(); break;
            case 6: deleteStudent(); break;
            case 7: sortAndDisplay(0); break;
            case 8: sortAndDisplay(1); break;
            case 0: puts("Goodbye."); return 0;
        }
    }
}
