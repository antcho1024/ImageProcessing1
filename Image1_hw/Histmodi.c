#include "Hist.h"
#include "Imgout.h"

void HISTOGRAM_MODIFICATION(UChar* Data, Int wid, Int hei, Int max, Int min)
{
	Char String[3][10] = {"Equal", "Spec", "End"};
	Int    LUT[pixRange] = { 0 };

	for (Int i = 0; i < wid * hei; i++)
		LUT[Data[i]]++;

	/////////////////////////////////////////////////////////////////
	//Histogram Equalization
	
	Int    EQUAL_LUT[pixRange] = { 0 };
	Int    Accum_Sum[pixRange] = { 0 }; //누적 빈도수

	UChar* EQUAL_IMG = (UChar*)calloc((wid * hei), sizeof(UChar));

	Accum_Sum[0] = LUT[0];
	for (Int i = 1; i < pixRange; i++)
		Accum_Sum[i] = Accum_Sum[i - 1] + LUT[i];

	for (Int i = 0; i < pixRange; i++) //코드 작성 필요
		EQUAL_LUT[i] = ((double)max / ((double)wid * (double)hei)) * (double)Accum_Sum[i] + 0.5;

	for (Int i = 0; i < wid * hei; i++)
		EQUAL_IMG[i] = EQUAL_LUT[Data[i]];

	ImageOutput(EQUAL_IMG, wid, hei, String[0]);
	HISTOGRAM(EQUAL_IMG, wid, hei, max, String[0]);
	/////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////
	//Histogram Specification

	Int    LUT_BUF[pixRange] = { 0 };
	Int    Speci_Accum_Sum[pixRange] = { 0 }; //누적 빈도수
	Int    SPECI_LUT[pixRange] = { 0 };
	Int    INV_EQUAL_LUT[pixRange] = { 0 };

	UChar* SPECI_IMG = (UChar*)calloc((wid * hei), sizeof(UChar));

	for (Int i = pixRange / 2; i < pixRange; i++)
		LUT_BUF[i] = 2048;

	Speci_Accum_Sum[0] = LUT_BUF[0];
	for (Int i = 1; i < pixRange; i++)
		Speci_Accum_Sum[i] = Speci_Accum_Sum[i - 1] + LUT_BUF[i];

	for (Int i = 0; i < pixRange; i++)
		INV_EQUAL_LUT[i] = ((double)max / ((double)wid * (double)hei)) * (double)Speci_Accum_Sum[i] + 0.5;

	Int Val1, Val2;
	for (Int i = 0; i < pixRange - 1; i++)
	{
		Val1 = INV_EQUAL_LUT[i];
		Val2 = INV_EQUAL_LUT[i + 1];
		if (Val1 != Val2)
		{
			for (Int j = Val1; j < Val2; j++)
				SPECI_LUT[j] = i + 1;
		}
		else
			SPECI_LUT[Val1] = 0;

	}
	SPECI_LUT[pixRange - 1] = max;

	for (Int i = 0; i < wid * hei; i++)
		SPECI_IMG[i] = SPECI_LUT[EQUAL_IMG[i]];

	ImageOutput(SPECI_IMG, wid, hei, String[1]);
	HISTOGRAM(SPECI_IMG, wid, hei, max, String[1]);
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	//End-in search
	
	UChar* End_IMG = (UChar*)calloc((wid * hei), sizeof(UChar));

	Int Low_num, High_num, Low_sum = 0, High_sum = 0;
	Int Low_Pos = 0, High_Pos = 255;
	
	////////////////////////////////////////////////////////////////
	//Low_Pos, High_Pos 구하기, 코드작성필요
	
	Low_num = wid * hei * (double)(LOW_Thres / 100.0);
	while (1) {
		Low_sum += LUT[Low_Pos];
		if (Low_num < Low_sum) break;
		Low_Pos++;
	}

	High_num = wid * hei * (double)(HIGH_Thres / 100.0);
	while (1)
	{
		High_sum += LUT[High_Pos];
		if (High_num < High_sum) break;
		High_Pos--;
	}
	////////////////////////////////////////////////////////////////

	for (int i = 0; i < wid * hei; i++)
	{
		if (Data[i] <= Low_Pos) End_IMG[i] = min;
		else if (Data[i] >= High_Pos) End_IMG[i] = max;
		else
		{
			double buf_out_pix;
			buf_out_pix = (((double)Data[i] - (double)Low_Pos) / ((double)High_Pos - (double)Low_Pos)) * 255.0 + 0.5;

			if (buf_out_pix < min)      End_IMG[i] = min;
			else if (buf_out_pix > max) End_IMG[i] = max;
			else                        End_IMG[i] = buf_out_pix;
		}
	}

	ImageOutput(End_IMG, wid, hei, String[2]);
	HISTOGRAM(End_IMG, wid, hei, max, String[2]);
	/////////////////////////////////////////////////////////////////

	free(EQUAL_IMG);
	free(SPECI_IMG);
	free(End_IMG);

}