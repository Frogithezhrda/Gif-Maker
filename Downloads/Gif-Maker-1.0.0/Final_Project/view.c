/*********************************
* Class: MAGSHIMIM Final Project *
* Play function				 	 *
**********************************/
#pragma warning(disable:4996)
#include "view.h"
/**
play the movie!!
display the images each for the duration of the frame one by one and close the window
input: a linked list of frames to display
output: none
**/
void play(FrameNode* list)
{
	cvNamedWindow("Display window", CV_WINDOW_AUTOSIZE); //create a window
	FrameNode* head = list;
	int imgNum = 1, playCount = 0;
	IplImage* image;
	while (playCount < GIF_REPEAT)
	{
		while (list != 0)
		{
			image = cvLoadImage(list->frame->path, 1);
			IplImage* pGrayImg = 0;
			pGrayImg = cvCreateImage(cvSize(image->width, image->height), image->depth, 1);
			if (!image) //The image is empty - shouldn't happen since we checked already.
			{
				printf("Could not open or find image number %d", imgNum);
			}
			else
			{
				cvShowImage("Display window", image); //display the image
				cvWaitKey(list->frame->duration); //wait
				list = list->next;
				cvReleaseImage(&image);
			}
			imgNum++;
		}
		list = head; // rewind
		playCount++;
	}
	cvDestroyWindow("Display window");
	return;
}


void printFrames(FrameNode* headFrameNode, char** frames)
{
    //setting variables
    char* durationStr = NULL;
    FrameNode* current = headFrameNode;
    int totalLength = 0;
    //mallocing small size so we can send it to the frames if they dont have anything
    *frames = (char*)malloc(sizeof(char) * 2);
    // sizing the duration str
    durationStr = (char*)malloc(sizeof(char) * STR_DURATION);
    //if the frames count is 0 than return nothing so the server will know to do nothing
    if (!headFrameNode)
    {
        strcpy(*frames, " ");
        return;
    }

    while (current)
    {
        totalLength += strlen(current->frame->path) + 1; // +1 for space separator
        totalLength += strlen(current->frame->name) + 1; // +1 for space separator
        totalLength += STR_DURATION;  // also adding the duration that might have saying the max will be about 999999
        totalLength += 3;  //spaces
        current = current->next;
    }
    //reallocing the size for the frames
    *frames = (char*)realloc(*frames, sizeof(char) * totalLength + 1);
    (*frames)[0] = '\0'; //resseting everything so there wont be anything else
    //reseting the current to equal to the first node
    current = headFrameNode;
    while (current)
    {
        //copying the path the name and the duration into the frames
        strcat(*frames, current->frame->path);
        strcat(*frames, " ");
        strcat(*frames, current->frame->name);
        strcat(*frames, " ");
        sprintf(durationStr, "%d", current->frame->duration);  // converting the  int to str
        strcat(*frames, durationStr);
        strcat(*frames, "\n");
        current = current->next;
    }
    //freeing the durationstring
    free(durationStr);
}
