
#define  Fireball_WIDTH   16
#define  Fireball_HEIGHT  32


const unsigned short FireballData[] = {
                    0x0000, 0x0000, 0x6A59, 0x6A72, 0x0000, 0x0000, 0x7B7B, 0x7B7B, 0x0000, 0x6A00,
                    0x4962, 0x1149, 0x0000, 0x7251, 0x7451, 0x7E7D, 0x0000, 0x7A5A, 0x7E63, 0x7E7E,
                    0x0000, 0x7262, 0x7E6C, 0x7E7E, 0x0000, 0x7262, 0x7E75, 0x7E7E, 0x0000, 0x2A21,
                    0x7E75, 0x7E7E, 0x005A, 0x0000, 0x0000, 0x0000, 0x6A7B, 0x0049, 0x0000, 0x0000,
                    0x7B72, 0x6A7B, 0x0049, 0x0000, 0x7A59, 0x7B7A, 0x005A, 0x0000, 0x625B, 0x7A7A,
                    0x006A, 0x0000, 0x5A7E, 0x7272, 0x0072, 0x0000, 0x6C7E, 0x7259, 0x0072, 0x0000,
                    0x757E, 0x7219, 0x006A, 0x0000, 0x0000, 0x2A19, 0x7E6C, 0x7E7E, 0x0000, 0x2A11,
                    0x7E6B, 0x7E7E, 0x0000, 0x2911, 0x7E63, 0x7D7D, 0x0000, 0x2100, 0x7C11, 0x7D7D,
                    0x0000, 0x1900, 0x6B11, 0x7D7D, 0x0000, 0x1900, 0x6219, 0xBDBD, 0x0000, 0x1100,
                    0x5A19, 0x7CBD, 0x0000, 0x0000, 0x5121, 0x63BD, 0x6C7E, 0x3219, 0x0062, 0x0000,
                    0x637E, 0x3219, 0x0059, 0x0000, 0x5A7E, 0x2A21, 0x0011, 0x0000, 0x195A, 0x1129,
                    0x0000, 0x0000, 0x2911, 0x0021, 0x0000, 0x0000, 0x2919, 0x0011, 0x0000, 0x0000,
                    0x2129, 0x0049, 0x0000, 0x0000, 0x4949, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x5121, 0x5A7C, 0x0000, 0x0000, 0x5129, 0x195A, 0x0000, 0x0000, 0x1129, 0x2100,
                    0x0000, 0x4900, 0x1921, 0x2911, 0x0000, 0x0000, 0x1919, 0x2919, 0x0000, 0x0000,
                    0x2119, 0x2121, 0x0000, 0x0000, 0x2919, 0x1129, 0x0000, 0x0000, 0x2919, 0x1121,
                    0x4949, 0x0000, 0x0000, 0x0000, 0x4949, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x2149, 0x0019, 0x0000, 0x0000, 0x2149, 0x0019,
                    0x0000, 0x0000, 0x2100, 0x0011, 0x0000, 0x0000, 0x2100, 0x0011, 0x0000, 0x0000,
                    0x2100, 0x0011, 0x0000, 0x0000, 0x1100, 0x0049, 0x0000, 0x0000, 0x4900, 0x0049,
                    0x0000, 0x0000, 0x4900, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,};

const unsigned short FireballPalette[] = {
                    0x0000, 0x0010, 0x0200, 0x0210, 0x4000, 0x4010, 0x4200, 0x6318, 0x6378, 0x7B34,
                    0x0088, 0x008C, 0x0090, 0x0094, 0x0098, 0x009C, 0x0100, 0x0104, 0x0108, 0x010C,
                    0x0110, 0x0114, 0x0118, 0x011C, 0x0180, 0x0184, 0x0188, 0x018C, 0x0190, 0x0194,
                    0x0198, 0x019C, 0x0200, 0x0204, 0x0208, 0x020C, 0x0210, 0x0214, 0x0218, 0x021C,
                    0x0280, 0x0284, 0x0288, 0x028C, 0x0290, 0x0294, 0x0298, 0x029C, 0x0300, 0x0304,
                    0x0308, 0x030C, 0x0310, 0x0314, 0x0318, 0x031C, 0x0380, 0x0384, 0x0388, 0x038C,
                    0x0390, 0x0394, 0x0398, 0x039C, 0x2000, 0x2004, 0x2008, 0x200C, 0x2010, 0x2014,
                    0x2018, 0x201C, 0x2080, 0x2084, 0x2088, 0x208C, 0x2090, 0x2094, 0x2098, 0x209C,
                    0x2100, 0x2104, 0x2108, 0x210C, 0x2110, 0x2114, 0x2118, 0x211C, 0x2180, 0x2184,
                    0x2188, 0x218C, 0x2190, 0x2194, 0x2198, 0x219C, 0x2200, 0x2204, 0x2208, 0x220C,
                    0x2210, 0x2214, 0x2218, 0x221C, 0x2280, 0x2284, 0x2288, 0x228C, 0x2290, 0x2294,
                    0x2298, 0x229C, 0x2300, 0x2304, 0x2308, 0x230C, 0x2310, 0x2314, 0x2318, 0x231C,
                    0x2380, 0x2384, 0x2388, 0x238C, 0x2390, 0x2394, 0x2398, 0x239C, 0x4000, 0x4004,
                    0x4008, 0x400C, 0x4010, 0x4014, 0x4018, 0x401C, 0x4080, 0x4084, 0x4088, 0x408C,
                    0x4090, 0x4094, 0x4098, 0x409C, 0x4100, 0x4104, 0x4108, 0x410C, 0x4110, 0x4114,
                    0x4118, 0x411C, 0x4180, 0x4184, 0x4188, 0x418C, 0x4190, 0x4194, 0x4198, 0x419C,
                    0x4200, 0x4204, 0x4208, 0x420C, 0x4210, 0x4214, 0x4218, 0x421C, 0x4280, 0x4284,
                    0x4288, 0x428C, 0x4290, 0x4294, 0x4298, 0x429C, 0x4300, 0x4304, 0x4308, 0x430C,
                    0x4310, 0x4314, 0x4318, 0x431C, 0x4380, 0x4384, 0x4388, 0x438C, 0x4390, 0x4394,
                    0x4398, 0x439C, 0x6000, 0x6004, 0x6008, 0x600C, 0x6010, 0x6014, 0x6018, 0x601C,
                    0x6080, 0x6084, 0x6088, 0x608C, 0x6090, 0x6094, 0x6098, 0x609C, 0x6100, 0x6104,
                    0x6108, 0x610C, 0x6110, 0x6114, 0x6118, 0x611C, 0x6180, 0x6184, 0x6188, 0x618C,
                    0x6190, 0x6194, 0x6198, 0x619C, 0x6200, 0x6204, 0x6208, 0x620C, 0x6210, 0x6214,
                    0x6218, 0x621C, 0x6280, 0x6284, 0x6288, 0x628C, 0x6290, 0x6294, 0x6298, 0x629C,
                    0x6300, 0x6304, 0x6308, 0x630C, 0x6310, 0x6314, 0x7BFF, 0x5294, 0x4210, 0x001F,
                    0x03E0, 0x03FF, 0x7C00, 0x7C1F, 0x7FE0, 0x7FFF,};