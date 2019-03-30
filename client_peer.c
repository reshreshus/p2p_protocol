#include "peer.h"

char client_buffer[BUFFER_SIZE];

int establish_connection_client(char *ip, int port) {
	int sock;
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Socket creation error\n");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in server_address;
	memset(&server_address, '0', sizeof(server_address));

	server_address.sin_family = AF_INET;
	// The htons() function converts the unsigned short integer host short from host byte order to network byte order.
	// Why sin?
	server_address.sin_port = htons(port);

	if(inet_pton(AF_INET, ip, &server_address.sin_addr) <= 0) {
		perror("Invalid address\n");
		exit(EXIT_FAILURE);
	}

	int s_addr_len = sizeof(server_address);
	//(socklen_t*)&s_addr_len
	if((connect(sock, (struct sockaddr *)&server_address, sizeof(server_address))) < 0){
		perror("Connection failed");
		perror(EXIT_FAILURE);
	}
	return sock;
}

int PROTOCOL_1_CODE = 1;

int PROTOCOL_0_CODE = 0;


void protocol_1_client(char *server_peer_ip, int server_peer_port) {
	// TODO: perhaps need to zero out the buffer?
	puts("in protocol 1");
	int sock = establish_connection_client(server_peer_ip, server_peer_port);

	// 1
	send(sock, &PROTOCOL_1_CODE, sizeof(PROTOCOL_0_CODE), 0);
	// 2
	inno_record my_record = get_my_record();
//	puts("trying to print inno_record struct");
//	puts(my_record.IP);
//	printf("my_record.name = %s\n", my_record.name);
	char *message = concatenate_record(my_record);
	printf("message: %s\n", message);
	send(sock, &message, strlen(message), 0);
	// 3
	send(sock, &records_size, sizeof(records_size), 0);
	if (records_size > 0){
		// 4
		for (int i = 0; i < records_size; i++){
			message = concatenate_record(records[i]);
			send(sock, &message, sizeof(message), 0);
		}
	}
}
void tcp_client(int port) {


	//send(sock, message, strlen(message), 0);
	//printf("message %s is sent from client\n", message);

	//Which will zero all bytes.
	//char buffer[1024] = {0};
	//int read_it = read(sock, buffer, 1024);

	//char* message = "Message for the client!";
	int read_it;
	int sent_it;
	/*
	sent_it = send(sock, &ask_for_file, sizeof(ask_for_file), 0);
	read_it = read(sock, &client_buffer, BUFFER_SIZE);
	char **words;
	if (strcmp(client_buffer, have_file) == 0)
	{
		// TODO
		int words_count = (int *) client_buffer;
		char *words[words_count];
		for (int i = 0; i < words_count; i++) {
			read_it = read(sock, &client_buffer, BUFFER_SIZE);
			words[i] = client_buffer;
		}

	} */
	/*
	FILE *f = fopen("test_client.txt", "wb");
		fwrite(words, sizeof(char), sizeof(words), f);
		fclose(f);
	while (1) {

		printf("type you word and I will send it to the server\n");
		scanf("%s", &word);
		puts("");

		sent_it = send(sock, &word, sizeof(word), 0);

		read_it = read(sock, &client_buffer, BUFFER_SIZE);
		printf("Message from the server: \"%s\"\n", client_buffer);
	}*/
}
