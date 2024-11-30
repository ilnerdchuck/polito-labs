volatile unsigned int *const USART1_PTR = (unsigned int *)0x40011004;


void my_printf(const char *s) {
    while(*s != '\0') { /* Loop until end of string */
        *USART1_PTR= (unsigned int)(*s); /* Transmit char */
        s++; /* Next char */
    }
}

void intToStr(int num, char *str) {
    int i = 0;
    int isNegative = 0;

    // Handle 0 explicitly
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    // Handle negative numbers
    if (num < 0) {
        isNegative = 1;
        num = -num;
    }

    // Process each digit of the number
    while (num != 0) {
        str[i++] = (num % 10) + '0';
        num /= 10;
    }

    // Add minus sign for negative numbers
    if (isNegative) {
        str[i++] = '-';
    }

    // Null-terminate the string
    str[i] = '\0';

    // Reverse the string
    int start = 0, end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

