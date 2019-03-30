#ifndef NETWORKS_PEER_H
#define NETWORKS_PEER_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <memory.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <pthread.h>

typedef struct inno_record_struct_ {
	char *IP;
	char *name;
	int port;
	int files_size;
	char **files;
} inno_record;

#define BUFFER_SIZE 4096
int records_size;
inno_record *records;

void read_words(FILE *f, char **words);
char* concat(const char *s1, const char *s2);
int number_of_words(FILE *file);
void print_word_list(char **words);
void write_word_list_to_file(char *file_name, char **words);

inno_record get_my_record(void);
char* concatenate_record(inno_record record);
//char* concatenate_record(struct inno_record record);

void protocol_1_client(char *server_peer_ip, int server_peer_port);
void protocol_1_server(int server_peer_port);
void tcp_client(int port);

#endif //NETWORKS_PEER_H