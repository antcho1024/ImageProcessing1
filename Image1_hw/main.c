#include "main.h"
#include "Arithmetic.h"
#include "Hist.h"
#include "Imgout.h"


void main()
{
	UChar *ori; //���� ���� ȭ�Ұ����� �����ϱ� ���� ����
	FILE *fp;

	Int wid = WIDTH; Int hei = HEIGHT;
	Int min = minVal; Int max = maxVal;

	Char String[5][10] = { "Ori", "Add" , "Sub" ,"Mul" ,"Div" };

	fopen_s(&fp, "lena_512x512.raw", "rb"); //���� ���� ����

	ori = (UChar*)malloc(sizeof(UChar) * (WIDTH * HEIGHT)); //���� ���� ũ�⸸ŭ ���� ����
	memset(ori, 0, sizeof(UChar) * (WIDTH * HEIGHT)); //0���� �ʱ�ȭ
	fread(ori, sizeof(UChar), (WIDTH * HEIGHT), fp); // ���� ���� �б�(���� ������ �ȼ� ���� �迭 ������ ����)

	Arithmetic_Operation(ori, wid, hei, min, max);
	HISTOGRAM_MODIFICATION(ori, wid, hei, max, min);
	HISTOGRAM(ori, wid, hei, max, String[0]); //������׷� ��� �Լ�

	free(ori);
	fclose(fp);
}