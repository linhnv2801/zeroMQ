//  Hello World worker
//  Connects REP socket to tcp://localhost:5560
//  Expects "Hello" from client, replies with "World"

#include "zhelpers.h"
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        void *context = zmq_ctx_new();

        //  Socket to talk to clients
        void *responder = zmq_socket(context, ZMQ_REP);
        char server[100] = "tcp://";
        zmq_connect(responder, strcat(strcat(server, argv[1]), ":5560"));

        while (1)
        {
            //  Wait for next request from client
            char *string = s_recv(responder);
            printf("Received request: [%s]\n", string);
            free(string);

            //  Do some 'work'
            sleep(1);

            //  Send reply back to client
            s_send(responder, "World");
        }
        //  We never get here, but clean up anyhow
        zmq_close(responder);
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
