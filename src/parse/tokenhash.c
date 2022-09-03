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

#define TOTAL_KEYWORDS 53
#define MIN_WORD_LENGTH 1
#define MAX_WORD_LENGTH 2
#define MIN_HASH_VALUE 1
#define MAX_HASH_VALUE 97
/* maximum key range = 97, duplicates = 0 */

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
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 60, 98, 98, 53, 48, 25, 98,
      50, 45, 10, 43, 38, 30, 33, 98, 28, 23,
      18, 13,  8,  3, 62, 57, 52, 47, 55, 98,
      15,  0,  5, 42, 37, 98, 32, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 40, 98, 35, 27, 98, 98, 98, 22, 98,
      98, 98, 98, 98, 98, 17, 98, 98, 98,  5,
      98, 98, 98, 98, 98, 98, 98, 12, 98, 98,
      98, 98, 98,  7, 20,  2, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
      98, 98, 98, 98, 98, 98
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
#line 20 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"=", 1, 0b00000000000001, 0b00000000000001, 0b00000000000000, "ASSIGN", 2, 0},
#line 28 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"==", 70, 0b00000000000000, 0b00000000000001, 0b00000000000000, "Eq", 0, 0},
#line 67 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"}", 0, 0b00000000000000, 0b00000000100000, 0b00000000000000, "Close", 0, 0},
#line 56 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"5", 0, 0b00000000000000, 0b00000000001000, 0b00000000000000, "DIGIT", 0, 0},
    {""},
#line 24 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {">", 70, 0b00000000000001, 0b00000000000001, 0b00000000000000, "Greater", 2, 0},
#line 26 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {">=", 70, 0b00000000000000, 0b00000000000001, 0b00000000000000, "GreEq", 0, 0},
#line 68 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"{", 0, 0b00000000000000, 0b00000001000000, 0b00000000000000, "Special", 0, 0},
#line 55 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"4", 0, 0b00000000000000, 0b00000000001000, 0b00000000000000, "DIGIT", 0, 0},
    {""},
#line 21 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"*", 10, 0b00000000000001, 0b00000000000001, 0b00000000000000, "REPEAT", 2, 3},
#line 34 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {">>", 60, 0b00000000000000, 0b00000000000001, 0b00000000000000, "ShiftRight", 0, 0},
#line 42 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"u", 100, 0b00000000000000, 0b00000100000010, 0b00000000000000, "Unsigned", 0, 1},
#line 54 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"3", 0, 0b00000000000000, 0b00000000001000, 0b00000000000000, "DIGIT", 0, 0},
    {""},
#line 25 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"<", 70, 0b00000000000001, 0b00000000000001, 0b00000000000000, "Smaller", 2, 0},
#line 27 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"<=", 70, 0b00000000000000, 0b00000000000001, 0b00000000000000, "SmEq", 0, 0},
#line 43 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"i", 100, 0b00000000000000, 0b00000100000010, 0b00000000000000, "Signed", 0, 1},
#line 53 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"2", 0, 0b00000000000000, 0b00000000001000, 0b00000000000000, "DIGIT", 0, 0},
    {""},
#line 35 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"|", 60, 0b00000000000001, 0b00000000000001, 0b00000000000000, "BitOr", 2, 0},
#line 22 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"**", 10, 0b00000000000000, 0b00000000000001, 0b00000000000000, "REPEAT", 0, 3},
#line 44 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"b", 100, 0b00000000000000, 0b00000100000010, 0b00000000000000, "Bits", 0, 1},
#line 52 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"1", 0, 0b00000000000000, 0b00000000001000, 0b00000000000000, "DIGIT", 0, 0},
    {""},
#line 36 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"&", 60, 0b00000000000001, 0b00000000000001, 0b00000000000000, "BitAnd", 2, 0},
#line 39 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"|>", 90, 0b00000000000000, 0b00000000000001, 0b00000000000000, "MatchCase", 0, 0},
#line 45 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"^", 80, 0b00000000000000, 0b00000100000010, 0b00000000000000, "Peek", 0, 1},
#line 51 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"0", 0, 0b00000000000000, 0b00000000001000, 0b00000000000000, "DIGIT", 0, 0},
    {""},
#line 19 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"-", 40, 0b00000000000001, 0b00000000000001, 0b00000000000000, "MINUS", 2, 0},
#line 33 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"<<", 60, 0b00000000000000, 0b00000000000001, 0b00000000000000, "ShiftLeft", 0, 0},
#line 46 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"B", 100, 0b00000000000000, 0b00000000000010, 0b00000000000000, "Bytes", 0, 8},
#line 50 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {".", 90, 0b00000000000000, 0b00000100000100, 0b00000000000000, "BigEndian", 0, 1},
    {""},
#line 66 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"]", 0, 0b00000000000000, 0b00000000100000, 0b00000000000000, "Close", 0, 0},
#line 32 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"->", 10, 0b00000000000000, 0b00000000000001, 0b00000000000000, "DoWhile", 0, 5},
#line 48 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"@", 100, 0b00000000000000, 0b00000000000010, 0b00000000000000, "Ref", 0, 0},
#line 70 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {",", 0, 0b00000000000000, 0b00000001000000, 0b00000000000000, "Special", 0, 0},
    {""},
#line 69 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"[", 0, 0b00000000000001, 0b00000001000000, 0b00000000000000, "Special", 2, 0},
#line 38 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"||", 57, 0b00000000000000, 0b00000000000001, 0b00000000000000, "Or", 0, 0},
#line 41 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"?", 20, 0b00000000000000, 0b00000000000001, 0b00000000000000, "Conditional", 0, 2},
#line 18 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"+", 40, 0b00000000000000, 0b00000000000001, 0b00000000000000, "PLUS", 0, 0},
    {""},
#line 65 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {")", 0, 0b00000000000000, 0b00000000100000, 0b00000000000000, "Close", 0, 0},
#line 31 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"<-", 10, 0b00000000000000, 0b00000000000001, 0b00000000000000, "???", 0, 0},
#line 60 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"9", 0, 0b00000000000000, 0b00000000001000, 0b00000000000000, "DIGIT", 0, 0},
#line 23 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"%", 50, 0b00000000000000, 0b00000000000001, 0b00000000000000, "Align", 0, 0},
    {""},
#line 61 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"(", 0, 0b00000000000001, 0b00000000010000, 0b00000000000000, "ParensOpen", 2, 0},
#line 37 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"&&", 57, 0b00000000000000, 0b00000000000001, 0b00000000000000, "And", 0, 0},
#line 59 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"8", 0, 0b00000000000000, 0b00000000001000, 0b00000000000000, "DIGIT", 0, 0},
#line 47 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"$", 100, 0b00000000000000, 0b00000000000010, 0b00000000000000, "Env", 0, 0},
    {""},
#line 40 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {":", 55, 0b00000000000001, 0b00000000000001, 0b00000000000000, "If_Else", 2, 0},
#line 30 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {":=", 89, 0b00000000000000, 0b00000000000001, 0b00000000000000, "WalrusAssign", 0, 0},
#line 58 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"7", 0, 0b00000000000000, 0b00000000001000, 0b00000000000000, "DIGIT", 0, 0},
    {""}, {""},
#line 49 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"!", 100, 0b00000000000001, 0b00000000000010, 0b00000000000000, "Skip", 2, 0},
#line 29 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"!=", 70, 0b00000000000000, 0b00000000000001, 0b00000000000000, "NEq", 0, 0},
#line 57 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"6", 0, 0b00000000000000, 0b00000000001000, 0b00000000000000, "DIGIT", 0, 0},
    {""}, {""}, {""},
#line 63 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"m!", 0, 0b00000000000000, 0b00000000000000, 0b00000000000000, "Match", 0, 6},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 64 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"[]", 0, 0b00000000000000, 0b00000000000000, 0b00000000000000, "ReadArray", 0, 4},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""},
#line 62 "/Users/theofabilous/Documents/GitHub/bitarray/src/parse/tokens.gperf"
    {"()", 0, 0b00000000000000, 0b00000000010000, 0b00000000000000, "ParensOpen", 0, 7}
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
