#include<string>  
#include<iostream>  
#include"des.h"  
using namespace std;  
//��̬����  
const int DES::ip[64]={  
	58,50,42,34,26,18,10,2,  
	60,52,44,36,28,20,12,4,  
	62,54,46,38,30,22,14,6,  
	64,56,48,40,32,24,16,8,  
	57,49,41,33,25,17,9,1,  
	59,51,43,35,27,19,11,3,  
	61,53,45,37,29,21,13,5,  
	63,55,47,39,31,23,15,7  
};  
const int DES::c0[28]={  
	57,49,41,33,25,17,9,  
	1,58,50,42,34,26,18,  
	10,2,59,51,43,35,27,  
	19,11,3,60,52,44,36  
};  
const int DES::d0[28]={  
	63,55,47,39,31,23,15,  
	7,62,54,46,38,30,22,  
	14,6,61,53,45,37,29,  
	21,13,5,28,20,12,4  
};  
const int DES::keyoff[16]={  
	1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1  
};  
const int DES::di[48]={  
	14,17,11,24,1,5,  
	3,28,15,6,21,10,  
	23,19,12,4,26,8,  
	16,7,27,20,13,2,  
	41,52,31,37,47,55,  
	30,40,51,45,33,48,  
	44,49,39,56,34,53,  
	46,42,50,36,29,32  
};  
const int DES::e_operate[48]={  
	32,1,2,3,4,5,  
	4,5,6,7,8,9,  
	8,9,10,11,12,13,  
	12,13,14,15,16,17,  
	16,17,18,19,20,21,  
	20,21,22,23,24,25,  
	24,25,26,27,28,29,  
	28,29,30,31,32,1  
};  
const int DES::sbox[8][64]={  
	{    
		14, 4, 13, 1, 1, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,    
			0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,    
			4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,    
			15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13    
	},    

	{    
		15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,    
			3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,    
			0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,    
			13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9    
		},    

		{    
			10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,    
				13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,     
				13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,    
				1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12    
		},    

		{    
			7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,     
				13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,    
				10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,    
				3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14    
			},    

			{    
				2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,    
					14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,    
					4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,    
					11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3    
			},    

			{    
				12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,    
					10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,    
					9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,    
					4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13    
				},    

				{    
					4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,    
						13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,    
						1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,    
						6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12    
				},    

				{    
					13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 13, 14, 5, 0, 12, 7,    
						1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,    
						7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,    
						2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11    
					}    
};   
const int DES::p_operate[32]={  
	16,7,20,21,  
	29,12,28,17,  
	1,15,23,26,  
	5,18,31,10,  
	2,8,24,14,  
	32,27,3,9,  
	19,13,30,6,  
	22,11,4,25  
};  
const int DES::back_ip[64]={  
	40,8,48,16,56,24,64,32,  
	39,7,47,15,55,23,63,31,  
	38,6,46,14,54,22,62,30,  
	37,5,45,13,53,21,61,29,  
	36,4,44,12,52,20,60,28,  
	35,3,43,11,51,19,59,27,  
	34,2,42,10,50,18,58,26,  
	33,1,41,9,49,17,57,25  
};  
const char DES::bitmask[8]={ 128,64,32,16,8,4,2,1};  

//ʵ�ֺ���  

//  
//�������� ,����8λǰ�油0
//  
void DES::SetMsg(char* _msg,int _length)  
{  
	int count = 0;
	plaintextLen = 0;
	if (_length>9)  
	{  
		return;  
	}  
	for (int i = 0; i < _length; i++)  
	{  
		if (_msg[i] != NULL)
		{
			count++;
		}
	}  
	for (int i=0; i < _length; i++)
	{
		if (i < _length - 1 - count)
		{
			msg[i] = '0';
		}
		else
		{
			msg[i] = _msg[i - (_length-1-count)];
		}

	}
	//ת���ɶ�����  
	Char2Bit(msg,bmsg,8);  
};  
//  
//������Կ  
//  
void DES::SetKey()  
{  
// 	if (_length>8)  
// 	{  
// 		return;  
// 	}  
// 	for (int i = 0; i < _length; i++)  
// 	{  
// 		key[i]=_key[i];  
// 	}  
	strcpy(key, "12345678");
	//ת�ɶ�����  
	Char2Bit(key,bkey,8);  
};  
//  
//�ַ�ת�ɶ�����  
//ok   length�ַ�����ĳ���  
void DES::Char2Bit(char* _carray,bool* _barray,int length)  
{  
	//int index=0;  
	for (int i = 0; i <length; i++)  
	{  
		for (int j = 0; j < 8; j++)  
		{  
			_barray[i*8+7-j]=(_carray[i]>>j)&1;  
		}  
	}  
};  
//  
//������ת���ַ�  
//  
void DES::Bit2Char(bool* _barray,char* _carray)  
{  
	char temp;  
	for (int i = 0; i < 8; i++)  
	{  
		//��ѧ����ת���ַ�  
		temp=0;  
		for (int j = 0; j < 8; j++)  
		{  
			if (_barray[i*8+j]==1)  
			{  
				temp|=bitmask[j];  
			}  
		}  
		//cout<<temp;  
		_carray[i]=temp;  
	}  
};  
//  
//��ʼ�û�����  
//ok  
void DES::InitSwap(bool in[64])  
{  
	//����  
	for (int i = 0; i < 32; i++)  
	{  
		lmsgi[i]=in[ip[i]-1];  
		rmsgi[i]=in[ip[i+32]-1];  
	}  
};  
//  
//��ʼ���û�����  
//ok  
void DES::InitReSwap(bool out[64])  
{  
	//��ϳ�64����  
	bool temp[64];  
	for (int i = 0; i < 32; i++)  
	{  
		temp[i]=rmsgi[i];  
		temp[32+i]=lmsgi[i];  
	}  
	//������ip����  
	for (int i = 0; i < 64; i++)  
	{  
		out[i]=temp[back_ip[i]-1];  
	}  
};  
//  
//ѭ������  
//ok  
void DES::SubKeyOff(bool* _subkey,int _off)  
{  
	//��û�и��õİ취???  
	bool temp;  
	for (int i = 0; i < _off; i++)  
	{  
		temp=_subkey[0];  
		for (int i = 0; i < 27; i++)  
		{  
			_subkey[i]=_subkey[i+1];  
		}  
		_subkey[27]=temp;  
	}  
};  
//  
//��������Կ  
//ok  
void DES::ProduceSubKey()  
{  
	//�û�ѡ��1  
	bool ctemp[28],dtemp[28];  
	for (int i = 0; i < 28; i++)  
	{  
		ctemp[i]=bkey[c0[i]-1];  
		dtemp[i]=bkey[d0[i]-1];  
	}  
	bool keytemp[56];  
	for (int i = 0; i < 16; i++)  
	{  
		//ѭ������  
		SubKeyOff(ctemp,keyoff[i]);  
		SubKeyOff(dtemp,keyoff[i]);  
		//�ϲ���һ��56����  
		for (int j = 0; j <28; j++)  
		{  
			keytemp[j]=ctemp[j];  
			keytemp[28+j]=dtemp[j];  
		}  
		//�û�ѡ��2  
		for (int j = 0; j < 48; j++)  
		{  
			subkey[i][j]=keytemp[di[j]-1];  
		}  
	}  
};  
//  
//e����  
//ok  
void DES::EOperation(bool a[32],bool b[48])  
{  
	for (int i = 0; i < 48; i++)  
	{  
		b[i]=a[e_operate[i]-1];  
	}  
};  
//  
//ģ2���  
//ok  
void DES::Mode2Add(bool a[],bool b[],bool c[],int length)  
{  
	for (int i = 0; i < length; i++)  
	{  
		if (a[i]==b[i])  
		{  
			c[i]=0;  
		}else  
		{  
			c[i]=1;  
		}  
	}  
};  
//  
//sbox����  
//ok  
void DES::DealSBox(bool in[48],bool out[32])  
{  
	bool _in[6],_out[4];  
	//8������  
	for (int i = 0; i < 8; i++)  
	{  
		//��ȡ����  
		for (int j = 0; j < 6; j++)  
		{  
			_in[j]=in[i*6+j];  
		}  
		//ѹ��  
		_DealSBox(_in,_out,i);  
		//�Ž�out����  
		for (int jj = 0; jj < 4; jj++)  
		{  
			out[i*4+jj]=_out[jj];  
		}  
	}  
};  
//  
//_dealsbox  
//ok  
void DES::_DealSBox(bool in[6],bool out[4],int box)  
{  
	int raw,col;  
	raw=in[0]*2+in[5];//ת����ʮ���� ��  
	col=in[1]*2*2*2+in[2]*2*2+in[3]*2+in[4];//��  
	int result=sbox[box][raw*16+col];  
	//ת�ɶ�����  
	for (int i = 3; i >=0; i--)  
	{  
		out[i]=(result>>(3-i))&1;  
	}  
};  
//  
//p����  
//ok  
void DES::POperation(bool temp[32],bool result[32])  
{  
	for (int i = 0; i < 32; i++)  
	{  
		result[i]=temp[p_operate[i]-1];  
	}  
};  
//  
//���ܺ���  
//isubkey�������Ǹ�����Կ����   ok  
void DES::CrypteFunction(bool in[32],int isubkey,bool out[32])  
{  
	//e ����  
	bool temp1[48];  
	EOperation(in,temp1);  
	bool temp2[48];  
	Mode2Add(temp1,(bool *)subkey[isubkey],temp2,48);//ok  
	//����ѹ��  
	bool temp3[48];  
	DealSBox(temp2,temp3);  
	//�û�����p  
	POperation(temp3,out);  

};  
//  
// des��������  
//ok  
void DES::Crypte()  
{  
	//ֱ����bmsg����  
	//ֱ����cryptedmsg�������  
	bool temp1[32],temp2[32];  
	//��ʼ�û�ip  
	InitSwap(bmsg);  
	//16�ֵ���  
	for (int i = 0; i < 16; i++)  
	{  
		if (i%2==0)  
		{  
			//L1=R0  
			CopyArray(rmsgi,lmsgi1,32);  
			//f(R0,k0)  
			CrypteFunction(rmsgi,i,temp1);  
			//L0+f(R0,k0)  
			Mode2Add(lmsgi,temp1,temp2,32);  
			//R1=L0+f(R0,k0)  
			CopyArray(temp2,rmsgi1,32);  
		}else  
		{  
			//L2=R1  
			CopyArray(rmsgi1,lmsgi,32);  
			//f(R1,k1)  
			CrypteFunction(rmsgi1,i,temp1);  
			//L1+f(R1,k1)  
			Mode2Add(lmsgi1,temp1,temp2,32);  
			//R2=L1+f(R1,k1)  
			CopyArray(temp2,rmsgi,32);  
		}  
	}  

	//���ʼ�û�ip  
	InitReSwap(bcryptedmsg);  
	//ת���ַ�  
	Bit2Char(bcryptedmsg,cryptedmsg);  
};  
//  
//���鸳ֵ  
//ok  
void DES::CopyArray(bool content[],bool empty[],int size)  
{  
	for (int i = 0; i < size; i++)  
	{  
		empty[i]=content[i];  
	}  
};  
//  
//����  
//ok  
void DES::Decipher()  
{  
	bool temp1[32],temp2[32];  
	//��ʼ�û�ip  
	InitSwap(bcryptedmsg);  
	//16�ֵ�������  

	for (int i = 0; i < 16; i++)  
	{  
		if (i%2==0)  
		{  
			//L1=R0  
			CopyArray(rmsgi,lmsgi1,32);  
			//f(R0,k0)  
			CrypteFunction(rmsgi,15-i,temp1);  
			//L0+f(R0,k0)  
			Mode2Add(lmsgi,temp1,temp2,32);  
			//R1=L0+f(R0,k0)  
			CopyArray(temp2,rmsgi1,32);  
		}else  
		{  
			//L2=R1  
			CopyArray(rmsgi1,lmsgi,32);  
			//f(R1,k1)  
			CrypteFunction(rmsgi1,15-i,temp1);  
			//L1+f(R1,k1)  
			Mode2Add(lmsgi1,temp1,temp2,32);  
			//R2=L1+f(R1,k1)  
			CopyArray(temp2,rmsgi,32);  
		}  
	}  
	//���ʼ�û�ip  
	InitReSwap(bdecipher);  
	//ת���ַ�  
	Bit2Char(bdecipher,decipher);  

};  
//  
//�������  
//  
void DES::OutPutCryptedMsg()  
{  
	//Bit2Char(bcryptedmsg,cryptedmsg);  
	cout<<endl<<"����:";  
	for (int i = 0; i < 8; i++)  
	{  
		cout<<cryptedmsg[i]<<' ';  
	}  
	cout<<endl;
	for (int i=0; i<64; i++)
	{
		cout<<bcryptedmsg[i];
	}
	cout<<endl;
};  
//  
//�����������  
//  
void DES::OutPutDecipher()  
{  
	//Bit2Char(bdecipher,decipher);  

	cout<<endl<<"����:";  
	for (int i = 0; i < plaintextLen; i++)  
	{  
		cout<<decipher[i]<<' ';  
	}  
	cout<<endl;  
};  

bool* DES::getCryptedMsg()
{
	return bcryptedmsg;
}

char* DES::getDecipher( )
{
	return decipher;
}

char* DES::getDecipherByCryped(bool bcryptedmsg[64] )
{
	bool temp1[32],temp2[32];  
	//��ʼ�û�ip  
	InitSwap(bcryptedmsg);  
	//16�ֵ�������  

	for (int i = 0; i < 16; i++)  
	{  
		if (i%2==0)  
		{  
			//L1=R0  
			CopyArray(rmsgi,lmsgi1,32);  
			//f(R0,k0)  
			CrypteFunction(rmsgi,15-i,temp1);  
			//L0+f(R0,k0)  
			Mode2Add(lmsgi,temp1,temp2,32);  
			//R1=L0+f(R0,k0)  
			CopyArray(temp2,rmsgi1,32);  
		}else  
		{  
			//L2=R1  
			CopyArray(rmsgi1,lmsgi,32);  
			//f(R1,k1)  
			CrypteFunction(rmsgi1,15-i,temp1);  
			//L1+f(R1,k1)  
			Mode2Add(lmsgi1,temp1,temp2,32);  
			//R2=L1+f(R1,k1)  
			CopyArray(temp2,rmsgi,32);  
		}  
	}  
	//���ʼ�û�ip  
	InitReSwap(bdecipher);  
	//ת���ַ�  
	Bit2Char(bdecipher,decipher); 
// 	memset(realDecipher, 0, 9);
// 	for (int i=0; i<plaintextLen; i++)
// 	{
// 		realDecipher[i] = decipher[i];
// 	}
// 	realDecipher[plaintextLen] = '\0';
// 	return realDecipher;
	return decipher;
}

int DES::getPlaintextLen()
{
	return plaintextLen;
}



// int main()  
// {  
// 	//�̲ĵĲ�������  
// 	char msg[8]={'0','1','2','3','4','5','6','7'};  
// 	char key[8]={'2','2','3','4','5','6','7','8'};  
// 	cout<<"���ģ�";  
// 	for (int i = 0; i < 8; i++)  
// 	{  
// 		cout<<msg[i]<<' ';  
// 	}  
// 	DES des;  
// 	//��������  
// 	des.SetMsg(msg,8);  
// 	//������Կ  
// 	des.SetKey(key,8);  
// 	//��������Կ  
// 	des.ProduceSubKey();  
// 	//����  
// 	des.Crypte();  
// 	//�������  
// 	des.OutPutCryptedMsg();  
// 	//����  
// 	des.Decipher();  
// 	//������ܺ������  
// 	des.OutPutDecipher();  
// 
// 	system("pause");  
// 	return 0;  
// }  