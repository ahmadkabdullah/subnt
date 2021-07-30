// important vars
unsigned int ip[5], mask[4]; // IP and Subnet Mask
unsigned int nid[4], bid[4]; // broadcast and network IDs
unsigned int ipf[4], ipl[4]; // first and last IPs
unsigned int hostn; // number of hosts
char input[19];

// funcs which were a waste since they'ree in the standard lib
void nsatoi(char string[], unsigned int iparray[]); // change a ip (string) to an ip (int-array)
unsigned int natoi(char string[]); // change a char array (string) to int
unsigned int npower(unsigned int base, unsigned int pow); // calculate power
unsigned int nstrl(char string[]); // get length of string

// to find values and assign them to the arrays
unsigned int iptomask(unsigned int ip[5], unsigned int mask[4]); // generate mask from ip CIDR or not, also returns host count
void toid_b(unsigned int ip[5], unsigned int mask[4], unsigned int bid[4]); // find broadcast ID
void toid_n(unsigned int ip[5], unsigned int mask[4], unsigned int nid[4]); // find network ID
void toip_first(unsigned int nid[4], unsigned int ipf[4]); // calculate first ip
void toip_last(unsigned int bid[4], unsigned int ipl[4]); // calculate last ip

// handling the central part of the program
unsigned short int interact(); // run a loop and take input from user
void argument(char c, char *str); // take an argument and give result

// outputing and inputing helper funcs
void nprinta(unsigned int ar[4]); // helper to print arrays
void getipinput(char ar[19]); // get input until ip length with message

// with vars already set up (input changed to ip array)
void nprint_mask(); // print out the mask
void nprint_id(); // print out the nid and bid
void nprint_range(); // print out first/last ip
void nprint_hostn(); // print out the host count
void nprint_full(); // print out all the previous in one
