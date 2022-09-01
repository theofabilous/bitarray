/* C code produced by gperf version 3.0.3 */
/* Command-line: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/gperf -L C -t -G --output-file=../src/parse/tokenhash.h ../src/parse/tokens.gperf  */
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

#line 2 "../src/parse/tokens.gperf"

#include <stdint.h>
#include <string.h>
typedef struct HashToken HashToken;
#line 7 "../src/parse/tokens.gperf"
struct HashToken
{
	const char* name;
	uint8_t precedence;
	uint16_t tokenize_flags;
	uint16_t tree_flags;
	uint16_t compile_flags;
	const char* descr;
	uint8_t max_search_size;
};

#define TOTAL_KEYWORDS 50
#define MIN_WORD_LENGTH 1
#define MAX_WORD_LENGTH 2
#define MIN_HASH_VALUE 1
#define MAX_HASH_VALUE 63
/* maximum key range = 63, duplicates = 0 */

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
      64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
      64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
      64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
      64, 64, 64, 60, 64, 64, 53, 48, 25, 64,
      43, 38, 10, 33, 28, 30, 23, 64, 18, 13,
       8,  3, 62, 57, 52, 47, 42, 37, 55, 64,
      15,  0,  5, 32, 27, 64, 22, 64, 64, 64,
      64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
      64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
      64, 17, 64, 12,  7, 64, 64, 64,  2, 64,
      64, 64, 64, 64, 64, 50, 64, 64, 64, 64,
      64, 64, 64, 64, 64, 64, 64, 45, 64, 64,
      64, 64, 64, 40, 20, 35, 64, 64, 64, 64,
      64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
      64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
      64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
      64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
      64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
      64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
      64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
      64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
      64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
      64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
      64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
      64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
      64, 64, 64, 64, 64, 64
    };
  register unsigned int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[1]];
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
#line 20 "../src/parse/tokens.gperf"
    {"=", 1, 0b00000000000001, 0b00000000000001, 0b00000000000000, "ASSIGN", 2},
#line 28 "../src/parse/tokens.gperf"
    {"==", 70, 0b00000000000000, 0b00000000000001, 0b00000000000000, "Eq", 0},
#line 44 "../src/parse/tokens.gperf"
    {"b", 100, 0b00000000000000, 0b00000100000010, 0b00000000000000, "Bits", 0},
#line 54 "../src/parse/tokens.gperf"
    {"3", 0, 0b00000000000000, 0b00000000001000, 0b00000000000000, "DIGIT", 0},
    {""},
#line 24 "../src/parse/tokens.gperf"
    {">", 70, 0b00000000000001, 0b00000000000001, 0b00000000000000, "Greater", 2},
#line 26 "../src/parse/tokens.gperf"
    {">=", 70, 0b00000000000000, 0b00000000000001, 0b00000000000000, "GreEq", 0},
#line 45 "../src/parse/tokens.gperf"
    {"^", 80, 0b00000000000000, 0b00000100000010, 0b00000000000000, "Peek", 0},
#line 53 "../src/parse/tokens.gperf"
    {"2", 0, 0b00000000000000, 0b00000000001000, 0b00000000000000, "DIGIT", 0},
    {""},
#line 21 "../src/parse/tokens.gperf"
    {"*", 10, 0b00000000000001, 0b00000000000001, 0b00000000000000, "REPEAT", 2},
#line 34 "../src/parse/tokens.gperf"
    {">>", 60, 0b00000000000000, 0b00000000000001, 0b00000000000000, "ShiftRight", 0},
#line 63 "../src/parse/tokens.gperf"
    {"]", 0, 0b00000000000000, 0b00000000100000, 0b00000000000000, "Close", 0},
#line 52 "../src/parse/tokens.gperf"
    {"1", 0, 0b00000000000000, 0b00000000001000, 0b00000000000000, "DIGIT", 0},
    {""},
#line 25 "../src/parse/tokens.gperf"
    {"<", 70, 0b00000000000001, 0b00000000000001, 0b00000000000000, "Smaller", 2},
#line 27 "../src/parse/tokens.gperf"
    {"<=", 70, 0b00000000000000, 0b00000000000001, 0b00000000000000, "SmEq", 0},
#line 66 "../src/parse/tokens.gperf"
    {"[", 0, 0b00000000000000, 0b00000001000000, 0b00000000000000, "Special", 0},
#line 51 "../src/parse/tokens.gperf"
    {"0", 0, 0b00000000000000, 0b00000000001000, 0b00000000000000, "DIGIT", 0},
    {""},
#line 35 "../src/parse/tokens.gperf"
    {"|", 60, 0b00000000000001, 0b00000000000001, 0b00000000000000, "BitOr", 2},
#line 22 "../src/parse/tokens.gperf"
    {"**", 10, 0b00000000000000, 0b00000000000001, 0b00000000000000, "REPEAT", 0},
#line 46 "../src/parse/tokens.gperf"
    {"B", 100, 0b00000000000000, 0b00000000000010, 0b00000000000000, "Bytes", 0},
#line 50 "../src/parse/tokens.gperf"
    {".", 90, 0b00000000000000, 0b00000100000100, 0b00000000000000, "BigEndian", 0},
    {""},
#line 36 "../src/parse/tokens.gperf"
    {"&", 60, 0b00000000000001, 0b00000000000001, 0b00000000000000, "BitAnd", 2},
#line 39 "../src/parse/tokens.gperf"
    {"|>", 90, 0b00000000000000, 0b00000000000001, 0b00000000000000, "MatchCase", 0},
#line 48 "../src/parse/tokens.gperf"
    {"@", 100, 0b00000000000000, 0b00000000000010, 0b00000000000000, "Ref", 0},
#line 67 "../src/parse/tokens.gperf"
    {",", 0, 0b00000000000000, 0b00000001000000, 0b00000000000000, "Special", 0},
    {""},
#line 19 "../src/parse/tokens.gperf"
    {"-", 40, 0b00000000000001, 0b00000000000001, 0b00000000000000, "MINUS", 2},
#line 33 "../src/parse/tokens.gperf"
    {"<<", 60, 0b00000000000000, 0b00000000000001, 0b00000000000000, "ShiftLeft", 0},
#line 41 "../src/parse/tokens.gperf"
    {"?", 20, 0b00000000000000, 0b00000000000001, 0b00000000000000, "Conditional", 0},
#line 18 "../src/parse/tokens.gperf"
    {"+", 40, 0b00000000000000, 0b00000000000001, 0b00000000000000, "PLUS", 0},
    {""},
#line 64 "../src/parse/tokens.gperf"
    {"}", 0, 0b00000000000000, 0b00000000100000, 0b00000000000000, "Close", 0},
#line 32 "../src/parse/tokens.gperf"
    {"->", 10, 0b00000000000000, 0b00000000000001, 0b00000000000000, "DoWhile", 0},
#line 60 "../src/parse/tokens.gperf"
    {"9", 0, 0b00000000000000, 0b00000000001000, 0b00000000000000, "DIGIT", 0},
#line 62 "../src/parse/tokens.gperf"
    {")", 0, 0b00000000000000, 0b00000000100000, 0b00000000000000, "Close", 0},
    {""},
#line 65 "../src/parse/tokens.gperf"
    {"{", 0, 0b00000000000000, 0b00000001000000, 0b00000000000000, "Special", 0},
#line 38 "../src/parse/tokens.gperf"
    {"||", 57, 0b00000000000000, 0b00000000000001, 0b00000000000000, "Or", 0},
#line 59 "../src/parse/tokens.gperf"
    {"8", 0, 0b00000000000000, 0b00000000001000, 0b00000000000000, "DIGIT", 0},
#line 61 "../src/parse/tokens.gperf"
    {"(", 0, 0b00000000000000, 0b00000000010000, 0b00000000000000, "ParensOpen", 0},
    {""},
#line 42 "../src/parse/tokens.gperf"
    {"u", 100, 0b00000000000000, 0b00000100000010, 0b00000000000000, "Unsigned", 0},
#line 31 "../src/parse/tokens.gperf"
    {"<-", 10, 0b00000000000000, 0b00000000000001, 0b00000000000000, "???", 0},
#line 58 "../src/parse/tokens.gperf"
    {"7", 0, 0b00000000000000, 0b00000000001000, 0b00000000000000, "DIGIT", 0},
#line 23 "../src/parse/tokens.gperf"
    {"%", 50, 0b00000000000000, 0b00000000000001, 0b00000000000000, "Align", 0},
    {""},
#line 43 "../src/parse/tokens.gperf"
    {"i", 100, 0b00000000000000, 0b00000100000010, 0b00000000000000, "Signed", 0},
#line 37 "../src/parse/tokens.gperf"
    {"&&", 57, 0b00000000000000, 0b00000000000001, 0b00000000000000, "And", 0},
#line 57 "../src/parse/tokens.gperf"
    {"6", 0, 0b00000000000000, 0b00000000001000, 0b00000000000000, "DIGIT", 0},
#line 47 "../src/parse/tokens.gperf"
    {"$", 100, 0b00000000000000, 0b00000000000010, 0b00000000000000, "Env", 0},
    {""},
#line 40 "../src/parse/tokens.gperf"
    {":", 55, 0b00000000000001, 0b00000000000001, 0b00000000000000, "If_Else", 2},
#line 30 "../src/parse/tokens.gperf"
    {":=", 89, 0b00000000000000, 0b00000000000001, 0b00000000000000, "WalrusAssign", 0},
#line 56 "../src/parse/tokens.gperf"
    {"5", 0, 0b00000000000000, 0b00000000001000, 0b00000000000000, "DIGIT", 0},
    {""}, {""},
#line 49 "../src/parse/tokens.gperf"
    {"!", 100, 0b00000000000001, 0b00000000000010, 0b00000000000000, "Skip", 2},
#line 29 "../src/parse/tokens.gperf"
    {"!=", 70, 0b00000000000000, 0b00000000000001, 0b00000000000000, "NEq", 0},
#line 55 "../src/parse/tokens.gperf"
    {"4", 0, 0b00000000000000, 0b00000000001000, 0b00000000000000, "DIGIT", 0}
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
