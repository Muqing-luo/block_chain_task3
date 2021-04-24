#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "c:\block_chain\sha256.h"
#include "mining.h"

#define N0 8  //�궨��hash��ͷ��N0��2����0 

int main(void)
 {
	int i,j;
	unsigned char hash[32]={0}; //��hash����ֵ
	BLOCK *pre,*h;//����ָ�� 
	SHA256_CTX ctx;
	sha256_init(&ctx);
	
	for(i=0;i<10;i++)//����10������ 
	{
		BLOCK *block=(BLOCK *)malloc(sizeof(BLOCK));//������ڴ�����ѭ���Դ��� 
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
		fwrite(block,blockBytes,1,fp);//ÿ��������Ϣ�洢���������ļ� block->next���棬������ 	
		fclose(fp);
		
		if(i==0)//��Ŀ��Ϊ��һ������ 
		{
			h=block;//��¼��ͷ��ַ 
			pre=block;
			continue;  
		}
		pre->next=block;//���������������һ�������¼�������ַ 
		pre=block;//�����µ������ַ����prehash 
	} 
	pre->next=NULL;
	return 0;
	system("pause");
}
