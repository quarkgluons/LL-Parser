
#include"ll1.h"

int main(int argc, char **argv)
{
	int i;
	char  filename[30];

	printf("hi fellas");
	if(argc<=1) {
		printf("Please Enter the file name also\n");
		return -1;
	}
		printf("Am i entering main");	
		strcpy(filename,argv[1]);
		readfile(filename);
		
		/*
		 * Initializing the First Set array of
		 * structures
		 */
		initFirstSet();


		
 		for(i=0; first[i].var!='@';i++) {
			if(first[i].epsilon == 1)
				strcat(first[i].firsts,"#");
		}
		i = 0;	
		while(grammar[i]!=NULL) {
			V[i] = grammar[i]->variables;
			i++;
		}
		V[i] = '\0';
		
		
		i=0;
		while(strlen(V)!=0) {
			firstFinding(V[i]);
			i++;
		}


		/*
		 * finishing touches to firstSet
		 */
		deleteDup();

/* 		for(i=0; first[i].var!='@';i++) {
			if(first[i].epsilon == 1)
				strcat(first[i].firsts,"#");
		}
*/
		

		/*
		 * printing the variables and its firsts
		 */
		i=0;
		while(first[i].var!='@') {
			printf("\nVariable %c ",first[i].var);
			printf("   %s",first[i].firsts);
			i++;
		}
		/*
		 * FINDING FOLLOW
		 */
		i=0;
		while(grammar[i]!=NULL) {
		  toFindFollowList[i] = grammar[i]->variables;
		  i++;
		}
	      
		//		puts("hi");
		toFindFollowList[i] = '\0';

		initFollowSet();
		
		follow[0].follows[0] = '$';
		follow[0].follows[1] = '\0';
		//		puts("\nhello");
		i = 0;
       		while(strlen(toFindFollowList)!=0) {
		  followFinding(toFindFollowList[i]);
       		  i++;
       		}

		i=0;
		while(follow[i].var!='@') {
		  removeEpsilon(follow[i].follows);
		  i++;
		}
		/*
		 *Printing the variables and its follows
		 */
		/*		i = 0;
		while(follow[i].var!='@') {
		  printf("\nVAr %c   %s\n",follow[i].var,follow[i].follows);
		  i++;
		}

		*/
		deleteDupFollow();
		
		i=0;
		while(follow[i].var!='@') {
		  printf("\nVAR %c    %s",follow[i].var,follow[i].follows);
		  i++;
		}
		
		//		puts(giveFirstList('S'));
	return 0;
}

