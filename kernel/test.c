#include <stdio.h>

static void attack_handler(void){
  int a = 3;
  return a;
}

static void attack_handler2(void){
  int a = 4;
  return a;
}

int main(){
  unsigned int target_addr;
  unsigned char call_stub[] = {0xe8, 0xf1, 0xf2, 0xf3, 0xf4};

  target_addr = attack_handler;  
  call_stub[1] = ((char*)&target_addr)[0];
  call_stub[2] = ((char*)&target_addr)[1];
  call_stub[3] = ((char*)&target_addr)[2];
  call_stub[4] = ((char*)&target_addr)[3];
  printf("%p\n%p",call_stub, target_addr);

}

