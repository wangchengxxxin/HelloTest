#include <string>
#include <vector>
#include "des.h"

using std::vector;
//partition�������ֵĶ���
#define SPANNUMBER 10



class NumberEncrypt
{
public:
	NumberEncrypt();
	~NumberEncrypt();
	void init();
	//�������ID����
	std::string encode(const std::string &str);
	//�������ݿ�
	void connectDB();
	void search();
	void partition();
	//�������ID����ident����ӳ��
	void ident();
	//����id�õ���mark������etuple�ش�����ݿ�
	void dataSave();
	//����ID���õ����Ӧ��mark
	int getOneMark(int inputid);
	//��ȡvector<int> mark
	vector<int> getMark();
	//��ȡvector<int> id
	vector<int> getID();
	//��ȡ���ݿ��б�����mark�������
	void getLessDataByMark( int mark);
	//��ȡ���ݿ��б�����markС������
	void getLargeDataByMark( int mark);
	//��ȡ���ݿ����������2��mark�м������
	void getMidDataByMark( int minmark,int maxmark);
	//SQL��� ��ȡ�������������ݲ����
	void sqlGet(char sqlstr[]);
	//����
	void desEncode(char* plaintext);
	//����
	char* desDecode(bool cryptedMsg[64]);
	//��txt�ж�ȡ�ļ������ܴ浽mysql��
	void readFileAndSave();
	//ת��id�����Ĳ��������ݿ�
	void tranferedSave(int m, char* id);

private:
	//�����id
	static int count;
	int part[SPANNUMBER];
	//Id�е������Сֵ
	int maxNumber;
	int	minNumber;
	//���ĳ���
	int numPlaintextLen;

	char realDecipher[9];

	vector<int> number;
	vector<int> mark;
	vector<int> id;

	DES des;
};