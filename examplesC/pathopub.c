//  Pathological publisher
//  Sends out 1,000 topics and then one random update per second

#include "czmq.h"

int main (int argc, char *argv [])
{
    zrex_t *context = zmq_ctx_new ();
    void *publisher = zmq_socket (context, ZMQ_PUB);
    if (argc == 2)
        zsock_bind (publisher, argv [1]);
    else
        zsock_bind (publisher, "tcp://*:5556");

    //  Ensure subscriber connection has time to complete
    sleep (1);

    //  Send out all 1,000 topic messages
    int topic_nbr;
    for (topic_nbr = 0; topic_nbr < 1000; topic_nbr++) {
        zstr_sendfm (publisher, "%03d", topic_nbr);
        zstr_send (publisher, "Save Roger");
    }
    //  Send one random update per second
    srandom ((unsigned) time (NULL));
    while (!zctx_interrupted) {
        sleep (1);
        zstr_sendfm (publisher, "%03d", randof (1000));
        zstr_send (publisher, "Off with his head!");
    }
    zmq_ctx_destroy (&context);
    return 0;
}
