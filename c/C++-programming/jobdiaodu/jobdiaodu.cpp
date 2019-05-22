#include<stdio.h>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

struct JCB {
	char name[10];
	int comet;
	int needt;
	int sourceid;
	int status;//0 ��ʾ�ȴ�,1��ʾ���У�2��ʾ����
	int sf;
	int waitt;//�Ѿ��ȴ���ʱ��
	//JCB* next;

	bool operator> (const JCB& a) const
	{
		if(sf==1)
			if (comet != a.comet)
				return comet > a.comet;
			else
			{
				cout << "ͬʱ����,����.*****************************" << endl;
				return false;
			}
		else if(sf==2)
			if (needt != a.needt) {
				return needt > a.needt;
			}
			else
			{
				if (comet != a.comet)
					return comet > a.comet;
				else
				{
					cout << "����ʱ��һ��������ͬʱ�������.*****************" << endl;
					return false;
				}
			}
		else if (sf == 3) 
		{
			int hrn = (waitt + needt) / needt;
			int hrna = (a.waitt + a.needt) / a.needt;
			if (hrn != hrna) 
			{
				return hrn > hrna;
			}
			else
			{
				if (needt != a.needt)
					return needt > a.needt;
				else 
				{
					cout << "�����Ӧ����ͬ��������ҵһ����������.*************" << endl;
					return false;
				}
			}
		}
		else {
			cout << "��ʱ���ж���������";
		}
	}
};

bool Comp(JCB& a, JCB& b) {
	return a > b;
}

void show(JCB& a) {
	cout << "\t" << a.waitt + a.comet << "\t" << a.waitt + a.comet + a.needt << "\t" << a.waitt + a.needt << endl;
}

void showJCB(JCB& a) {
	cout << a.name << "\t" << a.comet << "\t" << a.needt << "\t" << a.sourceid << "\t" << a.status << "\t" << a.sf << "\t" << a.waitt << endl;
}

int main()
{
	vector<JCB> vecw,vecf;
	int n = 0;
	int sf ;
	cout << "ѡ�����ַ��� (1��ʾ FCFS �� 2��ʾSJF�� 3 ��ʾHRN):" << endl;
	cin >> sf;
	JCB jcb;
	cout << "������ҵ����:" << endl;
	cin >> n;
	cout << "��ҵ����Ϊ" << n << endl;
	for (int i = 0; i < n; i++) 
	{
		cout << "�����" << i+1 << "����ҵ��" << "��ҵ��(���Ȳ�����9)" << endl;
		cin >> jcb.name;
		cout << "�����" << i+1 << "����ҵ��" << "����ʱ��(����)" << endl;
		cin >> jcb.comet;
		cout << "�����" << i+1 << "����ҵ��" << "��Ҫ��ʱ��(����)" << endl;
		cin >> jcb.needt;
		cout << "�����" << i+1 << "����ҵ��" << "��Ҫ����Դ(����)" << endl;
		cin >> jcb.sourceid;
		jcb.status = 0;
		jcb.sf = 1;
		jcb.waitt = 0;
		vecw.push_back(jcb);
	}
	//vector<JCB>::iterator jhead = vec.begin();
	sort(vecw.begin(), vecw.end(), Comp);//�Ȱ���fcfs�Ŷ� ��������
	int ct = vecw[vecw.size()-1].comet;//ct ��ʾ��ǰʱ�� Ҳ���ǵ�һ����ҵ�����ʱ��
	for (int i = 0; i < n; i++)
	{
		vecw[i].waitt = vecw[i].comet - ct;
		vecw[i].sf = sf;
	}
	JCB temp = vecw[vecw.size() - 1];//�����������ǵ�һ������������ ���Ե�һ������һ���Ƕ�β
	vecw.pop_back();
	sort(vecw.begin(), vecw.end(), Comp);//���°���ѡ�񷽷��Ŷ� ��������
	vecw.push_back(temp);
	for (int i = 0; i < vecw.size(); i++)
		showJCB(vecw[i]);
	int sumzhouzhuan = 0, sumdaiquan = 0;
	while (vecw.size()!=0)
	{
		if (vecw[vecw.size() - 1].comet >= ct)//���ȴ��б����һ��δ����ʱ
		{
			for (int i = 0; i < vecw.size(); i++) {
				vecw[i].sf = 1;
			}
			sort(vecw.begin(), vecw.end(), Comp);//�ٴ���FCFS����
			JCB temp = vecw[vecw.size() - 1];//�����������ǵ�һ������������ ���Ե�һ������һ���Ƕ�β
			vecw.pop_back();
			sort(vecw.begin(), vecw.end(), Comp);//���°���ѡ�񷽷��Ŷ� ��������
			vecw.push_back(temp);
			for (int i = 0; i < vecw.size(); i++) {
				vecw[i].sf = sf;
			}
		}
		JCB run = vecw[vecw.size() - 1];//�ѵ�ǰ���е����һ������
		if(ct<run.comet)
			ct = run.comet;
		vecw.pop_back();//ɾ���ȴ������еĸ�Ԫ��
		run.waitt = ct - run.comet;//��ǰ��ҵ�ĵȴ�ʱ��Ϊ��ǰʱ���ȥ������ʱ��
		run.status = 3;//��ǰ��ҵ���δ���
		vecf.push_back(run);//����ɵļ��뵽��ɶ���
		cout << "��ҵ" << run.name << endl;
		sumdaiquan = sumdaiquan + (run.waitt + run.needt) / run.needt;
		sumzhouzhuan = sumzhouzhuan + (run.waitt + run.needt);
		cout << "��ʼʱ��" << ct << "\t���ʱ��" << ct + run.needt << "\t��תʱ��" << run.waitt + run.needt << "\t��Ȩ��תʱ��" << (run.waitt + run.needt) / run.needt << endl;
		ct = ct + run.needt;//��ǰ��ҵ������ʱ��Ϊ��ǰʱ��
	}
	cout << endl << "ƽ����תʱ��" << sumzhouzhuan / n << "\t ƽ����Ȩ��תʱ��" << sumdaiquan / n << endl;
}

