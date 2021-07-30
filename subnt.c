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
			if (argc > 2) // if two args, take it as ip
			{
				argument(argv[1][2], argv[2]);
			}
			else // else go normal
			{
				argument(argv[1][2], input);
			}
			return 0; // close
			break;
		case 'i':
			break;
		case 'h':
		default:
			printf("# interactive mode \n");
			printf("\tsubnt       \t # \n");
			printf("\tsubnt -i    \t # \n");
			printf("\n");
			printf("# argument/piped mode \n");
			printf("\tsubnt -a  ip\t # return full info\n");
			printf("\t      -am ip\t # return subnetmask\n");
			printf("\t      -ai ip\t # return network/broadcast id\n");
			printf("\t      -ar ip\t # return first/last ip\n");
			printf("\t      -ah ip\t # return host count\n");
			printf("\n");
			printf("# help screen \n");
			printf("\tsubnt       \t # \n");
			printf("\tsubnt -h    \t # \n");
			return 0; // close
			break;
		}
	}

	// if no args or 'i' arg
	unsigned short int on = 2;
	while (on)
	{
		if (on==2) // if returneed 2 display menu
		{
			printf("Select an option:\n");
			printf("\t1. Get Subnet Mask\n");
			printf("\t2. Get Network and Broadcast ID\n");
			printf("\t3. Get First and Last IP\n");
			printf("\t4. Get Number of hosts\n");
			printf("\t5. Get Full Information\n");
			printf("\t0. Get Out\n");
			printf("\n");
		}

		on = interact(); // go to mode and get return val

		// reset arrays
		ip[0] = ip[1] = ip[2] = ip[3] = ip[4] = 0;
		mask[0] = mask[1] = mask[2] = mask[3] = 0;
		ipf[0] = ipf[1] = ipf[2] = ipf[3] = 0;
		ipl[0] = ipl[1] = ipl[2] = ipl[3] = 0;
		bid[0] = bid[1] = bid[2] = bid[3] = 0;
		nid[0] = nid[1] = nid[2] = nid[3] = 0;
		hostn = 0;
	}

	return 0; // close
}


void argument(char c, char *str)
{
	if (nstrl(str)) // if given a string use it as ip
	{
		nsatoi(str, ip);
	}
	else // else just ask for input or take it from pipe
	{
		nstrinput(input);
		nsatoi(input, ip);
	}

	// switch on type of output asked for
	switch (c)
	{
	case 'm': // mask
		nprint_mask();
		break;
	case 'i': // n/b id
		nprint_id();
		break;
	case 'r': // f/l ip
		nprint_range();
		break;
	case 'h': // h count
		nprint_hostn();
		break;
	default: // full
		nprint_full();
		break;
	}
}

unsigned short int interact()
{
	printf("NU> ");
	char o = ncharinput(); // take one char opt

	// process options
	switch (o)
	{
	case '1': // Subnet Mask
		printf("IP> ");
		nstrinput(input);
		nsatoi(input, ip);

		nprint_mask();
		break;
	case '2': // Network/Broadcast ID
		printf("IP> ");
		nstrinput(input);
		nsatoi(input, ip);

		nprint_id();
		break;
	case '3': // First/Last IP
		printf("IP> ");
		nstrinput(input);
		nsatoi(input, ip);

		nprint_range();
		break;
	case '4': // number of hosts available
		printf("IP> ");
		nstrinput(input);
		nsatoi(input, ip);

		nprint_hostn();
		break;
	case '5': // Full
		printf("IP> ");
		nstrinput(input);
		nsatoi(input, ip);

		nprint_full();
		break;
	case '0':
		return 0;
		break;
	default:
		printf("Incorrect option!\n\n");
		return 2; // continue loop but display menu
		break;
	}
	printf("\n");

	return 1; // continue loop
}