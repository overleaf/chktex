/*
 *  ChkTeX, utility functions -- header file.
 *  Copyright (C) 1995-96 Jens T. Berger Thielemann
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *  Contact the author at:
 *              Jens Berger
 *              Spektrumvn. 4
 *              N-0666 Oslo
 *              Norway
 *              E-mail: <jensthi@ifi.uio.no>
 *
 *
 */

#ifndef UTILITY_H
#define UTILITY_H 1

#ifndef CHKTEX_H
# include "ChkTeX.h"
#endif /* CHKTEX_H */
#ifndef OPSYS_H
# include "OpSys.h"
#endif /* OPSYS_H */


/*
 * How many indexes we'll allocate first time
 */
#define MINPUDDLE       256

/*
 * How many bytes we want in front/end of each TEXT buffer. > 2
 */
#define WALLBYTES       4

#ifndef HASH_SIZE
#  define HASH_SIZE    1009   /* A reasonably large prime */
#endif

#define FORWL(ind, list)  for(ind = 0; ind < (list).Stack.Used; ind++)


enum Strip {
    STRP_LFT = 0x01,
    STRP_RGT = 0x02,
    STRP_BTH = 0x03
};

struct HashEntry {
    struct HashEntry *Next;
    STRPTR Str;
};

struct Hash {
    struct HashEntry **Index;
};

struct Stack {
  APTR  *Data;
  ULONG Size, Used;
};

struct WordList {
    ULONG         MaxLen;
    BOOL          NonEmpty;
    struct Stack  Stack;
    struct Hash   Hash;
};
#define WORDLIST_DEFINED

struct FileNode {
  STRPTR        Name;
  FILE  *fh;
  ULONG Line;
};

/* Rotates x n bits left (should be an int, long, etc.) */
#define ROTATEL(x,n) ((x<<n) | (x>>((CHAR_BIT*sizeof(x)) - n)))

/* Rotates x n bits right (should be an int, long, etc.) */
#define ROTATER(x,n) ((x>>n) | (x<<((CHAR_BIT*sizeof(x)) - n)))

BOOL    fexists(const STRPTR Filename);

APTR    sfmemset(APTR to, int c, LONG n);
void *  saferealloc(void *old, size_t newsize);

int     strafter(const STRPTR Str, const STRPTR Cmp);
void    strrep(STRPTR String, const TEXT From, const TEXT To);
void    strxrep(STRPTR Buf, const STRPTR Prot, const TEXT To);
STRPTR  strip(STRPTR String, const enum Strip What);
void    strwrite(STRPTR To, const STRPTR From, ULONG Len);
int     strinfront(STRPTR Str, STRPTR Cmp);
STRPTR  strdupx(const STRPTR String, int Extra);
void    strmove(char *a, const char *b);

void    ClearHash(struct Hash *h);
void    InsertHash(const STRPTR a, struct Hash *h);
STRPTR  HasHash(const STRPTR a, const struct Hash *h);

BOOL    InsertWord(const STRPTR Word, struct WordList *WL);
STRPTR  HasWord(const STRPTR Word, struct WordList *WL);
void    MakeLower(struct WordList *wl);
void    ListRep(struct WordList *wl, const TEXT From, const TEXT To);
void    ClearWord(struct WordList *WL);

BOOL    StkPush(const APTR Data, struct Stack *Stack);
APTR    StkPop(struct Stack *Stack);
APTR    StkTop(struct Stack *Stack);

FILE *  CurStkFile(struct Stack *stack);
STRPTR  CurStkName(struct Stack *stack);
ULONG   CurStkLine(struct Stack *stack);
STRPTR  FGetsStk(STRPTR Dest, ULONG len, struct Stack *stack);
BOOL    PushFileName(const STRPTR Name, struct Stack *stack);
BOOL    PushFile(STRPTR, FILE *, struct Stack *);


void    FreeErrInfo(struct ErrInfo* ei);
struct ErrInfo *PushChar(const TEXT c, const ULONG Line,
				 const ULONG Column, struct Stack *Stk,
				 const STRPTR LineCpy);
struct ErrInfo *PushErr(const STRPTR Data, const ULONG Line, const ULONG Column,
		const ULONG ErrLen, const STRPTR LineCpy, struct Stack *Stk);
struct ErrInfo *TopChar(struct Stack *Stack);
struct ErrInfo *TopErr(struct Stack *Stack);
struct ErrInfo *PopErr(struct Stack *Stack);
struct ErrInfo *TopMatch(struct Stack *Stack, STRPTR String);

LONG    BrackIndex(TEXT const c);
void    AddBracket(TEXT const c);
TEXT   MatchBracket(TEXT const);



WORD    substring(const STRPTR source, STRPTR dest, ULONG pos, LONG len);

#ifndef  HAVE_STRLWR
#  define  strlwr  mystrlwr
STRPTR  mystrlwr(STRPTR String);
#endif

#ifndef  HAVE_STRDUP
#  define  strdup  mystrdup
STRPTR  mystrdup(const STRPTR String);
#endif


#ifndef HAVE_STRCASECMP
int strcasecmp(char* a, char* b);
#endif



#endif /* UTILITY_H */
