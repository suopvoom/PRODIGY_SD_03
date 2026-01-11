#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact {
    char name[50];
    char phone[15];
    char email[50];
};

void addContact() {
    FILE *fp = fopen("contacts.txt", "a");
    struct Contact c;

    printf("Enter Name: ");
    scanf(" %[^\n]", c.name);
    printf("Enter Phone: ");
    scanf(" %s", c.phone);
    printf("Enter Email: ");
    scanf(" %s", c.email);

    fwrite(&c, sizeof(c), 1, fp);
    fclose(fp);

    printf("\nContact added successfully!\n");
}

void viewContacts() {
    FILE *fp = fopen("contacts.txt", "r");
    struct Contact c;

    if (fp == NULL) {
        printf("\nNo contacts found.\n");
        return;
    }

    printf("\n--- Contact List ---\n");
    while (fread(&c, sizeof(c), 1, fp)) {
        printf("\nName : %s", c.name);
        printf("\nPhone: %s", c.phone);
        printf("\nEmail: %s\n", c.email);
    }

    fclose(fp);
}

void deleteContact() {
    FILE *fp = fopen("contacts.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    struct Contact c;
    char name[50];
    int found = 0;

    printf("Enter name to delete: ");
    scanf(" %[^\n]", name);

    while (fread(&c, sizeof(c), 1, fp)) {
        if (strcmp(c.name, name) != 0) {
            fwrite(&c, sizeof(c), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("contacts.txt");
    rename("temp.txt", "contacts.txt");

    if (found)
        printf("\nContact deleted successfully.\n");
    else
        printf("\nContact not found.\n");
}

void editContact() {
    FILE *fp = fopen("contacts.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    struct Contact c;
    char name[50];
    int found = 0;

    printf("Enter name to edit: ");
    scanf(" %[^\n]", name);

    while (fread(&c, sizeof(c), 1, fp)) {
        if (strcmp(c.name, name) == 0) {
            found = 1;
            printf("Enter new Name: ");
            scanf(" %[^\n]", c.name);
            printf("Enter new Phone: ");
            scanf(" %s", c.phone);
            printf("Enter new Email: ");
            scanf(" %s", c.email);
        }
        fwrite(&c, sizeof(c), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("contacts.txt");
    rename("temp.txt", "contacts.txt");

    if (found)
        printf("\nContact updated successfully.\n");
    else
        printf("\nContact not found.\n");
}

int main() {
    int choice;

    do {
        printf("\n==== Contact Management System ====");
        printf("\n1. Add Contact");
        printf("\n2. View Contacts");
        printf("\n3. Edit Contact");
        printf("\n4. Delete Contact");
        printf("\n5. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addContact(); break;
            case 2: viewContacts(); break;
            case 3: editContact(); break;
            case 4: deleteContact(); break;
            case 5: printf("\nExiting...\n"); break;
            default: printf("\nInvalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}
