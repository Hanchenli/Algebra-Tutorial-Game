#include "main.h"

//ע:֮�����±�Ҫ��AmountOfCubes+1,��Ϊ�˷�����CubeNumberֱ�ӷ������顣
//��Ȼÿ�η���,��Ҫ��CubeNumber��1���Ƕ�Ӧ����,�Բ��������Ǽ��ͻ��±�Խ�硣
//���ڰ����鳤�������1,�Ϳ���ֱ�Ӻ��޷��յ�ʹ��"CubeNumber"��Ԫ���ˡ�
//�������ڿճ���һ��0��Ԫ��,����û�������,ע�ⲻҪʹ������
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