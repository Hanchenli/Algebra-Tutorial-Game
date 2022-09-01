#ifndef _READRULES_H_
#define _READRULES_H_

struct CubeRule
{
	char name[20];
	char IsCube,SurfacesAllTheSame;
};
extern struct CubeRule *CubeRules[AmountOfCubes+1];

extern void ReadAllRules(void);

#endif //_READRULES_H_