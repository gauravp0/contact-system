#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<string.h>

struct cms
{
    long number;
    char name[20] , address[200] , email[30];
} list;
FILE *fp , *ft;
char query[20] , name[20];
int i,l ,n , ch, found;

int main() {
    main:
    printf("\t\t\t\t\t** WELCOME TO CONTACT MANAGEMENT SYSTEM **\n\n");
    printf("\t\t\t\t\t\t\t MAIN MENU\n");
    {
        printf("\t");
        printf("\t\t\t\t\t==========================\n");
        printf("\t\t\t\t\t\t[1] Add a new Contact\n");
        printf("\t\t\t\t\t\t[2] List all the Contacts\n");
        printf("\t\t\t\t\t\t[3] Search for Contact\n");
        printf("\t\t\t\t\t\t[4] Edit a Contact\n");
        printf("\t\t\t\t\t\t[5] Delete a Contact\n");
        printf("\t\t\t\t\t\t[0] Exit\n");
        printf("\t");
        printf("\t\t\t\t\t==========================\n");
    }
    int n;
    printf("Enter the Choice: ");
    scanf("%d", &n);
    switch (n) {
        case 0: {
            return 0;
        }
            break;
        case 1:
            fp = fopen("contact.dll", "a");
            for (;;) {
                fflush(stdin);
                printf("To Exit press Space Bar & Enter in the Name Section\n Name : ");
                scanf("%[^\n]", &list.name);
                if (strcmp(list.name, "") == 0 || strcmp(list.name, " ") == 0)
                    break;
                fflush(stdin);
                printf("Contact No: ");
                scanf("%ld", &list.number);
                fflush(stdin);
                printf("Address: ");
                scanf("%[^\n]", &list.address);
                fflush(stdin);
                printf("E-mail : ");
                scanf("%[^\n]", &list.email);
                printf("\n");
                fwrite(&list, sizeof(list), 1, fp);
            }
            fclose(fp);
            break;
        case 2: {
            printf("\t\t\t\t\t===============================================\n");
            printf("\t\t\t\t\t");
            printf("\t\tList of all Contacts\n");
            printf("\t\t\t\t\t===============================================\n");
            printf("\n\nName");
            printf("\t\tContact No");
            printf("\t ""Address");
            printf("\t\tE-mail\n");
            printf("=================================================================\n\n");
            for (i = 97; i <= 122; i = i + 1) {
                fp = fopen("contact.dll", "r");
                fflush(stdin);
                found = 0;
                while (fread(&list, sizeof(list), 1, fp) == 1) {
                    if (list.name[0] == i || list.name[0] == i - 32) {
                        printf("\nName\t: %s\nContact No\t: %ld\nAddress\t: %s\nE-mail\t: %s\n", list.name,
                               list.number, list.address, list.email);
                        found++;
                    }
                }
                if (found != 0) {
                    printf("=========================================================== [%c]-(%d)\n\n", i - 32, found);
                    getchar();
                }
                fclose(fp);
            }
            break;
            case 3: {
                printf("\t\t\t\t\t===============================================\n");
                printf("\t\t\t\t\t");
                printf("\t\t Search for Contact\n");
                printf("\t\t\t\t\t===============================================\n");
                do {
                    found = 0;
                    printf("Name of contact to Search: ");
                    fflush(stdin);
                    scanf("%[^\n]", &query);
                    l = strlen(query);
                    fp = fopen("contact.dll", "r");
                    system("cls");
                    printf("\n\nSearch result for '%s' \n===================================================\n", query);
                    while (fread(&list, sizeof(list), 1, fp) == 1) {
                        for (i = 0; i <= l; i++)
                            name[i] = list.name[i];
                        name[l] = '\0';
                        if (strcmp(name, query) == 0) {
                            printf("\nName\t %s\nContact No \t %ld\nAddress\t %s\nE-mail\t %s\n", list.name,
                                   list.number, list.address, list.email);
                            found++;
                            if (found % 4 == 0) {
                                printf("Press any key to continue...");
                                getchar();
                            }
                        }
                    }
                    if (found == 0)
                        printf("\nNo match found!");
                    else 
                        printf("\n%d match(s) found!", found);
                    fclose(fp);
                    printf("\nTry again?\n[1] Yes\t\t[0] No\n\t");
                    scanf("%d", &ch);
                } while (ch == 1);
                break;
                case 4: {
                    printf("\t\t\t\t\t===============================================\n");
                    printf("\t\t\t\t\t");
                    printf("\t\t\t Edit a Contact\n");
                    printf("\t\t\t\t\t===============================================\n");
                    fp = fopen("contact.dll", "r");
                    ft = fopen("temp.dat", "w");
                    fflush(stdin);
                    printf("Enter the name of contact to edit:");
                    scanf("%[^\n]", name);
                    while (fread(&list, sizeof(list), 1, fp) == 1) {
                        if (strcmp(name, list.name) != 0)
                            fwrite(&list, sizeof(list), 1, ft);
                    }
                    fflush(stdin);
                    printf("\n\nEditing '%s'\n\n", name);
                    printf("Name(Use identical):");
                    scanf("%[^\n]", &list.name);
                    fflush(stdin);
                    printf("Contact No :");
                    scanf("%ld", &list.number);
                    fflush(stdin);
                    printf("Address:");
                    scanf("%[^\n]", &list.address);
                    fflush(stdin);
                    printf("E-mail :");
                    gets(list.email);
                    printf("\n");
                    fwrite(&list, sizeof(list), 1, ft);
                    fclose(fp);
                    fclose(ft);
                    remove("contact.dll");
                    rename("temp.dat", "contact.dll");
                    break;
                }
                case 5: {
                    printf("\t\t\t\t\t===============================================\n");
                    printf("\t\t\t\t\t");
                    printf("\t\t\t Delete a Contact\n");
                    printf("\t\t\t\t\t===============================================\n");
                    fflush(stdin);
                    printf("\n\n\tEnter the name of Contact to delete:");
                    scanf("%[^\n]", &name);
                    fp = fopen("contact.dll", "r");
                    ft = fopen("temp.dat", "w");
                    while (fread(&list, sizeof(list), 1, fp) != 0)
                        if (strcmp(name, list.name) != 0)
                            fwrite(&list, sizeof(list), 1, ft);
                    fclose(fp);
                    fclose(ft);
                    remove("contact.dll");
                    rename("temp.dat", "contact.dll");
                    break;
                    default:
                        printf("Invalid choice");
                    break;
                }
            }
        }
    }
    printf("\n\n\nEnter the Choice:\n\n\t[1] Main Menu\t\t[0] Exit\n");
    scanf("%d", &ch);
    switch (ch) {
        case 1:
            goto main;
        case 0:
            break;
        default:
            printf("Invalid choice");
            break;
    }
    return 0;
}
