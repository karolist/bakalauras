/* Name: requests.h
 * Project: Nukreipimo sistema
 * Author: TT_KT
 * Creation Date: 2013-04-01
 */

/* Antrastinis failas prijungiamas prie PC ir MV programu. Jame apibreztos
 * USB request numeriai, naudojami komunikacijai tarp PC ir mikrovaldiklio
 */


#ifndef __REQUESTS_H_INCLUDED__
#define __REQUESTS_H_INCLUDED__

#define CUSTOM_RQ_ECHO          	0
/* Request nurodo, kad irenginis privalo atsiusti atgal wValue and wIndex.
 * Kintameji savije saugo atsitiktinius duomenys, kure siunciami rysio busenai
 * patikrinti, rysio testas.
 */
#define CUSTOM_RQ_SET_CONFIG    	1
/* Konfiguracijos uzklausa, ijungiami arba isjungiami tam tikri irenginio 
 * elemntai, irenginiai, pavyzdziui: lzerinis modulis, kreipimo mechanizmai,
 * garsinis signalizatorius. Duomenys grazinami patikrinimui.
 */
#define CUSTOM_RQ_SET_POSITION   	2
/* Get the current LED status. Control-IN.
 * This control transfer involves a 1 byte data phase where the device sends
 * the current status to the host. The status is in bit 0 of the byte.
 */

#endif /* __REQUESTS_H_INCLUDED__ */

// #ifndef __CONFIG_H_INCLUDED__
// #define __CONFIG_H_INCLUDED__
// 
// #define CONFIG_SERVO1          	(1<<0)
// #define CONFIG_SERVO2          	(1<<1)
// #define CONFIG_ADDSERVO         	(1<<2)
// #define CONFIG_SUPPLY         	(1<<3)
// #define CONFIG_BUZZER         	(1<<5)
// #define CONFIG_LASER3V         	(1<<6)
// #define CONFIG_LAZER5V         	(1<<7)
// 
// 
// #endif /* __CONFIGH_INCLUDED__ */