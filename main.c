// Eoghan Spillane
// R00175214
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

//gcc main.c -o main
//main QNA.txt 3

//This function is used for random ordered letters for difficulty 5 and the random order of the question.
void randomArray(int array[], int length){
    int i = 0;
    int x = 0;

    while(i < length){
        int newLet = rand()%length;

        //Checks if the new Int is already in the array.
        for (x = 0; x < i; x++){
            if(array[x] == newLet){
                break;
            }
        }

        if(x==i){
            array[i++] = newLet;
        }

    }
}


int main(int argc, char **argv) {
    FILE *f;
    FILE *results;
    char* fileName = argv[1];
    char* diffStr = argv[2];
    int difficulty = atoi(diffStr);
    srand(time(NULL));

    // Difficulty 6 is a random Difficulty
    if(difficulty == 6){
        difficulty = rand()%5 + 1;
    }


    // Checks if all the Commandline arguments are present
    if (argc < 3){
        printf("Enter Filename and difficulty");
        exit(1);
    }
    else{
        printf("File Name: %s\n", fileName);
        printf("Difficulty: %d\n", difficulty);
    }

    // Opens the file and checks if its valid
    if((f = fopen(fileName, "r")) == NULL){
        printf("File Not Found\n");
        exit(1);
    }

    //-------------------------------------------------------

    char buf[280]; //Temporarily holds the line read from the file
    char space[200]; // space get's overwritten by the Sscanf function every time it's run so no need to store it.

    char Answers[200][280];
    char Question[200][280];

    // This keep track of correctly and incorrectly answered questions
    int incorrect[200];

    // Breaks the file into 2 arrays
    // It also counts how many questions there are.
    int i = 0;
    while (fgets(buf, 200, f) != NULL) {
        sscanf(buf, "%[^?] %s %s", Question[i], space, Answers[i]); // Breaks the line and stores it in two arrays. The ? is discarded in space.
        i++;
    }

    // How many Questions are in the quiz
    printf("\n-----------------------------------");
    int numOfQuestions = i;
    int correct = 0;
    printf("\nThere are %d questions in this Quiz\n", numOfQuestions);

    //------------------------------------------------------
    // Temp Answer for the user
    char userAnswer[50];


    //These variables are used for random Order questions.
    int p = 0;
    int x = 0;
    int QuestOrder[numOfQuestions];
    randomArray(QuestOrder, numOfQuestions );

    while (p < i){
        // follows the re-odered list instead of the 1-5, i.e. (3,4,2,5,1)
        x = QuestOrder[p];
        printf("\nQuestion %d: %s?\n", p+1, Question[x]);

        // Difficulty is passed in as an argument.
        // Depending on the difficulty entered the clue is different
        if(difficulty == 1){
            printf("?\n");
        }
        else if(difficulty == 2){
            for(int y = 0; y < strlen(Answers[x]); y++){
                printf(" - ");
            }
            printf("\n");
        }
        else if(difficulty == 3){
            for(int y = 0; y < strlen(Answers[x]); y++){
                if(y == 0){
                    printf("%c", Answers[x][0]);
                }
                else if(y == strlen(Answers[x]) - 1){
                    printf("%c", Answers[x][strlen(Answers[x]) - 1]);
                }
                else{
                    printf(" - ");
                }
            }
            printf("\n");
        }
        else if (difficulty == 4){
            int let1 = 0;
            int let2 = 0;

            while(let1 == let2){
                let1 = rand()%strlen(Answers[x]);
                let2 = rand()%strlen(Answers[x]);
            }

            for(int y = 0; y < strlen(Answers[x]); y++){
                if(y == let1){
                    printf(" %c ", Answers[x][let1]);
                }
                else if(y == let2){
                    printf(" %c ", Answers[x][let2]);
                }
                else{
                    printf(" - ");
                }
            }
            printf("\n");

        }
        else if(difficulty == 5){
            int IndexArr[strlen(Answers[x])];
            randomArray(IndexArr, strlen(Answers[x]) );

            int loops;
            for(loops = 0; loops < strlen(Answers[x]); loops++){
                printf("%c", tolower(Answers[x][IndexArr[loops]]));
            }
            printf("\n");
        }

        // User enter's they're answer
        printf(">");
        scanf("%s", userAnswer);

        //Compare the actual answer to the user answer. Also lower's them before Comparing them.
        int result = strcmp(strlwr((char*) userAnswer), strlwr((char*) Answers[x]));

        if(result == 0){
            printf("Correct\n");
            correct++;
            incorrect[x] = 2;
        }
        else{
            printf("Incorrect\n");
            //printf("Correct answer is %s\n", Answers[x]);
            incorrect[x] = 1;
        }
        p++;
    }

    // The File output
    results = fopen("Results.txt", "w");
    fprintf(results, "Filename: %s\n", fileName);
    fprintf(results, "Difficulty: %d\n", difficulty);
    fprintf(results, "There were %d Questions\n", numOfQuestions);
    fprintf(results, "Score: %d/%d", correct, numOfQuestions);

    printf("\n-----------------------------------\n");
    printf("You got %d/%d Correct\n", correct, numOfQuestions);
    printf("Do you want to see the Correct Answers? Y/N\n>");



    //Print out the correct Answers
    char userInput[5];
    scanf(" %c", userInput);

    if(strcmp("Y", userInput) == 0){
        int loop;
        for(loop = 0; loop < numOfQuestions; loop++)
            if(incorrect[loop] == 1){
                printf("\n%s?: %s", Question[loop], Answers[loop]);
            }
    }

    //  Close files
    fclose(f);
    fclose(results);
    return 0;
}
