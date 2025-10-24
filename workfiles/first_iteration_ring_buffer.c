
#include <stdio.h>


int main() {


    #define BUFFER_SIZE 16
    int buffer[BUFFER_SIZE] = {0};
    int *p = &buffer[0];
    buffer[1] = 25;
    int goalPosition = 17;
    int bufferMask = BUFFER_SIZE - 1;
    p = &buffer[goalPosition & bufferMask];

    printf("%d\n", *p);

return 0;
}
