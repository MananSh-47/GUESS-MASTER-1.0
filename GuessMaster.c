
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main()
{
    int guess, rand_num, difficulty, limit, score, previous_guesses, previous_score;
    int scores[100], count = 0, num_of_guess = 0;
    int temp;
    char name[30], previous_name[30], names[100][30];
    char choice;

    FILE *fp;
    srand(time(0));
    printf("================================\n");
    printf("          GUESS MASTER 2.0      \n");
    printf("================================\n");

    fp = fopen("previous.txt", "r");
    if (fp == NULL)
    {
        printf("\nNo previous game record found.\n");
    }
    else
    {
        if (fscanf(fp, "%29s %d %d", previous_name, &previous_guesses, &previous_score) == 3)
        {
            printf("\n===== PREVIOUS GAME =====\n");
            printf("Player: %s\n", previous_name);
            printf("Guesses: %d\n", previous_guesses);
            printf("Score: %d\n", previous_score);
        }
        else
        {
            printf("\nPrevious game record is invalid.\n");
        }
        fclose(fp);
    }
    do
    {
        printf("\n========== MAIN MENU ==========\n");
        printf("1. Start Game\n");
        printf("2. View Leaderboard\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        if (choice == '1')
        {
            printf("\nEnter your name: ");
            scanf("%29s", name);
            do
            {
                printf("\nSelect Difficulty:\n");
                printf("1. Easy (1-50)\n");
                printf("2. Medium (1-100)\n");
                printf("3. Hard (1-500)\n");
                printf("Enter choice: ");
                scanf("%d", &difficulty);

                if (difficulty == 1)
                    limit = 50;
                else if (difficulty == 2)
                    limit = 100;
                else if (difficulty == 3)
                    limit = 500;
                else
                    printf("Invalid difficulty! Try again.\n");

            } while (difficulty < 1 || difficulty > 3);
            num_of_guess = 0;
            rand_num = (rand() % limit) + 1;
            printf("\nGuess a number between 1 and %d\n", limit);
            do
            {
                printf("--> ");
                scanf("%d", &guess);
                if (guess < 1 || guess > limit)
                {
                    printf("Invalid Input! Try again.\n");
                    continue;
                }

                num_of_guess++;

                if (guess > rand_num)
                    printf("Try lower!\n");
                else if (guess < rand_num)
                    printf("Try higher!\n");
                else
                {
                    printf("\nCONGRATULATIONS!\n");
                    printf("You guessed it correctly!\n");
                    printf("Guessed in %d attempts!\n", num_of_guess);
                }
            } while (guess != rand_num);

            if (num_of_guess <= 3)
                printf("\nLEGENDARY!\n");

            else if (num_of_guess <= 6)
                printf("\nGREAT!\n");

            else
                printf("\nNICE EFFORT!\n");

            score = 1000 - (num_of_guess * 10);

            if (score < 0)
                score = 0;
            printf("Your score: %d\n", score);

            fp = fopen("previous.txt", "w");
            if (fp != NULL)
            {
                fprintf(fp, "%s %d %d", name, num_of_guess, score);
                fclose(fp);
            }
            else
            {
                printf("Unable to save previous game record.\n");
            }

            fp = fopen("leaderboard.txt", "a");

            if (fp != NULL)
            {
                fprintf(fp, "%s %d\n", name, score);
                fclose(fp);
            }
            else
            {
                printf("Unable to save leaderboard record.\n");
            }
        }
        else if (choice == '2')
        {
            fp = fopen("leaderboard.txt", "r");

            if (fp == NULL)
            {
                printf("\nNo leaderboard records available.\n");
            }
            else
            {
                count = 0;
                while (count < 100 &&
                       fscanf(fp, "%29s %d", names[count],
                              &scores[count]) == 2)
                {
                    count++;
                }
                fclose(fp);
                for (int i = 0; i < count - 1; i++)
                {
                    for (int j = i + 1; j < count; j++)
                    {
                        if (scores[i] < scores[j])
                        {
                            temp = scores[i];
                            scores[i] = scores[j];
                            scores[j] = temp;

                            char temp_name[30];

                            strcpy(temp_name, names[i]);
                            strcpy(names[i], names[j]);
                            strcpy(names[j], temp_name);
                        }
                    }
                }
                printf("\n========== LEADERBOARD ==========\n");
                printf("Rank\tPlayer\tScore\n");

                if (count == 0)
                    printf("No records available.\n");

                for (int i = 0; i < count && i < 10; i++)
                {
                    printf("%d\t%s\t%d\n",
                           i + 1, names[i], scores[i]);
                }
            }
        }
        else if (choice == '3')
        {
            printf("\nThanks for playing!\n");
        }
        else
        {
            printf("\nInvalid choice! Please try again.\n");
        }
    } while (choice != '3');
    printf("\nDeveloped by MananSh-47\n");

    return 0;
}
