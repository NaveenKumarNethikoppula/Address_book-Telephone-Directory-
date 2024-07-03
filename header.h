#include<stdio.h>
#include <string.h>
typedef struct   // structure for address book
{
    char name[50];
    char mob_no[11];
    char gmail[50];
    char location[50];
}Address;

typedef enum   // enum for ststus
{
  success,
  failure,
}Status;


Status add_contacts(Address* member,int num);  // fun declaration for add details
Status check(char *use_name,char *arr);  // fun for checking duplicates
void copy_to_file(Address *member);   // fun to print details to file for permanent storage
Status search();                   // fun for searching details
Status edit_details();             // fun for editing details
Status print_details();            // fun for print details
Status delete_details();           // fun for delete details
