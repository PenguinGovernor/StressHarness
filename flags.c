#include "flags.h"

#include <stdlib.h>
#include <stdio.h>

struct flag_obj
{
  size_t length;
  bool *flags;
};

flag_t *newFlag(size_t size)
{
  // alloc the struct
  flag_t *pFlag = malloc(sizeof(flag_t));
  if (pFlag == NULL)
  {
    perror("Failed to allocate space for flag struct.");
    return pFlag;
  }

  // alloc the flags
  pFlag->flags = calloc(sizeof(bool), size);
  if (pFlag->flags == NULL)
  {
    perror("Failed to allocate space for flag.");
    free(pFlag);
    pFlag = NULL;
    return pFlag;
  }

  // set the length
  pFlag->length = size;
  return pFlag;
}

bool delFlag(flag_t **pFlag)
{
  if (pFlag == NULL || *pFlag == NULL)
  {
    perror("Passed null ref to del flag.");
    return false;
  }
  free((*pFlag)->flags);
  (*pFlag)->flags = NULL;
  free(*pFlag);
  *pFlag = NULL;
  return true;
}

bool setFlag(flag_t *pFlag, size_t index, bool val)
{

  if (pFlag == NULL)
  {
    perror("Passed null ref to set flag.");
    return false;
  }

  if (index >= pFlag->length)
  {
    perror("Invalid index in setflag");
    return false;
  }

  pFlag->flags[index] = val;
  return true;
}

bool checkFlag(flag_t *pFlag, size_t index)
{
  if (pFlag == NULL)
  {
    perror("Passed null ref to check flag.");
    return false;
  }

  if (index >= pFlag->length)
  {
    perror("Invalid index in check flag");
    return false;
  }

  return pFlag->flags[index];
}

size_t getFlagLength(flag_t *pFlag)
{
  if (pFlag == NULL)
  {
    perror("Passed null ref to getFlagLength.");
    return false;
  }

  return pFlag->length;
} 
