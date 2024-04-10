
#include <stdio.h>
#include "_test.h"
//#include "041034479.h"
#include<math.h>

typedef unsigned long long int uLLInt;

uLLInt binaryReservations[][2] = {0};
uLLInt week1[7] = {0};
uLLInt week2[7] = {0};
uLLInt schedulesORed [][2] = {0};
void displayMenu();
void displayStudentExamSchedule();
void displayUnbookedTimes();
void setExamBookingTime();
void convertLLIntToArray();
void weeksToBinary(uLLInt position, uLLInt week[]);
uLLInt convertToBinary(int num);
//void convertToBinary(int num);
uLLInt determineTestBitmask(int startTime, int duration);
uLLInt convertListToBinary(int examBookings[][5]);


int iterate(int array[][5],int stdID);
int main(void){
    int run = 1;
    while(run){
       
        displayMenu();
        int option = 0;
        scanf("%d",&option);
        switch(option){
            case 1:
                displayStudentExamSchedule();
            break;
            case 2:
                setExamBookingTime();

            break;
            case 3:
                displayUnbookedTimes();
            break;
            case 4:
            run = 0;
            break;
        }


    }

}

void displayMenu(){
    printf("\n1. Display a student's exam schedule\n2. Load a new exam booking\n3. Find unbooked times\n4. exit\n>");
}

    // find where stdID is in the array.
    // then iterate through that row.
    // week # would be [x][1]
    // day would be    [x][2]
    // start time      [x][3]
    // duration        [x][4]
    // exam end        [x][3]+[x][4]
void displayStudentExamSchedule(){
    //            printf("week %d: %s %10.2f - %.2f\n",week,daysArray[day],startTime,examEnd);

    int studentID;
                            //0        1          2            3        4        5          6
    char daysArray[7][10]={"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};
    printf("What is your student id?\n> ");
    scanf ("%d",&studentID);

    // checks the first index, then iterates if not found.
    if (examBookings[0][0] == studentID){
        int index = 0;
        while(examBookings[index][0]==studentID){

            int week = examBookings[index][1]>0?2:1;
            int day = examBookings[index][2];
            float startTime = (float)examBookings[index][3];
            int duration = examBookings[index][4];
            float examEnd = startTime+duration;
            printf("week %d: %s %10.2f - %.2f\n",week,daysArray[day],startTime,examEnd);
            index++;
        }
    }
    else{

        int index = iterate(examBookings,studentID);
        index++;
        while(examBookings[index][0]==studentID){
            int week = examBookings[index][1]>0?2:1;
            int day = examBookings[index][2];
            float startTime = (float)examBookings[index][3];
            int duration = examBookings[index][4];
            float examEnd = startTime+duration;
            printf("week %d: %s %10.2f - %.2f\n",week,daysArray[day],startTime,examEnd);
            index++;
        }
    }
}
// first, ask for the student id
// go through list until user stdId == std in the list
    // this means that the index is near that block of stdIDs
// but how do you add an entry without overwriting? -> add new entry to test this feature.

void setExamBookingTime(){

    uLLInt inputbitMask = 0xFFFFFFFFFFFFFFFF; 
    uLLInt week1Mask;
    uLLInt week2Mask;

    int studentID;
    int week, day,duration;
    int startTime,examEnd;

    printf("What is your student id?\n> ");
    scanf ("%d",&studentID);
    printf("Which week? 0 for week 1, 1 for Week 2 \n> ");
    scanf ("%d",&week);
    // using week, check to see if its already booked.
    
    printf("What date? 0(monday) to 5(saturday) \n> ");
    scanf ("%d",&day);
    printf("When does the exam begin? \n> ");
    scanf("%d",&startTime);
    printf("What is the duration of the exam? \n> ");
    scanf("%d",&duration);
 
    inputbitMask >>= (duration);
    inputbitMask =~ inputbitMask;
    inputbitMask >>= (startTime-9);
    inputbitMask >>= (8*day);

    convertListToBinary(examBookings);

    uLLInt bitMaskFromReserve = binaryReservations[studentID][week];
    uLLInt resultMask = inputbitMask | bitMaskFromReserve;
    printf("%lld", bitMaskFromReserve);


    if (resultMask == bitMaskFromReserve){
        printf("\n Already booked.\n");
    }
    else{
        printf("\nbooked \n");
    }
 

}

void displayUnbookedTimes(){
    convertListToBinary(examBookings);
    convertLLIntToArray();
}



// iterates through the array, stops when studentID is found.
int iterate(int array[][5], int stdID){
    int index = 0;
    for (int i = 0; array[i][0]!=stdID;i++){
        index = i;
    }
    return index;
}
/**
 * @brief Converts the examBookings array into uLLInt, stored in the binaryreserve array.
 * 
 * @param examBookings 
 * @return uLLInt 
 */
uLLInt convertListToBinary(int examBookings[][5]){
    
    int index = 0;
    for (int i = 0; i < 2655; i++){
       // uLLInt bitMask = 0x7FFFFFFFFFFFFFFF; 
        uLLInt bitMask = 0xFFFFFFFFFFFFFFFF; 

        int week = examBookings[i][1];
        int day = examBookings[i][2];
        int startTime = examBookings[i][3];
        int duration = examBookings[i][4];

        bitMask >>= (duration);
        bitMask =~bitMask;
        bitMask >>= (startTime-9);
        bitMask >>= (8*day);

        if (i > 1 && examBookings[i][0] != examBookings[i-1][0]){
            index++;
        }
        if (week == 0){
            uLLInt bitMaskOld = binaryReservations[index][0];
            //printf("%lld \n", bitMask);
            binaryReservations[index][0] = bitMask | bitMaskOld;
            printf("%d ", index);
        }
        if (week == 1){
            uLLInt bitMaskOld = binaryReservations[index][1]; // gets a copy of the current bitMask for ORing. This is more cases when multiple exams in one week.
            //printf("%lld \n", bitMask);
            binaryReservations[index][1] = bitMask | bitMaskOld;
            printf("%d ", index);

        }
    }
  
    
    printf("\n");
    for (int i = 0; i < 2655; i++){
        for (int j = 0; j < 2 ; j++){
            printf("binary reserve %d %d: %lld \n", i,j, binaryReservations[i][j]);

        }
    }
    
    
    return 0;
    
}


void convertLLIntToArray(){
    // for week 1 
    //uLLInt result = binaryReservations[0][0] | binaryReservations[1][0];
    //schedulesORed[0][0] = result;
    uLLInt current = binaryReservations[0][0];
    uLLInt next = binaryReservations[1][0];
    uLLInt result = next | current;
    schedulesORed[0][0] = result;
    for (int i = 2; i < 2655; i++){
        schedulesORed[0][0] = schedulesORed[0][0] | binaryReservations[i][0];
        
    }
    // for week 2
    uLLInt current2 = binaryReservations[0][1];
    uLLInt next2 = binaryReservations[1][1];
    uLLInt result2 = next2 | current2;
    schedulesORed[0][1] = result2;
    for (int i = 2; i < 2655; i++){
        schedulesORed[0][1] = schedulesORed[0][1] | binaryReservations[i][1];
        
    }
    
    
    printf("\nORed 0 0: %lld", schedulesORed[0][0]);
    printf("\nORed 0 1: %lld", schedulesORed[0][1]);



}
/**
void weeksToBinary(uLLInt num){
    for (int i = 0; i<63; i++){
        week[i] = position % 2;
        position = position / 2;
    }
}
**/
/**
for (int i = 0 ; i<8; i++){
        binArray[i] = (position % 2);
        position = position / 2;
    }
}
**/








