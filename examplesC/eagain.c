//  Shows how to provoke EAGAIN when reaching HWM

#include <czmq.h>

int main (void) {
    zrex_t *ctx = zmq_ctx_new ();
    
    void *mailbox = zmq_socket (ctx, ZMQ_DEALER);
    zsocket_set_sndhwm (mailbox, 4);
    zsocket_set_sndtimeo (mailbox, 0);
    zmq_connect (mailbox, "tcp://localhost:9876");

    int count;
    for (count = 0; count < 10; count++) {
        printf ("Sending message %d\n", count);
        int rc = zstr_sendf (mailbox, "message %d", count);
        if (rc == -1) {
            printf ("%s\n", strerror (errno));
            break;
        }
    }
    zmq_ctx_destroy (&ctx);
    return 0;
}
