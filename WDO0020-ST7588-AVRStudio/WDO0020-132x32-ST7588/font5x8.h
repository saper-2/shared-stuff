#ifndef _FONT3310_H_
#define _FONT3310_H_

// font size
#define GPH_CHAR_WIDTH 5
#define GPH_CHAR_HEIGHT 8

#define GPH_CHAR_START 32
#define GPH_CHAR_COUNT 95 // chars count in array

#define GPH_FONT_NAME g_font5x8

// set "1" if font column will be written form top to bottom (begin from MSB) 
// ,or 0 if in opposite direction (begin form LSB)
#define GPH_FONT_COLUMN_UP_DOWN 0

PROGMEM const uint8_t g_font5x8[] = {
	0x00, 0x00, 0x00, 0x00, 0x00,  // Id=1,0x0001 Code=[32,0x20] Name="space" Char=[ ]
	0x00, 0x00, 0x2f, 0x00, 0x00,  // Id=2,0x0002 Code=[33,0x21] Name="exclam" Char=[!]
	0x00, 0x07, 0x00, 0x07, 0x00,  // Id=3,0x0003 Code=[34,0x22] Name="quotedbl" Char=["]
	0x14, 0x3e, 0x14, 0x3e, 0x14,  // Id=4,0x0004 Code=[35,0x23] Name="numbersign" Char=[#]
	0x04, 0x2a, 0x3e, 0x2a, 0x10,  // Id=5,0x0005 Code=[36,0x24] Name="dollar" Char=[$]
	0x13, 0x08, 0x04, 0x32, 0x00,  // Id=6,0x0006 Code=[37,0x25] Name="percent" Char=[%]
	0x14, 0x2a, 0x14, 0x20, 0x00,  // Id=7,0x0007 Code=[38,0x26] Name="ampersand" Char=[&]
	0x00, 0x00, 0x07, 0x00, 0x00,  // Id=8,0x0008 Code=[39,0x27] Name="quotesingle" Char=[']
	0x00, 0x1e, 0x21, 0x00, 0x00,  // Id=9,0x0009 Code=[40,0x28] Name="parenleft" Char=[(]
	0x00, 0x21, 0x1e, 0x00, 0x00,  // Id=10,0x000A Code=[41,0x29] Name="parenright" Char=[)]
	0x00, 0x2a, 0x1c, 0x2a, 0x00,  // Id=11,0x000B Code=[42,0x2a] Name="asterisk" Char=[*]
	0x08, 0x08, 0x3e, 0x08, 0x08,  // Id=12,0x000C Code=[43,0x2b] Name="plus" Char=[+]
	0x00, 0x40, 0x30, 0x10, 0x00,  // Id=13,0x000D Code=[44,0x2c] Name="comma" Char=[,]
	0x08, 0x08, 0x08, 0x08, 0x00,  // Id=14,0x000E Code=[45,0x2d] Name="hyphen" Char=[-]
	0x00, 0x30, 0x30, 0x00, 0x00,  // Id=15,0x000F Code=[46,0x2e] Name="period" Char=[.]
	0x10, 0x08, 0x04, 0x02, 0x00,  // Id=16,0x0010 Code=[47,0x2f] Name="slash" Char=[/]
	0x00, 0x1e, 0x21, 0x1e, 0x00,  // Id=17,0x0011 Code=[48,0x30] Name="zero" Char=[0]
	0x00, 0x22, 0x3f, 0x20, 0x00,  // Id=18,0x0012 Code=[49,0x31] Name="one" Char=[1]
	0x22, 0x31, 0x29, 0x26, 0x00,  // Id=19,0x0013 Code=[50,0x32] Name="two" Char=[2]
	0x11, 0x25, 0x25, 0x1b, 0x00,  // Id=20,0x0014 Code=[51,0x33] Name="three" Char=[3]
	0x0c, 0x0a, 0x3f, 0x08, 0x00,  // Id=21,0x0015 Code=[52,0x34] Name="four" Char=[4]
	0x17, 0x25, 0x25, 0x19, 0x00,  // Id=22,0x0016 Code=[53,0x35] Name="five" Char=[5]
	0x1e, 0x25, 0x25, 0x18, 0x00,  // Id=23,0x0017 Code=[54,0x36] Name="six" Char=[6]
	0x01, 0x31, 0x0d, 0x03, 0x00,  // Id=24,0x0018 Code=[55,0x37] Name="seven" Char=[7]
	0x1a, 0x25, 0x25, 0x1a, 0x00,  // Id=25,0x0019 Code=[56,0x38] Name="eight" Char=[8]
	0x06, 0x29, 0x29, 0x1e, 0x00,  // Id=26,0x001A Code=[57,0x39] Name="nine" Char=[9]
	0x00, 0x36, 0x36, 0x00, 0x00,  // Id=27,0x001B Code=[58,0x3a] Name="colon" Char=[:]
	0x40, 0x36, 0x16, 0x00, 0x00,  // Id=28,0x001C Code=[59,0x3b] Name="semicolon" Char=[;]
	0x00, 0x08, 0x14, 0x22, 0x00,  // Id=29,0x001D Code=[60,0x3c] Name="less" Char=[<]
	0x14, 0x14, 0x14, 0x14, 0x00,  // Id=30,0x001E Code=[61,0x3d] Name="equal" Char=[=]
	0x00, 0x22, 0x14, 0x08, 0x00,  // Id=31,0x001F Code=[62,0x3e] Name="greater" Char=[>]
	0x00, 0x02, 0x29, 0x06, 0x00,  // Id=32,0x0020 Code=[63,0x3f] Name="question" Char=[?]
	0x1e, 0x21, 0x2d, 0x0e, 0x00,  // Id=33,0x0021 Code=[64,0x40] Name="at" Char=[@]
	0x3e, 0x09, 0x09, 0x3e, 0x00,  // Id=34,0x0022 Code=[65,0x41] Name="A" Char=[A]
	0x3f, 0x25, 0x25, 0x1a, 0x00,  // Id=35,0x0023 Code=[66,0x42] Name="B" Char=[B]
	0x1e, 0x21, 0x21, 0x12, 0x00,  // Id=36,0x0024 Code=[67,0x43] Name="C" Char=[C]
	0x3f, 0x21, 0x21, 0x1e, 0x00,  // Id=37,0x0025 Code=[68,0x44] Name="D" Char=[D]
	0x3f, 0x25, 0x25, 0x21, 0x00,  // Id=38,0x0026 Code=[69,0x45] Name="E" Char=[E]
	0x3f, 0x05, 0x05, 0x01, 0x00,  // Id=39,0x0027 Code=[70,0x46] Name="F" Char=[F]
	0x1e, 0x21, 0x29, 0x3a, 0x00,  // Id=40,0x0028 Code=[71,0x47] Name="G" Char=[G]
	0x3f, 0x04, 0x04, 0x3f, 0x00,  // Id=41,0x0029 Code=[72,0x48] Name="H" Char=[H]
	0x00, 0x21, 0x3f, 0x21, 0x00,  // Id=42,0x002A Code=[73,0x49] Name="I" Char=[I]
	0x10, 0x20, 0x20, 0x1f, 0x00,  // Id=43,0x002B Code=[74,0x4a] Name="J" Char=[J]
	0x3f, 0x0c, 0x12, 0x21, 0x00,  // Id=44,0x002C Code=[75,0x4b] Name="K" Char=[K]
	0x3f, 0x20, 0x20, 0x20, 0x00,  // Id=45,0x002D Code=[76,0x4c] Name="L" Char=[L]
	0x3f, 0x06, 0x06, 0x3f, 0x00,  // Id=46,0x002E Code=[77,0x4d] Name="M" Char=[M]
	0x3f, 0x06, 0x18, 0x3f, 0x00,  // Id=47,0x002F Code=[78,0x4e] Name="N" Char=[N]
	0x1e, 0x21, 0x21, 0x1e, 0x00,  // Id=48,0x0030 Code=[79,0x4f] Name="O" Char=[O]
	0x3f, 0x09, 0x09, 0x06, 0x00,  // Id=49,0x0031 Code=[80,0x50] Name="P" Char=[P]
	0x1e, 0x31, 0x21, 0x5e, 0x00,  // Id=50,0x0032 Code=[81,0x51] Name="Q" Char=[Q]
	0x3f, 0x09, 0x19, 0x26, 0x00,  // Id=51,0x0033 Code=[82,0x52] Name="R" Char=[R]
	0x12, 0x25, 0x29, 0x12, 0x00,  // Id=52,0x0034 Code=[83,0x53] Name="S" Char=[S]
	0x00, 0x01, 0x3f, 0x01, 0x00,  // Id=53,0x0035 Code=[84,0x54] Name="T" Char=[T]
	0x1f, 0x20, 0x20, 0x1f, 0x00,  // Id=54,0x0036 Code=[85,0x55] Name="U" Char=[U]
	0x0f, 0x30, 0x30, 0x0f, 0x00,  // Id=55,0x0037 Code=[86,0x56] Name="V" Char=[V]
	0x3f, 0x18, 0x18, 0x3f, 0x00,  // Id=56,0x0038 Code=[87,0x57] Name="W" Char=[W]
	0x33, 0x0c, 0x0c, 0x33, 0x00,  // Id=57,0x0039 Code=[88,0x58] Name="X" Char=[X]
	0x00, 0x07, 0x38, 0x07, 0x00,  // Id=58,0x003A Code=[89,0x59] Name="Y" Char=[Y]
	0x31, 0x29, 0x25, 0x23, 0x00,  // Id=59,0x003B Code=[90,0x5a] Name="Z" Char=[Z]
	0x00, 0x3f, 0x21, 0x21, 0x00,  // Id=60,0x003C Code=[91,0x5b] Name="bracketleft" Char=[[]
	0x02, 0x04, 0x08, 0x10, 0x00,  // Id=61,0x003D Code=[92,0x5c] Name="backslash" Char=[\]
	0x00, 0x21, 0x21, 0x3f, 0x00,  // Id=62,0x003E Code=[93,0x5d] Name="bracketright" Char=[]]
	0x00, 0x02, 0x01, 0x02, 0x00,  // Id=63,0x003F Code=[94,0x5e] Name="asciicircum" Char=[^]
	0x20, 0x20, 0x20, 0x20, 0x00,  // Id=64,0x0040 Code=[95,0x5f] Name="underscore" Char=[_]
	0x00, 0x01, 0x02, 0x00, 0x00,  // Id=65,0x0041 Code=[96,0x60] Name="grave" Char=[`]
	0x18, 0x24, 0x14, 0x3c, 0x00,  // Id=66,0x0042 Code=[97,0x61] Name="a" Char=[a]
	0x3f, 0x24, 0x24, 0x18, 0x00,  // Id=67,0x0043 Code=[98,0x62] Name="b" Char=[b]
	0x18, 0x24, 0x24, 0x00, 0x00,  // Id=68,0x0044 Code=[99,0x63] Name="c" Char=[c]
	0x18, 0x24, 0x24, 0x3f, 0x00,  // Id=69,0x0045 Code=[100,0x64] Name="d" Char=[d]
	0x18, 0x34, 0x2c, 0x08, 0x00,  // Id=70,0x0046 Code=[101,0x65] Name="e" Char=[e]
	0x08, 0x3e, 0x09, 0x02, 0x00,  // Id=71,0x0047 Code=[102,0x66] Name="f" Char=[f]
	0x28, 0x54, 0x54, 0x4c, 0x00,  // Id=72,0x0048 Code=[103,0x67] Name="g" Char=[g]
	0x3f, 0x04, 0x04, 0x38, 0x00,  // Id=73,0x0049 Code=[104,0x68] Name="h" Char=[h]
	0x00, 0x24, 0x3d, 0x20, 0x00,  // Id=74,0x004A Code=[105,0x69] Name="i" Char=[i]
	0x00, 0x20, 0x40, 0x3d, 0x00,  // Id=75,0x004B Code=[106,0x6a] Name="j" Char=[j]
	0x3f, 0x08, 0x14, 0x20, 0x00,  // Id=76,0x004C Code=[107,0x6b] Name="k" Char=[k]
	0x00, 0x21, 0x3f, 0x20, 0x00,  // Id=77,0x004D Code=[108,0x6c] Name="l" Char=[l]
	0x3c, 0x08, 0x0c, 0x38, 0x00,  // Id=78,0x004E Code=[109,0x6d] Name="m" Char=[m]
	0x3c, 0x04, 0x04, 0x38, 0x00,  // Id=79,0x004F Code=[110,0x6e] Name="n" Char=[n]
	0x18, 0x24, 0x24, 0x18, 0x00,  // Id=80,0x0050 Code=[111,0x6f] Name="o" Char=[o]
	0x7c, 0x24, 0x24, 0x18, 0x00,  // Id=81,0x0051 Code=[112,0x70] Name="p" Char=[p]
	0x18, 0x24, 0x24, 0x7c, 0x00,  // Id=82,0x0052 Code=[113,0x71] Name="q" Char=[q]
	0x3c, 0x04, 0x04, 0x08, 0x00,  // Id=83,0x0053 Code=[114,0x72] Name="r" Char=[r]
	0x28, 0x2c, 0x34, 0x14, 0x00,  // Id=84,0x0054 Code=[115,0x73] Name="s" Char=[s]
	0x04, 0x1f, 0x24, 0x20, 0x00,  // Id=85,0x0055 Code=[116,0x74] Name="t" Char=[t]
	0x1c, 0x20, 0x20, 0x3c, 0x00,  // Id=86,0x0056 Code=[117,0x75] Name="u" Char=[u]
	0x00, 0x1c, 0x20, 0x1c, 0x00,  // Id=87,0x0057 Code=[118,0x76] Name="v" Char=[v]
	0x3c, 0x30, 0x30, 0x3c, 0x00,  // Id=88,0x0058 Code=[119,0x77] Name="w" Char=[w]
	0x24, 0x18, 0x18, 0x24, 0x00,  // Id=89,0x0059 Code=[120,0x78] Name="x" Char=[x]
	0x0c, 0x50, 0x20, 0x1c, 0x00,  // Id=90,0x005A Code=[121,0x79] Name="y" Char=[y]
	0x24, 0x34, 0x2c, 0x24, 0x00,  // Id=91,0x005B Code=[122,0x7a] Name="z" Char=[z]
	0x00, 0x04, 0x1e, 0x21, 0x00,  // Id=92,0x005C Code=[123,0x7b] Name="braceleft" Char=[{]
	0x00, 0x00, 0x3f, 0x00, 0x00,  // Id=93,0x005D Code=[124,0x7c] Name="bar" Char=[|]
	0x00, 0x21, 0x1e, 0x04, 0x00,  // Id=94,0x005E Code=[125,0x7d] Name="braceright" Char=[}]
	0x02, 0x01, 0x02, 0x01, 0x00  // Id=95,0x005F Code=[126,0x7e] Name="asciitilde" Char=[~]
};


#endif
