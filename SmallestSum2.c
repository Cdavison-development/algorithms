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
            int PlaceHolder = arr->unvisited[arr->unvisitedSize];
            //PlaceHolder = arr->unvisited[arr->unvisitedSize];
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
    int cheapestVertex = INT_MAX;
    for(int i = 0; i <= arr->unvisitedSize;i++){
        int currentVertex = arr->unvisited[i];
        printf("The current vertex is %d",currentVertex);
        printf("\n");
        double localCost = 0;
            for(int j = 0; j<arr->tourCount;j++){
                //printf("testing dist matrix %f", dist_matrix[currentVertex][arr->tour[j]]);
                localCost += dist_matrix[currentVertex][arr->tour[j]];  
                printf("The local cost is %f",localCost);        
            }
        
            if(localCost < GlobalCost){
                GlobalCost = localCost;
                cheapestVertex = currentVertex;
            }
        }
        printf("\nThe lowest global cost is %f",GlobalCost);
        printf("\nThe cheapest vertex is %d",cheapestVertex);
    return cheapestVertex;
}


/**
 * Insert Vj between two connected vertices in the partial tour Vn and Vn+1, where n is a position in the partial tour
 * such that dist(vn,vj) + dist(Vn+1,Vj) - dist(Vn, Vn+1) is minimal
*/
//we want to close the starting loop AFTER we have found and inserted the first closest vertex.
//make sure insertion logic is correct, as in we are not moving items in the array.
/**
 * repeat steps 2 and 3 until all of the vertices have been visited
 * 
*/
int FindBestInsertionIdx(Arrays* arr, double **dist_matrix, int CheapestVertex){

            double GlobalMinDist = DBL_MAX;
            int GlobalCheapestInsertionIdx = INT_MAX;
            //iterate over tour, I am unsure whether we need i< or i<= so keep this in mind during testing
            for(int i =0; i<=arr->tourCount;i++){
                double localMinDist = dist_matrix[arr->tour[i]][CheapestVertex] + dist_matrix[arr->tour[i+1]][CheapestVertex] - dist_matrix[arr->tour[i]][arr->tour[i+1]];
                int localCheapestInsertionIdx = i;


                if(localMinDist < GlobalMinDist){
                    GlobalMinDist = localMinDist;
                    GlobalCheapestInsertionIdx = localCheapestInsertionIdx;
                }
                printf("\nInserting  %d between %d and %d : Cost increase %f", CheapestVertex,arr->tour[i],arr->tour[i+1],localMinDist);
                //printf("\nThe cheapest insertion index for for %d is : %d", arr->tour[i],localCheapestInsertionIdx);
            }
            printf("\nThe Global Min dist is : %f",GlobalMinDist);
            printf("\nThe cheapest insertion index is : %d",GlobalCheapestInsertionIdx);

            return GlobalCheapestInsertionIdx;
            //remember to account for adding the closing 0 to the end of the tour.

        // now that i have the best insertion idx, i need to remove it from unvisited, and add to the tour.
}

// now that i have the best insertion idx, i need to remove it from unvisited, and add to the tour, and do all relevant handling.
void InsertVertex(Arrays* arr, double **dist_matrix, int CheapestInsertionIdx, int CheapestVertex){

    //just need to push up all other items in the array
            for(int j = arr->tourCount;j>CheapestInsertionIdx;j--){
                arr->tour[j] = arr->tour[j-1];
            }
            arr->tour[CheapestInsertionIdx] = CheapestVertex;

            printf("Current tour : \n");
            for(int j = 0; j<=arr->tourCount;j++){
                printf("%d,",arr->tour[j]);
            }
            // **ensure this works as expected in testing**
            RemoveFromUnvisited(CheapestVertex,arr);
            arr->tourCount++;
            //printf("TourCount is : %d", arr->tourCount);
            arr->unvisitedSize--;
}

void SmallestSumInsertion(Arrays* arr){
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


    returnArrays(arr);
    setUpArrays(arr);
    double **dist_matrix;
    dist_matrix = distance_matrix(coordinates);
    for(int i = 0; i < 10;i++){
    int ClosestVertex = findClosestVertex(arr,dist_matrix);
    int BestInsertionIdx = FindBestInsertionIdx(arr,dist_matrix,findClosestVertex(arr,dist_matrix));
    InsertVertex(arr,dist_matrix,BestInsertionIdx,ClosestVertex);
    //ensure that this handling is correct also
    //if(arr->tourCount == 2){
       // arr->tour[2] == 0;
        //arr->tourCount++;
    //}
    }
    printf("Final tour : \n");
        for(int j = 0; j<=arr->tourCount;j++){
            printf("%d,",arr->tour[j]);
        }
    
}
void main(){

    Arrays arr;

    SmallestSumInsertion(&arr);
    
}
