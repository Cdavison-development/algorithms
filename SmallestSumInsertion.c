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

void array_size(){
    double **array1 = malloc(9 * sizeof(double *));
	for(int i = 0; i <= 9; i++){
		array1[i] = malloc(9 * sizeof(double));
    }
   // printf("Size of pointer: %lu bytes \n",sizeof(**array1));

}


/**
 * 
 *  The smallest sum insertion algorithm starts the tour with the vertex with the lowest index.
    In this case that is vertex 0. Each step, it selects a currently unvisited vertex where the
    total edge cost to all the vertices in the partial tour is minimal. It then inserts it between
    two connected vertices in the partial tour where the cost of inserting it between those two
    connected vertices is minimal.
    These steps can be followed to implement the smallest sum insertion algorithm. Assume
    that the indices i,j,k etc; are vertex labels unless stated otherwise. In a tiebreak situation,
    always pick the lowest index(indices)
 * 
 *  basically, find the vertex that has the lowest cost to add, then insert it between two vertices in the tour
 *  where the cost of inserting it is the lowest
 * 
 * 
 *  needs:
 *  define a metric for overall tour cost
*/


/**
 * 
 * TODO: The tour is replacing values and inserting a 0, rather than re-arranging
 * 
 * 
*/
void smallestSumInsertion(Coordinate *coordinates, double **dist_matrix){


    //add index 0 as the starting point
    int* tour = (int*)malloc(10 * sizeof(int));

    double cost = 0;
    //visited
    int * visited = (int*)malloc(9 * sizeof(int));
    int * unvisited = (int*)malloc(9 * sizeof(int));

    for(int i = 0; i<=8;i++){
        unvisited[i] = i;  
    }

    //put closing 0 in after first loop
    tour[0] = 0;
    visited[0] =0;
    tour[1] = 0;
    int VisitedCount = 1;
    int tourCount = 2;
    int UnvisitedCount = 8;
    //printf("Test");
        /**
         * 
         * gets the closest node and its index
        */
       //could convert this to a while
       
    for(int i = 0; i<10;i++){

           // double CurrentCost = DBL_MAX;
            //first find the closest from 0
        double globalClosest = DBL_MAX;
        int globalClosestidx = INT_MAX;

        
        // We need to go up with the size of the tour
        for(int j = 0;j<UnvisitedCount;j++){
            //printf("Closest sum %f", ClosestSum);
            double ClosestSum = 0;
           // bool Visited = true;
            //printf("Closest sum %f", ClosestSum);
            printf("j %d : ", j);
            for(int k = 0;k<tourCount-1;k++){
                printf("k %d : ", k);
                ClosestSum += dist_matrix[tour[k]][unvisited[j]];
                //if(ClosestSum < globalClosest && ClosestSum != 0 && Visited == false){
            }
            bool Visited = false;
                //printf("localClosest : %d", localClosest);
                for(int v = 0;v<UnvisitedCount;v++){ 
                    if(j != unvisited[v]){
                        Visited = true;
                        break;
                    }
                }
                printf("Closest sum %f", ClosestSum);
                if(ClosestSum < globalClosest && ClosestSum != 0){
                        globalClosest = ClosestSum;
                        globalClosestidx = j;       
                        printf("closest index = %d",j);
                        printf("Local closest : %f" ,globalClosest);
                    } 
            //printf("Visited[v]: %d", visited[v]);
        }
        

/**
        for(int j = 0;j<9;j++){
            // This needs to be the sum of distances from each unvisited vertex to the
            // existing partial tour vertices, so for example, does vertex 3 return the lowest sum 

            //loop through all unvisited vertices, and find the one that returns the lowest 
            //dist between this vertice and all vertices currently in the tour.



            double localClosest = dist_matrix[i][j];
            bool inVisited = false;
            //printf("localClosest : %d", localClosest);
            for(int v = 0;v<VisitedCount;v++){ 
                if(j == visited[v]){
                    inVisited = true;
                    break;
                }
            }
            //printf("Visited[v]: %d", visited[v]);
            if(localClosest < globalClosest && localClosest != 0 && inVisited == false){
                        globalClosest = localClosest;
                        globalClosestidx = j;       
                        printf("j = %d",j);
                        printf("Local closest : %f" ,localClosest);
                    } 
        }
        **/
            //printf("Global closest distance is: %f", globalClosest);
            //printf("Global closest index is: %d", globalClosestidx);


            //perhaps this should be set up to choose the higher index in a tie-break 
            double GlobalMinDist = DBL_MAX;
            int globalMinDistIdx = INT_MAX;
            for(int k = 0;k<tourCount;k++){
                    double localMinDist = dist_matrix[tour[k]][globalClosestidx] + dist_matrix[tour[k+1]][globalClosestidx] - dist_matrix[tour[k]][tour[k+1]];
                    //printf("localMinDist is: %f\n", localMinDist);
                    //printf("localMinDistidx is: %d\n", k);        
                    if(localMinDist < GlobalMinDist && localMinDist != 0 && k != 0 && k != tourCount){
                        GlobalMinDist = localMinDist;
                        globalMinDistIdx = k;
                        printf("globalMinDist is: %f\n", GlobalMinDist);
                        printf("globalMinDistIdx is: %d\n", globalMinDistIdx);
                    }
            }
            printf("global Closest Index is is: %d\n", globalClosestidx);

            for(int j = 10;j>=globalMinDistIdx;j--){
                //int OverwrittenVal = tour[j + 1];
                //tour[j + 1] = tour[j];

                tour[j] = tour[j-1];

            }
            //tour[globalMinDistIdx + 1] = tour[globalMinDistIdx];
            tour[globalMinDistIdx] = globalClosestidx;
            visited[VisitedCount] = globalClosestidx;
            //remove global closest index from unvisited
            //rather than remove global closest index, swap with item at the end, and deincrement Unvisited count, so this
            //value is not within the scope anymore
            for(int j =0;j<=UnvisitedCount;j++){
                if(unvisited[j]==globalClosestidx){
                    int PlaceHolder = INT_MAX;
                    PlaceHolder = unvisited[UnvisitedCount];
                    unvisited[UnvisitedCount] = unvisited[j];
                    unvisited[j] = PlaceHolder;
                }
            }
            

            //printf("TourCount is: %d", tourCount);
            printf("Current tour : \n");
            for(int j = 0; j<=tourCount;j++){
                printf("%d,",tour[j]);
            }
            printf("\n");
            printf("Current visited : \n");
            for(int j = 0; j<=VisitedCount;j++){
                printf("%d,",visited[j]);
            }
            printf("\n");

            VisitedCount++;
            tourCount++;
            UnvisitedCount--;
            //printf("globalMinDistIdx is: %d", globalMinDistIdx);
            
            //insert global closest idx into the globalMinDistIdx

    }
}


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
    array_size();
    
    smallestSumInsertion(coordinates,dist_matrix);
    //printf("cost at location %.2f", dist_matrix[0][1]);
    

}
