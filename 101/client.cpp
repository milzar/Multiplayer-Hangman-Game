#include "tcp.h"
#include<iostream>
#include <unistd.h>

using namespace std;

int main(){
    char dataReceived[1024] = {0};

    int socket_fd = setUpClientSocket();

    int n;
    while((n = read(socket_fd, dataReceived, sizeof(dataReceived)-1)) > 0){
        dataReceived[n] = 0;
        if(fputs(dataReceived, stdout) == EOF)
        {
            printf("\nStandard output error");
        }

        printf("\n");
    }

    return 0;
}
