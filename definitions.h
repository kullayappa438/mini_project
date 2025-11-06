#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define WRITEBYTE(WORD,BITPOS,VAL)            WORD =(WORD&(~(255<<BITPOS))|(VAL<<BITPOS))
#define READBIT(WORD,PIN)                 ((WORD>>PIN)&1)
#define READNIBBLE(WORD,PIN)                 ((WORD>>PIN)&15)
#define WRITENIBBLE(WORD,PIN,VAL)            WORD=((WORD&~(15<<PIN))|(VAL<<PIN))

#endif
