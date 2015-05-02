#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *routine( void *arg ) {
    int *n = (int*) arg;
    printf("routine(%d)\n", *n);
    pthread_exit( 0 );
}

int main( int argc, char *argv[] ) {
    pthread_t thread1, thread2;
    pthread_attr_t attr1, attr2;
    int i, j;
    void *res;

    if (0 != pthread_attr_init(&attr1)) {
        perror( "attr1" );
        exit( 1 );
    }
    if (0 != pthread_attr_init(&attr2)) {
        perror( "attr2" );
        exit( 1 );
    }

    i = 1;
    j = 2;
    if ( 0 != pthread_create( &thread1, &attr1, routine, (void*) &i ) ) {
        perror( "pthread_create( thread1 )" );
        exit( 1 );
    }

    if ( 0 != pthread_create( &thread2, &attr2, routine, (void*) &j ) ) {
        perror( "pthread_create( thread2 )" );
        exit( 1 );
    }

    if ( 0 != pthread_attr_destroy( &attr1 ) ) {
        perror( "pthread_attr_destroy( attr1 )" );
        exit( 1 );
    }

    if ( 0 != pthread_attr_destroy( &attr2 ) ) {
        perror( "pthread_attr_destroy( attr2 )" );
        exit( 1 );
    }

    if ( 0 != pthread_join( thread1, &res ) ) {
        perror( "pthread_join( thread1 )" );
        exit( 1 );
    }

    if ( 0 != pthread_join( thread2, &res ) ) {
        perror( "pthread_join( thread2 )" );
        exit( 1 );
    }

    return 0;
}
