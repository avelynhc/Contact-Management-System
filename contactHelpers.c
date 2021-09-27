#define _CRT_SECURE_NO_WARNINGS
#define MAXCONTACTS 5
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "contactHelpers.h"

// Clear the standard input buffer
void clearKeyboard(void)
{
    while (getchar() != '\n'); // empty execution code block on purpose
}

// pause function definition goes here:
void pause(void)
{
    printf("(Press Enter to Continue)");
    clearKeyboard();
    printf("\n");
}

// getInt function definition goes here:
int getInt(void)
{
    int val = 0;
    char ch;
    scanf("%d%c", &val, &ch);
    //tip: for validation loop
    //you put the condition which makes the input invalid
    while (ch != '\n')
    {
        clearKeyboard();
        printf("*** INVALID INTEGER *** <Please enter an integer>: ");
        scanf("%d%c", &val, &ch);
    }
    return val;
}

// getIntInRange function definition goes here:
int getIntInRange(int min, int max)
{
    int x = 0;
    x = getInt();
    while (min > x || x > max)
    {
        printf("*** OUT OF RANGE *** <Enter a number between %d and %d>: ", min, max);
        x = getInt();
    }
    return x;
}

// yes function definition goes here:
int yes(void)
{
    int flag = 1, result = 0;
    char NL = 'x', val2;
    do
    {
        scanf("%c%c", &val2, &NL);
        if (NL == '\n')
        {
            if (val2 == 'Y' || val2 == 'y')
            {
                flag = 0;
                result = 1;
            }
            else if (val2 == 'N' || val2 == 'n')
            {
                flag = 0;
                result = 0;
            }
        }
        else if (NL != '\n')
        {
            clearKeyboard();
            printf("*** INVALID ENTRY *** <Only (Y)es or (N)o are acceptable>: ");
        }
    } while (flag);
    return result;
}

// menu function definition goes here:
int menu(void)
{
    int result = 0;

    printf("Contact Management System\n");
    printf("-------------------------\n");
    printf("1. Display contacts\n");
    printf("2. Add a contact\n");
    printf("3. Update a contact\n");
    printf("4. Delete a contact\n");
    printf("5. Search contacts by cell phone number\n");
    printf("6. Sort contacts by cell phone number\n");
    printf("0. Exit\n\n");
    printf("Select an option:> ");
    result = getIntInRange(0, 6);
    return result;
}

// contactManagerSystem function definition goes here:
void contactManagerSystem(void)
{
    struct Contact finalContact[MAXCONTACTS]=
        { { { "Rick", {'\0'}, "Grimes" },
        { 11, "Trailer Park", 0, "A7A 2J2", "King City" },
        { "4161112222", "4162223333", "4163334444" } },
        {
        { "Maggie", "R.", "Greene" },
        { 55, "Hightop House", 0, "A9A 3K3", "Bolton" },
        { "9051112222", "9052223333", "9053334444" } },
        {
        { "Morgan", "A.", "Jones" },
        { 77, "Cottage Lane", 0, "C7C 9Q9", "Peterborough" },
        { "7051112222", "7052223333", "7053334444" } },
        {
        { "Sasha", {'\0'}, "Williams" },
        { 55, "Hightop House", 0, "A9A 3K3", "Bolton" },
        { "9052223333", "9052223333", "9054445555" } },};

    int flag = 1;
    do
    {
        switch (menu())
        {
        case 1:
            displayContacts(finalContact, MAXCONTACTS);
            pause();
            break;
        case 2:
            addContact(finalContact, MAXCONTACTS);
            pause();
            break;
        case 3:
            updateContact(finalContact, MAXCONTACTS);
            pause();
            break;
        case 4:
            deleteContact(finalContact, MAXCONTACTS);
            pause();
            break;
        case 5:
            searchContacts(finalContact, MAXCONTACTS);
            pause();
            break;
        case 6:
            //printf("\n<<< Feature to sort is unavailable >>>\n\n");
            sortContacts(finalContact, MAXCONTACTS);
            pause();
            break;
        case 0:
            printf("\nExit the program? (Y)es/(N)o: ");
            if (yes()==1)
            {
                printf("\nContact Management System: terminated\n");
                flag = 0;
                break;
            }
            else 
            {
                printf("\n");
                break; 
            }
        default:
            break;
        }

    } while (flag);
}

// +-------------------------------------------------+
// |                                                 |
// |                    N E W                        |
// |           S T U F F     G O E S                 |
// |                  B E L O W                      |
// |                                                 |
// +-------------------------------------------------+
// | ====== Assignment 2 | Milestone 3 =======       |
// +-------------------------------------------------+
// | Put empty function definitions below...         |
// +-------------------------------------------------+

// Generic function to get a ten-digit phone number (ensures 10-digit chars entered)
// ---------------------------------------------------------------------------------
// NOTE: Modify this function to validate only numeric character digits are entered
// ---------------------------------------------------------------------------------

void getTenDigitPhone(char phoneNum[])
{
    int needInput = 1;
    size_t i;

    while (needInput)
    {
        scanf("%[^\n]", phoneNum);
        clearKeyboard();

        // (String Length Function: validate entry of 10 characters)
        for (i = 0; phoneNum[i] != '\0'; i++)
        {
            if (strlen(phoneNum) == 10 && isdigit(phoneNum[i]))
            {
                needInput = 0;
            }
            else
            {
                printf("Enter a 10-digit phone number: ");
                scanf("%[^\n]", phoneNum);
                clearKeyboard();
            }
        }
    }
}

// findContactIndex:
int findContactIndex(const struct Contact contacts[], int size, const char cellNum[])
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (strcmp(contacts[i].numbers.cell,cellNum)==0)
        {
            return i;
        }
    }
    return -1;
}

// displayContactHeader
// Put empty function definition below:
void displayContactHeader(void)
{
    printf("\n+-----------------------------------------------------------------------------+\n");
    printf("|                              Contacts Listing                               |\n");
    printf("+-----------------------------------------------------------------------------+\n");
}

// displayContactFooter
// Put empty function definition below:
void displayContactFooter(int count)
{
    printf("+-----------------------------------------------------------------------------+\n");
    printf("Total contacts: %d\n\n",count);
}

// displayContact:
// Put empty function definition below:
void displayContact(const struct Contact* contact)
{
    printf(" %s", (contact->name).firstName);
    if (strlen((contact->name).middleInitial) != 0)
    {
        printf(" %s %s\n", (contact->name).middleInitial, (contact->name).lastName);
    }
    else
    {
        printf(" %s\n",(contact->name).lastName);
    }
    printf("    C: %-10s   H: %-10s   B: %-10s\n", (contact->numbers).cell, (contact->numbers).home, (contact->numbers).business);
    printf("       %d %s, ", (contact->address).streetNumber,(contact->address).street);
    if (contact->address.apartmentNumber > 0)
    {
        printf("Apt# %d, ", (contact->address).apartmentNumber);
    }
    printf("%s, %s\n", (contact->address).city, (contact->address).postalCode);
}

// displayContacts:
// Put empty function definition below:
void displayContacts(const struct Contact contacts[], int size)
{
    int j, totalContacts=0;
    displayContactHeader();
    for (j = 0; j < size; j++)
    {
        if (contacts[j].numbers.cell>0 && strlen(contacts[j].numbers.cell) != 0)
        {
            displayContact(&contacts[j]);
            totalContacts++;
        }
    }
    displayContactFooter(totalContacts);
}

// searchContacts:
// Put empty function definition below:
void searchContacts(const struct Contact contacts[], int size)
{
    int index = 0;
    char phoneNum[11];
    printf("\nEnter the cell number for the contact: ");
    getTenDigitPhone(phoneNum);
    index = findContactIndex(contacts, size, phoneNum);
    if (index == -1)
    {
        printf("*** Contact NOT FOUND ***\n\n");
    }
    else
    {
        printf("\n");
        displayContact(&contacts[index]);
        printf("\n");
    }
}

// addContact:
// Put empty function definition below:
void addContact(struct Contact contacts[], int size)
{
    int i, flag =1;
    for ( i = 0; i < size && flag == 1; i++)
    {
        if (strlen(contacts[i].numbers.cell) == 0)
        {
            *contacts[i].numbers.business = '\0';
            *contacts[i].numbers.home = '\0';
            printf("\n");
            getContact(&contacts[i]);
            printf("--- New contact added! ---\n\n");
            flag = 0;
        }
        else if (i == size - 1)
        {
            printf("\n*** ERROR: The contact list is full! ***\n\n");
        }
    }
}

// updateContact:
// Put empty function definition below:
void updateContact(struct Contact contacts[], int size)
{
    int index = 0;
    char phoneNum[11];
    printf("\nEnter the cell number for the contact: ");
    getTenDigitPhone(phoneNum);
    index = findContactIndex(contacts, size, phoneNum);
    if (index == -1)
    {
        printf("*** Contact NOT FOUND ***\n\n");
    }
    else
    {
        printf("\nContact found:\n");
        displayContact(&contacts[index]);
        printf("\n");
        printf("Do you want to update the name? (y or n): ");
        if (yes()==1)
        {
            *contacts[index].name.firstName = '\0';
            *contacts[index].name.middleInitial = '\0';
            *contacts[index].name.lastName = '\0';
            getName(&contacts[index].name);
        }
        printf("Do you want to update the address? (y or n): ");
        if (yes()==1)
        {
            contacts[index].address.apartmentNumber = '\0';
            *contacts[index].address.city = '\0';
            *contacts[index].address.postalCode = '\0';
            *contacts[index].address.street = '\0';
            contacts[index].address.streetNumber = '\0';
            getAddress(&contacts[index].address);
        }
        printf("Do you want to update the numbers? (y or n): ");
        if (yes() == 1)
        {
            *contacts[index].numbers.business = '\0';
            *contacts[index].numbers.cell = '\0';
            *contacts[index].numbers.home = '\0';
            getNumbers(&contacts[index].numbers);
        }
        printf("--- Contact Updated! ---\n\n");
    }
}

// deleteContact:
// Put empty function definition below:
void deleteContact(struct Contact contacts[], int size)
{
    int index = 0;
    char phoneNum[11];
    printf("\nEnter the cell number for the contact: ");
    getTenDigitPhone(phoneNum);
    index = findContactIndex(contacts, size, phoneNum);
    if (index == -1)
    {
        printf("*** Contact NOT FOUND ***\n");
    }
    else
    {
        printf("\nContact found:\n");
        displayContact(&contacts[index]);
        printf("\n");
        printf("CONFIRM: Delete this contact? (y or n): ");
        if (yes()==1)
        {
            *contacts->numbers.cell = '\0';
            printf("--- Contact deleted! ---\n\n");
        }
        else
        {
            printf("\n");
        }
    }
}

// sortContacts:
// Put empty function definition below:
void sortContacts(struct Contact contacts[], int size)
{
    int i, j;
    struct Contact temp;

    for (i = size - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (strcmp(contacts[j].numbers.cell, contacts[j+1].numbers.cell) > 0)
            {
                temp = contacts[j];
                contacts[j] = contacts[j + 1];
                contacts[j + 1] = temp;
            }
        }
    }
    printf("\n--- Contacts sorted! ---\n\n");
}
