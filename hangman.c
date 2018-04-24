/*
*======================================================================
*
*       FILENAME: hangman.c
*
*
*
*       DESCRIPTION: This is a simple game which gives the user five guesses.
*                       To get the correct word, otherwise the man will be hanged.
*
*
*       VERSION: Code::Blocks 13.2
*
*       CREATED: 22/04/2018
*
*       COMPILER: gcc
*
*
*       AUTHOR: Mohammed Kadiri
*
*     ===========================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#define MAX_LENGTH 13
#define WORDS 852



//Function prototype to populate array
void addWords(char *list[]);
//Function prototype to display menu
void start(char *list[]);
//Function prototype to display hangman
void display(int num);
//Function prototype menu screen
void menu();
//Function prototype to tell the user about the rules
void rules();

int main()
{
    system("COLOR 1F");//Set the background and font color
    char *words[WORDS];//Declare a char array of pointers
    addWords(words);//Populate the array with words
    menu();
    getchar();
    system("cls");//Clear screen
    start(words);
}

void start(char *list[])
{
    //Declaration and intialisation of variables
    char word[MAX_LENGTH];
    char userWord[MAX_LENGTH];
    char tempWord[2];
    char checkLetters[MAX_LENGTH];
    char letter;
    char temp;
    char response;
    int i,n,length,guesses,wordsLeft,k;
    static int j, counter;
    j = counter = 0;
    bool check;

    guesses = 0;

    srand(time(NULL)); //Seed the random number generator

    n = rand()%WORDS;  //Pick a random word between 0 - 852

    strcpy(word,list[n]); //Copy elements of list to word

    length = strlen(word); //Find length of the word

    wordsLeft = length;

    //Loop to fill userWord array with underscore character and display it on screen
    for(i = 0; i < length; i++)
    {
        userWord[i] = '_';
        printf("%c ",userWord[i]);
    }

    do
    {

        //Set boolean value to false and get a character
        check = false;
        printf("\n\nEnter a char: ");
        letter = getchar();
        fflush(stdin);

        //Loop to ensure to that user does not select a letter they have selected before
        for(i = 0; i < length; i++)
        {
            fflush(stdin);
            if(letter == checkLetters[i])
            {
                puts("You have already entered this letter");
                puts("Enter a different letter: ");
                temp = getchar();
                    printf("%c,  %c ", temp, letter);
            Loop: while(temp == letter)
                  {
                    fflush(stdin);
                    puts("You have already entered this letter");
                    puts("Enter a different letter: ");
                    temp = getchar();
                  }
                  letter = temp;
                //A loop again to ensure that the user does not select any letter they have selected before with the use of goto
                  for(k = 0; k < length; k++)
                  {
                      //If letter is in the array then go back and get a different letter
                      if(letter == checkLetters[k])
                        goto Loop;
                  }
                break; //Jump out of the loop once the checking has been done
            }
        }

        for(i = 0; i < length; i++) //Loop to the length of the word
        {
            if(letter == word[i])
            {
                checkLetters[j] = letter; //Array to ensure user does not select the same letter with the use of a static variable j
                userWord[i] = letter;  //Store the letter inside the user array
                check = true; //Set boolean flag to be true
                wordsLeft--; //Decrement words left
                counter++; //Increment static counter
                j++;
            }

        }

        if(check == true) //If a letter is contained in the word
        {
            puts("You are correct !!!");

            if(wordsLeft > 0)
            printf("\nYou have %d to go",wordsLeft); //Display the amount of words left for user to find

            if(counter == length) //If the user has entered the complete word
            {
                puts("\nYou have won the game");
                    break; //Jump out of the loop as the user has finished
            }

        }

        if(check == false) //If the user enters the wrong letter
        {
            puts("wrong");
            display(guesses); //Show the current hangman
            guesses++; //Increment for each time the user enters a wrong letter
        }

        printf("\n");
        //Loop to show the users array
        for(i = 0; i < length; i++)
            printf("%c ",userWord[i]);

    }while(guesses < 5); //Loop while guesses < 5

    if(guesses == 5) //Display the man hanged if guesses equals five
    {
        printf("\n");
        puts("You have missed too many guesses and you have been hanged :-(");
        display(6);
        printf("\nThe word was: "); //Tell the user the word
        puts(word);
    }

    free(list); //Free memory allocated

    puts("\n\nDo you want to play again ? (y/n)"); //Ask if the user wants to play again
    scanf("%c",&response);

    response = tolower(response); //Set the users response to lowercase

    if(response == 'y')
    {
        main(); //Start the game again
    }
}

//Function to add words to the array
void addWords(char *list[])
{
    //Declare pointers and variables
  int i, count;
  FILE *fp;

    //Set the pointer to the file words.txt as well as error check
   if((fp = fopen("words.txt","r")) == NULL)
        puts("Error in opening file");
   else
   {

        for (i = 0; i < WORDS; i++)
        {
            list[i] = malloc (128); /* allocate a memory slot of 128 chars */

            if(list == NULL) //If allocation of memory failed
                puts("Cannot allocate memory");
            else
              fscanf(fp, "%127s", list[i]); //Read each word from the file and store inside the array
        }
   }
       fclose(fp);
}

//Function to display current state of the hangman
void display(int num)
{
    switch(num)
    {
        //First wrong guess
        case 0:
                puts("_______________");
                puts("|             |");
                puts("|");
                puts("|");
                puts("|");
                puts("|");
                puts("|");
                puts("|");
                puts("|______________");
                break;
        //Second wrong guess
        case 1:
                puts("_______________");
                puts("|             |");
                puts("|             O");
                puts("|");
                puts("|");
                puts("|");
                puts("|");
                puts("|");
                puts("|______________");
                break;
        //Third wrong guess
        case 2:
                puts("_______________");
                puts("|             |");
                puts("|             O");
                puts("|             |");
                puts("|");
                puts("|");
                puts("|");
                puts("|");
                puts("|______________");
                break;
        //Fourth wrong guess
        case 3:
                puts("_______________");
                puts("|             |");
                puts("|             O");
                puts("|            /|");
                puts("|");
                puts("|");
                puts("|");
                puts("|");
                puts("|_______________");
                break;
        //Fifth wrong guess
        case 4:
                puts("_______________");
                puts("|             |");
                puts("|             O");
                puts("|            /|\\");
                puts("|");
                puts("|");
                puts("|");
                puts("|");
                puts("|_______________");
                break;
        //Sixth wrong guess
        case 5:
                puts("_______________");
                puts("|             |");
                puts("|             O");
                puts("|            /|\\");
                puts("|            /");
                puts("|");
                puts("|");
                puts("|");
                puts("|______________");
                break;
        //Seventh wrong guess and man is hung
         case 6:
                puts("_______________");
                puts("|             |");
                puts("|             O");
                puts("|            /|\\");
                puts("|            / \\");
                puts("|");
                puts("|");
                puts("|");
                puts("|______________");
                break;

        default:
            puts("Invalid input");
    }
}

//Display menu screen
void menu()
{
    system("cls");
    puts("##     ##    ###    ##    ##  ######   ##     ##    ###    ##    ##");
    puts("##     ##   ## ##   ###   ## ##    ##  ###   ###   ## ##   ###   ##");
    puts("##     ##  ##   ##  ####  ## ##        #### ####  ##   ##  ####  ##");
    puts("######### ##     ## ## ## ## ##   #### ## ### ## ##     ## ## ## ##");
    puts("##     ## ######### ##  #### ##    ##  ##     ## ######### ##  ####");
    puts("##     ## ##     ## ##   ### ##    ##  ##     ## ##     ## ##   ###");
    puts("##     ## ##     ## ##    ##  ######   ##     ## ##     ## ##    ##");
    rules();
    getchar();
}

//Function to display the rules of the game
void rules()
{
    printf("\n\tInstructions");
    printf("\n\t____________");
    printf("\n\t -->  Enter a letter you think the invisible word contains.\n");
    printf("\n\t -->  If the letter is correct, it will be displayed.\n");
    printf("\n\t -->  If you are wrong, your get one step closer to hanging the man.\n");
    printf("\n\t -->  If the man is hung, you lose the game.\n");
    printf("\n\t -->  If you get five wrong guesses the man will be hanged.\n");
    printf("\n\t -->  Will you be the one to save him ?\n");
}
