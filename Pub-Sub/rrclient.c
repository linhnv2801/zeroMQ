//  Hello World client
//  Connects REQ socket to tcp://localhost:5559
//  Sends "Hello" to server, expects "World" back

#include "zhelpers.h"
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        void *context = zmq_ctx_new();

        //  Socket to talk to server
        void *requester = zmq_socket(context, ZMQ_REQ);
        char server[100] = "tcp://";
        zmq_connect(requester, strcat(strcat(server, argv[1]), ":5559"));

        int request_nbr;
        for (request_nbr = 0; request_nbr != 10; request_nbr++)
        {
            s_send(requester, "Hello");
            char *string = s_recv(requester);
            printf("Received reply %d [%s]\n", request_nbr, string);
            free(string);
        }
        zmq_close(requester);
        zmq_ctx_destroy(context);
    }
    else if (argc > 2)
    {
        printf("Too many arguments supplied.\n");
    }
    else
    {
        printf("One argument expected.\n");
    }

    return 0;
}
