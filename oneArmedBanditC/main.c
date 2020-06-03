#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//The 3 wheels on the Slot Machine
char *sMLeft[] = {"BAR","C","B","P","A","A","G","L","O","L"};
char *sMMiddle[] = {"BAR","C","C","B","B","P","A","G","O","L"};
char *sMRight[] = {"BAR","C","C","C","B","P","A","G","O","O"};

//Game result
char *result[3];
//Circular pointer
int circ = 0;

//This method handles if the result is a win or not
int testForPrize(int paid){

        if((result[0] == result[1]) && (result[1]== result[2]) && (result[2] == "BAR"))
            return paid * 50;
        else if((result[0] == result[1]) && (result[1]== result[2]) && (result[2] == "G"))
                return paid * 24;
            else if((result[0] == result[1]) && (result[1]== result[2]) && (result[2] == "P"))
                    return paid * 24;
                else if((result[0] == result[1]) && (result[1]== result[2]) && (result[2] == "A"))
                        return paid * 18;
                    else if((result[0] == result[1]) && (result[1]== result[2]) && (result[2] == "B"))
                            return paid * 16;
                        else if((result[0] == result[1]) && (result[1]== result[2]) && (result[2] == "C"))
                                return paid * 12;
                            else if((result[0] == result[1]) && (result[1]== result[2]) && (result[2] == "O"))
                                    return paid * 10;
                                else if( (result[1] == result[2]) && (result[2] == "B"))
                                        return paid * 8;
                                    else if((result[1] == result[2]) && (result[2] == "C"))
                                            return paid * 8;
                                        else if(result[2] == "C")
                                                return paid * 2;
                                            else return 0;

    }

//This method handles the amount of money that will be spent on a round
int enterPayment(int credit){
    printf("Your total credit is: %d\nPlease select the amount you want to play with\n", credit);
    char *end;
    char buf[9];
    int paid;
    bool ok;
    // the following code makes sure thaat the value added by the user is correct
    do {
        ok = true;
        do {
             printf("Please enter a number: ");
             if (!fgets(buf, sizeof buf, stdin))
                break;

             // remove \n
             buf[strlen(buf) - 1] = 0;

             paid = strtol(buf, &end, 10);
             fflush(stdin);
        } while (end != buf + strlen(buf));
        if(paid <= 0)
            printf("Please enter a positive number or higher than 0: ");
        else if(paid > credit)
            printf("This number exceeds your total credit, please enter a different value: ");
        else ok = false;
    }while(ok);

    printf("\nYou entered: %d\n", paid);

    return paid;
}

//Selects a random number from each of the 3 wheels
void spinTheWheels(){

        circ += rand() % 10;
        if(circ > 9)
            circ -= 10;

        //i is circular pointer
        int* i = &sMLeft[0];

        result[0] = *(i+circ);

        circ += rand() % 10;
        if(circ > 9)
            circ -= 10;

        i = &sMMiddle[0];
        result[1] = *(i+circ);

        circ += rand() % 10;
        if(circ > 9)
            circ -= 10;

        i = &sMRight[0];
        result[2] = *(i+circ);

        printf("%s - %s - %s\n", result[0],result[1],result[2]);
    }

//Main method
int main()
{
    //Creates a time seed for rand()
    srand(time(NULL));

    //Account balance
    int credit = 10;

    //Repeat the game
    bool ok;

    //Game loop
    do {
        ok = false;

        int paid = enterPayment(credit);
        printf("Press enter to start the the game");
        getchar();
        credit -= paid;

        for(int j = 0; j < 6; j++){
            spinTheWheels();
            sleep(1);
        }

        printf("And the result is:\n");
        printf("%s - %s - %s\n", result[0],result[1],result[2]);

        credit = credit + testForPrize(paid);
        printf("\nYour new credit is: %d\n",credit);

        if(credit != 0){
            printf("\nTo play another round press 'y', to stop press enter");
            if(getchar() == 'y'){
                //Play another round
                ok = true;
                //Clears input buffer
                fflush(stdin);
            }
        } else printf("\nYou ran out of credit, Game over");

    }while(ok);

    printf("\nTotal amount of cashout: %d\n",credit);


    return 0;
}
