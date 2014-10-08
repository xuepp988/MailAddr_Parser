#include <iostream>
#include<fstream>
#include <string>
#include"email.h"

using namespace std;

int main()
{	
	Email_List list;
	int c;
	string Input;

	cout<<"测试用例1-9："<<endl;
	cin>>c;

	switch (c)
	{	
		case 1:Input="C:/Users/Yarrow/Documents/Visual Studio 2012/Projects/Compile/1.txt";break;
		case 2:Input="C:/Users/Yarrow/Documents/Visual Studio 2012/Projects/Compile/2.txt";break;
		case 3:Input="C:/Users/Yarrow/Documents/Visual Studio 2012/Projects/Compile/3.txt";break;
		case 4:Input="C:/Users/Yarrow/Documents/Visual Studio 2012/Projects/Compile/4.txt";break;
		case 5:Input="C:/Users/Yarrow/Documents/Visual Studio 2012/Projects/Compile/5.txt";break;
		case 6:Input="C:/Users/Yarrow/Documents/Visual Studio 2012/Projects/Compile/6.txt";break; //用户输入的所需读入邮件列表数据的绝对地址
		case 7:Input="C:/Users/Yarrow/Documents/Visual Studio 2012/Projects/Compile/7.txt";break;
		case 8:Input="C:/Users/Yarrow/Documents/Visual Studio 2012/Projects/Compile/8.txt";break;
		case 9:Input="C:/Users/Yarrow/Documents/Visual Studio 2012/Projects/Compile/9.txt";break;
		default:break;
	}
	string Output="C:/Users/Yarrow/Documents/Visual Studio 2012/Projects/Compile/Output.txt";
	cout<<"Please input filePath of Input.txt："<<endl;
//	cin>>Input;
	cout<<Input<<endl;
	ifstream in(Input,ios::in);

	if (! in.is_open())  
       	{ cout << "Error opening file"; getchar(); _exit (1); } 
	
/*	while (!in.eof() )  
	{	
		list.Num=0;
		getline(in,list.Address[list.Num],';'); 
		cout<<list.Address[list.Num]<<endl;
		list.Num++;	
	}*/
	
	in.clear();
	in.seekg(0,ios::beg); 

	cout<<"Please input filePath of Output.txt："<<endl;
//	cin>>Output;
	cout<<Output<<endl;
	ofstream out(Output,ios::out);
	if (! out.is_open())  
       	{ cout << "Error opening file"; getchar(); _exit (1); }
	
	cout<<endl<<"==========================="<<endl;    //分割线

	char ch;
	int i;
	char *Buffer=new char[100];
	list.Num=0;

	// 词法分析子程序
	while(true) 
	{
		list.GetBC(in,&ch); //检测是否为连续空白
		for(i=0;i<100;i++) Buffer[i]=NULL;  // 临时存放区进行置零
		int pos=list.Address[list.Num].find('@',0);

 		if((ch=='@'))
		{	
			
			if(pos!=-1)
			{
				cout<<"Parsing Error with @"<<endl;
				break;
			}
			
			cout<<"<sign,"<<ch<<","<<"2>"<<endl;
			out <<"<sign,"<<ch<<",2>"<<endl;
			list.Address[list.Num]
			.insert(list.Address[list.Num].size(),"@");//在尾部插入 	 
		}
		// 标识符
		else if (ch=='_'||ch=='-'||isalpha(ch)||isdigit(ch))
		{
			while (ch=='_'||ch=='-'||isalpha(ch)||isdigit(ch)) 
			{ 
				list.Concat(Buffer,&ch); 
				list.GetChar(in,&ch); 
			}

			//语义分析
			if(ch == '.')
			{
				// 此处多读入一个字符用于上层的while判断的退出，退格一位
				list.Retract(in,&ch);
				if(list.Semantic_Analyzer(Buffer)==0)
				{
					cout<<"<domain,"<<Buffer<<",1>"<<endl;
					out <<"<domain,"<<Buffer<<",1>"<<endl;
				}
				else
				{
					cout<<"Semantic_Analyzing error at"<<" "<<Buffer<<endl;
					out<<"Semantic_Analyzing error at"<<" "<<Buffer<<endl;
					break;
				}
			}
			else if(ch == '@')
			{
				list.Retract(in,&ch);
				cout<<"<username,"<<Buffer<<",1>"<<endl;
				out <<"<username,"<<Buffer<<",1>"<<endl;
			}
			else
			{
				cout<<"Parser suspended at"<<" "<<list.Address[list.Num]<<Buffer<<endl;
				break;
			}
			list.Address[list.Num].insert(list.Address[list.Num].size(),Buffer);//在尾部插入 
		}

		// 准备读入邮箱域名，仅处理四种域名：.com, .net, .gov, .edu, .org
		else if(ch=='.')
		{
			list.Address[list.Num].insert(list.Address[list.Num].size(),".");//在尾部插入 
			getline(in,list.suffix,';');
			if(list.suffix.compare("com")==0)
			{	
				cout<<"<suffix,"<<list.suffix<<",3>"<<endl; 
				out <<"<suffix,"<<list.suffix<<",3>"<<endl;
				list.Address[list.Num].insert(list.Address[list.Num].size(),list.suffix);//在尾部插入 
				cout<<endl<<"No."<<list.Num<<" "<<list.Address[list.Num]<<endl<<endl;
				cout<<list.Type[list.Num]<<endl;
				out<<endl<<"No."<<list.Num<<" "<<list.Address[list.Num]<<endl<<endl;
				out<<list.Type[list.Num]<<endl;
				list.Num++;
				cout<<"==========================="<<endl;    //分割线
				out<<"==========================="<<endl;
				continue;
			}
			else if(list.suffix.compare("net")==0)
			{
				cout<<"<suffix,"<<list.suffix<<",4>"<<endl; 
				out <<"<suffix,"<<list.suffix<<",4>"<<endl;
				list.Address[list.Num].insert(list.Address[list.Num].size(),list.suffix);//在尾部插入 
				cout<<endl<<"No."<<list.Num<<" "<<list.Address[list.Num]<<endl<<endl;
				cout<<list.Type[list.Num]<<endl;
				out<<endl<<"No."<<list.Num<<" "<<list.Address[list.Num]<<endl<<endl;
				out<<list.Type[list.Num]<<endl;
				list.Num++;
				cout<<"==========================="<<endl;    //分割线
				out<<"==========================="<<endl;
				continue;
			}
			else if(list.suffix.compare("gov")==0)
			{
				cout<<"<suffix,"<<list.suffix<<",5>"<<endl; 
				out <<"<suffix,"<<list.suffix<<",5>"<<endl;
				list.Address[list.Num].insert(list.Address[list.Num].size(),list.suffix);//在尾部插入 
				cout<<endl<<"No."<<list.Num<<" "<<list.Address[list.Num]<<endl<<endl;
				cout<<list.Type[list.Num]<<endl;
				out<<endl<<"No."<<list.Num<<" "<<list.Address[list.Num]<<endl<<endl;
				out<<list.Type[list.Num]<<endl;
				list.Num++;
				cout<<"==========================="<<endl;    //分割线
				out<<"==========================="<<endl;
				continue;
			}
			else if(list.suffix.compare("edu")==0)
			{
				cout<<"<suffix,"<<list.suffix<<",6>"<<endl; 
				out <<"<suffix,"<<list.suffix<<",6>"<<endl;
				list.Address[list.Num].insert(list.Address[list.Num].size(),list.suffix);//在尾部插入 
				cout<<endl<<"No."<<list.Num<<" "<<list.Address[list.Num]<<endl<<endl;
				cout<<list.Type[list.Num]<<endl;
				out<<endl<<"No."<<list.Num<<" "<<list.Address[list.Num]<<endl<<endl;
				out<<list.Type[list.Num]<<endl;
				list.Num++;
				cout<<"==========================="<<endl;    //分割线
				out<<"==========================="<<endl;
				continue;
			}
			else if(list.suffix.compare("org")==0)
			{
				cout<<"<suffix,"<<list.suffix<<",7>"<<endl; 
				out <<"<suffix,"<<list.suffix<<",7>"<<endl;
				list.Address[list.Num].insert(list.Address[list.Num].size(),list.suffix);//在尾部插入 
				cout<<endl<<"No."<<list.Num<<" "<<list.Address[list.Num]<<endl<<endl;
				cout<<list.Type[list.Num]<<endl;
				out<<endl<<"No."<<list.Num<<" "<<list.Address[list.Num]<<endl<<endl;
				out<<list.Type[list.Num]<<endl;
				list.Num++;
				cout<<"==========================="<<endl;    //分割线
				out<<"==========================="<<endl;
				continue;
			}
			else 
			{
				cout<<"Parser suspended at"<<" "<<list.Address[list.Num]<<list.suffix<<endl;
				out<<"Parser suspended at"<<" "<<list.Address[list.Num]<<list.suffix<<endl;
				break;
			}
		}
		else if(ch==EOF)
		{
			cout<<"Parsing completed"<<endl;
			out<<"Parsing completed"<<endl;
			break;
		}
		else
		{
			cout<<"Parsing error at"<<" "<<ch<<endl;
			out<<"Parsing error at"<<" "<<ch<<endl;
			break;
		}
	}
	getchar();
	getchar();
	in.close();
	out.close();
	return 0;
}