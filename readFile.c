#include"ll1.h"



/*
 * Any capital letter would be taken as a variable and as
 * a variable and as such will return true on finding
 * a Variable else a False
 */

int isVariable(int ch)
{
	if(ch >='A' && ch<='Z')
		return True;
	return False;
}


int isKnownVariable(int ch) 
{
	int i = 0;
	while(i< NUM_PROD && grammar[i] != NULL) {
		if(grammar[i]->variables == ch) {
			return i+1;
		}
		else {
			i = i + 1; 
		}
	}	
	return False;
}

void readRHS(struct RHS_productions ** node, FILE * fp)
{
	struct RHS_productions * temp_ptr = NULL;
	char temp_s[LENGTH_RHS];
	int i = 0;
	int ch;
	
	while(fgetc(fp)!='>')
		;
	while((ch = fgetc(fp))!='\n') {
		if(ch == ' ')
		       continue;
		temp_s[i] = ch;
		i++;

	}
	temp_s[i] = '\0';

	temp_ptr = malloc(sizeof(struct RHS_productions));
	*node = temp_ptr;

	strcpy(temp_ptr->production,temp_s);
	temp_ptr->next = NULL;

}

void readfile(char *filename)
{
	FILE *fp = NULL;
	int ch;
	int index;
	struct RHS_productions * ptr_s = NULL;
 	int i;
	fp = fopen(filename,"r");
	while((ch = fgetc(fp))!=EOF) {
		if(isVariable(ch)) {
			if((index = isKnownVariable(ch))) {
				index = index - 1;

				ptr_s = grammar[index]->produces;
				while(ptr_s->next != NULL)
					ptr_s = ptr_s->next;
			
				readRHS(&ptr_s->next,fp);
			}
			else {
				index = 0;
				while(grammar[index] != NULL)
					index++;
			
				grammar[index] = malloc(sizeof(struct productions));
				grammar[index]->variables = ch;
				putchar(grammar[index]->variables);
						
				grammar[index]->produces = NULL;
				readRHS(&(grammar[index]->produces),fp);

			}

				

		}
		else {
			printf("\nWrong Form Of Production\n");
		}	
	}
	printf("\n\n");
	for(i=0; grammar[i]!=NULL; i++) {
		ptr_s = grammar[i]->produces;
		printf("\n%c ->", grammar[i]->variables);
		while(ptr_s != NULL) {
			printf("| %s \n",ptr_s->production);
			ptr_s = ptr_s->next;
		}
	}

}
/*
int main()
{
	int i;
	for(i=0; i<NUM_PROD;i++) {
		grammar[i]=NULL;
	}
	readfile("productions.txt");
	return 0;
}

*/
