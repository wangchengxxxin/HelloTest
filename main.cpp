#include <iostream>
#include "NumberEncrypt.h"
using namespace std;

#pragma comment(lib,"libmysql.lib")
#define  RUN
void main()
{
	NumberEncrypt* numEnc = new NumberEncrypt();
	string min, max;
#ifdef RUN
	cout<<"请输入数值的范围查询(格式为：或 40 # 或 # 50 --#表示无穷)：";
	cin>>min>>max;
	//如果是 id<50  形式

	if(min.compare("#") == 0)
	{
		int intmax = atoi(max.c_str());
		int maxmark = numEnc->getOneMark(intmax);
		cout<<"onemark is "<<maxmark<<endl;

		numEnc->getData(maxmark, 1, 1, intmax);
		system("pause");
		numEnc->getData(maxmark, 1, 2, intmax);
		system("pause");
		numEnc->getData(maxmark, 1, 3, intmax);
	}
	//如果是  40<id  形式
	else if(max.compare("#") == 0)
	{
		int intmin = atoi(min.c_str());
		int minmark = numEnc->getOneMark(intmin);
		cout<<"onemark is "<<minmark<<endl;
		numEnc->getData(minmark, 2, 1, intmin);
		system("pause");
		numEnc->getData(minmark, 2, 2, intmin);
		system("pause");
		numEnc->getData(minmark, 2, 3, intmin);
	}

	//如果是  40<id<50  形式
	else
	{

	}
	//bool a[64]= {0,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0};
// 	bool a[64] = {0,0,1,1,1,0,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0};
// 	cout<<"解密之后为："<<numEnc->desDecode(a);
	#endif
	//numEnc->readFileAndSave();
	system("pause");
}