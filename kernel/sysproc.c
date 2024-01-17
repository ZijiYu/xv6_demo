#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "sysinfo.h"

uint64 get_free_memory();
uint64 get_used_proc();


uint64
sys_exit(void)
{
  int n;
  if(argint(0, &n) < 0)
    return -1;
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  if(argaddr(0, &p) < 0)
    return -1;
  return wait(p);
}

uint64
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64
sys_trace(void){
  int mask; // exit();会有一个int的入参
  if(argint(0, &mask) < 0) // 它通常在内核的系统调用处理函数中使用，用于安全地获取用户空间传递给系统调用的参数
    return -1;
  else{
    struct proc *p = myproc();
    p->trace_mask = mask; 
  }
  return 0;
}

uint64
sys_sysinfo(void){
  uint64 addr; // user pointer to struct sysinfo
  struct proc *p = myproc();
  struct sysinfo info; 

  info.nproc = get_used_proc();
  info.freemem = get_free_memory();

  // printf("free memeory: %lu\n",info.freemem);
  // printf("used process: %lu\n",info.nproc);

  if(argaddr(0, &addr) < 0) // only one argument "a pointer to a struct sysinfo"
    return -1;

  if(copyout(p->pagetable, addr, (char *)&info, sizeof(info)) < 0) // < 0 mean copy fail (from kernel to user)
    return -1;
  return 0;
}

#ifdef LAB_PGTBL
int
sys_pgaccess(void)
{
  // lab pgtbl: your code here.

  int len;

  if(argint(0, &len) < 0){
    return -1;
  }

  uint64 addr;

  if(argaddr(1, &addr) < 0){
    return -1;
  }

  int bitmask;
  if(argint(2,&bitmask) < 0){
    return -1;
  }

  if(len>32) len = 32;

  int res = 0x1111;
  struct proc *p = myproc();
  for(int i = 0; i < len; i ++){
    int va = addr + i * PGSIZE;
    int abit = vm_pgaccess(p-> pagetable,va);
    res = res | abit << i;
  }
  // copyout(pagetable_t pagetable, uint64 dstva, char *src, uint64 len)
  if(copyout(p->pagetable, bitmask , (char *)&res, sizeof(len)) < 0){
    return -1;
  }
  return 0;
  return 0;
}
#endif
uint64
sys_ugetpid(void)
{
  // lab pgtbl: your code here.
  return myproc()->pid;
}
