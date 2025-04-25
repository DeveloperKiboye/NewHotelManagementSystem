#include <stdio.h>
#include <errno.h>
#include <string.h>

int main (){
    FILE *file = fopen ("hotel.txt", "r");
    if (file == NULL){
        printf("Error opening file:%s\n" , strerror(errno));
        return errno;
    }
    printf("File opened successfully\n");
    return 0;
}