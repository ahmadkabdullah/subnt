#include <stdio.h>
#include "subnt.h"

void nprinta(unsigned int ar[4])
{
	unsigned short int i = 0;
	for (i=0; i<4; i++) {
		(i == 3)? printf("%d ", ar[i]): printf("%d.", ar[i]);
	}
	printf("\n");
}

void nprint_mask()
{
	printf("\tSubnet Mask: ");
	iptomask(ip, mask);
	nprinta(mask);
}

void nprint_id()
{
	iptomask(ip, mask);

	printf("\tNetwork ID: ");
	toid_n(ip, mask, nid);
	nprinta(nid);

	printf("\tBroadcast ID: ");
	toid_b(ip, mask, bid);
	nprinta(bid);
}

void nprint_range()
{
	iptomask(ip, mask);
	toid_n(ip, mask, nid);
	toid_b(ip, mask, bid);

	printf("\tFirst IP: ");
	toip_first(nid, ipf);
	nprinta(ipf);

	printf("\tLast IP: ");
	toip_last(bid, ipl);
	nprinta(ipl);
}

void nprint_hostn()
{
	printf("\tHosts: ");
	hostn = iptomask(ip, mask);
	printf("%d \n", hostn);
}

void nprint_full()
{
	printf("\tSubnet Mask: ");
	hostn = iptomask(ip, mask);
	nprinta(mask);

	printf("\tHosts: ");
	printf("%d\n", hostn);

	printf("\tNetwork ID: ");
	toid_n(ip, mask, nid);
	nprinta(nid);

	printf("\tBroadcast ID: ");
	toid_b(ip, mask, bid);
	nprinta(bid);

	printf("\tFirst IP: ");
	toip_first(nid, ipf);
	nprinta(ipf);

	printf("\tLast IP: ");
	toip_last(bid, ipl);
	nprinta(ipl);
}