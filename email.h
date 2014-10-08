using namespace std;

class Email_List
{
public:
	int Num;
	string Address[10];
	string Type[10];
	string suffix;

	void GetChar(ifstream &in,char *ch);	//读取字符送ch
	void GetBC(ifstream &in,char *ch);		//如果是空白则继续读下一个，直到不是空白
	void Retract(ifstream &in,char *ch);    //光标回退一位,并使 ch 为空
	void Concat(char *Buffer, char *ch);	//将ch中的字符连接到Buffer后面，Buffer是临时存放空间
	int Semantic_Analyzer(char *Buffer);    //语义判断
};

void Email_List::GetChar(ifstream &in,char *ch)
{	
	*ch=in.get();	
}

//如果是空白则继续读下一个，直到不是空白
void Email_List::GetBC(ifstream &in,char *ch)
{
	{ *ch=in.get(); }while(isspace(*ch)&&(*ch != EOF)); 
}

//光标回退一位,并使 ch 为空
void Email_List::Retract(ifstream &in,char *ch)
{
	in.seekg(-1,ios::cur); 
	*ch = '\0'; 
}

//将ch中的字符连接到Buffer后面，Buffer是临时存放空间
void Email_List::Concat(char *Buffer, char *ch)
{
	int i; 
	for(i=0;i<100;i++) 
	{ 
		if(*Buffer == NULL) 
		{ 
			*Buffer = *ch; 
			break; 
		} 
		Buffer++;    //指针位置后移
	} 
}

int Email_List::Semantic_Analyzer(char *Buffer)
{
	if(!strcmp(Buffer,"qq")){ Type[Num]="Email Domain: qq";return 0;}

	else if(!strcmp(Buffer,"sina")){ Type[Num]="Email Domain: sina";return 0;}

	else if(!strcmp(Buffer,"gmail")){ Type[Num]="Email Domain: gmail";return 0;}
	
	else if(!strcmp(Buffer,"163")){ Type[Num]="Email Domain: 163";return 0;}

	else if(!strcmp(Buffer,"whu")){ Type[Num]="Email Domain: whu";return 0;}

	else return 1;

	// 可以继续添加其他语义动作
}
