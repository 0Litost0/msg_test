/*****************************************************************
@简介：存放程序运行所需的一些头文件，函数或结构体声明等
****************************************************************/
#ifndef _COMMON_H_
#define _COMMON_H_
/**************************INCLUDE_FILE***********************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <time.h>
#include "common.h"
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include<sys/types.h>
/**************************DEFINE*****************************************/
// 用于创建一个唯一的key
#define MSG_FILE "/etc/passwd"
#define IPC_READ_KEY 0x00
#define IPC_WRITE_KEY 0x01


#define MAX_MSG_SIZE 128

/**************************STRUCT_DECELARATION****************************/	
// 消息结构
struct msg_form {
	long mtype;
	char mtext[MAX_MSG_SIZE];
};
	

/**************************GLOBAL_VAR**********************************/	

/**************************ENUM_DECELARATION**********************************/	
enum COMMUNICATION_PROTOCAL
{
	COMMUNICATION_PROTO_1 = 1,
	COMMUNICATION_PROTO_2
};

#endif

