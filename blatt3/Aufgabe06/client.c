#define _POSIX_C_SOURCE 200809L

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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

// create a new socket
int createSocket()
{
  int soc = socket(PF_INET, SOCK_STREAM, 0);
  if (soc < 0) { err("socket not created"); }
  printf("socket created\n");

  return soc;
}

// connect given socket soc to server at "localhost" on port "2342"
void connectToTimeServer(int soc)
{
  // specify information about the hostname and port to use
  struct addrinfo hints;
  struct addrinfo *info;

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  getaddrinfo("localhost", "2342", &hints, &info);

  connect(soc, info->ai_addr, info->ai_addrlen);

  return;
}

// send time request message to the server
void sendTimeRequest(int soc, const time_request_t* timeRequest)
{
  send(soc, (const void*)timeRequest, sizeof(time_request_t), 0);
  return;
}

// receive time respond message from the server and store it in timeRespond
void receiveTimeRespond(int soc, time_respond_t* timeRespond)
{
  recv(soc, (void *)timeRespond, sizeof(time_respond_t), 0);
  return;
}

int main(void)
{
  int soc = createSocket();
  connectToTimeServer(soc);

  time_request_t timeRequest;
  time_respond_t timeRespond;

  timeRequest.timezone = +1; // CET
  sendTimeRequest(soc, &timeRequest);

  receiveTimeRespond(soc, &timeRespond);
  printf("Current time in Münster: %s", timeRespond.time);


  timeRequest.timezone = -5; // EST
  sendTimeRequest(soc, &timeRequest);

  receiveTimeRespond(soc, &timeRespond);
  printf("Current time in New York: %s", timeRespond.time);


  // send disconnect message
  timeRequest.timezone = 127; // magic number
  sendTimeRequest(soc, &timeRequest);

  close(soc);
}