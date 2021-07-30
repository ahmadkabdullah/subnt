// main funcs

#include <stdio.h>
#include "subnt.h"

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
			printf("Select an option:\n");
			printf("\tm. Get Subnet Mask\n");
			printf("\ti. Get Network and Broadcast ID\n");
			printf("\tr. Get First and Last IP\n");
			printf("\th. Get Number of hosts\n");
			printf("\tf. Get Full Information\n");
			printf("\t0. Get Out\n");
			minteract(); // call interactive loop
			return 0;
			break;
		case 'h':
		default:
			break;
		}
	}
	// else if there are none or opt 'h'
	else
	{
		printf("subnt -i    \t # interactive mode\n");
		printf("\n");
		printf("subnt -af ip\t # return full info\n");
		printf("      -am ip\t # return subnetmask\n");
		printf("      -ai ip\t # return network/broadcast id\n");
		printf("      -ar ip\t # return first/last ip\n");
		printf("      -ah ip\t # return host count\n");
		printf("\n");
		printf("subnt -h  \t # help screen\n");
		return 0;
	}
}

void margument(char o, char *str)
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
		printf("NU> ");
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

void mopts(char o)
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
