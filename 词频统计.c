#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 27 //26个字母和'
//字典树的结构体定义
typedef struct Word
{
Word *next[MAX]; //数组下标0-25代表小写字母,26'
int num;
};
//结构体定义:单词和对应频率
typedef struct tlist
{
char word[200];
int time;
};
struct tlist list[3000000];
Word *root;
char str[200]="";
char tempword[1000];
int size=0;
//新建单词的函数
void createWord(char *str)
{
int len = strlen(str), id;
Word *p = root, *q;
for(int i = 0; i < len; i ++)//遍历单词判断当前字符是否为字母或'
{
if(str[i] >= 'a' && str[i] <= 'z')
id = str[i] - 'a';
if(str[i] >= 'A' && str[i] <= 'Z')
id = str[i] - 'A';
if(str[i] == '\'')
id = 26;
if(p->next[id] == NULL)//若已到达链表结尾,开辟新的结构体存入字母
{
q = (Word *)malloc(sizeof(Word));
for(int j = 0; j < MAX; j ++)
{q->num=0;q->next[j] = NULL;}
p->next[id] = q;
p = p->next[id];
}
else//若未到达链表结尾,指针指向下一个
{
p = p->next[id];
}
}
p->num++;
}
//读单词的函数
void readWord(Word *p,int len)
{
int i;
for(i=0;i<27;i++)
{
if(p->next[i]!=NULL)
{
if (i==26)
{str[len+1]='\0';str[len]='\'';len++;}
else
{
str[len]='a'+i;
len++;
}
readWord((Word*)p->next[i],len);
len--;
}
}
if(p->num!=0)
{
str[len]='\0' ;
strcpy(list[size].word,str); //如果遇到单词结束标志,将str存入list[size].word
list[size].time=p->num;
size++;
}
}
//主程序
int main()
{
root=(Word*)malloc(sizeof(Word));
int i,j;
for (i=0;i<27;i++) root->next[i]=NULL;
FILE *fp;
char x;
int len=0;
fp=fopen("text.txt","r");
while((x=fgetc(fp))!=EOF) //从txt文档中读入
{
if ((x>='A'&&x<='Z')||(x>='a'&&x<='z')||(x=='\''&&len!=0))
{tempword[len]=x;len++;}
else {tempword[len]='\0';
createWord(tempword);
len=0;
}
}
tempword[len]='\0';
createWord(tempword);
len=0;
fclose(fp);
readWord(root,0);
//比较频率大小冒泡排序
struct tlist temp;
for(i=0;i<size-1;i++)
for(j=i+1;j<size;j++)
if(list[i].time>list[j].time||(list[i].time==list[j].time&&strcmp(list[i].word,list[j].word)>0)) {
temp.time=list[i].time;
list[i].time=list[j].time;
list[j].time=temp.time;
strcpy(temp.word,list[i].word);
strcpy(list[i].word,list[j].word);
strcpy(list[j].word,temp.word);
}
//将单词和对应频率输出到result.txt中
FILE *fpx;
fpx=fopen("result.txt","w");
for (i=0;i<size;i++) fprintf(fpx,"%s %d\n",list[i].word,list[i].time);
fclose(fpx);
return 0;
}