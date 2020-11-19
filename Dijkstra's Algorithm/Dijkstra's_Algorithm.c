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

int numRowsandCol = 0;
int matrix[M_SIZE][M_SIZE];
int startNode, endNode;

void read_from_file(void);
void dijkstra(void);
void printPath(void);

int main(void) {
    char nodeOne, nodeTwo;
    read_from_file();
    
    while(startNode!='x') {
        printf("Enter a starting node(A-H): ");
        scanf(" %c", &nodeOne);
        printf("Enter an ending node(A-H): ");
        scanf(" %c", &nodeTwo);
        //converts alphabet to correspond with matrix index
        startNode = tolower(nodeOne)-97;
        endNode = tolower(nodeTwo)-97;
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
    char line[20];

    //checks if file was opened
    if(file_ptr==NULL) {
        perror("File cannot be opened");
        exit(1);
    }
    
    fgets(line, 20, file_ptr); //reads a line from the file
    numRowsandCol = atoi(&line[0]);
    
    int i=0;
    while (!feof(file_ptr)) {
        //Read line by line and store values into matrix
        fgets(line, 20, file_ptr);
        printf("%s",line);
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
    
    //initialize all values in arrays to zero
    for (int i=0; i< numRowsandCol; i++) {
        chosenNodes[i] = 0;
        cost[i] = 0;
    }
    chosenNodes[startNode] = 1; //mark the starting node as chosen
    
    
    
    
    
    
}
void printPath(void) {
    
    
    
}
