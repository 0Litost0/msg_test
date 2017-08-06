/*****************************************************************
@简介：该程序负责创建串口数据发送以及接收进程，同时负责创建相关消息队列
****************************************************************/
/**************************INCLUDE_FILE***********************************/
#include "server.h"

/**************************DEFINE*****************************************/

/**************************STRUCT_DECELARATION****************************/	

/**************************GLOBAL_VAR**********************************/	


int main (int argc, char * argv[])
{
	char path[256];
	key_t read_msg_key = 0;
	key_t write_msg_key = 0;
	int read_msg_id = 0;
	int write_msg_id = 0;
	struct msg_form msg;
	sprintf(path, "%s/etc/config.ini", (char*)getenv("HOME") );

	//创建子进程
	pid_t pid = 0;
	if ((pid = fork()) < 0)
	{
		perror("fork failed\n");
		exit (1);	
	}
	else if (0 == pid)
	{
		if ((pid = fork()) < 0)
		{
			perror("fork failed!\n");
			exit(1);
		}
		else if (pid > 0)
		{
			exit(0);
		}
		else	//创建的第二个子进程，该类进程在其父进程结束后，将被init进程收养
		{
			printf(" WRITE SERVICE PROCESS PID:%d\n", pid);
			//执行其他程序
			if ((write_msg_key = ftok( path, IPC_WRITE_KEY)) < 0)
			{
				perror("write_msg_key ftok error\n");
				exit(2);
			}
			if ((write_msg_id = msgget(write_msg_key, IPC_CREAT|0777)) == -1)
			{
				perror("write_msg_id msgget error\n");
				exit(1);
			}	
			printf("write_msg_id is: %d\n", write_msg_id);		

        
			while(1)
			{
				//从write_msg_id队列中顺序获取消息，并通过串口进行发送（现阶段将其打印到标准输出）
				if (msgrcv(write_msg_id, &msg, sizeof(msg.mtext), 0, 0) != -1)
				{
					printf("send data to serial:%s\n", msg.mtext);
				}				
			}
			exit(0);
		}
	}
	if (waitpid(pid, NULL, 0) != pid)
	{
		printf("waitpid error!\n");
		exit(1);
	}

	
	printf(" READ SERVICE PROCESS PID:%d\n", getpid());
	//执行其他程序
	//这些消息队列的创建，我觉得可以放在进程创建成功之后

	if ((read_msg_key = ftok( path, IPC_READ_KEY )) < 0)
	{	
		perror("read_msg_key ftok error\n");
		exit(2);		
	}
	if ((read_msg_id = msgget(read_msg_key, IPC_CREAT|0777)) == -1)
	{
		perror("read_msg_id msgget error\n");
		exit(1);
	}	
	printf("read_msg_id is: %d\n", read_msg_id);

	

	// 循环读取消息,并将数据放入读取队列
	for(;;) 
	{
		time_t tp;
		sleep(2);
		//交叉向read_msg队列写入两种类型的消息
		time(&tp);
		sprintf(msg.mtext,"The msg from commu_protocal:%d,Time:%s\n",COMMUNICATION_PROTO_1, ctime(&tp));
		msgsnd(read_msg_id, &msg, sizeof(msg.mtext), 0);
		sleep(2);
		//交叉向read_msg队列写入两种类型的消息
		time(&tp);
		sprintf(msg.mtext,"The msg from commu_protocal:%d,Time:%s\n",COMMUNICATION_PROTO_2, ctime(&tp));
		msgsnd(read_msg_id, &msg, sizeof(msg.mtext), 0);	
	}
	exit(0);



}


