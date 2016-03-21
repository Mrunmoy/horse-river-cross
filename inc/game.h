#ifndef __GAME_H__
#define __GAME_H__

#define MAX_GAME_STEPS	(14)

typedef enum StepState_t {
	ST_AVAILABE = 0,
	ST_TRIED,
	ST_STEPPED
}StepState_t;


#define STEP_TAKEN		  (-1)
#define GAME_OVER		  (-2)
#define ROAD_CLOSED       (-3)
#define GAME_INIT_ERROR   (-4)
#define GAME_WON		  (0)
#define STEPPED_BACK      (1)


struct Node_t
{
	int step_num;
	StepState_t state;
	struct Node_t *right_step;
	struct Node_t *middle_step;
	struct Node_t *left_step;
	struct Node_t *back_step;
};

typedef struct Node_t Node_t;
typedef struct Node_t * pNode_t;

extern int game_init(void);
extern void game_deinit(void);
extern pNode_t GetStartStone(int n);
extern int Game_GetStackTop(void);
extern int Try_left(pNode_t pHorse, pNode_t pStep);
extern int Try_middle(pNode_t pHorse, pNode_t pStep);
extern int Try_right(pNode_t pHorse, pNode_t pStep);
extern int Go_back(pNode_t pHorse, pNode_t pStone);
extern int Take_step(pNode_t pHorse, pNode_t pStone);
extern int AllStonesCleared(pNode_t pHorse, pNode_t pStone);



#endif /* __GAME_H__ */