#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>
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
    printf("Size of pointer: %lu bytes \n",sizeof(**array1));

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

void smallestSumInsertion(Coordinate *coordinates, double **dist_matrix){


    //add index 0 as the starting point
    int* tour = (int*)malloc(10 * sizeof(int));

    double cost = 0;
    //visited
    double * visited = (double*)malloc(9 * sizeof(double));

    //put closing 0 in after first loop
    tour[0] = 0;
    visited[0] =0;
    
    int tourCount = 1;

    for(int i = 0; i < 10;i++){
        if(i == 1){
            tour[1] = 0;
            tourCount++;
        } 
    }

        /**
         * 
         * gets the closest node and its index
        */
        for(int i = 0; i<10;i++){

           // double CurrentCost = DBL_MAX;
            //first find the closest from 0
            double globalClosest = DBL_MAX;
            int globalClosestidx = INT_MAX;

            for(int j = 0;j<9;j++){
                double localClosest = dist_matrix[i][j];
                if(localClosest < globalClosest && localClosest != 0){
                    globalClosest = localClosest;
                    globalClosestidx = j;
                }    
            }
            //printf("Global closest distance is: %f", globalClosest);
            //printf("Global closest index is: %d", globalClosestidx);


            //perhaps this should be set up to choose the higher index in a tie-break 
            double GlobalMinDist = DBL_MAX;
            int globalMinDistIdx = INT_MAX;
            for(int j = 0;j<tourCount;j++){
                
                //printf("tour j =,%d\n", tour[j]);
                //printf("tour j+1 =,%d\n", tour[j+1]);
                //printf("GlobalClosestIndex =,%d\n", globalClosestidx);


                //printf("First condition %f\n",dist_matrix[tour[j]][globalClosestidx]);
                //printf("Second condition %f\n",dist_matrix[tour[j+1]][globalClosestidx]);
                //printf("Third Condition %f\n",dist_matrix[tour[j]][tour[j+1]]);

                //insert the closest Index first, then check for best position, ensure it does not check at either ends
                //we are finding the optimal index not including tour[0] and tour[n]
                for(int k = 1;k<tourCount-1;k++){
                    //make a gap, check cost

                    //tour[k+1] = tour[k];
                    tour[k] = globalClosestidx;

                    double localMinDist = dist_matrix[tour[k]][globalClosestidx] + dist_matrix[tour[k+1]][globalClosestidx] - dist_matrix[tour[k]][tour[k+1]];
                    printf("localMinDist is: %f\n", localMinDist);
                    printf("localMinDistidx is: %d\n", k);
                
                    if(localMinDist <= GlobalMinDist && localMinDist != 0 && k != 0){
                        GlobalMinDist = localMinDist;
                        globalMinDistIdx = k;
                    }
                    printf("globalMinDistIdx is: %d\n", globalMinDistIdx);
                }


                //double localMinDist = dist_matrix[tour[j]][globalClosestidx] + dist_matrix[tour[j+1]][globalClosestidx] - dist_matrix[tour[j]][tour[j+1]];
               
                //printf("for value: %d\n",globalClosestidx);
                //printf("localMinDist is: %f\n", localMinDist);
                //printf("localMinDistidx is: %d\n", j);
                
                //if(localMinDist <= GlobalMinDist && localMinDist != 0 && j!=0){
                  //  GlobalMinDist = localMinDist;
                  //  globalMinDistIdx = j;
                //}
               // printf("globalMinDistIdx is: %d\n", globalMinDistIdx);
            }
            //printf("globalMinDistIdx is: %d\n", globalMinDistIdx);
            
            //this will be changing the value at the index, instead of pushing everything

            //we can iterate up to globalMinDistIdx, and push everything ahead up by one
            //to ensure the starting loop remains correct, we could add a condition that will
            //only do this if an integer is in the place we want to insert in
            //for(int j =0;j<tourCount;j++){
                //if(j == globalMinDistIdx){
                   // tour[j+1] = tour[j];
              //  }
           // }
           // tour[globalMinDistIdx] = globalClosestidx;


            printf("Current tour : \n");
            for(int j = 0; j<tourCount;j++){
                printf("%d,",tour[j]);
            }


            tourCount++;
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
