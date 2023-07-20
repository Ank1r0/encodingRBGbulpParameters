#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iomanip>

typedef unsigned char byte;

#define RED 4
#define GREEN 2
#define BLUE 1

typedef struct
{
	char status; // 1 bit
	char brightness; // 4 bit
	char red; // 1 bit
	char green; // 1 bit
	char blue; // 1 bit
} light;

void prnBin(byte b)
{
	for (int i = 7; i >= 0; --i)
	{
		printf("%d", b >> i & 1);
	}
	printf("\n");
}

unsigned char pack(light a)
{
	byte lightSettings = a.status << 7;
	lightSettings |= a.brightness << 3;
	lightSettings |= a.red << 2;
	lightSettings |= a.green << 1;
	lightSettings |= a.blue;
	prnBin(lightSettings);
	printf("%x\n", lightSettings);
	return lightSettings;
}
void unpack(unsigned char SettingsCode, light settings)
{


	printf("status = %d ", SettingsCode >> 7 & 1);
	settings.status = SettingsCode >> 7 & 1;
	int c = 0;
	for (int i = 6, k = 8; i > 2; --i, k /= 2)
	{
		if (SettingsCode >> i & 1 > 0)
		{
			c += k;
		}


	}
	printf("brigtness = %d ", c);
	settings.brightness = c;

	printf("red = %d ", SettingsCode >> 2 & 1);
	settings.red = SettingsCode >> 2 & 1;

	printf("green = %d ", SettingsCode >> 1 & 1);
	settings.green = SettingsCode >> 1 & 1;

	printf("blu = %d\n", SettingsCode >> 0 & 1);
	settings.blue = SettingsCode >> 0 & 1;

}

byte setColor(byte a, byte color)
{
	return a | color;
}

int main(int argc, char argv[])
{


	light light1;
	light1.blue = 0;
	light1.red = 0;
	light1.green = 0;
	light1.brightness = 7;
	light1.status = 1;
	byte temp = pack(light1);

	unpack(pack(light1), light1);
	prnBin(setColor(temp, GREEN | BLUE));

	byte a = 0xff;
	unpack(a, light1);
	printf("light\n%d\n %d\n %d\n %d\n %d\n", light1.status, light1.brightness, light1.red, light1.green, light1.blue);
	system("pause");
	return 0;
}