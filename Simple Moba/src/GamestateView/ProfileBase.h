#if !defined(PROFILEBASE_H)
#define PROFILEBASE_H


enum AspectRatioState
{
	aspect4x3,
	aspect5x4,
	aspect16x9,
	aspect16x10,
	aspectCount
};

enum ResolutionState
{
	// 4x3 Aspect ratios
	resolution800x600,
	resolution1024x768,
	resolution1152x864,
	resolution1600x1200,

	// 5x4 Aspect ratios
	resolution1265x985,
	resolution1280x1024,
	resolution1800x1440,

	// 16x9 Aspect ratios
	resolution1280x720,
	resolution1536x864,
	resolution1600x900,
	resolution1920x1080,
	resolution2560x1440,

	// 16x10 Aspect ratios
	resolution1280x800,
	resolution1440x900,
	resolution1680x1050,
	resolution1920x1200,

	resolutionCount

};

enum EnumResolutionParts
{
	WidthValue,
	HeightValue
};

enum BoundsParts
{
	boundsHorizontalAlign,
	boundsVerticalAlign,
	boundsPartPositionX,
	boundsPartPositionY,
	boundsScale,
	boundsImageWidth,
	boundsImageHeight,
	boundsResWidth,
	boundsResHeight,
	boundsPartCount
};

#endif