#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <iostream>
#include <sstream>


extern "C" const char* ASM_base64_stub(uint64_t str1_6chr, uint64_t str2_6chr);

/////////////////////////////////////////////////////////////////////////////////////

void  G_cout_ui32(uint32_t srcval)
{
	auto  tohex = [](uint8_t chr) -> char { return  chr < 10 ? chr + 0x30 : chr + 0x30 + 7 + 0x20; };
	auto  cout_bytes = [&](uint8_t byte, char* pdst) {
		*pdst++ = tohex( byte >> 4);
		*pdst = tohex( byte & 0xf );
	};
	char  hexes[] = "00 00 00 00  ";

	cout_bytes( srcval >> 24, hexes);

	srcval &= 0xff'ffff;
	cout_bytes( srcval >> 16, hexes + 3);

	srcval &= 0xffff;
	cout_bytes( srcval >> 8, hexes + 6);

	cout_bytes( srcval & 0xff, hexes + 9);

	std::cout << hexes;
}

void  G_out_ui8_16(const uint8_t* psrc_ui8)
{
	for (int i = 0; i < 4; ++i)
	{
		uint32_t  val_ui32 = (*psrc_ui8++ << 24) + (*psrc_ui8++ << 16) + (*psrc_ui8++ << 8) + *psrc_ui8++;
		G_cout_ui32(val_ui32);
	}
	std::cout << std::endl;
}

void  G_out_char_16(const char* psrc)
{
	const uint8_t* const psrc_bgn = (const uint8_t*)psrc;

	char  str[16 + 4 + 1];		// 0x20 ４文字分
	char*  pdst = str;
	for (int i = 0; i < 16; ++i)
	{
		*pdst++ = *psrc++;
		if ((i & 3) == 3)
		{ *pdst++ = 0x20; }
	}
	*pdst = 0;

	std::cout << str << std::endl;
}

/////////////////////////////////////////////////////////////////////////////////////

int main()
{
	uint64_t  str1_6chr = 0x4142'43444546;
	uint64_t  str2_6chr = 0x3132'33343536;

	const char*  pret_str = ASM_base64_stub(str1_6chr, str2_6chr);
	G_out_ui8_16((uint8_t*)pret_str);
	G_out_char_16(pret_str);

    return  0;
}
