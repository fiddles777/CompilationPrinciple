#include<stdio.h>
#include<string.h>
#include<vector>
#include<iostream>

std::vector< char >status;
char chID[20],ch[20];                 //chID当前字符标记 ,ch当前字符 
int line;                        //当前的函数 
int f;
FILE * istream;
bool  identify; 
void error()
{
	identify=false;
	printf("Line %d  %s error!\n",line,ch);
	fscanf(istream,"%d%s%s", &line,chID,ch);
}
 
void   program()
{
	if(!strcmp(chID,"{"))
	{
		status.pop_back();
		status.push_back('}');
		status.push_back('D');
		status.push_back('B');
		fscanf(istream,"%d%s%s", &line,chID,ch);
	}
	else
	{
		error();
	}
	return;
}

void declaration_list()
{
	if(!strcmp(chID,"int"))
	{
	    status.pop_back();
		status.push_back('B');
		status.push_back('C');
	}
	else if(strcmp(chID, "if") == 0 ||
        strcmp(chID, "while") == 0 ||
        strcmp(chID, "for") == 0 ||
        strcmp(chID, "read") == 0 ||
        strcmp(chID, "write") == 0 ||
        strcmp(chID, "{") == 0 ||
        strcmp(chID, ";") == 0 ||
        strcmp(chID, "ID") == 0 ||
        strcmp(chID, "(") == 0||
        strcmp(chID, "NUM") == 0 ||
        strcmp(chID, "}") == 0)
        {
        	status.pop_back();
        }
        else 
        {
        	error();
        }
        return ;
}

void declaration_stat()
{
	if(strcmp(chID, "int") == 0)
	{
		status.pop_back();
		status.push_back(';');
		status.push_back('g');
		fscanf(istream,"%d%s%s", &line,chID,ch);
	}
	else 
	{
		error();
	}
	return ;
}

void  statement_list()
{
	if(strcmp(chID, "}") == 0)
	{
		status.pop_back();
		
	}
	else if( strcmp(chID, "if") == 0 || strcmp(chID, "while") == 0 ||
        strcmp(chID, "for") == 0 || strcmp(chID, "read") == 0 ||
        strcmp(chID, "write") == 0 || strcmp(chID, "ID") == 0 ||
        strcmp(chID, "{") == 0 || strcmp(chID, ";") == 0 ||
        strcmp(chID, "NUM") == 0 || strcmp(chID, "(") == 0 )
        {
        	status.pop_back();
        	status.push_back('D');
        	status.push_back('E');
        }
        else 
        {
        	error();
        }
}


void statement()
{
	if(strcmp(chID, "{") == 0)
	{
		status.pop_back();
		status.push_back('K');
	}
	else if(strcmp(chID, "if") == 0)
	{
		status.pop_back();
		status.push_back('F');
	}
	else if(strcmp(chID, "while") == 0)
	{
		status.pop_back();
		status.push_back('G');	
	}
	else if(strcmp(chID, "for") == 0)
	{
		status.pop_back();
		status.push_back('H');
	}
	else if(strcmp(chID, "write") == 0)
	{
		status.pop_back();
		status.push_back('I');
	}
	else if(strcmp(chID, "read") == 0)
	{
		status.pop_back();
		status.push_back('J');
	}
	else if(strcmp(chID, "ID") == 0 || 
			strcmp(chID, "NUM") == 0 ||
			 strcmp(chID, "(") == 0||
			strcmp(chID, ";") == 0)
			{
				status.pop_back();
				status.push_back('L');
			}
	else {
		error();
	}
	return ;
}

void if_stat()
{
	if(strcmp(chID, "if") == 0)
	{
		status.pop_back();
		status.push_back('U');
		status.push_back('E');
		status.push_back(')');
		status.push_back('M');
		status.push_back('(');
		fscanf(istream,"%d%s%s", &line,chID,ch);
	}
	else 
	{
		error();
	}
}

void  while_stat()
{
	if(strcmp(chID, "while") == 0)
	{
		status.pop_back();
		status.push_back('E');
		status.push_back(')');
		status.push_back('M');
		status.push_back('(');
		fscanf(istream,"%d%s%s", &line,chID,ch);
	}
	else 
	{
		error();
	}
}

void for_stat()
{
	if(strcmp(chID, "for") == 0)
	{
		status.pop_back();
		status.push_back('E');
		status.push_back(')');
		status.push_back('M');
		status.push_back(';');
		status.push_back('M');
		status.push_back(';');
		status.push_back('M');
		status.push_back('(');
		fscanf(istream,"%d%s%s", &line,chID,ch);
	}
	else 
	{
		error();
	}
}
void write_stat()
{
	if(strcmp(chID,"write")==0)
	{
		status.pop_back();
		status.push_back(';');
		status.push_back('M');
		fscanf(istream,"%d%s%s", &line,chID,ch);
	}
	else 
	{
		error(); 
	} 
} 

void read_stat()
{
	if(strcmp(chID,"read")==0)
	{
		status.pop_back();
		status.push_back(';');
		status.push_back('g');
		fscanf(istream,"%d%s%s", &line,chID,ch);
	}
	else
	{
		error();
	}
}
void compound_stat()
{
	if(strcmp(chID,"{")==0)
	{
		status.pop_back();
		status.push_back('}');
		status.push_back('D');
		fscanf(istream,"%d%s%s", &line,chID,ch);
	}
	else 
	{
		error();
	}
}
void expression_stat()
{
	if(strcmp(chID,";")==0)
	{
		status.pop_back();
		fscanf(istream,"%d%s%s", &line,chID,ch);
	}
	else if(strcmp(chID,"ID")==0||
			strcmp(chID,"NUM")==0||
			strcmp(chID,"(")==0)
			{
				status.pop_back();
				status.push_back(';');
				status.push_back('M');
			}
		else 
		{
			error();
		}
}
void expression()
{
	char chID1[20],ch1[20];
	int line1,filep;
	
	if(strcmp(chID,"ID")==0)
	{
		filep=ftell(istream);
		fscanf(istream, "%d%s%s\n", &line1, &chID1, &ch1);
		if(strcmp(chID1,"=")==0)
		{
			status.pop_back();
			status.push_back('N');
			fscanf(istream, "%d%s%s\n", &line, &chID, &ch);
		}
		else
		{
			 fseek(istream, filep, 0);    //返回原位。 
			 status.pop_back();
			 status.push_back('N'); 
		}
	}
	else if(strcmp(chID,"NUM")==0|| strcmp(chID,"(")==0)
	{
		status.pop_back();
		status.push_back('N');
		
	}
	else 
	{
		error();
	}
	
}
void bool_expr()
{
	if(strcmp(chID,"ID")==0||
		strcmp(chID,"NUM")==0||
		strcmp(chID,"(")==0)
		{
			status.pop_back();
			status.push_back('O');
			status.push_back('P');
		}
		else 
		{
			error();
		}
}

void bool_expr1()
{
	if(  strcmp(chID, ">") == 0 ||
        strcmp(chID, ">=") == 0 ||
        strcmp(chID, "<") == 0 ||
        strcmp(chID, "<=") == 0 ||
        strcmp(chID, "==") == 0 ||
        strcmp(chID, "!=") == 0)
        {
          status.pop_back();
          status.push_back('P');
          fscanf(istream,"%d%s%s", &line,chID,ch);
        }
        else if(strcmp(chID, ";") == 0||strcmp(chID, ")") == 0)
        {
        	status.pop_back();
        }
}
void additive_expr()
{
	if(strcmp(chID, "ID") == 0||
		strcmp(chID, "NUM") == 0 ||
		strcmp(chID, "(") == 0  )
		{
			status.pop_back();
			status.push_back('Q');
			status.push_back('R');
		}
		else 	
		{
			error();
		}
}
void additive_expr1()
{
	//printf("1");
	 if (strcmp(chID, "+") == 0 || strcmp(chID, "-") == 0)
	 {
	 	status.pop_back();
	 	status.push_back('Q');
	 	status.push_back('R');
	 	fscanf(istream,"%d%s%s", &line,chID,ch);
	 }
	 else if(  strcmp(chID, ";") == 0 || strcmp(chID, ")") == 0 ||
        strcmp(chID, ">") == 0 || strcmp(chID, ">=") == 0 ||
        strcmp(chID, "<") == 0 || strcmp(chID, "<=") == 0 ||
        strcmp(chID, "==") == 0 || strcmp(chID, "!=") == 0)
        {
        	status.pop_back();
        }
        else 
        {
        	error();
        }
}
void term()
{
	if (strcmp(chID, "ID") == 0 || strcmp(chID, "NUM") == 0 || strcmp(chID, "(") == 0)
	{
		status.pop_back();
		status.push_back('S');
		status.push_back('T');
		
	}
	else 
	{
		error();
	}
}

void term1()
{
	if (strcmp(chID, "*") == 0 || strcmp(chID, "/") == 0)
	{
		status.pop_back();
		status.push_back('S');
		status.push_back('T');
		fscanf(istream,"%d%s%s", &line,chID,ch);
	}
	else if( strcmp(chID, ";") == 0 || strcmp(chID, ")") == 0 ||
        strcmp(chID, "+") == 0 || strcmp(chID, "-") == 0 ||
        strcmp(chID, ">") == 0 || strcmp(chID, ">=") == 0 ||
        strcmp(chID, "<") == 0 || strcmp(chID, "<=") == 0 ||
        strcmp(chID, "==") == 0 || strcmp(chID, "!=") == 0)
        {
        	status.pop_back();
        }
    else 
    {
    	error();
    }
}

void factor()
{
	if(strcmp(chID, "(") == 0)
	{
		status.pop_back();
		status.push_back(')');
		status.push_back('M');
		fscanf(istream,"%d%s%s", &line,chID,ch);
	}
	else if (strcmp(chID, "ID") == 0 || strcmp(chID, "NUM") == 0)
	{
		status.pop_back();
		fscanf(istream,"%d%s%s", &line,chID,ch);
	}
}

void   flag()
{
	if(strcmp(chID, "else") == 0)
	{
		status.pop_back();
		status.push_back('E');
		fscanf(istream,"%d%s%s", &line,chID,ch);
	}
	else if(strcmp(chID, "#") == 0)
	{
		error();
	}
	else
	{
		status.pop_back();
	}
}
void uCharacter(char temp)
{	//printf("%s",ch); 
	if(strcmp(chID,"if")==0&&temp=='b')
	{
		status.pop_back();
		fscanf(istream,"%d%s%s", &line,chID,ch);
	}
	else if(strcmp(chID,"while")==0&&temp=='c')
	{
		status.pop_back();
		fscanf(istream,"%d%s%s", &line,chID,ch);
	}
	else if(strcmp(chID,"for")==0&&temp=='d')
	{
		status.pop_back();
		fscanf(istream,"%d%s%s", &line,chID,ch);
	}
	else if(strcmp(chID,"write")==0&&temp=='e')
	{
		status.pop_back();
		fscanf(istream,"%d%s%s", &line,chID,ch);
	}
	else if(strcmp(chID,"read")==0&&temp=='f')
	{
		status.pop_back();
		fscanf(istream,"%d%s%s", &line,chID,ch);
	}
	else if(strcmp(chID,"ID")==0&&temp=='g')
	{
		status.pop_back();
		fscanf(istream,"%d%s%s", &line,chID,ch);
	}
	else if(strcmp(chID,"NUM")==0&&temp=='h')
	{
		status.pop_back();
		fscanf(istream,"%d%s%s", &line,chID,ch);
	}
	else if(strcmp(chID,"else")==0&&temp=='j')
	{
		status.pop_back();
		fscanf(istream,"%d%s%s", &line,chID,ch);
	}
	else if(chID[0]==temp&&strlen(chID)==1)
	{

		status.pop_back();
		fscanf(istream,"%d%s%s", &line,chID,ch);
	}
	else 
	{
		error();
	}
}
int main()
{
	if((istream=fopen("lex.txt","r"))==NULL)
	{
		printf("文件打开错误！\n");
		return -1;
	}
	 
	status.clear(); 
	//status.push_back('#');
	status.push_back('A');                 //初始压栈 
	
	fscanf(istream,"%d%s%s", &line,chID,ch);
	f=1;
	identify=true;
	while(!status.empty()&& f)
	{
	
		if(feof(istream))              //字符已经读完。 
		{
			f=0;
			continue; 
		} 
		char temp=status.back();
	
	//	printf("%s\n" ,ch);
		switch(temp)
		{
			case 'A': program(); break;
			case 'B': 	declaration_list(); break;
			case 'C':  declaration_stat(); break;
			case 'D':  statement_list(); break;
			case 'E':  statement();   break;
			case 'F':  if_stat();     break;
			case 'G':   while_stat(); break;
			case 'H':    for_stat();  break; 
			case 'I':    write_stat(); break;
			case 'J':   read_stat();   break;
			case 'K':	compound_stat(); break;
			case 'L':  expression_stat(); break;
			case 'M':  expression();     break;
			case 'N':  bool_expr();   	break;
			case 'O':  bool_expr1();    break;
			case 'P':	additive_expr(); break;
			case 'Q':  	additive_expr1();  break;
			case 'R':   term();  		break;
			case 'S': 	term1();		break;
			case 'T':	factor();		break;
			case 'U':   flag();         break;
			default :   uCharacter(temp);   break;
		}
	}
	if(!status.empty())
	{
		identify=false;
		printf("Line %d 缺少 %c\n",line ,status.front());     //表示缺少词语 
	}
	if(identify )
	{
		printf("语法编译成功未发现错误!\n");
	}
	else 
	{
		printf("语法编译发现错误！\n");
	}
	
	
 return 0;   
} 
