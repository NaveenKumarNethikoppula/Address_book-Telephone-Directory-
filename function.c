#include "header.h"

// Function to add contacts
Status add_contacts(Address* member, int num)
{
    char str[100], arr[50];
    int flag = 0;
    FILE *fptr = fopen("Address_book.txt", "r");

    // Check if file can be opened
    if (fptr == NULL)
    {
        printf("-------------------------------\n");
        printf("Error: Unable to open the file.\n");
        printf("-------------------------------\n");
        return failure;
    }

    printf("Enter Name: ");
    getchar();
    scanf("%[^\n]", arr);

    // Check if the name already exists
    while (fscanf(fptr, "%s", str) != EOF)
    {
        char *name = strtok(str, ",");
        if (check(arr, name) == failure)
        {
            flag = 1;
            break;
        }
    }

    fclose(fptr);

    if (flag == 1)
    {
        printf("-------------------------------\n");
        printf("Error: Name already exists\n");
        printf("-------------------------------\n");
        return failure;
    }

    strcpy(member->name, arr);  // Store name

    printf("Enter mobile number: ");
    scanf("%s", arr);

    // Check if mobile number is valid
    if (strlen(arr) != 10)
    {
        printf("-------------------------------\n");
        printf("Error: Mobile number not valid\n");
        printf("-------------------------------\n");
        return failure;
    }
    strcpy(member->mob_no, arr);  // Store mobile number

    printf("Enter Email ID: ");
    scanf("%s", arr);

    // Check if email ID is valid
    char *at_sign = strchr(arr, '@');
    if (at_sign == NULL || at_sign == arr)
    {
        printf("-------------------------------\n");
        printf("Error: Valid email ID required\n");
        printf("-------------------------------\n");
        return failure;
    }
    if (strstr(arr, ".com") == 0)
    {
        printf("-------------------------------\n");
        printf("Error: Email must end with .com\n");
        printf("-------------------------------\n");
        return failure;
    }
    strcpy(member->gmail, arr);  // Store email ID

    printf("Enter Location: ");
    getchar();
    scanf("%[^\n]", arr);
    strcpy(member->location, arr);  // Store location

    if (num == 0)
    {
        copy_to_file(member);  // Save to file
    }
    return success;
}

// Function to check if names match
Status check(char *user_name, char *arr)
{
    if (strcmp(user_name, arr) == 0)
    {
        return failure;
    }
    return success;
}

// Function to save contact to file
void copy_to_file(Address *member)
{
    FILE *fptr = fopen("Address_book.txt", "a");
    fseek(fptr, 0, SEEK_END);
    if (fptr != NULL)
    {
        fprintf(fptr, "%s,", member->name);
        fprintf(fptr, "%s,", member->mob_no);
        fprintf(fptr, "%s,", member->gmail);
        fprintf(fptr, "%s\n", member->location);
    }
    fclose(fptr);
}

// Function to search contacts
Status search()
{
    char arr[50], str[150];
    int option, flag = 0, error_flag = 0;
    FILE *fptr = fopen("Address_book.txt", "r");

    if (fptr == NULL)
    {
        printf("-------------------------------\n");
        printf("Error: Unable to open the file.\n");
        printf("-------------------------------\n");
        return failure;
    }

    printf("On what data You Want to Search\n1. Search by name\n2. Search by mobile number\n3. Search by Mail ID\n4. Search by Location\nEnter Your Choice: ");
    scanf("%d", &option);
    getchar(); // Clear newline character

    // Prompt for search input based on chosen option
    switch (option)
    {
        case 1:
            printf("Enter Name: ");
            scanf("%[^\n]", arr);
            break;
        case 2:
            printf("Enter Mobile Number: ");
            scanf("%s", arr);
            break;
        case 3:
            printf("Enter Mail ID: ");
            scanf("%s", arr);
            break;
        case 4:
            printf("Enter Location: ");
            scanf("%[^\n]", arr);
            break;
        default:
            printf("Invalid choice.\n");
            fclose(fptr);
            return failure;
    }

    // Search and print matching records
    while (fscanf(fptr, "%[^\n]\n", str) != EOF)
    {
        flag = 0;
        char *name = strtok(str, ",");
        char *mob_no = strtok(NULL, ",");
        char *gmail = strtok(NULL, ",");
        char *location = strtok(NULL, "\n");

        if (option == 1 && strncmp(arr, name, strlen(arr)) == 0)
        {
            flag = 1;
        }
        else if (option == 2 && strncmp(arr, mob_no, strlen(arr)) == 0)
        {
            flag = 1;
        }
        else if (option == 3 && strncmp(arr, gmail, strlen(arr)) == 0)
        {
            flag = 1;
        }
        else if (option == 4 && strncmp(arr, location, strlen(arr)) == 0)
        {
            flag = 1;
        }

        if (flag == 1)
        {
            error_flag = 1;
            printf("-------------------------------\n");
            printf("Record found\n");
            printf("Name     : %s\n", name);
            printf("Mob.No   : %s\n", mob_no);
            printf("Mail_Id  : %s\n", gmail);
            printf("Location : %s\n", location);
            printf("-------------------------------\n");
        }
    }

    // If no matching records found
    if (error_flag == 0)
    {
        printf("-------------------------------\n");
        printf("Record not found.\n");
        printf("-------------------------------\n");
        return failure;
    }
    return success;
}

// Function to print all details in address book
Status print_details()
{
    FILE *fptr = fopen("Address_book.txt", "r");
    if (fptr == NULL)
    {
        return failure;
    }

    char str[150];
    int flag = 0;

    // Read and print each line
    while (fscanf(fptr, "%[^\n]\n", str) != EOF)
    {
        flag = 1;
        char *name = strtok(str, ",");
        char *mob_no = strtok(NULL, ",");
        char *gmail = strtok(NULL, ",");
        char *location = strtok(NULL, "\n");
        printf("-------------------------------\n");
        printf("Name     : %s\n", name);
        printf("Mob.No   : %s\n", mob_no);
        printf("Mail_Id  : %s\n", gmail);
        printf("Location : %s\n", location);
        printf("-------------------------------\n");
    }

    fclose(fptr);

    // If no records found
    if (flag == 0)
    {
        return failure;
    }

    return success;
}

// Function to edit contact details
Status edit_details(Address * member)
{
    char arr[50], str[150];
    int flag = 0;
    FILE *fptr = fopen("Address_book.txt", "r");
    FILE *temp_fptr = fopen("temp.txt", "w");

    if (fptr == NULL || temp_fptr == NULL)
    {
        printf("-------------------------------\n");
        printf("Error: Unable to open the file.\n");
        printf("-------------------------------\n");
        return failure;
    }

    printf("Enter Name You want to Edit: ");
    getchar();
    scanf("%[^\n]", arr);

    while (fscanf(fptr, "%[^\n]\n", str) != EOF)
    {
        char *name = strtok(str, ",");
        char *mob_no = strtok(NULL, ",");
        char *gmail = strtok(NULL, ",");
        char *location = strtok(NULL, "\n");

        flag = 0;
        if (strcmp(arr, name) == 0)
        {
            flag = 1;
            add_contacts(member, 1);
            fprintf(temp_fptr, "%s,", member->name);
            fprintf(temp_fptr, "%s,", member->mob_no);
            fprintf(temp_fptr, "%s,", member->gmail);
            fprintf(temp_fptr, "%s\n", member->location);
        }

        if (flag == 0)
        {
            fprintf(temp_fptr, "%s,%s,%s,%s\n", name, mob_no, gmail, location);
        }
    }

    fclose(fptr);
    fclose(temp_fptr);

    // Rewrite updated data to main file
    fptr = fopen("Address_book.txt", "w");
    fseek(fptr, 0, SEEK_SET);
    temp_fptr = fopen("temp.txt", "r");
    char ch;
    while (fread(&ch, 1, 1, temp_fptr) > 0)
    {
        fwrite(&ch, 1, 1, fptr);
    }
    fclose(fptr);
    fclose(temp_fptr);

    return success;
}

// Function to delete contact details
Status delete_details()
{
    char arr[50], str[150];
    int flag = 0;
    FILE *fptr = fopen("Address_book.txt", "r");
    FILE *temp_fptr = fopen("temp.txt", "w");

    if (fptr == NULL || temp_fptr == NULL)
    {
        printf("-------------------------------\n");
        printf("Error: Unable to open the file.\n");
        printf("-------------------------------\n");
        return failure;
    }

    printf("Enter Name You want to Delete: ");
    getchar();
    scanf("%[^\n]", arr);

    while (fscanf(fptr, "%[^\n]\n", str) != EOF)
    {
        char *name = strtok(str, ",");
        char *mob_no = strtok(NULL, ",");
        char *gmail = strtok(NULL, ",");
        char *location = strtok(NULL, "\n");

        if (strcmp(arr, name) != 0)
        {
            fprintf(temp_fptr, "%s,%s,%s,%s\n", name, mob_no, gmail, location);
        }
        else
        {
            flag = 1;
        }
    }

    fclose(fptr);
    fclose(temp_fptr);

    // Rewrite updated data to main file
    fptr = fopen("Address_book.txt", "w");
    fseek(fptr, 0, SEEK_SET);
    temp_fptr = fopen("temp.txt", "r");
    char ch;
    while (fread(&ch, 1, 1, temp_fptr) > 0)
    {
        fwrite(&ch, 1, 1, fptr);
    }
    fclose(fptr);
    fclose(temp_fptr);

    // If no matching records found
    if (flag == 0)
    {
        printf("-------------------------------\n");
        printf("Error: Record not found.\n");
        printf("-------------------------------\n");
        return failure;
    }

    return success;
}

