#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h> //open() and something else
#include <sys/types.h> //for open() apparently
#include <sys/fcntl.h> //open()

void getCurrDir(char **currentDirectory);
int backgroundExec(char *inputStr);
int hasRedirectFile(char *inputStr);
int hasRedirectRight(char *inputStr);
int hasRedirectLeft(char *inputStr);
int hasPipe(char *inputStr);

//yet to fully implment >>, <, >, |, <- but these are close. line 200ish 
//argument handleing
// cd
// lstat also seems to think that everything is a ligitimate command, not enough time to fix that, 
//probably just a stupid mistake.

//time put in, almost breaching 20 hours, possibly beyond that by now

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
				

	//need to split each part of the command into char** array
	//scan each char* pointer to see if it is a <, >, >>, or |
	//break down the code into order of operation
	//
	//if ending & parent will not wait :Done
	//see if command is valid, fork :Done
	//add in arguments
	//see if given input txt
	//see if given output
	//see if given output appending
	//see if given pipe
	//set up pipe
	//fork
	//look for output, no input
				
				//pid stuff too
				
				//mostly test code
				
				if (splitStr != NULL ){
					char commandPtr[1000];
					int isPipe = 0;
					//int fileDes[2];
					strncpy(commandPtr, splitStr, 1000);
					pid_t childPID;
					printf("current pid is %i\n", getpid());
					childPID = fork(); 	
					if (childPID == 0) {
						printf("I'm the child\n"); 
						printf("My pid is %i\n", getpid());
						InfRun = 0; //bug prevention
						//need to check the avalibility of the command in question
						char * daPath = getenv("MYHOME");
						char*pathStr = strtok(daPath, ":");
						char pathTemp[1000];
						struct stat st;
						int firstTime = 1;
						int retVal;
						while (retVal != 0 && pathStr != NULL){
							if (firstTime != 1){ //stop strtok from running untill after first pass
								pathStr = strtok(NULL, ":");
							}
							strncpy(pathTemp, pathStr, 1000); //copy possible path
							strcat(pathTemp, commandPtr);//append command to back of possible path

							//need to look through possibilities in the path
							retVal = lstat(pathTemp, &st); //check if command is avalible
							firstTime = 0; 
						}
						if (retVal == 0){//comand found, look for extra commands (in out pipe)
							//pathStr is maintianed, so the correct path to call is still in it
							//look for redirections and crap
							//find next command
							//printf("\n\n\n command found!!!!"); //now look to see if anything comes after
							//printf("split Str before call to strtok: %s", splitStr);//this doesnt work and is no doubt breaking something else
							strncpy(splitStr, secondStr, 1000);
							splitStr = strtok(splitStr," ");
							if (strcmp(splitStr,commandPtr) == 0  && !isPipe){ //first string and command match, as expected
								printf("something is wrong, or this is a pipe");
							}
							else if (isPipe){
								while (strcmp(splitStr,"|") == 0){
									splitStr = strtok(NULL, " ");
								}
								splitStr = strtok(NULL, " "); //splitstr is now on the pipe command
								//need to see if pipe is ligitimate now fffffffuuuuuuuuuuuu
							}
							while (splitStr != NULL){
								splitStr = strtok(NULL, " ");
								if (strcmp(splitStr, "<") == 0){
									//open input fd
									//fileDes[0] = open(/*need path in here*/O_RDONLY);
								}
								else if (strcmp(splitStr, ">") == 0){
									//open output fd
								}
								else if (strcmp(splitStr, ">>") == 0){
									//open output fd at bottom of file
								}	
								else if (strcmp(splitStr, "|") == 0){
									//open pipe, fork pipe, tell fork that it is pipe
									isPipe = 1;
								}
								else {//must be an argument
									//argArr //the most pirate variable ever
								}
							}
							
							//printf("split Str after call to strtok: %s", splitStr);

						}
						else {
							printf("%s: command not found\n",commandPtr);//command then :command not found
						}
						//execlp("/bin/ls", "ls", "-l", NULL);
					}
					else {
						printf("I'm the parent\n my pid is %i\n", getpid());
						int status;
						//pid_t child_pid; 
						if (backgroundExec(secondStr) == 0){ //if it is not supposed to run in the background
							//child_pid	= 
							wait(&status);
							//some error thing
							/*
							printf("Parent: Child %d terminated...", (int)child_pid);
							if ( WIFSIGNALED(status)){
								printf("Abnormal\n");
							} 
							else if (WIFEXITED (status)){
								int rc = WEXITSTATUS(status);
								printf("successfully with exit status %d\n", rc);
							} */
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


int hasPipe(char *inputStr){
	int x;
	for (x = strlen(inputStr); x >= 0; x--){
		if (inputStr[x] == '|'){
			return 1;
		}
	}
	return 0;
}

int hasRedirectLeft(char *inputStr){ 
	int x;
	for (x = strlen(inputStr); x >=0; x--){
		if (inputStr[x] == '<'){
			return 1;
		}
	}
	return 0;
}
int hasRedirectRight(char *inputStr){ 
	int x;
	for (x = strlen(inputStr); x >=0; x--){
		if (inputStr[x+1] == ' ' && inputStr[x] == '>' && inputStr[x-1] == ' '){
			return 1;
		}
	}
	return 0;
}
int hasRedirectFile(char *inputStr){ 
	int x;
	for (x = strlen(inputStr); x > 0; x--){
		if (inputStr[x] == '>' && inputStr[x-1] == '>'){ //note: nothing is stopping a command ->
			return 1; // from having >> on the begining or end
		}
	}
	return 0;
}
int backgroundExec(char *inputStr){
	int len = (int)strlen(inputStr);
	if (len > 0){
		if (inputStr[len-1] == '&'){
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
