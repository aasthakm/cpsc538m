# libflush

libflush is a library to launch cache attacks on x86 as well as ARMv8 architecture. It allows to easily implement attacks based on [Prime+Probe](https://eprint.iacr.org/2005/271.pdf), [Flush+Reload](https://eprint.iacr.org/2013/448.pdf), [Evict+Reload](https://www.usenix.org/system/files/conference/usenixsecurity15/sec15-paper-gruss.pdf), [Flush+Flush](http://arxiv.org/abs/1511.04594) and [Prefetch]() attack techniques and thus offers a great playground for research and education purposes.

This library was developed in the [ARMageddon: Cache Attacks on Mobile Devices](https://www.usenix.org/conference/usenixsecurity16/technical-sessions/presentation/lipp) paper and used to build covert-channels that outperform state-of-the-art covert channels on Android by several orders of magnitude. It was utilized to implement [cache template attacks](https://www.usenix.org/system/files/conference/usenixsecurity15/sec15-paper-gruss.pdf) that monitor tap and swipe events as well as keystrokes, and even derive the words entered on the touchscreen.

## Table of content

- [Installation](#installation)
    - [Dependencies](#dependencies)
- [Build Configuration](#build-configuration)
- [Advanced Configuration](#advanced-configuration)
    - [Eviction strategy](#eviction-strategy)
    - [Timing measurements](#timing-measurements)
- [Usage](#usage)
    - [Initialization and termination](#initialization)
    - [Flush or evict an address](#flush-or-evict-an-address)
    - [Get timing information](#timing-information)
- [Example](#example)
- [License](#license)
- [References](#references)

## Installation

The library is shipped with a Makefile and can be compiled by running:
```bash
make
```

The necessary header files and the shared and static build library can be installed on the host system:
```bash
make install
```

In addition we provide a debug build that can be initiated by calling `make debug` as well as a simple test suite that can be run by calling `make test`. Code coverage of the test suite can be determined by running `make gcov`. Additional documentation can be build with the `make doc` target.


### Dependencies

* [check](https://libcheck.github.io/check/) - Unit Testing Framework for C (optional, for test cases)
* [libfiu](https://blitiri.com.ar/p/libfiu/) - Fault injection in userspace (optional, for test cases)
* [doxygen](www.doxygen.org) (optional, for HTML documentation)
* [Sphinx](http://www.sphinx-doc.org) (optional, for HTML documentation)
* [sphinx\_rtd\_theme](https://github.com/snide/sphinx_rtd_theme) (optional, for HTML documentation)
* [breathe](https://github.com/michaeljones/breathe) (optional, for HTML documentation)

## Build Configuration

The build system makes use of several configuration files. The parameters can be adjusted by modifying the files accordingly or by passing them to make (`make ARCH=x86`). The most important properties are the following:

* `ARCH`: Defines the target architecture.
    * _x86_ (default) - Support for \_i386\_ and \_x86\_64_
    <!-- * _armv7_ - Support for ARMv7 -->
    * _armv8_ - Support for ARMv8

If the library is build for the Raspberry Pi board 4B+ (armv8 architecture), the build system uses the [config-rpi.mk](config-rpi.mk).

* `USE_EVICTION`: Use eviction instead of flush instruction in flush based functions. Required for devices that do not expose a flush instruction (default: 0, enabled by default for _armv7_ architecture).
* `DEVICE_CONFIGURATION`: Defines cache and eviction based properties for the target device if eviction is used. See [libflush/eviction/strategies](libflush/eviction/strategies) for example device configurations.
    * _default_ (default) - Default device configuration.
    * _alto45_ - Alcatel OneTouch POP 2
    * _bacon_ - OnePlus One
    * _mako_ - Nexus 4
    * _hammerhead_ - Nexus 5
    * _tilapia_ - Nexus 7
    * _manta_ - Nexus 10
    * _zeroflte_ - Samsung Galaxy S6
* `TIME_SOURCE`: Gives the possibility to use different timing sources to measure the
execution time. Depending on the available privileges, one might want to change
the timing source.
    * _register_ - Performance register / Time-stamp counter (default)
    * _perf_ - Perf interface
    * _monotonic_clock_ - Monotonic clock
    * _thread_counter_ - Dedicated thread counter
* `WITH_PTHREAD`: Build with pthread support.
* `HAVE_PAGEMAP_ACCESS`: Defines if access to _/proc/self/pagemap_ is granted.

## Advanced Configuration

### Eviction strategy
If eviction is used, libflush uses the parameters defined by the `DEVICE_CONFIGURATION`. The device configuration is represented by a header file in [libflush/eviction/strategies](libflush/eviction/strategies) and is structured as the following:

**Cache specific configuration**
* `NUMBER_OF_SETS`: The number of sets in the cache
* `LINE_LENGTH`: The line length
* `LINE_LENGTH_LOG2`: The log base 2 of the line length

**Eviction strategy configuration**
* `ES_EVICTION_COUNTER`: Length of the loop
* `ES_NUMBER_OF_ACCESSES_IN_LOOP`: Number of accesses of an address in one loop round
* `ES_DIFFERENT_ADDRESSES_IN_LOOP`: Number of different addresses in one loop round

## Usage
The following sections illustrate the usage of libflush. For a complete overview
of the available functions please refer to the source code or to the
documentation that can be build.

### Initialization and termination

In order to use libflush one needs to include the header file and call the `libflush_init` to initialize
the library. In the end `libflush_terminate` needs to be called to clean-up.
```c
#include <libflush.h>

int main(int argc, char* argv[]) {
    // Initialize libflush
    libflush_session_t* libflush_session;
    if (libflush_init(&libflush_session, NULL) == false) {
        return -1;
    }

    // Use libflush...

    // Terminate libflush
    if (libflush_terminate(libflush_session) == false) {
        return -1;
    }

    return 0;
}
```
and link against the library:
```
gcc example.c `pkg-config --libs libflush`
```

### Flush or evict an address

To evict an address from the cache to the main memory, a dedicated flush
instruction (if available) or eviction can be used.

```c
void* address = &foo;

// Use the flush instruction (if possible)
libflush_flush(libflush_session, address);

// Use eviction
libflush_evict(libflush_session, address);
```

### Get timing information

To retrieve a time stamp depending on the used time source can be achieved with
the following function.

```c
uint64 time = libflush_get_timing(libflush_session);
```

In addition wrapper functions to measure the
execution time of different functions are given.

```c
uint64 time = libflush_reload_address(libflush_session, address);
```

## Example

A more sophisticated example using libflush can be found in the [example](example) directory. It implements
a calibration tool for the Flush+Reload, Prime+Probe, Evict+Reload, Flush+Flush and Prefetch attack. The example
can be compiled by running `make example` and executed by running `./example/build/<arch>/release/bin/example`.

## License

[Licensed](LICENSE) under the zlib license.

## References

* [1] [ARMageddon: Cache Attacks on Mobile Devices - Lipp, Gruss, Spreitzer, Maurice, Mangard](https://www.usenix.org/conference/usenixsecurity16/technical-sessions/presentation/lipp)
* [2] [Cache Template Attacks](https://www.usenix.org/system/files/conference/usenixsecurity15/sec15-paper-gruss.pdf)