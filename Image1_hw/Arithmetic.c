#include "Arithmetic.h"
#include "Hist.h"
#include "Imgout.h"

void Arithmetic_Operation(UChar *Ori, Int wid, Int hei, Int min, Int max) //코드 작성 필요
{
	Img_Buf img;
	Int cur = 0; //현재 화소 위치;

	Char String[5][10] = { "Ori", "Add" , "Sub" ,"Mul" ,"Div" };

	img.arithAdd = (UChar*)calloc((wid * hei), sizeof(UChar));

	do 
	{
		if (Ori[cur] + alpha > max) {
			img.arithAdd[cur] = max;
		}
		else {
			img.arithAdd[cur] = Ori[cur] + alpha;
		}
		cur++;
	} while (cur < wid*hei);

	cur = 0;
	img.arithSub = (UChar*)calloc((wid * hei), sizeof(UChar));

	do
	{
		if (Ori[cur] - beta < min) {
			img.arithSub[cur] = min;
		}
		else {
			img.arithSub[cur] = Ori[cur] - beta;
		}
		cur++;
	} while (cur < wid * hei);

	cur = 0;
	img.arithMul = (UChar*)calloc((wid * hei), sizeof(UChar));

	do
	{
		if (Ori[cur] * gamma > max) {
			img.arithMul[cur] = max;
		}
		else {
			img.arithMul[cur] = Ori[cur] * gamma;
		}
		cur++;
	} while (cur < wid * hei);

	cur = 0;
	img.arithDiv = (UChar*)calloc((wid * hei), sizeof(UChar));

	do
	{
		if (Ori[cur] / delta < min) {
			img.arithDiv[cur] = min;
		}
		else {
			img.arithDiv[cur] = Ori[cur] / delta;
		}
		
		cur++;
	} while (cur < wid * hei);

	ImageOutput(img.arithAdd, wid, hei, String[1]);
	HISTOGRAM(img.arithAdd, wid, hei, max, String[1]); 

	ImageOutput(img.arithSub, wid, hei, String[2]);
	HISTOGRAM(img.arithSub, wid, hei, max, String[2]);

	ImageOutput(img.arithMul, wid, hei, String[3]);
	HISTOGRAM(img.arithMul, wid, hei, max, String[3]);

	ImageOutput(img.arithDiv, wid, hei, String[4]);
	HISTOGRAM(img.arithDiv, wid, hei, max, String[4]);

	free(img.arithAdd);
	free(img.arithSub);
	free(img.arithMul);
	free(img.arithDiv);
}