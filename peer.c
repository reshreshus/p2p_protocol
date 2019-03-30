#include "peer.h"

void initiate_peer() {
    int server_port = 8088;
    int client_port = 6768;

    pthread_t server_part;
    pthread_t client_part;
    if(pthread_create(&server_part, NULL, protocol_1_server, &server_port)) {
        fprintf(stderr, "Error creating server thread\n");
        exit(EXIT_FAILURE);
    }
    sleep(5);

    if(pthread_create(&client_part, NULL, tcp_client, &client_port)) {
        fprintf(stderr, "Error creating server thread\n");
        exit(EXIT_FAILURE);
    }
    pthread_join( server_part, NULL);
    pthread_join( client_part, NULL);
}


int main(int argc, char **argv) {
	int local_server_port = 8088;
	puts("in main");
	protocol_1_client("127.0.0.1", local_server_port);
	protocol_1_server(8089);

    return 0;
}