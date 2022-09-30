/*****************************************************************/
/* File convert_float_to_bits.c:  asks for a floating point      */
/* input number and prints the value out in decimal, hex and     */
/* bits spaced for readability.  The program expects that input  */
/* floats are stored in IEEE 754 format after scanning, and is   */
/* currently built to run on little endian machines (i.e. Compaq,*/
/* Intel, etc.).  To run this program on a big endian machine,   */
/* the bit structures would require top-to-bottom inversions.    */
/*****************************************************************/
#include "float.h"


int main(int argc, char * argv[])
{
    char bit_string[43];
    double float_list[] = {
        237.75, -.0000005126, -92457321.670245,
        6.023E+23, 1.67339E-40, 6.0, -24.177E-10,
        7.14, 10000000003.2, -100000000003.2
    };


    for(int k = 0, instance = 0; k < 10; k++, instance++) {
        for(int i=0; i<42; i++){
            bit_string[i] = ' ';
        }
        bit_string[42] = '\0';

        instance_display_info(bit_string, float_list[instance]);
    }

    return 0;
}