#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "c:\block_chain\sha256.h"
#include "mining.h"

#define N0 8  //宏定义hash开头有N0个2进制0 

int main(void)
 {
	int i,j;
	unsigned char hash[32]={0}; //给hash赋初值
	BLOCK *pre,*h;//区块指针 
	SHA256_CTX ctx;
	sha256_init(&ctx);
	
	for(i=0;i<10;i++)//创造10个区块 
	{
		BLOCK *block=(BLOCK *)malloc(sizeof(BLOCK));//分配的内存跳出循环仍存在 
		puts("creating new block:\n");
		Block_init(block,hash); 
		Mining(&ctx,block,hash,N0); 
		printf("\ninfo of %d th block:\n",i+1);
		print_block(block);
		printf("hash:\n");
		for(j=0;j<32;j++)
			printf("%x ",hash[j]);
		puts("\n");
		
		char s[]="blockchain_data/block";
		char n[4];
		itoa(i+1,n,10);
		strcat(s,n);
		FILE *fp=fopen(s,"wb");
		if(fp==NULL)
		{
		printf("can't open the file\n");
		exit(0);
		}
		fwrite(block,blockBytes,1,fp);//每个区块信息存储到二进制文件 block->next不存，无意义 	
		fclose(fp);
		
		if(i==0)//当目标为第一个区块 
		{
			h=block;//记录链头地址 
			pre=block;
			continue;  
		}
		pre->next=block;//新区块加入链，上一个区块记录新区块地址 
		pre=block;//用最新的区块地址更新prehash 
	} 
	pre->next=NULL;
	return 0;
	system("pause");
}
