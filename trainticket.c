#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

/*******************************************GLOBAL VARIABLES**********************************************************/
// All the global variables and the composite data types will be declared here
typedef struct {
    char name[50];
    int train_num;
    int num_of_seats;
} pd;

/*******************************************FUNCTION PROTOTYPE**********************************************************/
// Function prototypes to be used
void reservation(void);                         // Main reservation function
void viewdetails(void);                         // View details of all the trains
void cancel(void);                              // Cancel a reservation
void printticket(char name[], int, int, float); // Print ticket 
void specifictrain(int);                        // Print data related to specific train
float charge(int, int);                         // Charge automatically w.r.t number of seats and train
void login();                                   // Login function

/******************************************FUNCTION DECLARATION**********************************************************/

/*********************************************MAIN()*************************************************/

int main() {
    system("cls"); 
    printf("\t\t=================================================\n");
    printf("\t\t|                                               |\n");
    printf("\t\t|        -----------------------------          |\n");
    printf("\t\t|           TRAIN TICKET RES. SYSTEM            |\n");
    printf("\t\t|        -----------------------------          |\n");
    printf("\t\t|                                               |\n");
    printf("\t\t|                                               |\n");
    printf("\t\t|                                               |\n");
    printf("\t\t|              BROUGHT TO YOU BY                |\n");
    printf("\t\t|           |  code-projects.org  |             |\n");
    printf("\t\t|                                               |\n");
    printf("\t\t=================================================\n\n\n");
        
    printf(" \n Press any key to continue:");
    
    getch();    
    system("cls");
    login();
    int menu_choice;
start:
    system("cls");
    printf("\n=================================\n");
    printf("    TRAIN RESERVATION SYSTEM");
    printf("\n=================================");
    printf("\n1>> Reserve A Ticket");
    printf("\n------------------------");
    printf("\n2>> View All Available Trains");
    printf("\n------------------------");
    printf("\n3>> Cancel Reservation");
    printf("\n------------------------");
    printf("\n4>> Exit");
    printf("\n------------------------");
    printf("\n\n-->");
    scanf("%d", &menu_choice);
    switch(menu_choice) {
        case 1:
            reservation();
            break;
        case 2:
            viewdetails();
            printf("\n\nPress any key to go to Main Menu..");
            getch();
            break;
        case 3:
            cancel();
            break;
        case 4:
            return 0;
        default:
            printf("\nInvalid choice");
    }
    goto start;
    return 0;
}

/****************************************** LOGIN FUNCTION *************************************************/
void login() {
    int attempts = 0;
    int i;
    char uname[10], pword[10], c;
    const char user[] = "user";
    const char pass[] = "pass";

    do {
        printf("\n  =======================  LOGIN FORM  =======================\n");
        printf(" \n                       ENTER USERNAME: ");
        scanf("%s", uname); 
        printf(" \n                       ENTER PASSWORD: ");
        i = 0;
        while (i < 10) {
            pword[i] = getch();
            c = pword[i];
            if (c == 13) break;
            else printf("*");
            i++;
        }
        pword[i] = '\0';

        if (strcmp(uname, user) == 0 && strcmp(pword, pass) == 0) {
            printf("  \n\n\n       WELCOME TO OUR SYSTEM !! YOUR LOGIN IS SUCCESSFUL");
            printf("\n\n\n\t\t\t\tPress any key to continue...");
            getch();
            break;
        } else {
            printf("\n        SORRY !!!!  LOGIN IS UNSUCCESSFUL");
            attempts++;
            getch();
            system("cls");
        }
    } while (attempts <= 2);

    if (attempts > 2) {
        printf("\nSorry you have entered the wrong username and password for three times!!!");
        getch();
        exit(0);
    }
    system("cls");
}

/****************************************** VIEW DETAILS FUNCTION *************************************************/
void viewdetails() {
    system("cls");
    printf("-----------------------------------------------------------------------------");    
    printf("\nTr.No\tName\t\t\tDestinations\t\tCharges\t\tTime\n");
    printf("-----------------------------------------------------------------------------");
    printf("\n1001\tRed Lines Express\tBoston to Manhattan\tRs.5000\t\t9am");
    printf("\n1002\tRed Lines Express\tManhattan To Boston\tRs.5000\t\t12pm");
    printf("\n1003\tLA City Express\t\tBoston To L.A\t\tRs.4500\t\t8am");
    printf("\n1004\tLA City Express\t\tL.A To Boston\t\tRs.4500\t\t11am");
    printf("\n1005\tIron City Express\tBoston To Chicago\tRs.4000\t\t7am");
    printf("\n1006\tIron City Express\tChicago To Boston\tRs.4000\t\t9.30am");
    printf("\n1007\tKeystone Express\tBoston To Washington\tRs.3500\t\t1pm");    
    printf("\n1008\tKeystone Express\tWashington To Boston\tRs.3500\t\t4pm");
    printf("\n1009\tMeteor Express\t\tBoston To Miami\t\tRs.6000\t\t3.35pm");
    printf("\n1010\tMeteor Express\t\tMiami To Boston\t\tRs.6000\t\t4.15pm");
}

/****************************************** RESERVATION FUNCTION *************************************************/
void reservation() {
    char confirm;
    float charges;
    pd passdetails;
    FILE *fp;
    fp = fopen("seats_reserved.txt", "a");
    if (fp == NULL) {
        printf("File not found");
        return;
    }
    system("cls");
    
    printf("\nEnter Your Name:> ");
    fflush(stdin);
    fgets(passdetails.name, sizeof(passdetails.name), stdin);
    passdetails.name[strcspn(passdetails.name, "\n")] = 0;  // Remove trailing newline character
    printf("\nEnter Number of seats:> ");
    scanf("%d", &passdetails.num_of_seats);
    printf("\n\n>>Press Enter To View Available Trains<< ");
    getch();
    system("cls");
    viewdetails();
    printf("\n\nEnter train number:> ");
start1:
    scanf("%d", &passdetails.train_num);
    if (passdetails.train_num >= 1001 && passdetails.train_num <= 1010) {
        charges = charge(passdetails.train_num, passdetails.num_of_seats);
        printticket(passdetails.name, passdetails.num_of_seats, passdetails.train_num, charges);        
    } else {
        printf("\nInvalid train Number! Enter again--> ");
        goto start1;
    }
    
    printf("\n\nConfirm Ticket (y/n):>");
start:
    scanf(" %c", &confirm);
    if (confirm == 'y') {
        fprintf(fp, "%s\t\t%d\t\t%d\t\t%.2f\n", passdetails.name, passdetails.num_of_seats, passdetails.train_num, charges);
        printf("==================");
        printf("\n Reservation Done\n");
        printf("==================");
        printf("\nPress any key to go back to Main menu");
    } else if (confirm == 'n') {
        printf("\nReservation Not Done!\nPress any key to go back to Main menu!");
    } else {
        printf("\nInvalid choice entered! Enter again-----> ");
        goto start;
    }
    fclose(fp);
    getch();
}

/****************************************** PRINT TICKET FUNCTION *************************************************/
void printticket(char name[], int num_of_seats, int train_num, float charges) {
    printf("\n-------------------\n");
    printf("\tTICKET\n");
    printf("-------------------\n");
    printf("Name:\t\t\t%s", name);
    printf("\nNumber of Seats:\t%d", num_of_seats);
    printf("\nTrain Number:\t\t%d", train_num);
    specifictrain(train_num);
    printf("\nCharges:\t\t%.2f", charges);
}

/****************************************** SPECIFIC TRAIN FUNCTION *************************************************/
void specifictrain(int train_num) {
    if (train_num == 1001) {
        printf("\nTrain:\t\t\tRed Lines Express");
        printf("\nDestination:\t\tBoston to Manhattan");
        printf("\nDeparture:\t\t9:00am");
    } else if (train_num == 1002) {
        printf("\nTrain:\t\t\tRed Lines Express");
        printf("\nDestination:\t\tManhattan to Boston");
        printf("\nDeparture:\t\t12:00pm");
    } else if (train_num == 1003) {
        printf("\nTrain:\t\t\tLA City Express");
        printf("\nDestination:\t\tBoston to L.A");
        printf("\nDeparture:\t\t8:00am");
    } else if (train_num == 1004) {
        printf("\nTrain:\t\t\tLA City Express");
        printf("\nDestination:\t\tL.A to Boston");
        printf("\nDeparture:\t\t11:00am");
    } else if (train_num == 1005) {
        printf("\nTrain:\t\t\tIron City Express");
        printf("\nDestination:\t\tBoston to Chicago");
        printf("\nDeparture:\t\t7:00am");
    } else if (train_num == 1006) {
        printf("\nTrain:\t\t\tIron City Express");
        printf("\nDestination:\t\tChicago to Boston");
        printf("\nDeparture:\t\t9:30am");
    } else if (train_num == 1007) {
        printf("\nTrain:\t\t\tKeystone Express");
        printf("\nDestination:\t\tBoston to Washington");
        printf("\nDeparture:\t\t1:00pm");
    } else if (train_num == 1008) {
        printf("\nTrain:\t\t\tKeystone Express");
        printf("\nDestination:\t\tWashington to Boston");
        printf("\nDeparture:\t\t4:00pm");
    } else if (train_num == 1009) {
        printf("\nTrain:\t\t\tMeteor Express");
        printf("\nDestination:\t\tBoston to Miami");
        printf("\nDeparture:\t\t3:35pm");
    } else if (train_num == 1010) {
        printf("\nTrain:\t\t\tMeteor Express");
        printf("\nDestination:\t\tMiami to Boston");
        printf("\nDeparture:\t\t4:15pm");
    }
}

/****************************************** CHARGE FUNCTION *************************************************/
float charge(int train_num, int num_of_seats) {
    if (train_num == 1001) {
        return 5000.0 * num_of_seats;
    }
    if (train_num == 1002) {
        return 5000.0 * num_of_seats;
    }
    if (train_num == 1003) {
        return 4500.0 * num_of_seats;
    }
    if (train_num == 1004) {
        return 4500.0 * num_of_seats;
    }
    if (train_num == 1005) {
        return 4000.0 * num_of_seats;
    }
    if (train_num == 1006) {
        return 4000.0 * num_of_seats;
    }
    if (train_num == 1007) {
        return 3500.0 * num_of_seats;
    }
    if (train_num == 1008) {
        return 3500.0 * num_of_seats;
    }
    if (train_num == 1009) {
        return 6000.0 * num_of_seats;
    }
    if (train_num == 1010) {
        return 6000.0 * num_of_seats;
    }
    return 0;
}

/****************************************** CANCEL FUNCTION *************************************************/
void cancel() {
    FILE *f, *t;
    int trainnum;
    int found = 0;
    pd passdetails;

    system("cls");
    printf("-----------------------\n");
    printf("Enter the train number to cancel: \n");
    printf("-----------------------\n");
    fflush(stdin);
    scanf("%d", &trainnum);

    f = fopen("seats_reserved.txt", "r");
    if (f == NULL) {
        printf("No reservations found.");
        return;
    }

    t = fopen("temp.txt", "w");
    if (t == NULL) {
        printf("Unable to open temporary file.");
        fclose(f);
        return;
    }

    while (fscanf(f, "%s\t\t%d\t\t%d", passdetails.name, &passdetails.num_of_seats, &passdetails.train_num) != EOF) {
        if (passdetails.train_num != trainnum) {
            float charges = charge(passdetails.train_num, passdetails.num_of_seats);
            fprintf(t, "%s\t\t%d\t\t%d\t\t%.2f\n", passdetails.name, passdetails.num_of_seats, passdetails.train_num, charges);
        } else {
            found = 1;
        }
    }

    fclose(f);
    fclose(t);

    remove("seats_reserved.txt");
    rename("temp.txt", "seats_reserved.txt");

    if (found) {
        printf("\nReservation Cancelled\n");
    } else {
        printf("\nNo reservation found for the given train number\n");
    }

    printf("Press any key to go back to Main Menu");
    getch();
}
