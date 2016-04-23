#include <stdio.h>
#include "my_link.h"

int main()
{
	node *cc;
	cc=create();
	display(cc);
	while(1)
	{
		char s[256];
		scanf("%s",s);
		if (strcmp(s,"!")!=0)
			insert(cc,s);

		else break;
	}

	display(cc);
	nfree(cc); 
	return 0;
}