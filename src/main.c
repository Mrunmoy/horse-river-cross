#include <stdio.h>
#include "../inc/game.h"



int main(void)
{
	int i, r = 0, result;
	pNode_t horse = NULL;
	pNode_t curStone = NULL;

	/* initialize game */
	if (game_init() < 0)
	{
		printf("Failed to initialize game.\n");
	}

	for (i = 0; (i < MAX_GAME_STEPS); i++)
	{
		/* horse takes first step */
		printf("\n===================================================================================================");
		printf("\n[S]");
		curStone = horse = GetStartStone(i);
		curStone->state = ST_STEPPED;

		result = Take_step(horse, curStone);

		if (AllStonesCleared(horse, curStone) == GAME_WON)
		{
			printf("Game solved!\n**********************************************************************************\n");
		}
		else
		{
			printf("could not solve starting at stone : %d\n", i);
		}
	}


	game_deinit();

	return 0;
}



