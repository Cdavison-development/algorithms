//initialise 4 different arrays, each representing a thread, initialise with zeros
#include <omp.h>
#include <stdio.h>
#include <unistd.h> // For usleep()
void serialised_update(){
    
    int thread1[10];
    int thread2[10];
    int thread3[10];
    int thread4[10];


    for (int i = 0; i < 10; i++) {
        thread1[i] = 0;
        thread2[i] = 0;
        thread3[i] = 0;
        thread4[i] = 0;
    }

    printf("| %10s | %10s | %10s | %10s |\n", "Thread1", "Thread2", "Thread3", "Thread4");
    printf("----------------------------------------------------------\n");

    // Print values in a column format
    for (int i = 0; i < 10; i++) {
        printf("| %10d | %10d | %10d | %10d |\n", thread1[i], thread2[i], thread3[i], thread4[i]);
    }

    for (int i = 0; i < 10; i++) {
        thread1[i] = 1;
        thread2[i] = 1;
        thread3[i] = 1;
        thread4[i] = 1;
        printf("| %10s | %10s | %10s | %10s |\n", "Thread1", "Thread2", "Thread3", "Thread4");
        printf("----------------------------------------------------------\n");

    // Print values in a column format
        for (int i = 0; i < 10; i++) {
            printf("| %10d | %10d | %10d | %10d |\n", thread1[i], thread2[i], thread3[i], thread4[i]);
        }
    }
}



void print_arrays(int thread1[], int thread2[], int thread3[], int thread4[], int size) {
    printf("\033[H\033[J"); // Clear the screen
    printf("thread1 = [");
    for (int i = 0; i < size; i++) {
        printf("%d", thread1[i]);
    }
    printf("]\n");

    printf("thread2 = [");
    for (int i = 0; i < size; i++) {
        printf("%d", thread2[i]);
    }
    printf("]\n");

    printf("thread3 = [");
    for (int i = 0; i < size; i++) {
        printf("%d", thread3[i]);
    }
    printf("]\n");

    printf("thread4 = [");
    for (int i = 0; i < size; i++) {
        printf("%d", thread4[i]);
    }
    printf("]\n");
    fflush(stdout); // Ensure the output is displayed immediately
}

void parallel_update() {
    int thread1[30] = {0};
    int thread2[30] = {0};
    int thread3[30] = {0};
    int thread4[30] = {0};

    // Print initial state
    print_arrays(thread1, thread2, thread3, thread4, 30);

    // Parallel update of arrays
    #pragma omp parallel for
    for (int i = 0; i < 30; i++) {
        // Update arrays incrementally
        thread1[i] = 1;
        #pragma omp critical
        {
            print_arrays(thread1, thread2, thread3, thread4, 30);
            usleep(50000); // Delay for visualization
        }

        thread2[i] = 1;
        #pragma omp critical
        {
            print_arrays(thread1, thread2, thread3, thread4, 30);
            usleep(50000); // Delay for visualization
        }

        thread3[i] = 1;
        #pragma omp critical
        {
            print_arrays(thread1, thread2, thread3, thread4, 30);
            usleep(50000); // Delay for visualization
        }

        thread4[i] = 1;
        #pragma omp critical
        {
            print_arrays(thread1, thread2, thread3, thread4, 30);
            usleep(50000); // Delay for visualization
        }
    }
}

int main() {
    parallel_update();
    return 0;
}