#include "NumberEncrypt.h"

 #include <windows.h>
#include <iostream>
#include "winsock.h" 
#include "mysql.h" 
#include <fstream>

using namespace std;
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "libmysql.lib")

//必备的一个数据结构
MYSQL mydata;


NumberEncrypt::NumberEncrypt()
{
	init();
}

NumberEncrypt::~NumberEncrypt()
{
	mysql_close(&mydata);
	mysql_server_end();

	number.~vector<int>();
	mark.~vector<int>();

}

void NumberEncrypt::init()
{
	maxNumber = minNumber = 0;
	//连接数据库
	connectDB();
	//读入数据并将序号和密文存入数据库
	readFileAndSave();

	//对数据进行partion
 	partition();
// 	//对每一个ID对应一个mark
 	ident();
// 	//存入mark
	dataSave();
}

void NumberEncrypt::search()
{
}

void NumberEncrypt::connectDB()
{
	//初始化数据库
	if (0 == mysql_library_init(0, NULL, NULL)) {
		cout << "mysql_library_init() succeed" << endl;
	} else {
		cout << "mysql_library_init() failed" << endl;
	}

#ifdef STEPBYSTEP
	system("pause");
#endif

	//初始化数据结构
	if (NULL != mysql_init(&mydata)) {
		cout << "mysql_init() succeed" << endl;
	} else {
		cout << "mysql_init() failed" << endl;
	}

#ifdef STEPBYSTEP
	system("pause");
#endif

	//在连接数据库之前，设置额外的连接选项
	//可以设置的选项很多，这里设置字符集，否则无法处理中文
	if (0 == mysql_options(&mydata, MYSQL_SET_CHARSET_NAME, "gbk")) {
		cout << "mysql_options() succeed" << endl;
	} else {
		cout << "mysql_options() failed" << endl;
	}

#ifdef STEPBYSTEP
	system("pause");
#endif

	//连接数据库
	if (NULL
		!= mysql_real_connect(&mydata, "localhost", "root", "", "wordstable",
		3306, NULL, 0))
		//这里的地址，用户名，密码，端口可以根据自己本地的情况更改
	{
		cout << "mysql_real_connect() succeed" << endl;
	} else {
		cout << "mysql_real_connect() failed" << endl;
	}


	//记得要在析构函数里面关掉mysql
	//mysql_free_result(result);
	//mysql_close(&mydata);
	//mysql_server_end();
}



void NumberEncrypt::ident()
{
	int length = number.size();
	for(vector<int>::size_type  i = 0; i<length; i++)
	{
		for (int j = 0; j < SPANNUMBER-1; j++)
		{
			if (number[i]<part[0])
			{
				mark.push_back(0*3+5);
				break;
			}
			if (number[i] >= part[j] && number[i] < part[j+1]){
				mark.push_back(j*3+5);
				break;
			}
			if (number[i]>part[9])
			{
				mark.push_back(9*3+5);
			}
		}
	}
	for (int i=0; i<length; i++)
	{
		cout<<"marks are "<<mark[i]<<"\t";
	}
	cout<<endl;
	
}

void NumberEncrypt::partition()
{
// 	string sqlstr = "SELECT id FROM words";
// 	MYSQL_RES *result = NULL;
// 	if(0 == mysql_query(&mydata, sqlstr.c_str())) 
// 	{
// 		cout<<"mysql_query() select data succeed"<<endl;
// 		result = mysql_store_result(&mydata);
// 		//取得并打印行数
// 		const int rowcont = mysql_num_rows(result);
// 		cout<<"row cont: "<<rowcont<<endl;
// 		
// 		//打印各行
// 		MYSQL_ROW row = NULL;
// 		row = mysql_fetch_row(result);
// 		int rowi;
// 		NumberEncrypt::maxNumber = minNumber = atoi(row[0]);
// 		int idCount = 0;
// 		while (NULL != row) {
// 			rowi = atoi(row[0]);
// 			number.push_back(rowi);
// 			if(rowi > maxNumber)
// 				maxNumber = rowi;
// 			if(rowi < minNumber)
// 				minNumber = rowi;
// 			cout << row[0] << "\t\t";
// 
// 			cout <<endl;
// 			row = mysql_fetch_row(result);
// 		}
// 		cout<<"maxid: "<<maxNumber<<"\t"<<"minid: "<<minNumber<<endl;
// 
// 		//对id进行划分
// 		int span = maxNumber - minNumber;
// 		for(int i = 0; i < SPANNUMBER; i++)
// 		{
// 			part[i] = double(span / SPANNUMBER) * i + minNumber;
// 			cout<<part[i]<<"\t"<<endl;
// 		}
// 	}
// 	else
// 	{
// 		cout<<"mysql_query() select data failed"<<endl;
// 		mysql_close(&mydata);
// 	}
	 		//对id进行划分
	 int span = maxNumber - minNumber;
	 for(int i = 0; i < SPANNUMBER; i++)
	 {
	 	part[i] = double(span / SPANNUMBER) * i + minNumber;
	 	cout<<"part i"<<part[i]<<endl;
	 }
}

void NumberEncrypt::dataSave()
{
	for(int i=0; i<number.size(); i++)
	{
// 		char idi[8];
// 		itoa(b, idi, 10);
// 		desEncode(idi);
// 		char  bcrypted[65];
// 		for (int i=0; i<64; i++)
// 		{
// 			bcrypted[i] = des.bcryptedmsg[i] + 48;
// 		}
// 		bcrypted[64] = '\0';
		char sqlstr[120];
		sprintf(sqlstr,"UPDATE words SET mark= '%d' WHERE id = '%d';", mark[i], i);
		if (0 == mysql_query(&mydata, sqlstr)) {
		} else {
			cout << "mysql_query() datasave  failed" << endl;
			mysql_close(&mydata);
		}
	}
}

int NumberEncrypt::getOneMark(int inputid)
{
	int mark;
	for (int j = 0; j < SPANNUMBER-1; j++)
	{
		if (inputid < part[0]){
			return 0*3+5;
		}
		if (inputid >= part[j] && inputid < part[j+1]){
		{
			mark = j*3+5;
			return mark;
		}		
	}
	}
	mark = 9*3+5;
	return mark;
}

vector<int> NumberEncrypt::getMark()
{
	return this->mark;
}

vector<int> NumberEncrypt::getID()
{
	return this->number;
}

void NumberEncrypt::getDataByMark(int mark, int choice, int outputway, int inputid)
{
	char sqlstr[50];
	if (choice == 1)
	{
		sprintf(sqlstr, "SELECT * FROM words WHERE mark <= '%d';", mark);
	}
	else if(choice == 2)
	{
		sprintf(sqlstr, "SELECT * FROM words WHERE mark >= '%d';", mark);
	}
	sqlGetByMark(sqlstr, choice, outputway, inputid);
}

// void NumberEncrypt::getLessDataByMark( int mark)
// {
// 	char sqlstr[50];
// 	sprintf(sqlstr, "SELECT * FROM words WHERE mark <= '%d';", mark);
// 	sqlGetByMark(sqlstr, 1);
// }
// 
// void NumberEncrypt::getLessPlatxtByMark(int mark)
// {
// 	char sqlstr[50];
// 	sprintf(sqlstr, "SELECT * FROM words WHERE mark <= '%d';", mark);
// 	sqlGetByMark(sqlstr, 2);
// }
// 
// void NumberEncrypt::getLargeDataByMark( int mark )
// {
// 	char sqlstr[50];
// 	sprintf(sqlstr, "SELECT * FROM words WHERE mark >= '%d';", mark);
// 	sqlGetByMark(sqlstr);
// }

void NumberEncrypt::sqlGetByMark(char sqlstr[], int choice, int outputway, int inputid)
{
	MYSQL_RES *result = NULL;
	if (0 == mysql_query(&mydata, sqlstr)) {
		std::cout << "mysql_query() select data succeed" << endl;

		//一次性取得数据集
		result = mysql_store_result(&mydata);
		//取得并打印行数
		int rowcount = mysql_num_rows(result);
		std::cout << "row count: " << rowcount << endl;

		//取得并打印各字段的名称
		unsigned int fieldcount = mysql_num_fields(result);
		MYSQL_FIELD *field = NULL;
		for (unsigned int i = 0; i < fieldcount; i++) {
			field = mysql_fetch_field_direct(result, i);
			std::cout << field->name << "\t\t\t";
		}
		std::cout << endl;

		//打印各行
		MYSQL_ROW row = NULL;
		row = mysql_fetch_row(result);
		while (NULL != row) {
			for (int i = 0 ; i < fieldcount; i++) {
				if(outputway == 1)
				{
					if (i==1)
					{
						bool bo[64];
						for (int i=0; i<64; i++)
						{
							bo[i] = (row[1])[i]-48;
						}
						std::cout<<row[i]<<"\t\t\t";
						//cout<<desDecode(bo)<<"\t\t";
					}
					else 
					std::cout << row[i] << "\t\t\t";
				}
				if (outputway == 2)
				{
					if (i==1)
					{
						bool bo[64];
						for (int i=0; i<64; i++)
						{
							bo[i] = (row[1])[i]-48;
						}
						//std::cout<<row[i]<<"\t\t";
						std::cout<<desDecode(bo)<<"\t\t\t";
					}
					else 
						std::cout << row[i] << "\t\t\t";
				}
				if (outputway == 3)
				{
					if (i==1)
					{
						bool bo[64];
						for (int i=0; i<64; i++)
						{
							bo[i] = (row[1])[i]-48;
						}
						char* temp = desDecode(bo);
						int inttemp = atoi(temp);
						//std::cout<<row[i]<<"\t\t";
						//std::cout<<desDecode(bo)<<"\t\t";
						if (choice == 1)
						{
							if (inttemp <= inputid)
							{
								std::cout<<inttemp<<"\t\t\t";
							}
							else
							{
								std::cout<<"mark符合，id不符"<<"\t\t";
							}
						}
						else if(choice == 2)
						{
							if (inttemp >= inputid)
							{
								std::cout<<inttemp<<"\t\t\t";
							}
							else
							{
								std::cout<<"mark符合，id 不符"<<"\t\t";
							}
						}
					}
					else 
						std::cout << row[i] << "\t\t";
				}
			}
			std::cout << endl;
			row = mysql_fetch_row(result);
		}

	} else {
		std::cout << "mysql_query() select data failed" << endl;
		mysql_close(&mydata);
	}
}


void NumberEncrypt::desEncode(char* plaintext)
{
	numPlaintextLen = sizeof(plaintext);
	des.SetMsg(plaintext, 9);
	des.SetKey();
	//加密
	des.Crypte();
}

char* NumberEncrypt::desDecode( bool cryptedMsg[64] )
{
	char* temp =  des.getDecipherByCryped(cryptedMsg);
	memset(realDecipher, 0, 9);
	bool equalToZero = true;
	int zeroCount = 0;
	for (int i=0; i<numPlaintextLen; i++)
	{
		if (equalToZero && temp[i] == '0')
		{
			zeroCount++;
		}
		if (temp[i] != '0')
		{
			equalToZero = false;
			realDecipher[i-zeroCount] = temp[i];
		}
	}
	realDecipher[numPlaintextLen] = '\0';
	return realDecipher;
}

void NumberEncrypt::readFileAndSave()
{
	maxNumber = 0;
	minNumber = 99999999;
	int intData;
	ifstream file;
	char *fileName = "data.txt";
	char dataBuf[9] = {"\0"};
	file.open(fileName);
	int i=0;

	if (file)
	{
		while (!file.eof())
		{
			file.getline(dataBuf, 8);
			intData = atoi(dataBuf);
			if (intData > maxNumber)
			{
				maxNumber = intData;
			}
			if(intData < minNumber)
			{
				minNumber = intData;
			}		
			number.push_back(atoi(dataBuf));
			//id.push_back(i++);
			tranferedSave(i++, dataBuf);
			cout<<dataBuf<<endl;
		}
	}
	else
	{
		cout<<"read file error"<<endl;
	}
	file.close();
}

void NumberEncrypt::tranferedSave(int m, char* number )
{
	desEncode(number);
	char  bcrypted[65];
	for (int i=0; i<64; i++)
	{
		bcrypted[i] = des.bcryptedmsg[i] + 48;
	}
	bcrypted[64] = '\0';
	char sqlstr[120];
	sprintf(sqlstr, "INSERT INTO words(id, etuple) VALUES('%d','%s');", m, bcrypted);
	if (0 == mysql_query(&mydata, sqlstr)) {
		cout << "mysql_query() tranfered insert data succeed" << endl;
	} else {
		cout << "数据已经录入，请不要重复录入" << endl;
		//mysql_close(&mydata);
	}
}
