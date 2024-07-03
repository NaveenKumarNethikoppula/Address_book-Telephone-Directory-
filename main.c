#include"header.h"

int main()
{
    Address member;
    int choice;
    while(1)
    {
	printf("1.Add Contacts\n2.Edit\n3.Search\n4.Print\n5.Delete\n6.Exit\nEnter Your Choice :");
	scanf("%d",&choice);
	switch(choice)
	{
	    case 1:
		if(add_contacts(&member,0) == success)
		{
		    printf("-----------------------------\n");
		    printf("Contact Saved Successfully\n");
		    printf("-----------------------------\n");
		} 
		else
		{
		    printf("-----------------------------\n");
		    printf("Contact Saving Failured\n");
		    printf("-----------------------------\n");
		}
		break;
	    case 2:
		if(edit_details(&member) == success)
		{
		    printf("-----------------------------\n");
		    printf("Details Edited Successfully\n");
		    printf("-----------------------------\n");
		}
		else
		{
		    printf("-----------------------------\n");
		    printf("Dtails Edit Failured\n");
		    printf("-----------------------------\n");
		}
		break;
	    case 3:
		if(search() == success)
		{
		    printf("-----------------------------\n");
		    printf("Contact Serched Successfully\n");
		    printf("-----------------------------\n");
		}
		else
		{
		    printf("-----------------------------\n");
		    printf("Contact Searching Failured\n");
		    printf("-----------------------------\n");
		}
		break;
	    case 4:
		if(print_details() == success)
		{
		    printf("-----------------------------\n");
		    printf("Details Printed Successfully\n");
		    printf("-----------------------------\n");
		}
		else
		{
		    printf("-----------------------------\n");
		    printf("Dtails Printing Failured\n");
		    printf("-----------------------------\n");
		}
		break;
	    case 5:
		if(delete_details() == success)
		{
		    printf("-----------------------------\n");
		    printf("Delete details Successfully\n");
		    printf("-----------------------------\n");
		}
		else
		{
		    printf("-----------------------------\n");
		    printf("Delete details Failured\n");
		    printf("-----------------------------\n");
		}
		break;
	    case 6:
		return 0;
	    default :
		printf("-----------------------------\n");
		printf("Error :Enter Valid Choice\n");
		printf("-----------------------------\n");
	}
    }
    return 0;
}

