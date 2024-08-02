#ifndef LINKEDLISTH
#define LINKEDLISTH
/*
handling all things that are related to the linkedlist like creating a frame switching places changing durations etc
also we free al the frames all the function related to linked lists of the frames are here.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "linkedList.h"
//max buffer inout
#define BUFFER_MAX 100
//how many chars to check in the end
#define END_CHECK 5
// Frame struct
typedef struct Frame
{
	char* name;
	unsigned int duration;
	char* path;
} Frame;


// Link (node) struct
typedef struct FrameNode
{
	Frame* frame;
	struct FrameNode* next;
} FrameNode;
/*
checking if the file ends with 3 of the image type files png jfif or jpg because if we get something which is not an image
the play function will get an error so we weill check if its an actual image
we check if the last 5 chars is the .jfif or .png or .jpg by checking in the end of the string we get in the path
input: path to check
output: if the file isValid
*/
bool checkFileValid(char* path, char* response);
/*
getting each part we need to create of the node creating the frame and putting all the info to it
and creating the node to it the next node putting the frame of frameNode to equal the frame we created with all info
putting memory to it and the name to the node with the struct just creating a frame and putting to the node
input: name, duration, and path
output: the new frame that we created
*/
FrameNode* createFrameNode(char* name, unsigned int duration, char* path);
/*
adding the frame by creating the frame or the head frame depends on what we go inputed we create the new frame and getting it
putting it in the head of the headframe and adding it to the list checking if the file is valid or not checking if the durration is valid
and not adding the frame if it has any flaws getting the response into the response inputed
input: the head frame node, the duration the name the path and the response
output: the new head with the added frame
*/
FrameNode* addFrame(FrameNode* headFrameNode, int duration, char* name, char* path, char* response);
/*
we send the head and the new node and go on the loop until we get to the end there we put instead of the next we put the new node
and make the head node equal the new list we created with the node we inputed in the end
input: the pointer to the headnode and the node we want to input
output: none
*/
void insertAtEnd(FrameNode** headNode, FrameNode* newNode);
/*
getting the headFrame node and the name to check we will go thorguth the function check for each name if we found it
if we did we will return taht we found eelse we will response that we didnt and return false
input: head to search and name to search
output: if wee found or not
*/
bool checkNameInList(FrameNode* headFrameNode, char* nameToCheck);/*
getting the pointer to the head node we will remove it from the linked list check if the head isnt null and go and search
if he is the name we inputed if it is than we will remove the head else we dont and go to the next and we will remove the other
part if it equals to the head if it didnt find the frame with the same name than responsed and return the normal headFrame
input: pointer to the headFrame, the name to remove the respnse
output: new head with removed frame
*/
void removeFrame(FrameNode** headFrameNode, char* name, char* response);
/*
just a function that takes all of the duration to change all of the durations into and makes each duration of the linked list
equal to that new duration we want it to
input: head to change all durations, the durations and the response
output: the new headFrame with the corrected all new durations
*/
FrameNode* changeAllDurations(FrameNode* headFrameNode, int durations, char* response);
/*
inside the fucntion we will get a name of a specific name to change the duration of it
go thorugh a loop get the name if it exists change the duration we also get from the user and change the duration of that secific node
else we just respone we that we didnt find the frame
input: head to check name of which duration to change, the duration we want to change into the response
output: headwith changed duration
*/
FrameNode* changeFrameDuration(FrameNode* headFrameNode, char* name, int duration, char* response);
/*
we get the frame name to change the location of and the index to change it we check if the index is ok
and we check if the list isnt null we find the frames and switch their locations by the inputed staff
by checking the name location and the index frame and switching them
input: the headframe to act on, the index to swithc the name the response
output: new head with changed location
*/
FrameNode* changeFrameLocation(FrameNode* headFrameNode, int index, char* name, char* response);
/*
we get the headOfthe frames we want to remove and we just go to each save the first go to the next one of the frame
and free the temp node we created we free using freeFrame which frees everything in the frrame
input: headFrame to free all from it
output: none
*/
void freeFrames(FrameNode* headFrameNodes);
/*
function that gets a specific node to free it takes that node and free each part of it the name path the frame itself
and the node itself
input: node to free
output: none
*/
void freeFrame(FrameNode* nodeToFree);

#endif
