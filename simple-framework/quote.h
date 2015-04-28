#ifndef QUOTE__H_
#define QUOTE__H_

#include <stdint.h>

struct Quote {
    int32_t lt;
    int32_t bid;
    int32_t ask;
};

int Quote_Initialize( struct Quote* quote );
int Quote_Finalize( struct Quote* quote );
char * Quote_ToString( struct Quote* quote );

#endif // QUOTE__H_
