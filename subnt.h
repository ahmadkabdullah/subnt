// change a ip (string) to an ip (int-array)
void nsatoi(char string[], unsigned int iparray[]);

// change a char array (string) to int
unsigned int natoi(char string[]);

// calculate power
unsigned int npower(unsigned int base, unsigned int pow);

// generate mask from ip CIDR or not, also returns host count
unsigned int iptomask(unsigned int ip[5], unsigned int mask[4]);

// find broadcast ID
void toid_b(unsigned int ip[5], unsigned int mask[4], unsigned int bid[4]);

// find network ID
void toid_n(unsigned int ip[5], unsigned int mask[4], unsigned int nid[4]);

// calculate first ip
void toip_first(unsigned int nid[4], unsigned int ipf[4]);

// calculate last ip
void toip_last(unsigned int bid[4], unsigned int ipl[4]);

// helper to print arrays
void printa(unsigned int ar[4]);

// get input until ip length with message
void getipinput(char ar[19]);

// run a loop and take input from user
unsigned short int interactive();
