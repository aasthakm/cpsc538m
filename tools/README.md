# Cache Attacks

This repository contains several libraries and tools to perform cache-attacks on
x86 and arm devices. The original source of these libraries and tools can be found [here](https://github.com/IAIK/armageddon), which were developed and utilized in the [Cache Template Attacks](https://www.usenix.org/system/files/conference/usenixsecurity15/sec15-paper-gruss.pdf) and [ARMageddon: Cache Attacks on Mobile Devices](https://www.usenix.org/conference/usenixsecurity16/technical-sessions/presentation/lipp) papers.


### Repository Content

| Directory  | Description |
| -------- | ------------- |
| [libflush](libflush) | Library to build cross-platform cache attacks |
| [cache\_template\_attacks](cache_template_attacks) | Cross-platform implementation of Cache Template Attacks |
| [pmu\_kmod](pmu_kmod) | Kernel module to enable userspace access to timestamp registers |
