#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 10

void *routine( void *arg ) {
    int *n = (int*) arg;
    printf("routine(%d)\n", *n);
    pthread_exit( 0 );
}

int main( int argc, char *argv[] ) {
    pthread_t thread[N];
    pthread_attr_t attr[N];
    int i;
    int arg[N];
    void *res;

    for ( i = 0; i < N; ++i ) {
        arg[i] = i+1;
    }

    for ( i = 0; i < N; ++i ) {
        if (0 != pthread_attr_init( &(attr[i]) ) ) {
            perror( "pthread_attr_init" );
            exit( 1 );
        }
    }

    for ( i = 0; i < N; ++i ) {
        if ( 0 != pthread_create( &(thread[i]), &(attr[i]), routine, (void*) &(arg[i]) ) ) {
            perror( "pthread_create" );
            exit( 1 );
        }
    }

    for ( i = 0; i < N; ++i ) {
        if ( 0 != pthread_attr_destroy( &(attr[i]) ) ) {
            perror( "pthread_attr_destroy" );
            exit( 1 );
        }
    }

    for ( i = 0; i < N; ++i ) {
        if ( 0 != pthread_join( thread[i], &res ) ) {
            perror( "pthread_join" );
            exit( 1 );
        }
    }

    return 0;
}
