#ifndef FILEHELPER
#define FILEHELPER
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"
#include "view.h"
#include "fileHelper.h"
//max linee input
#define MAX_BUFFER 100

/*
handling everything that has files if its saving the files and loading them it handles everything
in it each thing creating the file and loading the file info and addiing it to a linked list
*/

/*
a function that saves the file by the path we get it doesnt matter the which type it is 
its saves the file like text in the format
path,duration,name
it basicly just takes each node(first checking if its a valid location and file and not just a directory) creating a file in he loctaion
wrting each node with the format until the end of the nodes 
yes also sending a correct response and getting the file path so it will save it in that location
input: the frameNodes, and path of the file and the reponse
output: none
*/
void saveFile(FrameNode* frameNodes, char* path, char* response);
/*
the function will just load the file we load it in that format loading the file and creating a node list
path,duration,name
we get it using sscanf we get the info we want by splitting the lines using , and in the end \n we get each info to hes location
and we just create a new node with it each time creating a node from the staff we got and inputing it last
input: the filepath to write to and the response to write
output: the new head that we loaded with all the frameNodes
*/
FrameNode* loadFile(char* filePath, char* response);
#endif