// Tic-Tac-Toe game, with various difficulty modes. In difficult mode Computer does decision making with, predictive analysis, some calculations and some predefined moves, before making a move.



#include <stdio.h>
#include <stdlib.h> //it provides srand() and rand() functions for generating computer input
#include <time.h>   //it provides time() function

int input(char q[3][3]);
int randomness(int n); // for generating random input values for computer
int algo(char q[3][3]);

int x = 0;   // x checks winnings and draws and also keeps check of the turn number;
int move[9]; // Stores history of moves    // X is stored in 0,2,4,8

int main()
{
    printf("\n\n\n\nWELCOME TO TIC-TAC-TOE:\n\n ");
    char type; //   type asks for player or computer match;
    
    new_game:

    { // OUTER LOOP BEGINS

        printf("\nFOR Player vs Player match:-     ENTER: '0'\nFOR Player vs Computer match:-  (Easy mode): ENTER '1': || (Moderate mode): ENTER '2': || (Difficult mode) ENTER: 'ANYTHING ELSE'\n=> ");
        scanf("%c", &type); // Asks for match type, type 0= p vs p; type 1= player vs computer(easy mode); type 2= player vs compuer(moderate mode); type (anything else)= player vs computer (hard mode)
        getchar();

        char p[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
        printf("\n\n\n %c | %c | %c \n---+---+---\n %c | %c | %c \n---+---+---\n %c | %c | %c \n", p[0][0], p[0][1], p[0][2], p[1][0], p[1][1], p[1][2], p[2][0], p[2][1], p[2][2]);
        int y = 0, i, j, a = 0, b = 0, c = 0; //  y checks for illegal move/invalid input;  a,b,c are used for checking the conditions of winning
        int ch, mv = 0;                       // ch stores choice of position, mv is used as increament operator for storing history in move array

        while (x != 999 && x != 1000 && x != 9) // if x==999: Player 1 wins;  if x==1000: Player 2 wins;  if x==9: DRAW
        {
        // INPUT FROM PLAYER 1
        {
        again1:
            printf("\nPLAYER 1 (X) :- Enter the number to mark the position : ");
            scanf("%d", &ch);
            getchar();
            if (ch < 1 || ch > 9)
            {
                printf("INVALID INPUT");
                goto again1;
            }
            ch = ch + 48;
            for (i = 0; i < 3; i++)
                for (j = 0; j < 3; j++)
                    if (ch == p[i][j])
                    {
                        p[i][j] = 'X';
                        y = 1;
                    }
            if (y == 0)
            {
                printf("ILLEGAL MOVE");
                goto again1;
            }
            y = 0;
            move[mv] = ch - 48;
            mv += 2;
            }

            // DISPLAY OF PROGRESS of player1
            printf("\n\n %c | %c | %c \n---+---+---\n %c | %c | %c \n---+---+---\n %c | %c | %c \n", p[0][0], p[0][1], p[0][2], p[1][0], p[1][1], p[1][2], p[2][0], p[2][1], p[2][2]);

            // Checking if  X wins
            for (i = 0; i < 3; i++)
            {
                for (j = 0; j < 3; j++)
                {
                    if (p[i][j] == 'X')
                        a++;
                    if (p[j][i] == 'X')
                        b++;
                }
                if (p[i][i] == 'X')
                    c++;
                if (a == 3 || b == 3 || c == 3)
                {
                    x = 999;
                    goto result;
                }
                a = b = 0;
                if (p[0][2] == 'X' && p[1][1] == 'X' && p[2][0] == 'X')
                {
                    x = 999;
                    goto result;
                }
            }

            a = b = c = 0;
            x++;
            if (x == 9)
                continue; // if x==9 then the game has drawn and thus the command line skips the further code

                
            // INPUT FROM PLAYER 2 or COMPUTER
            
            if (type == '0')       // PLAYER INPUT STARTS
            { 
            again2:
                printf("\nPLAYER 2 (o) :- Enter the number to mark the position : ");
                scanf("%d", &ch);
                getchar();
                if (ch < 1 || ch > 9)
                {
                    printf("INVALID INPUT");
                    goto again2;
                }
                ch = ch + 48;
                for (i = 0; i < 3; i++)
                    for (j = 0; j < 3; j++)
                        if (ch == p[i][j])
                        {
                            p[i][j] = 'o';
                            y = 1;
                        }
                if (y == 0)
                {
                    printf("ILLEGAL MOVE");
                    goto again2;
                }
                y = 0;
            } // PLAYER 2 INPUT ENDS

            else if (type == '1')   // easy mode input starts
            {
                printf("\nCOMPUTER's (o) TURN");
                help_random:   // this comes from moderate mode for first random value
            again3:
                ch = randomness(9);
                ch = ch + 48;
                for (i = 0; i < 3; i++)
                    for (j = 0; j < 3; j++)
                        if (ch == p[i][j])
                        {
                            p[i][j] = 'o';
                            y = 1;
                        }
                if (y == 0)
                {
                    goto again3;
                }
                y = 0;
            }
            

            else if(type=='2')      // medium mode input starts
            {   
                printf("\nCOMPUTER's (o) TURN");
                if(x==1)
                   goto help_random;               // this helps to mark first value randomly
                algo(p);            // in moderate mode the predesigned decisions are bypassed, making the match easier for player and unpredictable for the computer 
            }   // medium mode input ends

            
            else                    // difficult mode input starts
            { 
                printf("\nCOMPUTER's (o) TURN");
                input(p);
            }
            // COMPUTER INPUT ENDS
            
            // INPUT FROM PLAYER 2 ENDS

            // DISPLAY OF PROGRESS of player 2
            printf("\n\n\n %c | %c | %c \n---+---+---\n %c | %c | %c \n---+---+---\n %c | %c | %c \n", p[0][0], p[0][1], p[0][2], p[1][0], p[1][1], p[1][2], p[2][0], p[2][1], p[2][2]);

            // to create clear separation between two rounds
            printf("---------------------------------------------------------------");

            // Checking if  Y wins
            for (i = 0; i < 3; i++)
            {
                for (j = 0; j < 3; j++)
                {
                    if (p[i][j] == 'o')
                        a++;
                    if (p[j][i] == 'o')
                        b++;
                }
                if (p[i][i] == 'o')
                    c++;
                if (a == 3 || b == 3 || c == 3)
                {
                    x = 1000;
                    goto result;
                }
                a = b = 0;
            }
            if (p[0][2] == 'o' && p[1][1] == 'o' && p[2][0] == 'o')
            {
                x = 1000;
                goto result;
            }
            a = b = c = 0;
            x++;
        }

    result: // results being displayed
        if (x == 999)
            printf("\n\nPLAYER 1(X): WON!!!\n\n");
        else if (x == 1000)
        {
            if (type == '0')
                printf("\n\nPLAYER 2(o): WON!!!\n\n");
            else
                printf("\n\nCOMPUTER(o): WON!!!\n\n");
        }
        else
            printf("\n\nTHE GAME WAS A DRAW!!!\n\n");

        printf(" \n\n\n");
    }
    // outer loop exit
    printf("GOODBYE!  SEE YOU AGAIN...\n                                                                             ||PRESS 'ENTER' FOR NEW GAME||\n");
    
   
    getchar();      // reinitializes the game
    x = 0;  
    int move[9];    //reinitialised here for fresh values
    system("clear");  // clears out the terminal, for a fresh new game
    goto new_game;
    return 0;
}

int input(char q[3][3]) // Provides input for computer in difficult mode
{
    int i, j, k, l = 0, a, b, c;
    char *pt = q[0], *t[9];

    for (i = 0; i < 9; i++)
    {
        t[i] = pt;
        pt++;
    }

    if (x == 1) // 1st move
    {

        // middle case
        if (move[1 - 1] == 5) // Signifies middle position = 'X'
        {
            int arr[] = {1, 3, 7, 9};
            k = arr[randomness(4) - 1]; // introduces some randomness for a playful game
            *t[k - 1] = 'o';
            return 0;
        }

        // corner's case
        if (move[0] == 1 || move[0] == 3 || move[0] == 7 || move[0] == 9)
        {
            *t[4] = 'o';
            return 0;
        }

        //(side middle's) case
        if (move[0] == 2 || move[0] == 4 || move[0] == 6 || move[0] == 8)
        {
            *t[4] = 'o';
            return 0;
        }
    }

    if (x == 3) // 2nd move
    {

        // Middle case begins
        if (move[1 - 1] == 5)
        {

            if (move[2] == 1 || move[2] == 3 || move[2] == 7 || move[2] == 9) // if move 2(x) is at corner positions
            {
                for (i = 0; i < 3; i++) // This snippet checks if x-x-_ exists in prime diagonal;
                {
                    if (q[i][i] == 'X')
                        l++;
                }
                if (l == 2)
                {
                    for (i = 0; i < 3; i++)
                    {
                        if (q[i][i] < 65) // 65 here refers to the ascii code of 1st alphabet, if it is less than this 65, it means that position is occupied by an integer character; Thus fulfilling our required condition
                        {
                            q[i][i] = 'o';
                            return 0;
                        }
                    }
                }
                l = 0;

                // similarily has to be done for other diagonal too
                if (q[0][2] == 'X')
                    l++;
                if (q[1][1] == 'X')
                    l++;
                if (q[2][0] == 'X')
                    l++;

                if (l == 2)
                {
                    if (q[0][2] < 65) // 65 here refers to the ascii code of 1st alphabet, if it is less than this 65, it means that position is occupied by an integer character; Thus fulfilling our required condition
                    {
                        q[0][2] = 'o';
                        return 0;
                    }
                    if (q[1][1] < 65)
                    {
                        q[1][1] = 'o';
                        return 0;
                    }
                    if (q[2][0] < 65)
                    {
                        q[2][0] = 'o';
                        return 0;
                    }
                }

                // if the x doesnt form winning move then
                if (*t[1 - 1] == '1')
                    *t[0] = 'o';
                else if (*t[3 - 1] == '3')
                    *t[2] = 'o';
                else if (*t[7 - 1] == '7')
                    *t[6] = 'o';
                else if (*t[9 - 1] == '9')
                    *t[8] = 'o';
                return 0;
            }
            else
            {
                algo(q); // contains core algorithm
                return 0;
            }
        }
        // middle case ends

        a = b = c = 0;

        // corner's case
        if (move[0] == 1 || move[0] == 3 || move[0] == 7 || move[0] == 9)
        {

            // if second move also placed at corner
            if (move[2] == 1 || move[2] == 3 || move[2] == 7 || move[2] == 9)
            {

                // checking if the second mark of player, is not adjacent corner, (if adjacent then algo())
                {
                    for (i = 0; i < 3; i++)
                    {
                        for (j = 0; j < 3; j++)
                        {
                            if (q[i][j] == 'X')
                                a++;
                            if (q[j][i] == 'X')
                                b++;
                        }
                        if (a > 1 || b > 1)
                            c = 99;
                        a = b = 0;
                    }
                }

                if (c == 0) // second marking is not adjacent corner
                {
                    int arr[] = {2, 4, 6, 8};
                    k = arr[randomness(4) - 1]; // introduces some randomness for a playful game
                    *t[k - 1] = 'o';
                    return 0;
                }
                else // second marking is adjacent corner
                {
                    algo(q);
                    return 0;
                }
            }

            // if second move is placed at middle of sides
            else if (move[2] == 2 || move[2] == 4 || move[2] == 6 || move[2] == 8)
            {

                // checking for non-adjacent markings  (if adjacent then algo())
                {
                    a = b = c = 0;
                    for (i = 0; i < 3; i++)
                    {
                        for (j = 0; j < 3; j++)
                        {
                            if (q[i][j] == 'X')
                                a++;
                            if (q[j][i] == 'X')
                                b++;
                        }
                        if (a > 1 || b > 1)
                            c = 99;
                        a = b = 0;
                    }
                }

                if (c == 0) // only curated non-adjacent middle side marking
                {
                help: // comes from(side middle case)
                    a = b = 0;

                    for (i = 0; i < 3; i += 2) //(PART 1) Checks the (first row and first column) and (third row and third column) for right marking position
                    {
                        a = b = 0;

                        for (j = 0; j < 3; j++)
                        {
                            if (q[i][j] == 'X')
                                a++;

                            if (q[j][i] == 'X')
                                b++;
                        }
                        if (a == 1 && b == 1) // marks the desired location
                        {
                            for (j = 0; j < 3; j++)
                            {
                                if (q[i][j] == '1' || q[i][j] == '3' || q[i][j] == '7' || q[i][j] == '9')
                                {
                                    q[i][j] = 'o';
                                    return 0;
                                }
                            }
                        }
                    }

                    for (i = 0; i < 3; i += 2) //(PART 2) Checks the (first row and third column) and (first row and third column) for right marking position
                    {
                        a = b = 0;

                        for (j = 0; j < 3; j++)
                        {
                            if (i == 0)
                            {

                                if (q[i][j] == 'X')
                                    a++;
                                if (q[j][i + 2] == 'X')
                                    b++;
                            }
                            else if (i == 2)
                            {
                                if (q[i][j] == 'X')
                                    a++;

                                if (q[j][i - 2] == 'X')
                                    b++;
                            }
                        }
                        if (a == 1 && b == 1) // marks the desired location
                        {
                            for (j = 0; j < 3; j++)
                            {
                                if (q[i][j] == '1' || q[i][j] == '3' || q[i][j] == '7' || q[i][j] == '9')
                                {
                                    q[i][j] = 'o';
                                    return 0;
                                }
                            }
                        }
                    }
                }
                else // this condition marks adjacent marking
                {
                    algo(q);
                    return 0;
                }
            }
            else
            {
                algo(q);
                return 0;
            }
            // ENTIRE CONDITION FOR CORNER MOVE ENDS
        }

        //(SIDE MIDDLE's) case
        if (move[0] == 2 || move[0] == 4 || move[0] == 6 || move[0] == 8)
        {

            // Checking just adjacent marking and opposite side middle marking
            for (i = 0; i < 3; i++)
            {
                a = b = 0;
                int a1 = 0, b1 = 0;
                for (j = 0; j < 3; j++)
                {
                    if (q[i][j] == 'X')
                        a++;
                    if (q[j][i] == 'X')
                        b++;

                    if (q[i][j] == 'o')
                        a1++;
                    if (q[j][i] == 'o')
                        b1++;
                }
                if ((a == 2 && a1 == 1) || (b == 2 && b1 == 2)) // Checks for opposite side middle
                {
                    int arr[] = {0, 2, 6, 8};
                    k = arr[randomness(4) - 1];
                    *t[k] = 'o';
                    return 0;
                }
                if (a == 2 || b == 2) // checks for adjacent marking
                {

                    algo(q);
                    return 0;
                }
            }

            // Second move is at corners
            if (move[2] == 1 || move[2] == 3 || move[2] == 7 || move[2] == 9)
            {
                goto help;
                return 0;
            }

            int l1 = 999;
            // Second move is adjacent side middle position
            if (move[2] == 2 || move[2] == 4 || move[2] == 6 || move[2] == 8)
            {
                for (i = 0; i < 3; i++)
                {
                    a = b = 0;
                    for (j = 0; j < 3; j++)
                    {
                        if (q[i][j] == 'X')
                            a++;
                        if (q[j][i] == 'X')
                            b++;
                    }
                    if (a > 1 && b > 1)
                    {
                        l1 = 0;
                    }
                }
                if (l1 == 999)
                {
                    goto help;
                    return 0;
                }
                else
                {
                    algo(q);
                    return 0;
                }
            }

            // if anything else left out then
            algo(q);
            return 0;
        }
        //(SIDE MIDDLE's) case ends

        // if any case left out then
        algo(q);
        return 0;
    } // ENTIRITY OF SECOND MOVE CASES END

    algo(q);
    return 0;
}

int algo(char q[3][3]) // the core algorithm for computer input generation post analysis
{
    int i, j, k, a = 0, b = 0, c = 0;

    // This snippet checks if COMPUTER (o) is winning
    {
        for (i = 0; i < 3; i++)
        {

            for (j = 0; j < 3; j++)
            {
                if (q[i][j] == 'o')
                    a++;

                if (q[j][i] == 'o')
                    b++;

                if (a == 2) // checks 'o' duo horizontally
                {
                    for (k = 0; k < 3; k++)
                    {
                        if (q[i][k] < 65) // 65 here refers to the ascii code of 1st alphabet, if it is less than this 65, it means that position is occupied by an integer character; Thus fulfilling our required condition
                        {
                            q[i][k] = 'o';
                            return 0;
                        }
                    }
                }

                if (b == 2) // checks 'o' duo vertically
                {
                    for (k = 0; k < 3; k++)
                    {
                        if (q[k][i] < 65)
                        {
                            q[k][i] = 'o';
                            return 0;
                        }
                    }
                }
            }
            a = b = 0;

            if (q[i][i] == 'o')
                c++;

            if (c == 2)
            {
                for (k = 0; k < 3; k++)
                {
                    if (q[i][i] < 65)
                    {
                        q[i][i] = 'o';
                        return 0;
                    }
                }
            }
        }
        c = 0;

        // checks for non prime diagonal duo
        {
            if (q[0][2] == 'o')
                c++;
            if (q[1][1] == 'o')
                c++;
            if (q[2][0] == 'o')
                c++;

            if (c == 2)
            {
                if (q[0][2] < 65)
                {
                    q[0][2] = 'o';
                    return 0;
                }
                if (q[1][1] < 65)
                {
                    q[1][1] = 'o';
                    return 0;
                }
                if (q[2][0] < 65)
                {
                    q[2][0] = 'o';
                    return 0;
                }
            }
        }
    }
    // COMPUTER (o) winning test ends

    a = b = c = 0;

    // This snippet checks if OPPONENT is winning
    {
        for (i = 0; i < 3; i++)
        {

            for (j = 0; j < 3; j++)
            {
                if (q[i][j] == 'X')
                    a++;

                if (q[j][i] == 'X')
                    b++;

                if (a == 2) // checks 'X' duo horizontally
                {
                    for (k = 0; k < 3; k++)
                    {
                        if (q[i][k] < 65) // 65 here refers to the ascii code of 1st alphabet, if it is less than this 65, it means that position is occupied by an integer character; Thus fulfilling our required condition
                        {
                            q[i][k] = 'o';
                            return 0;
                        }
                    }
                }

                if (b == 2) // checks 'X' duo vertically
                {
                    for (k = 0; k < 3; k++)
                    {
                        if (q[k][i] < 65)
                        {
                            q[k][i] = 'o';
                            return 0;
                        }
                    }
                }
            }
            a = b = 0;

            if (q[i][i] == 'X')
                c++;

            if (c == 2)
            {
                for (k = 0; k < 3; k++)
                {
                    if (q[i][i] < 65)
                    {
                        q[i][i] = 'o';
                        return 0;
                    }
                }
            }
        }
        c = 0;

        // checks for non prime diagonal duo
        {
            if (q[0][2] == 'X')
                c++;
            if (q[1][1] == 'X')
                c++;
            if (q[2][0] == 'X')
                c++;

            if (c == 2)
            {
                if (q[0][2] < 65)
                {
                    q[0][2] = 'o';
                    return 0;
                }
                if (q[1][1] < 65)
                {
                    q[1][1] = 'o';
                    return 0;
                }
                if (q[2][0] < 65)
                {
                    q[2][0] = 'o';
                    return 0;
                }
            }
        }
    }
    // OPPONENT (x) winning test ends

    a = b = c = 0;

    // if the two upper tests fail then, the computer places the mark next to its one of the existing previous mark
    //'o' duo formation try begins
    {
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
            {
                if (q[i][j] == 'o')
                    a++;

                if (q[j][i] == 'o')
                    b++;

                if (a == 1) // checks 'o' horizontally
                {
                    for (k = 0; k < 3; k++)
                    {
                        if (q[i][k] < 65)
                        {
                            q[i][k] = 'o';
                            return 0;
                        }
                    }
                }

                if (b == 1) // checks 'o' vertically
                {
                    for (k = 0; k < 3; k++)
                    {
                        if (q[k][i] < 65)
                        {
                            q[k][i] = 'o';
                            return 0;
                        }
                    }
                }
            }
            a = b = 0;

            if (q[i][i] == 'o')
                c++;

            if (c == 1)
            {
                for (k = 0; k < 3; k++)
                {
                    if (q[i][i] < 65)
                    {
                        q[i][i] = 'o';
                        return 0;
                    }
                }
            }
        }
        c = 0;
        {
            if (q[0][2] == 'o')
                c++;
            if (q[1][1] == 'o')
                c++;
            if (q[2][0] == 'o')
                c++;

            if (c == 1)
            {
                if (q[0][2] < 65)
                {
                    q[0][2] = 'o';
                    return 0;
                }
                if (q[1][1] < 65)
                {
                    q[1][1] = 'o';
                    return 0;
                }
                if (q[2][0] < 65)
                {
                    q[2][0] = 'o';
                    return 0;
                }
            }
        }
    }
    //'o' duo formation try ends

    a = b = c = k = 0;

    // if non of the above conditions valid, then the computer, at last, places mark randomly
    {
        for (i = 0; i < 3; i++)
            for (j = 0; j < 3; j++)
            {
                if (q[i][j] < 65)
                    a++;
            }

        char arr[a];

        for (i = 0; i < 3; i++)
            for (j = 0; j < 3; j++)
            {
                if (q[i][j] < 65)
                    arr[b] = q[i][j];
                b++;
            }

        k = arr[randomness(a) - 1]; // introduces some randomness for a playful game

        for (i = 0; i < 3; i++)
            for (j = 0; j < 3; j++)
            {
                if (q[i][j] == (k+48))
                {
                    q[i][j] = 'o';
                    return 0;
                }
            }
    }
    return 0;
}

int randomness(int n) // generates random value from (1 to n), (in case of computer 1 to 9)
{
    int r;
    srand(time(NULL));  // srand() seeds rand() with time(NULL), which returns current time in form of total no. of seconds since 1970(its date of inception)                              // with the seed value of time(), rand() generates and stores random values in r, till the given range.
    r = rand() % n + 1; // rand()%n+1 returns random values in range from(1 to n);   IN CASE OF EASY MODE INPUT (1 TO 9)
    return r;
}