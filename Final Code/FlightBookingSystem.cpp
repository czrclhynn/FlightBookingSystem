#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>

#define MAX_SEATS 40
#define MAX_FLIGHTS 100
#define MAX_BOOKINGS 100




//FUNCTION PROTOTYPES
void adminLogin();
void adminMenu();
void viewRecords();
void deleteRecords();
void addAdminAccount();
void addFlights();
void userRegister();
void userLogin();
void userMenu();
void clearScreen();
void displayAvailableFlights(int choice);
void bookFlight();
void displayRecords();
void cancelBooking();
void clearInputBuffer();
void viewUserProfile(const struct User *user);
void forgotPassword();
void viewAdminAccounts();// for the admin viewing 



int isAdminLoggedIn = 0; //number of admin logged in

//structure for booking records
struct BookingRecord {
    int bookingNumber;
    char passportNumber[20];
    char name[50];
    char flightClass[20];
    char destination[50];
    char date[20];
    char time[20];
    float price;
    int seatNumber;
};

//structure for user
struct User {
    char username[50];
    char password[50];
    char name[50];
    int age;
    char address[100];
    char gender[10];
    char securityQuestion[100];
    char securityAnswer[50];
};


struct BookingRecord bookings[MAX_BOOKINGS];
int numBookings = 0;


struct User users[100];
int numUsers = 0;
int currentUserIndex = -1; // Initialize to -1 to indicate no user is currently logged in



struct Flight {
    char destination[50];
    float economicPrice;
    float businessPrice;
    char availableDates[10][20]; // array of available dates
    int seatMap[MAX_SEATS]; // 0 means available, 1 means booked
    int numAvailableDates;
};

struct Flight domesticFlights[MAX_FLIGHTS];
int numDomesticFlights = 0;
struct Flight internationalFlights[MAX_FLIGHTS];
int numInternationalFlights = 0;


void adminLogin();
void userLogin();
void userRegister();

//function for hiding password
void getPassword(char *password) {
    char c;
    int i = 0;
    while (1) {
        c = getch();
        if (c == '\r' || c == '\n') {
            password[i] = '\0'; 
            break;
        } else if (c == '\b' && i > 0) { 
            printf("\b \b"); 
            i--;
        } else if (i < 49) { 
            password[i] = c;
            printf("*"); 
            i++;
        }
    }
}

//function for clearscreen
void clearScreen() {
    system("cls||clear");
}

//MAIN MENU FOR USER AND ADMIN
int main() {
    int choice;

    do {
    	 clearScreen();
	    // Teal and white colors
    printf("\033[1;36m__  _                                                                                                       _ .\033[0m\n");
    printf("\033[1;36m\\ `/ |                                                                                                   (  )\033[0m\n");
    printf("\033[1;36m \\__`!                                                                                         _ .      ( `  ) . )\033[0m\n");
    printf("\033[1;36m / ,' `-._________________              ____________________________________________         (  _ )_    (_, _(  ,_)_)\033[0m\n");
    printf("\033[1;36m'-\\_____     BitPair      `-.                                                                          (_  _(_ ,)\033[0m\n");
    printf("\033[1;36m   <____()-=O=O=O=O=O=[]====--)               \033[1;33mWelcome to Flight Booking System \033[0m\n");
    printf("\033[1;36m     `.___ ,-----,_______...-'                                                                         ( `    )_\033[0m\n");
    printf("\033[1;36m          /    .'                       ____________________________________________                  (         )\033[0m\n");
    printf("\033[1;36m         /   .'                                                                                      (            )\033[0m\n");
    printf("\033[1;36m        /  .'                                                                                            ____    )/\033[0m\n");
    printf("\033[1;36m        `-'                                                                                                         \033[0m\n");
    printf("\t\t\t\t\t\033[1;36m     ================================\033[0m\n");
    printf("\t\t\t\t\t\033[1;36m     ||   \033[1;33m  1. Admin Log In\033[0m   \033[1;36m     ||\033[0m\n");
    printf("\t\t\t\t\t\033[1;36m     ||   \033[1;33m  2. User Log In \033[0m    \033[1;36m    ||\033[0m\n");
    printf("\t\t\t\t\t\033[1;36m     ||   \033[1;33m  3. Register    \033[0m    \033[1;36m    ||\033[0m\n");
    printf("\t\t\t\t\t\033[1;36m     ||   \033[1;33m  4. Forgot Password \033[0m \033[1;36m   ||\033[0m\n");
    printf("\t\t\t\t\t\033[1;36m     ||   \033[1;33m  5. Exit           \033[0m \033[1;36m    ||\033[0m\n");
    printf("\t\t\t\t\t\033[1;36m     ================================\033[0m\n");
    printf("\n\t\t\t\t\t\033[0m      Enter your choice: \033[0m");
    // Input prompt with teal and white colors
   
    
    int choice;
    int result = scanf("%d", &choice);
    printf("\033[0m");  // Reset color

        if (result != 1) {
            while (getchar() != '\n');
            printf("\t\t\t\t\t\tInvalid input. Please enter a number between 1 and 5.\n");
            continue;
        }

        switch (choice) {
            case 1:
                adminLogin();
                break;
            case 2:
                userLogin();
                break;
            case 3:
                userRegister();
                break;
            case 4:
                forgotPassword();
                break;
            case 5:
                printf("\t\t\t\t   Are you sure to exit the program? (1 for Yes, 0 for No): ");
                int confirm;
                scanf("%d", &confirm);
                if (confirm) {
                    printf("\t\t\t\t\t\tExiting...\n");
                    return 0;  // Exit the program
            }
                break;
            default:
                printf("\t\t\t\tInvalid choice. Please enter a number between 1 and 5.\n");
        }
    } while (choice != 5);

    return 0;
}


#include <stdio.h>
#include <string.h>

// Function prototypes
void clearScreen();
void getPassword(char *password);
void userMenu();

//USER LOG IN
void userLogin() {
    clearScreen();
    printf("\t\t\t\t\t\033[1;36m---------------  \033[1;33mUser Log In \033[1;36m---------------\033[0m\n");
    char username[50];
    char password[50];
    int loginAttempts = 0;

    printf("\n\t\t\t\t\tEnter username: ");
    scanf("%49s", username);

    FILE *file = fopen("user_accounts.txt", "r");
    if (file != NULL) {
        int found = 0;
        while (fscanf(file, "%s %s %s %d %s %s %s", users[numUsers].username, users[numUsers].password, users[numUsers].name, &users[numUsers].age, users[numUsers].address, users[numUsers].gender, users[numUsers].securityAnswer) != EOF) {
            if (strcmp(users[numUsers].username, username) == 0) {
                found = 1;
                break;
            }
            numUsers++;
        }

        if (found) {
            fclose(file);
            while (loginAttempts < 3) {
                printf("\t\t\t\t\tEnter password: ");
                getPassword(password);

                if (strcmp(users[numUsers].password, password) == 0) {
                    printf("\n\n\t\t\t\t\tUser login successful!\n");
                    currentUserIndex = numUsers;
                    userMenu();
                    return;
                } else {
                    printf("\n\t\t\t\t\tInvalid password! Try again.\n");
                    loginAttempts++;
                }
            }

            // If the user exceeds login attempts, prompt for security question
            printf("\n\t\t\t\t\tYou've exceeded the maximum number of login attempts.\n");
            printf("\t\t\t\t\tAnswer the security question to continue.\n");
            printf("\t\t\t\t\tSecurity Question: What's your favorite color?\n");
            printf("\n\t\t\t\t\tYour Answer: ");
            char answer[50];
            scanf("%49s", answer);

            if (strcmp(users[numUsers].securityAnswer, answer) == 0) {
                printf("\n\n\t\t\t\t\t\tUser login successful!\n");
                currentUserIndex = numUsers;
                userMenu();
            } else {
                printf("\nIncorrect answer to the security question or invalid answer. Login failed.\n");
            }
        } else {
            fclose(file);
            printf("\n\t\t\t\t\tInvalid username.\n");
        }
    } else {
        printf("\n\t\t\t\t\tError accessing user accounts.\n");
    }

    printf("\t\t\t\t\tPress any key to return to Main Menu.\n");
    getchar();
    getchar();
}



//FOR USER PROFILE INFORMATION
void viewUserProfile(const struct User *user) {
    clearScreen();
    printf("\t\t\t\t\t\033[1;36m---------------  \033[1;33mUser Profile \033[1;36m---------------\033[0m\n");
    if (user == NULL) {
        printf("\t\t\t\t\tNo user profile to display.\n");
    } else {
        printf("\n\t\t\t\t\tUser Profile\n");
        printf("\t\t\t\t\tUsername: %s\n", user->username);
        printf("\t\t\t\t\tName: %s\n", user->name);
        printf("\t\t\t\t\tAge: %d\n", user->age);
        printf("\t\t\t\t\tAddress: %s\n", user->address);
        printf("\t\t\t\t\tGender: %s\n", user->gender);
    }
    printf("\n\t\t\t\t\tPress any key to return to User Menu.\n");
    getchar();
    clearInputBuffer();
}


//ADMIN LOG IN
void adminLogin() {
	    char username[50];
	    char password[50];
	
	    clearScreen();
	    printf("\t\t\t\t\t\033[1;36m---------------  \033[1;33mAdmin Log In \033[1;36m---------------\033[0m\n");
	    printf("\n\t\t\t\t\tEnter admin username: ");
	    scanf("%s", username);
	    printf("\t\t\t\t\tEnter admin password: ");
	    getPassword(password); 
	
		    if (strcmp(username, "Admin") == 0 && strcmp(password, "Admin123") == 0) {
		        printf("\n\t\t\t\t\tDefault admin login successful!\n");
		        isAdminLoggedIn = 1;
		        adminMenu();
		        return;
		    }
			printf("\n");
		    FILE *file = fopen("admin_accounts.txt", "r");
		    if (!file) {
		        perror("\n\t\t\t\t\tInvalid username or password");
		        return;
		    }
	
	    char existingUsername[50];
	    char existingPassword[50];
	    int found = 0;
		    while (fscanf(file, "%s %s", existingUsername, existingPassword) != EOF) {
		        if (strcmp(existingUsername, username) == 0 && strcmp(existingPassword, password) == 0) {
		            found = 1;
		            break;
		        }
		    }
		    fclose(file);
		
		    if (found) {
		        printf("\n\t\t\t\t\tAdmin login successful!\n");
		        isAdminLoggedIn = 1;
		        adminMenu();
		    } else {
		        printf("\n\t\t\t\t\tInvalid username or password!\n");
		    }
	
	    printf("\n\t\t\t\t\tPress any key to return to Main Menu.\n");
	    getchar();
	    getchar();
}


void adminMenu() {
    if (!isAdminLoggedIn) {
        printf("\n\t\t\t\t\tYou need to log in as admin first.\n");
        return;
    }

    int choice;

    do {
        clearScreen();
        printf("\n");
        printf("\t\t\t\t\t\t\033[1;36m+--------------------------+\033[0m\n");
        printf("\t\t\t\t\t\t\033[1;36m|        \033[1;33mAdmin Menu\033[1;36m        |\033[0m\n");
        printf("\t\t\t\t\t\t\033[1;36m+--------------------------+\033[0m\n");
        printf("\t\t\t\t\t\t\033[1;36m| \033[1;33m1. View Records\033[1;36m          |\033[0m\n");
        printf("\t\t\t\t\t\t\033[1;36m| \033[1;33m2. Cancel User Booking\033[1;36m   |\033[0m\n");
        printf("\t\t\t\t\t\t\033[1;36m| \033[1;33m3. Create Admin Account\033[1;36m  |\033[0m\n");// pinagtabi kona sila
        printf("\t\t\t\t\t\t\033[1;36m| \033[1;33m4. View Admin Accounts\033[1;36m   |\033[0m\n");// para ano siya hindi magulo hanapin
        printf("\t\t\t\t\t\t\033[1;36m| \033[1;33m5. Add Available Flights\033[1;36m |\033[0m\n");
        printf("\t\t\t\t\t\t\033[1;36m| \033[1;33m6. View Created Flights\033[1;36m  |\033[0m\n");
        printf("\t\t\t\t\t\t\033[1;36m| \033[1;33m7. Log out\033[1;36m               |\033[0m\n");
        printf("\t\t\t\t\t\t\033[1;36m+--------------------------+\033[0m\n");
        printf("\n\t\t\t\t\t\tEnter your choice: ");
        
        int result = scanf("%d", &choice);

        if (result != 1) {
            while (getchar() != '\n');
            printf("\t\t\t\t\t\tInvalid input. Please enter a number between 1 and 7.\n");
            continue;
        }

        switch (choice) {
            case 1:
                viewRecords();
                break;
            case 2:
                deleteRecords();
                break;
            case 3:
                addAdminAccount();
                break;
            case 4:
                viewAdminAccounts();
                break;
            case 5:
                addFlights();
                break;
            case 6:
                int flightChoice;
                do {
                    clearScreen();
                    printf("\t\t\t\t\t\033[1;36m---------------  \033[1;33mAvailable Flights \033[1;36m---------------\033[0m\n");
                    printf("\t\t\t\t\t1. Domestic Flights\n");
                    printf("\t\t\t\t\t2. International Flights\n");
                    printf("\t\t\t\t\t3. Return to Menu\n");
                    printf("\n\t\t\t\t\tEnter your choice: ");
                    result = scanf("%d", &flightChoice);

                    if (result != 1 || (flightChoice != 1 && flightChoice != 2 && flightChoice != 3)) {
                        while (getchar() != '\n');
                        printf("Invalid input. Please enter 1 for Domestic Flights, 2 for International Flights, or 3 to Return to Menu.\n");
                    }
                } while (flightChoice != 1 && flightChoice != 2 && flightChoice != 3);

                if (flightChoice != 3) {
                    displayAvailableFlights(flightChoice);
                }
                break;
            case 7:
                printf("\t\t\t\t\tAre you sure to logout admin account? (1 for Yes, 0 for No): ");
                int confirm;
                scanf("%d", &confirm);
                if (confirm == 1) {
                    printf("\t\t\t\t\tLogging Out Admin Menu...\n");
                    isAdminLoggedIn = 0;
                }
                break;
            default:
                printf("\t\t\t\t\tInvalid choice. Please enter a number between 1 and 7.\n");
        }
    } while (choice != 7);
}




void viewRecords() {
	    clearScreen();
	    printf("\t\t\t\t\t\033[1;36m---------------  \033[1;33mBooking Records \033[1;36m---------------\033[0m\n");
	    if (numBookings == 0) {
	        printf("\n\t\t\t\t\tNo Bookings Record.\n");
	    } else {
	        
	        int i;
	        for (i = 0; i < numBookings; i++) {
	            printf("\n\t\t\t\t\tBooking %d\n", bookings[i].bookingNumber);
	            printf("\t\t\t\t\tPassport Number: %s\n", bookings[i].passportNumber);
	            printf("\t\t\t\t\tName: %s\n", bookings[i].name);
	            printf("\t\t\t\t\tFlight Class: %s\n", bookings[i].flightClass);
	            printf("\t\t\t\t\tDestination: %s\n", bookings[i].destination);
	            printf("\t\t\t\t\tTime: %s\n", bookings[i].time);
	            printf("\t\t\t\t\tPrice: %.2f\n", bookings[i].price);
	            printf("\n");
	        }
	    }
	    printf("\n\t\t\t\t\t\tPress any key to return to Admin Menu.\n");
	    getchar();
	    getchar();
	}
	
	//CANCEL USER BOOKING
	void deleteRecords() {
	    clearScreen();
	    printf("\t\t\t\t\t\033[1;36m---------------  \033[1;33mCancel User Booking \033[1;36m---------------\033[0m\n");
	    if (numBookings == 0) {
	        printf("\n\t\t\t\t\tNo bookings to cancel.\n");
	        printf("\n\t\t\t\t\tPress any key to return to Admin Menu.\n");
	        getchar();
	        getchar();
	        return;
	    }
	
	    int bookingNumber;
	    
	    printf("\n\t\t\t\t\tEnter Booking Number to Cancel: ");
	    scanf("%d", &bookingNumber);
	
	    int found = 0;
	    int i;
	    for (i = 0; i < numBookings; i++) {
	        if (bookings[i].bookingNumber == bookingNumber) {
	            found = 1;
	            char confirmation;
	            printf("\t\t\t\t\tAre you sure you want to cancel booking %d? (y/n): ", bookingNumber);
	            getchar(); // Clear buffer
	            scanf("%c", &confirmation);
	            if (confirmation == 'y' || confirmation == 'Y') {
	                int j;
	                for (j = i; j < numBookings - 1; j++) {
	                    bookings[j] = bookings[j + 1];
	                }
	                numBookings--;
	                printf("\t\t\t\t\tBooking %d cancelled successfully.\n", bookingNumber);
	            } else {
	                printf("\t\t\t\t\tBooking cancellation aborted.\n");
	            }
	            break;
	        }
	    }
	
	    if (!found) {
	        printf("\t\t\t\t\tInvalid booking number.\n");
	    }
	
	    printf("\t\t\t\t\tPress any key to return to Admin Menu.\n");
	    getchar();
	    getchar();
}

//ADDING ADMIN ACCOUNT
void addAdminAccount() {
		 clearScreen();
		 printf("\t\t\t\t\t\033[1;36m---------------  \033[1;33mAdd Admin Account \033[1;36m---------------\033[0m\n");
	    char username[50];
	    char password[50];
	    char existingUsername[50];
	    char existingPassword[50];
	
	    printf("\n\t\t\t\t\tEnter admin username: ");
	    scanf("%s", username);
	
	    FILE *file = fopen("admin_accounts.txt", "r");
	    if (file != NULL) {
	        while (fscanf(file, "%s %s", existingUsername, existingPassword) != EOF) {
	            if (strcmp(existingUsername, username) == 0) {
	                printf("\n\t\t\t\t\tAccount already exists.\n");
	                fclose(file);
	                printf("\n\t\t\t\t\tPress any key to return to Admin Menu.\n");
	                getchar();
	                getchar();
	                return;
	            }
	        }
	        fclose(file);
	    } else {
	        
	        file = fopen("admin_accounts.txt", "a");
	        if (file == NULL) {
	            perror("\t\t\t\t\tError opening admin accounts file");
	            return;
	        }
	        fclose(file);
	    }
	
	    printf("\t\t\t\t\tEnter admin password: ");
	    scanf("%s", password);
	
	    
	    file = fopen("admin_accounts.txt", "a");
	    if (!file) {
	        perror("\t\t\t\t\tError adding admin account");
	        return;
	    }
	
	    fprintf(file, "%s %s\n", username, password);
	    fclose(file);
	    printf("\t\t\t\t\tAdmin account added successfully!\n");
	    printf("\t\t\t\t\tPress any key to return to Admin Menu.\n");
	    getchar();
	    getchar();
}

//VIEW ADMIN ACCOUNTS
void viewAdminAccounts() {
    clearScreen();
    printf("\t\t\t\t\t\033[1;36m---------------  \033[1;33mAdmin Accounts \033[1;36m---------------\033[0m\n");

    // Print the default admin account
    printf("\n\t\t\t\t\tAdmin Account 1\n");
    printf("\t\t\t\t\tUsername: admin\n");
    

    FILE *file = fopen("admin_accounts.txt", "r");//file handling
    if (!file) {
        perror("\n\t\t\t\t\tError opening admin accounts file.");
        return;
    }

    char username[50];
    char password[50];
    int accountNumber = 2; // Start from 2 kasi nga may default acc sha

    while (fscanf(file, "%s %s", username, password) != EOF) {
        printf("\n\t\t\t\t\tAdmin Account %d\n", accountNumber++);
        printf("\t\t\t\t\tUsername: %s\n", username);
        // pwede ka rin naman mag print here ng pass niya if ever gusto mo but i advice not to for security purpuses nya
        // printf("\t\t\t\t\tPassword: %s\n", password); - like that hhaahha
    }

    fclose(file);

    if (accountNumber == 2) {
        printf("\n\t\t\t\t\tNo additional admin accounts found.\n");
    }

    printf("\n\t\t\t\t\t\tPress any key to return to Admin Menu.\n");
    getchar();
    getchar();
}



//DISPLAY SEAT MAP
void displayAvailableSeats(int *seatMap) {
	printf("\t\t\t\t\t\033[1;36m**************  \033[1;32mSelect Seat \033[1;36m***************\033[0m\n");
    printf("\n\t\t\t\t\tSeat Map (0 means available, 1 means booked):\n");
    printf("\t\t\t\t\t\t");
    for (int i = 0; i < MAX_SEATS; i++) {
        printf("%d ", seatMap[i]);
        if ((i + 1) % 10 == 0) {
            if ((i + 1) == 20) {
                printf("\n\n\t\t\t\t\t\t");
            } else {
                printf("\n\t\t\t\t\t\t");
            }
        }
    }
    
}

//ADDING AVAILABLE FLIGHT
void addFlights() {
	    clearScreen();
	    printf("\t\t\t\t\t\033[1;36m---------------  \033[1;33mAdd Flight \033[1;36m---------------\033[0m\n");
	    int choice;
	    int validInput = 0;
	
	    do {
	        printf("\n\t\t\t\t\t1. Domestic Flight\n");
	        printf("\t\t\t\t\t2. International Flight\n");
	        printf("\t\t\t\t\t3. Return to Menu\n");
	        printf("\n\t\t\t\t\tChoice: ");
	        int result = scanf("%d", &choice);
			
			
	        if (result != 1) {
	            while (getchar() != '\n');
	            printf("\t\t\t\t\tInvalid input. Please enter a number (1, 2, or 3).\n");
	            continue;
	        }
	
	        if (choice == 1 || choice == 2 || choice == 3) {
	            validInput = 1;
	            if (choice == 1){
				printf("\n\t\t\t\t\tAdd Domestic Flight:\n");
				} else if (choice == 2){
					printf("\n\t\t\t\t\tAdd International Fliht:\n");
				} else if (choice == 3) {
		                return; // Return to menu
		            }
	        } else {
	            printf("\t\t\t\t\tInvalid choice. Please enter 1 for Domestic Flight, 2 for International Flight, or 3 to Return to Menu.\n");
	        }
	    } while (!validInput);
	
	    char destination[50];
	    float economicPrice, businessPrice;
	    int numAvailableDates;
	    char availableDates[10][20]; // array of available dates
	
	    printf("\n\t\t\t\t\tDestination (From > To): ");
	    scanf(" %[^\n]", destination);
	
	    do {
	        printf("\t\t\t\t\tEconomic Class Price: ");
	        int result = scanf("%f", &economicPrice);
	
	        if (result == 1 && economicPrice >= 0) {
	            validInput = 1;
	        } else {
	            validInput = 0;
	            printf("\n\t\t\t\tInvalid price. Please enter a valid positive number for Economic Class Price.\n");
	            while (getchar() != '\n');
	        }
	    } while (!validInput);
	
	    do {
	        printf("\t\t\t\t\tBusiness Class Price: ");
	        int result = scanf("%f", &businessPrice);
	
	        if (result == 1 && businessPrice >= 0) {
	            validInput = 1;
	        } else {
	            validInput = 0;
	            printf("\n\t\t\t\tInvalid price. Please enter a valid positive number for Business Class Price.\n");
	            while (getchar() != '\n');
	        }
	    } while (!validInput);
	
	    do {
	        printf("\t\t\t\t\tEnter number of available dates: ");
	        int result = scanf("%d", &numAvailableDates);
	
	        if (result == 1 && numAvailableDates > 0 && numAvailableDates <= 10) {
	            validInput = 1;
	        } else {
	            validInput = 0;
	            printf("\n\t\t\t\t\tInvalid number of dates. Please enter a number between 1 and 10.\n");
	            while (getchar() != '\n');
	        }
	    } while (!validInput);
	
	    for (int i = 0; i < numAvailableDates; i++) {
	        printf("\t\t\t\t\tEnter available date %d [MM/DD/YY]: ", i + 1);
	        scanf("%s", availableDates[i]);
	    }
	
	    struct Flight newFlight;
	    strcpy(newFlight.destination, destination);
	    newFlight.economicPrice = economicPrice;
	    newFlight.businessPrice = businessPrice;
	    newFlight.numAvailableDates = numAvailableDates;
	    for (int i = 0; i < numAvailableDates; i++) {
	        strcpy(newFlight.availableDates[i], availableDates[i]);
	    }
	    for (int i = 0; i < MAX_SEATS; i++) {
	        newFlight.seatMap[i] = 0; // Initialize all seats to available
	    }
	
	    if (choice == 1) {
	        domesticFlights[numDomesticFlights] = newFlight;
	        numDomesticFlights++;
	    } else {
	        internationalFlights[numInternationalFlights] = newFlight;
	        numInternationalFlights++;
	    }
	
	    printf("\n\t\t\t\t\tFlight added successfully!\n");
	    printf("\n\t\t\t\t\tPress any key to return to Admin Menu.\n");
	    getchar();
	    getchar();
}


//USER REGISTRATION
void userRegister() {
    clearScreen();
    printf("\t\t\t\t\t\033[1;36m---------------  \033[1;33mUser Register \033[1;36m---------------\033[0m\n");
    struct User newUser;

    printf("\n\t\t\t\t\tEnter username: ");
    scanf("%49s", newUser.username);  // Limit input to 49 characters

    FILE *file = fopen("user_accounts.txt", "r");
    if (file != NULL) {
        struct User existingUser;
        while (fscanf(file, "%s %s %s %d %s %s %s %s", existingUser.username, existingUser.password, existingUser.name, &existingUser.age, existingUser.address, existingUser.gender, existingUser.securityAnswer) != EOF) {
            if (strcmp(existingUser.username, newUser.username) == 0) {
                printf("\n\t\t\t\t\tUsername already exists.\n");
                fclose(file);
                printf("\n\t\t\t\t\tPress any key to return to Main Menu.\n");
                getchar();
                getchar();
                return;
            }
        }
        fclose(file);
    }

    printf("\t\t\t\t\tEnter password: ");
    getPassword(newUser.password);

    printf("\n\n\t\t\t\t\tEnter your name: ");
    scanf("%49s", newUser.name);  // Limit input to 49 characters
    printf("\t\t\t\t\tEnter your age: ");
    scanf("%d", &newUser.age);
    printf("\t\t\t\t\tEnter your address: ");
    scanf("%49s", newUser.address);  // Limit input to 49 characters
    printf("\t\t\t\t\tEnter your gender: ");
    scanf("%49s", newUser.gender);  // Limit input to 49 characters

    strcpy(newUser.securityQuestion, "What's your favorite color?");
    printf("\n\t\t\t\t\tSecurity Question: %s\n", newUser.securityQuestion);
    printf("\t\t\t\t\tEnter answer for the security question: ");
    scanf("%49s", newUser.securityAnswer);  // Limit input to 49 characters

    file = fopen("user_accounts.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s %s %s %d %s %s %s\n", newUser.username, newUser.password, newUser.name, newUser.age, newUser.address, newUser.gender, newUser.securityAnswer);
        fclose(file);
        printf("\n\t\t\t\t\tUser registered successfully!\n");
    } else {
        printf("\n\n\t\t\t\t\tError registering user.\n");
    }

    printf("\n\t\t\t\t\tPress any key to return to Main Menu.\n");
    getchar();
    getchar();
}



//ACCOUNT RETRIEVAL FOR USER
void forgotPassword() {
    clearScreen();
    printf("\t\t\t\t\t\033[1;36m---------------  \033[1;33mForgot Password \033[1;36m---------------\033[0m\n");

    char username[50];
    printf("\n\t\t\t\t\tEnter your username: ");
    scanf("%49s", username);  // Limit input to 49 characters

    FILE *file = fopen("user_accounts.txt", "r");
    FILE *tempFile = fopen("temp_user_accounts.txt", "w");
    if (file != NULL && tempFile != NULL) {
        struct User currentUser;
        int found = 0;
        while (fscanf(file, "%s %s %s %d %s %s %s", currentUser.username, currentUser.password, currentUser.name, &currentUser.age, currentUser.address, currentUser.gender, currentUser.securityAnswer) != EOF) {
            if (strcmp(currentUser.username, username) == 0) {
                found = 1;
                printf("\n\t\t\t\t\tSecurity Question: What is your favorite color?\n");

                char answer[50];
                printf("\t\t\t\t\tProvide the answer to the security question: ");
                scanf("%49s", answer);  // Limit input to 49 characters

                if (strcmp(currentUser.securityAnswer, answer) == 0) {
                    printf("\n\t\t\t\t\tSecurity answer matched!\n");
                    printf("\t\t\t\t\tEnter new password: ");
                    getPassword(currentUser.password);  // Update password
                } else {
                    printf("\n\t\t\t\t\tIncorrect answer to security question.\n");
                }
            }
            fprintf(tempFile, "%s %s %s %d %s %s %s\n", currentUser.username, currentUser.password, currentUser.name, currentUser.age, currentUser.address, currentUser.gender, currentUser.securityAnswer);
        }
        fclose(file);
        fclose(tempFile);

        remove("user_accounts.txt");
        rename("temp_user_accounts.txt", "user_accounts.txt");

        if (found) {
            printf("\n\t\t\t\t\tPassword changed successfully!\n");
        } else {
            printf("\n\t\t\t\t\tUsername not found.\n");
        }
    } else {
        printf("\n\t\t\t\t\tError accessing user data.\n");
    }

    printf("\n\t\t\t\t\tPress any key to return to Main Menu.\n");
    getchar();
    getchar();
}




//USER MENU
void userMenu() {
    int choice;

    do {
        clearScreen();
        printf("\n");
	    printf("\t\t\t\t\t\t\033[1;36m\033[5m+------------------------------+\033[0m\n");
	    printf("\t\t\t\t\t\t\033[1;36m\033[5m|         \033[1;33mUser Menu\033[1;36m\033[5m            |\033[0m\n");
	    printf("\t\t\t\t\t\t\033[1;36m\033[5m+------------------------------+\033[0m\n");
	    printf("\t\t\t\t\t\t\033[1;36m\033[5m| \033[1;33m1. Display Available Flights\033[1;36m\033[5m |\033[0m\n");
	    printf("\t\t\t\t\t\t\033[1;36m\033[5m| \033[1;33m2. Book Flight\033[1;36m\033[5m               |\033[0m\n");
	    printf("\t\t\t\t\t\t\033[1;36m\033[5m| \033[1;33m3. View Booking Records\033[1;36m\033[5m      |\033[0m\n");
	    printf("\t\t\t\t\t\t\033[1;36m\033[5m| \033[1;33m4. Cancel Booking\033[1;36m\033[5m            |\033[0m\n");
	    printf("\t\t\t\t\t\t\033[1;36m\033[5m| \033[1;33m5. View Profile\033[1;36m\033[5m              |\033[0m\n");
	    printf("\t\t\t\t\t\t\033[1;36m\033[5m| \033[1;33m6. Log Out\033[1;36m\033[5m                   |\033[0m\n");
	    printf("\t\t\t\t\t\t\033[1;36m\033[5m+------------------------------+\033[0m\n");
	    printf("\n\t\t\t\t\t\tEnter your choice: ");
        int result = scanf("%d", &choice);

        if (result != 1) {
            while (getchar() != '\n');
            printf("\t\t\t\t\t\tInvalid input. Please enter a number between 1 and 6.\n");
            continue;
        }

        switch (choice) {
            case 1: {
                int flightChoice;
                do {
                	clearScreen();
                	printf("\t\t\t\t\t\033[1;36m---------------  \033[1;33mAvailable Flights \033[1;36m---------------\033[0m\n\n");
                    printf("\t\t\t\t\t1. Domestic Flights\n");
                    printf("\t\t\t\t\t2. International Flights\n");
                    printf("\t\t\t\t\t3. Return to Menu\n");
                    printf("\n\t\t\t\t\tEnter your choice: ");
                    result = scanf("%d", &flightChoice);

                    if (result != 1 || (flightChoice != 1 && flightChoice != 2 && flightChoice != 3)) {
                        while (getchar() != '\n');
                        printf("Invalid input. Please enter 1 for Domestic Flights, 2 for International Flights, or 3 to Return to Menu.\n");
                    }
                } while (flightChoice != 1 && flightChoice != 2 && flightChoice != 3);

                if (flightChoice != 3) {
                    displayAvailableFlights(flightChoice);
                }
                break;
            }
            case 2:
                bookFlight();
                break;
            case 3:
                displayRecords();
                break;
            case 4:
                cancelBooking();
                break;
            case 5:
                viewUserProfile(&users[currentUserIndex]);
                break;
            case 6:
            	printf("\t\t\t\t  Are you sure to log out account? (1 for Yes, 0 for No): ");
                int confirm;
                scanf("%d", &confirm);
                if (confirm == 1) {
                printf("\n\t\t\t\t\tLogging Out User Menu...\n");
            } else {
            	userMenu();
			}
                break;
            default:
                printf("\t\t\t\t\tInvalid choice. Please enter a number between 1 and 6.\n");
        }
    } while (choice != 6);
}


//DISPLAYING AVAILABLE FLIGHTS CREATED BY ADMIN
void displayAvailableFlights(int choice) {
    clearScreen();
    printf("\t\t\t\t\t\033[1;36m---------------  \033[1;33mAvailable Flights \033[1;36m---------------\033[0m\n\n");
    if (choice == 1) {
        if (numDomesticFlights == 0) {
            printf("\n\t\t\t\t\tNo available domestic flights.\n");
        } else {
            
            for (int i = 0; i < numDomesticFlights; i++) {
                printf("\t\t\t\t\tDestination: %s\n", domesticFlights[i].destination);
                printf("\t\t\t\t\tEconomic Class Price: %.2f\n", domesticFlights[i].economicPrice);
                printf("\t\t\t\t\tBusiness Class Price: %.2f\n", domesticFlights[i].businessPrice);
                printf("\t\t\t\t\tAvailable Dates: ");
                for (int j = 0; j < domesticFlights[i].numAvailableDates; j++) {
                    printf("%s ", domesticFlights[i].availableDates[j]);
                }
                printf("\n\n");
            }
        }
    } else if (choice == 2) {
        if (numInternationalFlights == 0) {
            printf("\t\t\t\t\tNo available international flights.\n");
        } else {
            printf("\n\t\t\t\t\tAvailable International Flights:\n");
            for (int i = 0; i < numInternationalFlights; i++) {
                printf("\t\t\t\t\tDestination: %s\n", internationalFlights[i].destination);
                printf("\t\t\t\t\tEconomic Class Price: %.2f\n", internationalFlights[i].economicPrice);
                printf("\t\t\t\t\tBusiness Class Price: %.2f\n", internationalFlights[i].businessPrice);
                printf("\t\t\t\t\tAvailable Dates: ");
                for (int j = 0; j < internationalFlights[i].numAvailableDates; j++) {
                    printf("%s ", internationalFlights[i].availableDates[j]);
                }
                printf("\n\n");
            }
        }
    } else {
        printf("\t\t\t\t\tInvalid choice.\n");
    }
    printf("\t\t\t\t\tPress any key to return to Menu.\n");
    getchar();
    clearInputBuffer();
}


void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { //CLEAR INPUT BUFFER
        
    }
}

//USER BOOKING FLIGHT
void bookFlight() {
    clearScreen();
    printf("\t\t\t\t\t\033[1;36m---------------  \033[1;33mBOOK FLIGHT \033[1;36m---------------\033[0m\n\n");
    struct BookingRecord booking;
    int flightChoice;
    int validInput;
    int paymentChoice;

    do {
        printf("\t\t\t\t\tChoose Flight:\n");
        printf("\t\t\t\t\t1. Domestic Flight (Local Flight)\n");
        printf("\t\t\t\t\t2. International Flight\n");
        printf("\t\t\t\t\t3. Return to Menu\n");
        printf("\t\t\t\t\tEnter your choice: ");
        if (scanf("%d", &flightChoice) != 1) {
            printf("\t\t\t\t\t\tInvalid choice. Please try again.\n");
            clearInputBuffer();
            validInput = 0;
        } else if (flightChoice == 1 || flightChoice == 2 || flightChoice == 3) {
            validInput = 1;
            if (flightChoice == 3) {
                return; // Return to menu
            }
        } else {
            printf("\t\t\t\t\t\tInvalid choice. Please try again.\n");
            validInput = 0;
        }
    } while (!validInput);

    clearInputBuffer();
    clearScreen();
	printf("\t\t\t\t\t\033[1;36m**************  \033[1;32mBooking Details \033[1;36m***************\033[0m\n");
    printf("\n\t\t\t\t\tEnter Passport Number: ");
    scanf("%s", booking.passportNumber);
    clearInputBuffer();
    printf("\t\t\t\t\tEnter Name: ");
    scanf(" %[^\n]", booking.name);

    if ((flightChoice == 1 && numDomesticFlights == 0) || (flightChoice == 2 && numInternationalFlights == 0)) {
        printf("\n\t\t\t\t\tNo available flight to book.\n");
        printf("\n\t\t\t\t\tPress any key to return to User Menu.\n");
        getchar();
        clearInputBuffer();
        return;
    } else {
        printf("\n");
        if (flightChoice == 1) {
            if (numDomesticFlights == 0) {
            printf("\t\t\t\t\tNo available domestic flights.\n");
        } else {
            printf("\t\t\t\t\tAvailable Domestic Flights:\n");
            printf("\t\t\t\t\t\033[1;32m+-------------------------------------------+\033[0m\n");
            printf("\t\t\t\t\t\033[1;33m      Destination     |  Econo  |  Business  \033[0m\n");
            printf("\t\t\t\t\t\033[1;32m+------------------------+---------+--------+\033[0m\n");
            for (int i = 0; i < numDomesticFlights; i++) {
                printf("\t\t\t\t\t\033[1;33m %2d. %-20s  P%.2f   P%.2f   \033[0m\n", i + 1, domesticFlights[i].destination, domesticFlights[i].economicPrice, domesticFlights[i].businessPrice);
            }
            printf("\t\t\t\t\t\033[1;32m+-------------------------------------------+\033[0m\n");
        }
        } else {
            if (numInternationalFlights == 0) {
            	printf("\t\t\t\t\tNo available international flights.\n");
        	} else {
	            printf("\t\t\t\t\tAvailable International Flights:\n");
	            printf("\t\t\t\t\t\033[1;32m+-------------------------------------------+\033[0m\n");
	            printf("\t\t\t\t\t\033[1;33m|      Destination      |  Econo  |  Business  |\033[0m\n");
	            printf("\t\t\t\t\t\033[1;32m+------------------------+---------+--------+\033[0m\n");
            for (int i = 0; i < numInternationalFlights; i++) {
                printf("\t\t\t\t\t\033[1;33m %2d. %-20s P%.2f   P%.2f   \033[0m\n", i + 1, internationalFlights[i].destination, internationalFlights[i].economicPrice, internationalFlights[i].businessPrice);
            }
            	printf("\t\t\t\t\t\033[1;32m+-------------------------------------------+\033[0m\n");
        }
        }
    }

    int destinationChoice;
    do {
        printf("\t\t\t\t\tEnter Destination: ");
        if (scanf("%d", &destinationChoice) != 1 || 
            (flightChoice == 1 && (destinationChoice < 1 || destinationChoice > numDomesticFlights)) ||
            (flightChoice == 2 && (destinationChoice < 1 || destinationChoice > numInternationalFlights))) {
            printf("\t\t\t\t\tInvalid choice. Please try again.\n");
            clearInputBuffer();
            validInput = 0;
        } else {
            validInput = 1;
        }
    } while (!validInput);

    struct Flight *chosenFlight = (flightChoice == 1) ? &domesticFlights[destinationChoice - 1] : &internationalFlights[destinationChoice - 1];
    strcpy(booking.destination, chosenFlight->destination);

    clearInputBuffer();
    printf("\t\t\t\t\tAvailable Dates:\n");
    for (int i = 0; i < chosenFlight->numAvailableDates; i++) {
        printf("\t\t\t\t\t%d. %s\n", i + 1, chosenFlight->availableDates[i]);
    }

    int dateChoice;
    do {
        printf("\t\t\t\t\tSelect Date: ");
        if (scanf("%d", &dateChoice) != 1 || dateChoice < 1 || dateChoice > chosenFlight->numAvailableDates) {
            printf("\t\t\t\t\tInvalid choice. Please try again.\n");
            clearInputBuffer();
            validInput = 0;
        } else {
            validInput = 1;
        }
    } while (!validInput);
    strcpy(booking.date, chosenFlight->availableDates[dateChoice - 1]);

    int timeChoice;
    do {
        printf("\n");
	    printf("\t\t\t\t\t\033[1;32m+--------------+--------------+--------------+\033[0m\n");
	    printf("\t\t\t\t\t\033[1;33m|            Time of Departure               |\033[0m\n");
	    printf("\t\t\t\t\t\033[1;32m+--------------+--------------+--------------+\033[0m\n");
	    printf("\t\t\t\t\t\033[1;33m| 1. 4:00am    | \033[1;33m2. 7:00am    | \033[1;33m3. 9:00am    |\n");
	    printf("\t\t\t\t\t\033[1;33m| 4. 5:00pm    | \033[1;33m5. 7:00pm    | \033[1;33m6. 9:00pm    |\n");
	    printf("\t\t\t\t\t\033[1;32m+--------------+--------------+--------------+\033[0m\n");
        printf("\t\t\t\t\tSelect Time: ");
        if (scanf("%d", &timeChoice) != 1) {
            printf("\t\t\t\t\tInvalid choice. Please try again.\n");
            clearInputBuffer();
            validInput = 0;
        } else {
            switch (timeChoice) {
                case 1:
                    strcpy(booking.time, "4:00am");
                    validInput = 1;
                    break;
                case 2:
                    strcpy(booking.time, "7:00am");
                    validInput = 1;
                    break;
                case 3:
                    strcpy(booking.time, "9:00am");
                    validInput = 1;
                    break;
                case 4:
                    strcpy(booking.time, "5:00pm");
                    validInput = 1;
                    break;
                case 5:
                    strcpy(booking.time, "7:00pm");
                    validInput = 1;
                    break;
                case 6:
                    strcpy(booking.time, "9:00pm");
                    validInput = 1;
                    break;
                default:
                    printf("\t\t\t\t\tInvalid choice. Please try again.\n");
                    validInput = 0;
                    break;
            }
        }
    } while (!validInput);

    int classChoice;
    do {
        printf("\t\t\t\t\tSelect Seat Class:\n");
        printf("\t\t\t\t\t1. Economic\n");
        printf("\t\t\t\t\t2. Business\n");
        printf("\t\t\t\t\tEnter your choice: ");
        if (scanf("%d", &classChoice) != 1) {
            printf("\t\t\t\t\tInvalid choice. Please try again.\n");
            clearInputBuffer();
            validInput = 0;
        } else if (classChoice == 1) {
            strcpy(booking.flightClass, "Economic");
            booking.price = chosenFlight->economicPrice;
            validInput = 1;
        } else if (classChoice == 2) {
            strcpy(booking.flightClass, "Business");
            booking.price = chosenFlight->businessPrice;
            validInput = 1;
        } else {
            printf("\t\t\t\t\tInvalid choice. Please try again.\n");
            validInput = 0;
        }
    } while (!validInput);

    clearScreen();
    displayAvailableSeats(chosenFlight->seatMap);
	
    int seatChoice;
    do {
        printf("\n\t\t\t\t\tSelect a seat (0-%d): ", MAX_SEATS - 1);
        if (scanf("%d", &seatChoice) != 1 || seatChoice < 0 || seatChoice >= MAX_SEATS || chosenFlight->seatMap[seatChoice] == 1) {
            printf("\t\t\t\t\tInvalid seat choice or seat already booked. Please try again.\n");
            clearInputBuffer();
            validInput = 0;
        } else {
            validInput = 1;
            booking.seatNumber = seatChoice;
            chosenFlight->seatMap[seatChoice] = 1; // mark seat as booked
        }
    } while (!validInput);
	
	clearScreen();
	printf("\t\t\t\t\t\033[1;36m**************  \033[1;32mPayment \033[1;36m***************\033[0m\n");
    float payableAmount = booking.price;
    float paidAmount;
    float change;
    char cardNumber[20];

    char discountChoice;
    printf("\n\t\t\t   Are you eligible for a 20%% discount for elders or PWDs? (Y/N): ");
    scanf(" %c", &discountChoice);
    if (discountChoice == 'Y' || discountChoice == 'y') {
        payableAmount *= 0.8; // Applying 20% discount
    } else {
        payableAmount *= 1.12; // Adding 12% VAT
    }

    do {
        printf("\n\t\t\t\t\tSelect Payment Method:\n");
        printf("\t\t\t\t\t1. Credit Card\n");
        printf("\t\t\t\t\t2. GCash\n");
        printf("\t\t\t\t\t3. PayMaya\n");
        printf("\n\t\t\t\t\tEnter your choice: ");
        if (scanf("%d", &paymentChoice) != 1 || (paymentChoice != 1 && paymentChoice != 2 && paymentChoice != 3)) {
            printf("\t\t\t\t\tInvalid choice. Please try again.\n");
            clearInputBuffer();
            validInput = 0;
        } else {
            validInput = 1;
        }
    } while (!validInput);

    const char *paymentType;
    switch (paymentChoice) {
        case 1:
            paymentType = "Credit Card";
            break;
        case 2:
            paymentType = "GCash";
            break;
        case 3:
            paymentType = "PayMaya";
            break;
    }

    printf("\t\t\t\t\tEnter Card/Gcash/Paymaya Number: ");
    scanf("%s", cardNumber);

    do {
        printf("\t\t\t\t\tEnter Payment Amount: ");
        if (scanf("%f", &paidAmount) != 1) {
            printf("\t\t\t\t\t\tInvalid amount. Please try again.\n");
            clearInputBuffer();
            validInput = 0;
        } else if (paidAmount < payableAmount) {
            printf("\n\t\t\tInsufficient balance. Payment failed. Please enter a sufficient amount.\n");
            clearInputBuffer();
            validInput = 0;
        } else {
            validInput = 1;
        }
    } while (!validInput);

    change = paidAmount - payableAmount;
    clearInputBuffer();
    clearScreen();
	
	//PRINTING BOOKING SUMMARY
	printf("\t\t\t\t\t\033[1;36m**************  \033[1;32mBooking Summary \033[1;36m***************\033[0m\n");
   
	    printf("\n\t\t\t\t\t\033[1;36m+----------------------------------------------+\033[0m\n");
	    printf("\t\t\t\t\t\033[1;33m|               Booking Details                |\033[0m\n");
	    printf("\t\t\t\t\t\033[1;36m+----------------------------------------------+\033[0m\n");
	    printf("\t\t\t\t\t\033[1;33m       Attribute           |    Value    \033[0m\n");
	    printf("\t\t\t\t\t\033[1;36m+-------------------------+--------------------+\033[0m\n");
	    printf("\t\t\t\t\t\033[1;33m  Booking Number           |    %d       \033[0m\n", numBookings + 1);
	    printf("\t\t\t\t\t\033[1;33m  Passport Number          |    %s       \033[0m\n", booking.passportNumber);
	    printf("\t\t\t\t\t\033[1;33m  Name                     |    %s       \033[0m\n", booking.name);
	    printf("\t\t\t\t\t\033[1;33m  Flight Class             |    %s       \033[0m\n", booking.flightClass);
	    printf("\t\t\t\t\t\033[1;33m  Destination              |    %s       \033[0m\n", booking.destination);
	    printf("\t\t\t\t\t\033[1;33m  Date                     |    %s       \033[0m\n", booking.date);
	    printf("\t\t\t\t\t\033[1;33m  Time                     |    %s       \033[0m\n", booking.time);
	    printf("\t\t\t\t\t\033[1;33m  Seat Number              |    %d       \033[0m\n", booking.seatNumber);
	    printf("\t\t\t\t\t\033[1;36m+----------------------------------------------+\033[0m\n");
	    
	    printf("\n\t\t\t\t\t\033[1;33mBooking Successful!\033[0m");
    
    char printReceiptChoice;
    printf("\n\t\t\t\t\tDo you want to print the receipt? (Y/N): ");
    scanf(" %c", &printReceiptChoice);
    clearInputBuffer();

    if (printReceiptChoice == 'Y' || printReceiptChoice == 'y') {
        clearScreen();
        printf("\n\n\t\t\t\t\t\033[1;36m+--------------------------------------------+\033[0m\n");
	    printf("\t\t\t\t\t\033[1;33m|                  RECEIPT                   |\033[0m\n");
	    printf("\t\t\t\t\t\033[1;36m+--------------------------------------------+\033[0m\n");
	    printf("\t\t\t\t\t\033[1;33m|        Attribute            |     Value    |\033[0m\n");
	    printf("\t\t\t\t\t\033[1;36m+------------------------------+-------------+\033[0m\n");
	    printf("\t\t\t\t\t\033[1;33m  Ticket Price                |   %.2f   \033[0m\n", booking.price);
	    printf("\t\t\t\t\t\033[1;33m  Discount/VAT Applied        |   %.2f   \033[0m\n", (discountChoice == 'Y' || discountChoice == 'y') ? (booking.price * 0.2) : (booking.price * 0.12));
	    printf("\t\t\t\t\t\033[1;33m  Total Payable Amount        |   %.2f   \033[0m\n", payableAmount);
	    printf("\t\t\t\t\t\033[1;33m  Payment Type                |   %s  \033[0m\n", paymentType);
	    printf("\t\t\t\t\t\033[1;33m  Card Number                 |   %s \033[0m\n", cardNumber);
	    printf("\t\t\t\t\t\033[1;33m  Paid Amount                 |   %.2f   \033[0m\n", paidAmount);
	    printf("\t\t\t\t\t\033[1;33m  Change                      |   %.2f   \033[0m\n", change);
	    printf("\t\t\t\t\t\033[1;36m+--------------------------------------------+\033[0m\n");
    }

    booking.bookingNumber = numBookings + 1;
    bookings[numBookings] = booking; // Store the booking in the array
    numBookings++; // Increment the booking count

    printf("\n\t\t\t\t\tPress any key to return to User Menu.\n");
    getchar();
}


//DISPLAY BOOKING RECORDS
void displayRecords() {
    clearScreen();
    printf("\t\t\t\t\t\033[1;36m---------------  \033[1;33mBooking Records \033[1;36m---------------\033[0m\n");
    if (numBookings == 0) {
        printf("\n\t\t\t\t\tNo bookings to display.\n");
    } else {
        printf("\n\t\t\t\t\tBooking Records:\n");
        for (int i = 0; i < numBookings; i++) {
            printf("\n\t\t\t\t\tBooking Number: %d\n", bookings[i].bookingNumber);
            printf("\t\t\t\t\tPassport Number: %s\n", bookings[i].passportNumber);
            printf("\t\t\t\t\tName: %s\n", bookings[i].name);
            printf("\t\t\t\t\tFlight Class: %s\n", bookings[i].flightClass);
            printf("\t\t\t\t\tDestination: %s\n", bookings[i].destination);
            printf("\t\t\t\t\tDate: %s\n", bookings[i].date);
            printf("\t\t\t\t\tTime: %s\n", bookings[i].time);
            printf("\t\t\t\t\tSeat Number: %d\n", bookings[i].seatNumber);
            printf("\t\t\t\t\tPrice: %.2f\n\n", bookings[i].price);
        }
    }
    printf("\n\t\t\t\t\tPress any key to return to User Menu.\n");
    getchar();
    clearInputBuffer();
}

//CANCEL BOOKING
void cancelBooking() {
    clearScreen();
    printf("\t\t\t\t\t\033[1;36m---------------  \033[1;33mCancel Booking \033[1;36m---------------\033[0m\n");
    if (numBookings == 0) {
        printf("\t\t\t\t\tNo bookings to cancel.\n");
        printf("\n\t\t\t\t\tPress any key to return to User Menu.\n");
        getchar();
        getchar();
        return;
    }

    int bookingNumber;
    printf("\t\t\t\t\tEnter Booking Number to Cancel: ");
    scanf("%d", &bookingNumber);

    int found = 0;
    int i;
    for (i = 0; i < numBookings; i++) {
        if (bookings[i].bookingNumber == bookingNumber) {
            found = 1;
            char confirmation;
            printf("\t\t\t\t\tAre you sure you want to cancel booking %d? (y/n): ", bookingNumber);
            getchar(); // Clear buffer
            scanf("%c", &confirmation);
            if (confirmation == 'y' || confirmation == 'Y') {
                for (int j = i; j < numBookings - 1; j++) {
                    bookings[j] = bookings[j + 1];
                }
                numBookings--;
                printf("\t\t\t\t\tBooking %d canceled successfully.\n", bookingNumber);
            } else {
                printf("\t\t\t\t\tBooking cancellation aborted.\n");
            }
            break;
        }
    }

    if (!found) {
        printf("\n\t\t\t\t\tInvalid booking number.\n");
    }

    printf("\n\t\t\t\t\tPress any key to return to User Menu.\n");
    getchar();
    getchar();
}



