#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "cmessage.pb-c.h"
#include "addressbook.pb-c.h"

#define PORT 3490
#define BACKLOG 10
#define MAXSIZE 1024
#define h_addr h_addr_list[0] /* for backward compatibility */

typedef struct sockaddr_in sockaddr_in_t;
typedef struct hostent hostent_t;
typedef struct in_addr s_in_addr_t;
typedef struct sockaddr sockaddr_t;


Person **p1;
Book **b1;

void FillAddressBook(uint32_t *n_people, uint32_t *n_books, uint8_t *buf)
{
	AddressBook addBook = ADDRESS_BOOK__INIT;
	PhoneNumber ph0 = PHONE_NUMBER__INIT;
	PhoneNumber ph1 = PHONE_NUMBER__INIT;
	uint32_t len;

	addBook.n_people = 2;
	addBook.n_book = 1;

	p1 = malloc (sizeof (Person*)*addBook.n_people);
	b1 = malloc (sizeof (Book*)*addBook.n_book);

	for(int i=0; i<addBook.n_people; i++)
	{
		p1[i] = malloc (sizeof (Person));
		person__init (p1[i]);
	}

	for(int i=0; i<addBook.n_book; i++)
	{
		b1[i] = malloc (sizeof (Book));
		book__init (b1[i]);
	}

	ph0.number = "9552504703";
	ph0.type = PHONE_NUMBER__PHONE_TYPE__WORK;

	p1[0]->email = "shripad.1.joshi@jci.com";
	p1[0]->id = 21055;
	p1[0]->name = "Shripad";
	p1[0]->phone = &ph0;

	ph1.number = "9976554221";
	ph1.type = PHONE_NUMBER__PHONE_TYPE__MOBILE;

	p1[1]->email = "sunil.singh@jci.com";
	p1[1]->id = 21075;
	p1[1]->name = "Sunil";
	p1[1]->phone = &ph1;

	b1[0]->name = "Embedded C";

	addBook.people = p1;
	addBook.book = b1;

	len = address_book__get_packed_size(&addBook);

	printf("Length = %d\n", len);

	memcpy(buf, &len, sizeof len);

	address_book__pack(&addBook, (buf+sizeof (len)));

	*n_people = addBook.n_people;
	*n_books = addBook.n_book;

	printf("Total no. of messages being sent: %d\n", *n_people);
	printf("Total no. of book messages being sent: %d\n", *n_books);
}

void FreeAllBufferes(int n_people, int n_books)
{
	for(int i=0; i<n_people; i++)
	{
		free(p1[i]);
	}
	free(p1);

	for(int i=0; i<n_books; i++)
	{
		free(b1[i]);
	}
	free(b1);
}

void ConnectToServer(const char *argv, int *socket_fd)
{
	sockaddr_in_t server_info;
	hostent_t *he;

	if ((he = gethostbyname(argv)) == NULL)
	{
		fprintf(stderr, "Cannot get host name\n");
		exit(1);
	}

	if ((*socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		fprintf(stderr, "Socket Failure!!\n");
		exit(1);
	}

	memset(&server_info, 0, sizeof(server_info));

	server_info.sin_family = AF_INET;
	server_info.sin_port = htons(PORT);
	server_info.sin_addr = *((s_in_addr_t *) he->h_addr);

	if (connect(*socket_fd, (sockaddr_t *) &server_info, sizeof(sockaddr_t)) < 0)
	{
		perror("connect");
		exit(1);
	}
}


int main(int argc, char *argv[])
{
	int socket_fd;
	uint8_t buf[MAXSIZE];         	            // Buffer to store serialized data
	uint32_t n_people, n_books;

	if (argc > 2)
	{
		fprintf(stderr, "Usage: client hostname\n");
		exit(1);
	}

	if(argc == 1)
	{
		argv[1] = "localhost";
	}

	ConnectToServer(argv[1], &socket_fd);

	FillAddressBook(&n_people, &n_books, buf);

	while (n_people > 0)
	{
		if ((send(socket_fd, buf, MAXSIZE, 0)) == -1)
		{
			fprintf(stderr, "Failure Sending Message\n");
			close(socket_fd);
			exit(1);
		}
		n_people--;
	}

	FreeAllBufferes(n_people, n_books);

	close(socket_fd);

	return EXIT_SUCCESS;
}
