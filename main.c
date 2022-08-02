#include <stdio.h> //this is the header file for standard input and output functions. printf(), scanf() etc are here
#include <string.h> //this is the header file for strings functions e.g strcpy(), strcat()
#include <stdlib.h> //header file for standard libraries, you need this to work with files

struct user //creating a structure using structure tag "user". Structure is a user defined data type.Different data types are grouped together.
{
    char phone[50]; //a 'phone' string variable capable of holding 49 elements,the extra room is for null character
    char acct[50]; //an 'acct' string variable capable of holding 49 elements,the extra room is for null character
    char password[50]; //a "password' string variable with indexes same as the two above
    float balance; //a variable of float data type. Fractional value is precise up to 7 digits
}; //the structure is global

int main() //main function - compilation starts from here
{
   struct user usr, usr1;
   FILE *fp; //declaring a file
   char filename[50], phone[50], pword[50]; //declaring string variables, all can hold up to 49 characters
   int opt, choice; //variables of integer data type
   char cont = 'y'; //variable of character data type. It's not a string variable
   float amount; //a variable of float data type. Fractional value is precise up to 7 digits

    printf("\nWhat do you want to do?\n"); //this, like other statements with printf() will be written on the console(output)
    printf("\n1. Register an account"); //'\n' stands for newline character
    printf("\n2. Login to an account");

    printf("\n\nYour choice:\t"); //'\t' stands for horizontal tab
    scanf("%d", &opt); //scanf() makes it possible to write in the output. It takes input from the user and assign the input to the variable
                        //'&' beside the variable name in scanf() is used to know the memory location of the variable

    if(opt == 1) //if you choose to register an account, the following happens:
    {
        system("cls"); //to clear the screen of the console
        printf("Enter your account number:\t");
        scanf("%s", usr.acct); //the account number that will be entered by the user will be stored in the acct string variable in the structure
        printf("Enter your phone number:\t"); //printf continues to writes on the until it encounters a null character and then get terminated.
        scanf("%s", usr.phone); //no need for '&' when using this scanf because the name of an array indicate the address of the first element
        printf("Enter your new password:\t"); //null character is automatically added at the end by the compiler
        scanf("%s", usr.password); //scanf stops and will not read anything else after it encounters a white space. WARNING!
        usr.balance = 0.0;
        //now, let's create a file to store the structure
        strcpy(filename, usr.phone); //the phone number inputed is copied to the 'filename' string variable we created in line 17
        fp = fopen(strcat(filename, ".dat"),"w"); //the file will be created by us writing in it. strcat() makes the file path  to be "phonenumber.dat"
        fwrite(&usr, sizeof(struct user), 1, fp); //the phone number inputed will be the name of the file, it will be a "data(dat)" file
        if(fwrite != NULL) //to check if the file has been written sucessfully
        {
            printf("\n\nAccount successfully registered");
        }
        else
        {
            printf("\n\nSomething went wrong, please try again");
        }
        fclose(fp); //closing the file
    }

    if(opt == 2) //if you choose to login an account, the following happens:
    {
        system("cls"); //to clear the screen of the console
        printf("\nPhone number:\t"); //to enter the phone number already registered
        scanf("%s", &phone); //note that the phone here is a string variable on it own, not the one in the structure. It was declared in line 17
        printf("Password:\t"); //to enter the password already registered with the phone number
        scanf("%s", &pword);//note that the password here is a string variable on it own, not the one in the structure. It was declared in line 17
        strcpy(filename,phone); //if same phone number already registered with was entered, the file would have already been created
        fp = fopen(strcat(filename, ".dat"),"r"); //if the file was already created, you can read from it, else, you won't be able to
        if(fp == NULL) //this means the phone number has not been registered
           {
               printf("\nAccount number not registered");
           }
        else //this happens if the phone number is already registered, you can read it
            {
        fread(&usr, sizeof(struct user), 1, fp);
        fclose(fp);
        if(!strcmp(pword, usr.password)) //this compares both password, the registered and the newly entered password.
        {
            while(cont == 'y') //if the passwords are the same, the loop below happens. From line 19, cont == y, the loop breaks if otherwise
            {
                system("cls"); //clears the screen
                printf("\nPress 1 for balance inquiry");
                printf("\nPress 2 for depositing cash");
                printf("\nPress 3 for cash withdrawal");
                printf("\nPress 4 for online transfer");
                printf("\nPress 5 for password change");
                printf("\n\nYour choice:\t");
                scanf("%d", &choice); //the choice entered above is inputed here

                switch(choice) //starting a switch construct
                {
                case 1: //if you chose option 1
                    printf("\nYour current balance is #%.2f", usr.balance); //remember line 39, the starting balance is 0.0
                    break; //if you encounter break, the rest of the cases will not be evaluated. If not, subsequent expression also gets evaluated
                case 2://if you chose option 2
                    printf("\nEnter the amount:\t");
                    scanf("%f", &amount); //amount is a float variable, so %f is used as the placeholder
                    usr.balance += amount; //means usr.balance = usr.balance + amount
                    fp = fopen(filename,"w"); //opening the file already registered of course
                    fwrite(&usr,sizeof(struct user),1,fp); //the balance you just updated will be written in it
                    if(fwrite != NULL) //if what you wrote was successful, else, nothing happens
                    {
                        printf("\nSuccessfully deposited #%.2f", amount);
                    }
                    fclose(fp);
                    break;
                case 3: //if you chose option 3, almost same as option 2
                    printf("\nEnter the amount:\t");
                    scanf("%f", &amount);
                    usr.balance -= amount; //the only difference with that of option 2 is the negative sign
                    fp = fopen(filename,"w");
                    fwrite(&usr,sizeof(struct user),1,fp);
                    if(fwrite != NULL)
                    {
                        printf("\nYou have withdrawn #%.2f",amount);
                    }
                    fclose(fp);
                    break;
                case 4: //if you chose option 4
                    printf("\nPlease enter the phone number you want to transfer the money to:\t"); //this phone number too has to have been registered
                    scanf("%s", &phone); //what was in the phone string variable before, the present user would have changed now to the new user you want to transfer to, remember line 59
                    printf("\nPlease enter the amount to transfer:\t");
                    scanf("%f", &amount);
                    strcpy(filename,phone); //what will be in the string variable filename will be the phone number of the user you want to transfer to
                    fp = fopen(strcat(filename,".dat"), "r"); //this phone number has to have been registered before you can read it, comment in line 115
                    if(fp == NULL) //if the phone number you want to transfer to has not been registered
                    {
                        printf("\nAccount number not registered");

                    }
                    else //the phone number you want to transfer to has to have been registered before this can happen
                    {
                        fread(&usr1,sizeof(struct user),1,fp);
                        fclose(fp);
                        if(amount > usr.balance) //true, you have to have enough before you can transfer to another
                        {
                        printf("\nInsufficient balance");
                        }
                        else //if you have enough, this happens
                        {
                       fp = fopen(filename,"w"); //opening the file of the user you want to transfer to
                       usr1.balance += amount; //notice it is usr1, not the normal usr... usr1 means the user you want to transfer to
                       fwrite(&usr1,sizeof(struct user),1,fp); //writing the new amount that the user you transferred to have now to the individual's file
                       fclose(fp); //closing the file
                        }
                        if(fwrite != NULL) //if what you have written was successful, you have to update account of the user that transferred the money
                       {
                          printf("\nYou have successfully transferred #%.2f to %s", amount, phone); //phone is still the number of the user you transferred to
                          strcpy(filename,usr.phone); //now, filename has the number of the user that transferred the money
                          fp = fopen(strcat(filename,".dat"), "w"); //opening the file of the user that transferred the money
                          usr.balance -= amount; //updating the amount in the file that the user that transferred the money has
                          fwrite(&usr,sizeof(struct user),1,fp);//writing the amount to the file
                          fclose(fp); //closing the file
                       }
                    }
                    break;
                case 5:
                    printf("\nPlease enter your new password");
                    scanf("%s", pword); //the string variable 'pword' now contains a new password
                    fp = fopen(filename,"w"); //opening the user's file
                    strcpy(usr.password,pword); //copying the new password to the 'password' string variable in the structure
                    fwrite(&usr,sizeof(struct user),1,fp); //writing it to the file
                    if(fwrite != NULL) //checking if what was written was successful
                    printf("\nPassword successfully changed");
                    fclose(fp); //closing the file
                    break;
                default: //this happens if any other option different from 1-5 was chosen
                    printf("\nInvalid option");
                } //ending of switch construct

                printf("\nDo you want to continue the transaction [y/n]\t"); //if 'y', the loop continues, if 'n' or any other, it breaks
                scanf("%s", &cont);//whatever will be chosen above is stored in 'cont' variable
                } //ending of while loop construct

            } //ending of if the passwords registered and entered are same
            else //if the passwords are different
            {
            printf("\nInvalid password");
            }
        } //ending of if the phone number is already registered and you can read it
    } //ending of if you choose to login to an already registered account
    return 0; //the main function returns 0 if it is successfully completed
    } //ending of main function
