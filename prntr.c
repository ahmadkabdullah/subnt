// printer funcs

#include <stdio.h>
#include "subnt.h"

void nprinta(unsigned int ar[4])
{
	unsigned short int i = 0;
	for (i=0; i<4; i++) {
		(i == 3)? printf("%d", ar[i]): printf("%d.", ar[i]);
	}
	printf("\n");
}

void nprint_mask()
{
	printf("Subnet Mask: ");
	nprinta(mask);
}

void nprint_id()
{
	printf("Network ID: ");
	nprinta(nid);
	printf("Broadcast ID: ");
	nprinta(bid);
}

void nprint_range()
{
	printf("First IP: ");
	nprinta(ipf);
	printf("Last IP: ");
	nprinta(ipl);
}

void nprint_hostn()
{
	printf("Hosts: ");
	printf("%d\n", hostn);
}

void nprint_full()
{
	printf("Subnet Mask: ");
	nprinta(mask);

	printf("Hosts: ");
	printf("%d\n", hostn);

	printf("Network ID: ");
	nprinta(nid);

	printf("Broadcast ID: ");
	nprinta(bid);

	printf("First IP: ");
	nprinta(ipf);

	printf("Last IP: ");
	nprinta(ipl);
}