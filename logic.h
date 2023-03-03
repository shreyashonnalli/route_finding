//
//  logic.h
//  Route Finding
//
//  Created by Shreyas Honnalli on 04/03/2021.
//

#ifndef logic_h
#define logic_h
#include <stdio.h>
#include <stdlib.h>
#define fileError "File not found\n" //message for file not found
#define exitMessage "exiting the program\n" //message for exiting the program
#define dataStructureMessage "Creating data structure, may take up to a minute...\n" //message while creating data structure
#define bufferLength 300
#define maxLink 3000
#define maxNode 6000
#define maxAdjacencyLink 20
#define infinity 2147483646.5

//a node has the following info about it
struct node{
    int ID;
    double latitiude;
    double longitude;
};


//a link points to 2 nodes and stores distance between them
struct link{
    struct node *node1;
    struct node *node2;
    double length;
    int ID;
};


//way is list of nodes which if u follow in chronological order, youll get from start to end
struct way{
    struct node *nodes[maxNode];
    double distance;
    int numberOfnodes;
};

//comments for following functions found in logic.c
int LoadFile(void);
int ReadFile(FILE *file);
int StoreData(char *buffer);
int StoreDataInFile(void);
struct way ShortestDistance(struct node node1,struct node node2);
void ListNodes(void);
int GraphData(void);
void ExitProgram(void);
int CreateAdjacencyList(void);
struct node SearchNode(int ID);
#endif /* logic_h */
