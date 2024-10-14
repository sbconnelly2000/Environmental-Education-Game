#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int size = 0;

typedef struct {
    char username[20];
    char password[20];
} User;

User *users = NULL;

void updateUsers() {
    FILE *users_file = fopen("users.csv", "w");
    if (users_file == NULL) {
        printf("Error opening users_file\n");
        exit(EXIT_FAILURE);
    }
    fprintf(users_file, "Username,Password\n");
    for(int i = 0; i < size; i++) {
        fprintf(users_file, "%s,%s\n", users[i].username, users[i].password);
    }
    fclose(users_file);
}

void addUser(){
    size++;
    users = realloc(users, size * sizeof(User));
    if (users == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    printf("Enter username: ");
    scanf("%s", users[size - 1].username);
    printf("Enter password: ");
    scanf("%s", users[size - 1].password);
    updateUsers();
}

#define MAX_QUESTION_LENGTH 200
#define NUM_QUESTIONS 10

typedef struct {
    char question[MAX_QUESTION_LENGTH];
    int answer; // 1 for True, 0 for False
} QuizQuestion;

QuizQuestion quiz[NUM_QUESTIONS] = {
    {"Each of the organisms in an ecosystem plays a specific role as a producer, consumer, or decomposer: ", 1},
    {"A food web consists of many overlapping food chains within an ecosystem: ", 1},
    {"Energy primarily enters ecosystems through sunlight: ", 1},
    {"Some organisms, such as plants, algae, and rocks, capture sunlight energy and store it: ", 0},
    {"An energy pyramid illustrates the amount of energy transferred from one feeding level to another in a food web: ", 1},
    {"Biomes are large areas with similar flora, fauna, and microorganisms: ", 1},
    {"Organisms on this planet are not linked to others and are independent ", 0},
    {"If an ecosystem had only producers and consumers, the world would be cleaner: ", 1},
    {"Decomposers are classified by what they eat: ", 1},
    {"Ecosystems will fail if they do not remain in balance: ", 1}
};

void moveplayer(int *position1, int *position2, int player) {
    if(player == 1) {
        (*position1)++;
    } else if(player == 2) {
        (*position2)++;
    }

    if(*position1 == *position2) {
        for(int i = 0; i < 10; i++) {
            if(*position1 == i)
                printf(" 1      2 \n");
            else
                printf("\n");
        }
    } else {
        for(int i = 0; i < 10; i++) {
            if(*position1 == i)
                printf(" 1        \n");
            else if(*position2 == i)
                printf("        2 \n");
            else printf("\n");
        }
        printf("----------\n");
    }
    printf("\n");
}

void askQuestion1(int *position1, int *position2,int*p) {
    char answer;

    printf("Player 1: %s", quiz[*p].question);
    scanf(" %c", &answer);
    if(answer == 't' && quiz[*p].answer == 1) {
        (*position1)++;
        moveplayer(position1, position2, 1);
    } else if(answer == 'f' && quiz[*p].answer == 0) {
        (*position1)++;
        moveplayer(position1, position2, 1);
    } else {
        printf("Wrong answer\n");
        moveplayer(position1, position2,3);
    }
    (*p)++;
}


void askQuestion2(int *position1, int *position2,int*p) {
    char answer;
    printf("Player 2: %s", quiz[*p].question);
    scanf(" %c", &answer);
    if(answer == 't' && quiz[*p].answer == 1) {
        (*position2)++;
        moveplayer(position1, position2, 2);
    } else if(answer == 'f' && quiz[*p].answer == 0) {
        (*position2)++;
        moveplayer(position1, position2, 2);
    } else {
        printf("Wrong answer\n\n");
        moveplayer(position1,position2,3);
    }
    (*p)++;
}

int checkWin(int*position1,int*position2){
        if(*position1==*position2)
                printf("Tie");
        else if(*position1>*position2)
                printf("Player 1 Wins!!!");
        else if(*position2>*position1)
                printf("Player 2 Wins!!!");
        return 1;

}

void obstacle(int*position){
    int answer;
    printf("Your turtle is about to be scooped up by a bird what do you do(Enter '1',2',or '3)\n");
    printf("1. Keep running to the water\n");
    printf("2. Try to hide in the sand\n");
    printf("3. Fight the bird\n");
    scanf("%d",&answer);
    if(answer==1 || answer == 3){
        printf("The bird picks you up and moves you back to the begining\n\n");
        (*position)=0;
    }else if(answer == 2){
        printf("You succesfully escaped the bird!!!\n\n");
    }else{
        printf("The bird picks you up and moves you back to the begining\n\n");
        (*position)=0;
    }
}

int main() {
    int position1 = 0, position2 = 0;
    int p=0;

    printf("\033[2J");
    printf("\033[H");

    addUser();

    printf("\033[2J");
    printf("\033[H");

    srand(time(NULL));
    int randomNumber1 = rand() % 5;
    int randomNumber2 = rand() % 5;
    printf("\nEmbark on an enchanting journey where the mysteries of nature unfold before your eyes.\n");
    printf("In our game, \"Turtle Trek,\" players witness the awe-inspiring spectacle of baby turtles hatching and beginning their race to the ocean.\n");
    printf("Experience the challenges these resilient creatures face as they navigate sandy shores and evade predators on their quest for survival.\n");
    printf("Are you ready to immerse yourself in the delicate balance of life and nature?\n");
    printf("Join us in \"Turtle Trek\" and witness the incredible journey of these determined hatchlings.\n");

    printf("\nYou and your opponent will be racing to the ocean and the first person to make it to safety wins.\n");
    printf("Each correct answer will get you closer to the ocean\n");
    printf("Stay safe and watch out for birds.\n");

    printf("\nAnswer each question with either true or false 't' or 'f'\n\n");
    for(int i = 0;i<5;i++){
        askQuestion1(&position1, &position2,&p);
         if(i==randomNumber1){
            obstacle(&position1);
        }
        askQuestion2(&position1, &position2,&p);
         if(i==randomNumber2){
            obstacle(&position2);
        }
    }
    checkWin(&position1,&position2);
    return 0;
}
