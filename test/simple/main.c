#include <stdio.h>
#include <stdint.h>
#include "ring_buffer.h"
#include "ring_buffer_chapter.h"

//创建一个数组作为数据存储空间
#define BUFFER_SIZE 128
static uint8_t buffer[BUFFER_SIZE];

//创建环形缓冲区句柄
static ring_buffer rb;

//创建两个数组，一个作为数据存储空间，一个用于记录分段信息
#define BASE_SIZE 128
static uint8_t buffer_base[BASE_SIZE];
#define CHAPTER_SIZE 16
static uint32_t buffer_chapter[CHAPTER_SIZE];

//创建分段环形缓冲区句柄
static ring_buffer_chapter rbc;

int main(int argc, void ** argv)
{
    //初始化环形缓冲区参数
    RB_Init(&rb, buffer, BUFFER_SIZE);

    //写入向环形缓冲区写入数据
    RB_Write_String(&rb, "hello world", 11);
    RB_Write_Byte(&rb, '!');
    RB_Write_Byte(&rb, 0x00);

    //删除环形缓冲区部分数据
    RB_Delete(&rb, 2);

    //获取已储存的数据长度
    uint32_t num = RB_Get_Length(&rb);

    //读出环形缓冲区中的数据并打印
    uint8_t get[16];
    RB_Read_String(&rb, get, num);
    printf("%s\r\n", get);
    
    //初始化分段环形缓冲区参数
    RBC_Init(&rbc, buffer_base, BASE_SIZE, buffer_chapter, CHAPTER_SIZE);

    //写入向环形缓冲区写入数据1，并记录分段结尾
    RBC_Write_String(&rbc, "string1", 7);
    RBC_Write_Byte(&rbc, '!');
    RBC_Write_Byte(&rbc, 0x00);
    RBC_Ending_Chapter(&rbc);

    //写入向环形缓冲区写入数据2，并记录分段结尾
    RBC_Write_String(&rbc, "string2", 7);
    RBC_Write_Byte(&rbc, '!');
    RBC_Write_Byte(&rbc, 0x00);
    RBC_Ending_Chapter(&rbc);

    //获取已储存的分段数量
    num = RBC_Get_Chapter_Number(&rbc);

    //读出环形缓冲区中的数据并打印
    for (uint32_t i = 0; i < num; i++)
    {
        RBC_Read_Chapter(&rbc, get, NULL);
        printf("%s\r\n", get);
    }
    
    return 0;
}

