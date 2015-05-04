#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int
main( int argc, char *argv[] ) {
    pid_t pid, w;
    int status;

    printf( "parent::fork()\n" );
    pid = fork();
    if ( pid == -1 ) {
        perror( "fork" );
        exit( 0 );
    }
    else if ( pid == 0 ) {

        printf( "in child!\n" );
    }
    else {
        printf( "in parent! pid = %d\n", pid );
        do {
            w = waitpid( pid, &status, WUNTRACED | WCONTINUED );
            if ( w == -1 ) {
                perror( "waitpid" );
                exit( 1 );
            }
            else if ( WIFEXITED( status ) ) {
                printf( "exited, status=%d\n", WEXITSTATUS( status ) );
            }
            else if ( WIFSTOPPED( status ) ) {
                printf( "killed by signal, %d\n", WTERMSIG( status ) );
            }
            else if ( WIFCONTINUED( status ) ) {
                printf( "continue\n" );
            }
        } while ( !WIFEXITED( status ) && ! WIFSIGNALED( status ) );
    }
    return 0;
}
