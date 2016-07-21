/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   server.cpp
* Author: micky
*
* Created on March 4, 2016, 11:34 PM
*/


#define __WINDOWS
//#define __LINUX


#ifdef __WINDOWS
#include <iostream>
using std::iostream;

#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <ws2tcpip.h>

#include <stdint.h>
typedef uint8_t u_int8_t;
typedef uint16_t u_int16_t;
typedef uint32_t u_int32_t;

WSADATA wsa;

#endif


#ifdef __LINUX
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#endif

using namespace std;

#define PORT "3490"  // the port users will be connecting to
#define BACKLOG 10     // how many pending connections queue will hold



namespace APP
{
	void LogMessage(const char * message)
	{
		printf(message);
	}

	void ErrorMessage(const char * errortxt)
	{
		perror(errortxt);
	}

	void AppExit()
	{
		char c;
		std::cin >> c;
	}
};

namespace SMNET
{
	int InitStuff()
	{
		#ifdef __WINDOWS
				char anyin;


				//SOCKET s;
				//unsigned int sockfd;

				std::printf("\n Initialising Winsock..");

				if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
				{
					std::printf("Fauked Error code: %d", WSAGetLastError());

					cin >> anyin;
					return 1;
				}

				std::printf("Initialised.\n");

				return 0;
		#endif

		#ifdef __LINUX

		#endif
	}

	void CloseSocket(int sockfd)
	{
		#ifdef __WINDOWS
				closesocket(sockfd);
				WSACleanup();
		#endif
		#ifdef __LINUX
				close(sockfd);
		#endif
	}
};

#ifdef __LINUX
void sigchld_handler(int s)
{
	// waitpid() might overwrite errno, so we save and restore it:
	int saved_errno = errno;

	while (waitpid(-1, NULL, WNOHANG) > 0);

	errno = saved_errno;
}
#endif

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

/*
*
*/
int main(int argc, char** argv) {

	if (SMNET::InitStuff() == 1) return 1;//winsock init


	int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
	struct addrinfo hints, *servinfo, *p;
	struct sockaddr_storage their_addr; // connector's address information
	socklen_t sin_size;
	
	#ifdef __LINUX
		struct sigaction sa;
	#endif
	
	int yes = 1;
	char s[INET6_ADDRSTRLEN];
	int rv;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; // use my IP

	if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	// loop through all the results and bind to the first we can
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
			p->ai_protocol)) == -1) {
			perror("server: socket");
			continue;
		}

		#ifdef __WINDOWS
		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char*)&yes,
			sizeof(int)) == -1) {
			perror("setsockopt");
			exit(1);
		}
		#endif

		#ifdef __LINUX
		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
			sizeof(int)) == -1) {
			perror("setsockopt");
			exit(1);
		}
		#endif

		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			SMNET::CloseSocket(sockfd);
			perror("server: bind");
			continue;
		}

		break;
	}

	freeaddrinfo(servinfo); // all done with this structure

	if (p == NULL) {
		fprintf(stderr, "server: failed to bind\n");
		exit(1);
	}

	if (listen(sockfd, BACKLOG) == -1) {
		perror("listen");
		exit(1);
	}

	#ifdef __LINUX
	sa.sa_handler = sigchld_handler; // reap all dead processes
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa, NULL) == -1) {
		perror("sigaction");
		exit(1);
	}
	#endif

	printf("server: waiting for connections...\n");

	while (1) {  // main accept() loop
		sin_size = sizeof their_addr;
		new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
		if (new_fd == -1) {
			perror("accept");
			continue;
		}

		inet_ntop(their_addr.ss_family,
			get_in_addr((struct sockaddr *)&their_addr),
			s, sizeof s);
		printf("server: got connection from %s\n", s);


		#ifdef __WINDOWS
		
		SMNET::CloseSocket(sockfd);

		if (send(new_fd, "Simple MOBA client connected!", 29, 0) == -1)
			perror("send");
		
		SMNET::CloseSocket(new_fd);
		exit(0);

		#endif

		#ifdef __LINUX
			if (!fork()) { // this is the child process
				close(sockfd); // child doesn't need the listener
				if (send(new_fd, "Simple MOBA client connected!", 29, 0) == -1)
					perror("send");
				close(new_fd);
				exit(0);
			}
			close(new_fd);  // parent doesn't need this
		#endif
	

	}


	return 0;
}

