#include "menu.h"

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

void handleSocket()
{
    //setting everything we need
    WSADATA wsaData; //struct for windows socket info
    char response[BUFFER_SIZE] = { 0 };
    char* temp = NULL;
    int iResult = 0;
    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;
    FrameNode* headFrame = NULL;
    int socketActive = 0;
    struct addrinfo* result = NULL;
    struct addrinfo hints;
    char recvbuf[BUFFER_SIZE] = { 0 };
    int recvbuflen = BUFFER_SIZE;
    //makeword version of the winsock 2.2 for eahc number the version wsa gets the info of the socket into itselfs
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData); //starting up socket and loading libraries
    if (iResult != 0)
    {
        printf("WSAStartup failed: %d\n", iResult);
        return FALSE;
    }
    //all hints are flags for the server info
    ZeroMemory(&hints, sizeof(hints)); //makes sure that each part of hint is 0 the hints should be 0
    hints.ai_family = AF_INET; //setting each setting to the AF_INET ipv4 adresses
    hints.ai_socktype = SOCK_STREAM; //to the sock stream for a communication tunnel for tcp
    hints.ai_protocol = IPPROTO_TCP; //to tcp
    hints.ai_flags = AI_PASSIVE; //and passive so it will be set as a server

    // first the ip, second the port we will use third the flags result gets the struct of the address info
    iResult = getaddrinfo(NULL, PORT, &hints, &result); //getting the address info
    if (iResult != 0) //if getting the address was a fail than the print the socket failed and cleanup
    {
        printf("getaddrinfo failed!");
        WSACleanup();
        return FALSE;
    }
    //creating the socket
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol); //opening the socket for listening
    if (ListenSocket == INVALID_SOCKET) //if the socket is invalid than 
    {
        printf("socket failed! ");
        freeaddrinfo(result);
        WSACleanup();
        return FALSE;
    }
    //binding the adderss to the listening socket
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen); //binding the socket
    if (iResult == SOCKET_ERROR) //if error than close the socket clean up and free the addres info
    {
        printf("bind failed! ");
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return FALSE;
    }

    freeaddrinfo(result); //freeing the address info
            //starting to listen to the socket
    iResult = listen(ListenSocket, SOMAXCONN); //starting the listen we wil listen in the max we are allowed to
    if (iResult == SOCKET_ERROR) //if error than  close the socket clean up the socket and return false
    {
        printf("listen failed!");
        closesocket(ListenSocket);
        WSACleanup();
        return FALSE;
    }
    system("start GUI.exe"); //opening hte gui
    ClientSocket = accept(ListenSocket, NULL, NULL); //accepting the connection
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed: %ld\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return FALSE;
    }
    socketActive = 1; //if the socket is active than receive
    while (socketActive) //than couninue to recive none stop
    {
        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0); //receving info from the client socket to the buffer socket with the buffer length no need for flags
        if (iResult > 0)
        {
            recvbuf[iResult] = '\0'; //putting in the end of the buffer \0 for the string
            printf("Received: %s\n", recvbuf); //printing what we received
            if (strcmp(recvbuf, "END") == 0) //if the info we received is END than stop the socket
            {
                socketActive = 0;
            }
            else 
            { //parse a command to the head frame and send a response for the server with the same type as the recevie
                headFrame = parse_command(recvbuf, headFrame, response);
                send(ClientSocket, response, strlen(response), 0); //sending the repsonse to the client
            }
        }
    }
    freeFrames(headFrame); //free the frames
    closesocket(ClientSocket); //close the sockets
    closesocket(ListenSocket);
    WSACleanup(); //cleans up everything related to the socket
}

FrameNode* parse_command(char* recvbuf, FrameNode* headFrame, char* response)
{
    char* command = strtok(recvbuf, " "); //this just gets the command and saves it in a string literal they cant have their address taken
    char* frames = NULL;  
    int newDuration = 0;
    char* path = NULL;
    int duration = 0;
    char* name = NULL;
    char* location = NULL;
    //for each command we get from the server we will check for it and get the parameters from the server
    if (strcmp(command, "ADD_FRAME") == 0)
    {
        location = strtok(NULL, " "); //get a string literla of the location name and duration
        name = strtok(NULL, " ");
        duration = atoi(strtok(NULL, " ")); //make the duration int
        headFrame = addFrame(headFrame, duration, name, location, response); //adding the frame and getting the response
    }
    else if (strcmp(command, "REMOVE_FRAME") == 0)
    {
        name = strtok(NULL, " "); //getting the name
        removeFrame(&headFrame, name, response); //removing the frame
    }
    else if (strcmp(command, "CHANGE_LOCATION") == 0)
    {
        name = strtok(NULL, " "); //name and location removing changing the frame location
        location = atoi(strtok(NULL, " "));
        headFrame = changeFrameLocation(headFrame, location, name, response);
    }
    else if (strcmp(command, "CHANGE_DURATION") == 0)
    {
        name = strtok(NULL, " "); //getting the name and new duration
        newDuration = atoi(strtok(NULL, " "));
        headFrame = changeFrameDuration(headFrame, name, newDuration, response);
    }
    else if (strcmp(command, "CHANGE_ALL_DURATIONS") == 0)
    {
        newDuration = atoi(strtok(NULL, " "));
        headFrame = changeAllDurations(headFrame, newDuration, response);
    }
    else if (strcmp(command, "PRINT_LIST") == 0)
    {
        printFrames(headFrame, &frames); //getting the frames 
        strcpy(response, frames);   //sending them as a response
        free(frames);  //freeing the frames
    }
    else if (strcmp(command, "PLAY") == 0)
    {
        play(headFrame); //playing the video for the command
        strcpy(response, "Played video"); //sending response played
    }
    else if (strcmp(command, "SAVE_FRAMES") == 0)
    {
        path = strtok(NULL, " ");
        saveFile(headFrame, path, response); //getting the path and saving the file
    }
    else if (strcmp(command, "LOAD") == 0)
    {
        path = strtok(NULL, " ");
        headFrame = loadFile(path, response); //loading rhe file from the path
    }
    else
    {
        //if the command isnt known then send the response of invalid command
        strcpy(response, "Invalid command");
    }

    return headFrame;
}
