#include "linkedList.h"

#pragma warning(disable:4996)

FrameNode* createFrameNode(char* name, unsigned int duration, char* path)
{
	FrameNode* newFrameNode = (FrameNode*)malloc(sizeof(FrameNode)); //mallocing some memory just for the Node
	Frame* frame = (Frame*)malloc(sizeof(Frame)); //memory for the frame
	frame->name = (char*)malloc(strlen(name) + 1); //memory for the name
	frame->path = (char*)malloc(strlen(path) + 1); //memory for the path
	strcpy(frame->name, name); //copying name and path to their frame location
	strcpy(frame->path, path);
	frame->duration = duration; //duration equals to duration
	newFrameNode->frame = frame; //equaling the frames with thee nodeFrame
	newFrameNode->next = NULL; 
	return newFrameNode;
}

FrameNode* addFrame(FrameNode* headFrameNode, int duration, char* name, char* path, char* response)
{
	FrameNode* newFrameNode = NULL;
	FILE* fileCheck = NULL;

	fileCheck = fopen(path, "r"); //checking if the file opens than it exists else it doesnt
	if (fileCheck == NULL) //if its null then it doesnt exists
	{
		strcpy(response, "File Doesn't Exist!");
		return headFrameNode;
	}
	if (duration <= 0) //if the durtaion is 0 or less than it isnt valid
	{
		strcpy(response, "Not A Valid Duration!");
		return headFrameNode;
	}
	if (!checkNameInList(headFrameNode, name)) //if the name isnt in the list already join
	{
		if (checkFileValid(path, response)) //if its an image file than create the frame
		{
			newFrameNode = createFrameNode(name, duration, path); //creating a new node
			insertAtEnd(&headFrameNode, newFrameNode); //and inserting in the end and closing the file
			fclose(fileCheck);
		}
	}
	else
	{
		strcpy(response, "Name Already In File!");
		return headFrameNode;
	}
	strcpy(response, "Added Frame!");
	return headFrameNode;
}

void insertAtEnd(FrameNode** headNode, FrameNode* newNode)
{
	FrameNode* frameNode = *headNode;
	if (!*headNode) //if the head isnt null
	{
		*headNode = newNode; //head is the newNode
	}
	else
	{
		while (frameNode->next) //adding the nodes to the linked list
		{
			frameNode = frameNode->next;
		}
		frameNode->next = newNode;
	}
}
//we got to check if its an image file becuase if its not and you run it than the program will crash
bool checkFileValid(char* path, char* response)
{
	int pathLength = 0;
	int i = 0;
	char* pathTemp = NULL;
	pathLength = strlen(path);
	pathTemp = (char*)malloc(sizeof(char) * END_CHECK + 1); //checking the end which is the minumum last 5 chars .jfif(which is the image file we allowed one of them)
	if (pathLength < END_CHECK)  //if the pathLength is less than the minumum png/jpg image files
	{
		strcpy(response, "File Name Too Short!");
		return false;
	}
	for (i = 0; i < END_CHECK; i++) //we go for each one of the pathTemp ending and putting it in the next char of the str
	{
		pathTemp[i] = path[pathLength - END_CHECK + i];
	}
	pathTemp[END_CHECK] = '\0'; //putting a null
	if (strstr(pathTemp, ".jpg") || strstr(pathTemp, ".png") || strstr(pathTemp, ".jfif") || strstr(pathTemp, ".jpeg")) //checking if one of the image file types is in the end pathTemp than return true and free the memory
	{
		free(pathTemp);
		return true;
	}
	strcpy(response, "Can't Use This File!, File Is Not An Image File(jpg, png, jfif)!"); //else its not valid and return false
	free(pathTemp);
	return false;
}

bool checkNameInList(FrameNode* headFrameNode, char* nameToCheck)
{
	while (headFrameNode) //checking for each node
	{
		if (strcmp(headFrameNode->frame->name, nameToCheck) == 0) //for each name for each frame we check if its valid if it is than return true
		{
			return true;
		}
		headFrameNode = headFrameNode->next; //going to the next node
	}
	return false;
}

void removeFrame(FrameNode** headFrameNode, char* name, char* response)
{
	FrameNode* tempFrame = *headFrameNode;
	FrameNode* removedNode = NULL;
	if (*headFrameNode) //if the head is not null
	{
		if (strcmp((*headFrameNode)->frame->name, name) == 0) //then we check if the name of the headnode is the same
		{
			*headFrameNode = (*headFrameNode)->next; //we go to the next head node just the next node becuase we delte the first
			strcpy(response, "Frame Removed!");
			freeFrame(tempFrame); //free the frame
			return headFrameNode;
		}
		else
		{
			while (tempFrame->next && strcmp(tempFrame->next->frame->name, name) != 0)  //we check tempFrame->next is not null and the name of the next is not the same
			{
				tempFrame = tempFrame->next; //go to the next node
			}
			if (tempFrame->next) //we go to the next node if we found the name then it wont be null
			{
				removedNode = tempFrame->next; //we get the next of the node(the node we want to delete) 
				tempFrame->next = removedNode->next; //we now put tempFrame next to equal to the place of the old removedNode place
				freeFrame(removedNode); //freeing the removedNode(removing it)
				strcpy(response, "Frame Removed!");
				return headFrameNode;
			}
		}
	}
	strcpy(response, "Frame Not Found!");
}

FrameNode* changeFrameDuration(FrameNode* headFrameNode, char* name, int duration, char* response)
{
	FrameNode* currentNode = headFrameNode;
	if (duration <= 0) //if the durtaion is 0 or less than it isnt valid
	{
		strcpy(response,"Not A Valid Duration!");
		return headFrameNode;
	}
	while (currentNode) //as long as the node isnt null
	{
		if (strcmp(currentNode->frame->name, name) == 0) //check if we found the name
		{
			currentNode->frame->duration = duration; //than changing the duration of the name we found
			strcpy(response, "Changed Duration!"); //if we didnt find than print and just reutrn the head because we went thorguh anything and there wasnt the frame
			return headFrameNode;
		}
		currentNode = currentNode->next; //going to the next node
	}
	strcpy(response, "Couldn't Find The Frame!"); //if we didnt find than print and just reutrn the head because we went thorguh anything and there wasnt the frame
	return headFrameNode;
}


FrameNode* changeAllDurations(FrameNode* headFrameNode, int durations, char* response)
{
	FrameNode* currentNode = headFrameNode;
	if (durations <= 0) //if the duration is less than 0 or equals than its not valid
	{
		strcpy(response, "Not A Valid Duration!");
		return headFrameNode;
	}
	while (currentNode) //changing for each node the duration we got
	{
		currentNode->frame->duration = durations; //changing the durations to the duration we inputed
		currentNode = currentNode->next;
	}
	strcpy(response, "Changed Durations!");
	return headFrameNode;
}

FrameNode* changeFrameLocation(FrameNode* headFrameNode, int index, char* name, char* response) 
{
	FrameNode* tempNode = headFrameNode;
	FrameNode* prevTempNode = NULL;
	FrameNode* currentNode = headFrameNode;
	FrameNode* prevNode = NULL;
	FrameNode* targetNode = NULL;
	FrameNode* secondTempNode = NULL;
	FrameNode* prevTargetNode = NULL;
	bool flag = false;
	int i = 0;
	index -= 1; 


	if (!headFrameNode) //if there is not list
	{
		strcpy(response, "No Frames In List!");
		return headFrameNode;
	}
	if (index < 0) //if index is less than 0 its no good
	{
		strcpy(response, "Invalid index!");
		return headFrameNode;
	}

	while (tempNode && !flag) //checking if we found the node with the name and if the flag isnt false
	{
		if (strcmp(tempNode->frame->name, name) == 0) 
		{
			flag = true;
		}
		else 
		{
			prevTempNode = tempNode; //we save the one before it
			tempNode = tempNode->next; //we get the next node to search
		}
	}

	if (!flag) //if the flag is false that means we didnt find and return the head and that we didnt find
	{
		strcpy(response, "Can't Find Frame!");
		return headFrameNode;
	}

	while (i < index && currentNode)  //we get to the node of the index
	{
		prevNode = currentNode;
		currentNode = currentNode->next;
		i++;
	}

	if (!currentNode) //if the node of the indexes is NULL then the index isnt Good
	{
		strcpy(response, "Index Not Good!");
		return headFrameNode;
	}

	targetNode = currentNode; //target node is the index node
	prevTargetNode = prevNode; //and the prevNode is now the target prev that we saved

	if (prevTempNode) //if the previous of the name is not null than its the head
	{
		prevTempNode->next = targetNode; //then the next after it is the target
	}
	else
	{
		headFrameNode = targetNode; //if the node is the head then repalce it with the target node
	}

	if (prevTargetNode) //if the target next before node wasnt null that means the target isnt the head
	{
		prevTargetNode->next = tempNode; //then the next will be the name node the tempNode
	}
	else
	{
		headFrameNode = tempNode; //if the node is the head then repalce it with the target node
	}

	secondTempNode = tempNode->next; // we do the switch we save the next of the nameNode
	tempNode->next = targetNode->next; //we get the next to be the tagret node next
	targetNode->next = secondTempNode; //then we change the next of the target node to be the name node next so it will do the list correctly
	strcpy(response, "Changed Location!");
	return headFrameNode;
}


void freeFrames(FrameNode* headFrameNodes)
{
	FrameNode* temp = NULL; 
	while (headFrameNodes) //going to each node until null
	{
		temp = headFrameNodes; //temp node is the enode we want to free
		headFrameNodes = headFrameNodes->next; //going to the next node
		freeFrame(temp); //freeing the frame
	}
}

void freeFrame(FrameNode* nodeToFree)
{
	free(nodeToFree->frame->name); //freeing the name and the path
	free(nodeToFree->frame->path);
	free(nodeToFree->frame); //freeing the frame itself
	free(nodeToFree); //in the end freeing the node itself
}