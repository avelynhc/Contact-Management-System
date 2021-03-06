#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "contacts.h"
#include "contactHelpers.h"

// getName:
void getName(struct Name* name)
{
    printf("Please enter the contact's first name: ");
    scanf("%30[^\n]%*c", name->firstName);

    printf("Do you want to enter a middle initial(s)? (y or n): ");
    //scanf("%s%*c", &yesNo); //<--- Incorrect, not a c string, must be a char

    if (yes() == 1)
    {
        printf("Please enter the contact's middle initial(s): ");
        scanf("%6[^\n]", name->middleInitial);
        clearKeyboard();
    }

    printf("Please enter the contact's last name: ");
    scanf("%35[^\n]", name->lastName);
    clearKeyboard();
}

// getAddress:
void getAddress(struct Address* address)
{
    int x, y;
    do
    {
        printf("Please enter the contact's street number: ");
        x = getInt();
        if (x < 0)
        {
            printf("*** INVALID STREET NUMBER *** <must be a positive number>: ");
            scanf("%d", &address->streetNumber);
            clearKeyboard();
        }
        else if (x > 0)
        {
            address->streetNumber = x;
        }
    } while (address->streetNumber < 1);

    printf("Please enter the contact's street name: ");
    scanf("%40[^\n]%*c", address->street);

    printf("Do you want to enter an apartment number? (y or n): ");

    if (yes() == 1)
    {
        do
        {
            printf("Please enter the contact's apartment number: ");
            y = getInt();
            //scanf("%d%*c", &address->apartmentNumber);
            if (y < 0)
            {
                printf("*** INVALID APARTMENT NUMBER *** <must be a positive number>: ");
                scanf("%d", &address->apartmentNumber);
                clearKeyboard();
            }
            else if (y > 0)
            {
                address->apartmentNumber = y;
            }
        } while (address->apartmentNumber < 1);
    }

    printf("Please enter the contact's postal code: ");
    scanf("%7[^\n]", address->postalCode);
    clearKeyboard();

    printf("Please enter the contact's city: ");
    scanf("%40[^\n]", address->city);
    clearKeyboard();
}

// getNumbers:
void getNumbers(struct Numbers* numbers)
{
    printf("Please enter the contact's cell phone number: ");
    getTenDigitPhone(numbers->cell);

    printf("Do you want to enter a home phone number? (y or n): ");
    if (yes() == 1)
    {
        printf("Please enter the contact's home phone number: ");
        getTenDigitPhone(numbers->home);
    }

    printf("Do you want to enter a business phone number? (y or n): ");
    if (yes() == 1)
    {
        printf("Please enter the contact's business phone number: ");
        getTenDigitPhone(numbers->business);
    }
}

// +-------------------------------------------+
// | ====== Assignment 2 | Milestone 1 ======= |
// +-------------------------------------------+

// getContact:
// Define Empty function definition below:
void getContact(struct Contact* contact)
{
    getName(&contact->name);
    getAddress(&contact->address);
    getNumbers(&contact->numbers);
}
