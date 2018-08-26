#ifndef FLAGS_H
#define FLAGS_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct flag_obj flag_t;

flag_t *newFlag(size_t size);
bool delFlag(flag_t **pFlag);

bool setFlag(flag_t *pFlag, size_t index, bool val);
bool checkFlag(flag_t *pFlag, size_t index);
size_t getFlagLength(flag_t *pFlag);

#endif
 