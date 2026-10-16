#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define FILENAME "contacts_database.txt"

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

void addContact();
void viewContacts();
void searchContact();
void deleteContact();

int main() {
    int choice;

    while (1) {
        printf("\n==================================================\n");
        printf("      REAL-LIFE CONTACT MANAGEMENT SYSTEM         \n");
        printf("==================================================\n");
        printf("  1. Add New Contact\n");
        printf("  2. View All Contacts\n");
        printf("  3. Search Contact by Name\n");
        printf("  4. Delete Contact\n");
        printf("  5. Exit & Save\n");
        printf("==================================================\n");
        printf("Enter your choice (1-5): ");
        
        if (scanf("%d", &choice) != 1) {
            printf("[ERROR] Invalid input. Exiting.\n");
            break;
        }

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                viewContacts();
                break;
            case 3:
                searchContact();
                break;
            case 4:
                deleteContact();
                break;
            case 5:
                printf("\n[SAVED] Exiting program. Contacts safely stored in '%s'.\n", FILENAME);
                return 0;
            default:
                printf("\n[ERROR] Invalid choice! Please select between 1 and 5.\n");
        }
    }

    return 0;
}

// 1. Add Contact
void addContact() {
    FILE *fp = fopen(FILENAME, "a");
    if (fp == NULL) {
        printf("    [ERROR] Could not open database file!\n");
        return;
    }

    Contact c;
    printf("\n--- ADD NEW CONTACT ---\n");
    printf("    Enter Name (no spaces) : ");
    scanf("%s", c.name);
    printf("    Enter Phone Number     : ");
    scanf("%s", c.phone);
    printf("    Enter Email Address    : ");
    scanf("%s", c.email);

    fprintf(fp, "%s %s %s\n", c.name, c.phone, c.email);
    fclose(fp);
    printf("    [SUCCESS] Contact added successfully!\n");
}

// 2. View All Contacts
void viewContacts() {
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        printf("\n    [INFO] Directory is currently empty.\n");
        return;
    }

    Contact c;
    printf("\n--- CONTACT DIRECTORY ---\n");
    printf("    %-20s | %-15s | %-25s\n", "Name", "Phone", "Email");
    printf("    ------------------------------------------------------------------\n");

    while (fscanf(fp, "%s %s %s", c.name, c.phone, c.email) != EOF) {
        printf("    %-20s | %-15s | %-25s\n", c.name, c.phone, c.email);
    }
    printf("    ------------------------------------------------------------------\n");

    fclose(fp);
}

// 3. Search Contact
void searchContact() {
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        printf("\n    [INFO] Directory is empty.\n");
        return;
    }

    char target[50];
    printf("\n--- SEARCH CONTACT ---\n");
    printf("    Enter Name to search: ");
    scanf("%s", target);

    Contact c;
    bool found = false;

    while (fscanf(fp, "%s %s %s", c.name, c.phone, c.email) != EOF) {
        if (strcmp(c.name, target) == 0) {
            printf("\n    [FOUND] Contact Details:\n");
            printf("    Name  : %s\n", c.name);
            printf("    Phone : %s\n", c.phone);
            printf("    Email : %s\n", c.email);
            found = true;
            break;
        }
    }

    if (!found) {
        printf("\n    [NOT FOUND] No contact named '%s'.\n", target);
    }

    fclose(fp);
}

// 4. Delete Contact
void deleteContact() {
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        printf("\n    [INFO] Directory is empty.\n");
        return;
    }

    char target[50];
    printf("\n--- DELETE CONTACT ---\n");
    printf("    Enter Name to delete: ");
    scanf("%s", target);

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("    [ERROR] Temporary file error!\n");
        fclose(fp);
        return;
    }

    Contact c;
    bool found = false;

    while (fscanf(fp, "%s %s %s", c.name, c.phone, c.email) != EOF) {
        if (strcmp(c.name, target) == 0) {
            found = true;
        } else {
            fprintf(temp, "%s %s %s\n", c.name, c.phone, c.email);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (found) {
        printf("    [SUCCESS] Contact '%s' deleted successfully.\n", target);
    } else {
        printf("    [NOT FOUND] Contact '%s' did not exist.\n", target);
    }
}
