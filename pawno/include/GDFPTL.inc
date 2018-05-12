#include <a_samp>

#if defined _gdfptl_included
	#endinput
#endif
#define _gdfptl_included

/*
native crossp(Float:v1x, Float:v1y, Float:v1z, Float:v2x, Float:v2y, Float:v2z, &Float:output);
native GetDistanceFromPointToLine(&Float:distance, Float:line_vector_x, Float:line_vector_y, Float:line_vector_z, Float:line_x, Float:line_y, Float:line_z, Float:point_x, Float:point_y, Float:point_z);
*/

stock crossp(Float:v1x, Float:v1y, Float:v1z, Float:v2x, Float:v2y, Float:v2z, &Float:output)
{
	new
		Float:c1 = (v1y * v2z) - (v1z * v2y),
		Float:c2 = (v1z * v2x) - (v1x * v2z),
        Float:c3 = (v1x * v2y) - (v1y * v2x);
    output = floatsqroot ((c1 * c1) + (c2 * c2) + (c3 * c3));
    return 0;
}

stock GetDistanceFromPointToLine(&Float:distance, Float:line_vector_x, Float:line_vector_y, Float:line_vector_z, Float:line_x, Float:line_y, Float:line_z, Float:point_x, Float:point_y, Float:point_z)
{
	//A line is defined by a point (which is on the line (line_x/y/z)) and a vector which defines the direction (line_vector_x/y/z).
	new Float:output;
    crossp(line_vector_x, line_vector_y, line_vector_z, point_x - line_x, point_y - line_y, point_z - line_z, output);//Cross product of 2 vectors.
    distance = output / floatsqroot ((line_vector_x * line_vector_x) + (line_vector_y * line_vector_y) + (line_vector_z * line_vector_z));
	return 0;
}
