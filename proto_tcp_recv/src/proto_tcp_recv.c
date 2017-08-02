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
#define MAX_MSG_SIZE 1024



int main()
{
	int socket_fd, client_fd, num;
	struct sockaddr_in server;
	struct sockaddr_in dest;
	unsigned int len, i;
	AddressBook *addbook;
	socklen_t size;

	// Read packed message from standard-input.
	uint8_t buf[MAX_MSG_SIZE];

	int optval = 1;

	if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		fprintf(stderr, "Socket failure!!\n");
		exit(1);
	}

	if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)) == -1)
	{
		perror("setsockopt");
		exit(1);
	}
	memset(&server, 0, sizeof(server));
	memset(&dest, 0, sizeof(dest));
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = INADDR_ANY;

	if ((bind(socket_fd, (struct sockaddr *) &server, sizeof(struct sockaddr))) == -1)
	{
		fprintf(stderr, "Binding Failure\n");
		exit(1);
	}

	if ((listen(socket_fd, BACKLOG)) == -1)
	{
		fprintf(stderr, "Listening Failure\n");
		exit(1);
	}

	while (1)
	{
		size = sizeof(struct sockaddr_in);

		if ((client_fd = accept(socket_fd, (struct sockaddr *) &dest, &size)) == -1)
		{
			perror("accept");
			exit(1);
		}
		printf("Server got connection from client %s\n", inet_ntoa(dest.sin_addr));

		while (1)
		{
			if ((num = recv(client_fd, buf, MAX_MSG_SIZE, 0)) == -1)
			{
				perror("recv");
				exit(1);
			}
			else if (num == 0)
			{
				printf("Connection closed\n");
				return 0;
			}

			memcpy(&len, buf, sizeof (len));

			printf("\n\nLength of each message = %d\n", len);

			// Unpack the message using protobuf-c.

			addbook = address_book__unpack(NULL, len, (buf+(sizeof (len))));

			if(NULL == addbook)
			{
				printf("error unpacking incoming message\n");
			}
			else
			{
				printf("Total No. of people messages received: %d\n", (uint32_t)(addbook->n_people));
				printf("Total No. of book messages received: %d\n", (uint32_t)(addbook->n_book));

				for(i=0; i<addbook->n_people; i++)
				{
					printf("Email in Message received: %s\n", (addbook->people[i]->email));
					printf("Name in Message received: %s\n", (addbook->people[i]->name));
					printf("Phone in Message received: %s\n", (addbook->people[i]->phone->number));
					printf("Phone Type in Message received: %d\n", (addbook->people[i]->phone->type));
					printf("ID in Message received: %d\n\n", (addbook->people[i]->id));
				}

				for(i=0; i<addbook->n_book; i++)
				{
					printf("Book Name received: %s\n\n", (addbook->book[i]->name));
				}

				address_book__free_unpacked(addbook, NULL);
			}
			memset(buf, 0, MAX_MSG_SIZE);
		}

		close(client_fd);
		close(socket_fd);
	}
	return EXIT_SUCCESS;
}
