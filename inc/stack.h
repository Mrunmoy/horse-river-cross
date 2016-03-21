#ifndef __STACK_H__
#define __STACK_H__

#define MAX_STACK_SIZE		1200


extern int stack_init(void);
extern void stack_deinit(void);
extern int stack_last(void);
extern int stack_first(void);
extern int stack_pop(void);
extern int stack_push(int n);
extern void stack_clear(void);
extern void print_spacetilltop(void);

#endif /* __STACK_H__ */