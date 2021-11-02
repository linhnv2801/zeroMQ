//  Hello World client
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  if (argc == 2)
  {
    printf("Connecting to hello world server...\n");
    void *context = zmq_ctx_new();
    void *requester = zmq_socket(context, ZMQ_REQ);
    char server[100] = "tcp://";
    zmq_connect(requester, strcat(strcat(server, argv[1]), ":5555"));

    int request_nbr;
    for (request_nbr = 0; request_nbr != 10; request_nbr++)
    {
      char buffer[10];
      printf("Sending Hello %d...\n", request_nbr);
      zmq_send(requester, "Hello", 5, 0);
      zmq_recv(requester, buffer, 10, 0);
      printf("Received World %d\n", request_nbr);
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
