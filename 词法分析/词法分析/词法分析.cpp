#include<stdio.h>
#include<string.h>
#include<iostream>
#include<string>
FILE *fin,*fout;                                      //文件流 
std:: string word;                                   //暂存空间 
char ch;                                           //当前输入字符 
int line;                                         //表示行 

const int KEYWORldLEN=8;
std::string  keyword[KEYWORldLEN]={"if","else","for","while","do","int","read","write"};
//int Open_File()
////{
////	
////	if((fin=fopen("in.txt","r"))==NULL)
////	{
////		printf("文件读取打开失败!\n");
////		return  1; 
////	}
////	
////	if((fout=fopen("lex.txt","w"))==NULL)
////	{
////		printf("输出文件读取失败！\n");
////		return 2;
////	}
////	return 0;
////}
/*
  判断字符类型 1为字母，2为1-9的数字，3为分界符，4为运算符，5为注释符 
*/
int Idefine(char ch)
{
	if(ch>='A'&&ch<='z')  return 1;
	if(ch>='1'&&ch<='9') return  2;
	if(ch=='('||ch==')'||ch=='{'||ch=='}'||ch==';')  return 3;
	if(ch=='+'||ch=='-'||ch=='*'||ch=='>'||ch=='<'||ch=='='||ch=='!') return 4;
	if(ch=='/') return 5;
	if(ch=='0')  return 6; 
	
}
/*
是标识符函数 
*/
void Ide()
{
	int i=0;
	word=word+ch;
	ch=getc(fin);
	while((ch>='A'&&ch<='z')||(ch>='0'&&ch<='9'))                 //持续读入最长 
	{
		word=word+ch;
		ch=getc(fin);
	}
	int flag=0;                                              //是不是保留字的关键 
	for(i=0;i<KEYWORldLEN;i++)
	{
		if(word== keyword[i])
		{
			flag=1; 
			break;
		}
	}
	if(flag)
	{
		fprintf(fout,"Line %d %s  %s\n",line,word.c_str(),word.c_str()); 
	}
	else 
	{
		fprintf(fout,"Line %d ID  %s\n",line,word.c_str()); 
	}
}
/*
无符号整数 
*/ 
void Number()
{
	word=word+ch;
	ch=getc(fin);
	while(ch>='0'&&ch<='9')	
	{
		word=word+ch;
		ch=getc(fin);
	}
		fprintf(fout,"Line %d NUM  %s\n",line,word.c_str()); 
} 
/*
边界符号 
*/
void Bound()
{
		word=word+ch;
		ch=getc(fin);
		fprintf(fout,"Line %d %s  %s\n",line,word.c_str(),word.c_str()); 
 } 
 /*
 运算符 
 */
void Mathmatic()
{
	void Error(int type);             //申明 
 	word=word+ch;
    if(ch=='+'||ch=='*'||ch=='-')
    {
    	ch=getc(fin);
	}
	else if(ch=='>'||ch=='<'||ch=='=')
	{
		ch=getc(fin);
		if(ch=='=')
		{
			word=word+ch;
		}
	}
	else if(ch=='!')
	{
		ch=getc(fin);
		if(ch=='=')
		{
			word=word+ch;
			ch=getc(fin);
		}
		else 
		{
			Error(2); return;                 //错误为！后无= 
		}
	}
	fprintf(fout,"Line %d %s  %s\n",line,word.c_str(),word.c_str()); 
} 
/*
发生错误 1为当前输入错误，2为！错误3为注释错误 
*/ 
void Error(int type)
{
	switch(type)
	{
		case 1:std::cout<<"Line "<<line<<" 错误 "<<ch<<std::endl;ch=getc(fin); break;
		case 2:std::cout<<"Line "<<line<<" 错误 !" <<std::endl;     break;
		case 3: std:: cout<<"Line "<<line<<" 错误 注释不匹配"<<std::endl; break; 
	 } 
	 return ;
}
/*
 注释 
*/
void Annnotate()
{
	word=word+ch;	
	ch=getc(fin);
	if(ch!='*')                               //非* 为除法 
	{
		fprintf(fout,"Line  %d %s  %s\n",line,word.c_str(),word.c_str()); 
	    return ;
	}
	word=word+ch;	
	ch=getc(fin);

	int flag=0;             //判断前面是否y有*
	while(!(flag&&ch=='/')&&ch!=EOF)
	{

		word=word+ch;
		if(ch=='*')
		flag=1;
		else 
		flag=0;
		ch=getc(fin);
	} 
	if(ch==EOF)
	{
		Error(3);                     //不匹配 
	}
	else
	{	
	word=word+ch;
	fprintf(fout," %s\n",word.c_str()); 
	} 
	ch=getc(fin);
} 
/*
词法分析 
*/
void World_Ananly()
{

    ch=getc(fin);
    line=1;
	while(ch!=EOF)
	{
		word.clear();                                             //初始化 
		while(ch==' '||ch=='\n'||ch=='\t') 
		{
			if(ch=='\n') line++; 
			ch=getc(fin);    //开头跳过非字符；
		} 
		switch(Idefine(ch))
		{
		case 1:    Ide();		break;
		case 2:    Number();	break;
		case 3:	   Bound();		break;
		case 4:	   Mathmatic();  break;
		case 5:		Annnotate(); break;
		case 6:    fprintf(fout,"Line %d 0\n",line); ; ch=getc(fin); break;
		default:   	Error(1);		break;	
		}
	}
}

int main(int argc, char   **argv)
{
	if (argc<3)
	{
		printf("Please give input-file or output-file\n");
	}
	else
	{
		if (!(fin = fopen(argv[1],"r")))
		{
			printf("%s",argv[1]); 
			printf("Open input_file failed!\n");
			return 1;
		}
		if (!(fout = fopen(argv[2],"w")))
		{
			printf("Open output_file failed!\n");
			return 2;
		}
    World_Ananly();
     } 
	
	return 0;
}
