/*
 *  Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant 
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

#include "EmptyHeader.h"

#ifdef __psp2__

#ifdef RAKNET_SOCKET_2_INLINE_FUNCTIONS

#ifndef RAKNETSOCKET2_VITA
#define RAKNETSOCKET2_VITA







#endif // file header


#else // RAKNET_SOCKET_2_INLINE_FUNCTIONS


#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>

/*
 * Converts the specified Internet host address to
 * a string in the Internet standard dot notation.
 */
char *inet_ntoa(in_addr in)
{
	static char staticBuff[32];
	char workingbuff[8];
	int part1 = ((in.s_addr & 0xFF000000) >> 24);
	int part2 = ((in.s_addr & 0x00FF0000) >> 16);
	int part3 = ((in.s_addr & 0x0000FF00) >> 8);
	int part4 = ((in.s_addr & 0x000000FF) >> 0);

	itoa(part1, staticBuff, 10);
	strcat(staticBuff, ".");
	itoa(part2, workingbuff, 10);
	strcat(staticBuff, workingbuff);
	strcat(staticBuff, ".");
	itoa(part3, workingbuff, 10);
	strcat(staticBuff, workingbuff);
	strcat(staticBuff, ".");
	itoa(part4, workingbuff, 10);
	strcat(staticBuff, workingbuff);
	return (char*) staticBuff;
}


/*
 * Check whether "cp" is a valid ascii representation
 * of an Internet address and convert to a binary address.
 * Returns 1 if the address is valid, 0 if not.
 * This replaces inet_addr, the return value from which
 * cannot distinguish between failure and a local broadcast address.
 */

static int inet_aton(const char *cp, struct in_addr *addr)
{
	u_long val, base, n;
	char c;
	u_long parts[4], *pp = parts;

	for (;;) {
		/*
		 * Collect number up to ``.''.
		 * Values are specified as for C:
		 * 0x=hex, 0=octal, other=decimal.
		 */
		val = 0; base = 10;
		if (*cp == '0') {
			if (*++cp == 'x' || *cp == 'X')
				base = 16, cp++;
			else
				base = 8;
		}
		while ((c = *cp) != '\0') {
			if (isascii(c) && isdigit(c)) {
				val = (val * base) + (c - '0');
				cp++;
				continue;
			}
			if (base == 16 && isascii(c) && isxdigit(c)) {
				val = (val << 4) +
					(c + 10 - (islower(c) ? 'a' : 'A'));
				cp++;
				continue;
			}
			break;
		}
		if (*cp == '.') {
			/*
			 * Internet format:
			 *	a.b.c.d
			 *	a.b.c	(with c treated as 16-bits)
			 *	a.b	(with b treated as 24 bits)
			 */
			if (pp >= parts + 3 || val > 0xff)
				return (0);
			*pp++ = val, cp++;
		} else
			break;
	}
	/*
	 * Check for trailing characters.
	 */
	if (*cp && (!isascii(*cp) || !isspace(*cp)))
		return (0);
	/*
	 * Concoct the address according to
	 * the number of parts specified.
	 */
	n = pp - parts + 1;
	switch (n) {

	case 1:				/* a -- 32 bits */
		break;

	case 2:				/* a.b -- 8.24 bits */
		if (val > 0xffffff)
			return (0);
		val |= parts[0] << 24;
		break;

	case 3:				/* a.b.c -- 8.8.16 bits */
		if (val > 0xffff)
			return (0);
		val |= (parts[0] << 24) | (parts[1] << 16);
		break;

	case 4:				/* a.b.c.d -- 8.8.8.8 bits */
		if (val > 0xff)
			return (0);
		val |= (parts[0] << 24) | (parts[1] << 16) | (parts[2] << 8);
		break;
	}
	if (addr)
		addr->s_addr = htonl(val);
	return (1);
}


/*
 * Ascii internet address interpretation routine.
 * The value returned is in network order.
 */
in_addr_t inet_addr(const char *cp)
{
	struct in_addr val;

	if (inet_aton(cp, &val))
		return (val.s_addr);
	return (INADDR_NONE);
}






#endif // #ifdef RAKNET_SOCKET_2_INLINE_FUNCTIONS

#endif // #ifdef __psp2__
