#include<stdio.h>
#include<string.h>
#include<queue>
#include<iostream>
#include<string>
/*************************************************

@ aurther ������
2017-3-26 
����ԭ����ҵ  ��������ͼ���ɴ��룩 
*************************************************/ 

enum Statu{zero,one,tow,three}nowS;    //��ӦDFA������״̬ 
//enum Errow{a,b,c}nowErrow;   //���ִ���״̬ 
std::queue<char>buf1;
std::queue<char>buf2;

/*
*  ��ʼ�������Գ�ʼ״̬�������ڴ�ռ������� 
*/ 
void init()
{
	nowS=zero;
	while(!buf1.empty())
	{
		buf1.pop();
	}
	while(!buf2.empty())
	{
		buf2.pop();
	}
}
/*
*  buf1->buf2
*/
void 	TrForBuf()
{
	while(!buf1.empty())
	{
		buf2.push(buf1.front());
		buf1.pop();
	}
}
/*
*   ������Ϣ��� 
*/
void   ErrowEam()
{
	if(!buf2.empty())
	printf("errow sentence!\n");
	while(!buf2.empty()) 
	{
		printf("%c",buf2.front());
		buf2.pop();
	}
	printf("\n");
} 
/*
*����״̬ 
*/
void  ErrowS(int state)
{
   switch(state)
   {
   	case 1:   break;
   	case 2:   ErrowEam(); break;
   }	
}

/*
*  ������ch״̬Ϊ0ʱ�ĸı� 
*/
void  ChangeZeroS(char ch)
{
	switch(ch)
	{
		case 'a':  nowS=one; break;
		case 'b':  nowS=tow; break;
		default: 	TrForBuf();ErrowS(2);init(); break;
	}
}

/*
* ������ch״̬Ϊ1ʱ�ĸı� 
*/
void   ChangeOneS(char ch)
{
	switch(ch)
	{
		case 'a':  nowS=three; break;
		case 'b':  nowS=tow;  break;
		default: TrForBuf();ErrowS(2);init(); break;
	}
}
/*
*  ������ch״̬Ϊ2ʱ�ĸı� 
*/
void  ChangeTowS(char ch)
{
		switch(ch)
	{
		case 'a':  nowS=one; break;
		case 'b':  nowS=three;  break;
		default: TrForBuf();ErrowS(2);init(); break;
	}
}  
/*
*������ch״̬Ϊ3ʱ�ĸı� 
*/
void ChangeThreeS(char ch)
{
	TrForBuf();
	switch(ch)
	{
		case 'a':  nowS=three; break;
		case 'b':  nowS=three;  break;
		default: TrForBuf();ErrowS(2);init(); break;
	}
}
/*
*  ������� 
*/
void  endS()
{
		TrForBuf();
		if(nowS==three)             //��󵽴�����̬ 
		{
	    if(!buf2.empty()) 
		printf("right sentence!\n");
		while(!buf2.empty())   // ��ȷ������ 
		{
			
			printf("%c",buf2.front());
			buf2.pop();
		}
		printf("\n");
	    }
	    else ErrowS(2);

} 
int  main()
{
	
	std::string str;  //��������ַ��� 
	char ch;            //��ǰ�����ַ�
	while(std::getline(std::cin,str))                   //���� 
	{
	    init();
		int i,j;
		int len=str.length();
		for(i=0;i<len;i++)                               //��ÿ���ַ����� 
		{
	       ch=str[i];
		   buf1.push(ch); 
		   switch(nowS)
		   {
		   	  case zero:  ChangeZeroS(ch);break;
		   	  case one :  ChangeOneS(ch); break;
			  case tow :  ChangeTowS(ch); break;
			  case three: ChangeThreeS(ch);break;
			  default:    ErrowS(1);  init();     break;
			  
		   }	
		                           
		}
		endS();
	}
	return 0;
 } 
