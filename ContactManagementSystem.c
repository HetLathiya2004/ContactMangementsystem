#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct contacts {
    char name[20];
    char number[15];
    char company[10];
    char gmail[40];
} info;

FILE *storeContact = NULL;
FILE *tempContact = NULL;
int countContact = 0;

void addContact() {
    system("cls");
    storeContact = fopen("contactDetails.txt", "a");
    if (storeContact == NULL) {
        printf("\nSystem Error. Try again.\n");
        return;
    }
    printf("Enter Name: ");
    fflush(stdin);
    fgets(info.name, sizeof(info.name), stdin);
    info.name[strcspn(info.name, "\n")] = '\0'; // Remove trailing newline

    printf("Enter Number: ");
    fgets(info.number, sizeof(info.number), stdin);
    info.number[strcspn(info.number, "\n")] = '\0';

    printf("Enter Company: ");
    fgets(info.company, sizeof(info.company), stdin);
    info.company[strcspn(info.company, "\n")] = '\0';

    printf("Enter Gmail: ");
    fgets(info.gmail, sizeof(info.gmail), stdin);
    info.gmail[strcspn(info.gmail, "\n")] = '\0';

    fwrite(&info, sizeof(info), 1, storeContact);
    printf("\nContact successfully added.\n");
    countContact++;
    fclose(storeContact);
}

void deleteContact() {
    system("cls");
    char number[15];
    int found = 0;

    printf("Enter Number to delete: ");
    fflush(stdin);
    fgets(number, sizeof(number), stdin);
    number[strcspn(number, "\n")] = '\0';

    storeContact = fopen("contactDetails.txt", "r");
    tempContact = fopen("tempDetails.txt", "w");

    if (storeContact == NULL || tempContact == NULL) {
        printf("\nSystem Error. Try again.\n");
        return;
    }

    while (fread(&info, sizeof(info), 1, storeContact)) {
        if (strcmp(number, info.number) == 0) {
            found = 1;
        } else {
            fwrite(&info, sizeof(info), 1, tempContact);
        }
    }

    fclose(storeContact);
    fclose(tempContact);

    if (found) {
        remove("contactDetails.txt");
        rename("tempDetails.txt", "contactDetails.txt");
        printf("\nContact successfully deleted.\n");
        countContact--;
    } else {
        remove("tempDetails.txt");
        printf("\nContact not found.\n");
    }
}

void updateContact() {
    system("cls");
    char number[15], newName[20], newNumber[15], newCompany[10], newGmail[40];
    int found = 0;

    printf("Enter Number to update: ");
    fflush(stdin);
    fgets(number, sizeof(number), stdin);
    number[strcspn(number, "\n")] = '\0';

    storeContact = fopen("contactDetails.txt", "r");
    tempContact = fopen("tempDetails.txt", "w");

    if (storeContact == NULL || tempContact == NULL) {
        printf("\nSystem Error. Try again.\n");
        return;
    }

    while (fread(&info, sizeof(info), 1, storeContact)) {
        if (strcmp(number, info.number) == 0) {
            found = 1;
            printf("Enter New Name (or press Enter to keep unchanged): ");
            fgets(newName, sizeof(newName), stdin);
            newName[strcspn(newName, "\n")] = '\0';

            printf("Enter New Number (or press Enter to keep unchanged): ");
            fgets(newNumber, sizeof(newNumber), stdin);
            newNumber[strcspn(newNumber, "\n")] = '\0';

            printf("Enter New Company (or press Enter to keep unchanged): ");
            fgets(newCompany, sizeof(newCompany), stdin);
            newCompany[strcspn(newCompany, "\n")] = '\0';

            printf("Enter New Gmail (or press Enter to keep unchanged): ");
            fgets(newGmail, sizeof(newGmail), stdin);
            newGmail[strcspn(newGmail, "\n")] = '\0';

            if (strlen(newName) > 0) strcpy(info.name, newName);
            if (strlen(newNumber) > 0) strcpy(info.number, newNumber);
            if (strlen(newCompany) > 0) strcpy(info.company, newCompany);
            if (strlen(newGmail) > 0) strcpy(info.gmail, newGmail);
        }
        fwrite(&info, sizeof(info), 1, tempContact);
    }

    fclose(storeContact);
    fclose(tempContact);

    if (found) {
        remove("contactDetails.txt");
        rename("tempDetails.txt", "contactDetails.txt");
        printf("\nContact successfully updated.\n");
    } else {
        remove("tempDetails.txt");
        printf("\nContact not found.\n");
    }
}

void searchContact() {
    system("cls");
    char number[15];
    int found = 0;

    printf("Enter Number to search: ");
    fflush(stdin);
    fgets(number, sizeof(number), stdin);
    number[strcspn(number, "\n")] = '\0';

    storeContact = fopen("contactDetails.txt", "r");
    if (storeContact == NULL) {
        printf("\nSystem Error. Try again.\n");
        return;
    }

    while (fread(&info, sizeof(info), 1, storeContact)) {
        if (strcmp(number, info.number) == 0) {
            printf("\nName: %s\nNumber: %s\nCompany: %s\nGmail: %s\n", info.name, info.number, info.company, info.gmail);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nContact not found.\n");
    }
    fclose(storeContact);
}

void viewAllContact() {
    system("cls");
    storeContact = fopen("contactDetails.txt", "r");
    if (storeContact == NULL) {
        printf("\nSystem Error. Try again.\n");
        return;
    }

    printf("\nAll Contacts:\n");
    int i = 1;
    while (fread(&info, sizeof(info), 1, storeContact)) {
        printf("%d. Name: %s, Number: %s, Company: %s, Gmail: %s\n", i++, info.name, info.number, info.company, info.gmail);
    }

    fclose(storeContact);
}

int main() {
    int choice;
    do {
        system("cls");
        printf("\nContact Management System\n");
        printf("1. Add Contact\n");
        printf("2. Delete Contact\n");
        printf("3. Update Contact\n");
        printf("4. Search Contact\n");
        printf("5. View All Contacts\n");
        printf("6. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        getchar(); // Clear newline from buffer

        switch (choice) {
        case 1:
            addContact();
            break;
        case 2:
            deleteContact();
            break;
        case 3:
            updateContact();
            break;
        case 4:
            searchContact();
            break;
        case 5:
            viewAllContact();
            break;
        case 6:
            exit(0);
        default:
            printf("\nInvalid option. Try again.\n");
        }
        printf("\nPress Enter to continue...");
        getchar();
    } while (1);

    return 0;
}
