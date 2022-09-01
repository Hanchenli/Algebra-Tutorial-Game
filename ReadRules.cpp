#include "main.h"

//注:之所以下标要用AmountOfCubes+1,是为了方便用CubeNumber直接访问数组。
//不然每次访问,都要把CubeNumber减1才是对应内容,稍不留神忘记减就会下标越界。
//现在把数组长度特意加1,就可以直接毫无风险地使用"CubeNumber"号元素了。
//不过现在空出来一个0号元素,它是没有意义的,注意不要使用它。
struct CubeRule *CubeRules[AmountOfCubes+1];

void ReadAllRules(void)
{
	char AppName[] = "000";
	for(CubeID CubeNumber = 0;CubeNumber <= AmountOfCubes;CubeNumber++)
	{
		AppName[0] = '0'+CubeNumber/100;
		AppName[1] = '0'+(CubeNumber/10)%10;
		AppName[2] = '0'+CubeNumber%10;
		CubeRules[CubeNumber] = new struct CubeRule;
		::GetPrivateProfileString(AppName,"name","Unknown",CubeRules[CubeNumber]->name,20,"./CubeRules.ini"); 
		CubeRules[CubeNumber]->IsCube = ::GetPrivateProfileInt(AppName,"IsCube",0,"./CubeRules.ini");
		CubeRules[CubeNumber]->SurfacesAllTheSame = ::GetPrivateProfileInt(AppName,"SurfacesAllTheSame",1,"./CubeRules.ini");
	}

	return;
}