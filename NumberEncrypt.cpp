#include "NumberEncrypt.h"

 #include <windows.h>
#include <iostream>
#include "winsock.h" 
#include "mysql.h" 
#include <fstream>

using namespace std;
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "libmysql.lib")

//�ر���һ�����ݽṹ
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
	//�������ݿ�
	connectDB();
	//�������ݲ�����ź����Ĵ������ݿ�
	readFileAndSave();

	//�����ݽ���partion
 	partition();
// 	//��ÿһ��ID��Ӧһ��mark
 	ident();
// 	//����mark
	dataSave();
}

void NumberEncrypt::search()
{
}

void NumberEncrypt::connectDB()
{
	//��ʼ�����ݿ�
	if (0 == mysql_library_init(0, NULL, NULL)) {
		cout << "mysql_library_init() succeed" << endl;
	} else {
		cout << "mysql_library_init() failed" << endl;
	}

#ifdef STEPBYSTEP
	system("pause");
#endif

	//��ʼ�����ݽṹ
	if (NULL != mysql_init(&mydata)) {
		cout << "mysql_init() succeed" << endl;
	} else {
		cout << "mysql_init() failed" << endl;
	}

#ifdef STEPBYSTEP
	system("pause");
#endif

	//���������ݿ�֮ǰ�����ö��������ѡ��
	//�������õ�ѡ��ܶ࣬���������ַ����������޷���������
	if (0 == mysql_options(&mydata, MYSQL_SET_CHARSET_NAME, "gbk")) {
		cout << "mysql_options() succeed" << endl;
	} else {
		cout << "mysql_options() failed" << endl;
	}

#ifdef STEPBYSTEP
	system("pause");
#endif

	//�������ݿ�
	if (NULL
		!= mysql_real_connect(&mydata, "localhost", "root", "", "wordstable",
		3306, NULL, 0))
		//����ĵ�ַ���û��������룬�˿ڿ��Ը����Լ����ص��������
	{
		cout << "mysql_real_connect() succeed" << endl;
	} else {
		cout << "mysql_real_connect() failed" << endl;
	}


	//�ǵ�Ҫ��������������ص�mysql
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
// 		//ȡ�ò���ӡ����
// 		const int rowcont = mysql_num_rows(result);
// 		cout<<"row cont: "<<rowcont<<endl;
// 		
// 		//��ӡ����
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
// 		//��id���л���
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
	 		//��id���л���
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

void NumberEncrypt::getLessDataByMark( int mark)
{
	char sqlstr[50];
	sprintf(sqlstr, "SELECT * FROM words WHERE mark <= '%d';", mark);
	sqlGet(sqlstr);
}

void NumberEncrypt::getLargeDataByMark( int mark )
{
	char sqlstr[50];
	sprintf(sqlstr, "SELECT * FROM words WHERE mark >= '%d';", mark);
	sqlGet(sqlstr);
}

void NumberEncrypt::sqlGet(char sqlstr[])
{
	MYSQL_RES *result = NULL;
	if (0 == mysql_query(&mydata, sqlstr)) {
		cout << "mysql_query() select data succeed" << endl;

		//һ����ȡ�����ݼ�
		result = mysql_store_result(&mydata);
		//ȡ�ò���ӡ����
		int rowcount = mysql_num_rows(result);
		cout << "row count: " << rowcount << endl;

		//ȡ�ò���ӡ���ֶε�����
		unsigned int fieldcount = mysql_num_fields(result);
		MYSQL_FIELD *field = NULL;
		for (unsigned int i = 0; i < fieldcount; i++) {
			field = mysql_fetch_field_direct(result, i);
			cout << field->name << "\t\t";
		}
		cout << endl;

		//��ӡ����
		MYSQL_ROW row = NULL;
		row = mysql_fetch_row(result);
		while (NULL != row) {
			for (int i = 0 ; i < fieldcount; i++) {
				if (i==1)
				{
					bool bo[64];
					for (int i=0; i<64; i++)
					{
						bo[i] = (row[1])[i]-48;
					}
					cout<<desDecode(bo)<<"\t\t";
				}
				else 
				cout << row[i] << "\t\t";
			}
			cout << endl;
			row = mysql_fetch_row(result);
		}

	} else {
		cout << "mysql_query() select data failed" << endl;
		mysql_close(&mydata);
	}
}

void NumberEncrypt::desEncode(char* plaintext)
{
	numPlaintextLen = sizeof(plaintext);
	des.SetMsg(plaintext, 9);
	des.SetKey();
	//����
	des.Crypte();
}

char* NumberEncrypt::desDecode( bool cryptedMsg[64] )
{
	char* temp =  des.getDecipherByCryped(cryptedMsg);
	memset(realDecipher, 0, 9);
	for (int i=0; i<numPlaintextLen; i++)
	{
		realDecipher[i] = temp[i];
	}
	realDecipher[numPlaintextLen] = '\0';
	return realDecipher;
}

void NumberEncrypt::readFileAndSave()
{
	char maxchar[9]={""}, minchar[9]={"99999999"};
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
			if (strcmp(maxchar, dataBuf) < 0)
			{
				strcpy(maxchar, dataBuf);
			}
			if (strcmp(minchar, dataBuf) > 0)
			{
				strcpy(minchar, dataBuf);
			}
			number.push_back(atoi(dataBuf));
			//id.push_back(i++);
			tranferedSave(i++, dataBuf);
			cout<<dataBuf<<endl;
		}
		maxNumber = atoi(maxchar);
		minNumber = atoi(minchar);
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
		cout << "�����Ѿ�¼�룬�벻Ҫ�ظ�¼��" << endl;
		//mysql_close(&mydata);
	}
}
