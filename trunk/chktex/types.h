/*
 * Clone of <exec/types.h>, which could not be included because it's
 * (c) Commodore/Escom/Amiga/whatever.
 *
 */

#ifndef EXEC_TYPES_H
#define	EXEC_TYPES_H

#define GLOBAL	extern	    /* the declaratory use of an external */
#define IMPORT	extern	    /* reference to an external */
#define STATIC	static	    /* a local static variable */
#define REGISTER register   /* a (hopefully) register variable */

#ifndef VOID
#	define VOID		void
#endif


typedef void*			APTR;		/* Address pointer */

typedef unsigned long	ULONG;
typedef long			LONG;

#ifdef AMIGA
typedef unsigned long	LONGBITS;	/* Longword accessed bitwise */
#endif

typedef short			WORD;
typedef unsigned short	UWORD;
typedef unsigned short	WORDBITS;

typedef unsigned char	UBYTE;
typedef unsigned char	BYTEBITS;

typedef unsigned short	RPTR;	    /* relative pointer */


#if __STDC__
typedef signed char		BYTE;
#else
typedef char			BYTE;
#endif

#if defined(__cplusplus) || defined(AMIGA)
typedef unsigned char	TEXT;
#else
typedef char			TEXT;
#endif

typedef TEXT *			STRPTR;     /* pointer to a string */

typedef float			FLOAT;
typedef double			DOUBLE;
typedef short			BOOL;		/* Boolean value */


#ifndef TRUE
#	define TRUE			1L
#endif
#ifndef FALSE
#	define FALSE		0L
#endif
#ifndef NULL
#	define NULL			(void *) 0L
#endif


#endif
