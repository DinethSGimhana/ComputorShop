#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Game{
    char gameName [100];
    int gamecount;
    struct Game *nextGame;
}Game;

Game *head;

typedef struct Order{
    char customerName [100];
    char gameName [100];
    struct Order *nextOrder;
}Order;

Order *front,*rear;

typedef struct ProcessedOrder{
    char customerName [100];
    char gameName [100];
    struct ProcessedOrder *nextProcessedOrder;
}ProcessedOrder;

ProcessedOrder *top;

void addProcessedOrder(char customerName [100],char gameName [100]);
void displayLastProcessedOrder();
void reverseLastProcessedOrder();
void addReversedOrder(char customerName [100],char gameName [100]);
void displayProcessedOrders();
void cheackAvailability(char customerName [100],char gameName [100]);
void addOrder(char customerName [100],char gameName [100]);
void displayOrders();
void processNextOrder();
void insertGameHead(char gameName [100],int gameCount);
void insertGameTail(char gameName[],int gameCount);
void insertGameSpecific(char gameName[],int gameCount);
void displayGameList();

void addProcessedOrder(char customerName [100],char gameName [100]){
   ProcessedOrder *newProcessedOrder=(struct ProcessedOrder *)malloc(sizeof(struct ProcessedOrder));
   if(newProcessedOrder==NULL){
    printf("\nUnable to complete Order");
   }
   else{
        strcpy(newProcessedOrder->customerName,customerName);
        strcpy(newProcessedOrder->gameName,gameName);
    if(top==NULL){
        newProcessedOrder->nextProcessedOrder=NULL;
        top=newProcessedOrder;
    }
    else{
        newProcessedOrder->nextProcessedOrder=top;
        top=newProcessedOrder;
    }
   }
}

void displayLastProcessedOrder(){
    ProcessedOrder *lastProcessedOrder;
    if(top==NULL){
       printf("\nNo any Processed orders");
    }
    else{
        lastProcessedOrder=top;
        printf("\nLast Processed order Details:\nCustomer Name:%s\nGame name:%s\n",lastProcessedOrder->customerName,lastProcessedOrder->gameName);
    }
}

void reverseLastProcessedOrder(){
    ProcessedOrder *lastProcessedOrder;
    if(top==NULL){
       printf("\nNo any Processed orders");
    }
    else{
        lastProcessedOrder=top;
        printf("\nLast Processed order Details:\nCustomer Name:%s\nGame name:%s\n",lastProcessedOrder->customerName,lastProcessedOrder->gameName);
        top=top->nextProcessedOrder;
        addReversedOrder(lastProcessedOrder->customerName,lastProcessedOrder->gameName);
        free(lastProcessedOrder);
    }
}

void displayProcessedOrders(){
    ProcessedOrder *temp;
    if(top==NULL){
        printf("\nProcessed order list is empty!!!");
    }
    else{
        temp=top;
        while(temp!=NULL){
            printf("\nCustomer Name:%s",temp->customerName);
            printf("\nGame Name:%s",temp->gameName);
            temp=temp->nextProcessedOrder;
        }
    }
}

void cheackAvailability(char customerName [100],char gameName [100]){
   Game *temp;
   temp=head;
   if(head==NULL){
    printf("\nGame store is Empty");
   }
   else{
    while(temp!=NULL){
        if(strcmp(gameName,temp->gameName)==0){
            temp->gamecount--;
            addOrder(customerName,gameName);
            break;
        }
        temp=temp->nextGame;
    }
    if(temp==NULL){
        printf("\n!!!!That game is not in the Store!!!!");
    }
   }

}

void addOrder(char customerName [100],char gameName [100]){
    Order *newOrder=(struct Order*)malloc(sizeof(struct Order));
    if(newOrder==NULL){
        printf("\nUnable to place Order!!!");
    }
    else{
        strcpy(newOrder->customerName,customerName);
        strcpy(newOrder->gameName,gameName);
        if(front==NULL){
            front=newOrder;
            rear=newOrder;
            front->nextOrder=NULL;
            rear->nextOrder=NULL;
        }
        else{
            rear->nextOrder=newOrder;
            rear=newOrder;
            rear->nextOrder=NULL;
        }
}
}
void addReversedOrder(char customerName [100],char gameName [100]){
    Order *reverseOrder=(struct Order*)malloc(sizeof(struct Order));
    if(reverseOrder==NULL){
        printf("\nUnable to place Order!!!");
    }
    else{
        strcpy(reverseOrder->customerName,customerName);
        strcpy(reverseOrder->gameName,gameName);
        if(front==NULL){
            front=reverseOrder;
            rear=reverseOrder;
            front->nextOrder=NULL;
            rear->nextOrder=NULL;
        }
        else{
            reverseOrder->nextOrder=front;
            front=reverseOrder;
        }
        printf("\nReversed Last Processed Order Successfully");
        printf("\nLast Reversed Processed order Details:\nCustomer Name:%s\nGame name:%s\n",reverseOrder->customerName,reverseOrder->gameName);
    }
}
void displayOrders(){
    Order *temp;
    temp=front;
    if(front==NULL){
        printf("\nNo any Orders placed");
    }
    else{
        while(temp!=NULL){
            printf("\nCustomer Name:%s",temp->customerName);
            printf("\nGame Name:%s",temp->gameName);
            temp=temp->nextOrder;
        }
    }
}
void processNextOrder(){
    Order *processingOrder;
    if(front==NULL){
        printf("\nNo orders to Process");
    }
    else{
        processingOrder=front;
        front=front->nextOrder;
        addProcessedOrder(processingOrder->customerName,processingOrder->gameName);
        printf("\nOrder Completed Successfully!!!");
        printf("\nCustomer Name:%s",processingOrder->customerName);
        printf("\nGame Name:%s",processingOrder->gameName);
        free(processingOrder);
    }
}


void insertGameHead(char gameName [100],int gameCount){
    Game *newGame=(struct Game*)malloc(sizeof(struct Game));
    if(newGame==NULL){
        printf("\nUnable to reserve space!!!");
    }
    else{
       strcpy(newGame->gameName,gameName);
       newGame->gamecount=gameCount;
       newGame->nextGame=head;
       head=newGame;
       printf("\nGame added Successfully");
    }
}

void insertGameTail(char gameName[],int gameCount){
    Game *newGame=(struct Game*)malloc(sizeof(struct Game*));
    Game *temp;
    if(newGame==NULL){
        printf("\nUnable to reserve space!!!");
    }
    else{
        if(head==NULL){
            strcpy(newGame->gameName,gameName);
            newGame->gamecount=gameCount;
            newGame->nextGame=NULL;
            head=newGame;
        }
        else{
            temp=head;
            while(temp->nextGame!=NULL){
                temp=temp->nextGame;
            }
            strcpy(newGame->gameName,gameName);
            newGame->gamecount=gameCount;
            temp->nextGame=newGame;
            newGame->nextGame=NULL;
        }
        printf("\nGame added Successfully");
    }

}

void insertGameSpecific(char gameName[],int gameCount){
    Game *newGame=(struct Game*)malloc(sizeof(struct Game*));
    Game *temp,*tail;
    temp=head;
    //start find tail
    if(temp==NULL){
        tail=NULL;
    }
    else{
    while(temp->nextGame!=NULL){
            temp=temp->nextGame;
        }
        tail=temp;
    }
    //end find tail
    if(newGame==NULL){
        printf("\nUnable to reserve space!!!");
    }
    else{
        temp=head;
        strcpy(newGame->gameName,gameName);
        newGame->gamecount=gameCount;
        //if list is empty
        if(head==NULL){
            newGame->nextGame=NULL;
            head=newGame;
        }
        //if node is add to the head
        else if(strcmp(head->gameName,newGame->gameName)>0){
            newGame->nextGame=head;
            head=newGame;
        }
        else if(strcmp(tail->gameName,newGame->gameName)<0){
            tail->nextGame=newGame;
            newGame->nextGame=NULL;
        }
        else {
            while(strcmp(temp->nextGame->gameName,newGame->gameName)<0){
                temp=temp->nextGame;
            }
            newGame->nextGame=temp->nextGame;
            temp->nextGame=newGame;
             }

            printf("\nGame added Successfully");

    }

}

void displayGameList(){
    Game *temp;
    if(head==NULL){
         printf("\nNo Games!!!");
    }
    else{
        temp=head;
        while(temp!=NULL){
            printf("\nGame Name:%s\n",temp->gameName);
            printf("No of games:%d",temp->gamecount);
            temp=temp->nextGame;
        }
    }
}


int main(){
    int choice;
    char gameName [100],customerName [100],orderGameName [100];
    int gameCount;
    printf("\n\nMenu\n1.Add game to Begin\n2.Add game to end\n3.Add game to Alphabetical order\n4.Display Games\n5.Add Order to Queue\n6.Display Orders\n7.Process next Order\n8.Display Processed orders\n9.Display Last Processed Order\n10.Reverse Last Processed Order\nEnter your Choice:\n");
    scanf("%d",&choice);
    if(choice==1 ||choice==2||choice==3){
        printf("\nGame Name:");
        scanf("%s",gameName);
        printf("\nNo of Games:");
        scanf("%d",&gameCount);
        if(choice==1){
            insertGameHead(gameName,gameCount);
        }
        else if(choice==2){
            insertGameTail(gameName,gameCount);
        }
        else{
            insertGameSpecific(gameName,gameCount);
        }
        main();

    }
    else if(choice==4){
        displayGameList();
        printf("\nGame Stock");
        printf("\n----------");
        main();
    }
    else if(choice==5){
        printf("\nCustomer Name:");
        scanf("%s",customerName);
        printf("\nGame name:");
        scanf("%s",orderGameName);
        cheackAvailability(customerName,orderGameName);
        main();
    }
    else if(choice==6){
        printf("\nAll order to Complete");
        printf("\n---------------------");
        displayOrders();
        main();
    }
    else if(choice==7){
        processNextOrder();
        main();
    }
    else if(choice==8){
        displayProcessedOrders();
        printf("\nAll processed Orders");
        printf("\n--------------------");
        main();
    }
    else if(choice==9){
        displayLastProcessedOrder();
        main();
    }
    else if(choice==10){
        reverseLastProcessedOrder();
        main();
    }
    else{
        return 0;
    }

}




