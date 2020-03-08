#include "ChainStack.h"



int main()
{
	ptrToStack s = Create();;
	
	if (Push(s, 0x1222))
	{
		printf("%x\n", PopStack(s));
	}
	return 0;
}
    

