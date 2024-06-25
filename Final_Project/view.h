/*********************************
* Class: MAGSHIMIM Final Project *
* Play function declaration          *
**********************************/

#ifndef VIEWH
#define VIEWH
#define CV_IGNORE_DEBUG_BUILD_GUARD

#include <opencv2/imgcodecs/imgcodecs_c.h>
#include <stdio.h>
#include <stdlib.h>
#include <opencv2\core\core_c.h>
#include <opencv2\highgui\highgui_c.h>
#include "linkedList.h"
#include "view.h"
#define GIF_REPEAT 5
#define STR_DURATION 6

/*
the menu handles the gui info handles the play and every gui staff
*/


/*
the function just plays the video using the opencv library and repeating it 
by the amount we inputed to repeat it using the nodeList we got
input: frameList
output: none
*/
void play(FrameNode* list);
/*
the function tkaes the head of the frame and the frames double pointer so we can get the frames info written into the place in the memory then
we take the total size of the frames the name the path the duration we just get the the info for the frames into a string
so we would send it to the server!
input: headFrame , and the frames double pointer 
output: none
*/
void printFrames(FrameNode* headFrameNode, char** frames);

#endif