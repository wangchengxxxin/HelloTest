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
	cout<<"��������ֵ�ķ�Χ��ѯ(��ʽΪ��40  50 �� 40 # �� # 50 --#��ʾ����)��";
	cin>>min>>max;
	//����� id<50  ��ʽ

	if(min.compare("#") == 0)
	{
		int intmax = atoi(max.c_str());
		int maxmark = numEnc->getOneMark(intmax);
		cout<<"maxmark is "<<maxmark<<endl;

		//������ݿ��е�markֵ
		for (int i =0; i<numEnc->getMark().size(); i++)
		{
			if ((numEnc->getMark())[i] <= maxmark)
			{
				cout<<"��ѯ������ID��mark�ֱ��ǣ�"<<numEnc->getID()[i]<<"\t"<<numEnc->getMark()[i]<<endl;
			}
		}
		numEnc->getLessDataByMark(maxmark);
	}
	//�����  40<id  ��ʽ
	else if(max.compare("#") == 0)
	{
		int intmin = atoi(min.c_str());
		int minmark = numEnc->getOneMark(intmin);
		cout<<"minmark is "<<minmark<<endl;
		numEnc->getLargeDataByMark(minmark);
	}

	//�����  40<id<50  ��ʽ
	else
	{

	}
	//bool a[64]= {0,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0};
// 	bool a[64] = {0,0,1,1,1,0,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0};
// 	cout<<"�뿴�� ��Ҫ�����ˣ�"<<numEnc->desDecode(a);
	#endif
	//numEnc->readFileAndSave();
	system("pause");
}