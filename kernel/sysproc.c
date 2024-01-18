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
pte_t *
walk(pagetable_t pagetable, uint64 va, int alloc);

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
// int
// sys_pgaccess(void)
// {
//   // lab pgtbl: your code here.

//   int len;
//   uint64 addr;
//   int bitmask;
//   if(argint(0, &len) < 0){
//     return -1;
//   }

//   if(argaddr(1, &addr) < 0){
//     return -1;
//   }

//   if(argint(2,&bitmask) < 0){
//     return -1;
//   }

//   if(len>32) len = 32;

//   int res = 0;
//   struct proc *p = myproc();
//   for(int i = 0; i < len; i ++){
//     int va = addr + i * PGSIZE;
//     int abit = vm_pgaccess(p-> pagetable,va);
//     res = res | abit << i;
//   }
//   // copyout(pagetable_t pagetable, uint64 dstva, char *src, uint64 len)
//   if(copyout(p->pagetable, bitmask , (char *)&res, sizeof(res)) < 0){
//     return -1;
//   }
//   return 0;
// }

int sys_pgaccess(void)
{
  uint64 st;
  argaddr(0,&st);//获取user page虚拟地址
  char *buf = (char*)st;
  int len = 0;
  argint(1,&len);//获取要check的页数
  if(len > 32)len = 32;//限制check最大页数
  unsigned int abits = 0;//存储位掩码
  for(int i = 0; i < len; i++){
    pte_t *pte = walk(myproc()->pagetable, (uint64)buf+PGSIZE * i, 0);//获取最下级页表表项
    // (+PGSIZE*i)起到换页的效果
    if(*pte & PTE_A){
    	*pte &= ~PTE_A;//清除PTE_A
    	abits |= (1 << i);//获取位掩码
    }
  }
  argaddr(2,&st);//获取缓冲区的地址
  if(copyout(myproc()->pagetable, st, (char *)&abits, sizeof(abits)) < 0)//将位掩码拷贝到用户缓冲区
    return -1;
  return 0;
}

#endif
uint64
sys_ugetpid(void)
{
  // lab pgtbl: your code here.
  return myproc()->pid;
}
