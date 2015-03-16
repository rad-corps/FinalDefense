#pragma once

/**
* @brief A Structure to describe a colour value as an unsigned int, and as individual 8 bit components (char values)
**/
struct SColour
{
	/// @brief Default constructor for a SColour object
	SColour() {}
	/// @brief Constructor for an SColour obejct that constructs the SColour object from an unsigned integer value
	/// @param a_iColor the colour that the SColour will be created to specify
	SColour(unsigned int a_iColour) {argb.colour = a_iColour;}
	/// @brief Constructor to create an SColor object from four char values RGBA
	/// @param r unsigned char to represent the red component of an SColour object
	/// @param g unsigned char to represent the red component of an SColour object
	/// @param b unsigned char to represent the red component of an SColour object
	/// @param a unsigned char to represent the red component of an SColour object
	SColour(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		argb.colours.r = r;
		argb.colours.g = g;
		argb.colours.b = b;
		argb.colours.a = a;
	}
	/// and unnamed union that causes SColours member variables to use the same area of memory.
	/// this means that @param colour and @param colours occupy the same space, a change to one is 
	/// reflected in the other.
	union
	{
		unsigned int colour;
		struct SColours
		{
			unsigned char a, r, g, b;
		} colours;
	}argb;

};
