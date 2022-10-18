// ======================================================================
// FILE:        MyAI.cpp
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

#include "MyAI.hpp"

MyAI::MyAI() : Agent()
{
	// ======================================================================
	// YOUR CODE BEGINS
	// ======================================================================
	lastAct = 'i';
	visStart = 1;
	agentX = 0;
	agentY = 0;
	agentDir = 'R';
	gotGold = false;
	creatCoor = false;
	backStart = false;
	// ======================================================================
	// YOUR CODE ENDS
	// ======================================================================
}

Agent::Action MyAI::getAction
(
	bool stench,
	bool breeze,
	bool glitter,
	bool bump,
	bool scream
)
{
	// ======================================================================
	// YOUR CODE BEGINS
	// ======================================================================

	//initialize
	if (creatCoor == false)
	{
		char** coor = coordinate();
		creatCoor = true;
	}
	isStench = stench;
	isBreeze = breeze;
	isBump = bump;
	isGold = glitter;
	
	// agent at (x,0)
	if (agentY == 0)
	{
		// agent at (0,0) case:
		if (agentX == 0 && visStart == 1)
		{
			// breeze/stench --> turn and climb
			if (isBreeze == true || isStench == true) 
			{
				visStart = 2;
				if (lastAct == 'l')
				{
					return CLIMB;
				}
				else
				{
					lastAct = 'l';
					updateDirection();
					return TURN_LEFT;
				}
			}
			// got gold --> climb
			else if (gotGold == true) 
			{
				visStart = 2;
				return CLIMB;
			}
			// otherwise, moveforward
			else
			{
				visStart = 2;
				lastAct = 'f';
				updatePosition();
				//updateCoor();
				return FORWARD;
			}
		}
		// got gold --> climb
		else if (agentX == 0 && gotGold == true)
		{
			return CLIMB;
		}
		// visit start point 2nd time:
		else if (agentX == 0 && visStart == 2)
		{
			backStart = false;
			if (agentDir == 'L')
			{
				lastAct = 'r';
				updateDirection();
				return TURN_RIGHT;
			}
			else if (lastAct == 'l')
			{
				return CLIMB;
			}
			else
			{
				lastAct = 'f';
				updatePosition();
				//updateCoor();
				return FORWARD;
			}
		}
		// visit start point more than 2 times --> climb
		else if (agentX == 0 && visStart > 2)
		{
			if (agentY == 0)
			{
				return CLIMB;
			}
		}
		// agent at (x,0) case:
		else                                        
		{
			visStart = 2;
			// found a gold --> grab and go back to start point
			if (isGold == true)                       
			{
				backStart = true;
				gotGold = true;
				lastAct = 'g';
				return GRAB;
			}
			if (gotGold == true)
			{
				if (agentDir != 'L')
				{
					lastAct = 'l';
					updateDirection();
					return TURN_LEFT;
				}
				else
				{
					lastAct = 'f';
					updatePosition();
					//updateCoor();
					return FORWARD;
				}
			}
			// breeze/stench --> go back to start point
			else if (isBreeze == true || isStench == true)
			{
				backStart = true;
				if (agentDir == 'L')
				{
					lastAct = 'f';
					updatePosition();
					//updateCoor();
					return FORWARD;
				}
				else
				{
					lastAct = 'l';
					updateDirection();
					return TURN_LEFT;
				}
			}
			// reach xMax --> go up
			else if (isBump == true || agentY == 6)
			{
				if (agentDir != 'U')
				{
					lastAct = 'l';
					updateDirection();
					return TURN_LEFT;
				}
				else
				{
					lastAct = 'f';
					updatePosition();
					//updateCoor();
					return FORWARD;
				}
			}
			// back to start point
			else
			{
				if (backStart != true)
				{
					lastAct = 'f';
					updatePosition();
					return FORWARD;
				}
				else
				{
					if (agentDir != 'L')
					{
						lastAct = 'r';
						updateDirection();
						return TURN_RIGHT;
					}
					else
					{
						lastAct = 'f';
						updatePosition();
						return FORWARD;
					}
				}
			}
		}
	}
	// agnet at (0,y):
	else if (agentX == 0)
	{
		visStart = 3;
		visStart++;
		// found a gold --> grab and go back to start point
		if (isGold == true)
		{
			backStart = true;
			gotGold = true;
			lastAct = 'g';
			return GRAB;
		}
		if (gotGold == true)
		{
			if (agentDir != 'D')
			{
				lastAct = 'l';
				updateDirection();
				return TURN_LEFT;
			}
			else
			{
				lastAct = 'f';
				updatePosition();
				//updateCoor();
				return FORWARD;
			}
		}
		// breeze/stench --> go back to start point
		else if (isBreeze == true || isStench == true)
		{
			backStart = true;
			if (agentDir == 'D')
			{
				lastAct = 'f';
				updatePosition();
				//updateCoor();
				return FORWARD;
			}
			else
			{ 
				lastAct = 'l';
				updateDirection();
				return TURN_LEFT;
			}
		}
		// reach yMax --> go right
		else if (isBump == true || agentY == 6)
		{
			if (agentDir != 'R')
			{
				lastAct = 'r';
				updateDirection();
				return TURN_RIGHT;
			}
			else
			{
				lastAct = 'f';
				updatePosition();
				//updateCoor();
				return FORWARD;
			}
		}
		// back to start point
		else
		{
			if (backStart != true)
			{
				lastAct = 'f';
				updatePosition();
				return FORWARD;
			}
			else
			{
				if (agentDir != 'D')
				{
					lastAct = 'r';
					updateDirection();
					return TURN_RIGHT;
				}
				else
				{
					lastAct = 'f';
					updatePosition();
					return FORWARD;
				}
			}
		}
	}
	// agent at (xMax, y) or (x, yMax) case:
	else
	{
		// agent at (x, yMax)  case:
		if (agentDir == 'R')
		{
			visStart = 3;
			// found a gold --> grab and go back to start point
			if (isGold == true)
			{
				backStart = true;
				gotGold = true;
				lastAct = 'g';
				return GRAB;
			}
			// found a gold, breeze, stench or reach xMax --> make a righ turn => facing down
			else if (gotGold == true || isBreeze == true || isStench == true || isBump == true || agentY == 6)
			{
				backStart = true;
				lastAct = 'r';
				updateDirection();
				return TURN_RIGHT;
			}
			// otherwise, move forward
			else
			{
				lastAct = 'f';
				updatePosition();
				//updateCoor();
				return FORWARD;
			}
		}
		// agent at (xMax, y)  case:
		else if (agentDir == 'U')
		{
			// found a gold --> grab and go back to start point
			if (isGold == true)
			{
				backStart = true;
				gotGold = true;
				lastAct = 'g';
				return GRAB;
			}
			// found a gold, breeze, stench or reach xMax --> make a righ turn => facing down
			else if (gotGold == true || isBreeze == true || isStench == true || isBump == true || agentY == 6)
			{
				backStart = true;
				lastAct = 'l';
				updateDirection();
				return TURN_LEFT;
			}
			// otherwise, move forward
			else
			{
				lastAct = 'f';
				updatePosition();
				//updateCoor();
				return FORWARD;
			}
		}
		else if (agentDir == 'D')
		{
			// agent at (xMax, y) -- go back case:
			if (visStart == 2)
			{
				lastAct = 'f';
				updatePosition();
				//updateCoor();
				return FORWARD;
			}
			// agent at (x, yMax)  -- go back case :
			else
			{
				lastAct = 'r';
				updateDirection();
				return TURN_RIGHT;
			}
		}
		else
		{
			// agent at (xMax, y)  -- go back case :
			if (visStart == 3)
			{
				lastAct = 'f';
				updatePosition();
				//updateCoor();
				return FORWARD;
			}
			// agent at (x, yMax) -- go back case:
			else
			{
				lastAct = 'l';
				updateDirection();
				return TURN_LEFT;
			}

		}
	}
	

	// ======================================================================
	// YOUR CODE ENDS
	// ======================================================================
}

// ======================================================================
// YOUR CODE BEGINS
// ======================================================================

char** MyAI::coordinate()
{
	char** coor = new char*[8];
	for (int i = 0; i < 8; i++)
	{
		coor[i] = new char[8];
		for (int j = 0; j < 8; j++)
		{
			if (i == 8 || j == 8)
				coor[i][j] = 'X';
			else
				coor[i][j] = ' ';
		}
	}
	return coor;
}

void MyAI::updatePosition()
{
	if (agentDir == 'R')
	{
		agentX += 1;
	}
	else if (agentDir == 'L')
	{
		agentX -= 1;
	}
	else if (agentDir == 'U')
	{
		agentY += 1;
	}
	else
	{
		agentY -= 1;
	}
}

void MyAI::updateDirection()
{
	if (agentDir == 'U')
	{
		if (lastAct == 'l')
			agentDir = 'L';
		else if (lastAct == 'r')
			agentDir = 'R';
		else
			agentDir = 'U';
	}
	else if (agentDir == 'D')
	{
		if (lastAct == 'l')
			agentDir = 'R';
		else if (lastAct == 'r')
			agentDir = 'L';
		else
			agentDir = 'D';
	}
	else if (agentDir == 'L')
	{
		if (lastAct == 'l')
			agentDir = 'D';
		else if (lastAct == 'r')
			agentDir = 'U';
		else
			agentDir = 'L';
	}
	else
	{
		if (lastAct == 'l')
			agentDir = 'U';
		else if (lastAct == 'r')
			agentDir = 'D';
		else
			agentDir = 'R';
	}
	
}
/*
void MyAI::updateCoor()
{
	if (isGold == true)
	{
		coor[agentX][agentY] = 'G';
	}
	else if (isBreeze == true)
	{
		coor[agentX][agentY] = 'B';
	}
	else if (isStench == true)
	{
		coor[agentX][agentY] = 'S';
	}
	else if (isBump == true)
	{
		if (agentX == 0)
			coor[agentX][agentY + 1] = 'X';
		else
			coor[agentX + 1][agentY] = 'X';
	}
	else
	{
		coor[agentX][agentY] = '-';
	}
}
*/

// ======================================================================
// YOUR CODE ENDS
// ======================================================================