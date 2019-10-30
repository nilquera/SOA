/*
 * libc.c 
 */

#include <libc.h>
#include <types.h>
#include <errno.h>

int errno;

void itoa(int a, char *b)
{
  int i, i1;
  char c;
  
  if (a==0) { b[0]='0'; b[1]=0; return ;}
  
  i=0;
  while (a>0)
  {
    b[i]=(a%10)+'0';
    a=a/10;
    i++;
  }
  
  for (i1=0; i1<i/2; i1++)
  {
    c=b[i1];
    b[i1]=b[i-i1-1];
    b[i-i1-1]=c;
  }
  b[i]=0;
}

int strlen(char *a)
{
  int i;
  
  i=0;
  
  while (a[i]!=0) i++;
  
  return i;
}

/*Printa por pantalla el error contenido en errno*/
/*Com tinc acces a la variable errno desde qualsevol arxiu si està declarada al .c i no al .h?*/
void perror(){ 
  char *buffer;
  if (errno == EBADF) buffer = "Bad file number\n";
  else if (errno == EACCES) buffer = "Permission denied\n";
  else if (errno == ENOSYS) buffer = "Function not implemented\n";
  else if (errno == EINTR) buffer = "Interrupted system call\n";
  else if (errno == ENOMEM) buffer = "Not enough core\n";
  else if (errno == ENULLPTR) buffer = "Null pointer detected\n";
  else if (errno == ESRCH) buffer = "No such process\n";
  else buffer = "Undefined error\n"; 
  write(1, buffer, strlen(buffer));
}
