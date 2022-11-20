#define _POSIX_C_SOURCE 200809L

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <time.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "message.h"

void err(char *msg)
{
  perror(msg);
  exit(EXIT_FAILURE);
}

// global listen socket
int listenSoc;

void shutdownTimeServer(int param)
{
  (void) param;
  printf("shutting down time server\n");
  // close listen socket on shutdown
  close(listenSoc);
  exit(EXIT_SUCCESS);
}

// create listening socket
int createListenSocket()
{
  // create socket
  int soc = socket(PF_INET, SOCK_STREAM, 0);
  if (soc < 0) { err("socket not created"); }
  printf("socket created\n");

  // specify information about the hostname and port to use
  struct addrinfo hints;
  struct addrinfo *info;

  memset(&hints, 0, sizeof(hints)); // clear memory
  hints.ai_family = AF_INET;        // use IP as protocol
  hints.ai_socktype = SOCK_STREAM;  // use TCP as protocol
  hints.ai_flags = AI_PASSIVE;      // this side is used as the server

  // turn hostname and port information in addrinfo struct
  // information in hints is used as a hint to fill info
  int retval = getaddrinfo("localhost", "2342", &hints, &info);
  if (retval != 0) {
    printf("getaddrinfo failed %s\n", gai_strerror(retval));
    exit(EXIT_FAILURE);
  }
  
  // bind socket to address
  retval = bind(soc, info->ai_addr, info->ai_addrlen);
  // release memory used by info
  freeaddrinfo(info);
  if (retval < 0) { close(soc); err("bind failed"); }
  printf("bound to localhost:2342\n");

  // listen for (up to 1) incoming connection
  retval = listen(soc, 1);
  if (retval < 0) { close(soc); err("listen failed"); }
  printf("listen for incoming connection\n");

  return soc;
}

// accept incoming connection
int acceptConnection(int listenSoc)
{
  // space for information about connecting client
  struct sockaddr_in claddr;
  socklen_t claddrSize = sizeof(claddr);

  // accept incoming connection
  int soc = accept(listenSoc, (struct sockaddr *)&claddr, &claddrSize);
  if (soc < 0) { close(listenSoc); err("accept failed"); }
  printf("client from host %s port %d connected\n",
      inet_ntoa(claddr.sin_addr), ntohs(claddr.sin_port));

  return soc;
}

// receive time request message and store it in timeRequest
void receiveTimeRequest(int connectionSoc, time_request_t* timeRequest)
{
  // receive data on the connection socket and store them in timeRequest
  int bytesrcvd = recv(connectionSoc, (void *)timeRequest, sizeof(time_request_t), 0);
  if (bytesrcvd < 0) { close(connectionSoc); err("error while receiving"); }
  printf("received %d bytes\n", bytesrcvd);
}

// fill the timeRespond variable with a appropriate respond for the timeRequest request
void createTimeRespond(const time_request_t* timeRequest, time_respond_t* timeRespond)
{
  // get current time
  time_t rawtime;
  time(&rawtime);

  // convert time to greenwich mean time
  struct tm* ptm = gmtime(&rawtime);
  // adjust time with the send timezone
  ptm->tm_hour = (ptm->tm_hour + timeRequest->timezone)%24;
  // print time into a string
  char * timeAsASCI = asctime(ptm);

  // copy string into respond
  strncpy(timeRespond->time, timeAsASCI, 255);
}

// send respond message back to the client
void sendTimeRespond(int connectionSoc, const time_respond_t* timeRespond)
{
  // send sizeof(time_respond_t) bytes from timeRespond to the connection socket
  int bytessend = send(connectionSoc, (const void*)timeRespond, sizeof(time_respond_t), 0);
  if (bytessend < 0) { close(connectionSoc); err("error while sending"); }
  printf("send %d bytes\n", bytessend);
}


int main(void)
{
  // register shutdown method for SIGINT
  // server can be stopped using ^C
  signal(SIGINT, shutdownTimeServer);

  // create listening socket
  listenSoc = createListenSocket();
  
  // forever ...
  while (1) {
    // ... take incoming connections
    int connectSoc = acceptConnection(listenSoc);
    // forever ...
    while (1) {
      // .. do one request -> respond cycle
      // save on request and one respond
      time_request_t timeRequest;
      time_respond_t timeRespond;

      // receive request and store it in timeRequest
      receiveTimeRequest(connectSoc, &timeRequest);

      // check for magic number to disconnect from client
      if (timeRequest.timezone == 127) { break; }

      // create appropriate respond and store it in timeRespond
      createTimeRespond(&timeRequest, &timeRespond);

      // send respond to client
      sendTimeRespond(connectSoc, &timeRespond);
    }
    // after magic number is send the connection to the client is closed
    close(connectSoc);
  }
  // the while loop above can only be exit using the signal handler
  exit(EXIT_FAILURE);
}

