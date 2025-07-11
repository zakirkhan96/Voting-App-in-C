#include <stdio.h>
#include <string.h>

#define MAX_VOTERS 200
#define MAX_PARTIES 4
#define MAX_CITIES 10

void printPartyNames() {
	
    printf("\nChoose your Favorable party.\n");
    
    printf("1. PSK Party\n");
    printf("Their symbol is a LADDER\n");
    printf("\n");
    printf("    ||    ||\n");
    printf("    ||====||\n");
    printf("    ||====||\n");
    printf("    ||====||\n");
    printf("    ||====||\n");
    printf("    ||====||\n");
    printf("    ||    ||\n\n");
    
    printf("2. PMN Party\n");
    printf("Their symbol is a TREE\n");
    printf("\n");
    printf("      ^^     \n");
    printf("     ^^^^    \n");
    printf("    ^^^^^^   \n");
    printf("   ^^^^^^^^  \n");
    printf("      ||      \n");
    printf("      ||      \n\n");
    
    printf("3. PSI Party\n");
    printf("Their symbol is a ROCKET\n");
    printf("\n");
    printf("    /\\        \n");
    printf("   /  \\       \n");
    printf("  |    |      \n");
    printf("  |    |      \n");
    printf("  |    |      \n");
    printf("  |____|      \n");
    printf("   |  |       \n");
    printf("  /    \\      \n");
    printf(" |      |     \n");
    printf(" |______|     \n\n");
    
    printf("4. PZK Party\n");
    printf("Their symbol is 3 FISHES\n");
    printf("\n");
    printf("><((((('>\n");
    printf("   ><((((('>\n");
    printf("      ><((((('>\n\n");
    
}

void printCityNames() {
	
    printf("\nFollowing are the names of 10 cities in Pakistan.\nYou can cast a vote for any 1 out of these.\n ");
    char cities[][20] = {"Karachi", "Lahore", "Islamabad", "Faisalabad", "Rawalpindi", "Multan", "Hyderabad", "Quetta", "Peshawar", "Sialkot"};

    for (int i = 0; i < 10; ++i) {
        printf("%d. %s\n", i + 1, cities[i]);
    }

}

void calculateResult(int votes[][MAX_VOTERS], int size, const char entityType[], const char entityNames[][20]) {
	
    printf("\nThe total votes for each %s are as follows:\n", entityType);
    for (int i = 0; i < size; i++) {
        int totalVotes = 0;
        for (int j = 0; j < MAX_VOTERS; j++) {
            totalVotes += votes[i][j];
        }
        printf("%s %s: %d votes\n", entityNames[i], entityType, totalVotes);
    }

}

void askForFeedback(char feedback[]) {
	
    printf("\n\nIf you want to share any advice,suggestion or any problem which you want the future government to deal with\nThen feel free to share it here: ");
    scanf(" %[^\n]s", feedback);

}

int main() {
	
    int vote, parties[MAX_PARTIES][MAX_VOTERS] = {0};
    int cities[MAX_CITIES][MAX_VOTERS] = {0};
    int partySize = 0, citySize = 0;
    int choice;
    char userFeedback[100];

    char partyNames[MAX_PARTIES][20] = {"PSK Party", "PMN Party", "PSI Party", "PZK Party"};
    char cityNames[MAX_CITIES][20] = {"Karachi", "Lahore", "Islamabad", "Faisalabad", "Rawalpindi", "Multan", "Hyderabad", "Quetta", "Peshawar", "Sialkot"};

	printf("VOTING SYSTEM\n");
	printf("=============\n\n");
	printf("WELCOME TO VOTING SYSTEM FOR 2024 ELECTIONS\n\n");
	printf("\nDESCRIPTION: \nThis voting system allows you to select your favorable party along with your desired city.\nYou can also see the results , also it allows you to share your opinion in the end.\n");
	
    do {
    	
        printPartyNames();

        while (1) {
        	
            printf("Enter the party number you want to vote for (1, 2, 3, 4): ");
            scanf("%d", &vote);

            if (vote >= 1 && vote <= MAX_PARTIES) {
                printf("To cast your vote, Enter 1: ");
                scanf("%d", &parties[vote - 1][partySize]);
                partySize++;
                break;
            } else {
                printf("Please enter a valid party number\n");
            }
        
		}

        printCityNames();

        while (1) {
        	
            printf("Enter the city number you want to vote for (1-10): ");
            scanf("%d", &vote);

            if (vote >= 1 && vote <= MAX_CITIES) {
                printf("To cast your vote, Enter 1: ");
                scanf("%d", &cities[vote - 1][citySize]);
                citySize++;
                break;
            } else {
                printf("Please enter a valid city number\n");
            }
        
		}

        askForFeedback(userFeedback);

      
        printf("\nThank you for your participation in the elections. May our country prosper and thrive!\n\n");

        
        printf("Do you want to vote again or see the calculated result?\n");
        printf("Enter 1 for vote or 2 for result: ");
        scanf("%d", &choice);

    } while (choice == 1);

  
    calculateResult(parties, MAX_PARTIES, "Party", partyNames);
    calculateResult(cities, MAX_CITIES, "City", cityNames);

    
    printf("\nVoter's Feedback: %s\n", userFeedback);

    return 0;
}
