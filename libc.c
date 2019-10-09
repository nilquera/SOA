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
  if (errno == EBADF) write(1, "Bad file number\n", 16);
  else if (errno == EACCES) write(1, "Permission denied\n", 18);
  else if (errno == ENOSYS) write (1, "Function not implemented\n", 25);
  else if (errno == EINTR) write (1, "Interrupted system call\n", 24);
  else write (1, "Undefined error\n", 16); 
}
