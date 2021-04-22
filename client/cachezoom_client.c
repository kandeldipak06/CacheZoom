#define _GNU_SOURCE

#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/types.h>
#include <unistd.h>
#include "../kernel/cachezoom_kernel.h"


int main(int argc, char * argv[])
{

  if (argc < 2){
    printf("[X] No arguments provided!\n");
    return -1;
  }

  
  int _FD_;
  struct cachezoom_generic_param param;

  //open the device for reading and writing
  _FD_ = open("/dev/cachezoom", O_RDWR);
  if(_FD_ == -1){
    printf("Couldn't open /dev/cachezoom\n");
    return -1;
  }

  //OPEN_CACHEZOOM_DRV();
   
  int sw = atoi(argv[1]);

  switch(sw)
  {
    case 0:
      if (argc < 6){
        printf("[X] Not enough arguments provided!\n");
        return 1;
      }
      //strtoull converts the given string to unsigned
      //long long with base 16(passed as third argument)
      //lapic next deadline address
      param.param_0 = strtoull(argv[2], NULL, 16);

      //local_timer_interrupt handler address
      param.param_1 = strtoull(argv[3], NULL, 16);

      //timer interrupt value
      param.param_2 = atoi(argv[4]);

      //target cpu number
      param.param_3 = atoi(argv[5]);

      //call the ioctl with the setted parameter values
      if(ioctl(_FD_, CACHEZOOM_IOCTL_INIT, &param)) {
        printf("IOCTL failed %d\n", errno);
        return -1;
      }
      //INIT_CACHEZOOM(strtoull(argv[2], NULL, 16), strtoull(argv[3], NULL, 16), atoi(argv[4]), atoi(argv[5]));
      break;
    
    case 1:
      if(ioctl(_FD_, CACHEZOOM_IOCTL_INSTALL_TIMER, &param)) {
        printf("IOCTL failed %d\n", errno);
        return -1;
      }     
      //INSTALL_TIMER();
      break;
    
    case 2:
      if(ioctl(_FD_, CACHEZOOM_IOCTL_UNINSTALL_TIMER, &param)) {
        printf("IOCTL failed %d\n", errno);
        return -1;
      }
      //UNINSTALL_TIMER();
      break;
   
   case 3:
      if(ioctl(_FD_, CACHEZOOM_IOCTL_TEST, &param)) {
        printf("IOCTL failed %d\n", errno);
        return -1;
      }
      //TEST_CACHEZOOM();
      break;
    
    default:
      printf("Invalid switch.\n");
      return -1;
      break;
  }    
}
