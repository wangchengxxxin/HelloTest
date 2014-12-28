#ifndef _DES_H
#define _DES_H

class DES  
{  
private:  
	//public:  
	//����  
	char msg[8];  
	bool bmsg[64];  
	//��Կ  
	char key[8];  
	bool bkey[64];  
	//16������Կ  
	bool subkey[16][48];  
	//l0 r0�м����  
	bool rmsgi[32],lmsgi[32];//��i��  
	bool rmsgi1[32],lmsgi1[32];//��i+1��  

	char realDecipher[9];
	//���ĵĳ���
	int plaintextLen;
public:
	//����  
	bool bcryptedmsg[64];  
	char cryptedmsg[8];  
	//���ܵĽ��  
	bool bdecipher[64];  
	char decipher[8];  

private:  
	//��̬����  

	//�����������ڳ�ʼ��  
	//��ʼֵ��ip  
	const static int ip[64];  
	//����Կ  
	//�û�ѡ��1  
	const static int c0[28];  
	const static int d0[28];  
	//ѭ�����Ʊ�  
	const static int keyoff[16];  
	//�û�ѡ��2  
	const static int di[48];  
	//���ܺ���  
	//e����  
	const static int e_operate[48];  
	//sbox  
	const static int sbox[8][64];  
	//�û�����p  
	const static int p_operate[32];  
	//���ʼ�û�ip  
	const static int back_ip[64];  
	//λ����  
	const static char bitmask[8];  
public:  
	//�������ĺ���Կ  
	//_lengthҪС�ڻ����8  
	void SetMsg(char* _msg,int _length);  
	void SetKey();  
	//��������Կ  
	void ProduceSubKey();  
	//�ܵĵļ�������  
	void Crypte();  
	//����  
	void Decipher();  
	//�������  
	void OutPutCryptedMsg();  
	//������ת���ַ�  
	void Bit2Char(bool* _barray,char* _carray);//length=64  
	//������ܺ������  
	void OutPutDecipher();  
	//���64λ����
	bool* getCryptedMsg();
	//��ý��ܺ������
	char* getDecipher();
	//�������ĵõ����ܺ������
	char* getDecipherByCryped(bool bcryptedmsg[64]);
	//�õ����ĵĳ���
	int getPlaintextLen();
private:  
	//�ַ�ת�ɶ����ƣ������浽64λbool������  
	void Char2Bit(char* _carray,bool* _barray,int length);  
	////������ת���ַ�  
	//void Bit2Char(bool* _barray,char* _carray);//length=64  
	//��ʼ�û�  
	void InitSwap(bool in[64]);  
	//��ʼ���û�  
	void InitReSwap(bool out[64]);  
	//ѭ������  
	void SubKeyOff(bool* _subkey,int _off);  
	//e�����������  
	void EOperation(bool a[32],bool b[48]);  
	//ģ2���  
	//��ͬΪ0 ��ͬΪ1  
	void Mode2Add(bool a[],bool b[],bool c[],int length);  
	//sbox  
	void DealSBox(bool in[48],bool out[32]);  
	void _DealSBox(bool in[6],bool out[4],int box);  
	//p opraration  
	void POperation(bool temp[32],bool result[32]);  
	//���ܺ���  
	void CrypteFunction(bool in[32],int isubkey,bool out[32]);  

	//����֮�丳ֵ  
	void CopyArray(bool array1[],bool array2[],int size);  

}; 
#endif _DES_H