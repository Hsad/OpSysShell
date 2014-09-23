#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>


//void getCurrDir(char* currentDirectory);

int main(){
	
	int envSet;
	envSet = setenv("MYHOME","/bin:.",0);
	if (envSet != 0){ printf("MYHOME not set"); }

	char * home = getenv( "MYHOME" );
  if ( home == NULL )
  {
  	fprintf( stderr, "$MYHOME is not set!\n" );
  	return EXIT_FAILURE;
  }

	char *currentDirectory = "Heres ya fuckin path"; 
	//getCurrDir(currentDirectory); //Need to call free() on this later
	printf("hasnt errored yet");
	char str[1000];
	char *splitStr;
	FILE *fp = stdin;	

	int InfRun = 1; // 1
	while (InfRun){
		fprintf(stdout, "%s",currentDirectory);
		if (fgets(str, 1000, fp) != NULL){
			splitStr = strtok(str," ");
			if (splitStr != NULL){
				printf("%s",splitStr);
			}
			if (strcmp(str,"exit\0") == 1){
				InfRun = 0;
				break;
			}
			printf("%s",str);
		}
		
	}
	if (fp != NULL){fclose(fp); fp = NULL;}
	
  return EXIT_SUCCESS;
}
/*
void getCurrDir(char *currentDirectory){
	currentDirectory = NULL;
	free(currentDirectory); //open up the pointer, and remove chance for constant mem leak
	int notLargeEnough = 1;
	int currDirSize = MAX_PATH+1;
	char *currDir = currentDirectory;
	char *currDirErr;
	currDirErr = NULL;
	while (notLargeEnough){
		//getcwd(currDir, (size_t)currDirSize);
		fprintf(stderr,"about to segfault");
		currDir = get_current_dir_name();
		fprintf(stderr, "past segfault");
		if (currDirr != NULL){
			//return currDir;
			currentDirectory = currDir;
			notLargeEnough = 0;
		}
		printf("%s",currDir);
		printf("%i\n",errno);
		printf("%i",ERANGE);
		if (errno == ERANGE){
			currDirSize += 100;
		}
		if (currDirSize > 100000){
			fprintf(stderr, "Something is going wrong inside getCurrDir()");
			notLargeEnough = 0;
			//return EXIT_FAILURE;
		}	
	}
}*/
