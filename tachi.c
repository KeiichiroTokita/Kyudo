/*This program makes a "tachi-jun" in Kyudo matches.
We carry this out by indicating the name of the file which contains
information about members: name, grade, tomoyumi.

"./a.out 2017summer"
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define max_people 50

int make_memberslist(char *, int *, char **, int *, double *, char **);
void sorting(int, int, int *, char **, int *, double *, char **);

int main(int argc, char **argv)
{
  if(argc != 2){
    printf("Error : the number of variables\n");
    exit(1);
  }

  char *filename;
  filename = (char *)malloc(sizeof(char) * 30);
  strcpy(filename, argv[1]);

  int i, j;

  int * number; //通し番号
  char ** name; //氏名
  int * grade; //期
  double * seiseki; //的中数など
  char ** yumi; //共弓など

  number = (int *)malloc(sizeof(int) * max_people);
  name = (char **)malloc(sizeof(char*) * max_people);
  grade = (int *)malloc(sizeof(int) * max_people);
  seiseki = (double *)malloc(sizeof(double) * max_people);
  yumi = (char **)malloc(sizeof(char*) * max_people);
  for(i = 0; i < max_people; i++){
    name[i] = (char *)malloc(sizeof(char) * 20);
    yumi[i] = (char *)malloc(sizeof(char) * 20);
  }

  for(i = 0; i < max_people; i++){
    number[i] = 0;
    name[i][0] = '\0';
    grade[i] = 0;
    seiseki[i] = 0.0;
    yumi[i][0] = '\0';
  }

  int num_people;
  num_people = make_memberslist(filename, number, name, grade, seiseki, yumi);

  int syajo = 0;

  while(syajo != 1 && syajo != 2 && syajo != 3 && syajo != 4 && syajo != 5){
    printf("3人立で何射場使いますか？1から5の整数を入力し, Enterを押してください\n");
    scanf("%d", &syajo);
  }
  sorting(syajo, num_people, number, name, grade, seiseki, yumi);

  // calculate
  // return : tachi lists

  return 0;

}

int make_memberslist(char * filename, int * number, char ** name, int * grade, double * seiseki, char ** yumi)
{
  FILE *fp;
  fp = fopen(filename, "r");
  if(fp == NULL){
    printf("Error : no file\n");
    exit(1);
  }

  int i;

  char midashi[50];
  fscanf(fp, "%s", midashi);
//  printf("%s\n", midashi);

  i = 0;

  while( fscanf(fp, "%d, %[^,],%d, %lf, %s", &number[i], name[i], &grade[i], &seiseki[i], yumi[i]) != EOF ){
//    fprintf(stdout, "%d, %s, %d, %lf, %s\n", number[i], name[i], grade[i], seiseki[i], yumi[i]);
    i++;
  }

  int num_people = i;
  printf("the total number of people : %d\n", num_people);

  return num_people;
}

void sorting(int syajo, int num_people, int * number, char ** name, int * grade, double * seiseki, char ** yumi)
{
  int i, j;
  int num_3tachi, num_tachime;
  int tachi_3people, tachi_2people;

  num_3tachi = (num_people % 3 == 0 ? num_people / 3 : num_people / 3 + 1);
  num_tachime = (num_3tachi % syajo == 0 ? num_3tachi / syajo : num_3tachi / syajo + 1);

  tachi_3people = num_people - 2 * num_3tachi;
  tachi_2people = num_3tachi - tachi_3people;

  printf("3人立%d個, 2人立%d個\n", tachi_3people, tachi_2people);

  int tachi_ninzu[num_tachime + 1][syajo + 1];
  for(j = 0; j < num_tachime + 1; j++){
    for(i = 0; i < syajo + 1; i++){
      tachi_ninzu[j][i] = 0;
    }
  }
  for(i = 1; i < syajo + 1; i++){
    for(j = 1; j < num_tachime + 1; j++){
      if(tachi_3people > 0){
        tachi_ninzu[j][i] = 3;
        tachi_3people -- ;
      }else if(tachi_2people > 0){
        tachi_ninzu[j][i] = 2;
        tachi_2people -- ;
      }
    }
  }


  printf("    ");
  for(i = 0; i < syajo; i++){
    printf(" 第%d射場 ", i+1);
  }
  printf("\n");

  for(j = 1; j < num_tachime + 1; j++){
    printf("%d立目",j);
    for(i = 1; i < syajo + 1; i++){
      if(tachi_ninzu[j][i] != 0){
        printf("    %d    ", tachi_ninzu[j][i]);
      }
    }
    printf("\n");
  }









}
