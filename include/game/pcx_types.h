#ifndef PCX_TYPES_9
#define PCX_TYPES_9

struct gl_texture_t
{
	u16 width;
	u16 height;

	int format;
	int internalFormat;
	u32 id;

	u8 *texels;
	u16 *palette;
};

#endif
