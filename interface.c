//
//  interface.c
//  Route Finding
//
//  Created by Shreyas Honnalli on 04/03/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "logic.h"
void RunInterface(void){
    char userInput;
    int nodeInput=0;
    //load data from the file and store it in the system
    LoadFile();
    
    
    do{
        
        //main menu and userinput
        printf(MenuMessage);
        scanf(" %c", &userInput);
        
        
        //if user chooses to list all the nodes
        if(userInput == '1'){
            ListNodes();
        }
        
        //if user chooses to find the shortest distance between 2 nodes
        else if(userInput == '2'){
            
            //ask user to input 2 nodes
            printf(ShortestDistanceMessage);
            printf(ShortestDistanceStartMessage);
            scanf("%i", &nodeInput);
            struct node startNode = SearchNode(nodeInput);
            //if node input is invalid then go to main menu
            if(startNode.ID == 0){
                printf(InvalidNodeMessage);
                continue;
            }
            printf(ShortestDistanceDestinationMessage);
            scanf("%i", &nodeInput);
            struct node endNode = SearchNode(nodeInput);
            //if node input invalid, go to main menu
            if (endNode.ID == 0){
                printf(InvalidNodeMessage);
                continue;
            }
            
            
            //otherwise calculate the shortest distance between the 2 if they are valid
            struct way path;
            for(int i=0;i<maxNode;i++){
                path.nodes[i]=(struct node*)malloc(sizeof(path.nodes[i]));
            }
            path = ShortestDistance(startNode, endNode);
            //print the distance between the nodes through links and the path
            printf("\nThe shortest distance from ID: %i to ID: %i is %f\n", startNode.ID, endNode.ID, path.distance);
            printf("Path= %i",path.nodes[0]->ID);
            int i=0;
            while(path.nodes[i]!=NULL){
                i++;
                if(i<=path.numberOfnodes){
                    printf(" <- %i",path.nodes[i]->ID);
                }
            }
            printf("\n\n");
            //dereference the pointer
            for(int j=0;j<=path.numberOfnodes;j++){
                path.nodes[j]=NULL;
            }
        }
        
        
        
        //if user chooses to plot the map
        else if(userInput == '3'){
            GraphData();
        }
        
        
        
        //if user chooses wrong input
        else if(userInput!='1'&&userInput!='2'&&userInput!='3'&&userInput!='4'){
            printf(InvalidMenuMessage);
        }
    }while (userInput !='4');
    
    
    //if user chooses to exit
    if(userInput=='4'){
    printf(exitMessage);
    ExitProgram();
    }
}
