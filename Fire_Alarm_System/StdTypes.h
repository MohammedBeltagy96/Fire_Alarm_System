#ifndef STDTYPES_H_
#define STDTYPES_H_

typedef unsigned char u8; /*NOTE: we used typedef instead of "#define" to avoid the problem when using pointers.*/
typedef signed char s8;
typedef char c8;

typedef unsigned short u16; /*NOTE: here integer size = short size =  2 byte */
typedef signed short s16;

typedef unsigned long u32;
typedef signed long s32;


typedef enum{
	FALSE=0,
	TRUE,
	
}Bool_t;

typedef enum{
	OK,
	NOK,
	NULL_PTR,
	OUTOFRANGE
	
}Error_t;

#define  NULLPTR ((void*)(0))
#define  NULL ((u8)(0))

#define MAX_U8 ((u8)(255))
#define MIN_U8 ((u8)(0))

#define MIN_S8 ((s8)(-128))
#define MAX_S8 ((s8)(127))
#define ZERO_S8 ((s8)(0))


#define MAX_U16 ((u16)(65535))
#define MIN_U16 ((u16)(0))

#define MIN_S16 ((s16)-32768)
#define MAX_S16 ((s16)32767)
#define ZERO_S16 ((s16)0)


#define MAX_U32 ((u32)(4294967295))
#define MIN_U32 ((u32)(0))

#define MIN_S32 ((s32)(-2147483648))
#define MAX_S32 ((s32)(2147483647))
#define ZERO_S32 ((s32)(0))

#endif /* STDTYPES_H_ */