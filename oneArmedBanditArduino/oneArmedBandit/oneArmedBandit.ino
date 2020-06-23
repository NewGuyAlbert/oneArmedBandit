const char *sMLeft[] = {"BAR","C","B","P","A","A","G","L","O","L"};
const char* sMMiddle[] = {"BAR","C","C","B","B","P","A","G","O","L"};
const char *sMRight[] = {"BAR","C","C","C","B","P","A","G","O","O"};
char *result[3];

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

int enterPayment(int credit){
    Serial.print("Your total credit is: ");
    Serial.println(credit);
    Serial.println("Please select the amount you want to play with");

    char *end;
    char buf[9];
    int paid;
    bool ok;

    do {
        ok = true;
        Serial.println("Please enter a number: ");

        String readString;

        bool ok2 = true;
        do{

        while (Serial.available()> 0) {
            char c = Serial.read();  //gets one byte from serial buffer
            readString += c; //makes the string readString
            delay(2);  //slow looping to allow buffer to fill with next character
            ok2 = false;
        }
        }while(ok2);

        paid = readString.toInt();
             
             
        if(paid <= 0)
            Serial.println("Please enter a positive number or higher than 0: ");
        else if(paid > credit)
            Serial.println("This number exceeds your total credit, please enter a different value: ");
        else ok = false;
    }while(ok);
 
    Serial.print("You entered: ");
    Serial.println(paid);

    return paid;

    
}

void spinTheWheels(){

        int randNumber = 0;
        randNumber += random(10);
        if(randNumber > 9)
            randNumber -= 10;

        result[0] = sMLeft[randNumber];

        randNumber += random(10);
        if(randNumber > 9)
            randNumber -= 10;

        result[1] = sMMiddle[randNumber];

        randNumber += random(10);
        if(randNumber > 9)
            randNumber -= 10;

        result[2] = sMRight[randNumber];

        Serial.print(result[0]);Serial.print("-");Serial.print(result[1]);Serial.print("-");Serial.println(result[2]);
}

void setup() {
  Serial.begin(9600);
  
  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));

  //Account balance
  int credit = 10;

  //Repeat the game
  bool ok;
    
  do {
        ok = false;

        int paid = enterPayment(credit);
        Serial.println("Press enter to start the the game");

        credit -= paid;

        for(int j = 0; j < 6; j++){
            spinTheWheels();
            delay(1000);
        }

        Serial.println("And the result is:");
        Serial.print(result[0]);Serial.print("-");Serial.print(result[1]);Serial.print("-");Serial.println(result[2]);
        
        credit = credit + testForPrize(paid);
        Serial.print("Your new credit is: ");Serial.println(credit);

        if(credit != 0){
            Serial.println("To play another round send 'y', to stop press enter");

            bool ok2 = true;
            char input;
            do{
    
            if(Serial.available()> 0) {
                input = Serial.read();  //gets one byte from serial buffer
                delay(2);  //slow looping to allow buffer to fill with next character
                ok2 = false;
            }
            //Clear buffer
            while(Serial.available()> 0) {
                Serial.read();
            }
            }while(ok2);
            
            if(input == 'y'){
                //Play another round
                ok = true;
            }
        } else Serial.println("You ran out of credit, Game over");
        
  }while(ok);

  Serial.print("Total amount of cashout: ");
  Serial.println(credit);
  
}

void loop() {
  


}
