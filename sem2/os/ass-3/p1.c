#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

sem_t resourceAccess;
sem_t readTry;
pthread_mutex_t mxReaderCount;
pthread_mutex_t mxWriterCount;

int readerCount = 0;
int writerCount = 0;
int sharedData = 100;

void *reader(void *arg) {
  int id = *((int *)arg);

  sem_wait(&readTry);

  pthread_mutex_lock(&mxReaderCount);
  readerCount++;
  if (readerCount == 1) {
    sem_wait(&resourceAccess);
  }
  pthread_mutex_unlock(&mxReaderCount);

  sem_post(&readTry);

  printf("Reader %d: Reading shared data = %d\n", id, sharedData);
  sleep(1);

  pthread_mutex_lock(&mxReaderCount);
  readerCount--;
  if (readerCount == 0) {
    sem_post(&resourceAccess);
  }
  pthread_mutex_unlock(&mxReaderCount);

  pthread_exit(NULL);
}

void *writer(void *arg) {
  int id = *((int *)arg);

  pthread_mutex_lock(&mxWriterCount);
  writerCount++;
  if (writerCount == 1) {
    sem_wait(&readTry);
  }
  pthread_mutex_unlock(&mxWriterCount);

  sem_wait(&resourceAccess);

  sharedData += 50;
  printf("[!] Writer %d: UPDATED shared data to = %d\n", id, sharedData);
  sleep(1);

  sem_post(&resourceAccess);

  pthread_mutex_lock(&mxWriterCount);
  writerCount--;
  if (writerCount == 0) {
    sem_post(&readTry);
  }
  pthread_mutex_unlock(&mxWriterCount);

  pthread_exit(NULL);
}

int main() {
  int numReaders = 4;
  pthread_t rId[3], wId;

  // scanf("%d", &numReaders);
  int rNum[numReaders];

  for (int i = 0; i < numReaders; i++) {
    rNum[i] = i;
  }
  int wNum = 1;

  sem_init(&resourceAccess, 0, 1);
  sem_init(&readTry, 0, 1);
  pthread_mutex_init(&mxReaderCount, NULL);
  pthread_mutex_init(&mxWriterCount, NULL);

  printf("Execution Started\n");

  for (int i = 0; i < numReaders; i++) {
    pthread_create(&rId[i], NULL, reader, &rNum[i]);
  }
  pthread_create(&wId, NULL, writer, &wNum);

  for (int i = 0; i < numReaders; i++) {
    pthread_join(rId[i], NULL);
  }
  pthread_join(wId, NULL);

  sem_destroy(&resourceAccess);
  sem_destroy(&readTry);
  pthread_mutex_destroy(&mxReaderCount);
  pthread_mutex_destroy(&mxWriterCount);

  printf("All threads finished. Program closing safely.\n");
  return 0;
}
