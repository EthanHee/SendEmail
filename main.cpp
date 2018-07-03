#include "CSmtp.h"
#include <conio.h>
#include <iostream>

using namespace std;
std::vector<std::string> split(const  std::string& s, const std::string& delim);

/*
传入参数个数：

传入参数：1、邮件主题；
          2、邮件正文
		  3、附件路径
		  4、收件人邮箱 用#做分割，可能有多个邮箱

*/

int main(int argc, char **argv)
{
	if (argc != 5)
	{
		cout << "参数错误！" << endl;
		system("pause");
		return 0;
	}
   
//   for (int i = 1; i < argc; ++i)
//		cout << argv[i] << endl;

   string allReceiver = argv[4];
   std::vector<std::string> eachReceiver = split(allReceiver,"#");

   cout << "邮件主题：" << argv[1] << endl;
   cout << "邮件正文：" << argv[2] << endl;
   cout << "附件路径：" << argv[3] << endl;

   cout << "收件人：" << endl;
   for (int j = 0; j < eachReceiver.size(); j++)
   {
	   cout << eachReceiver.at(j).c_str() << endl;		    //收件人邮箱
   }

    CSmtp mail;
	
   if(mail.GetLastError() != CSMTP_NO_ERROR)
   {
		printf("Unable to initialise winsock2.\n");
		return -1;
	}

	mail.SetSMTPServer("smtp.exmail.qq.com", 465);	//腾讯企业邮件服务器地址  端口  
	mail.SetLogin("");			                    //邮箱用户名
	mail.SetPassword("");			                //登录密码
	mail.SetSenderName("");			                //发件人称呼
	mail.SetSenderMail("");	                        //发件邮箱
	mail.SetReplyTo("");		                    //收件人回信邮箱地址

	//mail.SetSubject("The  test message");			//邮件主题
	mail.SetSubject(argv[1]);			//邮件主题

	for (int j = 0; j < eachReceiver.size(); j++)
	{
		mail.AddRecipient(eachReceiver.at(j).c_str());		    //收件人邮箱
	}
	mail.SetXPriority(XPRIORITY_NORMAL);			 //优先级
	mail.SetXMailer("The Bat! (v3.02) Professional");//版本信息
	mail.SetMessageBody(argv[2]);	 //邮件正文内容
	mail.AddAttachment(argv[3]);//添加附件，本地目录
  
    
	if( mail.Send() )
		printf("The mail was send successfully.\n");		//发送成功
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
