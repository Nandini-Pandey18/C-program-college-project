// DOCTOR'S INVENTORY MANAGEMENT SYSTEM
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct Appointment {
    char name[50];
    int age;
    char gender[10];
    char doctorType[30];
    char doctor[50];
    char date[15];
    char time[20];
};
void assignDoctor(char docType[], char doctor[]) {
    if (strcmp(docType, "General Physician") == 0)
        strcpy(doctor, "Dr. Joshi");
    else if (strcmp(docType, "Cardiologist") == 0)
        strcpy(doctor, "Dr. Shalini");
    else if (strcmp(docType, "Dermatologist") == 0)
        strcpy(doctor, "Dr. Priya");
    else if (strcmp(docType, "Pediatrician") == 0)
        strcpy(doctor, "Dr. Mehra");
    else if (strcmp(docType, "Orthopedic") == 0)
        strcpy(doctor, "Dr. Roy");
    else
        strcpy(doctor, "Dr. Joshi");
}
int isSlotBooked(char doctorType[], char date[], char time[], char ignoreName[]) {
    FILE *fp = fopen("appointments.txt", "r");
    struct Appointment a;

    if (fp == NULL) return 0;

    while (fscanf(fp, " %49[^|]|%d|%9[^|]|%29[^|]|%49[^|]|%14[^|]|%19[^\n]\n",
                  a.name, &a.age, a.gender, a.doctorType,
                  a.doctor, a.date, a.time) == 7){
        if (strcmp(a.doctorType, doctorType) == 0 &&
            strcmp(a.date, date) == 0 &&
            strcmp(a.time, time) == 0 &&
            strcmp(a.name, ignoreName) != 0)
        {
            fclose(fp);
            return 1;
        }
    }
fclose(fp);
return 0;
}
void selectDoctorType(char type[]) {
    int choice;
    printf("\nSELECT DOCTOR TYPE:\n");
    printf("1. General Physician\n");
    printf("2. Cardiologist\n");
    printf("3. Dermatologist\n");
    printf("4. Pediatrician\n");
    printf("5. Orthopedic\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1: strcpy(type, "General Physician"); break;
        case 2: strcpy(type, "Cardiologist"); break;
        case 3: strcpy(type, "Dermatologist"); break;
        case 4: strcpy(type, "Pediatrician"); break;
        case 5: strcpy(type, "Orthopedic"); break;
        default: strcpy(type, "General Physician");
    }
}
void addAppointment() {
    struct Appointment a;
    FILE *fp = fopen("appointments.txt", "a");
    if (fp == NULL) {
        printf("\nError opening file!\n");
        return;
    }

    printf("\nEnter Patient Name: ");
    scanf(" %[^\n]", a.name);
    printf("Enter Age: ");
    scanf("%d", &a.age);
    printf("Enter Gender: ");
    scanf(" %[^\n]", a.gender);

    selectDoctorType(a.doctorType);
    assignDoctor(a.doctorType, a.doctor);

    printf("Enter Appointment Date (YYYY-MM-DD): ");
    scanf(" %[^\n]", a.date);
    printf("Enter Time Slot (e.g., 10:00 AM): ");
    scanf(" %[^\n]", a.time);

    if (isSlotBooked(a.doctorType, a.date, a.time, "")) {
        printf("\nSorry! This time slot is NOT AVAILABLE!\n");
        fclose(fp);
        return;
    }

    fprintf(fp, "%s|%d|%s|%s|%s|%s|%s\n",
            a.name, a.age, a.gender,
            a.doctorType, a.doctor,
            a.date, a.time);

    fclose(fp);
    printf("\nAppointment Added Successfully!\n");
}
void viewAppointments() {
    struct Appointment a;
    FILE *fp = fopen("appointments.txt", "r");
    int count = 0;

    if (fp == NULL) {
        printf("\nNo appointments found!\n");
        return;
    }

    printf("\n------ APPOINTMENT LIST ------\n");

    while (fscanf(fp, " %49[^|]|%d|%9[^|]|%29[^|]|%49[^|]|%14[^|]|%19[^\n]\n",
                  a.name, &a.age, a.gender,
                  a.doctorType, a.doctor,
                  a.date, a.time) == 7)
    {
        count++;
        printf("\nAppointment %d\n", count);
        printf("Name        : %s\n", a.name);
        printf("Age         : %d\n", a.age);
        printf("Gender      : %s\n", a.gender);
        printf("Doctor Type : %s\n", a.doctorType);
        printf("Doctor      : %s\n", a.doctor);
        printf("Date        : %s\n", a.date);
        printf("Time        : %s\n", a.time);
    }

    if (count == 0)
        printf("\nNo appointments in the file.\n");

    fclose(fp);
    system("notepad appointments.txt");
}
void searchAppointment() {
    char searchName[50];
    struct Appointment a;
    FILE *fp = fopen("appointments.txt", "r");
    int found = 0;

    if (fp == NULL) {
        printf("\nNo appointments found!\n");
        return;
    }

    printf("\nEnter patient name to search: ");
    scanf(" %[^\n]", searchName);

    while (fscanf(fp, " %49[^|]|%d|%9[^|]|%29[^|]|%49[^|]|%14[^|]|%19[^\n]\n",
                  a.name, &a.age, a.gender, a.doctorType,
                  a.doctor, a.date, a.time) == 7)
    {
        if (strcmp(a.name, searchName) == 0) {
            found = 1;
            printf("\nAppointment Found:\n");
            printf("Name        : %s\n", a.name);
            printf("Age         : %d\n", a.age);
            printf("Gender      : %s\n", a.gender);
            printf("Doctor Type : %s\n", a.doctorType);
            printf("Doctor      : %s\n", a.doctor);
            printf("Date        : %s\n", a.date);
            printf("Time        : %s\n", a.time);
        }
    }

    if (!found)
        printf("\nNo appointment found for %s.\n", searchName);

    fclose(fp);
}
void deleteAppointment() {
    char name[50];
    struct Appointment a;
    FILE *fp = fopen("appointments.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    int found = 0;

    if (fp == NULL) {
        printf("\nNo appointments found!\n");
        return;
    }

    printf("\nEnter patient name to delete: ");
    scanf(" %[^\n]", name);

    while (fscanf(fp, " %49[^|]|%d|%9[^|]|%29[^|]|%49[^|]|%14[^|]|%19[^\n]\n",
                  a.name, &a.age, a.gender, a.doctorType,
                  a.doctor, a.date, a.time) == 7)
    {
        if (strcmp(a.name, name) != 0)
            fprintf(temp, "%s|%d|%s|%s|%s|%s|%s\n",
                    a.name, a.age, a.gender,
                    a.doctorType, a.doctor,
                    a.date, a.time);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);

    remove("appointments.txt");
    rename("temp.txt", "appointments.txt");

    if (found)
        printf("\nAppointment deleted successfully!\n");
    else
        printf("\nNo appointment found for %s.\n", name);
}
void modifyAppointment() {
    char name[50];
    struct Appointment a, oldA;
    FILE *fp = fopen("appointments.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    int found = 0;

    if (fp == NULL) {
        printf("\nNo appointments found!\n");
        return;
    }

    printf("\nEnter patient name to modify: ");
    scanf(" %[^\n]", name);

    while (fscanf(fp, " %49[^|]|%d|%9[^|]|%29[^|]|%49[^|]|%14[^|]|%19[^\n]\n",
                  a.name, &a.age, a.gender,
                  a.doctorType, a.doctor,
                  a.date, a.time) == 7)
    {
        if (strcmp(a.name, name) == 0) {
            found = 1;
            oldA = a;

            printf("\n--- Current Appointment Details ---\n");
            printf("Name        : %s\n", a.name);
            printf("Age         : %d\n", a.age);
            printf("Gender      : %s\n", a.gender);
            printf("Doctor Type : %s\n", a.doctorType);
            printf("Doctor      : %s\n", a.doctor);
            printf("Date        : %s\n", a.date);
            printf("Time        : %s\n", a.time);

            printf("\n--- Enter NEW Details ---\n");
            printf("Enter Patient Name: ");
            scanf(" %[^\n]", a.name);
            printf("Enter Age: ");
            scanf("%d", &a.age);
            printf("Enter Gender: ");
            scanf(" %[^\n]", a.gender);

            selectDoctorType(a.doctorType);
            assignDoctor(a.doctorType, a.doctor);

            printf("Enter New Date (YYYY-MM-DD): ");
            scanf(" %[^\n]", a.date);
            printf("Enter New Time Slot: ");
            scanf(" %[^\n]", a.time);
            if (isSlotBooked(a.doctorType, a.date, a.time, name)) {
                printf("\nThis slot is already booked! Modification cancelled.\n");

                fprintf(temp, "%s|%d|%s|%s|%s|%s|%s\n",
                        oldA.name, oldA.age, oldA.gender,
                        oldA.doctorType, oldA.doctor,
                        oldA.date, oldA.time);
            } else {
                fprintf(temp, "%s|%d|%s|%s|%s|%s|%s\n",
                        a.name, a.age, a.gender,
                        a.doctorType, a.doctor,
                        a.date, a.time);
                printf("\nAppointment Updated Successfully!\n");
            }
        }
        else {
            fprintf(temp, "%s|%d|%s|%s|%s|%s|%s\n",
                    a.name, a.age, a.gender,
                    a.doctorType, a.doctor,
                    a.date, a.time);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("appointments.txt");
    rename("temp.txt", "appointments.txt");

    if (!found)
        printf("\nNo appointment found for %s.\n", name);
}
void countAppointments() {
    FILE *fp = fopen("appointments.txt", "r");
    struct Appointment a;
    int count = 0;

    if (fp == NULL) {
        printf("\nNo appointments found!\n");
        return;
    }

    while (fscanf(fp, " %49[^|]|%d|%9[^|]|%29[^|]|%49[^|]|%14[^|]|%19[^\n]\n",
                  a.name, &a.age, a.gender,
                  a.doctorType, a.doctor,
                  a.date, a.time) == 7)
    {
        count++;
    }

    fclose(fp);
    printf("\nTotal Appointments: %d\n", count);
}
void deleteAllAppointments() {
    if (remove("appointments.txt") == 0)
        printf("\nAll appointments deleted successfully!\n");
    else
        printf("\nNo appointments to delete.\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n==== DOCTOR'S APPOINTMENT ALLOTMENT SYSTEM ====\n");
        printf("1. Add Appointment\n");
        printf("2. View All Appointments\n");
        printf("3. Search Appointment\n");
        printf("4. Delete Appointment\n");
        printf("5. Modify Appointment\n");
        printf("6. Count Appointments\n");
        printf("7. Clear All\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

switch (choice)
{case 1:
    addAppointment();
    break;
case 2:
    viewAppointments();
    break;
case 3:
    searchAppointment();
    break;
case 4:
    deleteAppointment();
    break;
case 5:
    modifyAppointment();
    break;
case 6:
    countAppointments();
    break;
case 7:
    deleteAllAppointments();
    break;
case 8:
    printf("\nExiting Program!\n");
    return 0;
default:
    printf("\nInvalid choice! Try again.\n");
}
}
}
