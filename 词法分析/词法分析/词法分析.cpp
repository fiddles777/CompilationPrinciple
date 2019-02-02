#include<stdio.h>
#include<string.h>
#include<iostream>
#include<string>
FILE *fin,*fout;                                      //�ļ��� 
std:: string word;                                   //�ݴ�ռ� 
char ch;                                           //��ǰ�����ַ� 
int line;                                         //��ʾ�� 

const int KEYWORldLEN=8;
std::string  keyword[KEYWORldLEN]={"if","else","for","while","do","int","read","write"};
//int Open_File()
////{
////	
////	if((fin=fopen("in.txt","r"))==NULL)
////	{
////		printf("�ļ���ȡ��ʧ��!\n");
////		return  1; 
////	}
////	
////	if((fout=fopen("lex.txt","w"))==NULL)
////	{
////		printf("����ļ���ȡʧ�ܣ�\n");
////		return 2;
////	}
////	return 0;
////}
/*
  �ж��ַ����� 1Ϊ��ĸ��2Ϊ1-9�����֣�3Ϊ�ֽ����4Ϊ�������5Ϊע�ͷ� 
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
�Ǳ�ʶ������ 
*/
void Ide()
{
	int i=0;
	word=word+ch;
	ch=getc(fin);
	while((ch>='A'&&ch<='z')||(ch>='0'&&ch<='9'))                 //��������� 
	{
		word=word+ch;
		ch=getc(fin);
	}
	int flag=0;                                              //�ǲ��Ǳ����ֵĹؼ� 
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
�޷������� 
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
�߽���� 
*/
void Bound()
{
		word=word+ch;
		ch=getc(fin);
		fprintf(fout,"Line %d %s  %s\n",line,word.c_str(),word.c_str()); 
 } 
 /*
 ����� 
 */
void Mathmatic()
{
	void Error(int type);             //���� 
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
			Error(2); return;                 //����Ϊ������= 
		}
	}
	fprintf(fout,"Line %d %s  %s\n",line,word.c_str(),word.c_str()); 
} 
/*
�������� 1Ϊ��ǰ�������2Ϊ������3Ϊע�ʹ��� 
*/ 
void Error(int type)
{
	switch(type)
	{
		case 1:std::cout<<"Line "<<line<<" ���� "<<ch<<std::endl;ch=getc(fin); break;
		case 2:std::cout<<"Line "<<line<<" ���� !" <<std::endl;     break;
		case 3: std:: cout<<"Line "<<line<<" ���� ע�Ͳ�ƥ��"<<std::endl; break; 
	 } 
	 return ;
}
/*
 ע�� 
*/
void Annnotate()
{
	word=word+ch;	
	ch=getc(fin);
	if(ch!='*')                               //��* Ϊ���� 
	{
		fprintf(fout,"Line  %d %s  %s\n",line,word.c_str(),word.c_str()); 
	    return ;
	}
	word=word+ch;	
	ch=getc(fin);

	int flag=0;             //�ж�ǰ���Ƿ�y��*
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
		Error(3);                     //��ƥ�� 
	}
	else
	{	
	word=word+ch;
	fprintf(fout," %s\n",word.c_str()); 
	} 
	ch=getc(fin);
} 
/*
�ʷ����� 
*/
void World_Ananly()
{

    ch=getc(fin);
    line=1;
	while(ch!=EOF)
	{
		word.clear();                                             //��ʼ�� 
		while(ch==' '||ch=='\n'||ch=='\t') 
		{
			if(ch=='\n') line++; 
			ch=getc(fin);    //��ͷ�������ַ���
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
