#include <stdio.h>
#include "subnt.h"

unsigned int ip[5]; // IP Address (length is 5 with CIDR)
unsigned int mask[4]; // Subnet Mask
unsigned int nid[4], bid[4]; // Broadcast and Network IDs
unsigned int ipf[4], ipl[4]; // First and Last IPs
unsigned int hostn; // number of hosts
char input[19]; // input storing

const char* str_inte = "\
Select an option: \n\
    m. Get Subnet Mask \n\
    i. Get Network and Broadcast ID \n\
    r. Get First and Last IP \n\
    h. Get Number of hosts \n\
    f. Get Full Information \n\
    0. Get Out\n\
";

const char* str_help = "\
subnt -i       # interactive mode \n\
\n\
subnt -af ip   # return full info \n\
      -am ip   # return subnetmask \n\
      -ai ip   # return network/broadcast id \n\
      -ar ip   # return first/last ip \n\
      -ah ip   # return host count \n\
\n\
subnt -h       # help screen \n\
";

int main(int argc, char **argv)
{
	// if args then get them
	if (argc > 1)
	{
		switch (argv[1][1])
		{
		case 'a':
			if (argc > 2) // if two args, pass second
			{
				margument(argv[1][2], argv[2]); // call with arg as ip
			}
			else // else go normal
			{
				margument(argv[1][2], input); // call with pipe as ip
			}
			return 0;
			break;
		case 'i':
			printf("%s", str_inte);
			minteract(); // call interactive loop
			return 0;
			break;
		case 'h':
			printf("%s", str_help);
		default:
			break;
		}
	}
	// else if there are none
	else
	{
		printf("%s", str_help);
		return 0;
	}
}

void margument(const char o, const char *str)
{
	if (nstrl(str)) // if given a string use it as ip
	{
		nsatoi(str, ip);
	}
	else // else just take it from pipe
	{
		nstrinput(input);
		nsatoi(input, ip);
	}

	mopts(o);
}

void minteract()
{
	char o;
	while (1) // loop for input and call mopts
	{
		// ask for opt
		printf("\nOP> ");
		o = ncharinput(); // take one char opt

		if (o == '0') // if 0 then break out
		{
			break;
		}

		// ask for ip
		printf("IP> ");
		nstrinput(input);
		nsatoi(input, ip);

		mopts(o);

		// reset data just to be safe
		ip[0] = ip[1] = ip[2] = ip[3] = ip[4] = 0;
		mask[0] = mask[1] = mask[2] = mask[3] = 0;
		ipf[0] = ipf[1] = ipf[2] = ipf[3] = 0;
		ipl[0] = ipl[1] = ipl[2] = ipl[3] = 0;
		bid[0] = bid[1] = bid[2] = bid[3] = 0;
		nid[0] = nid[1] = nid[2] = nid[3] = 0;
		hostn = 0;
	}
}

void mopts(const char o)
{
	switch (o)
	{
	case 'm': // Subnet Mask
		// process
		tomask(ip, mask);
		// print
		nprint_mask();
		break;
	case 'h': // number of hosts available
		// process
		hostn = tomask(ip, mask);
		// print
		nprint_hostn();
		break;
	case 'i': // Network/Broadcast ID
		// process
		tomask(ip, mask);
		toid_n(ip, mask, nid);
		toid_b(ip, mask, bid);
		// print
		nprint_id();
		break;
	case 'r': // First/Last IP
		// process
		tomask(ip, mask);
		toid_n(ip, mask, nid);
		toid_b(ip, mask, bid);
		toip_first(nid, ipf);
		toip_last(bid, ipl);
		// print
		nprint_range();
		break;
	case 'f': // Full
	default:
		// process
		hostn = tomask(ip, mask);
		toid_n(ip, mask, nid);
		toid_b(ip, mask, bid);
		toip_first(nid, ipf);
		toip_last(bid, ipl);
		// print
		nprint_full();
		break;
	}
}
