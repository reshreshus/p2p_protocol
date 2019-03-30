#include <ctype.h>
#include <assert.h>

#include "peer.h"

char server_buffer[BUFFER_SIZE];

int ADDR_LEN = sizeof(struct sockaddr);

int establish_socket_server(int port){
	int s_fd;
	if((s_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	int opt = 1;
//     Forcefully attaching socket to the port 8080
//    if (setsockopt(s_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
//                                                  &opt, sizeof(opt)))
//    {
//        perror("setsockopt");
//        exit(EXIT_FAILURE);
//    }

	struct sockaddr_in address;

	address.sin_family = AF_INET;
	//What is this?
	address.sin_addr.s_addr = INADDR_ANY;
	//address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(port);

	if (bind (s_fd, (struct sockaddr*)&address, (socklen_t*) ADDR_LEN) < 0){
		perror("Bind failed");
		exit(EXIT_FAILURE);
	}

	// 2nd argument defines the maximum length to which the queue of pending connections for sockfd may grow.
	if (listen(s_fd, 10) < 0){
		perror("listen failed");
		exit(EXIT_FAILURE);
	}
	return s_fd;
}

//    printf("I am SERVER, look at me! port number %d\n", port);
//    FILE* file_to_distribute = fopen("files/test.txt", "r");
//    int words_count = number_of_words(file_to_distribute);
//    //printf("words_count = %d\n", words_count);
//    fseek(file_to_distribute, 0, SEEK_SET);
//    char *words[words_count];
//    //puts("Been here!");
//    read_words(file_to_distribute, words);
//    //puts("Been here!");
//    printf("a word is %s\n", words[5]);
//    print_word_list(words);
//    write_word_list_to_file("output.txt", words);

//    puts("ready to accept connections");

int is_number(char *input){
	int length = strlen (input);
	for (int i=0;i<length; i++) {
		if (!isdigit(input[i]))
		{
			printf ("Entered input is not a number\n");
			return 0;
		}
	}
	return 1;
}

char** str_split(char* a_str, const char a_delim)
{
	char** result    = 0;
	size_t count     = 0;
	char* tmp        = a_str;
	char* last_comma = 0;
	char delim[2];
	delim[0] = a_delim;
	delim[1] = 0;

	/* Count how many elements will be extracted. */
	while (*tmp)
	{
		if (a_delim == *tmp)
		{
			count++;
			last_comma = tmp;
		}
		tmp++;
	}

	/* Add space for trailing token. */
	count += last_comma < (a_str + strlen(a_str) - 1);

	/* Add space for terminating null string so caller
	   knows where the list of returned strings ends. */
	count++;

	result = malloc(sizeof(char*) * count);

	if (result)
	{
		size_t idx  = 0;
		char* token = strtok(a_str, delim);

		while (token)
		{
			assert(idx < count);
			*(result + idx++) = strdup(token);
			token = strtok(0, delim);
		}
		assert(idx == count - 1);
		*(result + idx) = 0;
	}

	return result;
}

int count_occurrences(char *inspected, char *occur){
	int count = 0;
	const char *tmp = inspected;
	while(tmp = strstr(tmp, occur))
	{
		count++;
		tmp++;
	}
	return count;
}

int check_format(char *message){
	//TODO
	return 0;
}

void add_new_record(inno_record record){
	records = (inno_record*) realloc(records, sizeof(records));
	records[records_size] = record;
	records_size++;
}

void print_records(){
	for (int i = 0; i < records_size; i++){
		char *record_str = concatenate_record(records[i]);
		printf("%s \n", record_str);
	}
}



void protocol_1_server(int server_peer_port) {
	// hardcoded
	int port = 7890;

	int s_fd = establish_socket_server(port);
    fd_set readfds;
    struct sockaddr_in client_addr;

    int comm_socket_fd;
    long sent_recv_bytes;
    while(1) {
        FD_ZERO(&readfds);
        FD_SET(s_fd, &readfds);
        printf("blocked on select System call...\n");

        select(s_fd + 1, &readfds, NULL, NULL, NULL);
        if (FD_ISSET(s_fd, &readfds)) {
            printf("New connection recieved recvd, accept the connection. Client and Server completes TCP-3 way handshake at this point\n");

            comm_socket_fd = accept(s_fd, (struct sockaddr *) &client_addr, &ADDR_LEN);
            if (comm_socket_fd < 0) {
                perror("accept failed");
                exit(0);
            }
            printf("Connection accepted from client : %s:%u\n",
                   inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

            while (1) {
                printf("Server ready to service client msgs.\n");
				char buffer[BUFFER_SIZE];

                memset(buffer, 0, BUFFER_SIZE);

				sent_recv_bytes = read(comm_socket_fd, (char *) buffer, BUFFER_SIZE);
				printf("received message \"%s\"\n", buffer);
				if (sent_recv_bytes == 0) {
					// exit if sent nothing - 0 bytes
					close(comm_socket_fd);
					break;
				}
				if (is_number(buffer) == 1){
					int protocol_id = atoi(buffer);
					if (protocol_id == 1) {
						sent_recv_bytes = read(comm_socket_fd, (char *) buffer, BUFFER_SIZE);
						int delim_occurrences = count_occurrences(buffer, ":");
						if (delim_occurrences >= 3){
							char **elemenets = str_split(buffer, ":");
							char *name = elemenets[0];
							char *ip = elemenets[1];
							char *s_port = elemenets[2];
							int port;
							sprintf(port, "%d", s_port);
							//ignore files for now
							inno_record client_record = {.name = name, .IP = ip, .files_size = 0, .port = port};
							add_new_record(client_record);


						}

						if (check_format(buffer) == 1){

						}
					}
				}


                //sent_it = send(comm_socket_fd, number_of_words, sizeof(number_of_words), 0);
//                char *result = concat("echo: ", ((char *) server_buffer));
//                sent_recv_bytes = send(comm_socket_fd, result, strlen(result), 0);
                //printf("Server sent %d bytes in reply to client\n", sent_recv_bytes);
                //free(result);
            }
        }
    }
}