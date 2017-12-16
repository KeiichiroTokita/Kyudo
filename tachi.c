/*This program makes a "tachi-jun" in Kyudo matches.
We carry this out by indicating the name of the file which contains
information about members: name, grade, tomoyumi.

"./a.out 2017summer"
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define max_people 50

void make_memberslist(char[]);

int main(int argc, char **argv)
{
  if(argc != 2){
    printf("Error : the number of variables\n");
    exit(1);
  }

  char filename[30];
  strcpy(filename, argv[1]);

  make_memberslist(filename);

  // calculate
  // return : tachi lists

  return 0;

}

void make_memberslist(char filename[])
{
  FILE *fp;
  fp = fopen(filename, "r");
  if(fp == NULL){
    printf("Error : no file\n");
    exit(1);
  }

  int i;

  int number[max_people];
  char name[max_people][20];
  int grade[max_people]; //期
  double seiseki[max_people];
  char yumi[max_people][20];

  for(i = 0; i < max_people; i++){
    number[i] = 0;
    name[i][0] = '\0';
    grade[i] = 0;
    seiseki[i] = 0.0;
    yumi[i][0] = '\0';
  }

  char midashi[20];
  fscanf(fp, "%s", midashi);
  printf("%s\n", midashi);

  i = 0;

  while( fscanf(fp, "%d, %[^,],%d, %lf, %s", &number[i], name[i], &grade[i], &seiseki[i], yumi[i]) != EOF ){
    fprintf(stdout, "%d, %s, %d, %lf, %s\n", number[i], name[i], grade[i], seiseki[i], yumi[i]);
    i++;
  }

  int num_people = i;
  printf("the total number of people : %d\n", num_people);

  return;
}
