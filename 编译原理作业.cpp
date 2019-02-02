#include<stdio.h>
#include<string.h>
#include<queue>
#include<iostream>
#include<string>
/*************************************************

@ aurther 郭海富
2017-3-26 
编译原理作业  （将流程图做成代码） 
*************************************************/ 

enum Statu{zero,one,tow,three}nowS;    //对应DFA的三个状态 
//enum Errow{a,b,c}nowErrow;   //三种错误状态 
std::queue<char>buf1;
std::queue<char>buf2;

/*
*  初始化函数对初始状态，及其内存空间进行清空 
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
*   错误信息输出 
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
*错误状态 
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
*  当输入ch状态为0时的改变 
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
* 当输入ch状态为1时的改变 
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
*  当输入ch状态为2时的改变 
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
*当输入ch状态为3时的改变 
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
*  结束输出 
*/
void  endS()
{
		TrForBuf();
		if(nowS==three)             //最后到达终钛态 
		{
	    if(!buf2.empty()) 
		printf("right sentence!\n");
		while(!buf2.empty())   // 正确语句输出 
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
	
	std::string str;  //输入的总字符串 
	char ch;            //当前输入字符
	while(std::getline(std::cin,str))                   //输入 
	{
	    init();
		int i,j;
		int len=str.length();
		for(i=0;i<len;i++)                               //对每个字符遍历 
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
