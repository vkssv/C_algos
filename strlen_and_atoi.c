#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <errno.h>

/* Maximum number of bytes in a message. */
#define NL_TEXTMAX      INT_MAX
#define unlikely(x)     __builtin_expect((x),0)

/*
 * Time complexity O(n), worst case n=NL_TEXTMAX, space complexity O(1):
 * just allocate auto pos to "consume" it on the stack.
 */
ssize_t strlen(char *s) {

	char *pos = s;

	for(;;) {
		if (unlikely(pos == NULL)) {
			fprintf(stderr, "Invalid argument\n");
			return -EINVAL;
		}
		if (*pos == '\0')
			return pos - s;

		if (unlikely((pos - s) == NL_TEXTMAX)) {
			fprintf(stderr,
			"Maximum number of bytes in a message string exceeded (%d)\n",
			NL_TEXTMAX);
			return -EMSGSIZE;
		}
		pos++;
	}
}

/* time complexity O(1), space complexity 0(1) */
int my_atoi(char s) {

	if (s < ' ') {
		fprintf(stderr,
				"Invalid argument: unprintable control code (decimal)=%d\n",
				s);
		return 0;
	}

	if (s < '0') {
		fprintf(stderr,
				"Invalid argument: punctuation mark or misc symbol ('%c'), code (decimal)=%d\n",
				s, s);
		return 0;
	}

	if ((s == '0') || (s <= '9')) {
		return (s -'0');
	}

	/* if count in hexadecimal */
	switch(s) {
	case 'A':
	case 'a':
		return 0xA;
	case 'B':
	case 'b':
		return 0xB;
	case 'C':
	case 'c':
		return 0xC;
	case 'D':
	case 'd':
		return 0xD;
	case 'E':
	case 'e':
		return 0xE;
	case 'F':
	case 'f':
		return 0xF;
	default:
		fprintf(stderr,
				"Invalid argument: letter or misc symbol ('%c'), code (decimal)=%d\n",
				s, s);
		return 0;
	}
}

/* Iterative function to implement atoi() in a standard way:
 * Parses the C-string str interpreting its content as an integral number, which
 * is returned as a value of type int.
 * 
 * The function first discards as many whitespace characters as necessary until
 * the first non-whitespace character is found. Then, starting from this
 * character, takes an optional initial plus or minus sign followed by as many
 * base-10 digits as possible, and interprets them as a numerical value.
 * The string can contain additional characters after those that form the
 * integral number, which are ignored and have no effect on the behavior of this
 * function.
 * 
 * If the first sequence of non-whitespace characters in str is not a valid
 * integral number, or if no such sequence exists because either str is empty or
 * it contains only whitespace characters, no conversion is performed and zero
 * is returned.
 *
 * Time complexity O(n), worst case n=NL_TEXTMAX, space complexity O(1).
 */
int atoi_str(const char* s)
{
	int num = 0;
	int sign = 0;
	char *start;

	if (unlikely(s == NULL)) {
		fprintf(stderr, "Invalid argument: got a NULL ptr\n");
		return 0;
	}

	if (unlikely(!*s)) {
		fprintf(stderr, "Invalid argument: got an empty str\n");
		return 0;
	}

	start = (char *)s;
	while (*start) {
		/* check against malicious strings without '\0' */
		if (unlikely((start - s) == NL_TEXTMAX)) {
			fprintf(stderr,
					"Max number of bytes in a message string exceeded (%d)\n",
					NL_TEXTMAX);
			return 0;
		}
		if ((!sign) && ((*start == ' ') ||
			((*start >= '\t') && (*start <= '\r')))) {
			start++;
			continue;
		}

		switch(*start) {
		case('+'):
			if (!sign) {
				start++;
				sign = 1;
				continue; 
			} else {
				return 0;
			}
		case('-'):
			if (!sign) {
				start++;
				sign = -1;
				continue;
			} else {
				return 0;
			}
		}

		if ((*start >= '0') || (*start <= '9'))
			break;

		if ((*start < '\t') || (*start < '0') || (*start > '9'))
			return 0;
	}

	if (!sign)
		sign = 1;

	while (*start) {
		/* check against malicious strings without '\0' */
		if (unlikely((start - s) == NL_TEXTMAX)) {
			fprintf(stderr,
					"Max number of bytes in a message string exceeded (%d)\n",
					NL_TEXTMAX);
			return 0;
		}

		if ((*start < '0') || (*start > '9'))
			break;

		/* check against overflow for big numbers */
		if (unlikely(num > INT_MAX / 10 || (num == INT_MAX / 10 && *start - '0' > 7))) {
			fprintf(stdout,
					"Invalid argument: number is too big or too small\n");
			return 0;
		}
		num = num * 10 + (*start - '0');
		start++;
	}

	return num*sign;
}


int main(int argc, char *argv[]) {

	char s_len[] = "x132121";
	char c;
	char empty[] = "";
	char *n = NULL;
	char S[] = "-  56454 45ABC   ";
	char S1[] = "-56454 45ABC   ";
	char S2[] = " ABC123   ";
	char S3[] = ":123   ";
	char S4[] = "+135   ";
	char S5[] = "-;135   ";
	char S6[] = "  13-545-6545";
	char S7[] = "2147483649";
	char S8[] = "-2147483649";
	char S9[] = "                    ";

	(void) argc;
	(void) argv;

	fprintf(stdout, ">>>> TESTS:\n\n");

	fprintf(stdout, "1. string S='%s'\n", s_len);
	fprintf(stdout, "1. len = %ld\n\n", strlen(s_len));
	
	fprintf(stdout, "2. Provide a number, please:\n");
	scanf("%1c", &c);
	fprintf(stdout, "2. input='%c', atoi=(%d)\n\n", c, my_atoi(c));

	fprintf(stdout, "3. string is empty S='%s'\n", empty);
	fprintf(stdout, "3. atoi(S)=%d\n\n", atoi_str(empty));
	
	fprintf(stdout, "4. string is a NULL ptr\n");
	fprintf(stdout, "4. atoi(S)=%d\n\n", atoi_str(n));

	fprintf(stdout, "5. string S='%s'\n", S);
	fprintf(stdout, "5. atoi(S)=%d\n\n", atoi_str(S));

	fprintf(stdout, "6. string S='%s'\n", S1);
	fprintf(stdout, "6. atoi(S)=%d\n\n", atoi_str(S1));

	fprintf(stdout, "7. string S='%s'\n", S2);
	fprintf(stdout, "7. atoi(S)=%d\n\n", atoi_str(S2));

	fprintf(stdout, "8. string S='%s'\n", S3);
	fprintf(stdout, "8. atoi(S)=%d\n\n", atoi_str(S3));

	fprintf(stdout, "9. string S='%s'\n", S4);
	fprintf(stdout, "9. atoi(S)=%d\n\n", atoi_str(S4));

	fprintf(stdout, "10. string S='%s'\n", S5);
	fprintf(stdout, "10. atoi(S)=%d\n\n", atoi_str(S5));

	fprintf(stdout, "11. string S='%s'\n", S6);
	fprintf(stdout, "11. atoi(S)=%d\n\n", atoi_str(S6));

	fprintf(stdout, "12. string S='%s'\n", S7);
	fprintf(stdout, "12. atoi(S)=%d\n\n", atoi_str(S7));

	fprintf(stdout, "13. string S='%s'\n", S8);
	fprintf(stdout, "13. atoi(S)=%d\n\n", atoi_str(S8));

	fprintf(stdout, "14. string S='%s'\n", S9);
	fprintf(stdout, "14. atoi(S)=%d\n\n", atoi_str(S9));

	return EXIT_SUCCESS;
}
