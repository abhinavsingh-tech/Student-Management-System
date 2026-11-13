
#include <stdio.h>
#include <string.h>

struct Student {
    char name[50];
    int roll;
    char course[30];
    float marks;
};

struct Student s[100];
int count = 0;

// Find student using roll number
int findStudent(int roll) {
    for (int i = 0; i < count; i++) {
        if (s[i].roll == roll) {
            return i;
        }
    }
    return -1;
}

// Save records to file
void saveRecords() {
    FILE *file = fopen("students.dat", "wb");

    if (file == NULL) {
        printf("\nError saving records!\n");
        return;
    }

    fwrite(s, sizeof(struct Student), count, file);
    fclose(file);
}

// Load records from file
void loadRecords() {
    FILE *file = fopen("students.dat", "rb");

    if (file == NULL) {
        return;
    }

    count = fread(s, sizeof(struct Student), 100, file);
    fclose(file);
}

// Add student
void addStudent() {
    if (count >= 100) {
        printf("\nStudent limit reached!\n");
        return;
    }

    int roll;

    printf("\nEnter student name: ");
    scanf(" %49[^\n]", s[count].name);

    printf("Enter roll number: ");
    scanf("%d", &roll);

    if (findStudent(roll) != -1) {
        printf("\nRoll number already exists!\n");
        return;
    }

    s[count].roll = roll;

    printf("Enter course: ");
    scanf(" %29[^\n]", s[count].course);

    printf("Enter marks: ");
    scanf("%f", &s[count].marks);

    count++;

    saveRecords();

    printf("\nStudent added successfully!\n");
}

// View all students
void viewStudents() {
    if (count == 0) {
        printf("\nNo student records found!\n");
        return;
    }

    printf("\n========== STUDENT RECORDS ==========\n");

    for (int i = 0; i < count; i++) {
        printf("\nStudent %d\n", i + 1);
        printf("Name       : %s\n", s[i].name);
        printf("Roll Number: %d\n", s[i].roll);
        printf("Course     : %s\n", s[i].course);
        printf("Marks      : %.2f\n", s[i].marks);
        printf("-------------------------------------\n");
    }
}

// Search student
void searchStudent() {
    int roll;

    printf("\nEnter roll number to search: ");
    scanf("%d", &roll);

    int index = findStudent(roll);

    if (index == -1) {
        printf("\nStudent not found!\n");
    } else {
        printf("\nStudent Found!\n");
        printf("Name       : %s\n", s[index].name);
        printf("Roll Number: %d\n", s[index].roll);
        printf("Course     : %s\n", s[index].course);
        printf("Marks      : %.2f\n", s[index].marks);
    }
}

// Update student
void updateStudent() {
    int roll;

    printf("\nEnter roll number to update: ");
    scanf("%d", &roll);

    int index = findStudent(roll);

    if (index == -1) {
        printf("\nStudent not found!\n");
        return;
    }

    printf("\nEnter new name: ");
    scanf(" %49[^\n]", s[index].name);

    printf("Enter new course: ");
    scanf(" %29[^\n]", s[index].course);

    printf("Enter new marks: ");
    scanf("%f", &s[index].marks);

    saveRecords();

    printf("\nStudent details updated successfully!\n");
}

// Delete student
void deleteStudent() {
    int roll;

    printf("\nEnter roll number to delete: ");
    scanf("%d", &roll);

    int index = findStudent(roll);

    if (index == -1) {
        printf("\nStudent not found!\n");
        return;
    }

    for (int i = index; i < count - 1; i++) {
        s[i] = s[i + 1];
    }

    count--;

    saveRecords();

    printf("\nStudent deleted successfully!\n");
}

// Main function
int main() {
    int choice;

    loadRecords();

    do {
        printf("\n\n=====================================");
        printf("\n       STUDENT MANAGEMENT SYSTEM");
        printf("\n=====================================");
        printf("\n1. Add Student");
        printf("\n2. View All Students");
        printf("\n3. Search Student");
        printf("\n4. Update Student");
        printf("\n5. Delete Student");
        printf("\n6. Exit");
        printf("\n=====================================");
        printf("\nEnter your choice: ");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;

            case 2:
                viewStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                printf("\nThank you for using Student Management System!\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 6);

    return 0;
}
