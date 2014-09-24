#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

//void getCurrDir(char* currentDirectory);

int main(){

	struct pastCommand{
		int number;
		char command[1000]; 
	};
	struct pastCommand history[1000]; //billions and billions of stars
	int histCount = 0;

	int envSet;
	envSet = setenv("MYHOME","/bin:.",0);
	if (envSet != 0){ printf("MYHOME not set"); }

	char * home = getenv( "MYHOME" );
  if ( home == NULL )
  {
  	fprintf( stderr, "$MYHOME is not set!\n" );
  	return EXIT_FAILURE;
  }

	char *currentDirectory = "Heres/ya/fuckin/path"; 
	//getCurrDir(currentDirectory); //Need to call free() on this later
	//printf("hasnt errored yet");
	char str[1000]; 
	char *splitStr;
	FILE *fp = stdin;

	int InfRun = 1; // 1
	while (InfRun){  //InfLoop
		fprintf(stdout, "%s$ ",currentDirectory);  //print Cur Dir
		if (fgets(str, 1000, fp) != NULL){  //read in command
			//printf("Always?");
			
			splitStr = strtok(str," "); //Spit incomeing command
			if (splitStr != NULL && strcmp(splitStr,"\n") != 0){ //save history
				printf("Saving command");
				histCount++; //increment
				if (histCount == 1000) { histCount = 0; }//reset
				history[histCount].number = histCount; //add com to hist
				strncpy(	history[histCount].command , str, 1000);
			}
			if (splitStr != NULL && strcmp(splitStr,"exit\n") == 0){ //exit
				printf(">%s",splitStr);
				InfRun = 0;
				break;
			}
			while (splitStr != NULL){ //parsing loop
				printf(">>>%s\n",splitStr);
				///all commands lead from here
				if (splitStr[0] == '!'){ //bang command
					printf("BANG");
					if (strlen(splitStr) > 1){ //more than just a !
						if (splitStr[1] == '!'){//repeat last command
							printf("Hist Com > %s\n",history[histCount-1].command);
							strncpy(str, history[histCount-1].command,1000);//-1 because last command is !!
							printf("after strncpy %s\n", str);
							//also set current command to last command
							strncpy(history[histCount].command, history[histCount-1].command, 1000);
							//printf("after strncpy %s",
							splitStr = strtok(str," ");
						}
						else {
							int allNum = 1; //true
							int x; //start at 1 becasue of !
							for (x = 1; x < strlen(splitStr); x++){
								if (isAlpha(splitStr[x])){
									
								}
							}
						}
					}
				}






				//printf("Before Strtok%s", splitStr);
				splitStr = strtok(NULL," ");
				//printf("\nafter STRTOK%s", splitStr);
			}
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
