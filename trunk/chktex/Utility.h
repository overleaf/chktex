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
 * How many bytes we want in front/end of each char buffer. > 2
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
  void **Data;
  unsigned long Size, Used;
};

struct WordList {
    unsigned long         MaxLen;
    int          NonEmpty;
    struct Stack  Stack;
    struct Hash   Hash;
};
#define WORDLIST_DEFINED

struct FileNode {
  STRPTR        Name;
  FILE  *fh;
  unsigned long Line;
};

/* Rotates x n bits left (should be an int, long, etc.) */
#define ROTATEL(x,n) ((x<<n) | (x>>((CHAR_BIT*sizeof(x)) - n)))

/* Rotates x n bits right (should be an int, long, etc.) */
#define ROTATER(x,n) ((x>>n) | (x<<((CHAR_BIT*sizeof(x)) - n)))

int    fexists(const STRPTR Filename);

void *  sfmemset(void *to, int c, long n);
void *  saferealloc(void *old, size_t newsize);

int     strafter(const STRPTR Str, const STRPTR Cmp);
void    strrep(STRPTR String, const char From, const char To);
void    strxrep(STRPTR Buf, const STRPTR Prot, const char To);
STRPTR  strip(STRPTR String, const enum Strip What);
void    strwrite(STRPTR To, const STRPTR From, unsigned long Len);
int     strinfront(STRPTR Str, STRPTR Cmp);
STRPTR  strdupx(const STRPTR String, int Extra);
void    strmove(char *a, const char *b);

void    ClearHash(struct Hash *h);
void    InsertHash(const STRPTR a, struct Hash *h);
STRPTR  HasHash(const STRPTR a, const struct Hash *h);

int    InsertWord(const STRPTR Word, struct WordList *WL);
STRPTR  HasWord(const STRPTR Word, struct WordList *WL);
void    MakeLower(struct WordList *wl);
void    ListRep(struct WordList *wl, const char From, const char To);
void    ClearWord(struct WordList *WL);

int    StkPush(void *Data, struct Stack *Stack);
void   *StkPop(struct Stack *Stack);
void   *StkTop(struct Stack *Stack);

FILE *  CurStkFile(struct Stack *stack);
STRPTR  CurStkName(struct Stack *stack);
unsigned long   CurStkLine(struct Stack *stack);
STRPTR  FGetsStk(STRPTR Dest, unsigned long len, struct Stack *stack);
int    PushFileName(const STRPTR Name, struct Stack *stack);
int    PushFile(STRPTR, FILE *, struct Stack *);


void    FreeErrInfo(struct ErrInfo* ei);
struct ErrInfo *PushChar(const char c, const unsigned long Line,
				 const unsigned long Column, struct Stack *Stk,
				 const STRPTR LineCpy);
struct ErrInfo *PushErr(const STRPTR Data, const unsigned long Line, const unsigned long Column,
		const unsigned long ErrLen, const STRPTR LineCpy, struct Stack *Stk);
struct ErrInfo *TopChar(struct Stack *Stack);
struct ErrInfo *TopErr(struct Stack *Stack);
struct ErrInfo *PopErr(struct Stack *Stack);
struct ErrInfo *TopMatch(struct Stack *Stack, STRPTR String);

long    BrackIndex(char const c);
void    AddBracket(char const c);
char   MatchBracket(char const);



short    substring(const STRPTR source, STRPTR dest, unsigned long pos, long len);

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
