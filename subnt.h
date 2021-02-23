void nsatoi(char string[], unsigned int iparray[]);
unsigned int natoi(char string[]);
unsigned int npower(unsigned int base, unsigned int pow);

unsigned int iptomask(unsigned int ip[5], unsigned int mask[4]);

void toid_b(unsigned int ip[5], unsigned int mask[4], unsigned int bid[4]);
void toid_n(unsigned int ip[5], unsigned int mask[4], unsigned int nid[4]);

void toip_first(unsigned int nid[4], unsigned int ipf[4]);
void toip_last(unsigned int bid[4], unsigned int ipl[4]);

unsigned short int nsane(unsigned int ar[]);
