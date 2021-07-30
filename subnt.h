// subnt header file

/*****************************************************************
*
*	global arrays, for using with handler or printer funcs
*
*****************************************************************/

unsigned int ip[5]; // IP Address (length is 5 with CIDR)
unsigned int mask[4]; // Subnet Mask
unsigned int nid[4], bid[4]; // Broadcast and Network IDs
unsigned int ipf[4], ipl[4]; // First and Last IPs
unsigned int hostn; // number of hosts
char input[19]; // input storing

/*************************************************************************************
*
*	central functions that manipulate all the others
*
**************************************************************************************/

unsigned short int interact(); // run a loop and take input from user continuously
void argument(char c, char *str); // take an argument and give result

/*************************************************************************
*
*	functions which print the results of the handling funcs
*
**************************************************************************/

// high printers
void nprint_mask(); // print out the mask
void nprint_id(); // print out the nid and bid
void nprint_range(); // print out first/last ip
void nprint_hostn(); // print out the host count
void nprint_full(); // print out all the previous in one

// base printer
void nprinta(unsigned int ar[4]); // print arrays

/***************************************************************************
*
*	functions handling input and the processing of data
*
***************************************************************************/

// to get input
void nstrinput(char ar[19]); // get input as str until ip length
char ncharinput(); // get one char from input without ruining everything

// processing of data
unsigned int iptomask(unsigned int ip[5], unsigned int mask[4]); // generate mask from ip CIDR or not, also returns host count
void toid_b(unsigned int ip[5], unsigned int mask[4], unsigned int bid[4]); // find broadcast ID
void toid_n(unsigned int ip[5], unsigned int mask[4], unsigned int nid[4]); // find network ID
void toip_first(unsigned int nid[4], unsigned int ipf[4]); // calculate first ip
void toip_last(unsigned int bid[4], unsigned int ipl[4]); // calculate last ip

// waste funcs since they're in the std lib
void nsatoi(char string[], unsigned int iparray[]); // change a ip (string) to an ip (int-array)
unsigned int natoi(char string[]); // change a char array (string) to int
unsigned int npower(unsigned int base, unsigned int pow); // calculate power
unsigned int nstrl(char string[]); // get length of string