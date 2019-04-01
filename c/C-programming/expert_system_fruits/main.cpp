#include <string.h>
#include <iostream>
using namespace std;
#define True 1
#define False 0
#define DontKnow -1
int main()
{
	const char * str[] = { "Բ����","С����","����Բ��","������","��״" ,
		"��ɫ","��ɫ����ɫ","��������ɫ","��ɫ����","��ɫ�аߵ�",
		"�ᡢ��","��","��Ƥ����ʳ��","������һ��","��Ƥ��ëë",
		"��Ƥ���ܳ�","С","����","����","⨺���","����","��ݮ"};
	int rulep[][6] = { {1,6,11,13,0,0},{2,7,11,14,0,0},{3,8,11,15,0,0},{4,9,12,16,0,0},{5,10,11,17,0,0} };
	int rulc[] = { 18,19,20,21,22 };
	class fact //��ʵ��
	{
	private:
		int Number;//��ʵ�ı��
		char Content[21];//��ʵ������
		int Active;
		int Succ;
	public:
		fact *Next;
		fact(int Num, char *L)
		{
			strcpy(Content, L);
			Number = Num;
			Active = False;
			//-1 ���Ѿ����������ϡ�1 ���Ѿ��������ϡ�
			Succ = DontKnow; //0 ���ޣ�-1 �ǲ�֪����1 ���С�
			Next = NULL;
		}
		char *GetContent()
		{
			char *L;
			L = new char[21];
			strcpy(L, Content);
			return L;
		}
		int GetNumber()
		{
			return Number;
		}
		int GetAct()
		{
			return Active;
		}
		int GetSucc()
		{
			return Succ;
		}
		void PutAct(const int Act0, int Suc0)
		{
			Active = Act0;
			Succ = Suc0;
		}
	};
	fact *Fact;

	class list
	{
	private:
		int Number;
	public:
		list *Next;
		list(int Num)
		{
			Number = Num;
			Next = NULL;
		}
		int GetNumber()
		{
			return Number;
		}
	};

	class rule
	{
		char *Name;
		list *Pre;
		int Conc;
	public:
		rule *Next;
		rule(char *N, int P[], int C);
		~rule();
		int Query();
		void GetName()
		{
			cout << Name;
		}
	};
	rule::~rule()
	{
		list *L;
		while (Pre)
		{
			L = Pre->Next;
			delete Pre;
			Pre = L;
		}
		delete Name;
	}
}
