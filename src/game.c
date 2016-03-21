#include <stdio.h>
#include <stdlib.h>
#include "../inc/game.h"
#include "../inc/stack.h"
/*
---------------------------------------
			[ 0]	[ 1]	[ 2]
	[3]		[ 4]	[ 5]	[ 6]
	[7]		[ 8]	[ 9]	[10]
			[11]	[12]	[13]
---------------------------------------
			H
*/
pNode_t game_board;

int check_game_complete(pNode_t pHorse, pNode_t pStone);


void reset_gameboard(void)
{
	int i;
	/* initialize game board */
	for (i = 0; i < MAX_GAME_STEPS; i++)
	{
		game_board[i].step_num = i;
		game_board[i].state = ST_AVAILABE;
		game_board[i].back_step = NULL;
		game_board[i].right_step = NULL;
		game_board[i].middle_step = NULL;
		game_board[i].left_step = NULL;
	}

	/* setup the game board travel rule */
	game_board[0].left_step = &game_board[6];
	game_board[0].middle_step = &game_board[9];
	game_board[0].right_step = &game_board[7];

	game_board[1].left_step = &game_board[10];
	game_board[1].middle_step = &game_board[8];
	game_board[1].right_step = &game_board[3];

	game_board[2].left_step = &game_board[9];
	game_board[2].middle_step = &game_board[4];

	game_board[3].left_step = &game_board[1];
	game_board[3].middle_step = &game_board[9];
	game_board[3].right_step = &game_board[11];

	game_board[4].left_step = &game_board[2];
	game_board[4].middle_step = &game_board[10];
	game_board[4].right_step = &game_board[12];

	game_board[5].left_step = &game_board[13];
	game_board[5].middle_step = &game_board[11];
	game_board[5].right_step = &game_board[7];

	game_board[6].left_step = &game_board[12];
	game_board[6].middle_step = &game_board[8];
	game_board[6].right_step = &game_board[0];

	game_board[7].left_step = &game_board[0];
	game_board[7].middle_step = &game_board[5];
	game_board[7].right_step = &game_board[12];

	game_board[8].left_step = &game_board[1];
	game_board[8].middle_step = &game_board[6];
	game_board[8].right_step = &game_board[13];

	game_board[9].left_step = &game_board[3];
	game_board[9].middle_step = &game_board[0];
	game_board[9].right_step = &game_board[2];

	game_board[10].left_step = &game_board[11];
	game_board[10].middle_step = &game_board[4];
	game_board[10].right_step = &game_board[1];

	game_board[11].left_step = &game_board[3];
	game_board[11].middle_step = &game_board[5];
	game_board[11].right_step = &game_board[10];

	game_board[12].left_step = &game_board[7];
	game_board[12].middle_step = &game_board[4];
	game_board[12].right_step = &game_board[6];

	game_board[13].left_step = &game_board[8];
	game_board[13].middle_step = &game_board[5];
}


int game_init(void)
{
	int result = 0;

	/* initialize stack */
	if (stack_init() < 0)
	{
		printf("Failed to initialize stack.\n");
		result = GAME_INIT_ERROR;
	}
	else
	{
		game_board = (pNode_t)malloc(sizeof(Node_t)*MAX_GAME_STEPS);

		if (game_board)
		{
			/* initialize game board */
			reset_gameboard();
		}
		else
		{
			result = GAME_INIT_ERROR;
		}
	}

	return result;
}


void game_deinit(void)
{
	int i;
	for (i = 0; i < MAX_GAME_STEPS; i++)
	{
		game_board[i].back_step = NULL;
		game_board[i].right_step = NULL;
		game_board[i].middle_step = NULL;
		game_board[i].left_step = NULL;
	}
	free(game_board);
	stack_deinit();
}

pNode_t GetStartStone(int n)
{
	if (n < MAX_GAME_STEPS)
	{
		reset_gameboard();
		stack_clear();
		stack_push(n);
		return &game_board[n];
	}

	return NULL;
}

int AllStonesCleared(pNode_t pHorse, pNode_t pStone)
{
	int i;

	for (i = 0; i < MAX_GAME_STEPS; i++)
	{
		if (game_board[i].state == ST_AVAILABE)
			return GAME_OVER;
	}

	return (check_game_complete(pHorse, pStone));
}

int check_game_complete(pNode_t pHorse, pNode_t pStone)
{
	int start = stack_first();
	int last = stack_last();

	if (last < MAX_GAME_STEPS)
	{
		int left = (game_board[last].left_step) ? game_board[last].left_step->step_num : -1;
		int middle = (game_board[last].middle_step) ? game_board[last].middle_step->step_num : -1;
		int right = (game_board[last].right_step) ? game_board[last].right_step->step_num : -1;

		if ((start == left) || (start == middle) || (start == right))
		{
			return GAME_WON;
		}
	}
	return GAME_OVER;
}

int Try_left(pNode_t pHorse, pNode_t pStone)
{
	int result = ROAD_CLOSED;
	if ((result = AllStonesCleared(pHorse, pStone)) != GAME_WON)
	{
		/*
		if a step is present on the left
		*/
		if (pStone->left_step)
		{
			/*
			if this step is available
			*/
			if (pStone->left_step->state != ST_STEPPED)
			{
				pStone->left_step->back_step = pStone;
				pStone = pStone->left_step;
				pStone->state = ST_STEPPED;
				pHorse = pStone;
				printf("[L]");
				stack_push(pStone->step_num);
				result = Take_step(pHorse, pStone);
			}
			else
			{
				result = STEP_TAKEN;
			}
		}
	}
	return result;
}


int Try_middle(pNode_t pHorse, pNode_t pStone)
{
	int result = ROAD_CLOSED;
	if ((result = AllStonesCleared(pHorse, pStone)) != GAME_WON)
	{
		/*
		if a step is present on the left
		*/
		if (pStone->middle_step)
		{
			/*
			if this step is available
			*/
			if (pStone->middle_step->state != ST_STEPPED)
			{
				pStone->middle_step->back_step = pStone;
				pStone = pStone->middle_step;
				pStone->state = ST_STEPPED;
				pHorse = pStone;
				printf("[M]");
				stack_push(pStone->step_num);
				result = Take_step(pHorse, pStone);
			}
			else
			{
				result = STEP_TAKEN;
			}
		}
	}
	return result;
}


int Try_right(pNode_t pHorse, pNode_t pStone)
{
	int result = ROAD_CLOSED;
	if ((result = AllStonesCleared(pHorse, pStone)) != GAME_WON)
	{
		/*
		if a step is present on the left
		*/
		if (pStone->right_step)
		{
			/*
			if this step is available
			*/
			if (pStone->right_step->state != ST_STEPPED)
			{
				pStone->right_step->back_step = pStone;
				pStone = pStone->right_step;
				pStone->state = ST_STEPPED;
				pHorse = pStone;
				printf("[R]");
				stack_push(pStone->step_num);
				result = Take_step(pHorse, pStone);
			}
			else
			{
				result = STEP_TAKEN;
			}
		}
	}

	return result;
}

int Go_back(pNode_t pHorse, pNode_t pStone)
{
	int result = ROAD_CLOSED;
	/*
	if back step is available
	*/
	if (pStone->back_step)
	{
		pNode_t tmp = pStone;
		/* Mark the current stone as availabe */
		pStone->state = ST_AVAILABE;
		pStone = pStone->back_step;
		tmp->back_step = NULL;
		pHorse = pStone;
		//print_spacetilltop();
		//printf("[B]%-2d", pStone->step_num);
		stack_pop();
		result = STEPPED_BACK;
	}

	return result;
}


int Take_step(pNode_t pHorse, pNode_t pStone)
{
	int result = -1;

	if ((result = AllStonesCleared(pHorse, pStone)) != GAME_WON)
	{
		/*
		Try stepping on left stone
		*/
		if ((result = Try_left(pHorse, pStone)) != GAME_WON)
		{
			/*
			Try stepping on middle stone
			*/
			if ((result = Try_middle(pHorse, pStone)) != GAME_WON)
			{
				/*
				Try stepping on right stone
				*/
				if ((result = Try_right(pHorse, pStone)) != GAME_WON)
				{
					/* take a step back */
					printf("\n");
					result = Go_back(pHorse, pStone);
				}
			}
		}
	}
	return result;
}


int Game_GetStackTop(void)
{
	return stack_pop();
}