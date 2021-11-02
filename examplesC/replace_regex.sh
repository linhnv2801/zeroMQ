sed -i 's/zsocket_new/zmq_socket/g' *.c
sed -i 's/zsocket_bind/zsock_bind/g' *.c
sed -i 's/zctx_t/zrex_t/g' *.c
sed -i 's/zctx_new/zmq_ctx_new/g' *.c
sed -i 's/zctx_destroy/zmq_ctx_destroy/g' *.c
sed -i 's/zsocket_destroy/zmq_close/g' *.c
sed -i 's/zsocket_connect/zmq_connect/g' *.c
