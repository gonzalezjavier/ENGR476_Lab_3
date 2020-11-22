//
//
//  Dijkstra's Algorithm
//  This porgram computes the shortest path from a starting
//  node to and ending node.
//
//  Created by Javier Gonzalez on 11/11/20.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#define M_SIZE 8
#define INFINITE 999

int numRowsandCol = 0;
int matrix[M_SIZE][M_SIZE];
int startNode, endNode;

void read_from_file(void);
void dijkstra(void);
int minCostIndex(int [], int []);
void printPath(int [], int[]);

int main(void) {
    char nodeOne, nodeTwo;
    read_from_file();
//    printf("Matrix now\n");
//    for (int i = 0; i < numRowsandCol; i++) {
//        for (int j=0; j<numRowsandCol; j++) {
//            printf("%d", matrix[i][j]);
//        }
//        printf("\n");
//    }
//    printf("\n");
    
    while(1) {
        printf("Enter a starting node(%c-%c): ",65,numRowsandCol+64);
        scanf(" %c", &nodeOne);
        printf("Enter an ending node(%c-%c): ",65,numRowsandCol+64);
        scanf(" %c", &nodeTwo);
        //converts alphabet to correspond with matrix index
        startNode = toupper(nodeOne)-65;
        endNode = toupper(nodeTwo)-65;
        //need to check if the start and end node are valid else ask again for valid ones
        if((startNode>=numRowsandCol || startNode<0) || (endNode>=numRowsandCol || endNode<0)) {//out of range
            printf("Input is out of range of available nodes, try again.\n");
            continue;
        }
        dijkstra();
    }
    
    return 0;
}
/*
// This function opens up the source file and loads in the
// the cost matrix.
*/
void read_from_file(void) {
    FILE *file_ptr = fopen("./Test_File.txt", "r"); //Open file
    char size;
    //char line[numRowsandCol+2];//stores each line of text     PROBLEM IS THAT NUMROWSANDCOLS ARE ZERO HERE

    //checks if file was opened
    if(file_ptr==NULL) {
        perror("File cannot be opened");
        exit(1);
    }
    size = fgetc(file_ptr);

    //fgets(line, 20, file_ptr); //reads a line from the file
    numRowsandCol = atoi(&size);
    char line[numRowsandCol+2];
    fgets(line, numRowsandCol+2, file_ptr);
    
    int i=0;
    while (!feof(file_ptr)) {
        //Read line by line and store values into matrix
        fgets(line, numRowsandCol+2, file_ptr);
        //printf("%s",line);
        for (int j=0; j<numRowsandCol; j++) {
            matrix[i][j] = line[j]-48;
        }
        i++;
    }
    fclose(file_ptr);
}

 /*
 //This function calculates the shortest path from the starting
 //node to all other nodes in the cost matrix.
 */
void dijkstra(void) {
    int chosenNodes[numRowsandCol]; //keeps track of chosen/unchosen nodes
    int cost[numRowsandCol];    //keeps track of the cost to get to each node from start node
    int path[numRowsandCol];
    
    //initialize all values in arrays to zero
    for (int i=0; i< numRowsandCol; i++) {
        chosenNodes[i] = 0;
        cost[i] = INFINITE;
        path[i]=0;
    }
    cost[startNode] = 0; //cost of node to itself is always zero
    
    for (int i=0; i<numRowsandCol-1; i++) {
        int chosenNodeIndex = minCostIndex(chosenNodes, cost); //least cost

        chosenNodes[chosenNodeIndex] = 1; //mark chosen node as chosen

        //update the neighbors of the chosen node
        for (int j=0; j < numRowsandCol; j++) {
                //not chosen        neighbors                       the combined cost from source neighbor is less than the previous cost
            if (!chosenNodes[j] && matrix[chosenNodeIndex][j]!=0 && cost[chosenNodeIndex] + matrix[chosenNodeIndex][j] < cost[j]) { //if not chosen and are neighbors
                cost[j] = cost[chosenNodeIndex] + matrix[chosenNodeIndex][j];
                path[j] = chosenNodeIndex;
            }
        }
    }
    printPath(cost, path);
}
//this checks the available nodes and their distance from the source node
int minCostIndex(int chosenNodes[], int cost[]) {
    int min = INFINITE;
    int minIndex = 0;
    for (int i =0; i < numRowsandCol; i++) {
        if (chosenNodes[i] == 0 && cost[i] <= min) { //looking at unchosen nodes
            min = cost[i];
            minIndex = i;
        }
    }
    return minIndex;
}
void printPath(int cost[], int path[]) {
    int reversePath[numRowsandCol];
//
//    for (int i=0; i < numRowsandCol; i++) {
//        printf("%c \t\t %d\n", 65+i, cost[i]);
//    }
    
    int index = endNode;
    int counter=0;
    //printf(" %c ", index+65);
    reversePath[counter++] = index+65;
    while (index!=startNode) {
        index = path[index];
        reversePath[counter++] = index+65;
        //printf(" %c ", index+65);
    }
    printf("Total Cost: %d\nPath Taken: ", cost[endNode]);
    counter-=1;
    while(reversePath[counter]!=endNode+65) {
        printf("%c->", reversePath[counter--]);
    }
    printf("%c\n", reversePath[counter]);
}
