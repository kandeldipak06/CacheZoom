sudo sh configure_os.sh   #run configure_os.sh
rm -rf data/*.data
cd kernel && make clean && make  #build the kernel module
sudo rmmod cachezoom_kernel      #remove the module from computer
sudo insmod cachezoom_kernel.ko  #load the kernel module to the computer
cd ../client 
make clean && make
#bind the process to cpu proceessor 0   -- taskset -c 0 
#/proc/kallsyms holds the address of exported symbols of kernel ie global variables
sudo ./cachezoom 0 `sudo cat /proc/kallsyms | grep "t lapic_next_deadline" | awk '{print $1}'` `sudo cat /proc/kallsyms | grep "T apic_timer_interrupt" | awk '{print $1}'` 4815 1
sudo ./cachezoom 1