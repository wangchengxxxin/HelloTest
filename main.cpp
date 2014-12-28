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
	cout<<"请输入数值的范围查询(格式为：40  50 或 40 # 或 # 50 --#表示无穷)：";
	cin>>min>>max;
	//如果是 id<50  形式

	if(min.compare("#") == 0)
	{
		int intmax = atoi(max.c_str());
		int maxmark = numEnc->getOneMark(intmax);
		cout<<"maxmark is "<<maxmark<<endl;

		//检测数据库中的mark值
		for (int i =0; i<numEnc->getMark().size(); i++)
		{
			if ((numEnc->getMark())[i] <= maxmark)
			{
				cout<<"查询出来的ID和mark分别是："<<numEnc->getID()[i]<<"\t"<<numEnc->getMark()[i]<<endl;
			}
		}
		numEnc->getLessDataByMark(maxmark);
	}
	//如果是  40<id  形式
	else if(max.compare("#") == 0)
	{
		int intmin = atoi(min.c_str());
		int minmark = numEnc->getOneMark(intmin);
		cout<<"minmark is "<<minmark<<endl;
		numEnc->getLargeDataByMark(minmark);
	}

	//如果是  40<id<50  形式
	else
	{

	}
	//bool a[64]= {0,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0};
// 	bool a[64] = {0,0,1,1,1,0,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0};
// 	cout<<"请看好 我要解密了："<<numEnc->desDecode(a);
	#endif
	//numEnc->readFileAndSave();
	system("pause");
}