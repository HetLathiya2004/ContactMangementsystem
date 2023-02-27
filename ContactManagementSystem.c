#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct contacts
{
    char name[20];
    char number[15];
    char company[10];
    char gmail[40];
} info;
FILE *storeContact = NULL;
FILE *tempContact = NULL;
int countContact = 0;
void addContact()
{
    system("cls");
    int check;
    storeContact = fopen("contactDetails.txt", "r");
    if (storeContact == NULL)
    {
        printf("\nSystem Error try agian\n");
        return;
    }
    if (countContact == 0)
    {
        while (fread(&info, sizeof(info), 1, storeContact) > 0)
        {
            countContact++;
        }
    }
    fclose(storeContact);
    printf("Enter Name :");
    fflush(stdin);
    gets(info.name);
    printf("Enter Number :");
    fflush(stdin);
    gets(info.number);
    printf("Enter Company :");
    fflush(stdin);
    gets(info.company);
    printf("Enter Gmail :");
    fflush(stdin);
    gets(info.gmail);
    storeContact = fopen("contactDetails.txt", "a");
    if (storeContact == NULL)
    {
        printf("System Error try agian\n");
        return;
    }
    fwrite(&info, sizeof(info), 1, storeContact);
    printf("\nContact is successfully Added\n");
    countContact++;
    fclose(storeContact);
}
void deleteContact()
{
    system("cls");
    char number[15];
    char name[20];
    int check = 0;
    printf("\nIf you want to delete contact then provide the contact infomation\n");
    printf("Enter Name :");
    fflush(stdin);
    gets(name);
    printf("Enter Number :");
    fflush(stdin);
    gets(number);
    storeContact = fopen("contactDetails.txt", "r");
    tempContact = fopen("tempDetails.txt", "a");
    if (storeContact == NULL || tempContact == NULL)
    {
        printf("\nSystem error try again\n");
        return;
    }
    while (!feof(storeContact))
    {
        fread(&info, sizeof(info), 1, storeContact);
        if (!strcmp(name, info.name) && !strcmp(number, info.number))
        {
            check = 1;
        }
    }
    if (check == 1)
    {
        rewind(storeContact);
        while (fread(&info, sizeof(info), 1, storeContact) > 0)
        {
            if (!strcmp(name, info.name) && !strcmp(number, info.number))
            {
                countContact--;
            }
            else
            {
                fwrite(&info, sizeof(info), 1, tempContact);
            }
        }
        fclose(tempContact);
        fclose(storeContact);
        remove("contactDetails.txt");
        rename("tempDetails.txt", "contactDetails.txt");
        printf("\nContact is successfully Deleted\n");
    }
    else
    {
        printf("\nContact is not found\n");
        fclose(tempContact);
        fclose(storeContact);
    }
}
void updateContact()
{
    system("cls");
    char name[20], newNumber[15], number[15], company[10], gmail[40];
    int check, choose, name2, number2, company2, gmail2;
    char ch;
    storeContact = fopen("contactDetails.txt", "r");
    if (storeContact == NULL)
    {
        printf("\nSystem Error try agian\n");
        return;
    }
    if (countContact == 0)
    {
        while (fread(&info, sizeof(info), 1, storeContact) > 0)
        {
            countContact++;
        }
    }
    rewind(storeContact);
    if (countContact == 0)
    {
        printf("\nThere is no contact\n");
        return;
    }
    printf("\nWhich contact do you want to update Enter Number :");
    fflush(stdin);
    gets(number);
    while (fread(&info, sizeof(info), 1, storeContact) > 0)
    {
        if (!strcmp(number, info.number))
        {
            check = 1;
        }
    }
    fclose(storeContact);
    if (check == 1)
    {
    again:
        printf("\nIf you want to update Name then Press 'Y' otherwise 'N'\n");
        fflush(stdin);
        scanf("%c", &ch);
        if (ch == 'Y' || ch == 'y')
        {
            printf("Enter New Name :");
            fflush(stdin);
            gets(name);
            name2 = 1;
        }
        else if (ch == 'N' || ch == 'n')
        {
        }
        else
        {
            printf("\nInvalid Key try again\n");
            goto again;
        }
    again1:
        printf("If you want to update Number then Press 'Y' otherwise 'N'\n");
        fflush(stdin);
        scanf("%c", &ch);
        if (ch == 'Y' || ch == 'y')
        {
            printf("Enter New Number :");
            fflush(stdin);
            gets(newNumber);
            number2 = 1;
        }
        else if (ch == 'N' || ch == 'n')
        {
        }
        else
        {
            printf("\nInvalid Key try again\n");
            goto again1;
        }
    again2:
        printf("If you want to update Company then Press 'Y' otherwise 'N'\n");
        fflush(stdin);
        scanf("%c", &ch);
        if (ch == 'Y' || ch == 'y')
        {
            printf("Enter New Comapay :");
            fflush(stdin);
            gets(company);
            company2 = 1;
        }
        else if (ch == 'N' || ch == 'n')
        {
        }
        else
        {
            printf("\nInvalid Key try again\n");
            goto again2;
        }
    again3:
        printf("Do you want to update G-mail then Press 'Y' otherwise 'N'\n");
        fflush(stdin);
        scanf("%c", &ch);
        if (ch == 'Y' || ch == 'y')
        {
            printf("Enter New E-mail :");
            fflush(stdin);
            gets(gmail);
            gmail2 = 1;
        }
        else if (ch == 'N' || ch == 'n')
        {
        }
        else
        {
            printf("\nInvalid Key try again\n");
            goto again1;
        }
        storeContact = fopen("contactDetails.txt", "r");
        tempContact = fopen("tempDetails.txt", "a");
        if (storeContact == NULL || tempContact == NULL)
        {
            printf("\nSystem Error try agian\n");
            return;
        }
        while (fread(&info, sizeof(info), 1, storeContact) > 0)
        {
            if (!strcmp(number, info.number))
            {
                if (name2 == 1)
                {
                    strcpy(info.name, name);
                }
                if (number2 == 1)
                {
                    strcpy(info.number, newNumber);
                }
                if (company2 == 1)
                {
                    strcpy(info.company, company);
                }
                if (gmail2 == 1)
                {
                    strcpy(info.gmail, gmail);
                }
                fwrite(&info, sizeof(info), 1, tempContact);
            }
            else
            {
                fwrite(&info, sizeof(info), 1, tempContact);
            }
        }
        fclose(storeContact);
        fclose(tempContact);
        remove("contactDetails.txt");
        rename("tempDetails.txt", "contactDetails.txt");
        printf("\nContact is successfully updated\n");
    }
    else
    {
        printf("\nContact is not found\n");
    }
}
void searchContact()
{
    system("cls");
    char number[15];
    int notFound = 0, check;
    storeContact = fopen("contactDetails.txt", "r");
    if (storeContact == NULL)
    {
        printf("\nSystem Error try agian\n");
        return;
    }
    if (countContact == 0)
    {
        while (fread(&info, sizeof(info), 1, storeContact) > 0)
        {
            countContact++;
        }
    }
    rewind(storeContact);
    if (countContact == 0)
    {
        printf("\nThere is no contact\n");
        return;
    }
    printf("Enter Number :");
    fflush(stdin);
    gets(number);
    for (int i = 1; i <= countContact; i++)
    {
        fread(&info, sizeof(info), 1, storeContact);
        if (!strcmp(number, info.number))
        {
        }
        else
        {
            notFound++;
        }
    }
    rewind(storeContact);
    if (notFound == countContact)
    {
        printf("\nContact in not found\n");
    }
    else
    {
        printf("\n");
        for (int i = 1; i <= countContact; i++)
        {
            fread(&info, sizeof(info), 1, storeContact);
            if (!strcmp(number, info.number))
            {
                printf("%d.%s\t%s\t%s\t%s\n", i, info.name, info.number, info.company, info.gmail);
            }
        }
    }
    fclose(storeContact);
}
void viewAllContact()
{
    system("cls");
    int check;
    storeContact = fopen("contactDetails.txt", "r");
    if (storeContact == NULL)
    {
        printf("\nSystem Error try agian\n");
        return;
    }
    if (countContact == 0)
    {
        while (fread(&info, sizeof(info), 1, storeContact) > 0)
        {
            countContact++;
        }
    }
    rewind(storeContact);
    if (countContact == 0)
    {
        printf("\nThere is no contact\n");
        return;
    }
    printf("\n");
    for (int i = 1; i <= countContact; i++)
    {
        fread(&info, sizeof(info), 1, storeContact);
        printf("%d.%s\t%s\t%s\t%s\n", i, info.name, info.number, info.company, info.gmail);
    }
    fclose(storeContact);
}
int main()
{
    system("cls");
    int choose;
    printf("\nWelcome to contact management system project\n");
    do
    {
        printf("\nPress 1 to Add new contact\n");
        printf("Press 2 to Delete contact\n");
        printf("Press 3 to Upadate contact\n");
        printf("Press 4 to Search contact\n");
        printf("Press 5 to View all contacts\n");
        printf("Press 6 to Exit\n");
    again:
        printf("Please choose any option: ");
        scanf("%d", &choose);
        switch (choose)
        {
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
            break;
        default:
            printf("\nInvalid option try again\n");
            goto again;
        }
  } while (1);
  return 0;
}
