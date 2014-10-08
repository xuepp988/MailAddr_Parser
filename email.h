using namespace std;

class Email_List
{
public:
	int Num;
	string Address[10];
	string Type[10];
	string suffix;

	void GetChar(ifstream &in,char *ch);	//��ȡ�ַ���ch
	void GetBC(ifstream &in,char *ch);		//����ǿհ����������һ����ֱ�����ǿհ�
	void Retract(ifstream &in,char *ch);    //������һλ,��ʹ ch Ϊ��
	void Concat(char *Buffer, char *ch);	//��ch�е��ַ����ӵ�Buffer���棬Buffer����ʱ��ſռ�
	int Semantic_Analyzer(char *Buffer);    //�����ж�
};

void Email_List::GetChar(ifstream &in,char *ch)
{	
	*ch=in.get();	
}

//����ǿհ����������һ����ֱ�����ǿհ�
void Email_List::GetBC(ifstream &in,char *ch)
{
	{ *ch=in.get(); }while(isspace(*ch)&&(*ch != EOF)); 
}

//������һλ,��ʹ ch Ϊ��
void Email_List::Retract(ifstream &in,char *ch)
{
	in.seekg(-1,ios::cur); 
	*ch = '\0'; 
}

//��ch�е��ַ����ӵ�Buffer���棬Buffer����ʱ��ſռ�
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
		Buffer++;    //ָ��λ�ú���
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

	// ���Լ�������������嶯��
}
