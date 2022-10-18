// ======================================================================
// FILE:        MyAI.hpp
//
// AUTHOR:      Abdullah Younis
//
// DESCRIPTION: This file contains your agent class, which you will
//              implement. You are responsible for implementing the
//              'getAction' function and any helper methods you feel you
//              need.
//
// NOTES:       - If you are having trouble understanding how the shell
//                works, look at the other parts of the code, as well as
//                the documentation.
//
//              - You are only allowed to make changes to this portion of
//                the code. Any changes to other portions of the code will
//                be lost when the tournament runs your code.
// ======================================================================

#ifndef MYAI_LOCK
#define MYAI_LOCK

#include <iostream>
#include "Agent.hpp"

class MyAI : public Agent
{
public:
	MyAI(void);

	Action getAction
	(
		bool stench,
		bool breeze,
		bool glitter,
		bool bump,
		bool scream
	);

	// ======================================================================
	// YOUR CODE BEGINS
	// ======================================================================
	char** coordinate();
	void updatePosition();
	void updateDirection();
	//void updateCoor();

private:
	int agentX;
	int agentY;
	int visStart;
	char lastAct;
	char agentDir;
	bool backStart;
	bool creatCoor;
	bool gotGold;
	bool isGold;
	bool isBump;
	bool isPit;
	bool isWumps;
	bool isBreeze;
	bool isStench;
	char** coor;


	// ======================================================================
	// YOUR CODE ENDS
	// ======================================================================
};

#endif