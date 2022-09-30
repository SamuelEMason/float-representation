#include <math.h>
#include <stdio.h>


void instance_display_info(char* bit_string, float instance);
float convert_bit_string_to_float(char* bit_string);
int get_bit_string_size(char* bit_string);
int convert_char_bit_to_int(char bit);
int convert_int_from_substring(char* bit_string, int start, int end);
void print_bit_string(char* bit_string, int start, int end);


union float_32{
        float   floating_value_in_32_bits;
        int     floating_value_as_int;
        struct  sign_exp_mantissa{
                unsigned  mantissa:23;
                unsigned  exponent:8;
                unsigned      sign:1;
        } f_bits;
	struct single_bits{
		unsigned  b0 :1;
		unsigned  b1 :1;
		unsigned  b2 :1;
		unsigned  b3 :1;
		unsigned  b4 :1;
		unsigned  b5 :1;
		unsigned  b6 :1;
		unsigned  b7 :1;
		unsigned  b8 :1;
		unsigned  b9 :1;
		unsigned  b10:1;
		unsigned  b11:1;
		unsigned  b12:1;
		unsigned  b13:1;
		unsigned  b14:1;
		unsigned  b15:1;
		unsigned  b16:1;
		unsigned  b17:1;
		unsigned  b18:1;
		unsigned  b19:1;
		unsigned  b20:1;
		unsigned  b21:1;
		unsigned  b22:1;
		unsigned  b23:1;
		unsigned  b24:1;
		unsigned  b25:1;
		unsigned  b26:1;
		unsigned  b27:1;
		unsigned  b28:1;
		unsigned  b29:1;
		unsigned  b30:1;
		unsigned  b31:1;
	}bit;
} float_32;


void instance_display_info(char* bit_string, float instance) {

    float_32.floating_value_in_32_bits = instance;

    bit_string[0] = float_32.bit.b31?'1':'0';

    bit_string[2] = float_32.bit.b30?'1':'0';
    bit_string[3] = float_32.bit.b29?'1':'0';
    bit_string[4] = float_32.bit.b28?'1':'0';
    bit_string[5] = float_32.bit.b27?'1':'0';

    bit_string[7] = float_32.bit.b26?'1':'0';
    bit_string[8] = float_32.bit.b25?'1':'0';
    bit_string[9] = float_32.bit.b24?'1':'0';
    bit_string[10] = float_32.bit.b23?'1':'0';

    bit_string[12] = float_32.bit.b22?'1':'0';
    bit_string[13] = float_32.bit.b21?'1':'0';
    bit_string[14] = float_32.bit.b20?'1':'0';

    bit_string[16] = float_32.bit.b19?'1':'0';
    bit_string[17] = float_32.bit.b18?'1':'0';
    bit_string[18] = float_32.bit.b17?'1':'0';
    bit_string[19] = float_32.bit.b16?'1':'0';

    bit_string[21] = float_32.bit.b15?'1':'0';
    bit_string[22] = float_32.bit.b14?'1':'0';
    bit_string[23] = float_32.bit.b13?'1':'0';
    bit_string[24] = float_32.bit.b12?'1':'0';

    bit_string[26] = float_32.bit.b11?'1':'0';
    bit_string[27] = float_32.bit.b10?'1':'0';
    bit_string[28] = float_32.bit.b9?'1':'0';
    bit_string[29] = float_32.bit.b8?'1':'0';

    bit_string[31] = float_32.bit.b7?'1':'0';
    bit_string[32] = float_32.bit.b6?'1':'0';
    bit_string[33] = float_32.bit.b5?'1':'0';
    bit_string[34] = float_32.bit.b4?'1':'0';

    bit_string[36] = float_32.bit.b3?'1':'0';
    bit_string[37] = float_32.bit.b2?'1':'0';
    bit_string[38] = float_32.bit.b1?'1':'0';
    bit_string[39] = float_32.bit.b0?'1':'0';

    printf("\nThe floating value for\t%f is broken out as:\n", float_32.floating_value_in_32_bits);
    float_32.floating_value_in_32_bits = convert_bit_string_to_float(bit_string);

    printf("mantissa:\t0x%x\t\t\tor:  ", convert_int_from_substring(bit_string, 12, 40));
    print_bit_string(bit_string, 12, 40);
    printf("\nexponent:\t0x%x\t\t\t\tor:  ", convert_int_from_substring(bit_string, 1, 11));
    print_bit_string(bit_string, 2, 11);
    printf("\nsign:\t\t%x\t\t\t\tor:  ", convert_char_bit_to_int(bit_string[0]));
    print_bit_string(bit_string, 0, 1);
    printf("\nin base10:\t%f\t\t\tor:  ", float_32.floating_value_in_32_bits);
    print_bit_string(bit_string, 0, 40);
    printf("\n\n");
}


float convert_bit_string_to_float(char* bit_string) {

    int size = get_bit_string_size(bit_string);
    char bit = bit_string[0];
    int signbit = convert_char_bit_to_int(bit);
    int exponent[] = {0, 0, 0, 0, 0, 0, 0, 0};
    int mantissa[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    int i = 1;
    for(int j = 0; i < 11; i++) {
        if(bit_string[i] == ' ') {
            continue;
        }
        exponent[j] = convert_char_bit_to_int(bit_string[i]);
        j++;
    }

    for(int j = 0; i < size; i++) {
        if(bit_string[i] == ' ') {
            continue;
        }
        mantissa[j] = convert_char_bit_to_int(bit_string[i]);
        j++;
    }

    int sum = 0;
    for(int i = 7, j = 0; i >= 0; i--, j++) {
        sum += exponent[i] * (1 << j);
    }
    int exp = sum - 127;
    float exp_val = pow(2, exp);

    float fsum = 0.0;
    for(int i = 0, j = -1; i < 23; i++, j--) {
        fsum += mantissa[i] * pow(2, j);
    }

    float mant_val = 1.0 + fsum;
    float converted_value = exp_val * mant_val;
    if(signbit) converted_value *= -1;

    return converted_value;
}


int get_bit_string_size(char* bit_string) {
    int size = 0;
    while(bit_string[size] != '\0') {
        size++;
    }
    return size;
}


int convert_char_bit_to_int(char bit) {
    if(bit == '0') {
        return 0;
    }
    else if(bit == '1') {
        return 1;
    }
}


int convert_int_from_substring(char* bit_string, int start, int end) {
    
    int sum = 0;
    for(int i = end, j = 0; i >= start; i--) {
        if(bit_string[i] == ' ') continue;
        int bit = convert_char_bit_to_int(bit_string[i]);
        sum += bit * (1 << j);
        j++;
    }
    return sum;
}


void print_bit_string(char* bit_string, int start, int end) {
    for(int i = start; i < end; i++) {
        printf("%c", bit_string[i]);
    }
}