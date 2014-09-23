#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	
	//int InfRun = true;
	//while (InfRun){
		//printf()
	//}
	int envSet;
	envSet = setenv("MYHOME","/bin:.",0);
	if (envSet != 0){ printf("MYHOME not set"); }

	char * home = getenv( "MYHOME" );
  if ( home == NULL )
  {
  	fprintf( stderr, "$MYHOME is not set!\n" );
  	return EXIT_FAILURE;
  }
 
  printf( "$MYHOME is %s\n", home );
 
  char copy_of_home[100];  /* BIG assumption that len < 100 */
  strcpy( copy_of_home, home );
  printf( "$MYHOME copy is %s\n", copy_of_home );
	
  return EXIT_SUCCESS;
}
