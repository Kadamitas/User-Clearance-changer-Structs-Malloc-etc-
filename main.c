#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct UserID{
char* FullID ; //this holds the initial ID
char* NumberID; //this only holds the Numbers youll change
char* NameID; //this holds the user Identifier
char Clearance; //im gonna let you guess what this holds

}UserID;
char* NameIDGiver(char* FullID){ //returns the User Identifier
    char* temp = malloc(sizeof(char)*3);
    temp[0] = FullID[0]; //this makes it so I only get the first two chars, then make a null char so its a string
    temp[1] = FullID[1];
    temp[2] = '\0';
    return temp;
}
char* NumberIDGiver(char* FullID){ //returns the Number ID
    char* temp = malloc(sizeof(char)*5);
    temp[0] = FullID[2]; //this makes it so I only get the next 4 chars, then make a null char so its a string
    temp[1] = FullID[3];
    temp[2] = FullID[4];
    temp[3] = FullID[5];
    temp[4] = '\0';
    return temp;
}
char ClearanceGiver(char* NumberID){ //returns the Clearance
    int total = 0;
    for(int i =0;NumberID[i]!='\0';i++){
        total += NumberID[i]-48 ; //in ASCII the 1 symbol is actually 49 so I minus 48 to get the dec
    }
    if (total <= 10){
        return 'A';
    }else if (total <25){
        return 'B';
    }else{
        return 'C';
    }
}


int main(){
    //boring declarations
    int ArraySize = 3;
    UserID* UserIDs = (UserID*) malloc(sizeof(UserID) * ArraySize); //making an array of IDs, big enough to hold 3, you can realloc l8r, make sure to increment ArraySize Accordindly
  //  UserIDs[0].FullID = malloc(sizeof(char)*7); // 6 chars + null char
    UserIDs[0].FullID = "DK2346";
  //  UserIDs[1].FullID = malloc(sizeof(char)*7); // 6 chars + null char
    UserIDs[1].FullID = "JM1102";
  //  UserIDs[2].FullID = malloc(sizeof(char)*7); // 6 chars + null char
    UserIDs[2].FullID = "GW8990";

    UserIDs[0].NameID = malloc(sizeof(char)*3); // 2 chars + null char
    UserIDs[0].NameID = NameIDGiver(UserIDs[0].FullID);
    UserIDs[1].NameID = malloc(sizeof(char)*3); // 2 chars + null char
    UserIDs[1].NameID = NameIDGiver(UserIDs[1].FullID);
    UserIDs[2].NameID = malloc(sizeof(char)*3); // 2 chars + null char
    UserIDs[2].NameID = NameIDGiver(UserIDs[2].FullID);

   // UserIDs[0].NameID = malloc(sizeof(char)*5); // 4 chars + null char
    UserIDs[0].NumberID = NumberIDGiver(UserIDs[0].FullID);
   // UserIDs[1].NameID = malloc(sizeof(char)*5); // 4 chars + null char
    UserIDs[1].NumberID = NumberIDGiver(UserIDs[1].FullID);
 //   UserIDs[2].NameID = malloc(sizeof(char)*5); // 4 chars + null char
    UserIDs[2].NumberID = NumberIDGiver(UserIDs[2].FullID);

    //no malloc needed since a char only has one size lmao
    UserIDs[0].Clearance = ClearanceGiver(UserIDs[0].NumberID);
    UserIDs[1].Clearance = ClearanceGiver(UserIDs[1].NumberID);
    UserIDs[2].Clearance = ClearanceGiver(UserIDs[2].NumberID);

    // menu
    int Selection = 0;
    int UserSelection = -1;
    char * IDSelection = malloc(sizeof(char)*3);
    char ClearanceSelection = -1;

    menu:
    printf("%s", "\nUser ID Program \n");
    printf("%s", "1. View User ID \n");
    printf("%s", "2. View User Clearance \n");
    printf("%s", "3. Change User Clearance \n");
     printf("%s", "4. Exit \n");
    scanf("%i", &Selection);
    switch(Selection){ // checks what you picked and then does a choose your own adventure
        case 1:
        goto VUI;
        break;

        case 2:
        goto VUC;
        break;

        case 3:
        goto CUC;
        break;

        case 4:
        goto exit;
        break;

        default:
        printf("Wrong number, try again.");
        goto menu;
        break;
    }

    VUI: //View User IDs
        for(int i = 0; i < ArraySize; i++){ 
            printf("%s \n", UserIDs[i].FullID);
        }
        goto menu;
    VUC: //View User Clearance
        for(int i = 0; i < ArraySize; i++){ 
            printf("User %s has %c level clearance \n", UserIDs[i].FullID, UserIDs[i].Clearance);
        }
        goto menu;
    CUC: //Change User Clearance
        printf("\nUser who gonna get his clearance changed (1-3):");
        scanf("%i", &UserSelection);
        if(UserSelection > ArraySize || UserSelection < 1){ //checks if its between 1-3
            printf(":/ Invalid User ID, can you pick a valid User ID next time? Going back to menu...\n");
            goto menu;
        }
        printf("\nClearance to change to:");
        scanf(" %c", &ClearanceSelection);
        if( (ClearanceSelection > 67 && ClearanceSelection < 65 ) || (ClearanceSelection > 99 && ClearanceSelection < 97)){ // checks if its a,b,c / A,B,C in ASCII
            printf(":/ Invalid Clearance, can you pick a valid Clearance next time? Going back to menu...\n");
            goto menu;
        }
        printf("\nNew ID #:");
        scanf("%s", IDSelection);
        if(ClearanceGiver(IDSelection) != ClearanceSelection){
            printf("Ruh Roh Raggy, thats an invalid id, can you pick a valid ID next time? Going back to menu...\n ");
            goto menu;

        }else{
            //the -1 is there because this isn't MATLAB so the 1st index isnt 1, its 0
            UserIDs[UserSelection-1].NumberID = IDSelection; // this overwrites the numbers but leaves the null char there because the ID SHOULDNT be longer than 4
           
            UserIDs[UserSelection-1].FullID= UserIDs[UserSelection-1].NameID; //overwrites FullID with name
            strcat(UserIDs[UserSelection-1].FullID, UserIDs[UserSelection-1].NumberID); // combines Name with number
            UserIDs[UserSelection-1].Clearance = ClearanceGiver(UserIDs[UserSelection-1].NumberID);
            printf("\nSuccessful Clearance Update\n");
            goto menu;
        }

        printf("User who gonna get his clearance changed:");
        goto menu;
    exit: //goes to return
    printf("Exiting program \n");
   // for(int i = 0; i<ArraySize;i++){
    //    free(UserIDs[i].FullID);
    //    free(UserIDs[i].NameID);
     //   free(UserIDs[i].NumberID);
   // }
   // free(UserIDs);
    return 0;
}