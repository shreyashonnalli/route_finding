//
//  logic.c
//  Route Finding
//
//  Created by Shreyas Honnalli on 04/03/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "logic.h"
struct link links[maxLink]; //list of links between nodes
struct node nodes[maxNode]; //list of nodes
double nodesLength[maxNode][maxNode]; //creates a matrix of distances from i to j
int nodeCount;//number of nodes
int linkCount;//number of links

//create a file pointer so its ready to read from file and store information
int LoadFile(void){
    FILE *fp = NULL;
    fp = fopen("Final_Map.map", "r");
    if (fp == NULL){
        printf(fileError);
        return 1;
    }
    else{
        int readStatus = ReadFile(fp);
        printf(dataStructureMessage);
        CreateAdjacencyList();
        StoreDataInFile();
        if(readStatus == 0){
            return 0;
        }
        else{
            return 1;
        }
    }
}

//creates the buffer and passes the buffer through to a function which actually reads in data
int ReadFile(FILE *file){
    char buffer[bufferLength];
    while(fgets(buffer,bufferLength,file)){

        //buffer passed to function for data to be read in
        int storeStatus = StoreData(buffer);

        //if theres an invalid line then ignore and continue
        if(storeStatus == 1){
            continue;
        }
    }

    //return 0 indicating all data that could be read is read
    return 0;
}


//takes in a line of buffer and stores it in a link value or a node value depending on what the buffer line is
int StoreData(char *buffer){
    struct link currentLink;
    currentLink.ID=0;
    currentLink.length=0;
    struct node currentNode;
    int linkNodeCount=0;
    char secondCharacter = buffer[1];
    if (secondCharacter == 'l'){
        for (int i=7;i<bufferLength;i++){

            //reads in id of the link
            if(buffer[i]=='d'&&buffer[i-1]=='i'){
                int j=i+2;
                char linkIDString[30];
                int k =0;
                while(buffer[j]!=' '){
                    linkIDString[k]=buffer[j];
                    k++;
                    j++;
                }
                linkIDString[k]='\0';
                currentLink.ID = atoi(linkIDString);
                continue;
            }

            //reads in the two nodes which are in the link
            if(buffer[i]=='e'&&buffer[i-1]=='d'&&buffer[i-2]=='o'&&buffer[i-3]=='n'){
                int j=i+2;
                char linkNodeString[30];
                int k=0;
                while(buffer[j]!=' '){
                    //node ids are copied onto here
                    linkNodeString[k]=buffer[j];
                    k++;
                    j++;
                }


                //node id is in string form
                linkNodeString[k]='\0';
                linkNodeCount++;
                bool duplicatePresent = false;
                int duplicatePresentAt = 0;


                //check if theres a node already in system of the node being scanned
                for (int a=0;a<maxNode;a++){
                    if(nodes[a].ID == atoi(linkNodeString)){
                        duplicatePresent = true;
                        duplicatePresentAt = a;
                        break;
                    }
                }


                //if theres a node already in system then point to that
                if(duplicatePresent == true){
                    if(linkNodeCount == 1){
                        currentLink.node1 = &nodes[duplicatePresentAt];
                    }
                    else if (linkNodeCount == 2){
                        currentLink.node2 = &nodes[duplicatePresentAt];
                    }
                }

                //if theres no node which has ID which is in buffer right now assign the buffer ID to a new node
                else if (duplicatePresent == false){
                    for(int m=0;m<maxNode;m++){
                        if(nodes[m].ID==0){
                            if(linkNodeCount == 1){
                                    nodes[m].ID=atoi(linkNodeString);
                                    currentLink.node1 = &nodes[m];
                                break;
                            }
                            else if (linkNodeCount == 2){
                                    nodes[m].ID=atoi(linkNodeString);
                                    currentLink.node2 = &nodes[m];
                                break;
                            }
                            else{
                                printf("Counting error detected");
                                return 1;
                            }
                        }
                    }
                }
                continue;
            }

            //reads about length between nodes(i.e. length of link)
            if(buffer[i]=='h'&&buffer[i-1]=='t'&&buffer[i-2]=='g'&&buffer[i-3]=='n'){
                int j=i+2;
                char linkLengthString[30];
                int k=0;
                while(buffer[j]!=' '){
                    //length of links is copied into here
                    linkLengthString[k]=buffer[j];
                    k++;
                    j++;
                }
                linkLengthString[k]='\0';
                currentLink.length = atof(linkLengthString);
            }


            //if end of buffer line then stop reading
            if (buffer[i]=='\n'){
                break;
            }
        }

        //link is copied onto the array system
        for(int n=0;n<maxLink;n++){
            if(links[n].ID == 0){
                links[n]=currentLink;
                break;
            }
        }

        //returning 0 indicates successful storage
        return 0;
    }



    //if the buffer is information about a node
    else if (secondCharacter == 'n'){
        for (int i=7;i<bufferLength;i++){

            //reads info about node ID
            if(buffer[i]=='d'&&buffer[i-1]=='i'){
                int j = i+2;
                int k=0;
                char nodeIDString[30];
                while(buffer[j]!=' '){
                    nodeIDString[k]=buffer[j];
                    k++;
                    j++;
                }
                nodeIDString[k]='\0';
                currentNode.ID = atoi(nodeIDString);
                continue;
            }

            //reads info about nodes latitude
            if(buffer[i]=='t'&&buffer[i-1]=='a'&&buffer[i-2]=='l'){
                int j = i+2;
                char nodeLatString[30];
                int k=0;
                while(buffer[j]!=' '){
                    nodeLatString[k]=buffer[j];
                    k++;
                    j++;
                }
                nodeLatString[k]='\0';
                currentNode.latitiude = atof(nodeLatString);
                continue;
            }

            //reads into about nodes longitude
            if(buffer[i]=='n'&&buffer[i-1]=='o'&&buffer[i-2]=='l'){
                int j = i+2;
                int k=0;
                char nodeLonString[30];
                while(buffer[j]!=' '){
                    nodeLonString[k]=buffer[j];
                    k++;
                    j++;
                }
                nodeLonString[k]='\0';
                currentNode.longitude = atof(nodeLonString);
                continue;
            }

            //if end of buffer then break
            if (buffer[i]=='\n'){
                break;
            }


        }

        //since we have already read in node ID values from link, we just need to find them and assign the correct latitude and longitudes to them
        for(int m = 0;m<maxNode;m++){
            if(nodes[m].ID == currentNode.ID){
                nodes[m].latitiude = currentNode.latitiude;
                nodes[m].longitude = currentNode.longitude;
            }
        }

        //returning 0 indicates successful storage
        return 0;
    }

    //if the buffer line is neither of type link or node then return 1 and dont do anything
    return 1;
}


//creates an adjacency list data structure called nodeLength
//This nodeLength data structure will be updated in the function which implements dijkstras algorithm as the distances which have been set to infinity will be known as we calculate shortest distance
//Uses technique from Crazy Programmer website which is referenced in planning report
int CreateAdjacencyList(){
    bool linkPresent = false;
    bool linkPresent2 = false;


    //counts number of nodes
    for (int i=0;i<maxNode;i++){
        if(nodes[i].ID!=0){
            nodeCount++;
        }
    }


    //counts the number of links
    for (int a=0;a<maxLink;a++){
        if(links[a].ID!=0){
            linkCount++;
        }
    }




    //creates the adjacency list nodesLength

    //search through every node and see if theres a link with each other
    for (int i=0;i<nodeCount;i++){
        for (int j=0;j<nodeCount;j++){


            //if the nodes i and j are the same then the distance from i to j is 0
            if(nodes[i].ID == nodes[j].ID){
                nodesLength[i][j] = 0.00;
                continue;
            }

            //else search through all links to see if theres a link between nodes i and j
            for (int k = 0;k<linkCount;k++){
                linkPresent = links[k].node1->ID == nodes[i].ID && links[k].node2->ID == nodes[j].ID;
                linkPresent2 = links[k].node2->ID == nodes[i].ID && links[k].node1->ID == nodes[j].ID;

                //if link is present then make the length between them the length of the link
                if (linkPresent==true||linkPresent2==true){
                    nodesLength[i][j] = links[k].length;
                    break;
                }
            }

            //if link is not present after searching through all the links then set the distance between them to infinity
            if (nodesLength[i][j] == 0){
                nodesLength[i][j] = infinity;
                continue;
            }
        }
    }
    return 0;
}

//stores data in the system into a Coordinates.dat which is of appropriate file format so that we can use gnupoint to display it
//data is in format latitude longitude
int StoreDataInFile(){
    FILE *storeFile = NULL;
    storeFile = fopen("Coordinates.dat", "w");
    if (storeFile == NULL){
        return 1;
    }
    for (int i=0;i<linkCount;i++){
        fprintf(storeFile, "%f\t%f\n%f\t%f\n\n",links[i].node1->longitude, links[i].node1->latitiude,links[i].node2->longitude,links[i].node2->latitiude);
    }
    fclose(storeFile);
    return 0;
}

//implements dijkstra's algorithm
//returns the shortest distance from node1 to node2 through a structure called path
struct way ShortestDistance(struct node node1,struct node node2){
    struct way path;
    //count is the number of nodes seen so far
    int count = 0;
    //predecessor of each node
    int pred[nodeCount];
    //distance from source to each node
    double distance[nodeCount];
    int startNode = 0;
    int endNode = 0;
    int visited[nodeCount], nextNode = 0;
    double minDistance;
    //get the index value of the starting node i.e. node1
    for(int i=0;i<nodeCount;i++){
        if (node1.ID == nodes[i].ID){
            startNode = i;
        }
        if (node2.ID == nodes[i].ID){
            endNode = i;
        }
    }

    //set the distance array as the adjacency list from startNode to each node
    //all visited status is set to 0
    //predecessor of all nodes is the startNode to start off with
    for(int i=0;i<nodeCount;i++){
        distance[i] = nodesLength[startNode][i];
        visited[i] = 0;
        pred[i] = startNode;
    }

    //initialise variables before we count
    visited[startNode] = 1;
    distance[startNode] = 0;
    count = 1;


    //dijkstras algorithm
    while (count<nodeCount-1){
        minDistance = infinity;
        for (int j=0;j<nodeCount;j++){
            if (distance[j]<minDistance&&visited[j]==0){
                minDistance = distance[j];
                nextNode = j;
            }


            visited[nextNode] = 1;
            for(int k=0;k<nodeCount;k++){
                if(visited[k]==0){
                    if (minDistance+nodesLength[nextNode][k]<distance[k]){
                        distance[k]=minDistance+nodesLength[nextNode][k];
                        pred[k]=nextNode;
                    }
                }
            }

        }
        count++;
    }



    //creates a way struct called path which is a list of nodes the user has to take to get from point A to B
    int m = endNode;
    int numberOfNodes = 0;
    do{
        path.nodes[numberOfNodes]=&nodes[m];
        numberOfNodes++;
        m = pred[m];
    }while(m!=startNode);
    path.nodes[numberOfNodes]=&nodes[m];
    path.distance = distance[endNode];
    path.numberOfnodes = numberOfNodes;

    //return path
    return path;
}

//prints a list of nodes
void ListNodes(){
    for (int i=0;i<maxNode;i++){
        if(nodes[i].ID!=0){
            printf("%i. Node ID:%i, latitude:%f, longitude:%f\n",i+1,nodes[i].ID,nodes[i].latitiude,nodes[i].longitude);
        }
    }
}

//plots the data which is in the Coordinates.dat file using gnupoint
int GraphData(){
    system("gnuplot -persist -e \"plot 'Coordinates.dat' with linespoints linestyle 2\"");
    return 0;
}
//searches through the data structure to see if a node exists or not in it
struct node SearchNode(int ID){
    for(int i=0;i<nodeCount;i++){
        if(nodes[i].ID == ID){
            return nodes[i];
        }
    }
    return nodes[maxNode-1];
}

//exits the program
void ExitProgram(void){
    exit(0);
}
