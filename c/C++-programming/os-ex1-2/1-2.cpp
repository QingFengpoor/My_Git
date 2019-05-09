/*
 *����C/C++ģ����̵���,������תʱ��Ƭ�����㷨
 */
#include<stdio.h>
#include<malloc.h>
#include<iostream>
enum process_status { READY, RUN, FINISH }; //���̵�����״̬
//����������ݽṹ
typedef struct pcb
{
	char process_tag[20]; //�洢���̱�ʶ��
	struct pcb* next; //������һ�����̵�ָ��
	int time_slice; // ��ת�����㷨��Ϊ��תʱ��Ƭ ���䵽��ʱ��Ƭ��
	int take_cpu_time=0; //ռ��CPUʱ��Ƭ��
	int process_time; //��������ʱ��Ƭ��
	process_status status; //���̵�dǰ��״̬
} PCB;
//������̿��ƿ�����ṹ
typedef struct
{
	PCB* run; //��ǰ���еĽ���ָ��
	PCB* ready; //��ǰ׼�����е�ͷָ��
	PCB* tail; //׼�����еĶ�βָ��
	PCB* finish; //��ɶ��е�ָ��
} PCBC;
void init_pcbc(PCBC* p)
{
	p->run = NULL;
	p->ready = NULL;
	p->tail = NULL;
	p->finish = NULL;
}
//������̣��������������
void input_process(PCBC* pcbc)
{
	PCB* pcb;
	pcb = (PCB*)malloc(sizeof(PCB));
	printf("��������̱�ʶ����");
	std::cin>>pcb->process_tag;
	printf("�����ʽΪ�� ������CPUʱ��Ƭ������������ʱ��Ƭ���� : ");
	scanf_s("%d,%d", &pcb->time_slice, &pcb->process_time);
	pcb->status = READY; //��ʼ������״̬
	//����������Ϊ��ʱ
	if (pcbc->ready == NULL && pcbc->tail == NULL)
	{
		pcbc->ready = pcbc->tail = pcb;
		pcb->next = NULL;
	}
	else
	{
		//���½����Ԫ�ؼ����β
		pcb->next = pcbc->tail->next;
		pcbc->tail->next = pcb;
		pcbc->tail = pcb;
	}
}
/*
 *��ӡ��ǰ���̿��ƿ��е����
 */
void print_log(PCBC* pcbc)
{
	PCB* ready, * finish;
	ready = pcbc->ready;
	finish = pcbc->finish;
	printf("--------------------------------------------------  \n");
	printf("Run�� \n");
	if (pcbc->run != NULL)
	{
		printf("%s  %04d  %04d  %04d \n", pcbc->run->process_tag, pcbc->run->time_slice, pcbc->run->take_cpu_time, pcbc->run->process_time);
	}
	else
	{
		printf("Run is empty! \n");
	}
	printf("Ready��\n");
	while (ready != NULL)
	{
		printf("%s  %04d  %04d  %04d \n", ready->process_tag, ready->time_slice, ready->take_cpu_time, ready->process_time);
		ready = ready->next;
	}
	printf("Finish��\n");
	while (finish != NULL)
	{
		printf("%s  %04d  %04d  %04d \n", finish->process_tag, finish->time_slice, finish->take_cpu_time, finish->process_time);
		finish = finish->next;
	}
}
/*
 *ͨ����תʱ��Ƭ�����㷨
 */
void run_pcbc_timeSlice(PCBC* xpcbc)
{
	PCBC* pcbc = xpcbc;
	PCB* temp, * pre, * tail;
	//�����Ǹ�CPU��ѭ������
	while (pcbc->ready != NULL)
	{
		pcbc->run = pcbc->ready; //���������ж��׼������ж���
		pcbc->ready = pcbc->ready->next; //�ı����Ԫ��
		print_log(pcbc);
		pcbc->run->take_cpu_time += 1;
		pcbc->run->process_time -= 1;
		if (pcbc->run->process_time == 0)
		{
			if (pcbc->finish == NULL)
			{
				pcbc->finish = pcbc->run;
				pcbc->finish->next = NULL;
				tail = pcbc->finish;
			}
			else
			{
				tail = new pcb;
				tail->next = pcbc->run;
				tail = tail->next;
				tail->next = NULL;
			}
		}
		else
		{
			if (pcbc->run->time_slice == pcbc->run->take_cpu_time) //ռ��CPUʱ��Ƭ����
			{
				//��������β
				pcbc->run->take_cpu_time = 0;
				pcbc->run->next = NULL;
				pcbc->tail->next = pcbc->run;
				pcbc->tail = pcbc->run;
				if (pcbc->ready == NULL)
				{
					pcbc->ready = pcbc->tail;
					pcbc->ready->next = NULL;
				}
			}
			else
			{
				pcbc->run->next = pcbc->ready;
				pcbc->ready = pcbc->run;
			}
		}
	}
	pcbc->run = NULL;
	print_log(pcbc);
}
int main()
{
	PCBC* pcbc; //�������̿��ƿ��� ;
	int pcb_num; //��¼���������Ŀ
	pcbc = (PCBC*)malloc(sizeof(PCBC));
	printf("������Ҫ����Ľ�����Ŀ�� ");
	scanf_s("%d", &pcb_num);
	init_pcbc(pcbc); //��ʼ�����̿��ƿ���
	for (int i = 0; i < pcb_num; i++)
	{
		input_process(pcbc); //�������н��̣��������������
	}
	//ͨ��ʱ��Ƭ��ת�����㷨
	printf("By the time slice------------------------\n");
	run_pcbc_timeSlice(pcbc);
	return 0;
}
