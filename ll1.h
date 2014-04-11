#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define LENGTH_RHS 40
#define NUM_PROD 10
#define NUM_TERM 20

#define True 1
#define False 0

char V[NUM_PROD];
char toFindFollowList[NUM_PROD];

struct productions {
	char variables;
	struct RHS_productions * produces;
};
  
struct RHS_productions {
	char production[LENGTH_RHS];
	struct RHS_productions * next;
};

struct first_set {
	char var;
	char firsts[NUM_TERM];
	int epsilon;
}first[NUM_PROD];

struct follow_set {
  char var;
  char follows[NUM_TERM];
}follow[NUM_PROD];

struct productions * grammar[NUM_PROD];


