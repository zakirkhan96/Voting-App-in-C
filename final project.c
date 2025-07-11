#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_PARTIES 10
#define MAX_CITIES 10
#define MAX_VOTERS 200

char usernames[MAX_USERS][20];
char passwords[MAX_USERS][20];
char roles[MAX_USERS][10];
int userCount = 0;

char partyNames[MAX_PARTIES][30] = {"PSK Party", "PMN Party", "PSI Party", "PZK Party"};
int partyCount = 4;

char cityNames[MAX_CITIES][20] = {
    "Karachi", "Lahore", "Islamabad", "Faisalabad", "Rawalpindi",
    "Multan", "Hyderabad", "Quetta", "Peshawar", "Sialkot"
};

int partyVotes[MAX_PARTIES] = {0};
int cityVotes[MAX_CITIES] = {0};

// Load users from users.txt
void loadUsers() {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Error: users.txt not found!\n");
        exit(1);
    }

    while (fscanf(file, "%[^,],%[^,],%s\n", usernames[userCount], passwords[userCount], roles[userCount]) != EOF) {
        userCount++;
    }

    fclose(file);
}

// Authenticate user
int authenticate(char *username, char *password, char *roleOut) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(usernames[i], username) == 0 && strcmp(passwords[i], password) == 0) {
            strcpy(roleOut, roles[i]);
            return 1;
        }
    }
    return 0;
}

// Admin adds a new user
void addUser() {
    char newUsername[20], newPassword[20], newRole[10];
    printf("Enter new username: ");
    scanf("%s", newUsername);
    printf("Enter new password: ");
    scanf("%s", newPassword);
    printf("Enter role (admin/voter): ");
    scanf("%s", newRole);

    FILE *file = fopen("users.txt", "a");
    if (file == NULL) {
        printf("Error opening users.txt\n");
        return;
    }
    fprintf(file, "%s,%s,%s\n", newUsername, newPassword, newRole);
    fclose(file);
    printf("User added successfully!\n");
}

// Admin shows vote results
void showResults() {
    printf("\n--- Voting Results by Party ---\n");
    for (int i = 0; i < partyCount; i++) {
        printf("%s: %d votes\n", partyNames[i], partyVotes[i]);
    }

    printf("\n--- Voting Results by City ---\n");
    for (int i = 0; i < MAX_CITIES; i++) {
        printf("%s: %d votes\n", cityNames[i], cityVotes[i]);
    }
}

// Admin views feedback
void viewFeedback() {
    FILE *file = fopen("feedback.txt", "r");
    if (file == NULL) {
        printf("No feedback available yet.\n");
        return;
    }

    char line[200];
    printf("\n--- Voter Feedback ---\n");
    while (fgets(line, sizeof(line), file)) {
        printf("- %s", line);
    }
    fclose(file);
    printf("\n");
}

// Voter casts vote
void vote() {
    int partyChoice, cityChoice;
    
    printf("\n--- Parties ---\n");
    for (int i = 0; i < partyCount; i++) {
        printf("%d. %s\n", i + 1, partyNames[i]);
    }
    do {
        printf("Choose a party (1-%d): ", partyCount);
        scanf("%d", &partyChoice);
    } while (partyChoice < 1 || partyChoice > partyCount);
    partyVotes[partyChoice - 1]++;

    printf("\n--- Cities ---\n");
    for (int i = 0; i < MAX_CITIES; i++) {
        printf("%d. %s\n", i + 1, cityNames[i]);
    }
    do {
        printf("Choose a city (1-10): ");
        scanf("%d", &cityChoice);
    } while (cityChoice < 1 || cityChoice > 10);
    cityVotes[cityChoice - 1]++;

    printf("Vote cast successfully!\n");
}

// Voter gives feedback
void giveFeedback() {
    char feedback[200];
    FILE *file = fopen("feedback.txt", "a");
    if (file == NULL) {
        printf("Error opening feedback.txt\n");
        return;
    }
    printf("Enter your feedback/suggestion: ");
    getchar();  // clear newline
    fgets(feedback, sizeof(feedback), stdin);
    fprintf(file, "%s", feedback);
    fclose(file);
    printf("Thank you for your feedback!\n");
}

// Admin panel
void adminMenu() {
    int choice;
    do {
        printf("\n--- Admin Panel ---\n");
        printf("1. Show Voting Results\n");
        printf("2. Add New User\n");
        printf("3. View Feedback\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: showResults(); break;
            case 2: addUser(); break;
            case 3: viewFeedback(); break;
            case 4: printf("Logging out...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 4);
}

// Voter panel
void voterMenu() {
    int choice;
    do {
        printf("\n--- Voter Panel ---\n");
        printf("1. Vote\n");
        printf("2. Submit Feedback\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: vote(); break;
            case 2: giveFeedback(); break;
            case 3: printf("Logging out...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 3);
}

int main() {
    char username[20], password[20], role[10];

    // === File Initialization ===
    FILE *fileCheck;

    // Create users.txt if not exists
    fileCheck = fopen("users.txt", "r");
    if (fileCheck == NULL) {
        printf("users.txt not found. Creating default users.txt...\n");
        fileCheck = fopen("users.txt", "w");
        if (fileCheck != NULL) {
            fprintf(fileCheck, "admin,admin123,admin\n");
            fprintf(fileCheck, "voter1,vote123,voter\n");
            fclose(fileCheck);
            printf("Default admin and voter added.\n");
        } else {
            printf("Error: Cannot create users.txt\n");
            return 1;
        }
    } else {
        fclose(fileCheck);
    }

    // Create feedback.txt if not exists
    fileCheck = fopen("feedback.txt", "r");
    if (fileCheck == NULL) {
        printf("feedback.txt not found. Creating new feedback.txt...\n");
        fileCheck = fopen("feedback.txt", "w");
        if (fileCheck != NULL) {
            fclose(fileCheck);
        } else {
            printf("Error: Cannot create feedback.txt\n");
            return 1;
        }
    } else {
        fclose(fileCheck);
    }

    // Load users from file
    loadUsers();

    printf("=== Welcome to Voting System ===\n");

    int attempts = 0, loggedIn = 0;
    while (attempts < 3 && !loggedIn) {
        printf("\nEnter username: ");
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);

        if (authenticate(username, password, role)) {
            printf("Login successful! Role: %s\n", role);
            loggedIn = 1;
        } else {
            printf("Incorrect credentials. Try again.\n");
            attempts++;
        }
    }

    if (!loggedIn) {
        printf("Too many failed attempts. Exiting...\n");
        return 1;
    }

    if (strcmp(role, "admin") == 0) {
        adminMenu();
    } else if (strcmp(role, "voter") == 0) {
        voterMenu();
    } else {
        printf("Invalid role. Exiting.\n");
    }

    return 0;
}
