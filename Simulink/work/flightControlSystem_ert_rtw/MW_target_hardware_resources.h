#ifndef PORTABLE_WORDSIZES
#ifdef __MW_TARGET_USE_HARDWARE_RESOURCES_H__
#ifndef __MW_TARGET_HARDWARE_RESOURCES_H__
#define __MW_TARGET_HARDWARE_RESOURCES_H__

#define MW_MULTI_TASKING_MODE 1

#define MW_USECODERTARGET 1
#define MW_TARGETHARDWARE PARROT Mambo
#define MW_CONNECTIONINFO_TCPIP_IPADDRESS 192.168.3.1
#define MW_CONNECTIONINFO_TCPIP_PORT 17725
#define MW_CONNECTIONINFO_TCPIP_VERBOSE 1
#define MW_EXTMODE_CONFIGURATION TCP/IP
#define MW_RTOS Baremetal
#define MW_RUNTIME_BUILDACTION 1
#define MW_RUNTIME_DISABLEPARALLELBUILD 0
#define MW_UI_LAUNCH 1
#define MW_CONFIG_ENABLEPROFILING 0
#define MW_CONFIG_ENABLEOPTICALFLOW 1
#define MW_CONFIG_ENABLEIMAGEVISION 0
#define MW_CONFIG_USEIMAGEVISIONFORPOSITION 0
#define MW_CONFIG_USELOOKUP 0
#define MW_CONFIG_NOSAFETY 1
#define MW_CONFIG_ABORT 0
#define MW_CONFIG_MAXACCELERATION 60
#define MW_CONFIG_IMAGELOGGING 0
#define MW_CLOCKING_CPUCLOCKRATEMHZ 416
#define MW_DATAVERSION 2016.02

#endif /* __MW_TARGET_HARDWARE_RESOURCES_H__ */

#endif

#endif
