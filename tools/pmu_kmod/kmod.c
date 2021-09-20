#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>

static void enable_cpu_counters(void* data)                                                                         
{                                                                                                       
    asm volatile("msr pmuserenr_el0, %0" :: "r"(0xf));
//    armv8pmu_pmcr_write (ARMV8_PMCR_LC|ARMV8_PMCR_E);                                                      
    asm volatile("msr PMCNTENSET_EL0, %0" :: "r" ((u32)(1<<31)));
//    armv8pmu_pmcr_write(armv8pmu_pmcr_read() | ARMV8_PMCR_E|ARMV8_PMCR_LC);   
    printk("\nCPU:%d \n", smp_processor_id());
}                                                                                                       

static void disable_cpu_counters (void* data)                                                                        
{                                                                                                                                                                                                   
    printk(KERN_INFO "\ndisabling user-mode PMU access on CPU #%d \n",                       
    smp_processor_id());
    /* Program PMU and disable all counters */                                                            
//    armv8pmu_pmcr_write(armv8pmu_pmcr_read() |~ARMV8_PMCR_E);                                              
    asm volatile("msr pmuserenr_el0, %0" ::"r"((u64)0));                                                 
}                                                                                                       

static int __init init(void)                                                                                              
{
    unsigned int reguser=0;     

    isb();

    asm volatile("mrs %0, pmcr_el0" : "=r" (reguser));
    printk(KERN_INFO "\nPMCR_EL0 register before : %x\n", reguser);
    asm volatile("mrs %0, pmuserenr_el0" : "=r" (reguser));
    printk(KERN_INFO "\nPMUSERENR register before : %x\n", reguser);

    on_each_cpu (enable_cpu_counters, NULL, 1);                                                             
    printk(KERN_INFO "\nEnable Access PMU Initialized\n");

    /* Enable counters */
    asm volatile("mrs %0, pmcr_el0" : "=r" (reguser));
    printk(KERN_INFO "\nPMCR_EL0 register after : %x\n", reguser);
    asm volatile("mrs %0, pmuserenr_el0" : "=r" (reguser));
    printk(KERN_INFO "\nPMUSERENR register after : %x\n", reguser);

    return 0;                                                                                              
}                                                                                                       

static void __exit fini(void)                                                                                              
{                                                                                                       
    on_each_cpu(disable_cpu_counters, NULL, 1);                                                            
    printk(KERN_INFO "\nAccess PMU Disabled\n");                                                          
}                                                                                                       

module_init (init);                                                                                      
module_exit (fini);

MODULE_LICENSE("Dual BSD/GPL");
