// Johana Di Girolamo 
// Term Project

#include<iostream>
#include<cstdlib>

#include<cctype> //tolower
#include<locale> //tolower

using namespace std;

struct board
{
    int round;
    char guesses[8][4];
};


//level 1
void puzzleGame();
void printPuzzle(char [][39], int, int, int, int);

//level 2
bool levelTwo();
bool questions(string question, string correctAnswer, int &tries);

//this is used for making sure the puzzle is done correctly
bool validMove(char[][39], int, int, int);

//level 3
void unscrambleWords();

//level 4
bool masterMind();
void printMasterBoard(char input[], int size, int correct[], int almostCorrect[], int round, const board &printBoard);


//level 5
void finalLevel();


int main()
{
    char playing;

    //this is the intro to the game
    cout << "Welcome to puzzle game by Johana Di Girolamo!" << endl;
    cout << endl << "You really want to get an A in your Computer Science class that you currently have a B+ in, ";
    cout << endl << "so your professor gives you a set of challenges to complete in order for him to bump your ";
    cout << endl << "grade to an A!" << endl;

    cout << "Do you take the challenge? (Y/N) [Warning: Saying no will quit the game] ";
    cin >> playing;

    //if they pick Y or y, then the game will continue
    //if they pick N or n, then game ends
    //if they pick any other letter, it is safe to assume they mistyped so they will be asked again
    while(playing != 'Y' && playing != 'y' && playing != 'n' && playing != 'N')
    {
        cout << "Please pick either Y or N : ";
        cin >> playing;
    }
    if(playing == 'N' || playing == 'n')
    {
        cout << "Professor: Sorry to see you go... You were very capable of getting that A!" << endl;
        return 0;                           //this will end main immediately
    }

    //taking the challenge
    cout << endl << "Professor: I see you want a good grade in the class!" << endl;
    cout << "You will go through a series of puzzles. Upon completion of a puzzle, you will" << endl;
    cout << "get 2 letters. These letters will be presented to you in the final level, and you" << endl;
    cout << "will have to guess the secret phrase (made up of those letters) to complete the challenge!" << endl;

    cout << endl << "For your first challenge, you will have to complete a maze.. Good luck!" << endl;

    //level one
    puzzleGame();

    //level 2
    if(!levelTwo()) //false = they failed
        return 0;

    //level 3
    unscrambleWords();

    //level 4; masterMind
    if(!masterMind())
        return 0;

    //level 5 FINAL LEVEL!! :D
    finalLevel();

    cout << endl << "Professor: Good job! I knew you could do it. You now have an A in the class... Next time, just do good in the class" << endl;
    cout << "instead of depending on extra credit! And turn in your stuff in time!!! Have a good Winter Break" << endl;

}


void puzzleGame()
{
    //we need to make the array of the maze
    //this was originally made in another text and then transfered to be put into individual chars
    //I soon after learned that they could be put under "" without having to add the commas
    //but it was too late... :(

    int rows = 16;
    int cols = 39;

    char maze[16][39] = {{'/','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','\\'},
                         {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ','|',' ',' ',' ','|',' ','|',' ',' ','|','-','|',' ',' ',' ','|'},
                         {'|',' ','|','-','|','_','_','_','|',' ','|','-','-','-','-','-','-','-','-','-','|',' ','-','|',' ','|','-','|',' ','|','-','-','|',' ','|',' ',' ',' ','|'},
                         {'|','_','|',' ','|',' ',' ',' ','|',' ','|','-','-','-','|',' ',' ',' ',' ',' ','|',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ','|'},
                         {' ',' ',' ',' ',' ',' ','|',' ','|',' ',' ',' ',' ',' ',' ',' ','|','-','|',' ','|','-','-','|',' ','|','-','|',' ','|','-','-','|',' ','|',' ',' ',' ','|'},
                         {'|','-','-','-','|',' ','|','-','|',' ','|','-','|','-','|',' ','|',' ','|',' ',' ',' ',' ',' ',' ','|',' ','|',' ','|',' ',' ',' ',' ','|','-','|',' ','|'},
                         {'|',' ',' ',' ','|',' ','|',' ','|',' ','|',' ','|',' ',' ',' ','|',' ','-','-','-','-','-','-','-','|',' ','|',' ','|','-','-','|',' ',' ',' ','|',' ','|'},
                         {'|','-','-','-','|',' ','|',' ','|',' ','|',' ','|',' ','|','-','|',' ','|',' ','|',' ',' ',' ',' ',' ',' ','|',' ','|',' ',' ','|',' ','|','-','|',' ','|'},
                         {'|',' ',' ',' ',' ',' ','|',' ','|','_','_','_','|',' ','|','_','|',' ','|','-','|',' ','|','_','_','|',' ','|',' ','|','-','-','|',' ','|',' ','-','-','|'},
                         {'|',' ','|','-','-','-','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ','|',' ',' ',' ',' ',' ',' ','|',' ','|',' ','|'},
                         {'|',' ','|','_','_','_','|',' ','|','-','-','|','-','-','-','-','-','-','|',' ','|',' ','|','-','-','|',' ','|',' ','|','-','-','|',' ','|','-','|',' ','|'},
                         {'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ','|',' ',' ',' ',' ',' ','|'},
                         {'|','-','-','|',' ','|','-','-','|',' ',' ','|',' ','|','-','-','-','-','|',' ','|','-','-','-','-','|','-','|','-','-','|',' ','|','-','-','-','-','-','|'},
                         {'|',' ',' ','|',' ','|','_','_','_','_','_','|','_','_','_','_','_','_','_','_','_','_','_','_','_','|',' ',' ',' ',' ',' ',' ','|','-','-','-','-','-','|'},
                         {'|',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ','|','-','-','|',' ',' ',' ',' ',' ',' ',' ',' '},
                         {'\\','-','-','|','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','|','-','|',' ',' ','|','-','-','-','-','-','-','-','/'}};
    //with the maze set, we need to initialize the starting point to be at [4][0], and they cannot go below or above 0-39 && 0-16
    int r = 4;
    int c = 0;

    int turns = 0;
    char userMove;

    //this is no longer enabled because user wouldnt be able to read prof's instructions
    //so it'll start getting cleared after the first input
    //system("CLS");
    printPuzzle(maze, rows, cols, r, c);

    do
    {

        cout << "Enter the direction in which you want to go" << endl;
        do
        {
            cout << "[W A S D] or [< ^ v >] & Not out of Bounds: ";
            cin >> userMove;
        }while(!validMove(maze, r, c, userMove));

        //this will make a check on what the move was in order to make the
        //move on the screen. [rather, moves the location of the X and then
        //afterwards showcased a move on the screen]
        if(userMove == 'w' || userMove == '^' || userMove == 'W')
            r--;
        else if(userMove == 'a' || userMove == '<' || userMove == 'A')
            c--;
        else if(userMove == 's' || userMove == 'v' || userMove == 'S' || userMove == 'V')
            r++;
        else if(userMove == 'd' || userMove == '>' || userMove == 'D')
            c++;

        //this will clear the screen so that the maze will always stay at the top of the screen.
        system("CLS");
        // This will show the updated maze on the screen
        printPuzzle(maze, rows, cols, r, c);

        // we are keeping track of the turns so that the user can see how well or bad they did
        // [has nothing to do with the game, just a neat feature. If I had more time on this
        // i could make it so that the amount of bonus points the user receives is based upon
        // how many turns they make + other features included in the other levels, but due to
        // time constrains, I will keep it like this.]
        turns++;

    }while/*(r != 4 || c != 1); this was used for testing so that the maze would end early*/(r != 14 || c != 38);        //this is all under a loop UNTIL the X reaches the final location

    cout << "You completed the maze in " << turns << " amount of turns! [77 is the lowest amount of turns to complete!]" << endl;

    //the letters will be used in the final level
    cout << endl << "Professor: Good job completing the maze! Your two letters for completing this 1st level are 'G' and 'O'" << endl << endl;

}

void printPuzzle(char maze[][39], int rows, int cols, int xRow, int xCol)
{

     /*  /-------------------------------------\
    **   |                      | | | |  |-|   |
    **   | |-|___| |---------| -| |-| |--| |   |
    **   |_| |   | |---|     |  |          |   |
    **->       | |       |-| |--| |-| |--| |   |
    **   |---| |-| |-|-| | |      | | |    |-| |
    **   |   | | | | |   | -------| | |--|   | |
    **   |---| | | | | |-| | |      | |  | |-| |
    **   |     | |___| |_| |-| |__| | |--| | --|
    **   | |---|                  | |      | | |
    **   | |___| |--|------| | |--| | |--| |-| |
    **   |       |  |        |      |    |     |
    **   |--| |--|  | |----| |----|-|--| |-----|
    **   |  | |_____|_____________|      |-----|
    **   |  |                     | |--|          ->
    **   \--|---------------------|-|  |-------/
    */

    for(int r = 0; r < rows; r++)
    {
        for(int c = 0; c < cols; c++)
        {
            if(r == xRow && c == xCol)
                cout << "X";
            else
                cout << maze[r][c];
        }
        cout << endl;
    }



}

bool levelTwo()
{
    //professor's instructions
    cout << "Professor: For the next level, I will test your knowledge in this class.. Good luck answering all the questions!" << endl;
    cout << "You will have 3 tries to get it right... but you have 3 tries globally. Meaning if you get one wrong in the first" << endl;
    cout << "question, you will only have 2 tries left for the rest of the questions.. If you get them wrong, the challenge is over." << endl << endl;

    //I've only added this part so that the screen can be cleared [but not immediately]
    char ready;

    cout << "Are you ready to take the challenge? [Y/N] (Saying N will quit the game): ";
    do
    {
        cin >> ready;
        if(ready == 'N' || ready == 'n')
            return false;
    }while(ready!= 'Y' && ready != 'y');

    //want to clear the screen for beauty purposes
    system("CLS");

    int tries = 3;

    //these are all questions that all CS1428 students should know by the end of the year!! :D
    //they questions and answers are sent to a function so that the amount of code used isn't repeated.
    //tries is sent as reference because the return type is bool [continued with more that 0 tries left = true]
    if(!questions("Arrays are passed by ______ when sent to a function. Fill in the blank. ", "reference", tries))
        return false;

    cout << endl << "Correct!" << endl;
    cout << "Amount of Tries Left : " << tries << endl;

    if(!questions("What library is is needed for the std::rand() function? ", "cstdlib", tries))
        return false;

    cout << endl << "Correct!" << endl;
    cout << "Amount of Tries Left : " << tries << endl;

    if(!questions("A ____ variable is only seen within a function it's declared in. Fill in the blank. ","local",tries))
        return false;

    cout << endl <<"Correct! You have finished this level" << endl;
    cout << endl << "Professor: Good job completing the level 2! Your two letters for completing this level are 'D' and 'R'" << endl;
    return true;
}

bool questions(string question, string correctAnswer, int &tries) //right = true, wrong = false
{
    //this is repeated code for each of the questions
    cout << question;
    string answer;

    do
    {
        cin >> answer;

        // cout << "Your answer is : " << answer << endl; //this line was used for testing purposes

        //here, we use "tolower" so that even if the user answers with random caps [i.e. rEfErenCe] then
        //it is still counted correct because they are graded upon knowing the answer and not on caps.
        for(int i = 0; i < answer.size(); i++)
        {
            answer[i] = tolower(answer[i]);
        }

        // cout << "Answer is now : " << answer << endl; //this line was used for testing purposes

        if(answer != correctAnswer)
        {
            tries--;
            if(tries == 0)
            {
                cout << "You have ran out of tries. The correct answer was " << correctAnswer << "... Good luck next time! :D";
                return false;
            }
            else
                cout << "[Tries Left: " << tries << "] Wrong, try again: ";
        }
        else    //they get it right
            break;

    }while(tries != 0);

    return true;
}

//this is used for the maze
bool validMove(char maze[][39], int r, int c, int userMove)
{
    //checks every attempt of the user's input to make sure they don't
    //go out of bounds or run into a wall!
    if(userMove == 'w' || userMove == '^' || userMove == 'W')
    {
        if(r - 1 < 0)
            return false;
        if(maze[r-1][c] != ' ')
            return false;
        return true;
    }
    else if(userMove == 'a' || userMove == '<' || userMove == 'A')
    {
        if(c - 1 < 0)
            return false;
        if(maze[r][c-1] != ' ')
            return false;
        return true;
    }
    else if(userMove == 's' || userMove == 'v' || userMove == 'S' || userMove == 'V')
    {
        if(r + 1 > 16)
            return false;
        if(maze[r+1][c] != ' ')
            return false;
        return true;
    }
    else if(userMove == 'd' || userMove == '>' || userMove == 'D')
    {
        if(c + 1 > 39)
            return false;
        if(maze[r][c+1] != ' ')
            return false;
        return true;
    }
    else
        return false;

    //it will only ever be a valid move when the input is wasd or <^v> and not out of bounds
}

void unscrambleWords()
{

    //I've only added this part so that the screen can be cleared [but not immediately]
    char ready;

    cout << "Professor: In this level, you will be presented with words, however the letters have been scrambled." << endl;
    cout << "Good luck making these words rights!!" << endl;

    cout << "Are you ready for the challenge? [Y/N] (Saying N will quit the game): ";
    do
    {
        cin >> ready;
        if(ready == 'N' || ready == 'n')
            return;
    }while(ready!= 'Y' && ready != 'y');

    //want to clear the screen for beauty purposes
    system("CLS");

    //game begins
    string input;
    string wordTwo;

    cout << "Unscramble [One Word]- troptpyoe :: "; //prototype


    //I will use similar code to check the answer in all lowercase
    //this loop will gather the answer, check if it's correct, then either
    //print it's correct, or not!
    do
    {
        cin >> input;
        for(int i = 0; i < input.size(); i++)
        {
            input[i] = tolower(input[i]);
        }
        if(input != "prototype")
            cout << "Wrong! Try Again: ";
    }while(input != "prototype");

    //want to clear the screen for beauty purposes
    system("CLS");

    cout << "Unscramble [Two Words]- pmeeratra isasnpg :: "; //parameter passing
    do
    {
        //since it's more than one word, there has to be two inputs.
        //works with just putting a space
        cin >> input;
        cin >> wordTwo;
        for(int i = 0; i < input.size(); i++)
        {
            input[i] = tolower(input[i]);
        }
        for(int i = 0; i < wordTwo.size(); i++)
        {
            wordTwo[i] = tolower(wordTwo[i]);
        }
        if(input != "parameter" || wordTwo != "passing")
            cout << "Wrong! Try Again: ";
    }while(input != "parameter" || wordTwo != "passing");

    //want to clear the screen for beauty purposes
    system("CLS");

    cout << "Unscramble [Two Words]- uncfoitn vlaodoringe :: "; //function overloading
    do
    {
        cin >> input;
        cin >> wordTwo;
        for(int i = 0; i < input.size(); i++)
        {
            input[i] = tolower(input[i]);
        }
        for(int i = 0; i < wordTwo.size(); i++)
        {
            wordTwo[i] = tolower(wordTwo[i]);
        }
        if(input != "function" || wordTwo != "overloading")
            cout << "Wrong! Try Again: ";
    }while(input != "function" || wordTwo != "overloading");

    //want to clear the screen for beauty purposes
    system("CLS");

    cout << "Unscramble [Three Words]- ilmtu-ldimesanoni yrarsa :: "; //multi-dimensional arrays
    do
    {
        //its three words, however there is a - connecting two of the words
        //so we still only get "2" inputs
        cin >> input;
        cin >> wordTwo;
        for(int i = 0; i < input.size(); i++)
        {
            input[i] = tolower(input[i]);
        }
        for(int i = 0; i < wordTwo.size(); i++)
        {
            wordTwo[i] = tolower(wordTwo[i]);
        }
        if(input != "multi-dimensional" || wordTwo != "arrays")
            cout << "Wrong! Try Again: ";
    }while(input != "multi-dimensional" || wordTwo != "arrays");

    system("CLS");

    //the game is over now [this level , at least] :D
    cout << "Professor: Good job completing this challenge. Your letters for this level are : 'S' and 'F'." << endl;

    //this function ends
    return;
}

bool masterMind()
{
    srand(time(0));
    //so all randomizations are purely random


    char ready;
    //this level is master mind.. :D
    cout << "Professor: I'm glad you have made it this far. You are very capable of getting the bonus points!" << endl;
    cout << "For this level you will need to use your mind. We will play MasterMind. I will select a pattern " << endl;
    cout << "of colors of marbles in a random order and you must be able to match the patterns through a lot of" << endl;
    cout << "critical thinking and some guessing. If you don't know how to play MasterMind, I recommend you look" << endl;
    cout << "it up now! Getting a 'o' means you have a marble in the correct spot. A '.' means you have the right" << endl;
    cout << "color in the board, just not in the correct position. Ready to take the challenge? [Y/N] ";

    do
    {
        cin >> ready;
        if(ready == 'N' || ready == 'n')
            return false;
    }while(ready!= 'Y' && ready != 'y');

    //want to clear the screen for beauty purposes
    system("CLS");

    //variables for this level
    char userColor; //this will be the color of their choice
    //  [R- red; B- blue; G- green; O- orange; P- Purple; Y- yellow]

    int userPlace;  //this will be in the position they desire 1-4 [0-3 in arrays]
    char submit;    //this is so they can pick when to submit their line of answers so that they can make changes if needed

    char answer[4];
    char input[4] = {' ', ' ', ' ', ' '};

    board printBoard;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            printBoard.guesses[i][j] = ' ';
        }
    }

    int randomNumber;
//this is where the answer will be randomized
// (this is what the user will try to guess)
    for(int i = 0; i < 4; i++)
    {
        randomNumber = rand()%6;

        // 0 IS RED
        if(randomNumber == 0)
            answer[i] = 'R';
        // 1 IS BLUE
        else if(randomNumber == 1)
            answer[i] = 'B';
        // 2 IS GREEN
        else if(randomNumber == 2)
            answer[i] = 'G';
        // 3 IS ORANGE
        else if(randomNumber == 3)
            answer[i] = 'O';
        // 4 IS PURPLE
        else if (randomNumber == 4)
            answer[i] = 'P';
        // 5 IS YELLOW
        else
            answer[i] = 'Y';
    }

    char pos1 = answer[0];
    char pos2 = answer[1];
    char pos3 = answer[2];
    char pos4 = answer[3];


    //this was used for testing purposes :D you may use it if you want to as well
    //cout << "answer: " << pos1 << pos2 << pos3 << pos4 << endl;

    bool gameWon = false;
    bool gameOver = false;

    //these are arrays bc correct and almost correct are different per round
    int correct[8] = {0};
    int almostCorrect[8] = {0};

    int round = 1;


    printMasterBoard(input, 4, correct, almostCorrect, round, printBoard);

    do
    {
        for(int i = 0; i < 4; i++)
        {
            input[i] = ' ';
        }
        do
        {
            //in here, we will do loops to make sure that the user inputs valid answers
            do
            {
                cout << "Where do you want to place your marble? [1,2,3,4] ";
                cin >> userPlace;
            }while(userPlace < 1 || userPlace > 4);

            //checking the colors as well
            do
            {
                cout << "What color do you want to place here? [R,B,G,O,P,Y] ";
                cin >> userColor;
            }while(userColor != 'R' && userColor != 'B' && userColor != 'G' && userColor != 'O' && userColor != 'P' && userColor != 'Y');

            input[userPlace-1] = userColor;

            //we want to print a rough draft of what their submission looks like
            cout << "< " << input[0] << " " << input[1] << " " << input[2] << " " << input[3] << " >" << endl;


            //however this is not final until it gets "submitted" to check with the actual answer
            cout << "Would you like to submit it like this? [Y/y for yes, anything else for no] ";
            cin >> submit;

        }while(submit != 'Y' && submit != 'y');

        // so that it clears and looks nice
        system("CLS");

        correct[round-1] = 0;
        almostCorrect[round-1] = 0;

        //this is the checking of how close or not they were in their submission
        bool checked[4] = {false};
        for(int i = 0; i < 4; i++)
        {
            if(input[i] == answer[i])
            {
                correct[round-1]++;
                checked[i] = true; //i would be the position
            }else if(input[i] == pos1 && checked[0] == false)
            {
                almostCorrect[round-1]++;
                checked[0] = true;
            }else if(input[i] == pos2 && checked[1] == false)
            {
                almostCorrect[round-1]++;
                checked[1] = true;
            }else if(input[i] == pos3 && checked[2] == false)
            {
                almostCorrect[round-1]++;
                checked[2] = true;
            }else if(input[i] == pos4 && checked[3] == false)
            {
                almostCorrect[round-1]++;
                checked[3] = true;
            }
        }


        // this is used for better work in the printing.
        printBoard.round = round;
        for(int i = 0; i < 4; i++)
        {
            printBoard.guesses[round-1][i] = input[i];
        }

        //sending it to the print
        printMasterBoard(input, 4, correct, almostCorrect, round, printBoard);

        //checking if game is over
        if(correct[round-1] == 4)
            gameWon = true;
        else if(round == 8)
            gameOver = true;
        //if it repeats, it'll add to the rounds
        else
            round++;
    }while(!gameOver && !gameWon);

    // if the game is won [means the game ended apart from the last round occurring]
    if(gameWon == true)
    {
        cout << "Professor: Good job winning! :D Here are the final letters you will need for the final level: 'A' & 'E'" << endl;
        return true; // true = win
    }

    cout << "Professor: I am sorry you couldn't win.... Sorry you couldn't get your extra credit." << endl;
    return false; // false = lost
}



void printMasterBoard(char input[], int size, int correct[], int almostCorrect[], int round, const board &printBoard)
{
    /*
    ---------
  8 |       | <>
  7 |       | <>
  6 |       | <>
  5 |       | <>
  4 |       | <>
  3 |       | <>
  2 |    G  | <o>
  1 |R B B G| <.>
    */

    cout << "  ---------" << endl;
    for(int i = 7; i >= 0; i--)
    {
        cout << " " << i+1 << "|" << printBoard.guesses[i][0] << " " << printBoard.guesses[i][1] << " " << printBoard.guesses[i][2] << " " << printBoard.guesses[i][3] << "|  <";
        for(int j = 0; j < correct[i]; j++)
            cout << "o";
        for(int k = 0; k < almostCorrect[i]; k++)
            cout << ".";

        cout << ">" << endl;
    }


}

void finalLevel()
{
    char ready;
    cout << "Ready for the final challenge? [Y/N] ";
    do
    {
        cin >> ready;
        if(ready == 'N' || ready == 'n')
            return;
    }while(ready != 'Y' && ready != 'y');

    system("CLS");

    cout << "Professor: You have completed all the puzzles. Now, you must think of a key phrase made up from the" << endl;
    cout << "letters you have gathered from completing the challenges. You can re-use letters as much as you want. Some aren't used." << endl;
    cout << "Your one hint : the phrase is made up of TWO WORDS!" << endl;

    string wordOne;
    string wordTwo;

    do
    {
        cout << "[Hint: TWO WORDS] You were given: 'G' 'O' 'D' 'R' 'S' 'F' 'A' 'E'. Guess: ";
        cin >> wordOne;
        cin >> wordTwo;

        for(int i = 0; i < wordOne.size(); i++)
        {
            wordOne[i] = tolower(wordOne[i]);
        }
        for(int i = 0; i < wordTwo.size(); i++)
        {
            wordTwo[i] = tolower(wordTwo[i]);
        }

        if(wordOne != "good" && wordTwo != "grades")
            cout << "Try Again" << endl;

    }while(wordOne != "good" && wordTwo != "grades");

    return;

//g o o d
//g r a d e s
//
//g o d r a d e s


}
