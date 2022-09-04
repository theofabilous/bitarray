/* C code produced by gperf version 3.0.3 */
/* Command-line: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/gperf -L C -t -G --output-file=/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokenhash.c /Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf  */
/* Computed positions: -k'1-2' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif

#line 2 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"


#include "tokenhash.h"
#line 6 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"

#define TOTAL_KEYWORDS 110
#define MIN_WORD_LENGTH 1
#define MAX_WORD_LENGTH 2
#define MIN_HASH_VALUE 1
#define MAX_HASH_VALUE 152
/* maximum key range = 152, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
hash (str, len)
     register const char *str;
     register unsigned int len;
{
  static unsigned char asso_values[] =
    {
      153, 153, 153, 153, 153, 153, 153, 153, 153, 153,
      153, 153, 153, 153, 153, 153, 153, 153, 153, 153,
      153, 153, 153, 153, 153, 153, 153, 153, 153, 153,
      153, 153, 153, 125,   0, 153,   9,   4, 127,   5,
      120, 122,  30, 100, 117, 115,  95, 153, 112, 107,
      102,  97,  92,  87,  82,  77,  72,  67, 110, 153,
       20,  10,   0,   5,  62,  56, 105,  51,  46,  41,
       36,  31,  26,  21,  16,  11,   6, 153,   1,  89,
       84,  95,  79,  70,  74,  69, 127, 122, 117, 112,
      107,  45, 153,  55,  40,   5, 153, 102,  65,  97,
       92,  87,  82,  77,  72,  60,  67,  62,  55,  45,
       57,  52,  47,  42,  37,  32,  27,  25,  22,  17,
       12,   7,   2,  50,  35,  15,  85, 153, 153, 153,
      153, 153, 153, 153, 153, 153, 153, 153, 153, 153,
      153, 153, 153, 153, 153, 153, 153, 153, 153, 153,
      153, 153, 153, 153, 153, 153, 153, 153, 153, 153,
      153, 153, 153, 153, 153, 153, 153, 153, 153, 153,
      153, 153, 153, 153, 153, 153, 153, 153, 153, 153,
      153, 153, 153, 153, 153, 153, 153, 153, 153, 153,
      153, 153, 153, 153, 153, 153, 153, 153, 153, 153,
      153, 153, 153, 153, 153, 153, 153, 153, 153, 153,
      153, 153, 153, 153, 153, 153, 153, 153, 153, 153,
      153, 153, 153, 153, 153, 153, 153, 153, 153, 153,
      153, 153, 153, 153, 153, 153, 153, 153, 153, 153,
      153, 153, 153, 153, 153, 153, 153, 153, 153, 153,
      153, 153, 153, 153, 153, 153, 153
    };
  register unsigned int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[1]+1];
      /*FALLTHROUGH*/
      case 1:
        hval += asso_values[(unsigned char)str[0]];
        break;
    }
  return hval;
}

static struct HashToken wordlist[] =
  {
    {""},
#line 27 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {">", 70, 0b00000000000001, 0b00000000000001, 0b00000000000100, "GREATER_THAN?", 2, 9, 0, true},
#line 29 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {">=", 70, 0b00000000000000, 0b00000000000001, 0b00000000000100, "GREATER_EQ?", 0, 9, 0, true},
#line 105 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"N!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-N!-", 0, 0, 0, false},
#line 128 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"z!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-z!-", 0, 0, 0, false},
#line 26 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"%", 50, 0b00000000000000, 0b00000000000001, 0b00000000000100, "ALIGN", 0, 9, 0, true},
#line 45 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"?", 20, 0b00000000000000, 0b00000000000001, 0b01000000000100, "--?--", 9, 0, 2, false},
#line 38 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {">>", 60, 0b00000000000000, 0b00000000000001, 0b00000000000100, "SHIFT_RIGHT", 0, 9, 0, true},
#line 103 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"L!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-L!-", 0, 0, 0, false},
#line 126 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"y!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-y!-", 0, 0, 0, false},
#line 51 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"$", 100, 0b00000000000000, 0b00000000000010, 0b00000000000011, "GET_ENV", 0, 7, 0, true},
#line 22 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"=", 1, 0b00000000000001, 0b00000000000001, 0b00000100000100, "ASSIGN", 2, 9, 0, true},
#line 31 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"==", 70, 0b00000000000000, 0b00000000000001, 0b00000000000100, "EQUAL?", 0, 9, 0, true},
#line 101 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"K!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-K!-", 0, 0, 0, false},
#line 124 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"x!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-x!-", 0, 0, 0, false},
    {""},
#line 73 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"}", 0, 0b00000000000000, 0b00000000100000, 0b00000000000000, "Close", 0, 6, 0, false},
#line 36 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"=>", 20, 0b00000000000000, 0b00000000000001, 0b00000000000000, "MatchWith", 0, 9, 0, false},
#line 99 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"J!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-J!-", 0, 0, 0, false},
#line 122 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"w!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-w!-", 0, 0, 0, false},
    {""},
#line 28 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"<", 70, 0b00000000000001, 0b00000000000001, 0b00000000000100, "LESS_THAN?", 2, 9, 0, true},
#line 30 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"<=", 70, 0b00000000000000, 0b00000000000001, 0b00000000000100, "LESS_EQ?", 0, 9, 0, true},
#line 97 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"I!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-I!-", 0, 0, 0, false},
#line 120 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"v!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-v!-", 0, 0, 0, false},
    {""},
#line 46 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"u", 100, 0b00000000000001, 0b00000100000010, 0b10000000000100, "--u--", 2, 7, 1, false},
#line 118 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"u!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-u!-", 0, 0, 0, false},
#line 95 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"H!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-H!-", 0, 0, 0, false},
#line 116 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"t!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-t!-", 0, 0, 0, false},
    {""},
#line 23 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"*", 40, 0b00000000000001, 0b00000000000001, 0b00100000000100, "TIMES", 2, 9, 0, true},
#line 37 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"<<", 60, 0b00000000000000, 0b00000000000001, 0b00000000000100, "SHIFT_LEFT", 0, 9, 0, true},
#line 93 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"G!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-G!-", 0, 0, 0, false},
#line 114 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"s!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-s!-", 0, 0, 0, false},
    {""},
#line 39 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"|", 60, 0b00000000000001, 0b00000000000001, 0b00000000000000, "BitOr", 2, 9, 0, false},
#line 25 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"*>", 10, 0b00000000000000, 0b00000000000001, 0b00100000000100, "LOOP", 0, 9, 3, true},
#line 91 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"F!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-F!-", 0, 0, 0, false},
#line 112 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"r!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-r!-", 0, 0, 0, false},
    {""},
#line 49 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"^", 80, 0b00000000000000, 0b00000100000010, 0b10000000000100, "--^--", 0, 7, 1, false},
#line 43 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"|>", 90, 0b00000000000000, 0b00000000000001, 0b00000000000000, "MatchCase", 0, 9, 0, false},
#line 89 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"E!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-E!-", 0, 0, 0, false},
#line 110 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"q!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-q!-", 0, 0, 0, false},
    {""},
#line 75 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"[", 0, 0b00000000000001, 0b00000001000000, 0b00000000000000, "Special", 2, 3, 0, false},
#line 67 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"m!", 0, 0b00000000000000, 0b00000000000000, 0b00000000000000, "Match", 0, 0, 6, false},
#line 87 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"D!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-D!-", 0, 0, 0, false},
#line 108 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"p!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-p!-", 0, 0, 0, false},
    {""},
#line 74 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"{", 0, 0b00000000000001, 0b00000001000000, 0b00000000000000, "Special", 2, 4, 0, false},
#line 42 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"||", 57, 0b00000000000000, 0b00000000000001, 0b00000000000100, "AND?", 0, 9, 0, true},
#line 85 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"C!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-C!-", 0, 0, 0, false},
#line 106 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"o!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-o!-", 0, 0, 0, false},
    {""},
#line 72 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"]", 0, 0b00000000000000, 0b00000000100000, 0b00000000000000, "Close", 0, 6, 0, false},
#line 102 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"l!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-l!-", 0, 0, 0, false},
#line 81 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"A!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-A!-", 0, 0, 0, false},
#line 104 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"n!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-n!-", 0, 0, 0, false},
    {""},
#line 47 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"i", 100, 0b00000000000001, 0b00000100000010, 0b10000000000100, "--i--", 2, 7, 1, false},
#line 96 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"i!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-i!-", 0, 0, 0, false},
#line 52 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"@", 100, 0b00000000000000, 0b00000000000010, 0b00000000000011, "GET_FIELD", 0, 7, 0, true},
#line 100 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"k!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-k!-", 0, 0, 0, false},
    {""},
#line 48 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"b", 100, 0b00000000000001, 0b00000100000010, 0b00000000000000, "Bits", 2, 7, 1, false},
#line 82 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"b!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-b!-", 0, 0, 0, false},
#line 64 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"9", 0, 0b00000000000000, 0b00000000001000, 0b00000000000000, "DIGIT", 0, 0, 0, false},
#line 98 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"j!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-j!-", 0, 0, 0, false},
    {""},
#line 119 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"U!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-U!-", 0, 0, 0, false},
#line 115 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"S!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-S!-", 0, 0, 0, false},
#line 63 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"8", 0, 0b00000000000000, 0b00000000001000, 0b00000000000000, "DIGIT", 0, 0, 0, false},
#line 94 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"h!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-h!-", 0, 0, 0, false},
    {""},
#line 117 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"T!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-T!-", 0, 0, 0, false},
#line 78 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"_R", 0, 0b00000000000000, 0b00000000000000, 0b00000000000100, "READ", 0, 0, 0, true},
#line 62 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"7", 0, 0b00000000000000, 0b00000000001000, 0b00000000000000, "DIGIT", 0, 0, 0, false},
#line 92 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"g!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-g!-", 0, 0, 0, false},
    {""},
#line 113 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"R!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-R!-", 0, 0, 0, false},
#line 69 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"m{", 0, 0b00000000000000, 0b00000000010000, 0b00000000000000, "", 0, 1, 0, false},
#line 61 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"6", 0, 0b00000000000000, 0b00000000001000, 0b00000000000000, "DIGIT", 0, 0, 0, false},
#line 90 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"f!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-f!-", 0, 0, 0, false},
    {""},
#line 109 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"P!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-P!-", 0, 0, 0, false},
#line 68 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"[]", 0, 0b00000000000000, 0b00000000000000, 0b00100000000100, "READ_ARRAY", 0, 0, 4, true},
#line 60 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"5", 0, 0b00000000000000, 0b00000000001000, 0b00000000000000, "DIGIT", 0, 0, 0, false},
#line 88 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"e!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-e!-", 0, 0, 0, false},
    {""},
#line 107 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"O!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-O!-", 0, 0, 0, false},
#line 70 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"l{", 0, 0b00000000000000, 0b00000000010000, 0b00000000000000, "", 0, 1, 0, false},
#line 59 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"4", 0, 0b00000000000000, 0b00000000001000, 0b00000000000000, "DIGIT", 0, 0, 0, false},
#line 86 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"d!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-d!-", 0, 0, 0, false},
    {""},
#line 54 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {".", 90, 0b00000000000000, 0b00000100000100, 0b10000000000100, "--.--", 0, 8, 1, false},
#line 111 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"Q!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-Q!-", 0, 0, 0, false},
#line 58 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"3", 0, 0b00000000000000, 0b00000000001000, 0b00000000000000, "DIGIT", 0, 0, 0, false},
#line 84 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"c!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-c!-", 0, 0, 0, false},
    {""},
#line 20 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"+", 40, 0b00000000000000, 0b00000000000001, 0b00000000000100, "PLUS", 0, 9, 0, true},
#line 79 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"_P", 0, 0b00000000000000, 0b00000000000000, 0b00000000000100, "PEEK", 0, 0, 0, true},
#line 57 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"2", 0, 0b00000000000000, 0b00000000001000, 0b00000000000000, "DIGIT", 0, 0, 0, false},
#line 80 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"a!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-a!-", 0, 0, 0, false},
    {""},
#line 50 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"B", 100, 0b00000000000001, 0b00000000000010, 0b1000000000000010, "BYTES", 2, 7, 8, true},
#line 83 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"B!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-B!-", 0, 0, 0, false},
#line 56 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"1", 0, 0b00000000000000, 0b00000000001000, 0b00000000000000, "DIGIT", 0, 0, 0, false},
#line 129 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"Z!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-Z!-", 0, 0, 0, false},
    {""},
#line 44 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {":", 55, 0b00000000000001, 0b00000000000001, 0b100000000000100, "--:--", 2, 9, 0, false},
#line 33 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {":=", 89, 0b00000000000000, 0b00000000000001, 0b00000000000100, "WALRUS_ASSIGN", 0, 9, 0, true},
#line 55 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"0", 0, 0b00000000000000, 0b00000000001000, 0b00000000000000, "DIGIT", 0, 0, 0, false},
#line 127 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"Y!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-Y!-", 0, 0, 0, false},
    {""},
#line 21 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"-", 40, 0b00000000000001, 0b00000000000001, 0b00000000000100, "MINUS", 2, 9, 0, true},
#line 34 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"<-", 10, 0b00000000000000, 0b00000000000001, 0b00000000000100, "--<---", 0, 9, 0, false},
#line 76 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {",", 0, 0b00000000000000, 0b00000001000000, 0b00000000000000, "Special", 0, 2, 0, false},
#line 125 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"X!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-X!-", 0, 0, 0, false},
    {""},
#line 65 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"(", 0, 0b00000000000001, 0b00000000010000, 0b00000000000000, "ParensOpen", 2, 5, 0, false},
#line 35 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"->", 10, 0b00000000000000, 0b00000000000001, 0b00100000000100, "LOOP_WHILE", 0, 9, 5, true},
#line 71 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {")", 0, 0b00000000000000, 0b00000000100000, 0b00000000000000, "Close", 0, 6, 0, false},
#line 123 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"W!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-W!-", 0, 0, 0, false},
    {""},
#line 53 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"!", 100, 0b00000000000001, 0b00000000000010, 0b00000100000010, "SKIP", 2, 7, 0, true},
#line 32 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"!=", 70, 0b00000000000000, 0b00000000000001, 0b00000000000100, "NOT_EQUAL?", 0, 9, 0, true},
#line 40 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"&", 60, 0b00000000000001, 0b00000000000001, 0b00000000000000, "BitAnd", 2, 9, 0, false},
#line 121 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"V!", 0, 0b00000000000000, 0b00000000000000, 0b1000010000000010, "-V!-", 0, 0, 0, false},
    {""}, {""},
#line 24 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"**", 10, 0b00000000000000, 0b00000000000001, 0b00100000000100, "LOOP", 0, 9, 3, true},
    {""},
#line 41 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"&&", 57, 0b00000000000000, 0b00000000000001, 0b00000000000100, "OR?", 0, 9, 0, true},
    {""}, {""},
#line 77 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"{}", 0, 0b00000000000000, 0b00000000000000, 0b00000000000011, "RAW_VALUE", 0, 0, 0, true},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""},
#line 66 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"()", 0, 0b00000000000000, 0b00000000010000, 0b1000000000000010, "--()--", 0, 0, 7, false}
  };

struct HashToken *
in_word_set (str, len)
     register const char *str;
     register unsigned int len;
{
  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      unsigned int key = hash (str, len);

      if (key <= MAX_HASH_VALUE)
        {
          register const char *s = wordlist[key].name;

          if (*str == *s && !strcmp (str + 1, s + 1))
            return &wordlist[key];
        }
    }
  return 0;
}
