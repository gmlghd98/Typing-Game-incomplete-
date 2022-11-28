#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 167303
#define WORD_SIZE 50

int count = 0;
char* max_words[7];

void timeover(int signum)
{
	printf("\n\ntime over!!\n\n");
	exit(0);
}

int Find_blank()
{
        int idx;
        for(idx = 0; idx < 7; idx++)
        {
                if(max_words[idx] == NULL)
                        return idx;
        }
        return 0;
}

void Insert_word(char* word)
{
	int idx;
	idx = Find_blank();
	max_words[idx] = (char*)malloc(sizeof(char) * WORD_SIZE);
        strcpy(max_words[idx], word);
	count++;
}

void Print_list()
{
	printf("\n[words]\n");

                for(int k = 0; k < 7; k++) {
                        if(max_words[k] == NULL)
                                continue;
                        else
                                printf("%s   ", max_words[k]);
                }
                printf("\n");
}

int main(void) {

	FILE* fp;
        char* string = (char*)malloc(sizeof(char) * WORD_SIZE);
	char* dict[SIZE];
	char* buf = (char*)malloc(sizeof(char) * WORD_SIZE);

        int i = 0;
	srand(time(0));

	for(int k = 0; k < 7; k++) // 개수 제한 배열 초기화
		max_words[k] = NULL;

        if((fp = fopen("/usr/share/dict/words", "r")) == NULL) {
                printf("fail to open file\n");
                return(0);
        }
        else {
                while(i != SIZE) {
                        dict[i] = (char*)malloc(sizeof(char) * WORD_SIZE);
                        fscanf(fp, "%s", string);
                        strcpy(dict[i], string);
			i++;
                }
        }
	
	int timelimit;
	struct sigaction act;

	act.sa_handler = timeover;
	sigaction(SIGALRM, &act, NULL);
	printf("input timelimit (sec): ");
	scanf("%d", &timelimit);
	
	alarm(timelimit);
	
	i = 0;
	int num;
	num = rand() % SIZE;
	Insert_word(dict[num]); // 초기에 단어 1개 삽입
	while(count != 8) {
		Print_list(); // 목록들 출력

		printf("START!!\n > ");
		scanf("%s", buf);
		for(int k = 0; k < 7; k++) { 
                        if(max_words[k] != NULL) {
                                if(!strcmp(buf, max_words[k])) {
                                        printf("success!\n");
                                        max_words[k] = NULL;
                                        break;
                                }
                                else {
                                        printf("try again!\n");
                                        num = rand() % SIZE;
                                        Insert_word(dict[num]);
                                        break;
                                }
                        }
                }
	}
	printf("words are more than 7\n"); // 단어 개수가 7개가 넘은 경우
	fclose(fp);
	return(0);
}	
