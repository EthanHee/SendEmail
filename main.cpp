#include "CSmtp.h"
#include <conio.h>
#include <iostream>

using namespace std;
std::vector<std::string> split(const  std::string& s, const std::string& delim);

/*
�������������

���������1���ʼ����⣻
          2���ʼ�����
		  3������·��
		  4���ռ������� ��#���ָ�����ж������

*/

int main(int argc, char **argv)
{
	if (argc != 5)
	{
		cout << "��������" << endl;
		system("pause");
		return 0;
	}
   
//   for (int i = 1; i < argc; ++i)
//		cout << argv[i] << endl;

   string allReceiver = argv[4];
   std::vector<std::string> eachReceiver = split(allReceiver,"#");

   cout << "�ʼ����⣺" << argv[1] << endl;
   cout << "�ʼ����ģ�" << argv[2] << endl;
   cout << "����·����" << argv[3] << endl;

   cout << "�ռ��ˣ�" << endl;
   for (int j = 0; j < eachReceiver.size(); j++)
   {
	   cout << eachReceiver.at(j).c_str() << endl;		    //�ռ�������
   }

    CSmtp mail;
	
   if(mail.GetLastError() != CSMTP_NO_ERROR)
   {
		printf("Unable to initialise winsock2.\n");
		return -1;
	}

	mail.SetSMTPServer("smtp.exmail.qq.com", 465);	//��Ѷ��ҵ�ʼ���������ַ  �˿�  
	mail.SetLogin("");			                    //�����û���
	mail.SetPassword("");			                //��¼����
	mail.SetSenderName("");			                //�����˳ƺ�
	mail.SetSenderMail("");	                        //��������
	mail.SetReplyTo("");		                    //�ռ��˻��������ַ

	//mail.SetSubject("The  test message");			//�ʼ�����
	mail.SetSubject(argv[1]);			//�ʼ�����

	for (int j = 0; j < eachReceiver.size(); j++)
	{
		mail.AddRecipient(eachReceiver.at(j).c_str());		    //�ռ�������
	}
	mail.SetXPriority(XPRIORITY_NORMAL);			 //���ȼ�
	mail.SetXMailer("The Bat! (v3.02) Professional");//�汾��Ϣ
	mail.SetMessageBody(argv[2]);	 //�ʼ���������
	mail.AddAttachment(argv[3]);//��Ӹ���������Ŀ¼
  
    
	if( mail.Send() )
		printf("The mail was send successfully.\n");		//���ͳɹ�
	else
	{
		printf("%s\n",GetErrorText(mail.GetLastError()));
		printf("Unable to send the mail.\n");
	}
	
	system("pause");
	return 0;
}

std::vector<std::string> split(const  std::string& s, const std::string& delim)
{
	std::vector<std::string> elems;
	size_t pos = 0;
	size_t len = s.length();
	size_t delim_len = delim.length();
	if (delim_len == 0) return elems;
	while (pos < len)
	{
		int find_pos = s.find(delim, pos);
		if (find_pos < 0)
		{
			elems.push_back(s.substr(pos, len - pos));
			break;
		}
		elems.push_back(s.substr(pos, find_pos - pos));
		pos = find_pos + delim_len;
	}
	return elems;
}
