#ifndef MENUH
#define MENUH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "linkedList.h"
#include "view.h"
#include "fileHelper.h"

/*
this handles all the socket input the commmands that we get from the server etc..
*/

#define PORT "1200"
#define BUFFER_SIZE 1024
#define TRUE 0
#define FALSE 1
/*
handling the parse command getting the response to write into the headframe to use and the recvbuffer the input that we get fron the server
this will parse each command with each parameter the commands will be parsed and will send info to the server as a result and in addition 
the server will also handle each request and will do the actions for it
input: the info that we got the recvbuffer the had frame and the response to send at the end
output: the new Framenode so we will update all
*/
FrameNode* parse_command(char* recvbuf, FrameNode* headFrame, char* response);
/*
handling the socket opening the socket info to a tcp type and into a server getting it to 
listen into port 1200 and getting the info from the buffer into recvbuf we get the parameters for it
getting the commands output after the actions we will send the response to the gui
input: none
output: none
*/
void handleSocket();

#endif