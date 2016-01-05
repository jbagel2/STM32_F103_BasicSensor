/*
 * HelperFunctions.h
 *
 *  Created on: Dec 20, 2015
 *      Author: Jacob
 */

#ifndef HELPERFUNCTIONS_H_
#define HELPERFUNCTIONS_H_

void SetArray_Size(char buffer[], uint16_t size)
{
	memset(buffer, '1', size);
}

void ClearArray_Size(char buffer[], uint16_t size)
{
	memset(buffer, '\0', size);
}

uint16_t IndexOf(char *arrayToSearch[], uint16_t arraySize,char *stringToFind)
{
	uint16_t correctedSize = arraySize / sizeof(int); //NEED TO EVALUATE IF sizeof(int) evaluates as expected
	uint16_t i = 0;
	for(i; i < correctedSize ;i++)
	{
		if(strstr(arrayToSearch[i],stringToFind))
		{
			return i;
		}
	}
	return NULL;
}

#endif /* HELPERFUNCTIONS_H_ */
