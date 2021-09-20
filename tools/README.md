# Cache Attacks

This repository contains several libraries and tools to perform cache-attacks on
x86 and arm devices. The original source of these libraries and tools can be found [here](https://github.com/IAIK/armageddon), which were developed and utilized in the [Cache Template Attacks](https://www.usenix.org/system/files/conference/usenixsecurity15/sec15-paper-gruss.pdf) and [ARMageddon: Cache Attacks on Mobile Devices](https://www.usenix.org/conference/usenixsecurity16/technical-sessions/presentation/lipp) papers.

<!--
The published code has been used to perform the most
powerful cross-core cache attacks [Prime+Probe](https://eprint.iacr.org/2005/271.pdf), [Flush+Reload](https://eprint.iacr.org/2013/448.pdf), [Evict+Reload](https://www.usenix.org/system/files/conference/usenixsecurity15/sec15-paper-gruss.pdf), [Flush+Flush](http://arxiv.org/abs/1511.04594) on non-rooted ARM-based devices without any privileges.

We have developed this libraries and tools in the [ARMageddon: Cache Attacks on Mobile Devices](https://www.usenix.org/conference/usenixsecurity16/technical-sessions/presentation/lipp) paper and used it to build covert-channels that outperform state-of-the-art covert channels on Android by several orders of magnitude. We utilized it to implement [cache template attacks](https://www.usenix.org/system/files/conference/usenixsecurity15/sec15-paper-gruss.pdf) that monitor tap and swipe events as well as keystrokes, and even derive the words entered on the touchscreen. Moreover, we used it to attack cryptographic primitives in Java and to monitor cache activity in the ARM TrustZone from the normal world.

The [ARMageddon: Cache Attacks on Mobile Devices](https://www.usenix.org/conference/usenixsecurity16/technical-sessions/presentation/lipp) paper by Lipp, Gruss, Spreitzer, Maurice and Mangard has be published at the Usenix Security Symposium 2016 and presented at [Black Hat Europe 2016](https://www.blackhat.com/eu-16/briefings/schedule/index.html#armageddon-how-your-smartphone-cpu-breaks-software-level-security-and-privacy-4887).
-->

### Repository Content

| Directory  | Description |
| -------- | ------------- |
| [libflush](libflush) | Library to build cross-platform cache attacks |
| [cache\_template\_attacks](cache_template_attacks) | Cross-platform implementation of Cache Template Attacks |
| [pmu\_kmod](pmu_kmod) | Kernel module to enable userspace access to timestamp registers |
<!--
| [Eviction Strategy Evaluator](eviction_strategy_evaluator) | Find eviction strategy for your device |
| [Input Simulator](input_simulator) | Simple tool to simulate touch events |
-->

<!--
## References

* [1] [ARMageddon: Cache Attacks on Mobile Devices - Lipp, Gruss, Spreitzer, Maurice, Mangard](https://www.usenix.org/conference/usenixsecurity16/technical-sessions/presentation/lipp)
* [2] [ARMageddon: How Your Smartphone CPU Breaks Software-Level Security and Privacy (Black Hat Europe 2016) - Lipp, Maurice](https://www.blackhat.com/eu-16/briefings/schedule/index.html#armageddon-how-your-smartphone-cpu-breaks-software-level-security-and-privacy-4887)
-->