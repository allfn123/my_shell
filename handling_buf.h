#include <string.h>
//function handling_buf


int handling_buf(char *before,char segment[][BUF_SIZE])		//This function is used to separate the buf from myfifo into several independent segments.
{
	char *tmp;
	int num_of_segment=0;					//num_of_segment is used to memorize the numbers of independent segments.
	strcpy(segment[0],strtok(before," "));
	while(tmp=strtok(NULL," "))				//segment is array of string that memorizes the containment of each segment.
	{
		num_of_segment++;
		strcpy(segment[num_of_segment],tmp);
	}
	
	if (num_of_segment==0 && strcmp(segment[0],"\n")==0)
		return num_of_segment+1;
	if (strcmp(segment[num_of_segment],"\n")==0)
		num_of_segment--;
	else
		segment[num_of_segment][strlen(segment[num_of_segment])-1]='\0';	

	return num_of_segment+1;
}

