#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LOAD 1
#define DEL 2
#define EXIT 3
#define ARRSIZE 100

typedef struct Time{
    unsigned int hours;
    unsigned int minutes;
} Time;

typedef struct BusRoute{
    unsigned int busrouteNumber;
    char * startingLocation;
    char * endingLocation;
    Time startTime;
    Time endTime;
} BusRoute;

int MenuItem();
void executeMenuItem(int menuItem);
BusRoute ** detectEmptyElements(BusRoute ** ActiveBusRoute);
void loadBusRoute(BusRoute **);
void deleteRoute(BusRoute ** ActiveBusRoute);

int main (void){   
    
    BusRoute * ActiveBusRoutes[ARRSIZE] = {'\0'};
    int i = 0; 
    BusRoute ** empty;
    int choice = EXIT;
    do{
        choice = MenuItem();

    switch (choice) {
        case LOAD:
            empty = detectEmptyElements(ActiveBusRoutes);
            loadBusRoute(empty);
        break;
        case DEL:
            deleteRoute(ActiveBusRoutes);
        break;
        case EXIT:
        break;
        default:
           printf("invalid input");
        break;
    }
    } while (choice != EXIT);
    printf("Program exited\n");
    exit(EXIT_SUCCESS);
}

int MenuItem(){
    int choice;
    printf("\n\nBus Route Registration System");
    printf("\nEnter one of the Following\n 1. Load new bus route\n 2. Delete a bus route\n 3. Exit\n >");
    scanf("%d", &choice);
    return choice;
}

BusRoute ** detectEmptyElements(BusRoute ** ActiveBusRoute){
    int i = 0;
    for (BusRoute **start = ActiveBusRoute, **iterator = start; iterator < start+100; iterator++){
        if (*(iterator) == NULL){
            printf("Spot avaliable at %d", i);
            return iterator;
        } 
        i++;
    }
}

void loadBusRoute(BusRoute ** emptySpot){
    BusRoute *pNewRoute = (BusRoute *)malloc(sizeof(BusRoute));
    char clearBuffer, sign;
    printf("\nBus route Number: ");
    scanf("%u", &pNewRoute->busrouteNumber);

    printf("\nEnter Starting Location: ");
    scanf("%c", &clearBuffer);
    char tempStart[30] = {'\0'};
    scanf("%[^\n]", tempStart);
    pNewRoute->startingLocation = (char *)malloc(strlen(tempStart)+1);
    strcpy(pNewRoute->startingLocation,tempStart);

    printf("\nEnter Ending location: ");
    scanf("%c", &clearBuffer);
    char tempEnd[30] = {'\0'};
    scanf("%[^\n]", tempEnd);

    pNewRoute->endingLocation = (char *)malloc(30 * sizeof(char));
    strcpy(pNewRoute->endingLocation,tempEnd);

    printf("\nStart time (hours):(mins): ");
    scanf("%u%c%u", &pNewRoute->startTime.hours,&sign,&pNewRoute->startTime.minutes);
    printf("\nend time (hours):(mins): ");
    scanf("%u%c%u", &pNewRoute->endTime.hours,&sign,&pNewRoute->endTime.minutes);

    *emptySpot = pNewRoute;
    printf("Route %d loaded.", pNewRoute->busrouteNumber);
}

void deleteRoute(BusRoute ** ActiveBusRoute){
    unsigned int toDel = 0;
    unsigned int found = 0;
    printf("Enter the route to delete:\n");
    scanf("%u",&toDel);
    int index = ARRSIZE-1;
    for (BusRoute **start = (ActiveBusRoute+(ARRSIZE-1)), **iterator = start; iterator >= start-(ARRSIZE-1); iterator--){
        if (*iterator!=NULL){
            if (*iterator!=NULL && (*iterator)->busrouteNumber == toDel){
                free((*iterator)->startingLocation);
                free((*iterator)->endingLocation);
                free((*iterator));
                *iterator = NULL;
                printf("Route %u deleted", toDel);
                found = 1;
            }
        }
        index--;
    }
    if (!found){ printf("Route %d not found.", toDel);}
}