//Deepkumar Patel, dgp52, 145005704
//Viraj Patel, vjp60, 168001058

#include <stdio.h>
#include "mymalloc.h"
#include <time.h>
#include <sys/time.h>

 int time_it_took[6];
int  successful_allocations[6];
int  failed_allocations[6];
//char workloads[] = {'A','B','C','D','E','F'};



void workLoadA() {
    struct timeval start[100], end[100];
    successful_allocations[0] = 0;
    failed_allocations[0] = 0;
    int j;
        for (j = 0; j < 100; j++){
        gettimeofday(&start[j], NULL);
    char *p[3000];
    int i;
//    printf("-----malloc() 1 byte 3000 times-----\n");
    for (i = 0; i < 3000; i++) {
       p[i] = (char*)malloc(1);
       if(p[i]!=NULL) {
            successful_allocations[0]++;
       } else {
           failed_allocations[0]++;
       }
    }

//    printf("-----free() 3000 1 byte pointers-----\n");
    for (i = 0; i < 3000; i++) {
        free(p[i]);
    }
        gettimeofday(&end[j], NULL);
    }
     long int time = 0;
    int k;
    for (k = 0; k<100; k++){
        time += ((end[k].tv_sec * 1000000 + end[k].tv_usec) - (start[k].tv_sec * 1000000 + start[k].tv_usec));
    }
    
    time /= 100;
    time_it_took[0] = time;
    successful_allocations[0] /= 100;
    failed_allocations[0] /= 100;
}

void workLoadB(){
    struct timeval start[100], end[100];
    successful_allocations[1] = 0;
    failed_allocations[1] = 0;
    int j;
        for (j = 0; j < 100; j++){
        gettimeofday(&start[j], NULL);
//    printf("-----malloc() 1 byte 1 time-----\n");
        char *p;
        p = (char*)malloc(1);
        if(p != NULL) {
                successful_allocations[1]++;
           } else {
               failed_allocations[1]++;
           }
    //    printf("-----free() 3000 1 byte pointers-----\n");
        int i;
        for (i = 0; i < 3000; i++) {
            free(p);
        }
        gettimeofday(&end[j], NULL);
    }
     long int time = 0;
    int k;
    for (k = 0; k<100; k++){
        time += ((end[k].tv_sec * 1000000 + end[k].tv_usec) - (start[k].tv_sec * 1000000 + start[k].tv_usec));
    }
    
    time /= 100;
    time_it_took[1] = time;
    // successful_allocations[1] /= 100;
    // failed_allocations[1] /= 100;
}

void workLoadC(){
    struct timeval start[100], end[100];
    successful_allocations[2] = 0;
    failed_allocations[2] = 0;
    int j;
        for (j = 0; j < 100; j++){
        gettimeofday(&start[j], NULL);
    char *p[3000];
    int i;
//    printf("-----malloc() 1 byte 3000 times-----\n");
    for (i = 0; i < 3000; i++) {
       p[i] = (char*)malloc(1);
       if(p[i]!=NULL) {
//            printf("Memory allocated @%p \n",p[i]);
            successful_allocations[2]++;
       } else {
//            printf("WorkLoadC Allocation Failed!");
            failed_allocations[2]++;
       }
    }
//    printf("-----free() 3000 1 byte pointers-----\n");
    for (i = 0; i < 3000; i++) {
        free(p[i]);
    }
        gettimeofday(&end[j], NULL);
    }
     long int time = 0;
    int k;
    for (k = 0; k<100; k++){
        time += ((end[k].tv_sec * 1000000 + end[k].tv_usec) - (start[k].tv_sec * 1000000 + start[k].tv_usec));
    }
    
    time /= 100;
    time_it_took[2] = time;
    successful_allocations[2] /= 100;
    failed_allocations[2] /= 100;
}

void workLoadD(){
    struct timeval start[100], end[100];
    successful_allocations[3] = 0;
    failed_allocations[3] = 0;
    int j;
        for (j = 0; j < 100; j++){
        gettimeofday(&start[j], NULL);
    char *p[2500];
    int i;
//    printf("-----malloc() 6 byte 2500 times-----\n");
    for (i = 0; i < 2500; i++) {
       p[i] = (char*)malloc(6);
       if(p[i]!=NULL) {
//            printf("Memory allocated @%p \n",p[i]);
            successful_allocations[3]++;
       } else {
//            printf("WorkLoadD Allocation Failed!");
            failed_allocations[3]++;
       }
    }
//    printf("-----free() 2500 6 byte pointers-----\n");
    for (i = 0; i < 2500; i++) {
        free(p[i]);
    }
        gettimeofday(&end[j], NULL);
    }
    long int time = 0;
    int k;
    for (k = 0; k<100; k++){
        time += ((end[k].tv_sec * 1000000 + end[k].tv_usec) - (start[k].tv_sec * 1000000 + start[k].tv_usec));
    }
    
    time /= 100;
    time_it_took[3] = time;
    successful_allocations[3] /= 100;
    failed_allocations[3] /= 100;
}

void workLoadE(){
    struct timeval start[100], end[100];
    successful_allocations[4] = 0;
    failed_allocations[4] = 0;
    int j;
        for (j = 0; j < 100; j++){
        gettimeofday(&start[j], NULL);
    char *p[3000];
    int i;
//    printf("-----malloc() 1 byte and free immediately 3000 times-----\n");
    for (i = 0; i < 3000; i++) {
       p[i] = (char*)malloc(1);
       if(p[i]!=NULL) {
            successful_allocations[4]++;
       } else {
           failed_allocations[4]++;
       }
       free(p[i]);
    }
//    printf("-----malloc() 6 byte 2500 times-----\n");
    for (i = 0; i < 2500; i++) {
       p[i] = (char*)malloc(6);
       if(p[i]!=NULL) {
            successful_allocations[4]++;
       } else {
           failed_allocations[4]++;
       }
    }
    char *a = malloc(1);
    free(a);
//    printf("-----free() 2500 6 byte pointers-----\n");
    for (i = 0; i < 2500; i++) {
        free(p[i]);
    }
        gettimeofday(&end[j], NULL);
    }
    long int time = 0;
    int k;
    for (k = 0; k<100; k++){
        time += ((end[k].tv_sec * 1000000 + end[k].tv_usec) - (start[k].tv_sec * 1000000 + start[k].tv_usec));
    }
    
    time /= 100;
    time_it_took[4] = time;
    successful_allocations[4] /= 100;
    failed_allocations[4] /= 100;
}

void workLoadF(){
    struct timeval start[100], end[100];
    successful_allocations[5] = 0;
    failed_allocations[5] = 0;
    int j;
        for (j = 0; j < 100; j++){
        gettimeofday(&start[j], NULL);
//    printf("-----Redundant freeing the same pointer-----\n");
    char *a = malloc(1);
    free(a);
    free(a);
//    printf("-----malloc() 1 byte 1500 times-----\n");
    char *p[1500];
    int i;
    for(i = 0;i<1500;i++){
        p[i] = (char*)malloc(1);
        if(p[i]!=NULL) {
            successful_allocations[5]++;
       } else {
           failed_allocations[5]++;
       }
    }
//    printf("-----malloc() 1 byte 1500 times again-----\n");
    char *pp[1500];
    for(i = 0;i<1500;i++){
        pp[i] = (char*)malloc(1);
        if(p[i]!=NULL) {
            successful_allocations[5]++;
       } else {
           failed_allocations[5]++;
       }
    }
//    printf("-----free() first 1500 pointers-----\n");
    for(i = 0;i<1500;i++){
        free(p[i]);
    }
//    printf("-----free() second 1500 pointers-----\n");
    for(i = 0;i<1500;i++){
        free(pp[i]);
    }
        gettimeofday(&end[j], NULL);
    }
     long int time = 0;
    int k;
    for (k = 0; k<100; k++){
        time += ((end[k].tv_sec * 1000000 + end[k].tv_usec) - (start[k].tv_sec * 1000000 + start[k].tv_usec));
    }
    
    time /= 100;
    time_it_took[5] = time;
    successful_allocations[5] /= 100;
    failed_allocations[5] /= 100;
    
}

int main() {
    printf("----------------------------------------------------------------------------------------\n");
    printf("Workload A: malloc() 1 byte 3000 times, then free() the 3000 1 byte pointers one by one\n");
    printf("----------------------------------------------------------------------------------------\n");
    workLoadA();

    printf("------------------------------------------------------------------------\n");
    printf("Workload B: malloc() 1 byte and immediately free it 3000 times in a row\n");
    printf("------------------------------------------------------------------------\n");
    workLoadB();

    printf("----------------------------------------------------------------------------------\n");
    printf("Workload C: malloc() 1 byte 3000 times and free them. Keep track of all operation\n");
    printf("----------------------------------------------------------------------------------\n");
    workLoadC();

    printf("----------------------------------------------------------------------------------\n");
    printf("Workload D: malloc() 6 byte 2500 times and free them. Keep track of all operation\n");
    printf("----------------------------------------------------------------------------------\n");
    workLoadD();

    printf("------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("Workload E: malloc() 1 byte and free immediately, keep doing this for 3000 times. Then malloc() 6 byte 2500 times and free them all\n");
    printf("------------------------------------------------------------------------------------------------------------------------------------\n");
    workLoadE();

    printf("---------------------------------------------------------------------------------------------------------------------\n");
    printf("Workload F: Redundant free, free() unallocated memory then allocate 1 byte 1500 times twice, finally free everything\n");
    printf("---------------------------------------------------------------------------------------------------------------------\n");
    workLoadF();
    int p;
    for (p = 0; p<6;p++){
        printf("the time it took for workload %d to run 100 times, is %d\n",p,time_it_took[p]);
        printf("\tnumber of allocations failed in this workload is: %d\n",failed_allocations[p]);
        printf("\tnumber of allocations succeeded in this workload is: %d\n",successful_allocations[p]);
    }
    return 0;
}
