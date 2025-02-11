#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <stdbool.h>
double euclidean_distance(double x1,double x2, double y1, double y2){
        double distance = sqrt(((x1 - x2)*(x1-x2)) + ((y1 - y2)*(y1-y2)));
        //printf("distance is = %f ", distance);
        return distance;
}


void print2DArray(double **array, int rows, int cols) {
    for (int i = 0; i < rows; i++) {        // Loop through rows
        for (int j = 0; j < cols; j++) {    // Loop through columns
            printf("%.2f ", array[i][j]);  // Print each element with 2 decimal places
        }
        printf("\n");                       // Newline after each row
    }
}
//test
typedef struct {
    double x;
    double y;
} Coordinate;

double **distance_matrix(Coordinate *coordinates){
    double **matrix = malloc(9 * sizeof(double *));
	for(int i = 0; i <= 9; i++){
		matrix[i] = malloc(9 * sizeof(double));
    }
    sizeof(**matrix);
    for(int i = 0; i<=9;i++){
        for(int j = 0;j<=9;j++){
            matrix[i][j] = euclidean_distance(coordinates[i].x,coordinates[j].x,coordinates[i].y,coordinates[j].y);
        }
    }

    //printf("location %f ", matrix[0][1]);
    print2DArray(matrix, 9, 9);
    //free(coordinates);
    return matrix;
    
}

/**
 * 
 * TODO: finding the closest Vertex
 * 
*/
/**
 * attempting to do a breakdown of smallest sum insertion step by step
*/

/**
 * start off with vertex Vi
*/
//define relevant arrays, define starting point

typedef struct {
    int* tour;
    int* visited;
    int* unvisited;
    int startingVertex;
    int visitedSize;
    int unvisitedSize;
    int tourCount;
} Arrays;

void returnArrays(Arrays* arr) {
    //Arrays arr;
    // we use the arr-> operator rather than the arr. operator as we are referencing a pointer to a struct
    arr->tour = (int*)malloc(10 * sizeof(int));
    arr->visited = (int*)malloc(9 * sizeof(int));
    arr->unvisited = (int*)malloc(9 * sizeof(int));

    //return arr; // Return struct containing the arrays
}

//helper function to remove items from the Unvisited array
void RemoveFromUnvisited(int IdxToRemove,Arrays* arr){

    //Starting from the end,push every item up one, up to Idx to remove, effectively removing that item

    for(int j =0;j<=arr->unvisitedSize;j++){
        if(arr->unvisited[j]==IdxToRemove){
            int PlaceHolder = INT_MAX;
            PlaceHolder = arr->unvisited[arr->unvisitedSize];
            arr->unvisited[arr->unvisitedSize] = arr->unvisited[j];
            arr->unvisited[j] = PlaceHolder;
            }
        }
    
}

void setUpArrays(Arrays* arr){
    //set starting vertex to 0;
    arr->startingVertex = 0;
    
    // define size of the unvisited and visited array
    arr->unvisitedSize =8;
    arr->visitedSize = 1;
    //increment count of items in the tour
    arr->tourCount = 1;

    // populate unvisited array with 1 to 9 as the array has not yet properly Visited any vertex, yet we start with 0 in the tour
    for(int i = 0; i<9;i++){
        arr->unvisited[i] = i;
    }
    arr->visited[0] = arr->startingVertex;
    //start the tour at 0
    arr->tour[0] = arr->startingVertex;

    RemoveFromUnvisited(arr->startingVertex,arr);
    arr->unvisitedSize--;
}

/**
 * find a vertex Vj such that the distance from all items in the partial tour is minimal
*/
// for every unvisited vertex, find distance from all items in the partial tour, and return the min vertex.
// once found, be sure to make the relevant changes to the arrays

int findClosestVertex(Arrays* arr, double **dist_matrix){

    //to find the closest vertex, i need to iterate over all items in the tour for each vertex, and return the closest one

    //iterate for each vertex
    double GlobalCost = DBL_MAX;
    for(int i = 0; i <= arr->unvisitedSize;i++){
        int currentVertex = arr->unvisited[i];
        double localCost = DBL_MAX;
        for(int j = 0; j<arr->tourCount;j++){
            
        }
    }
}

/**
 * Insert Vj between two connected vertices in the partial tour Vn and Vn+1, where n is a position in the partial tour
 * such that dist(vn,vj) + dist(Vn+1,Vj) - dist(Vn, Vn+1) is minimal
*/
//we want to close the starting loop AFTER we have found and inserted the first closest vertex.
//make sure insertion logic is correct, as in we are not moving items in the array.
/**
 * repeat steps 2 and 3 until all of the veritces have been visited
 * 
*/

void main(){
    Coordinate coordinates[] = {
        {867.8813832218043, 399.10334472405395},
        {263.5067701401023, 95.23581230656842},
        {949.1191382487299, 644.5029485036863},
        {940.7453325005885, 977.8121745416246},
        {968.1971754167525, 201.96289606671135},
        {978.9460051753653, 734.4678390438083},
        {426.372831602882, 293.7296237694936},
        {556.6539038363909, 719.5543505449659},
        {143.18918666443426, 756.1858968640379}
    };
    double **dist_matrix;
    dist_matrix = distance_matrix(coordinates);
    //array_size();
    
    //smallestSumInsertion(coordinates,dist_matrix);
    Arrays arr;
    //pass the address of arr to the function
    returnArrays(&arr);
    setUpArrays(&arr);
    //printf("cost at location %.2f", dist_matrix[0][1]);
    

}
