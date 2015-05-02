#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct ThreadArguments {
    int tid;
    char *prog;
    char *module;
};

void *routine( void *arg ) {
    int *n = (int*) arg;
    printf("routine(%d)\n", *n);
    pthread_exit( 0 );
}

int main( int argc, char *argv[] ) {
    pthread_t *threads;
    pthread_attr_t *attrs;
    int nthreads;
    int i;
    struct ThreadArguments *args;
    void *res;

    if ( argc < 2 ) {
        printf( "Usage: %s [MODULE NAME]...\n", argv[0] );
        exit( 0 );
    }

    nthreads = argc - 1;
    threads = malloc( nthreads * sizeof( *threads ) );
    if ( !threads ) {
        perror( "malloc" );
        exit( 0 );
    }
    attrs = malloc( nthreads * sizeof( *attrs ) );
    if ( !attrs ) {
        perror( "malloc" );
        exit( 0 );
    }
    args = malloc( nthreads * sizeof( *args ) );
    if ( !args ) {
        perror( "malloc" );
        exit( 0 );
    }

    for ( i = 0; i < nthreads; ++i ) {
        if ( 0 != pthread_attr_init( &(attrs[i]) ) ) {
            perror( "pthread_attr_init" );
            exit( 0 );
        }
        args[i].tid = i;
        args[i].prog = argv[0];
        args[i].module = argv[i+1];
        printf( "creating arguments for thread: %d, module: '%s'\n", i, argv[i+1] );
    }

    /* begin creating threads */
    for ( i = 0; i < nthreads; ++i ) {
        if ( 0 != pthread_create( &(threads[i]), &(attrs[i]), routine, (void*) &(args[i]) ) ) {
            perror( "pthread_create" );
            exit( 0 );
        }
    }

    /* no longer need attrs so clean up */
    for ( i = 0; i < nthreads; ++i ) {
        if ( 0 != pthread_attr_destroy( &(attrs[i]) ) ) {
            perror( "pthread_attr_destroy" );
            exit( 0 );
        }
    }
    free( attrs );

    for ( i = 0; i < nthreads; ++i ) {
        if ( 0 != pthread_join( threads[i], &res ) ) {
            perror( "pthread_join" );
            exit( 0 );
        }
    }

    /* clean up threads and args */
    free( threads );
    free( args );

    return 0;
}
