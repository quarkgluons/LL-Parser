#include"ll1.h"

int isEpsilon(char ch)
{
	if(ch == '#')
		return True;
	return False;
}

int isTerminal(char ch)
{
	if (ch >= 'a' && ch<='z')
		return True;
	return False;
}

void deleteDup()
{
	int i = 0;
	int j = 0, k = 0, flag = 0, in = 0; 
	char temp[NUM_TERM];
	while(first[i].var!='@') {
		in = 0;
		for(j=0;j<strlen(first[i].firsts);j++) { 
			k = j+1;
			flag = 0;
		       	while(k<strlen(first[i].firsts)) {
				if(first[i].firsts[j] == first[i].firsts[k]) {
					flag = 1;
				}
				k++;
			}
			if(flag == 0) {
				temp[in] = first[i].firsts[j];
				in++;
			}
			
		}	
		temp[in] = '\0';
		strcpy(first[i].firsts,temp);
		i++;
	}
}

void initFirstSet()
{
	int i = 0;

	struct RHS_productions *ptr_s = NULL;
	for(i=0; i<NUM_PROD; i++) {
		first[i].var = '@';
		first[i].epsilon = 0;
		first[i].firsts[0] = '\0';
	}
	i=0;
	while(grammar[i]!=NULL) {
		first[i].var = grammar[i]->variables;
		i++;
	}
	/*
	 * finding if any of the variables produce Epsilon,
	 * if so setting the epsilon flag in first_set struct
	 */
	i = 0;
	while(grammar[i]!=NULL) {
		ptr_s = grammar[i]->produces;
		while(ptr_s!=NULL) {
			if(strcmp("#",ptr_s->production)==0) {
			  //				printf("\nproductions containing epsion %c\n",grammar[i]->variables);
				first[i].epsilon = 1;
				break;
			}
			ptr_s = ptr_s->next;
		}
		i++;
	}

}

int removeFromV(char ch)
{
	char temp[NUM_PROD];
	int i=0;
	int ret = -1;
	int j = 0;
	while(i<strlen(V)) {
		if(V[i] == ch) {
			ret = i;
			i++;
			continue;
		}
		temp[j] = V[i];
		j++; i++;

	}
	temp[j] = '\0';
	strcpy(V,temp);
	return ret;

}

void firstFinding(char var)
{
	int index = 0;
	int i = 0, j;
	int num = 0;
	char tempo[NUM_TERM];
	char temp[2];
	struct RHS_productions * ptr_s = NULL;

	if(strlen(V)==0)
		return;

	if(removeFromV(var)!=-1) {
		i=0;
		while(grammar[i]!=NULL) {
			if (grammar[i]->variables == var) {
				index = i;
				break;
			}
			i++;
		}
		
		num = strlen(first[index].firsts);
		ptr_s = grammar[index]->produces;
		while(ptr_s!=NULL) { 
			for(i=0; i<strlen(ptr_s->production); i++) {

//				if(isEpsilon(ptr_s->production[i])) {
					
//				}
				if(isTerminal(ptr_s->production[i])) {
				  temp[0] = ptr_s->production[i];
				  //				  first[index].firsts[num] = ptr_s->production[i];
				  //					num++;
	
					//					first[index].firsts[num] = '\0';
//					printf("\n\nindex  %d  num  %d\n\n  ",index,num);
				  temp[1] = '\0';
				  strcat(first[index].firsts,temp);
					break;	
				}
				if(isVariable(ptr_s->production[i])) {
					firstFinding(ptr_s->production[i]);
					j=0;
					while(first[j].var!='@') {
						if(first[j].var==ptr_s->production[i]) {
							break;
						}
						j++;
					}
					strcpy(tempo,first[j].firsts);
					if(i != strlen(ptr_s->production)-1) {
					removeEpsilon(tempo);
					}
					//					if(index!=j) {
						strcat(first[index].firsts,tempo);
						//					}
					if(first[j].epsilon==1) {
					  /*					  firstFinding(ptr_s->production[i+1]);
					  j = 0;
					  while(first[j].var!='@') {
					    if(first[j].var==ptr_s->production[i]) {
					      break;
					    }
					    j++;
					  }
					  strcat(first[index].firsts,first[j].firsts);
					  */	continue;
					}
					else
						break;
				}

			}

			ptr_s = ptr_s->next;
		}
	}//end if
//	else {

//	}

	
}
/*
int main()
{
	int i = 0;
	while(i<NUM_PROD) {
		grammar[i]=NULL;
		i++;
	}

	readfile("productions.txt");
	initFirstSet();
	i=0;
	while(i<NUM_PROD) {
		printf("\nvariable%c",first[i].var);
//		printf("\nFirsts %s",first[i].firsts);
		printf("\nepsilon :  %d",first[i].epsilon);

		i++;
	}
	for(i=0; grammar[i]!=NULL; i++) {
		V[i]=grammar[i]->variables;
	}
	V[i] = '\0';
	i=0;
	while(strlen(V)!=0) {
		puts(V);
		firstFinding(V[i]);
		i++;
	}
	i = 0;
	while(first[i].var!='$') {
		printf("\nVariable %c ",first[i].var);
		printf("   %s",first[i].firsts);

		i++;
	}
}
*/
