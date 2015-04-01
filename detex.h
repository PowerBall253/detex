/*

Copyright (c) 2015 Harm Hanemaaijer <fgenfb@yahoo.com>

Permission to use, copy, modify, and/or distribute this software for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

*/

#ifndef __DETEX_H__
#define __DETEX_H__

#undef __BEGIN_DECLS
#undef __END_DECLS
#ifdef __cplusplus
#define __BEGIN_DECLS extern "C" {
#define __END_DECLS }
#else
#define __BEGIN_DECLS /* empty */
#define __END_DECLS /* empty */
#endif

__BEGIN_DECLS

#include <stdint.h>
#include <stdbool.h>

#define DETEX_INLINE_ONLY __attribute__((always_inline)) inline

/* Maximum uncompressed block size in bytes. */
#define DETEX_MAX_BLOCK_SIZE 128

/* Detex library pixel formats. */

enum {
	/* The format has 16-bit components. */
	DETEX_PIXEL_FORMAT_16BIT_COMPONENT_BIT = 0x1,
	/* The format has an alpha component. */
	DETEX_PIXEL_FORMAT_ALPHA_COMPONENT_BIT = 0x2,
	/* The sequential component order is RGB. */
	DETEX_PIXEL_FORMAT_RGB_COMPONENT_ORDER_BIT = 0x0,
	/* The sequential component order is BGR. */
	DETEX_PIXEL_FORMAT_BGR_COMPONENT_ORDER_BIT = 0x4,
	/* The format has one component. */
	DETEX_PIXEL_FORMAT_ONE_COMPONENT_BIT = 0x0,
	/* The format has two components. */
	DETEX_PIXEL_FORMAT_TWO_COMPONENTS_BIT = 0x10,
	/* The format has three components. */
	DETEX_PIXEL_FORMAT_THREE_COMPONENTS_BIT = 0x20,
	/* The format has four components. */
	DETEX_PIXEL_FORMAT_FOUR_COMPONENTS_BIT = 0x30,
	/* The format is stored as 8-bit pixels. */
	DETEX_PIXEL_FORMAT_8BIT_PIXEL_BIT = 0x100,
	/* The format is stored as 16-bit pixels. */
	DETEX_PIXEL_FORMAT_16BIT_PIXEL_BIT = 0x200,
	/* The format is stored as 32-bit pixels. */
	DETEX_PIXEL_FORMAT_32BIT_PIXEL_BIT = 0x300,
	/* The format is stored as 64-bit pixels. */
	DETEX_PIXEL_FORMAT_64BIT_PIXEL_BIT = 0x400,
	/* The format has signed integer components. */
	DETEX_PIXEL_FORMAT_SIGNED_BIT = 0x1000,
	/* The format has (half-)float components. */
	DETEX_PIXEL_FORMAT_FLOAT_BIT = 0x2000,

	DETEX_PIXEL_FORMAT_RGBA8 = (
		DETEX_PIXEL_FORMAT_ALPHA_COMPONENT_BIT |
		DETEX_PIXEL_FORMAT_FOUR_COMPONENTS_BIT |
		DETEX_PIXEL_FORMAT_32BIT_PIXEL_BIT
		),
	DETEX_PIXEL_FORMAT_BGRA8 = (
		DETEX_PIXEL_FORMAT_ALPHA_COMPONENT_BIT |
		DETEX_PIXEL_FORMAT_BGR_COMPONENT_ORDER_BIT |
		DETEX_PIXEL_FORMAT_FOUR_COMPONENTS_BIT |
		DETEX_PIXEL_FORMAT_32BIT_PIXEL_BIT
		),
	DETEX_PIXEL_FORMAT_RGBX8 = (
		DETEX_PIXEL_FORMAT_THREE_COMPONENTS_BIT |
		DETEX_PIXEL_FORMAT_32BIT_PIXEL_BIT
		),
	DETEX_PIXEL_FORMAT_BGRX8 = (
		DETEX_PIXEL_FORMAT_BGR_COMPONENT_ORDER_BIT |
		DETEX_PIXEL_FORMAT_THREE_COMPONENTS_BIT |
		DETEX_PIXEL_FORMAT_32BIT_PIXEL_BIT
		),
	DETEX_PIXEL_FORMAT_R8 = (
		DETEX_PIXEL_FORMAT_ONE_COMPONENT_BIT |
		DETEX_PIXEL_FORMAT_8BIT_PIXEL_BIT
		),
	DETEX_PIXEL_FORMAT_RG8 = (
		DETEX_PIXEL_FORMAT_TWO_COMPONENTS_BIT |
		DETEX_PIXEL_FORMAT_16BIT_PIXEL_BIT
		),
	DETEX_PIXEL_FORMAT_R16 = (
		DETEX_PIXEL_FORMAT_16BIT_COMPONENT_BIT |
		DETEX_PIXEL_FORMAT_ONE_COMPONENT_BIT |
		DETEX_PIXEL_FORMAT_16BIT_PIXEL_BIT
		),
	DETEX_PIXEL_FORMAT_SIGNED_R16 = (
		DETEX_PIXEL_FORMAT_16BIT_COMPONENT_BIT |
		DETEX_PIXEL_FORMAT_ONE_COMPONENT_BIT |
		DETEX_PIXEL_FORMAT_16BIT_PIXEL_BIT |
		DETEX_PIXEL_FORMAT_SIGNED_BIT
		),
	DETEX_PIXEL_FORMAT_RG16 = (
		DETEX_PIXEL_FORMAT_16BIT_COMPONENT_BIT |
		DETEX_PIXEL_FORMAT_TWO_COMPONENTS_BIT |
		DETEX_PIXEL_FORMAT_32BIT_PIXEL_BIT
		),
	DETEX_PIXEL_FORMAT_SIGNED_RG16 = (
		DETEX_PIXEL_FORMAT_16BIT_COMPONENT_BIT |
		DETEX_PIXEL_FORMAT_TWO_COMPONENTS_BIT |
		DETEX_PIXEL_FORMAT_32BIT_PIXEL_BIT |
		DETEX_PIXEL_FORMAT_SIGNED_BIT
		),
	DETEX_PIXEL_FORMAT_FLOAT_RGBX16 = (
		DETEX_PIXEL_FORMAT_16BIT_COMPONENT_BIT |
		DETEX_PIXEL_FORMAT_THREE_COMPONENTS_BIT |
		DETEX_PIXEL_FORMAT_64BIT_PIXEL_BIT |
		DETEX_PIXEL_FORMAT_FLOAT_BIT
		),
	DETEX_PIXEL_FORMAT_FLOAT_BGRX16 = (
		DETEX_PIXEL_FORMAT_16BIT_COMPONENT_BIT |
		DETEX_PIXEL_FORMAT_BGR_COMPONENT_ORDER_BIT |
		DETEX_PIXEL_FORMAT_THREE_COMPONENTS_BIT |
		DETEX_PIXEL_FORMAT_64BIT_PIXEL_BIT |
		DETEX_PIXEL_FORMAT_FLOAT_BIT
		),
	DETEX_PIXEL_FORMAT_SIGNED_FLOAT_RGBX16 = (
		DETEX_PIXEL_FORMAT_16BIT_COMPONENT_BIT |
		DETEX_PIXEL_FORMAT_THREE_COMPONENTS_BIT |
		DETEX_PIXEL_FORMAT_64BIT_PIXEL_BIT |
		DETEX_PIXEL_FORMAT_SIGNED_BIT |
		DETEX_PIXEL_FORMAT_FLOAT_BIT
		),
	DETEX_PIXEL_FORMAT_SIGNED_FLOAT_BGRX16 = (
		DETEX_PIXEL_FORMAT_16BIT_COMPONENT_BIT |
		DETEX_PIXEL_FORMAT_BGR_COMPONENT_ORDER_BIT |
		DETEX_PIXEL_FORMAT_THREE_COMPONENTS_BIT |
		DETEX_PIXEL_FORMAT_64BIT_PIXEL_BIT |
		DETEX_PIXEL_FORMAT_SIGNED_BIT |
		DETEX_PIXEL_FORMAT_FLOAT_BIT
		),
};

/* Mode mask flags. */

enum {
	DETEX_MODE_MASK_ETC_INDIVIDUAL = 0x1,
	DETEX_MODE_MASK_ETC_DIFFERENTIAL = 0x2,
	DETEX_MODE_MASK_ETC_T = 0x4,
	DETEX_MODE_MASK_ETC_H = 0x8,
	DETEX_MODE_MASK_ETC_PLANAR = 0x10,
	DETEX_MODE_MASK_ALL_MODES_ETC1 = 0x3,
	DETEX_MODE_MASK_ALL_MODES_ETC2 = 0x1F,
	DETEX_MODE_MASK_ALL_MODES_ETC2_PUNCHTHROUGH = 0X1E,
	DETEX_MODE_MASK_ALL_MODES_BPTC = 0xFF,
	DETEX_MODE_MASK_ALL_MODES_BPTC_FLOAT = 0x3FFF,
	DETEX_MODE_MASK_ALL = 0XFFFFFFFF,
};

/* Decompression function flags. */

enum {
	/* Function returns false (invalid block) when the compressed block */
	/* is in a format not allowed to be generated by an encoder. */
	DETEX_DECOMPRESS_FLAG_ENCODE = 0x1,
	/* For compression formats that have opaque and non-opaque modes, */
	/* return false (invalid block) when the compressed block is encoded */
	/* using a non-opaque mode. */
	DETEX_DECOMPRESS_FLAG_OPAQUE_ONLY = 0x2,
	/* For compression formats that have opaque and non-opaque modes, */
	/* return false (invalid block) when the compressed block is encoded */
	/* using an opaque mode. */
	DETEX_DECOMPRESS_FLAG_NON_OPAQUE_ONLY = 0x4,
};

/* Set mode function flags. */

enum {
	/* The block is opaque (alpha is always 0xFF). */
	DETEX_SET_MODE_FLAG_OPAQUE = 0x2,
	/* The block is non-opaque (alpha is not always 0xFF). */
	DETEX_SET_MODE_FLAG_NON_OPAQUE = 0x4,
	/* The block has punchthrough alpha (alpha is either 0x00 or 0xFF). */
	DETEX_SET_MODE_FLAG_PUNCHTHROUGH = 0x8,
	/* The block only consists of one or two different pixel colors. */
	DETEX_SET_MODE_FLAG_MAX_TWO_COLORS = 0x10,
};

/*
 * Decompression functions for 8-bit RGB8/RGBA8 formats. The output pixel format
 * is DETEX_PIXEL_FORMAT_RGBA8 or DETEX_PIXEL_FORMAT_RGBX8 (32-bit pixels with
 * optional alpha component, red component in lowest-order byte. When the
 * texture format does not have alpha, alpha is set to 0xFF.
 */

/* Decompress a 64-bit 4x4 pixel texture block compressed using the ETC1 */
/* format. */
bool detexDecompressBlockETC1(const uint8_t *bitstring, uint32_t mode_mask,
	uint32_t flags, uint8_t *pixel_buffer);
/* Decompress a 64-bit 4x4 pixel texture block compressed using the ETC2 */
/* format. */
bool detexDecompressBlockETC2(const uint8_t *bitstring, uint32_t mode_mask,
	uint32_t flags, uint8_t *pixel_buffer);
/* Decompress a 64-bit 4x4 pixel texture block compressed using the */
/* ETC2_PUNCHTROUGH format. */
bool detexDecompressBlockETC2_PUNCHTHROUGH(const uint8_t *bitstring,
	uint32_t mode_mask, uint32_t flags, uint8_t *pixel_buffer);
/* Decompress a 128-bit 4x4 pixel texture block compressed using the ETC2_EAC */
/* format. */
bool detexDecompressBlockETC2_EAC(const uint8_t *bitstring, uint32_t mode_mask,
	uint32_t flags, uint8_t *pixel_buffer);


/* Decompress a 64-bit 4x4 pixel texture block compressed using the BC1 */
/* format. */
bool detexDecompressBlockBC1(const uint8_t *bitstring, uint32_t mode_mask,
	uint32_t flags, uint8_t *pixel_buffer);
/* Decompress a 64-bit 4x4 pixel texture block compressed using the BC1A */
/* format. */
bool detexDecompressBlockBC1A(const uint8_t *bitstring, uint32_t mode_mask,
	uint32_t flags, uint8_t *pixel_buffer);
/* Decompress a 64-bit 4x4 pixel texture block compressed using the BC2 */
/* format. */
bool detexDecompressBlockBC2(const uint8_t *bitstring, uint32_t mode_mask,
	uint32_t flags, uint8_t *pixel_buffer);
/* Decompress a 64-bit 4x4 pixel texture block compressed using the BC3 */
/* format. */
bool detexDecompressBlockBC3(const uint8_t *bitstring, uint32_t mode_mask,
	uint32_t flags, uint8_t *pixel_buffer);
/* Decompress a 128-bit 4x4 pixel texture block compressed using the BPTC */
/* (BC7) format. */
bool detexDecompressBlockBPTC(const uint8_t *bitstring, uint32_t mode_mask,
	uint32_t flags, uint8_t *pixel_buffer);

/*
 * Decompression functions for 8-bit unsigned R and RG formats. The
 * output format is DETEX_PIXEL_FORMAT_R8 or DETEX_PIXEL_FORMAT_RG8.
 */

/* Decompress a 64-bit 4x4 pixel texture block compressed using the */
/* unsigned RGTC1 (BC4) format. */
bool detexDecompressBlockRGTC1(const uint8_t *bitstring, uint32_t mode_mask,
	uint32_t flags, uint8_t *pixel_buffer);
/* Decompress a 128-bit 4x4 pixel texture block compressed using the */
/* unsigned RGTC2 (BC5) format. */
bool detexDecompressBlockRGTC2(const uint8_t *bitstring, uint32_t mode_mask,
	uint32_t flags, uint8_t *pixel_buffer);

/*
 * Decompression functions for 16-bit unsigned/signed R and RG formats. The
 * output format is DETEX_PIXEL_FORMAT_R16, DETEX_PIXEL_FORMAT_SIGNED_R16,
 * DETEX_PIXEL_FORMAT_RG16, or DETEX_PIXEL_FORMAT_SIGNED_RG16.
 */

/* Decompress a 64-bit 4x4 pixel texture block compressed using the */
/* signed RGTC1 (signed BC4) format. */
bool detexDecompressBlockSIGNED_RGTC1(const uint8_t *bitstring, uint32_t mode_mask,
	uint32_t flags, uint8_t *pixel_buffer);
/* Decompress a 128-bit 4x4 pixel texture block compressed using the */
/* signed RGTC2 (signed BC5) format. */
bool detexDecompressBlockSIGNED_RGTC2(const uint8_t *bitstring, uint32_t mode_mask,
	uint32_t flags, uint8_t *pixel_buffer);
/* Decompress a 64-bit 4x4 pixel texture block compressed using the */
/* ETC2_R11_EAC format. */
bool detexDecompressBlockEAC_R11(const uint8_t *bitstring, uint32_t mode_mask,
	uint32_t flags, uint8_t *pixel_buffer);
/* Decompress a 64-bit 4x4 pixel texture block compressed using the */
/* ETC2_SIGNED_R11_EAC format. */
bool detexDecompressBlockEAC_SIGNED_R11(const uint8_t *bitstring,
	uint32_t mode_mask, uint32_t flags, uint8_t *pixel_buffer);
/* Decompress a 128-bit 4x4 pixel texture block compressed using the */
/* ETC2_RG11_EAC format. */
bool detexDecompressBlockEAC_RG11(const uint8_t *bitstring, uint32_t mode_mask,
	uint32_t flags, uint8_t *pixel_buffer);
/* Decompress a 128-bit 4x4 pixel texture block compressed using the */
/* ETC2_SIGNED_RG11_EAC format. */
bool detexDecompressBlockEAC_SIGNED_RG11(const uint8_t *bitstring,
	uint32_t mode_mask, uint32_t flags, uint8_t *pixel_buffer);

/*
 * Decompression functions for 16-bit half-float formats. The output format is
 * DETEX_PIXEL_FORMAT_FLOAT_RGBX16 or DETEX_PIXEL_FORMAT_SIGNED_FLOAT_RGBX16.
 */

/* Decompress a 128-bit 4x4 pixel texture block compressed using the */
/* BPTC_FLOAT (BC6H) format. The output format is */
/* DETEX_PIXEL_FORMAT_FLOAT_RGBX16. */
bool detexDecompressBlockBPTC_FLOAT(const uint8_t *bitstring, uint32_t mode_mask,
	uint32_t flags, uint8_t *pixel_buffer);
/* Decompress a 128-bit 4x4 pixel texture block compressed using the */
/* BPTC_FLOAT (BC6H_FLOAT) format. The output format is */
/* DETEX_PIXEL_FORMAT_SIGNED_FLOAT_RGBX16. */
bool detexDecompressBlockBPTC_SIGNED_FLOAT(const uint8_t *bitstring,
	uint32_t mode_mask, uint32_t flags, uint8_t *pixel_buffer);


/*
 * Get mode functions. They return the internal compression format mode used
 * inside the compressed block.
 */

uint32_t detexGetModeETC1(const uint8_t *bitstring);
uint32_t detexGetModeETC2(const uint8_t *bitstring);
uint32_t detexGetModeETC2_PUNCHTHROUGH(const uint8_t *bitstring);
uint32_t detexGetModeETC2_EAC(const uint8_t *bitstring);

/*
 * Set mode functions. The set mode function modifies a compressed texture block
 * so that the specified mode is set, making use of information about the block
 * (whether it is opaque, non-opaque or punchthrough for formats with alpha,
 * whether at most two different colors are used).
 */

/*
 * Set mode functions for 8-bit RGB8/RGB8A formats. pixel_buffer is assumed to
 * be in DETEX_PIXEL_FORMAT_RGBA8 or DETEX_PIXEL_FORMAT_RGBX8 format.
 */

void detexSetModeETC1(uint8_t *bitstring, uint32_t mode, uint32_t flags,
	uint32_t *colors);


/* Compressed texture format definitions for general texture decompression */
/* functions. */

enum {
	DETEX_TEXTURE_FORMAT_BC1 = 0,
	DETEX_TEXTURE_FORMAT_BC1A,
	DETEX_TEXTURE_FORMAT_BC2,
	DETEX_TEXTURE_FORMAT_BC3,
	DETEX_TEXTURE_FORMAT_RGTC1,
	DETEX_TEXTURE_FORMAT_SIGNED_RGTC1,
	DETEX_TEXTURE_FORMAT_RGTC2,
	DETEX_TEXTURE_FORMAT_SIGNED_RGTC2,
	DETEX_TEXTURE_FORMAT_BPTC_FLOAT,
	DETEX_TEXTURE_FORMAT_BPTC_SIGNED_FLOAT,
	DETEX_TEXTURE_FORMAT_BPTC,
	DETEX_TEXTURE_FORMAT_ETC1,
	DETEX_TEXTURE_FORMAT_ETC2,
	DETEX_TEXTURE_FORMAT_ETC2_PUNCHTHROUGH,
	DETEX_TEXTURE_FORMAT_ETC2_EAC,
	DETEX_TEXTURE_FORMAT_EAC_R11,
	DETEX_TEXTURE_FORMAT_EAC_SIGNED_R11,
	DETEX_TEXTURE_FORMAT_EAC_RG11,
	DETEX_TEXTURE_FORMAT_EAC_SIGNED_RG11,
};

/*
 * General texture decompression functions (tiled or linear) with specifie
 * compression format.
 */

/*
 * General block decompression function. Block is decompressed using the given
 * compressed format, and stored in the given pixel format.
 */
bool detexDecompressBlock(const uint8_t *bitstring, uint32_t texture_format,
	uint32_t mode_mask, uint32_t flags, uint8_t *pixel_buffer,
	uint32_t pixel_format);

/*
 * Decode texture function (tiled). Decode an entire compressed texture into an
 * array of image buffer tiles (corresponding to compressed blocks), converting
 * into the given pixel format.
 */
bool detexDecompressTextureTiled(const uint8_t *bitstring, uint32_t texture_format,
	uint32_t width_in_blocks, uint32_t height_in_blocks, uint8_t *pixel_buffer,
	uint32_t pixel_format);

/*
 * Decode texture function (linear). Decode an entire texture into a single
 * image buffer, with pixels stored row-by-row, converting into the given pixel
 * format.
 */
bool detexDecompressTextureLinear(const uint8_t *bitstring, uint32_t texture_format,
	uint32_t width_in_blocks, uint32_t height_in_blocks, uint8_t *pixel_buffer,
	uint32_t pixel_format);


/*
 * Miscellaneous functions.
 */

/* Return size of compressed block in bytes given the texture format. */
uint32_t detexGetCompressedBlockSize(uint32_t texture_format);

/*
 * Convert pixels between different formats. Only valid for conversions
 * that do not change the precision or pixel size. The target pixel buffer must
 * be allocated with sufficient size to the hold the result. Returns true if
 * succesful.
 */
bool detexConvertPixels(uint8_t *source_pixel_buffer, uint32_t nu_pixels,
	uint32_t source_pixel_format, uint8_t *target_pixel_buffer,
	uint32_t target_pixel_format);

/* Return pixel size in bytes for pixel format. */
static DETEX_INLINE_ONLY int detexGetPixelSize(uint32_t pixel_format) {
	return 1 << (((pixel_format & 0x700) >> 8) - 1);
}

/* Return size of block in bytes for particular pixel format. */
static DETEX_INLINE_ONLY int detexGetBlockSize(uint32_t pixel_format) {
	return 16 * detexGetPixelSize(pixel_format);
}

/* Return the number of components of pixel format. */
static DETEX_INLINE_ONLY int detexGetNumberOfComponents(uint32_t pixel_format) {
	return 1 + ((pixel_format & 0x30) >> 4);
}

extern const uint8_t detex_clamp0to255_table[767];

/* Clamp a value in the range -255 to 511 to the the range 0 to 255. */
static DETEX_INLINE_ONLY uint8_t detexClamp0To255(int x) {
	return detex_clamp0to255_table[x + 255];
}

/*
 * Define some short functions for pixel packing/unpacking. The compiler will
 * take care of optimization by inlining and removing unused functions.
 *
 * The pixel format used corresponds to formats with an RGB component order,
 * including:
 *
 * DETEX_PIXEL_FORMAT_RGB8, DETEX_PIXEL_FORMAT_RGBA8
 *	detexPack32RGB8Alpha0xFF, detexPack32R8, detexPack32G8, detexPack32B8,
 *	detexPixel32GetR8, detexPixel32GetG8, detexPixel32GetB8
 * DETEX_PIXEL_FORMAT_RGBA8
 *	detexPack32RGBA8, detexPack32A8, detexPixel32GetA8
 * DETEX_PIXEL_FORMAT_RG16, DETEX_PIXEL_FORMAT_SIGNED_RG16,
 * DETEX_PIXEL_FORMAT_FLOAT_RG16
 *	detexPack32_rg16, detexPack32_r16, detexPack32_g16, detexPack32_rg16, detexPixel32Get_r16,
 *	detexPixel32Get_g16
 * DETEX_PIXEL_FORMAT_FLOAT_RGBX16, DETEX_PIXEL_FORMAT_SIGNED_FLOAT_RGBX16
 *	detexPack64_rgb16, detexPack64_r16, detexPack64_g16, detexPack64_b16, detexPixel64Get_r16,
 *	detexPixel64Get_g16, detexPixel64Get_b16
 */

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ || !defined(__BYTE_ORDER__)

static DETEX_INLINE_ONLY uint32_t detexPack32RGBA8(int r, int g, int b, int a) {
	return (uint32_t)r | ((uint32_t)g << 8) | ((uint32_t)b << 16) |
		((uint32_t)a << 24);
}

static DETEX_INLINE_ONLY uint32_t detexPack32RGB8Alpha0xFF(int r, int g, int b) {
	return detexPack32RGBA8(r, g, b, 0xFF);
}

static DETEX_INLINE_ONLY uint32_t detexPack32R8(int r) {
	return (uint32_t)r;
}

static DETEX_INLINE_ONLY uint32_t detexPack32G8(int g) {
	return (uint32_t)g << 8;
}

static DETEX_INLINE_ONLY uint32_t detexPack32B8(int b) {
	return (uint32_t)b << 16;
}

static DETEX_INLINE_ONLY uint32_t detexPack32A8(int a) {
	return (uint32_t)a << 24;
}

static DETEX_INLINE_ONLY uint32_t detexPack32R16(uint32_t r16) {
	return r16;
}

static DETEX_INLINE_ONLY uint32_t detexPack32G16(uint32_t g16) {
	return g16 << 16;
}

static DETEX_INLINE_ONLY uint32_t detexPack32RG16(uint32_t r16, uint32_t g16) {
	return r16 | (g16 << 16);
}

static DETEX_INLINE_ONLY uint64_t detexPack64R16(uint32_t r16) {
	return r16;
}

static DETEX_INLINE_ONLY uint64_t detexPack64G16(uint32_t g16) {
	return g16 << 16;
}

static DETEX_INLINE_ONLY uint64_t detexPack64B16(uint32_t b16) {
	return (uint64_t)b16 << 32;
}

static DETEX_INLINE_ONLY uint64_t detexPack64A16(uint32_t a16) {
	return (uint64_t)a16 << 48;
}

static DETEX_INLINE_ONLY uint64_t detexPack64RGB16(uint16_t r16, uint16_t g16, uint16_t b16) {
	return (uint64_t)r16 | ((uint64_t)g16 << 16) | ((uint64_t)b16 << 32);
}

static DETEX_INLINE_ONLY uint64_t detexPack64RGBA16(uint16_t r16, uint16_t g16, uint16_t b16, uint16_t a16) {
	return (uint64_t)r16 | ((uint64_t)g16 << 16) | ((uint64_t)b16 << 32) | ((uint64_t)a16 << 48);
}

static DETEX_INLINE_ONLY uint32_t detexPixel32GetR8(uint32_t pixel) {
	return pixel & 0xFF;
}

static DETEX_INLINE_ONLY uint32_t detexPixel32GetG8(uint32_t pixel) {
	return (pixel & 0xFF00) >> 8;
}

static DETEX_INLINE_ONLY uint32_t detexPixel32GetB8(uint32_t pixel) {
	return (pixel & 0xFF0000) >> 16;
}

static DETEX_INLINE_ONLY uint32_t detexPixel32GetA8(uint32_t pixel) {
	return (pixel & 0xFF000000) >> 24;
}

static DETEX_INLINE_ONLY int detexPixel32GetSignedR8(uint32_t pixel) {
	return (int8_t)(pixel & 0xFF);
}

static DETEX_INLINE_ONLY int detexPixel32GetSignedG8(uint32_t pixel) {
	return (int8_t)((pixel & 0xFF00) >> 8);
}

static DETEX_INLINE_ONLY uint32_t detexPixel32GetR16(uint32_t pixel) {
	return pixel & 0x0000FFFF;
}

static DETEX_INLINE_ONLY uint32_t detexPixel32GetG16(uint32_t pixel) {
	return (pixel & 0xFFFF0000) >> 16;
}

static DETEX_INLINE_ONLY int detexPixel32GetSignedR16(uint32_t pixel) {
	return (int16_t)(pixel & 0x0000FFFF);
}

static DETEX_INLINE_ONLY int detexPixel32GetSignedG16(uint32_t pixel) {
	return (int16_t)((pixel & 0xFFFF0000) >> 16);
}

static DETEX_INLINE_ONLY uint64_t detexPixel64GetR16(uint64_t pixel) {
	return pixel & 0xFFFF;
}

static DETEX_INLINE_ONLY uint64_t detexPixel64GetG16(uint64_t pixel) {
	return (pixel & 0xFFFF0000) >> 16;
}

static DETEX_INLINE_ONLY uint64_t detexPixel64GetB16(uint64_t pixel) {
	return (pixel & 0xFFFF00000000) >> 32;
}

static DETEX_INLINE_ONLY uint64_t detexPixel64GetA16(uint64_t pixel) {
	return (pixel & 0xFFFF000000000000) >> 48;
}

#define DETEX_PIXEL32_ALPHA_BYTE_OFFSET 3

#else

#error Big-endian byte order not supported.

static DETEX_INLINE_ONLY uint32_t detexPack32RGBA8(int r, int g, int b, int a) {
	return a | ((uint32_t)b << 8) | ((uint32_t)g << 16) | ((uint32_t)r << 24);
}

static DETEX_INLINE_ONLY uint32_t detexPack32RGB8Alpha0xFF(int r, int g, int b) {
	return pack_rgba(r, g, b, 0xFF);
}

static DETEX_INLINE_ONLY uint32_t detexPack32R8(int r) {
	return (uint32_t)r << 24;
}

static DETEX_INLINE_ONLY uint32_t detexPack32G8(int g) {
	return (uint32_t)g << 16;
}

static DETEX_INLINE_ONLY uint32_t detexPack32B8(int b) {
	return (uint32_t)b << 8;
}

static DETEX_INLINE_ONLY uint32_t detexPack32A8(int a) {
	return a;
}

static DETEX_INLINE_ONLY uint32_t detexPack32RG16(uint32_t r16, uint32_t g16) {
	return g16 | (r16 << 16);
}

static DETEX_INLINE_ONLY int detexPixel32GetR8(uint32_t pixel) {
	return (pixel & 0xFF000000) >> 24;
}

static DETEX_INLINE_ONLY int detexPixel32GetG8(uint32_t pixel) {
	return (pixel & 0xFF0000) >> 16;
}

static DETEX_INLINE_ONLY int detexPixel32GetB8(uint32_t pixel) {
	return (pixel & 0xFF00) >> 8;
}

static DETEX_INLINE_ONLY int detexPixel32GetA8(uint32_t pixel) {
	return pixel & 0xFF;
}

static DETEX_INLINE_ONLY uint32_t detexPixel32GetR16(uint32_t pixel) {
	return ((pixel & 0xFF000000) >> 24) | ((pixel & 0x00FF0000) >> 8);
}

static DETEX_INLINE_ONLY uint32_t detexPixel32GetG16(uint32_t pixel) {
	return ((pixel & 0x0000FF00) >> 8) | ((pixel & 0x000000FF) << 8);
}

#define DETEX_PIXEL32_ALPHA_BYTE_OFFSET 0

#endif

__END_DECLS

#endif
