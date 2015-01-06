#include <string>
#include <vector>
#include "des.h"

using std::vector;
//partition函数划分的段数
#define SPANNUMBER 10



class NumberEncrypt
{
public:
	NumberEncrypt();
	~NumberEncrypt();
	void init();
	//对输入的ID加密
	std::string encode(const std::string &str);
	//连接数据库
	void connectDB();
	void partition();
	//对输入的ID进行ident函数映射
	void ident();
	//把由id得到的mark与密文etuple回存进数据库
	void dataSave();
	//输入ID，得到其对应的mark
	int getOneMark(int inputid);
	//获取vector<int> mark
	vector<int> getMark();
	//获取vector<int> id
	vector<int> getID();
	/*根据mark获取数据库中的数据,choice=1为小于等于，choice=2为大于等于,
	outputway=1 输出64位密文 outputway=2输出
	根据mark查询的解密后明文，outputway=3 输出根据输入id来查询的明文*/
	void getData(int mark, int choice, int outputway, int inputid);

// 	//获取数据库中比输入mark大的密文
// 	void getLessDataByMark( int mark);
// 	//获取比输入mark大的明文
// 	void getLessPlatxtByMark(int mark);
// 	//获取数据库中比输入mark小的数据
// 	void getLargeDataByMark( int mark);
// 	//获取数据库中在输入的2个mark中间的数据
// 	void getMidDataByMark( int minmark,int maxmark);

	void sqlGetByMark(char sqlstr[], int choice, int outputway, int inputid);
	//加密
	void desEncode(char* plaintext);
	//解密
	char* desDecode(bool cryptedMsg[64]);
	//从txt中读取文件并加密存到mysql中
	void readFileAndSave();
	//转换id成密文并存入数据库
	void tranferedSave(int m, char* id);

private:
	//输入的id
	static int count;
	int part[SPANNUMBER];
	//Id中的最大、最小值
	int maxNumber;
	int	minNumber;
	//明文长度
	int numPlaintextLen;

	char realDecipher[9];

	vector<int> number;
	vector<int> mark;
	vector<int> id;

	DES des;
};