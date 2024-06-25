#include "fileHelper.h"

#pragma warning(disable:4996)


void saveFile(FrameNode* frameNodes, char* path, char* response)
{
    FILE* file = NULL;
    file = fopen(path, "w"); //if the file is a valid file not jsut a location than it will open else
    if (file == NULL) 
    {
        strcpy(response, "Failed To Create File/Open!"); //reponse this and free the path
        return;
    }
    while (frameNodes) //for each node write it into a file with the format path,duration,name
    {
        fprintf(file, "%s,%d,%s\n", frameNodes->frame->path, frameNodes->frame->duration, frameNodes->frame->name); //getting each thing from the frame
        frameNodes = frameNodes->next; //going to the next check
    }
    strcpy(response, "Frames saved!"); //getting the response to the server
    fclose(file); //closing the file
}

FrameNode* loadFile(char* filePath, char* response)
{
    char* line = NULL;
    FILE* file = NULL;
    FILE* fileChecker = NULL;
    char* name = NULL;
    char* path = NULL;
    char* durationStr = NULL;
    unsigned int duration = 0;
    FrameNode* headFrameNode = NULL;
    FrameNode* tempNode = NULL;
    file = fopen(filePath, "r");
    if (file == NULL) //if it doesnt exist than just fre the path and the line and create a new project
    {
        strcpy(response, "Failed To Open!!"); //the reponse to the server
        return headFrameNode;
    }
    line = (char*)malloc(sizeof(char) * MAX_BUFFER);
    while (fgets(line, MAX_BUFFER, file) != NULL) //reading each line with max 100 chars
    {
        path = (char*)malloc(sizeof(char) * strlen(line) + 1); //mallocing for each thee size
        name = (char*)malloc(sizeof(char) * strlen(line) + 1);
        durationStr = (char*)malloc(sizeof(char) * strlen(line) + 1);
        sscanf(line, "%[^,],%[^,],%[^\n]", path, durationStr, name); //getting the line from it and splitting it for each using sscanf
        //which tells it to read everything from the string execpt the comma [^,] reprsents reading everything but a comma so the same with \n
        path = realloc(path, sizeof(char) * strlen(path) + 1); //reallocing the info to be as efficent we can
        name = realloc(name, sizeof(char) * strlen(name) + 1);
        duration = atoi(durationStr);
        if (!(duration == 0 || name == NULL || path == NULL))
        {
            fileChecker = fopen(path, "r");
            if (fileChecker)
            {
                tempNode = createFrameNode(name, duration, path); //we shall create a node with all of the staff we gathered and insert it at thee end
                insertAtEnd(&headFrameNode, tempNode);
                fclose(fileChecker);
            }
        }
        free(path); //we free everthing
        free(name);
        free(durationStr);
    }
    fclose(file);
    free(line);
    strcpy(response, "Loaded Frames"); //just sending the response to the server as the response
    return headFrameNode;
}