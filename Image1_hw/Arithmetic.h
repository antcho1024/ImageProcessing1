#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
typedef unsigned char UChar;
typedef char          Char;
typedef int           Int;

typedef struct _Arith_Oper_Image_Buffer
{
	UChar *arithAdd;
	UChar *arithSub;
	UChar *arithMul;
	UChar *arithDiv;
}Img_Buf;

#define alpha      30  //출력 영상 = 원본 영상 + alpha 
#define beta       30  //출력 영상 = 원본 영상 - beta 
#define gamma      1.2 //출력 영상 = 원본 영상 * gamma 
#define delta      1.2 //출력 영상 = 원본 영상 / delta 

void Arithmetic_Operation(UChar *Ori, Int wid, Int hei, Int min, Int max);
