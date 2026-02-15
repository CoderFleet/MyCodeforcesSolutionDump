#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int *numbers;
    int n;
    double result;
} ThreadData;

void* compute_average(void* arg) {
    ThreadData *data = (ThreadData*)arg;

    int sum = 0;
    for(int i = 0; i < data->n; i++)
        sum += data->numbers[i];

    data->result = (double)sum / data->n;

    return NULL;
}


int main(int argc, char *argv[]) {

    int n = argc - 1;
    int numbers[n];

    for(int i = 0; i < n; i++)
        numbers[i] = atoi(argv[i+1]);

    ThreadData data;
    data.numbers = numbers;
    data.n = n;

    pthread_t tid;
    pthread_create(&tid, NULL, compute_average, &data);
    pthread_join(tid, NULL);

    printf("Average = %.2f\n", data.result);

    return 0;
}
