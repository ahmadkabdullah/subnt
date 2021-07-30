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
	printf("\tSubnet Mask: ");
	nprinta(mask);
}

void nprint_id()
{
	printf("\tNetwork ID: ");
	nprinta(nid);
	printf("\tBroadcast ID: ");
	nprinta(bid);
}

void nprint_range()
{
	printf("\tFirst IP: ");
	nprinta(ipf);
	printf("\tLast IP: ");
	nprinta(ipl);
}

void nprint_hostn()
{
	printf("\tHosts: ");
	printf("%d\n", hostn);
}

void nprint_full()
{
	printf("\tSubnet Mask: ");
	nprinta(mask);

	printf("\tHosts: ");
	printf("%d\n", hostn);

	printf("\tNetwork ID: ");
	nprinta(nid);

	printf("\tBroadcast ID: ");
	nprinta(bid);

	printf("\tFirst IP: ");
	nprinta(ipf);

	printf("\tLast IP: ");
	nprinta(ipl);
}