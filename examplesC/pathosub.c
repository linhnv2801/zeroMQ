//  Pathological subscriber
//  Subscribes to one random topic and prints received messages

#include "czmq.h"

int main (int argc, char *argv [])
{
    zrex_t *context = zmq_ctx_new ();
    void *subscriber = zmq_socket (context, ZMQ_SUB);
    if (argc == 2)
        zmq_connect (subscriber, argv [1]);
    else
        zmq_connect (subscriber, "tcp://localhost:5556");

    srandom ((unsigned) time (NULL));
    char subscription [5];
    sprintf (subscription, "%03d", randof (1000));
    zsocket_set_subscribe (subscriber, subscription);
    
    while (true) {
        char *topic = zstr_recv (subscriber);
        if (!topic)
            break;
        char *data = zstr_recv (subscriber);
        assert (streq (topic, subscription));
        puts (data);
        free (topic);
        free (data);
    }
    zmq_ctx_destroy (&context);
    return 0;
}
