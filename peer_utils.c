#include "peer.h"

void initialize_records(){
	// TODO
	records_size = 0;
	inno_record misha;
	inno_record sergey;
}

// Returns hostname for the local computer
void checkHostName(int hostname)
{
	if (hostname == -1)
	{
		perror("gethostname");
		exit(1);
	}
}

// Returns host information corresponding to host name
void checkHostEntry(struct hostent * hostentry)
{
	if (hostentry == NULL)
	{
		perror("gethostbyname");
		exit(1);
	}
}

// Driver code
inno_record get_my_record() {
	puts("in *get_my_record");
	char hostbuffer[256];
	char *IPbuffer;
	struct hostent *host_entry;
	int hostname;

	// To retrieve hostname
	hostname = gethostname(hostbuffer, sizeof(hostbuffer));
	checkHostName(hostname);

	// To retrieve host information
	host_entry = gethostbyname(hostbuffer);
	checkHostEntry(host_entry);

	// To convert an Internet network
	// address into ASCII string
	IPbuffer = inet_ntoa(*((struct in_addr *)
			host_entry->h_addr_list[0]));

	// hardcoded
	int my_port = 6789;

//	printf("Hostname: %s\n", hostname);
	printf("Hostbuffer: %s\n", hostbuffer);
	printf("Host IP: %s\n", IPbuffer);
	char *host = strdup(hostbuffer);
//	strcat(host, hostbuffer);
//	puts(host);
	//TODO
//	char **files;
	inno_record my_record = {.IP = IPbuffer, .name = host, .files_size = 0, .port = my_port}; //.files = NULL
//	my_record.IP = IPbuffer;
//	my_record.name = hostbuffer;
//	my_record.files_size = 0;
//	my_record.files = files;
//	my_record.port = my_port;
	return my_record;
}

char* concatenate_record(inno_record record){
	puts("in concatenate_record");
//	printf("record.IP = %s\n", record.IP);
//	printf("record.name = %s\n", record.name);
	char *message = record.name;
//	strcat(message, );
//	message = concat(message, record.name);
//	puts("!_!_!");
//	puts(message);
	strcat(message, ":");
	strcat(message, record.IP);
	strcat(message, ":");
	char port_s[5];
	//itoa(record.port, port_s, 10);

	sprintf(port_s, "%d", record.port);
	strcat(message, port_s);
	if (record.files_size == 0){
		strcat(message, ":");
	} else {
		for (int i = 0; i < record.files_size; i++){
			//It's wrong, again, right?
			strcat(message, ":");
			strcat(message, record.files[i]);
		}
	}
	return message;
}

void read_words(FILE *f, char **words) {
    puts("reading words!");
    char x[1024];
    // assumes no word exceeds length of 1023
    //char *words[number_of_words];
    int i = 0;
    while (fscanf(f, " %1023s", x) == 1) {
        words[i] = strdup(x);
        i = i + 1;
        //puts(x);
    }
}

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}


int number_of_words(FILE *file) {
    char ch;
    ch=fgetc(file);
    int words_count = 0;
    while(ch!=EOF)
    {
        if(ch==' '||ch=='\n')
        {
            words_count++;
        }
        ch=fgetc(file);
    }
    return words_count;
}


void print_word_list(char **words){
    //int size = sizeof(words)/sizeof(words[0]);
    int size = 8;
    printf("%d\n", size);
    puts("Been here!");
    for(int i = 0; i < size ; i++){
        printf("%s ", words[i]);
    }
    puts("");
}

void write_word_list_to_file(char *file_name, char **words){
    //int size = sizeof(words)/sizeof(char);
    FILE *f = fopen(file_name, "wb");
    fwrite(words, sizeof(char), sizeof(words), f);
    fclose(f);
}


/*
void read_file_names(char **words){
    DIR *dir;
    if ((dir = opendir ("./files")) != NULL) {
      int i = 0;
      struct dirent *ent;
      char x[1024];
      //char *x = malloc(1024 * sizeof(char));
      while ((ent = readdir (dir)) != NULL) {
        strcpy(x, ent.d_name);
        printf("%d\n", strlen(ent.d_name));
        if (strcmp(x, ".") != 0 && strcmp(x, "..") != 0) {
            puts(x);
            //puts(strdup(x));
            words[i] = strdup(x);
            puts(words[i]);
            //strcpy(words[i], x);
            //strcpy(words[i], x);
            i = i + 1;
        }
      }
      closedir (dir);
    } else {
      // could not open directory
      perror ("");
      return EXIT_FAILURE;
    }
    puts("once in a while");
}
*/