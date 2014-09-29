#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>

void getCurrDir(char **currentDirectory);

int main(){

	struct pastCommand{
		int number ;
		char command[1000]; 
	};
	struct pastCommand history[1000]; //billions and billions of stars
	int histCount = -1;

	int envSet;
	envSet = setenv("MYHOME","/bin:.",0);
	if (envSet != 0){ printf("MYHOME not set"); }

	char * home = getenv( "MYHOME" );
  if ( home == NULL )
  {
  	fprintf( stderr, "$MYHOME is not set!\n" );
  	return EXIT_FAILURE;
  }

	char *currentDirectory = "\nHeres/ya/fuckin/path";
	currentDirectory = NULL; 
	getCurrDir(&currentDirectory); //Need to call free() on this later
	//printf("hasnt errored yet");
	char str[1000];
	char secondStr[1000];
	char thirdStr[1000];
	char *splitStr;
	FILE *fp = stdin;

	int safety = 1000;
	int InfRun = 1; // 1
	while (InfRun && safety > 0){  //InfLoop
		safety--;  //protects from infinate loops in children
		fprintf(stdout, "%s$ ",currentDirectory);  //print Cur Dir
		if (fgets(str, 1000, fp) != NULL){  //read in command
			//printf("Always?");
			strncpy(secondStr, str, 1000);

			splitStr = strtok(str," "); //Spit incomeing command
			if (splitStr != NULL && strcmp(splitStr,"\n") != 0){ //save history
				//printf("Saving command");
				histCount++; //increment
				if (histCount == 1000) { histCount = 0; }//reset
				history[histCount].number = histCount; //add com to hist
				strncpy(	history[histCount].command , secondStr, 1000);
			}
			if (splitStr != NULL && (strcmp(splitStr,"exit\n") == 0 || strcmp(splitStr,"quit\n")== 0)){ //exit
				printf("bye\n\n");
				InfRun = 0;
				break;
			} 
			

			int dontSplit = 0;
			while (splitStr != NULL){ //parsing loop
				//printf(">>>%s\n",splitStr);
				///all commands lead from here
				
				if (splitStr[0] == '!'){ //bang command
					//printf("BANG");
					if (strlen(splitStr) > 1){ //more than just a !
						if (splitStr[1] == '!'){//repeat last command -!!-
							//printf("Hist Com > %s\n",history[histCount-1].command);
							strncpy(str, history[histCount-1].command,1000);//-1 because last command is !!
							//printf("after strncpy %s\n", str);
							//also set current command to last command
							strncpy(history[histCount].command, history[histCount-1].command, 1000);
							//printf("after strncpy %s",
							splitStr = strtok(str," ");
							dontSplit = 1;
						}
						else {
							int allNum = 1; //true
							int x; //start at 1 becasue of !
							for (x = 1; x < strlen(splitStr); x++){
								if (isalpha(splitStr[x])){
									allNum = 0;
									break;
								}
							}
							if (allNum && strlen(splitStr) <= 5 && strlen(splitStr) > 2){ //not too many numbers // >2 added to avoid ! counting as !0
								//not sure why ^ is 5
								//find number, find command at number, run command
								int num = atoi(strtok(splitStr, "!")); //returns 0 if empty
								printf("Number is >> %i",num);
								strncpy(str, history[num].command,1000);
								splitStr = strtok(str," ");
								printf("splt > %s\n",splitStr);
								dontSplit = 1;
							} 
							else { // !+letters  Search for command
								int same = 0;
								int y;
								for (x = 999; x > -1; x--){
									for (y=0; y < strlen(splitStr)-2; y++){
										//printf("splitstr len %i\n",(int)strlen(splitStr));
										//printf("hist command %s\n",history[x].command);
										//printf("splitStr     %s\n",splitStr);
										same = 1;
										if (history[x].command[y] != splitStr[y+1]){
											//printf("not Same");
											same = 0;
											break;
										}
									} // v not working
									if (same){ //Prefix matched, set splitStr
										//printf("SplitStr > %s\n", splitStr);
										printf("%i: %s",history[x].number,history[x].command);
										strncpy(str, history[x].command, 1000);
										splitStr = strtok(str, " ");
										//printf("spltStr %s\n",splitStr);
										dontSplit = 1;
										break;
									}
								}
								if (!same){
									strncpy(thirdStr, secondStr, 1000); //throw data into third buffer
									char *tempCharPtr; //temp pointer
									tempCharPtr = strtok(thirdStr, " !\n"); //cut ' ' and !
									printf("ERROR: no command with '%s' prefix in history\n", tempCharPtr); //print error
									splitStr = NULL; //this kills the inner while loop that reads the parts of the command
								}
							}
						}
					}
				}
				if (splitStr != NULL && strcmp(splitStr,"history\n") == 0){ //exit
					//print history
					int z;//,c = histCount;
					//while (history[z].number != -1){
					for (z=0;z<histCount;z++){
						printf("%i:%s",history[z].number,history[z].command);
					}
				}
				//need to search path for command, and run it;
				//pid stuff too
				if (splitStr != NULL && strcmp(splitStr, "fork\n") == 0){
					pid_t childPID;
					printf("current pid is %i\n", getpid());
					childPID = fork(); 	
					if (childPID == 0) {
						printf("I'm the child\n"); 
						printf("My pid is %i\n", getpid());
						InfRun = 0;
						execlp("/bin/ls", "ls", "-l", NULL);
					}
					else {
						printf("I'm the parent\n my pid is %i\n", getpid());
						int status;
						pid_t child_pid; 
						child_pid	= wait(&status);
						//some error thing
						printf("Parent: Child %d terminated...", (int)child_pid);
						if ( WIFSIGNALED(status)){
							printf("Abnormal\n");
						} 
						else if (WIFEXITED (status)){
							int rc = WEXITSTATUS(status);
							printf("successfully with exit status %d\n", rc);
						}
					}
					//need to make a list of children PID's and merc them when the parent dies, unless otherwise
				}

				




				//printf("Before Strtok%s", splitStr);
				if (!dontSplit){
					splitStr = strtok(NULL," ");
				}
				dontSplit = 0;
				//printf("\nafter STRTOK%s", splitStr);
			}
		}
	}
	if (fp != NULL){fclose(fp); fp = NULL;}
	free(currentDirectory); //not *currentDirectory becassue of reasons
	
  return EXIT_SUCCESS;
}


int hasPipes(char *inputStr){
	char *split;
	split = strtok(inputStr, " ");
	while (split != NULL){
		if (strcmp(split,"|") == 0){
			return 1;
		}
		split = strtok(NULL, " ");
	}
	return 0;
}
//this is not done
int hasRedirect(char *inputStr){ // < = 1, > = 2, >> = 3
	char *split;
	split = strtok(inputStr, " ");
	while (split != NULL){
		if (strcmp(split,"<") == 0){
			return 1;
		}
		else if (strcmp(split,">") == 0){
			return 2;
		}
		else if (strcmp(split,">>") == 0){
			return 3;
		}
		split = strtok(NULL, " ");
	}
	return 0;
}

int backgroundExec(char *inputStr){
	int len = (int)strlen(inputStr);
	if (len > 0){
		if (input[len-1] == '&'){
			return 1;
		}
	}
	return 0;
}

void getCurrDir(char **currentDirectory){
	
	free(*currentDirectory); //open up the pointer, and remove chance for constant mem leak
	*currentDirectory = NULL;
	int notLargeEnough = 1;
	int currDirSize = PATH_MAX+1;
	char *currDir = malloc(1000);
	if (currDir == NULL) {fprintf(stderr, "CurrDir is NULL");}
	//char *currDirErr;
	//currDirErr = NULL;
	while (notLargeEnough){
		//getcwd(currDir, (size_t)currDirSize);
		//fprintf(stderr,"about to segfault");
		//currDirErr = getcwd(currDir, 1000);
		getcwd(currDir, 1000);
		//fprintf(stderr, "past segfault");
		if (currDir != NULL){
			//return currDir;
			//printf("<><><><><>%s",currDir);
			*currentDirectory = currDir;
			notLargeEnough = 0;
			//printf("CURRENTDIRECTORY%s", *currentDirectory);
		}
		//printf("%s",currDir);
		//printf("%i\n",errno);
		//printf("%i",ERANGE);
		if (errno == ERANGE){
			currDirSize += 100;
		}
		if (currDirSize > 100000){
			fprintf(stderr, "Something is going wrong inside getCurrDir()");
			notLargeEnough = 0;
			//return EXIT_FAILURE;
		}	
	}
}
