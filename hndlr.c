// handler funcs

#include <stdio.h>
#include "subnt.h"

void toip_first(unsigned int nid[4], unsigned int ipf[4])
{
	ipf[0] = nid[0];
	ipf[1] = nid[1];
	ipf[2] = nid[2];
	ipf[3] = nid[3]+1;
}

void toip_last(unsigned int bid[4], unsigned int ipl[4])
{
	ipl[0] = bid[0];
	ipl[1] = bid[1];
	ipl[2] = bid[2];
	ipl[3] = bid[3]-1;
}

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

unsigned int tomask(unsigned int ip[5], unsigned int mask[4])
{
	short int cidr = ip[4];
	short int ioct = 0;
	short int bitson = 0;

	// if there is no CIDR set one
	if (cidr == 0)
	{
		if (ip[0] >= 191 && ip[0] <= 223) // if class C
		{
			cidr=24;
		}
		else if (ip[0] >= 128 && ip[0] <= 191) // if class B
		{
			cidr=16;
		}
		else if (ip[0] >= 1 && ip[0] <= 126) // if class A
		{
			cidr=8;
		}
		else // else class D, E
		{
			cidr=32;
		}
	}

	// set other octets according to cidr
	if (cidr >= 24)
	{
		mask[0] = 255; mask[1] = 255; mask[2] = 255;
		ioct = 4; // in octet 3 according to 0-index
		bitson = cidr-24; // bits on in the octet
	}
	else if (cidr >= 16)
	{
		mask[0] = 255; mask[1] = 255; mask[3] = 0;
		ioct = 3;
		bitson = cidr-16;
	}
	else if (cidr >= 8)
	{
		mask[0] = 255; mask[2] = 0; mask[3] = 0;
		ioct = 2;
		bitson = cidr-8;
	}
	else if (cidr >= 0)
	{
		mask[1] = 0; mask[2] = 0; mask[3] = 0;
		ioct = 1;
		bitson = cidr-0;
	}

	int num = 256;
	short int i;

	for (i=0; i<bitson; i++) // calculate subnet octet
	{
		num /= 2; // half value as we go right
		mask[ioct-1] += num; // sum value
	}

	return npower(2, (32-cidr))-2; // number of hosts
}

void nstrinput(char ar[19])
{
	char c;
	unsigned short int i = 0;

	while ((c=getchar()) != '\n')
	{
		if (i < 19) // if not passing char ip length limit
		{
			ar[i] = c; // add to array
			i++;
		}
		// else discard char
	}

	ar[i] = '\0'; // close char array
}

char ncharinput()
{
	char c, o;
	unsigned int i = 0;

	while ((c=getchar()) != '\n')
	{
		if (i == 0)
		{
			o = c; // take first char
		}
		i++;
	}

	return o;
}

void nsatoi(char s[], unsigned int ia[5])
{
	short int i, j, k; i=j=k=0; // index vars
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

			while (sela < selb) // from start to end of selection
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

unsigned int natoi(char s[4])
{
	int i = 0;
	int calc = 0;
	unsigned int ret = 0; // return value

	while (s[i] != '\0') // reach the end of string
	{
		i++;
	}
	const int len = i-1; // length of string now known (-1 for \0 in end?)

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

unsigned int npower(unsigned int b, unsigned int p)
{
	short int i = 0;
	unsigned int ret = 1;

	while (i<p) // for p times
	{
		ret = ret * b; // multiply by itself
		i++;
	}
	return ret;
}

unsigned int nstrl(char str[])
{
	short int i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return i;
}
