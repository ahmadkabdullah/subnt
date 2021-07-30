// subnt header file

#ifndef _SUBNT_H

/*****************************************************************
*
*	global arrays, for using with handler funcs
	(and printer ones in turn)
*
*****************************************************************/

extern unsigned int ip[5]; // IP Address (length is 5 with CIDR)
extern unsigned int mask[4]; // Subnet Mask
extern unsigned int nid[4], bid[4]; // Broadcast and Network IDs
extern unsigned int ipf[4], ipl[4]; // First and Last IPs
extern unsigned int hostn; // number of hosts
extern char input[19]; // input storing

/*************************************************************************************
*
*	central functions that manipulate all the others
*	providing an interface for the user
*
**************************************************************************************/

void minteract(); // run a loop and take input from user continuously
void margument(const char c, const char *str); // take an argument and give result
void mopts(const char o); // handle options passed by two funcs

/*************************************************************************
*
*	functions which print data made by handling funcs
*
**************************************************************************/

// high printers
void nprint_mask(); // print out the mask
void nprint_id(); // print out the nid and bid
void nprint_range(); // print out first/last ip
void nprint_hostn(); // print out the host count
void nprint_full(); // print out all the previous in one

// base printer
void nprinta(const unsigned int ar[4]); // print arrays

/***************************************************************************
*
*	functions handling input and the processing of data
*
***************************************************************************/

// processing of data
unsigned int tomask(const unsigned int ip[5], unsigned int mask[4]); // generate mask from ip CIDR or not, also returns host count
void toid_b(const unsigned int ip[5], const unsigned int mask[4], unsigned int bid[4]); // find broadcast ID
void toid_n(const unsigned int ip[5], const unsigned int mask[4], unsigned int nid[4]); // find network ID
void toip_first(const unsigned int nid[4], unsigned int ipf[4]); // calculate first ip
void toip_last(const unsigned int bid[4], unsigned int ipl[4]); // calculate last ip

// waste funcs since they're in the std lib
void nstrinput(char ar[19]); // get input as str until ip length
char ncharinput(); // get one char from input without ruining everything
void nsatoi(const char string[], unsigned int iparray[]); // change a ip (string) to an ip (int-array)
unsigned int natoi(const char string[]); // change a char array (string) to int
unsigned int npower(const unsigned int base, const unsigned int pow); // calculate power
unsigned int nstrl(const char string[]); // get length of string

#endif
