#ifndef __BITMAP_H__
#define __BITMAP_H__

typedef struct BitmapFlagsType {
	UInt16 compressed:1;  			// Data format:  0=raw; 1=compressed
	UInt16 hasColorTable:1;			// if true, color table stored before bits[]
	UInt16 hasTransparency:1;		// true if transparency is used
	UInt16 indirect:1;				// true if bits are stored indirectly
	UInt16 forScreen:1;				// system use only
	UInt16 reserved:11;
} BitmapFlagsType;


// this definition correspond to the 'Tbmp' and 'tAIB' resource types
typedef struct BitmapType {
	Int16  				width;
	Int16  				height;
	UInt16  				rowBytes;
	BitmapFlagsType	flags;
	UInt8					pixelSize;			// bits/pixel
	UInt8					version;				// version of bitmap. This is vers 2
	UInt16	 			nextDepthOffset;	// # of DWords to next BitmapType
													//  from beginnning of this one
	UInt8					transparentIndex;	// v2 only, if flags.hasTransparency is true,
													// index number of transparent color
	UInt8					compressionType;	// v2 only, if flags.compressed is true, this is
													// the type, see BitmapCompressionType
														
	UInt16	 			reserved;			// for future use, must be zero!
	
	// [colorTableType] pixels | pixels*
	                                    // If hasColorTable != 0, we have:
	                                    //   ColorTableType followed by pixels. 
													// If hasColorTable == 0:
	                                    //   this is the start of the pixels
	                                    // if indirect != 0 bits are stored indirectly.
	                                    //	  the address of bits is stored here
	                                    //   In some cases the ColorTableType will
	                                    //   have 0 entries and be 2 bytes long.
} BitmapType;

typedef BitmapType *BitmapPtr;


#endif // __BITMAP_H__
