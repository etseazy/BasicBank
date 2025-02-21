//___________BANK APPLICATION___________

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

char first_name[20], last_name[20], mobile_no[11];
short int customer_id = 0;
float withdraw = 0, deposit = 0, totalMoney = 0;
char mode;
FILE *Masterfile, *Balance, *Transaction, *tempfile;

// Function to open Masterfile
int Open_Masterfile(char mode) {
    if (mode == 'a') {
        Masterfile = fopen("C:/MinGW/Masterfile.txt", "a");
    } else if (mode == 'r') {
        Masterfile = fopen("C:/MinGW/Masterfile.txt", "r");
    } else if (mode == 'w') {
        Masterfile = fopen("C:/MinGW/Masterfile.txt", "w");
    }
    if (Masterfile == NULL) {
        perror("Error opening Masterfile");
    }
    mode = '\0';
    return 0;
}

// Function to open Transaction file
int Open_transactionfile() {
    Transaction = fopen("C:/MinGW/Transaction.txt", "a");
    if (Transaction == NULL) {
        perror("Error opening Transaction file");
    }
    return 0;
}

// Function to open Balance file
int Open_Balancefile(char mode) {
    if (mode == 'a') {
        Balance = fopen("C:/MinGW/Balance.txt", "a");
    } else if (mode == 'r') {
        Balance = fopen("C:/MinGW/Balance.txt", "r");
    } else if (mode == 'w') {
        Balance = fopen("C:/MinGW/Balance.txt", "w");
    }
    if (Balance == NULL) {
        perror("Error opening Balance file");
    }
    mode = '\0';
    return 0;
}

// Function to open Temp file
int Open_tempfile(char mode) {
    if (mode == 'a') {
        tempfile = fopen("C:/MinGW/tempfile.txt", "a");
    } else if (mode == 'r') {
        tempfile = fopen("C:/MinGW/tempfile.txt", "r");
    } else if (mode == 'w') {
        tempfile = fopen("C:/MinGW/tempfile.txt", "w");
    }
    if (tempfile == NULL) {
        perror("Error opening Temp file");
    }
    mode = '\0';
    return 0;
}

// Function to read last customer ID
int Get_max_id() {
    int max_id = 0;
    char line[60];
    char delimiter[] = ",";
    Open_Masterfile('r');
    while (fgets(line, sizeof(line), Masterfile)) {
        int token_id;
        char *token = strtok(line, delimiter);
        sscanf(token, "%d", &token_id);
        if (token_id > max_id) {
            max_id = token_id;
        }
    }
    fclose(Masterfile);
    return max_id;
}

// Function to store customer data
int Store_data(int customer_id, char first_name[], char last_name[], char mobile_no[], float totalMoney) {
    Open_Masterfile('a');
    time_t t;
    time(&t);
    char ftime[30];
    strftime(ftime, sizeof(ftime), "%x %H:%M", localtime(&t));
    fprintf(Masterfile, "%d,%s,%s,%s,%s\n", customer_id, ftime, first_name, last_name, mobile_no);
    fclose(Masterfile);
    Open_Balancefile('a');
    fprintf(Balance, "%d,%.4f\n", customer_id, totalMoney);
    fclose(Balance);
    return 0;
}

// Function to create account
int Create_acc() {
    printf("Enter First name: ");
    scanf("%s", first_name);
    printf("Enter Last name: ");
    scanf("%s", last_name);
    printf("Enter Mobile number: ");
    scanf("%s", mobile_no);
    totalMoney = 0.0;
    customer_id = Get_max_id() + 1;
    printf("Your customer ID: %d\n", customer_id);
    Store_data(customer_id, first_name, last_name, mobile_no, totalMoney);
    return customer_id;
}

// Function to deposit money
int Deposit_money(int id) {
    printf("Enter amount to deposit: ");
    scanf("%f", &deposit);
    Open_transactionfile();
    fprintf(Transaction, "%d,Deposited: %.4f\n", id, deposit);
    fclose(Transaction);
    printf("Amount %.4f deposited.\n", deposit);
    deposit = 0;
    return 0;
}

// Function to withdraw money
int Withdraw_money(int id) {
    printf("Enter amount to withdraw: ");
    scanf("%f", &withdraw);
    Open_transactionfile();
    fprintf(Transaction, "%d,Withdrawn: %.4f\n", id, withdraw);
    fclose(Transaction);
    printf("Amount %.4f withdrawn.\n", withdraw);
    withdraw = 0;
    return 0;
}

// Main menu function
int Main_menu(int id) {
    int menu;
    while (1) {
        printf("1: Display Profile Info\n2: Deposit Money\n3: Withdraw Money\n4: Exit\n>> ");
        scanf("%d", &menu);
        switch (menu) {
            case 1:
                printf("Displaying profile info...\n");
                break;
            case 2:
                Deposit_money(id);
                break;
            case 3:
                Withdraw_money(id);
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}

// Main function
int main() {
    int choice, id;
    printf("WELCOME TO YOUR BANK\n");
    do {
        printf("1: Create Account\n2: Log in\n>> ");
        scanf("%d", &choice);
    } while (choice != 1 && choice != 2);
    if (choice == 1) {
        id = Create_acc();
        Main_menu(id);
    } else {
        printf("Enter your customer ID: ");
        scanf("%d", &id);
        Main_menu(id);
    }
    return 0;
}
