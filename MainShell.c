#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void getCurrDir(char);

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

	char *currentDirectory = NULL; 
	//getCurrDir(& currentDirectory); //Need to call free() on this later
	
	int InfRun = 0; // 1
	while (InfRun){
		fprintf(stdout, currentDirectory);
		
	}
	
  return EXIT_SUCCESS;
}

void getCurrDir(char currentDirectory){
	//free(currentDirectory); //open up the pointer, and remove chance for constant mem leak
	//int notLargeEnough = 1;
	//int currDirSize = 100;
	//char *currDir = currentDirectory;
	//char *currDirErr = NULL;
	//while (notLargeEnough){
		//currDirErr = getcwd(currDir, (size_t)currDirSize) ;
		//if (currDirErr != NULL){
			////return currDir;
			//currentDirectory = currDir;
			//notLargeEnough = 0;
		//}
		//else if (errno == ERANGE){
			//currDirSize += 100;
		//}
		//if (currDirSize > 100000){
			//fprintf(stderr, "Something is going wrong inside getCurrDir()");
			//return EXIT_FAILURE;
		//}
}
