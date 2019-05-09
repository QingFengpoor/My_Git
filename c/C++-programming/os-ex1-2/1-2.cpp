/*
 *利用C/C++模拟进程调度,运用轮转时间片调度算法
 */
#include<stdio.h>
#include<malloc.h>
#include<iostream>
enum process_status { READY, RUN, FINISH }; //进程的三种状态
//定义进程数据结构
typedef struct pcb
{
	char process_tag[20]; //存储进程标识符
	struct pcb* next; //连接下一个进程的指针
	int time_slice; // 轮转调度算法中为轮转时间片 分配到的时间片数
	int take_cpu_time=0; //占用CPU时间片数
	int process_time; //进程所需时间片数
	process_status status; //进程当d前的状态
} PCB;
//定义进程控制块的链结构
typedef struct
{
	PCB* run; //当前运行的进程指针
	PCB* ready; //当前准备队列的头指针
	PCB* tail; //准备队列的队尾指针
	PCB* finish; //完成队列的指针
} PCBC;
void init_pcbc(PCBC* p)
{
	p->run = NULL;
	p->ready = NULL;
	p->tail = NULL;
	p->finish = NULL;
}
//输入进程，并加入就绪队列
void input_process(PCBC* pcbc)
{
	PCB* pcb;
	pcb = (PCB*)malloc(sizeof(PCB));
	printf("请输入进程标识符：");
	std::cin>>pcb->process_tag;
	printf("输入格式为： （分配CPU时间片数，进程所需时间片数） : ");
	scanf_s("%d,%d", &pcb->time_slice, &pcb->process_time);
	pcb->status = READY; //初始化就绪状态
	//当就绪队列为空时
	if (pcbc->ready == NULL && pcbc->tail == NULL)
	{
		pcbc->ready = pcbc->tail = pcb;
		pcb->next = NULL;
	}
	else
	{
		//将新进入的元素加入队尾
		pcb->next = pcbc->tail->next;
		pcbc->tail->next = pcb;
		pcbc->tail = pcb;
	}
}
/*
 *打印当前进程控制块中的情况
 */
void print_log(PCBC* pcbc)
{
	PCB* ready, * finish;
	ready = pcbc->ready;
	finish = pcbc->finish;
	printf("--------------------------------------------------  \n");
	printf("Run： \n");
	if (pcbc->run != NULL)
	{
		printf("%s  %04d  %04d  %04d \n", pcbc->run->process_tag, pcbc->run->time_slice, pcbc->run->take_cpu_time, pcbc->run->process_time);
	}
	else
	{
		printf("Run is empty! \n");
	}
	printf("Ready：\n");
	while (ready != NULL)
	{
		printf("%s  %04d  %04d  %04d \n", ready->process_tag, ready->time_slice, ready->take_cpu_time, ready->process_time);
		ready = ready->next;
	}
	printf("Finish：\n");
	while (finish != NULL)
	{
		printf("%s  %04d  %04d  %04d \n", finish->process_tag, finish->time_slice, finish->take_cpu_time, finish->process_time);
		finish = finish->next;
	}
}
/*
 *通过轮转时间片调度算法
 */
void run_pcbc_timeSlice(PCBC* xpcbc)
{
	PCBC* pcbc = xpcbc;
	PCB* temp, * pre, * tail;
	//进行那个CPU的循环调用
	while (pcbc->ready != NULL)
	{
		pcbc->run = pcbc->ready; //将就绪队列队首加入运行队列
		pcbc->ready = pcbc->ready->next; //改变队首元素
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
			if (pcbc->run->time_slice == pcbc->run->take_cpu_time) //占用CPU时间片数到
			{
				//将其加入队尾
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
	PCBC* pcbc; //创建进程控制块链 ;
	int pcb_num; //记录处理进程数目
	pcbc = (PCBC*)malloc(sizeof(PCBC));
	printf("请输入要处理的进程数目： ");
	scanf_s("%d", &pcb_num);
	init_pcbc(pcbc); //初始化进程控制块链
	for (int i = 0; i < pcb_num; i++)
	{
		input_process(pcbc); //输入所有进程，并进入就绪队列
	}
	//通过时间片轮转调度算法
	printf("By the time slice------------------------\n");
	run_pcbc_timeSlice(pcbc);
	return 0;
}
