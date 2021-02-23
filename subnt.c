#include <stdio.h>
#include "subnt.h"

// helper to print array
void printm(unsigned int ar[]);
void printm(unsigned int ar[])
{
	short int i = 0;
	for (i=0; i<4; i++) { 
		(i == 3)? printf("%d", ar[i]): printf("%d.", ar[i]);
	}
	printf("\n");
}

// main func
int main()
{
	unsigned int ip[5], mask[4];
	unsigned int nid[4], bid[4];
	unsigned int ipf[4], ipl[4];
	char input[] = "192.168.1.2/24";

	printf("IP ");
	printf("%s \n", input);
	nsatoi(input, ip); // sane input

	printf("SM ");
	unsigned int hostc = iptomask(ip, mask);
	printm(mask);
	printf("\n");

	printf("N ");
	toid_n(ip, mask, nid);
	printm(nid);
	printf("B ");
	toid_b(ip, mask, bid);
	printm(bid);
	printf("\n");

	printf("F ");
	toip_first(nid, ipf);
	printm(ipf);
	printf("L ");
	toip_last(bid, ipl);
	printm(ipl);
	printf("\n");
}

// calculate first ip
void toip_first(unsigned int nid[4], unsigned int ipf[4])
{
	ipf[0] = nid[0];
	ipf[1] = nid[1];
	ipf[2] = nid[2];
	ipf[3] = nid[3]+1;
}

// calculate last ip
void toip_last(unsigned int bid[4], unsigned int ipl[4])
{
	ipl[0] = bid[0];
	ipl[1] = bid[1];
	ipl[2] = bid[2];
	ipl[3] = bid[3]-1;
}

// find network ID
void toid_n(unsigned int ip[], unsigned int mask[4], unsigned int nid[4])
{
	short int i = 0;
	while (mask[i] == 255) // find subnet octet and assign previous octets
	{
		nid[i] = ip[i]; // set same number from ip if 255
		i++;
	}

	unsigned int step = 256-mask[i]; // get size of a subnet
	unsigned int ov = 0; // octet val

	while (ov <= ip[i]) // when smaller than ip octet step up
	{
		ov += step;
	}

	ov -= step; // step back
	nid[i] = ov; // set subnet octect to found val

	i++; // move right
	while (i<4) // set remaining octects
	{
		nid[i] = 0; // set them to 0
		i++;
	}
}

// find broadcast ID
void toid_b(unsigned int ip[], unsigned int mask[4], unsigned int bid[4])
{
	short int i = 0;
	while (mask[i] == 255) // find subnet octet and assign previous octets
	{
		bid[i] = ip[i]; // set same number from ip if 255
		i++;
	}

	int step = 256-mask[i]; // get size of a subnet
	int ov = 0; // octet val

	while (ov <= ip[i]) // when smaller than ip octet step up
	{
		ov += step;
	}

	ov -= 1; // negate 1
	bid[i] = ov; // set subnet octect to found val

	i++; // move right
	while (i<4) // set remaining octects
	{
		bid[i] = 255; // set them to 255
		i++;
	}
}

// generate mask from ip CIDR or not, also returns host count
unsigned int iptomask(unsigned int ip[5], unsigned int mask[4])
{
	short int cidr = ip[4];
	short int ioct = 0;
	short int bitson = 0;

	// if there is no CIDR
	if (cidr == 0)
	{
		if (ip[1] <= 127) // if class A
		{
			cidr=8;
		}
		else if (ip[1] <= 191) // if class B
		{
			cidr=16;
		}
		else if (ip[1] <= 224) // if class C
		{
			cidr=24;
		}
	}

	// set other octets
	if (cidr >= 24)
	{
		mask[0] = 255; mask[1] = 255; mask[2] = 255;
		ioct = 3; // in octet 3 according to 0-index
		bitson = cidr-24; // bits on in the octet
	}
	else if (cidr >= 16)
	{
		mask[0] = 255; mask[1] = 255; mask[3] = 0;
		ioct = 2;
		bitson = cidr-16;
	}
	else if (cidr >= 8)
	{
		mask[0] = 255; mask[2] = 0; mask[3] = 0;
		ioct = 1;
		bitson = cidr-8;
	}
	else if (cidr >= 0)
	{
		mask[1] = 0; mask[2] = 0; mask[3] = 0;
		ioct = 0;
		bitson = cidr-0;
	}

	int num = 256;
	short int i;

	for (i=0; i<bitson; i++) // calculate subnet octet
	{
		num /= 2; // half value as we go right
		mask[ioct] += num; // sum value
	}

	return npower(2, (32-cidr))-2; // number of hosts
}

// change a ip (string) to an ip (int-array)
void nsatoi(char s[], unsigned int ia[5])
{
	short int i, j, k; i=j=k=0;
	short int sel, sela, selb; // selection vars
	char scut[5]; // value selected (cut)
	int cidr = 0; // cidr pos

	short int loopy = 1;
	// get ip
	while (loopy)
	{
		switch (s[i])
		{
		case '/':
			cidr = i+1; // mark cidr pos
		case '\0':
		case '.':
			if (s[i] == '\0') // if at end
			{
				loopy = 0; // stop looping
			}

			selb = i; // set point b
			sel = 0; // stop selection

			while (sela < selb)
			{
				scut[j] = s[sela]; // cut char in selection
				j++; // next element
				sela++; // next selection
			}

			scut[j] = '\0'; // conclude char array cut
			j = 0;
			ia[k] = natoi(scut); // add to output by calling natoi on cut
			k++;

			break;
		default:
			if (sel == 0) // if not selecting
			{
				sela = i; // set point a
				sel = 1; // start selection
			}
			break;
		}
		i++;
	}

	if (cidr != 0) // get cidr if available
	{
		j=0;
		while (s[cidr] != '\0') // add as with ip part
		{
			scut[j] = s[cidr];
			j++;
			cidr++;
		}

		scut[j] = '\0'; // conclude
		ia[k] = natoi(scut); // to int and add to array
	}
	else // set to 0 otherwise
	{
		ia[k] = 0;
	}

	// check result
	k=0;
	while (k < 5)
	{
		if (ia[k] > 255) // shouldn't be more than 255
		{
			ia[k] = 255;
		}
		if (!ia[k])
		{
			ia[k] = 0;
		}
		k++;
	}
}

// change a char array (string) to int
unsigned int natoi(char s[4])
{
	int i = 0;
	int calc = 0;
	unsigned int ret = 0; // return value

	while (s[i] != '\0') // reach the end of string
	{
		i++;
	}
	const int len = i; // length of string now known

	while (i > -1) // go through each char backwards
	{
		calc = npower(10, (len-i)); // positional value using power

		switch (s[i]) // add each digit according to position value
		{
		case '0': ret += 0*calc; break;
		case '1': ret += 1*calc; break;
		case '2': ret += 2*calc; break;
		case '3': ret += 3*calc; break;
		case '4': ret += 4*calc; break;
		case '5': ret += 5*calc; break;
		case '6': ret += 6*calc; break;
		case '7': ret += 7*calc; break;
		case '8': ret += 8*calc; break;
		case '9': ret += 9*calc; break;
		}
		i--; //step back
	}
	return ret;
}

// calculate power
unsigned int npower(unsigned int b, unsigned int p)
{
	short int i = 1;
	unsigned int ret = 1;

	while (i<p) // for p times
	{
		ret = ret * b; // multiply by itself
		i++;
	}
	return ret;
}
