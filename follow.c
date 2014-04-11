#include"ll1.h"

void initFollowSet()
{
  int i = 0;
  for (i=0; i<NUM_PROD; i++) {
    follow[i].var = '@';
    follow[i].follows[0] = '\0';
  }
}
void deleteDupFollow()
{
	int i = 0;
      	int j = 0, k = 0, flag = 0, in = 0;
	char temp[NUM_TERM];
	while(follow[i].var!='@') {
		in = 0;
		for(j=0; j<strlen(follow[i].follows); j++) {
			k = j+1;
			flag = 0;
			while(k<strlen(follow[i].follows)) {
				if(follow[i].follows[j] == follow[i].follows[k]) {
					flag = 1;
				}
				k++;
			}
			if(flag == 0) {
				temp[in] = follow[i].follows[j];
				in++;
			}
		}
		temp[in] = '\0';
		strcpy(follow[i].follows,temp);
		i++;
	}	
}
/*
void initFollow() 
{
  int i;
  for(i=0; i< NUM_PROD; i++) {
    follow[i].var = '@';
    follow[i].follows[0] = '\0';
  }
}
*/
int containEpsilon(char *str)
{
  while(*str!='\0') {
    if(*str == '#')
      return True;
    str++;
  }
  return False;
}

void removeEpsilon(char *str) {
  char temp[NUM_TERM];
  int i , j =0;
  for (i=0;i < strlen(str);i++) {
    if(str[i] == '#')
      continue;
    temp[j] = str[i];
    j++;
  }
  temp[j] = '\0';
  strcpy(str,temp);
}

int removeFollowList(char ch) 
{
  char temp[NUM_PROD];
  int i = 0;
  int ret = -1;
  int j = 0;
  while(i<strlen(toFindFollowList)) {
    if(toFindFollowList[i] == ch) {
      ret = i;
      i++;
      continue;
    }
    temp[j] = toFindFollowList[i];
    j++;
    i++;
  }
  temp[j] = '\0';
  strcpy(toFindFollowList,temp);
  return ret;
}

char * giveFirstList(char ch)
{
  int i=0;
  char * str=NULL;
  while(first[i].var != ch ) {
    i++;
  }
  str = first[i].firsts;
  return str;
}


void followFinding(char ch)
{
	int i = 0;
       	int j = 0;
	int k = 0;
	int l = 0;
	int index = 0;
	char temp[2];
		
	struct RHS_productions *ptr_s = NULL;
	if(strlen(toFindFollowList)==0) {
		return;
	}
	if((removeFollowList(ch))!=-1) {
		i = 0; 
		while(grammar[i]!=NULL) {
			if(grammar[i]->variables == ch) {
				break;
			}
			i++;
		}
		index = i;

//		printf("\n\nindex   %d\n\n",index);
		follow[index].var = ch;
		i = 0;
		while(grammar[i]!=NULL) {
			ptr_s = grammar[i]->produces;
			while(ptr_s!=NULL) {
				for(j=0; j<strlen(ptr_s->production);j++) {
					if(ch == ptr_s->production[j]) { 
						k = j+1;
						for(k=j+1;k<=strlen(ptr_s->production); k++) {
/*							if(ptr_s->production[k]=='\0') {
								
										followFinding(grammar[i]->variables);
											
										l = 0; 
										while(follow[l].var != grammar[i]->variables) {
											l++;
										}
										strcat(follow[index].follows,follow[l].follows);
									break;	
							}
*/							if(isTerminal(ptr_s->production[k])) {
								temp[0] = ptr_s->production[k];
								temp[1] = '\0';
								strcat(follow[index].follows,temp);
								break;	
							}	
							if(isVariable(ptr_s->production[k])) {
								if(containEpsilon(giveFirstList(ptr_s->production[k]))) {
/*									if(ptr_s->production[k]=='\0') {
										followFinding(grammar[i]->variables);
											
										l = 0; 
										while(follow[l].var != grammar[i]->variables) {
											l++;
										}
										strcat(follow[index].follows,follow[l].follows);	
									}
									else {
										
*/										l = 0; 
										while(first[l].var != ptr_s->production[k]) {
											l++;
										}
										strcat(follow[index].follows,first[l].firsts);	
									}
//								}
								else {

									l = 0; 
									while(first[l].var != ptr_s->production[k]) {
										l++;
									}
									strcat(follow[index].follows,first[l].firsts);
									break;
								}	
								
							}
							if(ptr_s->production[k]=='\0') {
								followFinding(grammar[i]->variables);
								l = 0; 
								while(follow[l].var != grammar[i]->variables) {
									l++;
								}
								strcat(follow[index].follows,follow[l].follows);
								break;	
							}
						}	
					}	
				}
				ptr_s = ptr_s->next;
			}
			i++;
		}		
	}
}


/*
void followFinding(char ch)
{
  int i = 0,k = 0, j = 0;
  int l=0;
  int index = 0;
  char temp[2];
  char *str =NULL;

  struct RHS_productions * ptr_s = NULL;
 
  if(strlen(toFindFollowList)==0)
     return;
  if(removeFollowList(ch) != -1) {
    i = 0; 
    while(grammar[i]!=NULL){
      ptr_s = grammar[i]->produces;
      while(ptr_s!=NULL) {
	for(j=0; j<strlen(ptr_s->production); j++) {
	  if(ptr_s->production[j] == ch) { 
	    k = j+1;
	    for(k = j+1;k<strlen(ptr_s->production); k++) {
	      if(isVariable(ptr_s->production[k])) {
		str = giveFirstList(ptr_s->production[k]);
		puts(str);
		strcat(follow[index].follows,str);
		if(containEpsilon(follow[index].follows)) {
		  removeEpsilon(follow[index].follows);
		  followFinding(ptr_s->production[k+1]);
		  l=0;
		  while(follow[l].var!=ptr_s->production[k+1])
		    l++;
		  strcat(follow[index].follows,first[l].firsts);
		  
		}
		else
		  break;
	      }
	      if(isTerminal(ptr_s->production[k])) {
	      temp[0] = ptr_s->production[k];
	      temp[1] = '\0';
	      strcat(follow[index].follows,temp);
	      }
	    } 
	  }
	}
	ptr_s = ptr_s -> next;
      }
      i++;
    }
  }
}

*/

/*
char * followFinding(char  ch){
  int i = 0;
  int j;
  int index = 0;
  int k = 0;
  char temp[2];
  struct RHS_productions * ptr_s = NULL;

  if(strlen(toFindFollowList)==0)
    return '\0';

  while(grammar[i]->variables!=ch) {
    i++;
  }
  removeFollowList(ch);
  
    ptr_s = grammar[i]->produces;
    while(ptr_s != NULL) {
      for(j=0; j < strlen(ptr_s->production); j++) {
       	if(isVariable(ptr_s->production[j])) {
	  follow[index].var = ptr_s->production[j];
	  if(isVariable(ptr_s->production[j+1])) {
	    k = 0;
	    while(first[k].var != ptr_s->production[j+1])
	      k++;
	    strcat(follow[index].follows,first[k].firsts);
	    if(containEpsilon(first[k].firsts)) {
	      //	      strcat(follow[index].follows,followFinding(ptr_s->production[j+2]));
	    }
	    printf("\n%c      %s",follow[index].var,follow[index].follows);
	    //     	    if(containEpsilon(follow[index].follows)) {
	      //	      removeEpsilon(follow[index].follows);
	    //      continue;
	    //    }
       	  }
	  if(isTerminal(ptr_s->production[j+1])) {
	    temp[0] = ptr_s->production[j+1];
	    temp[1] = '\0';
	    strcat(follow[index].follows,temp);
	  }
	}
	  index++;
      }
      ptr_s = ptr_s -> next;
    }
}
*/
