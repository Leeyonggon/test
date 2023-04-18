#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 2
#define MAXDELAY 1000000
#define N_PUT 20
#define N_GET 20
#define rand2() ((double)rand()/RAND_MAX)

struct buffer {
   int buf[BUFSIZE];
   int in;
   int out;
   int count;
};

void initbuf(struct buffer* p);
void* producer(void* arg);
void* consumer(void* arg);
void putmsg(struct buffer* p, int msg);
int getmsg(struct buffer* p);

int main()
{
   struct buffer bbuf;
   pthread_t tid_1, tid_2;

   initbuf(&bbuf);

   pthread_create(&tid_1, NULL, producer, &bbuf);
   pthread_create(&tid_2, NULL, consumer, &bbuf);

   pthread_join(tid_1, NULL);
   pthread_join(tid_2, NULL);

   return 0;
}
void initbuf(struct buffer* p)
{
   p->in = p->out = p->count = 0;
}
void* producer(void* arg)
{
   struct buffer* p = (struct buffer*)arg;
   int msg = 0;
   int i;

   for (i = 0; i < N_PUT; i++) {
      usleep(rand2() * MAXDELAY);
      msg++;
      printf("insert message %d\n", msg);
      putmsg(p, msg);
   }
}
void* consumer(void* arg)
{
   struct buffer* p = (struct buffer*)arg;
   int msg;
   int i;

   for (i = 0; i < N_GET; i++) {
      usleep(rand2() * MAXDELAY);
      msg = getmsg(p);
      printf("--->removes message %d\n", msg);
   }
}
void putmsg(struct buffer* p, int msg)
{
   while (p->count == BUFSIZE)
      ;
   p->count++;
   p->buf[p->in] = msg;
   p->in = (p->in + 1) % BUFSIZE;

   printf("putmsg: buffer size = %d\n", p->count);
}
int getmsg(struct buffer* p)
{
   int msg;

   while (p->count == 0)
      ;
   p->count--;
   msg = p->buf[p->out];
   p->out = (p->out + 1) % BUFSIZE;

   printf("---> getmsg: buffer size = %d\n", p->count);

   return msg;
}

