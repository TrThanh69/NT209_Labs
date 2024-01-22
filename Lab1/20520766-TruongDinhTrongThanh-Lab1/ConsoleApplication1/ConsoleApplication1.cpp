#include <stdio.h>

void PrintBits(unsigned int x)
{
	int i;
	for (i = 8 * sizeof(x) - 1; i >= 0; i--)
	{
		(x & (1 << i)) ? putchar('1') : putchar('0');
	}
	printf("\n");
}
void PrintBitsOfByte(unsigned int x)
{
	int i;
	for (i = 7; i >= 0; i--)
	{
		(x & (1 << i)) ? putchar('1') : putchar('0');
	}
	printf("\n");
}

// 1.1
int bitAnd(int x, int y) //Sử dụng Định luật De morgan (4 toán tử)
{
	return ~(~x | ~y);
}

// 1.2
int negative(int x) //Chuyển sang bù 2 (1 toán tử)
{
	return ~x + 1;
}

// 1.3
int setBit(int x, int n) // Lấy x OR với Mask = 1 đã được dịch trái n bit (2 toán tử)
{
	return x | 1 << n;
}

// 1.4
int divpw2(int x, int n) //Chuyển n sang dạng bù 2 sau đó lấy x dịch trái n bit đó (2 toán tử)
{
	n = ~n + 1;
	return x << n;
}

// 1.5
int getnbit(int x, int n) // Thay đổi 32-n bit đầu = 0 (5 toán tử)
{
	x = ~x;
	int k = 0;
	k = ~k;
	k = k << n;
	return ~(x | k);
}

// 2.1
int isSameSign(int x, int y) // XOR 2 bit dấu nếu bằng 0 thì cùng dấu (4 toán tử)
{
	x = (x >> 31);
	y = (y >> 31);
	return !(x ^ y);
}

// 2.2
int is8x(int x) // Các số chia hết cho 8 đều có 3 bit cuối = 0 (2 toán tử)
{
	x = x << 29;
	x = !x;
	return x;
}

// 2.3
int isPositive(int x) // Kiểm tra bằng XOR (4 toán tử)
{
	return !(x >> 31) ^ !x;
}

// 2.4
int isLess2n(int x, int y) // Dịch phải n bit nếu khác 0 thì x > 2^n (2 toán tử)
{
	x = x >> y;
	x = !x;
	return x;
}

int main()
{
	int score = 0;
	printf("Your evaluation result:");
	printf("\n1.1");
	if (bitAnd(3, -9) == (3 & -9))
	{
		printf("\tPass.");
		score += 1;
	}
	else
		printf("\tFailed.");

	printf("\n1.2");
	if (negative(0) == 0 && negative(9) == -9 && negative(-5) == 5)
	{
		printf("\tPass.");
		score += 1;
	}
	else
		printf("\tFailed.");

	printf("\n1.3");
	if (setBit(6, 2) == 6 && setBit(5, 0) == 5 && setBit(32, 3) == 40)
	{
		printf("\tPass.");
		score += 2;
	}
	else
		printf("\tFailed.");

	printf("\n1.4");
	if (divpw2(10, -1) == 20 && divpw2(15, -2) == 60 && divpw2(2, -4 == 32))
	{
		printf("\tPass.");
		score += 3;
	}
	else
		printf("\tFailed.");

	printf("\n1.5");
	if (getnbit(0, 0) == 0 && getnbit(31, 3) == 7 && getnbit(16, 4) == 0)
	{
		printf("\tPass.");
		score += 3;
	}
	else
		printf("\tFailed.");

	printf("\n2.1");
	if (isSameSign(4, 2) && !isSameSign(13, -4) && isSameSign(0, 10))
	{
		printf("\tPass.");
		score += 2;
	}
	else
		printf("\tFailed.");

	printf("\n2.2");
	if (is8x(16) && !is8x(3) && is8x(0))
	{
		printf("\tPass.");
		score += 2;
	}
	else
		printf("\tFailed.");

	printf("\n2.3");
	if (isPositive(10) && !isPositive(-5) && !isPositive(0))
	{
		printf("\tPass.");
		score += 3;
	}
	else
		printf("\tFailed.");

	printf("\n2.4");
	if (isLess2n(12, 4) && !isLess2n(8, 3) && !isLess2n(15, 2))
	{
		printf("\tPass.");
		score += 3;
	}
	else
		printf("\tFailed.");

	printf("\n--- FINAL RESULT ---");
	printf("\nScore: %.1f", (float)score / 2);
	if (score < 5)
		printf("\nTrouble when solving these problems? Contact your instructor to get some hints :)");
	else
	{
		if (score < 8)
			printf("\nNice work. But try harder.");
		else
		{
			if (score >= 10)
				printf("\nExcellent. We found a master in bit-wise operations :D");
			else
				printf("\nYou're almost there. Think more carefully in failed problems.");
		}
	}

	printf("\n\n\n");
}