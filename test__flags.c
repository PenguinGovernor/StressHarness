#include "flags.h"

#include <stdio.h>
#include <stdbool.h>

int main()
{
	flag_t *flag = newFlag(10);
	// int testsPassed = 0;
	bool falseTestFailed = false, trueTestFailed = false;

	for (size_t i = 0; i < getFlagLength(flag); i += 1)
	{
		if (checkFlag(flag, i) == true)
		{
			falseTestFailed = true;
		}
		setFlag(flag, i, true);
	}

	for (size_t i = 0; i < getFlagLength(flag); i += 1)
	{
		if (checkFlag(flag, i) == false)
		{
			falseTestFailed = true;
		}
	}

	if (falseTestFailed == false)
	{
		printf("Passed false test\n");
	}

	if (trueTestFailed == false)
	{
		printf("Passed true test\n");
	}

	if (getFlagLength(flag) == 10)
	{
		printf("Passed length test\n");
	}

	delFlag(&flag);

	return 0;
}
 
