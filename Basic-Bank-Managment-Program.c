#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

int i,seconds;
int main_exit = 2;
int left = 5;

//Structs
struct date{
    int month,day,year;
};

struct {

    char name[60];
    int acc_no, age;
    char address[60];
    char country_code[2];
    double phone[10]; //no country code needed
    char acc_type[10]; //may not implement
    float amt;
    struct date dob;
    struct date deposit;
    struct date withdraw;
}add,upd,check,rem,transaction;



//Functions
float interest(float t, float amount, int rate)
{
    float SI;
    SI=(rate*t*amount)/100.00;
    return (SI);
}
void menu_revert()
{
    add_invalid:
        system("cls");
        printf("\t\t\nEnter 1 to go to the Main Menu and 0 to exit: ");
        scanf("%d", &main_exit);
        if (main_exit==1)
        {
            system("cls");
            menu();
        }
        else if (main_exit==0)
        {
            system("cls");
            close();
        }
        else
        {
            printf("\nInvalid, wait 5 seconds.");
            fordelay(5);
            goto add_invalid;
        }
}
void fordelay(seconds)
{
    #ifdef _WIN32
        Sleep(1000 * seconds);
    #else
        sleep(seconds);
    #endif
}
void check_file(void)
{
    FILE *ptr;
    ptr = fopen("record.dat","a+");
    fclose(ptr);
    menu(); //maybe call main here post login
}
void new_acc()//completed
{
    system("cls");
    printf("\n\n\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 New ACCOUNT INTERFACE \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    int choice;
    FILE *ptr;
    ptr = fopen("record.dat", "a+");
    account_no:
    printf("\n\nEnter today's date (MM/DD/YYYY): "); //no error checking for now
    scanf("%d/%d/%d",&add.deposit.month,&add.deposit.day,&add.deposit.year);
    printf("\n\nEnter the account number\t(Hint: 1-10):\t");
    scanf("%d",&check.acc_no);
    while(fscanf(ptr,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",&add.acc_no,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.address,add.country_code,&add.phone,add.acc_type,&add.amt,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
    {
        if (check.acc_no==add.acc_no)
        {
            printf("Account no. already in use!");
            fordelay(5);
            goto account_no;
        }
    }
    add.acc_no=check.acc_no;
    printf("\nEnter Customer Name: ");
    scanf("%s", add.name);
    printf("\nEnter the DOB (MM/DD/YYYY): ");
    scanf("%d/%d/%d",&add.dob.month,&add.dob.day,&add.dob.year);
    printf("\nEnter age: ");
    scanf("%d",&add.age);
    printf("\nEnter address (Street address only, no city, no zip: ");
    scanf("%s",add.address);
    printf("\nEnter Country Code (ex. US): ");
    scanf("%s",add.country_code);
    printf("\nEnter Phone # (10 digits): ");
    scanf("%lf",add.phone);
    printf("\nEnter the amount to depost: $");
    scanf("%f",&add.amt);
    printf("\nType of account:\n\t#Saving\n\t#Checking\n\t#CD");
    scanf("%s",add.acc_type);

    fprintf(ptr,"%d %s %d/%d/%d %d %lf %s %s %f %s %d/%d/%d",add.acc_no, add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.phone,add.address,add.country_code,add.amt,add.acc_type,add.deposit.month,add.deposit.day,add.deposit.year);
    fclose(ptr);
    printf("\n\n\t\t\xB2\xB2\xB2\xB2 Account Created Successfully! \xB2\xB2\xB2\xB2");
    fordelay(5);
    menu_revert();
}
void edit()//completed
{
    int choice, test=0;
    FILE *old, *newrec;
    old=fopen("record.dat", "r");
    newrec=fopen("new.dat", "w");

    printf("\nEnter the account no. of the customer to edit/change: ");
    scanf("%d",&upd.acc_no);
    while (fscanf(old,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",&add.acc_no,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.address,add.country_code,&add.phone,add.acc_type,&add.amt,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
     {
         if(add.acc_no==upd.acc_no)
         {
             test=1;
             printf("\nCustomer Account found.\n");
             printf("Which information do you want to change");
             printf("\n1. Address\n2. Phone\nEnter choice (1 or 2): ");
             scanf("%d",choice);
             if(choice==1)
             {
                 printf("\n\n Enter new address:\n");
                 scanf("%s", upd.address);
                 fprintf(newrec,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,upd.address,add.country_code,add.phone,add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);
                 system("cls");
                 printf("Changes saved.");
             }
             else if(choice==0)
             {
                 printf("\nEnter new phone number: ");
                 scanf("%d", upd.phone);
                 fprintf(newrec,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,upd.address,add.country_code,add.phone,add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);
                 system("cls");
                 printf("Changes saved.");
             }
         }
         else
            fprintf(newrec,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.country_code,add.phone,add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);

     }
    fclose(old);
    fclose(newrec);
    remove("record.dat");
    rename("new.dat","record.dat");
}
void transact(void)//completed
{
    FILE *old, *newrec;
    old = fopen("record.dat", "r");
    newrec = fopen("new.dat", "w");
    system("Color 9");
    int choice,test=0;
    printf("Enter the account no. to make transactions: ");
    scanf("%d", transaction.acc_no);
    while (fscanf(old,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",&add.acc_no,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.address,add.country_code,&add.phone,add.acc_type,&add.amt,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
    {
        if(add.acc_no==transaction.acc_no)
        {   test=1;
            if(strcmpi(add.acc_type, "cd")== 0)
            {
                printf("\a\a\a\a\n\nYou can't deposit or withdraw cash in a CD. \nContact Account Management.");
                fordelay(5);
                system("cls");
                menu();
            }
            printf("Do you want to..\n1. Deposit\n2.Withdraw\n\nEnter choice (1 or 2): ");
            scanf("%d", choice);
            if(choice==1)
            {
                printf("\nEnter the amount to deposit: ");
                scanf("%f",&transaction.amt);
                add.amt += transaction.amt;
                fprintf(newrec,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.country_code,add.phone,add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);
                printf("\n\nDeposited successful");
            }
            else
            {
                printf("Enter the amount to withdraw: ");//will not check for over withdraw for now.
                scanf("%f", &transaction.amt);
                add.amt -= transaction.amt;
                fprintf(newrec,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.country_code,add.phone,add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);
                printf("\n\nWitthdraw successful");

            }
        }
        else
        {
            fprintf(newrec,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.country_code,add.phone,add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);
        }
    }
    fclose(old);
    fclose(newrec);
    remove("record.dat");
    rename("new.dat","record.dat");
    if(test!=1)
    {
        printf("\n\nRecord not found!!");
        transact_invalid:
        printf("\n\nEnter 0 to try again, 1 to return to main menu, and 2 to exit: ");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit==0)
            transact();
        else if(main_exit==1)
            menu();
        else if(main_exit==2)
            close();
        else
        {
            printf("\nInvalid");
            goto transact_invalid;
        }
    }
    else
        menu_revert();
}
void see() //-------------------------------< Continue here.
{
    FILE *old;
    int test=0, rate;
    int choice;
    float time;
    float intrst;
    system("color 9");
    old=fopen("record.dat", "r");
    printf("Record to check:\n1. Account No.\n2. Name\nEnter choice: ");
    scanf("%d", &choice);
    if(choice==1)
    {
        printf("Enter the Account No. to list: ");
        scanf("%d", &check.acc_no);
        while (fscanf(old,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",&add.acc_no,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.address,add.country_code,&add.phone,add.acc_type,&add.amt,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
        {
            if(add.acc_no==check.acc_no)
            {
                system("cls");
                test=1;
                printf("\nAccount NO.:%d\nName:%s \nDOB:%d/%d/%d \nAge:%d \nAddress:%s \nCountry Code:%s \nPhone number:%.0lf \nType Of Account:%s \nAmount deposited:$ %.2f \nDate Of Deposit:%d/%d/%d\n\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.country_code,add.phone,
                add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);
                if (strcmpi(add.acc_type, "saving"))
                {
                    time=(1.0/12.0);
                    rate=8;
                    intrst=interest(time,add.amt,rate);
                    printf("$.%.2f as interest on %d of every month", intrst, add.deposit.day);
                }
                else if (strcmpi(add.acc_type, "cd"))
                {
                    time=3.0;
                    rate=13;
                    intrst=interest(time,add.amt,rate);
                    printf("\n\n$.%.2f as interest on %d of every month", intrst,add.deposit.day);
                }
                else
                {
                    printf("\n\nNo interest is earned for this type of account.");
                }
            }
        }
    }
    else if(choice==2)
    {
        printf("Enter the Name (First and Last): "); //No entry checking done for now.
        scanf("%s",&check.name);
        while (fscanf(old,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",&add.acc_no,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.address,add.country_code,&add.phone,add.acc_type,&add.amt,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
        {
            if(add.name==check.name)
            {
                system("cls");
                test=1;
                printf("\nAccount NO.:%d\nName:%s \nDOB:%d/%d/%d \nAge:%d \nAddress:%s \nCountry Code:%s \nPhone number:%.0lf \nType Of Account:%s \nAmount deposited:$ %.2f \nDate Of Deposit:%d/%d/%d\n\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.country_code,add.phone,
                add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);
                if (strcmpi(add.acc_type, "saving"))
                {
                    time=(1.0/12.0);
                    rate=8;
                    intrst=interest(time,add.amt,rate);
                    printf("$.%.2f as interest on %d of every month", intrst, add.deposit.day);
                }
                else if (strcmpi(add.acc_type, "cd"))
                {
                    time=3.0;
                    rate=13;
                    intrst=interest(time,add.amt,rate);
                    printf("\n\n$.%.2f as interest on %d of every month", intrst,add.deposit.day);
                }
                else
                {
                    printf("\n\nNo interest is earned for this type of account.");
                }
            }
        }
    }
    fclose(old);
    if(test!=1)
    {
        system("cls");
        printf("Record not found.");
        see_invalid:
        printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit");
        scanf("%d", &main_exit);
        system("cls");
        if(main_exit==0)
            see();
        else if(main_exit==1)
            menu();
        else if(main_exit==2)
            close();
        else
        {
            system("cls");
            printf("Invalid entry");
            fordelay(5);
            goto see_invalid;
        }
    }
    else
    {
        menu_revert();
    }
}
void erase(void)//completed
{
     FILE *old, *newrec;
     int test = 0;
     old = fopen("record.dat", "r");
     newrec = fopen("new.dat", "w");
     printf("Enter the account no. of the customer to be deleted: ");
     scanf("%d", &rem.acc_no);
     while (fscanf(old,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",&add.acc_no,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.address,add.country_code,&add.phone,add.acc_type,&add.amt,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
     {
        if(add.acc_no!=rem.acc_no)
            fprintf(newrec,"%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",add.acc_no,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.address,add.country_code,add.phone,add.acc_type,add.amt,add.deposit.month,add.deposit.day,add.deposit.year);

        else
        {
            test=1;
            printf("\nRecord Deleted Successfully!\n");
        }
     }
     fclose(old);
     fclose(newrec);
     remove("record.dat");
     rename("new.dat","record.dat");
     if(test==0)
     {
         printf("\nRecord not found!!\a\a\a");
         erase_invalid:
            printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit: ");
            scanf("%d",&main_exit);
            if(main_exit==0)
                erase();
            else if(main_exit==1)
                menu();
            else if(main_exit==2)
                close();
            else
            {
                printf("\nInvalid Entry");
                goto erase_invalid;
            }
     }
     else
        menu_revert();
}
void view_list()
{
    printf("Not written yet"); //temp
}

void menu(void) //completed
{
    int choice;
    system("color 9");
    printf("\n\n\t\tCUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM");
    printf("\n\n\n\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    printf("\n\n\t\t1. Create new account");
    printf("\n\t\t2. Update existing account information");
    printf("\n\t\t3. For transactions");
    printf("\n\t\t4. View existing account details");
    printf("\n\t\t5. Remove existing account");
    printf("\n\t\t6. View account list");
    printf("\n\t\t7. Exit");
    printf("\n\n\n\n\n\t\tEnter your selection: ");
    scanf("%d", &choice);
    //need to clear screen after
    system("cls");
    switch(choice)
    {
        case 1:new_acc();
        break;
        case 2:edit();
        break;
        case 3:transact();
        break;
        case 4:see();
        break;
        case 5:erase();
        break;
        case 6:view_list();
        break;
        case 7:close();
        break;
    }
}

void time_out(void)//completed
{
    int l = 60;
    for(i=0;i<60;i++)
    {
        printf("\t\tTIMED OUT!\n\n");
        printf("\t\t%d seconds remaining..", l);
        l--;

        #ifdef _WIN32
            Sleep(1000);
        #else
            sleep(1);
        #endif // _WIN32
        system("cls");
    }
    main();
}

void close(void)//completed
{
    printf("This program was created by Daniel Clark.");
}

void login_timeout(input)
{
    int attempts = input;
    system("cls");
    printf("Warning %d attempts left.", left);
    --left;
    if (attempts > 5)
    {
       time_out();
    }
    else
    {
        login_try:
        printf("\t\t\nEnter 1 to try again and 0 to exit: ");
        scanf("%d", &main_exit);
        if (main_exit==1)
        {
            system("cls");
            main();
        }
        else if (main_exit==0)
        {
            system("cls");
            close();
        }
        else
        {
            printf("\nInvalid, wait 5 seconds.");
            fordelay(5);
            goto login_try;
        }
    }

}
int main(){
    system("color 9");
    static c=0;
    printf("\n\n\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 CUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    char pass[10], password[10] = "pythonftw";
    printf("\n\n\n\t\tThis program will create a record.dat file\n\t\tfor demonstration purposes.");
    printf("\n\n\n\n\t\tEnter Password to login: ");
    scanf("%s", pass);
    if (strncmp(pass, password, 10) == 0)
        {   system("cls");
            printf("Password Match!\n");
            printf("LOADING...");
            for(i=0;i<6;i++)
            {
                fordelay(1);
                printf(".");
            }
            system("cls");
            check_file();
            //menu(); called in check_file() TRIAL
            //return 0;
        }
    else
        {
        system("cls");
        printf("Incorrect Password\n\n");
        c++;
        login_timeout(c);
        }
    return 0;
}
