//
//
//  Dijkstra's Algorithm
//  This program computes the shortest path from a starting
//  node to and ending node.
//
//  Created by Javier Gonzalez on 11/11/20.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#define INFINITE 999

int numRowsandCol = 0; //number of rows and columns in cost matrix
int **matrix; //holds the cost matrix
int startNode, endNode; //marks the start and destination

void read_from_file(void);
void dijkstra(void);
int minCostIndex(int [], int []);
void printPath(int [], int[]);

int main(void) {
    char nodeOne, nodeTwo;
    read_from_file(); //read in matrix from file along with its size

    printf("To exit program, type in X for starting node and ending node\n");
    while(1) {
        //prompts user for starting node and end node
        printf("Enter a starting node(%c-%c): ",65,numRowsandCol+64);
        scanf(" %c", &nodeOne);
        printf("Enter an ending node(%c-%c): ",65,numRowsandCol+64);
        scanf(" %c", &nodeTwo);
        
        //converts alphabet to correspond with matrix index
        startNode = toupper(nodeOne)-65;
        endNode = toupper(nodeTwo)-65;
        //need to check if the start and end node are valid else ask again for valid ones
        if((startNode>=numRowsandCol || startNode<0) || (endNode>=numRowsandCol || endNode<0)) {//out of range
            if (startNode==23 & endNode==23) { //break out to end program if desired by user
                break;
            }
            printf("Input is out of range of available nodes, try again.\n");
            continue;
        }
        dijkstra();
    }
    //frees the memory for the matrix
    for (int i=0; i < numRowsandCol; i++) {
        free(matrix[i]);
        matrix[i] = NULL;
    }
    free(matrix);
    matrix = NULL;
    
    return 0;
}
/*
// This function opens up the source file and loads in the
// the cost matrix.
*/
void read_from_file(void) {
    FILE *file_ptr = fopen("./Test_File.txt", "r"); //Open file
    char size; //holds the number of rows and columns

    //checks if file was opened
    if(file_ptr==NULL) {
        perror("File cannot be opened");
        exit(1);
    }
    //load in number of colums and rows
    size = fgetc(file_ptr);
    numRowsandCol = atoi(&size);
    //this is allocating the memory for the matrix based on the size being read from the file
    matrix = malloc(sizeof(int *)*numRowsandCol);
    for (int i=0; i < numRowsandCol; i++) {
        matrix[i] = malloc(sizeof(int)*numRowsandCol);
    }
    
    char line[numRowsandCol+2]; //stores each line of the file as it is being loaded in
    fgets(line, numRowsandCol+2, file_ptr); //skips file pointer to next line
    
    //Read line by line and store values into matrix
    int i=0;
    while (!feof(file_ptr)) {
        fgets(line, numRowsandCol+2, file_ptr);
        for (int j=0; j<numRowsandCol; j++) {
            matrix[i][j] = line[j]-48; //converts the ASCII values to match index of matrix (0-numRowsCol)
        }
        i++;
        if (i>=numRowsandCol) { //break out
            break;
        }
    }
    fclose(file_ptr);
}

 /*
 //This function calculates the shortest path from the starting
 //node to all other nodes in the cost matrix and passes the cost
 //and path taken to be printed to terminal.
 */
void dijkstra(void) {
    int chosenNodes[numRowsandCol]; //keeps track of chosen/unchosen nodes
    int cost[numRowsandCol];    //keeps track of the cost to get to each node from start node
    int path[numRowsandCol*2];    //keeps track of the path to get
    
    //initialize all values in arrays to zero
    for (int i=0; i< numRowsandCol; i++) {
        chosenNodes[i] = 0;
        cost[i] = INFINITE;
        path[i]=0;
    }
    cost[startNode] = 0; //cost of node to itself is always zero
    
    for (int i=0; i<numRowsandCol-1; i++) {
        int chosenNodeIndex = minCostIndex(chosenNodes, cost); //least cost index of available nodes

        chosenNodes[chosenNodeIndex] = 1; //mark least cost node as chosen

        //update the neighbors of the chosen node
        for (int j=0; j < numRowsandCol; j++) {
                //update only if not chosen, not itself, and neighbors of chosen node the combined cost is less than it was previously
            if (!chosenNodes[j] && matrix[chosenNodeIndex][j]!=0 && cost[chosenNodeIndex] + matrix[chosenNodeIndex][j] < cost[j]) {
                cost[j] = cost[chosenNodeIndex] + matrix[chosenNodeIndex][j]; //accumulates cost
                path[j] = chosenNodeIndex; //updates the path
            }
        }
    }
    printPath(cost, path);
}
//this checks the available nodes and their distance from the source node
//the index of the lowest cost node is then returned
int minCostIndex(int chosenNodes[], int cost[]) {
    int min = INFINITE; //set the temporary min value to infinite
    int minIndex = 0; //holds the index of the min cost node
    for (int i =0; i < numRowsandCol; i++) {
        if (chosenNodes[i] == 0 && cost[i] <= min) { //looking at unchosen nodes
            min = cost[i];
            minIndex = i;
        }
    }
    return minIndex;
}
void printPath(int cost[], int path[]) {
    int reversePath[numRowsandCol*2]; //will hold the path in correct order
    int index = endNode; //used for finding the path backwards
    int counter=0; //counts the number of times until start node is reached
    
    reversePath[counter++] = index+65;
    while (index!=startNode) {  //iterates through path backwards until start node is reached
        index = path[index];
        reversePath[counter++] = index+65;
    }
    //Prints the cost and path
    printf("Total Cost: %d\nPath Taken: ", cost[endNode]);
    counter-=1;
    while(reversePath[counter]!=endNode+65) {
        printf("%c->", reversePath[counter--]);
    }
    printf("%c\n", reversePath[counter]);
}
