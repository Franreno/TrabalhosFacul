
  
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
 
#define A 5
#define thinking 2
#define hunger 1
#define eat 0
#define Lef (Number + 4) % A
#define right (Number + 1) % A
 
int PhilStates[A];
int phil[A] = { 0, 1, 2, 3, 4 };
 
sem_t mutex;
sem_t semp[A];
 
void maint(int Number)
{
    if (PhilStates[Number] == hunger
        && PhilStates[Lef] != eat
        && PhilStates[right] != eat) {
        // PhilStates that eat
        PhilStates[Number] = eat;
 
        sleep(2);
 
        printf("Philosopher %d picks up fork %d and %d\n",
                      Number + 1, Lef + 1, Number + 1);
 
        printf("Philosopher %d is eating\n", Number + 1);
 
      
        sem_post(&semp[Number]);
    }
}
 
// take up chopsticks
void Pick_Fork(int Number)
{
 
    sem_wait(&mutex);
 
    // PhilStates that hunger
    PhilStates[Number] = hunger;
 
    printf("Philosopher %d is hunger\n", Number + 1);
 
    // eat if neighbours are not eat
    maint(Number);
 
    sem_post(&mutex);
 
    // if unable to eat wait to be signalled
    sem_wait(&semp[Number]);
 
    sleep(1);
}
 
// put down chopsticks
void Drop_Fork(int Number)
{
 
    sem_wait(&mutex);
 
    // PhilStates that thinking
    PhilStates[Number] = thinking;
 
    printf("Philosopher %d putting fork %d and %d down\n",
           Number + 1, Lef + 1, Number + 1);
    printf("Philosopher %d is thinking\n", Number + 1);
 
    maint(Lef);
    maint(right);
 
    sem_post(&mutex);
}
 
void* SELF(void* num)
{
 
    while (1) {
 
        int* m = num;
 
        sleep(1);
 
        Pick_Fork(*m);
 
        sleep(0);
 
        Drop_Fork(*m);
    }
}
 
int main()
{
 
    int k;
    pthread_t thread_id[A];
 
    // initialize the semaphores
    sem_init(&mutex, 0, 1);
 
    for (k = 0; k < A; k++)
 
        sem_init(&semp[k], 0, 0);
 
    for (k = 0; k < A; k++) {
 
        // create philosopher processes
        pthread_create(&thread_id[k], NULL,
                       SELF, &phil[k]);
 
        printf("Philosopher %d is thinking\n", k + 1);
    }
 
    for (k = 0; k < A; k++)
 
        pthread_join(thread_id[k], NULL);
}