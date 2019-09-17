#ifndef _UTIL_H_
#define _UTIL_H_

FILE* safeOpen(const char *fileName, const char *mode);
void shuffleArray(int *v, int n);
int mapValue(int x, int a, int b, int A, int B);
void freeArray(void **p);
void endProgram(char *message);

#endif // _UTIL_H_