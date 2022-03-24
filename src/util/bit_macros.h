#define GET_NTH_ARG(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, \
_62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, \
_74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, \
_86, _87, _88, _89, _90, _91, _92, _93, _94, _95, _96, _97, \
_98, _99, _100, _101, _102, _103, _104, _105, _106, _107, _108, _109, \
_110, _111, _112, _113, _114, _115, _116, _117, _118, _119, _120, _121, \
_122, _123, _124, _125, _126, _127, _128, NAME, ...) NAME


#define bitarray_as_map(...) GET_NTH_ARG(__VA_ARGS__, __BINMAP_128, __BINMAP_127, __BINMAP_126,\
 __BINMAP_125, __BINMAP_124, __BINMAP_123, __BINMAP_122, __BINMAP_121, __BINMAP_120, \
__BINMAP_119, __BINMAP_118, __BINMAP_117, __BINMAP_116, __BINMAP_115, __BINMAP_114, __BINMAP_113, __BINMAP_112, \
__BINMAP_111, __BINMAP_110, __BINMAP_109, __BINMAP_108, __BINMAP_107, __BINMAP_106, __BINMAP_105, __BINMAP_104, \
__BINMAP_103, __BINMAP_102, __BINMAP_101, __BINMAP_100, __BINMAP_99, __BINMAP_98, __BINMAP_97, __BINMAP_96, \
__BINMAP_95, __BINMAP_94, __BINMAP_93, __BINMAP_92, __BINMAP_91, __BINMAP_90, __BINMAP_89, __BINMAP_88, \
__BINMAP_87, __BINMAP_86, __BINMAP_85, __BINMAP_84, __BINMAP_83, __BINMAP_82, __BINMAP_81, __BINMAP_80, \
__BINMAP_79, __BINMAP_78, __BINMAP_77, __BINMAP_76, __BINMAP_75, __BINMAP_74, __BINMAP_73, __BINMAP_72, \
__BINMAP_71, __BINMAP_70, __BINMAP_69, __BINMAP_68, __BINMAP_67, __BINMAP_66, __BINMAP_65, __BINMAP_64, \
__BINMAP_63, __BINMAP_62, __BINMAP_61, __BINMAP_60, __BINMAP_59, __BINMAP_58, __BINMAP_57, __BINMAP_56, \
__BINMAP_55, __BINMAP_54, __BINMAP_53, __BINMAP_52, __BINMAP_51, __BINMAP_50, __BINMAP_49, __BINMAP_48, \
__BINMAP_47, __BINMAP_46, __BINMAP_45, __BINMAP_44, __BINMAP_43, __BINMAP_42, __BINMAP_41, __BINMAP_40, \
__BINMAP_39, __BINMAP_38, __BINMAP_37, __BINMAP_36, __BINMAP_35, __BINMAP_34, __BINMAP_33, __BINMAP_32, \
__BINMAP_31, __BINMAP_30, __BINMAP_29, __BINMAP_28, __BINMAP_27, __BINMAP_26, __BINMAP_25, __BINMAP_24, \
__BINMAP_23, __BINMAP_22, __BINMAP_21, __BINMAP_20, __BINMAP_19, __BINMAP_18, __BINMAP_17, __BINMAP_16, \
__BINMAP_15, __BINMAP_14, __BINMAP_13, __BINMAP_12, __BINMAP_11, __BINMAP_10, __BINMAP_9, __BINMAP_8, \
__BINMAP_7, __BINMAP_6, __BINMAP_5, __BINMAP_4, __BINMAP_3, __BINMAP_2, __BINMAP_1)(__VA_ARGS__)


#define __BINMAP_2(_1, _2) \
1, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2)})

#define __BINMAP_4(_1, _2, _3, _4) \
2, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4)})

#define __BINMAP_6(_1, _2, _3, _4, _5, _6) \
3, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6)})

#define __BINMAP_8(_1, _2, _3, _4, _5, _6, _7, \
_8) \
4, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8)})

#define __BINMAP_10(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10) \
5, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10)})

#define __BINMAP_12(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12) \
6, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12)})

#define __BINMAP_14(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14) \
7, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14)})

#define __BINMAP_16(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16) \
8, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16)})

#define __BINMAP_18(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18) \
9, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18)})

#define __BINMAP_20(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20) \
10, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20)})

#define __BINMAP_22(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22) \
11, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22)})

#define __BINMAP_24(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24) \
12, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24)})

#define __BINMAP_26(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26) \
13, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26)})

#define __BINMAP_28(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28) \
14, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28)})

#define __BINMAP_30(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30) \
15, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30)})

#define __BINMAP_32(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32) \
16, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32)})

#define __BINMAP_34(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34) \
17, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34)})

#define __BINMAP_36(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36) \
18, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36)})

#define __BINMAP_38(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38) \
19, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38)})

#define __BINMAP_40(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40) \
20, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40)})

#define __BINMAP_42(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42) \
21, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42)})

#define __BINMAP_44(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44) \
22, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44)})

#define __BINMAP_46(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46) \
23, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46)})

#define __BINMAP_48(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48) \
24, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48)})

#define __BINMAP_50(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50) \
25, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50)})

#define __BINMAP_52(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52) \
26, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52)})

#define __BINMAP_54(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54) \
27, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54)})

#define __BINMAP_56(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56) \
28, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56)})

#define __BINMAP_58(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58) \
29, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58)})

#define __BINMAP_60(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58, _59, _60) \
30, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58), \
((BinaryMapEntry) _59, _60)})

#define __BINMAP_62(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58, _59, _60, _61, \
_62) \
31, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58), \
((BinaryMapEntry) _59, _60), ((BinaryMapEntry) _61, _62)})

#define __BINMAP_64(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58, _59, _60, _61, \
_62, _63, _64) \
32, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58), \
((BinaryMapEntry) _59, _60), ((BinaryMapEntry) _61, _62), \
((BinaryMapEntry) _63, _64)})

#define __BINMAP_66(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58, _59, _60, _61, \
_62, _63, _64, _65, _66) \
33, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58), \
((BinaryMapEntry) _59, _60), ((BinaryMapEntry) _61, _62), \
((BinaryMapEntry) _63, _64), ((BinaryMapEntry) _65, _66)})

#define __BINMAP_68(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58, _59, _60, _61, \
_62, _63, _64, _65, _66, _67, \
_68) \
34, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58), \
((BinaryMapEntry) _59, _60), ((BinaryMapEntry) _61, _62), \
((BinaryMapEntry) _63, _64), ((BinaryMapEntry) _65, _66), \
((BinaryMapEntry) _67, _68)})

#define __BINMAP_70(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58, _59, _60, _61, \
_62, _63, _64, _65, _66, _67, \
_68, _69, _70) \
35, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58), \
((BinaryMapEntry) _59, _60), ((BinaryMapEntry) _61, _62), \
((BinaryMapEntry) _63, _64), ((BinaryMapEntry) _65, _66), \
((BinaryMapEntry) _67, _68), ((BinaryMapEntry) _69, _70)})

#define __BINMAP_72(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58, _59, _60, _61, \
_62, _63, _64, _65, _66, _67, \
_68, _69, _70, _71, _72) \
36, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58), \
((BinaryMapEntry) _59, _60), ((BinaryMapEntry) _61, _62), \
((BinaryMapEntry) _63, _64), ((BinaryMapEntry) _65, _66), \
((BinaryMapEntry) _67, _68), ((BinaryMapEntry) _69, _70), \
((BinaryMapEntry) _71, _72)})

#define __BINMAP_74(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58, _59, _60, _61, \
_62, _63, _64, _65, _66, _67, \
_68, _69, _70, _71, _72, _73, \
_74) \
37, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58), \
((BinaryMapEntry) _59, _60), ((BinaryMapEntry) _61, _62), \
((BinaryMapEntry) _63, _64), ((BinaryMapEntry) _65, _66), \
((BinaryMapEntry) _67, _68), ((BinaryMapEntry) _69, _70), \
((BinaryMapEntry) _71, _72), ((BinaryMapEntry) _73, _74)})

#define __BINMAP_76(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58, _59, _60, _61, \
_62, _63, _64, _65, _66, _67, \
_68, _69, _70, _71, _72, _73, \
_74, _75, _76) \
38, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58), \
((BinaryMapEntry) _59, _60), ((BinaryMapEntry) _61, _62), \
((BinaryMapEntry) _63, _64), ((BinaryMapEntry) _65, _66), \
((BinaryMapEntry) _67, _68), ((BinaryMapEntry) _69, _70), \
((BinaryMapEntry) _71, _72), ((BinaryMapEntry) _73, _74), \
((BinaryMapEntry) _75, _76)})

#define __BINMAP_78(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58, _59, _60, _61, \
_62, _63, _64, _65, _66, _67, \
_68, _69, _70, _71, _72, _73, \
_74, _75, _76, _77, _78) \
39, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58), \
((BinaryMapEntry) _59, _60), ((BinaryMapEntry) _61, _62), \
((BinaryMapEntry) _63, _64), ((BinaryMapEntry) _65, _66), \
((BinaryMapEntry) _67, _68), ((BinaryMapEntry) _69, _70), \
((BinaryMapEntry) _71, _72), ((BinaryMapEntry) _73, _74), \
((BinaryMapEntry) _75, _76), ((BinaryMapEntry) _77, _78)})

#define __BINMAP_80(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58, _59, _60, _61, \
_62, _63, _64, _65, _66, _67, \
_68, _69, _70, _71, _72, _73, \
_74, _75, _76, _77, _78, _79, \
_80) \
40, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58), \
((BinaryMapEntry) _59, _60), ((BinaryMapEntry) _61, _62), \
((BinaryMapEntry) _63, _64), ((BinaryMapEntry) _65, _66), \
((BinaryMapEntry) _67, _68), ((BinaryMapEntry) _69, _70), \
((BinaryMapEntry) _71, _72), ((BinaryMapEntry) _73, _74), \
((BinaryMapEntry) _75, _76), ((BinaryMapEntry) _77, _78), \
((BinaryMapEntry) _79, _80)})

#define __BINMAP_82(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58, _59, _60, _61, \
_62, _63, _64, _65, _66, _67, \
_68, _69, _70, _71, _72, _73, \
_74, _75, _76, _77, _78, _79, \
_80, _81, _82) \
41, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58), \
((BinaryMapEntry) _59, _60), ((BinaryMapEntry) _61, _62), \
((BinaryMapEntry) _63, _64), ((BinaryMapEntry) _65, _66), \
((BinaryMapEntry) _67, _68), ((BinaryMapEntry) _69, _70), \
((BinaryMapEntry) _71, _72), ((BinaryMapEntry) _73, _74), \
((BinaryMapEntry) _75, _76), ((BinaryMapEntry) _77, _78), \
((BinaryMapEntry) _79, _80), ((BinaryMapEntry) _81, _82)})

#define __BINMAP_84(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58, _59, _60, _61, \
_62, _63, _64, _65, _66, _67, \
_68, _69, _70, _71, _72, _73, \
_74, _75, _76, _77, _78, _79, \
_80, _81, _82, _83, _84) \
42, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58), \
((BinaryMapEntry) _59, _60), ((BinaryMapEntry) _61, _62), \
((BinaryMapEntry) _63, _64), ((BinaryMapEntry) _65, _66), \
((BinaryMapEntry) _67, _68), ((BinaryMapEntry) _69, _70), \
((BinaryMapEntry) _71, _72), ((BinaryMapEntry) _73, _74), \
((BinaryMapEntry) _75, _76), ((BinaryMapEntry) _77, _78), \
((BinaryMapEntry) _79, _80), ((BinaryMapEntry) _81, _82), \
((BinaryMapEntry) _83, _84)})

#define __BINMAP_86(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58, _59, _60, _61, \
_62, _63, _64, _65, _66, _67, \
_68, _69, _70, _71, _72, _73, \
_74, _75, _76, _77, _78, _79, \
_80, _81, _82, _83, _84, _85, \
_86) \
43, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58), \
((BinaryMapEntry) _59, _60), ((BinaryMapEntry) _61, _62), \
((BinaryMapEntry) _63, _64), ((BinaryMapEntry) _65, _66), \
((BinaryMapEntry) _67, _68), ((BinaryMapEntry) _69, _70), \
((BinaryMapEntry) _71, _72), ((BinaryMapEntry) _73, _74), \
((BinaryMapEntry) _75, _76), ((BinaryMapEntry) _77, _78), \
((BinaryMapEntry) _79, _80), ((BinaryMapEntry) _81, _82), \
((BinaryMapEntry) _83, _84), ((BinaryMapEntry) _85, _86)})

#define __BINMAP_88(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58, _59, _60, _61, \
_62, _63, _64, _65, _66, _67, \
_68, _69, _70, _71, _72, _73, \
_74, _75, _76, _77, _78, _79, \
_80, _81, _82, _83, _84, _85, \
_86, _87, _88) \
44, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58), \
((BinaryMapEntry) _59, _60), ((BinaryMapEntry) _61, _62), \
((BinaryMapEntry) _63, _64), ((BinaryMapEntry) _65, _66), \
((BinaryMapEntry) _67, _68), ((BinaryMapEntry) _69, _70), \
((BinaryMapEntry) _71, _72), ((BinaryMapEntry) _73, _74), \
((BinaryMapEntry) _75, _76), ((BinaryMapEntry) _77, _78), \
((BinaryMapEntry) _79, _80), ((BinaryMapEntry) _81, _82), \
((BinaryMapEntry) _83, _84), ((BinaryMapEntry) _85, _86), \
((BinaryMapEntry) _87, _88)})

#define __BINMAP_90(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58, _59, _60, _61, \
_62, _63, _64, _65, _66, _67, \
_68, _69, _70, _71, _72, _73, \
_74, _75, _76, _77, _78, _79, \
_80, _81, _82, _83, _84, _85, \
_86, _87, _88, _89, _90) \
45, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58), \
((BinaryMapEntry) _59, _60), ((BinaryMapEntry) _61, _62), \
((BinaryMapEntry) _63, _64), ((BinaryMapEntry) _65, _66), \
((BinaryMapEntry) _67, _68), ((BinaryMapEntry) _69, _70), \
((BinaryMapEntry) _71, _72), ((BinaryMapEntry) _73, _74), \
((BinaryMapEntry) _75, _76), ((BinaryMapEntry) _77, _78), \
((BinaryMapEntry) _79, _80), ((BinaryMapEntry) _81, _82), \
((BinaryMapEntry) _83, _84), ((BinaryMapEntry) _85, _86), \
((BinaryMapEntry) _87, _88), ((BinaryMapEntry) _89, _90)})

#define __BINMAP_92(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58, _59, _60, _61, \
_62, _63, _64, _65, _66, _67, \
_68, _69, _70, _71, _72, _73, \
_74, _75, _76, _77, _78, _79, \
_80, _81, _82, _83, _84, _85, \
_86, _87, _88, _89, _90, _91, \
_92) \
46, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58), \
((BinaryMapEntry) _59, _60), ((BinaryMapEntry) _61, _62), \
((BinaryMapEntry) _63, _64), ((BinaryMapEntry) _65, _66), \
((BinaryMapEntry) _67, _68), ((BinaryMapEntry) _69, _70), \
((BinaryMapEntry) _71, _72), ((BinaryMapEntry) _73, _74), \
((BinaryMapEntry) _75, _76), ((BinaryMapEntry) _77, _78), \
((BinaryMapEntry) _79, _80), ((BinaryMapEntry) _81, _82), \
((BinaryMapEntry) _83, _84), ((BinaryMapEntry) _85, _86), \
((BinaryMapEntry) _87, _88), ((BinaryMapEntry) _89, _90), \
((BinaryMapEntry) _91, _92)})

#define __BINMAP_94(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58, _59, _60, _61, \
_62, _63, _64, _65, _66, _67, \
_68, _69, _70, _71, _72, _73, \
_74, _75, _76, _77, _78, _79, \
_80, _81, _82, _83, _84, _85, \
_86, _87, _88, _89, _90, _91, \
_92, _93, _94) \
47, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58), \
((BinaryMapEntry) _59, _60), ((BinaryMapEntry) _61, _62), \
((BinaryMapEntry) _63, _64), ((BinaryMapEntry) _65, _66), \
((BinaryMapEntry) _67, _68), ((BinaryMapEntry) _69, _70), \
((BinaryMapEntry) _71, _72), ((BinaryMapEntry) _73, _74), \
((BinaryMapEntry) _75, _76), ((BinaryMapEntry) _77, _78), \
((BinaryMapEntry) _79, _80), ((BinaryMapEntry) _81, _82), \
((BinaryMapEntry) _83, _84), ((BinaryMapEntry) _85, _86), \
((BinaryMapEntry) _87, _88), ((BinaryMapEntry) _89, _90), \
((BinaryMapEntry) _91, _92), ((BinaryMapEntry) _93, _94)})

#define __BINMAP_96(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58, _59, _60, _61, \
_62, _63, _64, _65, _66, _67, \
_68, _69, _70, _71, _72, _73, \
_74, _75, _76, _77, _78, _79, \
_80, _81, _82, _83, _84, _85, \
_86, _87, _88, _89, _90, _91, \
_92, _93, _94, _95, _96) \
48, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58), \
((BinaryMapEntry) _59, _60), ((BinaryMapEntry) _61, _62), \
((BinaryMapEntry) _63, _64), ((BinaryMapEntry) _65, _66), \
((BinaryMapEntry) _67, _68), ((BinaryMapEntry) _69, _70), \
((BinaryMapEntry) _71, _72), ((BinaryMapEntry) _73, _74), \
((BinaryMapEntry) _75, _76), ((BinaryMapEntry) _77, _78), \
((BinaryMapEntry) _79, _80), ((BinaryMapEntry) _81, _82), \
((BinaryMapEntry) _83, _84), ((BinaryMapEntry) _85, _86), \
((BinaryMapEntry) _87, _88), ((BinaryMapEntry) _89, _90), \
((BinaryMapEntry) _91, _92), ((BinaryMapEntry) _93, _94), \
((BinaryMapEntry) _95, _96)})

#define __BINMAP_98(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58, _59, _60, _61, \
_62, _63, _64, _65, _66, _67, \
_68, _69, _70, _71, _72, _73, \
_74, _75, _76, _77, _78, _79, \
_80, _81, _82, _83, _84, _85, \
_86, _87, _88, _89, _90, _91, \
_92, _93, _94, _95, _96, _97, \
_98) \
49, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58), \
((BinaryMapEntry) _59, _60), ((BinaryMapEntry) _61, _62), \
((BinaryMapEntry) _63, _64), ((BinaryMapEntry) _65, _66), \
((BinaryMapEntry) _67, _68), ((BinaryMapEntry) _69, _70), \
((BinaryMapEntry) _71, _72), ((BinaryMapEntry) _73, _74), \
((BinaryMapEntry) _75, _76), ((BinaryMapEntry) _77, _78), \
((BinaryMapEntry) _79, _80), ((BinaryMapEntry) _81, _82), \
((BinaryMapEntry) _83, _84), ((BinaryMapEntry) _85, _86), \
((BinaryMapEntry) _87, _88), ((BinaryMapEntry) _89, _90), \
((BinaryMapEntry) _91, _92), ((BinaryMapEntry) _93, _94), \
((BinaryMapEntry) _95, _96), ((BinaryMapEntry) _97, _98)})

#define __BINMAP_100(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58, _59, _60, _61, \
_62, _63, _64, _65, _66, _67, \
_68, _69, _70, _71, _72, _73, \
_74, _75, _76, _77, _78, _79, \
_80, _81, _82, _83, _84, _85, \
_86, _87, _88, _89, _90, _91, \
_92, _93, _94, _95, _96, _97, \
_98, _99, _100) \
50, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58), \
((BinaryMapEntry) _59, _60), ((BinaryMapEntry) _61, _62), \
((BinaryMapEntry) _63, _64), ((BinaryMapEntry) _65, _66), \
((BinaryMapEntry) _67, _68), ((BinaryMapEntry) _69, _70), \
((BinaryMapEntry) _71, _72), ((BinaryMapEntry) _73, _74), \
((BinaryMapEntry) _75, _76), ((BinaryMapEntry) _77, _78), \
((BinaryMapEntry) _79, _80), ((BinaryMapEntry) _81, _82), \
((BinaryMapEntry) _83, _84), ((BinaryMapEntry) _85, _86), \
((BinaryMapEntry) _87, _88), ((BinaryMapEntry) _89, _90), \
((BinaryMapEntry) _91, _92), ((BinaryMapEntry) _93, _94), \
((BinaryMapEntry) _95, _96), ((BinaryMapEntry) _97, _98), \
((BinaryMapEntry) _99, _100)})

#define __BINMAP_102(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58, _59, _60, _61, \
_62, _63, _64, _65, _66, _67, \
_68, _69, _70, _71, _72, _73, \
_74, _75, _76, _77, _78, _79, \
_80, _81, _82, _83, _84, _85, \
_86, _87, _88, _89, _90, _91, \
_92, _93, _94, _95, _96, _97, \
_98, _99, _100, _101, _102) \
51, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58), \
((BinaryMapEntry) _59, _60), ((BinaryMapEntry) _61, _62), \
((BinaryMapEntry) _63, _64), ((BinaryMapEntry) _65, _66), \
((BinaryMapEntry) _67, _68), ((BinaryMapEntry) _69, _70), \
((BinaryMapEntry) _71, _72), ((BinaryMapEntry) _73, _74), \
((BinaryMapEntry) _75, _76), ((BinaryMapEntry) _77, _78), \
((BinaryMapEntry) _79, _80), ((BinaryMapEntry) _81, _82), \
((BinaryMapEntry) _83, _84), ((BinaryMapEntry) _85, _86), \
((BinaryMapEntry) _87, _88), ((BinaryMapEntry) _89, _90), \
((BinaryMapEntry) _91, _92), ((BinaryMapEntry) _93, _94), \
((BinaryMapEntry) _95, _96), ((BinaryMapEntry) _97, _98), \
((BinaryMapEntry) _99, _100), ((BinaryMapEntry) _101, _102)})

#define __BINMAP_104(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58, _59, _60, _61, \
_62, _63, _64, _65, _66, _67, \
_68, _69, _70, _71, _72, _73, \
_74, _75, _76, _77, _78, _79, \
_80, _81, _82, _83, _84, _85, \
_86, _87, _88, _89, _90, _91, \
_92, _93, _94, _95, _96, _97, \
_98, _99, _100, _101, _102, _103, \
_104) \
52, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58), \
((BinaryMapEntry) _59, _60), ((BinaryMapEntry) _61, _62), \
((BinaryMapEntry) _63, _64), ((BinaryMapEntry) _65, _66), \
((BinaryMapEntry) _67, _68), ((BinaryMapEntry) _69, _70), \
((BinaryMapEntry) _71, _72), ((BinaryMapEntry) _73, _74), \
((BinaryMapEntry) _75, _76), ((BinaryMapEntry) _77, _78), \
((BinaryMapEntry) _79, _80), ((BinaryMapEntry) _81, _82), \
((BinaryMapEntry) _83, _84), ((BinaryMapEntry) _85, _86), \
((BinaryMapEntry) _87, _88), ((BinaryMapEntry) _89, _90), \
((BinaryMapEntry) _91, _92), ((BinaryMapEntry) _93, _94), \
((BinaryMapEntry) _95, _96), ((BinaryMapEntry) _97, _98), \
((BinaryMapEntry) _99, _100), ((BinaryMapEntry) _101, _102), \
((BinaryMapEntry) _103, _104)})

#define __BINMAP_106(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58, _59, _60, _61, \
_62, _63, _64, _65, _66, _67, \
_68, _69, _70, _71, _72, _73, \
_74, _75, _76, _77, _78, _79, \
_80, _81, _82, _83, _84, _85, \
_86, _87, _88, _89, _90, _91, \
_92, _93, _94, _95, _96, _97, \
_98, _99, _100, _101, _102, _103, \
_104, _105, _106) \
53, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58), \
((BinaryMapEntry) _59, _60), ((BinaryMapEntry) _61, _62), \
((BinaryMapEntry) _63, _64), ((BinaryMapEntry) _65, _66), \
((BinaryMapEntry) _67, _68), ((BinaryMapEntry) _69, _70), \
((BinaryMapEntry) _71, _72), ((BinaryMapEntry) _73, _74), \
((BinaryMapEntry) _75, _76), ((BinaryMapEntry) _77, _78), \
((BinaryMapEntry) _79, _80), ((BinaryMapEntry) _81, _82), \
((BinaryMapEntry) _83, _84), ((BinaryMapEntry) _85, _86), \
((BinaryMapEntry) _87, _88), ((BinaryMapEntry) _89, _90), \
((BinaryMapEntry) _91, _92), ((BinaryMapEntry) _93, _94), \
((BinaryMapEntry) _95, _96), ((BinaryMapEntry) _97, _98), \
((BinaryMapEntry) _99, _100), ((BinaryMapEntry) _101, _102), \
((BinaryMapEntry) _103, _104), ((BinaryMapEntry) _105, _106)})

#define __BINMAP_108(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58, _59, _60, _61, \
_62, _63, _64, _65, _66, _67, \
_68, _69, _70, _71, _72, _73, \
_74, _75, _76, _77, _78, _79, \
_80, _81, _82, _83, _84, _85, \
_86, _87, _88, _89, _90, _91, \
_92, _93, _94, _95, _96, _97, \
_98, _99, _100, _101, _102, _103, \
_104, _105, _106, _107, _108) \
54, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58), \
((BinaryMapEntry) _59, _60), ((BinaryMapEntry) _61, _62), \
((BinaryMapEntry) _63, _64), ((BinaryMapEntry) _65, _66), \
((BinaryMapEntry) _67, _68), ((BinaryMapEntry) _69, _70), \
((BinaryMapEntry) _71, _72), ((BinaryMapEntry) _73, _74), \
((BinaryMapEntry) _75, _76), ((BinaryMapEntry) _77, _78), \
((BinaryMapEntry) _79, _80), ((BinaryMapEntry) _81, _82), \
((BinaryMapEntry) _83, _84), ((BinaryMapEntry) _85, _86), \
((BinaryMapEntry) _87, _88), ((BinaryMapEntry) _89, _90), \
((BinaryMapEntry) _91, _92), ((BinaryMapEntry) _93, _94), \
((BinaryMapEntry) _95, _96), ((BinaryMapEntry) _97, _98), \
((BinaryMapEntry) _99, _100), ((BinaryMapEntry) _101, _102), \
((BinaryMapEntry) _103, _104), ((BinaryMapEntry) _105, _106), \
((BinaryMapEntry) _107, _108)})

#define __BINMAP_110(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58, _59, _60, _61, \
_62, _63, _64, _65, _66, _67, \
_68, _69, _70, _71, _72, _73, \
_74, _75, _76, _77, _78, _79, \
_80, _81, _82, _83, _84, _85, \
_86, _87, _88, _89, _90, _91, \
_92, _93, _94, _95, _96, _97, \
_98, _99, _100, _101, _102, _103, \
_104, _105, _106, _107, _108, _109, \
_110) \
55, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58), \
((BinaryMapEntry) _59, _60), ((BinaryMapEntry) _61, _62), \
((BinaryMapEntry) _63, _64), ((BinaryMapEntry) _65, _66), \
((BinaryMapEntry) _67, _68), ((BinaryMapEntry) _69, _70), \
((BinaryMapEntry) _71, _72), ((BinaryMapEntry) _73, _74), \
((BinaryMapEntry) _75, _76), ((BinaryMapEntry) _77, _78), \
((BinaryMapEntry) _79, _80), ((BinaryMapEntry) _81, _82), \
((BinaryMapEntry) _83, _84), ((BinaryMapEntry) _85, _86), \
((BinaryMapEntry) _87, _88), ((BinaryMapEntry) _89, _90), \
((BinaryMapEntry) _91, _92), ((BinaryMapEntry) _93, _94), \
((BinaryMapEntry) _95, _96), ((BinaryMapEntry) _97, _98), \
((BinaryMapEntry) _99, _100), ((BinaryMapEntry) _101, _102), \
((BinaryMapEntry) _103, _104), ((BinaryMapEntry) _105, _106), \
((BinaryMapEntry) _107, _108), ((BinaryMapEntry) _109, _110)})

#define __BINMAP_112(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58, _59, _60, _61, \
_62, _63, _64, _65, _66, _67, \
_68, _69, _70, _71, _72, _73, \
_74, _75, _76, _77, _78, _79, \
_80, _81, _82, _83, _84, _85, \
_86, _87, _88, _89, _90, _91, \
_92, _93, _94, _95, _96, _97, \
_98, _99, _100, _101, _102, _103, \
_104, _105, _106, _107, _108, _109, \
_110, _111, _112) \
56, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58), \
((BinaryMapEntry) _59, _60), ((BinaryMapEntry) _61, _62), \
((BinaryMapEntry) _63, _64), ((BinaryMapEntry) _65, _66), \
((BinaryMapEntry) _67, _68), ((BinaryMapEntry) _69, _70), \
((BinaryMapEntry) _71, _72), ((BinaryMapEntry) _73, _74), \
((BinaryMapEntry) _75, _76), ((BinaryMapEntry) _77, _78), \
((BinaryMapEntry) _79, _80), ((BinaryMapEntry) _81, _82), \
((BinaryMapEntry) _83, _84), ((BinaryMapEntry) _85, _86), \
((BinaryMapEntry) _87, _88), ((BinaryMapEntry) _89, _90), \
((BinaryMapEntry) _91, _92), ((BinaryMapEntry) _93, _94), \
((BinaryMapEntry) _95, _96), ((BinaryMapEntry) _97, _98), \
((BinaryMapEntry) _99, _100), ((BinaryMapEntry) _101, _102), \
((BinaryMapEntry) _103, _104), ((BinaryMapEntry) _105, _106), \
((BinaryMapEntry) _107, _108), ((BinaryMapEntry) _109, _110), \
((BinaryMapEntry) _111, _112)})

#define __BINMAP_114(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58, _59, _60, _61, \
_62, _63, _64, _65, _66, _67, \
_68, _69, _70, _71, _72, _73, \
_74, _75, _76, _77, _78, _79, \
_80, _81, _82, _83, _84, _85, \
_86, _87, _88, _89, _90, _91, \
_92, _93, _94, _95, _96, _97, \
_98, _99, _100, _101, _102, _103, \
_104, _105, _106, _107, _108, _109, \
_110, _111, _112, _113, _114) \
57, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58), \
((BinaryMapEntry) _59, _60), ((BinaryMapEntry) _61, _62), \
((BinaryMapEntry) _63, _64), ((BinaryMapEntry) _65, _66), \
((BinaryMapEntry) _67, _68), ((BinaryMapEntry) _69, _70), \
((BinaryMapEntry) _71, _72), ((BinaryMapEntry) _73, _74), \
((BinaryMapEntry) _75, _76), ((BinaryMapEntry) _77, _78), \
((BinaryMapEntry) _79, _80), ((BinaryMapEntry) _81, _82), \
((BinaryMapEntry) _83, _84), ((BinaryMapEntry) _85, _86), \
((BinaryMapEntry) _87, _88), ((BinaryMapEntry) _89, _90), \
((BinaryMapEntry) _91, _92), ((BinaryMapEntry) _93, _94), \
((BinaryMapEntry) _95, _96), ((BinaryMapEntry) _97, _98), \
((BinaryMapEntry) _99, _100), ((BinaryMapEntry) _101, _102), \
((BinaryMapEntry) _103, _104), ((BinaryMapEntry) _105, _106), \
((BinaryMapEntry) _107, _108), ((BinaryMapEntry) _109, _110), \
((BinaryMapEntry) _111, _112), ((BinaryMapEntry) _113, _114)})

#define __BINMAP_116(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58, _59, _60, _61, \
_62, _63, _64, _65, _66, _67, \
_68, _69, _70, _71, _72, _73, \
_74, _75, _76, _77, _78, _79, \
_80, _81, _82, _83, _84, _85, \
_86, _87, _88, _89, _90, _91, \
_92, _93, _94, _95, _96, _97, \
_98, _99, _100, _101, _102, _103, \
_104, _105, _106, _107, _108, _109, \
_110, _111, _112, _113, _114, _115, \
_116) \
58, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58), \
((BinaryMapEntry) _59, _60), ((BinaryMapEntry) _61, _62), \
((BinaryMapEntry) _63, _64), ((BinaryMapEntry) _65, _66), \
((BinaryMapEntry) _67, _68), ((BinaryMapEntry) _69, _70), \
((BinaryMapEntry) _71, _72), ((BinaryMapEntry) _73, _74), \
((BinaryMapEntry) _75, _76), ((BinaryMapEntry) _77, _78), \
((BinaryMapEntry) _79, _80), ((BinaryMapEntry) _81, _82), \
((BinaryMapEntry) _83, _84), ((BinaryMapEntry) _85, _86), \
((BinaryMapEntry) _87, _88), ((BinaryMapEntry) _89, _90), \
((BinaryMapEntry) _91, _92), ((BinaryMapEntry) _93, _94), \
((BinaryMapEntry) _95, _96), ((BinaryMapEntry) _97, _98), \
((BinaryMapEntry) _99, _100), ((BinaryMapEntry) _101, _102), \
((BinaryMapEntry) _103, _104), ((BinaryMapEntry) _105, _106), \
((BinaryMapEntry) _107, _108), ((BinaryMapEntry) _109, _110), \
((BinaryMapEntry) _111, _112), ((BinaryMapEntry) _113, _114), \
((BinaryMapEntry) _115, _116)})

#define __BINMAP_118(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58, _59, _60, _61, \
_62, _63, _64, _65, _66, _67, \
_68, _69, _70, _71, _72, _73, \
_74, _75, _76, _77, _78, _79, \
_80, _81, _82, _83, _84, _85, \
_86, _87, _88, _89, _90, _91, \
_92, _93, _94, _95, _96, _97, \
_98, _99, _100, _101, _102, _103, \
_104, _105, _106, _107, _108, _109, \
_110, _111, _112, _113, _114, _115, \
_116, _117, _118) \
59, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58), \
((BinaryMapEntry) _59, _60), ((BinaryMapEntry) _61, _62), \
((BinaryMapEntry) _63, _64), ((BinaryMapEntry) _65, _66), \
((BinaryMapEntry) _67, _68), ((BinaryMapEntry) _69, _70), \
((BinaryMapEntry) _71, _72), ((BinaryMapEntry) _73, _74), \
((BinaryMapEntry) _75, _76), ((BinaryMapEntry) _77, _78), \
((BinaryMapEntry) _79, _80), ((BinaryMapEntry) _81, _82), \
((BinaryMapEntry) _83, _84), ((BinaryMapEntry) _85, _86), \
((BinaryMapEntry) _87, _88), ((BinaryMapEntry) _89, _90), \
((BinaryMapEntry) _91, _92), ((BinaryMapEntry) _93, _94), \
((BinaryMapEntry) _95, _96), ((BinaryMapEntry) _97, _98), \
((BinaryMapEntry) _99, _100), ((BinaryMapEntry) _101, _102), \
((BinaryMapEntry) _103, _104), ((BinaryMapEntry) _105, _106), \
((BinaryMapEntry) _107, _108), ((BinaryMapEntry) _109, _110), \
((BinaryMapEntry) _111, _112), ((BinaryMapEntry) _113, _114), \
((BinaryMapEntry) _115, _116), ((BinaryMapEntry) _117, _118)})

#define __BINMAP_120(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58, _59, _60, _61, \
_62, _63, _64, _65, _66, _67, \
_68, _69, _70, _71, _72, _73, \
_74, _75, _76, _77, _78, _79, \
_80, _81, _82, _83, _84, _85, \
_86, _87, _88, _89, _90, _91, \
_92, _93, _94, _95, _96, _97, \
_98, _99, _100, _101, _102, _103, \
_104, _105, _106, _107, _108, _109, \
_110, _111, _112, _113, _114, _115, \
_116, _117, _118, _119, _120) \
60, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58), \
((BinaryMapEntry) _59, _60), ((BinaryMapEntry) _61, _62), \
((BinaryMapEntry) _63, _64), ((BinaryMapEntry) _65, _66), \
((BinaryMapEntry) _67, _68), ((BinaryMapEntry) _69, _70), \
((BinaryMapEntry) _71, _72), ((BinaryMapEntry) _73, _74), \
((BinaryMapEntry) _75, _76), ((BinaryMapEntry) _77, _78), \
((BinaryMapEntry) _79, _80), ((BinaryMapEntry) _81, _82), \
((BinaryMapEntry) _83, _84), ((BinaryMapEntry) _85, _86), \
((BinaryMapEntry) _87, _88), ((BinaryMapEntry) _89, _90), \
((BinaryMapEntry) _91, _92), ((BinaryMapEntry) _93, _94), \
((BinaryMapEntry) _95, _96), ((BinaryMapEntry) _97, _98), \
((BinaryMapEntry) _99, _100), ((BinaryMapEntry) _101, _102), \
((BinaryMapEntry) _103, _104), ((BinaryMapEntry) _105, _106), \
((BinaryMapEntry) _107, _108), ((BinaryMapEntry) _109, _110), \
((BinaryMapEntry) _111, _112), ((BinaryMapEntry) _113, _114), \
((BinaryMapEntry) _115, _116), ((BinaryMapEntry) _117, _118), \
((BinaryMapEntry) _119, _120)})

#define __BINMAP_122(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58, _59, _60, _61, \
_62, _63, _64, _65, _66, _67, \
_68, _69, _70, _71, _72, _73, \
_74, _75, _76, _77, _78, _79, \
_80, _81, _82, _83, _84, _85, \
_86, _87, _88, _89, _90, _91, \
_92, _93, _94, _95, _96, _97, \
_98, _99, _100, _101, _102, _103, \
_104, _105, _106, _107, _108, _109, \
_110, _111, _112, _113, _114, _115, \
_116, _117, _118, _119, _120, _121, \
_122) \
61, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58), \
((BinaryMapEntry) _59, _60), ((BinaryMapEntry) _61, _62), \
((BinaryMapEntry) _63, _64), ((BinaryMapEntry) _65, _66), \
((BinaryMapEntry) _67, _68), ((BinaryMapEntry) _69, _70), \
((BinaryMapEntry) _71, _72), ((BinaryMapEntry) _73, _74), \
((BinaryMapEntry) _75, _76), ((BinaryMapEntry) _77, _78), \
((BinaryMapEntry) _79, _80), ((BinaryMapEntry) _81, _82), \
((BinaryMapEntry) _83, _84), ((BinaryMapEntry) _85, _86), \
((BinaryMapEntry) _87, _88), ((BinaryMapEntry) _89, _90), \
((BinaryMapEntry) _91, _92), ((BinaryMapEntry) _93, _94), \
((BinaryMapEntry) _95, _96), ((BinaryMapEntry) _97, _98), \
((BinaryMapEntry) _99, _100), ((BinaryMapEntry) _101, _102), \
((BinaryMapEntry) _103, _104), ((BinaryMapEntry) _105, _106), \
((BinaryMapEntry) _107, _108), ((BinaryMapEntry) _109, _110), \
((BinaryMapEntry) _111, _112), ((BinaryMapEntry) _113, _114), \
((BinaryMapEntry) _115, _116), ((BinaryMapEntry) _117, _118), \
((BinaryMapEntry) _119, _120), ((BinaryMapEntry) _121, _122)})

#define __BINMAP_124(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58, _59, _60, _61, \
_62, _63, _64, _65, _66, _67, \
_68, _69, _70, _71, _72, _73, \
_74, _75, _76, _77, _78, _79, \
_80, _81, _82, _83, _84, _85, \
_86, _87, _88, _89, _90, _91, \
_92, _93, _94, _95, _96, _97, \
_98, _99, _100, _101, _102, _103, \
_104, _105, _106, _107, _108, _109, \
_110, _111, _112, _113, _114, _115, \
_116, _117, _118, _119, _120, _121, \
_122, _123, _124) \
62, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58), \
((BinaryMapEntry) _59, _60), ((BinaryMapEntry) _61, _62), \
((BinaryMapEntry) _63, _64), ((BinaryMapEntry) _65, _66), \
((BinaryMapEntry) _67, _68), ((BinaryMapEntry) _69, _70), \
((BinaryMapEntry) _71, _72), ((BinaryMapEntry) _73, _74), \
((BinaryMapEntry) _75, _76), ((BinaryMapEntry) _77, _78), \
((BinaryMapEntry) _79, _80), ((BinaryMapEntry) _81, _82), \
((BinaryMapEntry) _83, _84), ((BinaryMapEntry) _85, _86), \
((BinaryMapEntry) _87, _88), ((BinaryMapEntry) _89, _90), \
((BinaryMapEntry) _91, _92), ((BinaryMapEntry) _93, _94), \
((BinaryMapEntry) _95, _96), ((BinaryMapEntry) _97, _98), \
((BinaryMapEntry) _99, _100), ((BinaryMapEntry) _101, _102), \
((BinaryMapEntry) _103, _104), ((BinaryMapEntry) _105, _106), \
((BinaryMapEntry) _107, _108), ((BinaryMapEntry) _109, _110), \
((BinaryMapEntry) _111, _112), ((BinaryMapEntry) _113, _114), \
((BinaryMapEntry) _115, _116), ((BinaryMapEntry) _117, _118), \
((BinaryMapEntry) _119, _120), ((BinaryMapEntry) _121, _122), \
((BinaryMapEntry) _123, _124)})

#define __BINMAP_126(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58, _59, _60, _61, \
_62, _63, _64, _65, _66, _67, \
_68, _69, _70, _71, _72, _73, \
_74, _75, _76, _77, _78, _79, \
_80, _81, _82, _83, _84, _85, \
_86, _87, _88, _89, _90, _91, \
_92, _93, _94, _95, _96, _97, \
_98, _99, _100, _101, _102, _103, \
_104, _105, _106, _107, _108, _109, \
_110, _111, _112, _113, _114, _115, \
_116, _117, _118, _119, _120, _121, \
_122, _123, _124, _125, _126) \
63, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58), \
((BinaryMapEntry) _59, _60), ((BinaryMapEntry) _61, _62), \
((BinaryMapEntry) _63, _64), ((BinaryMapEntry) _65, _66), \
((BinaryMapEntry) _67, _68), ((BinaryMapEntry) _69, _70), \
((BinaryMapEntry) _71, _72), ((BinaryMapEntry) _73, _74), \
((BinaryMapEntry) _75, _76), ((BinaryMapEntry) _77, _78), \
((BinaryMapEntry) _79, _80), ((BinaryMapEntry) _81, _82), \
((BinaryMapEntry) _83, _84), ((BinaryMapEntry) _85, _86), \
((BinaryMapEntry) _87, _88), ((BinaryMapEntry) _89, _90), \
((BinaryMapEntry) _91, _92), ((BinaryMapEntry) _93, _94), \
((BinaryMapEntry) _95, _96), ((BinaryMapEntry) _97, _98), \
((BinaryMapEntry) _99, _100), ((BinaryMapEntry) _101, _102), \
((BinaryMapEntry) _103, _104), ((BinaryMapEntry) _105, _106), \
((BinaryMapEntry) _107, _108), ((BinaryMapEntry) _109, _110), \
((BinaryMapEntry) _111, _112), ((BinaryMapEntry) _113, _114), \
((BinaryMapEntry) _115, _116), ((BinaryMapEntry) _117, _118), \
((BinaryMapEntry) _119, _120), ((BinaryMapEntry) _121, _122), \
((BinaryMapEntry) _123, _124), ((BinaryMapEntry) _125, _126)})

#define __BINMAP_128(_1, _2, _3, _4, _5, _6, _7, \
_8, _9, _10, _11, _12, _13, \
_14, _15, _16, _17, _18, _19, \
_20, _21, _22, _23, _24, _25, \
_26, _27, _28, _29, _30, _31, \
_32, _33, _34, _35, _36, _37, \
_38, _39, _40, _41, _42, _43, \
_44, _45, _46, _47, _48, _49, \
_50, _51, _52, _53, _54, _55, \
_56, _57, _58, _59, _60, _61, \
_62, _63, _64, _65, _66, _67, \
_68, _69, _70, _71, _72, _73, \
_74, _75, _76, _77, _78, _79, \
_80, _81, _82, _83, _84, _85, \
_86, _87, _88, _89, _90, _91, \
_92, _93, _94, _95, _96, _97, \
_98, _99, _100, _101, _102, _103, \
_104, _105, _106, _107, _108, _109, \
_110, _111, _112, _113, _114, _115, \
_116, _117, _118, _119, _120, _121, \
_122, _123, _124, _125, _126, _127, \
_128) \
64, ((BinaryMapEntry[]) {((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6), \
((BinaryMapEntry) _7, _8), ((BinaryMapEntry) _9, _10), \
((BinaryMapEntry) _11, _12), ((BinaryMapEntry) _13, _14), \
((BinaryMapEntry) _15, _16), ((BinaryMapEntry) _17, _18), \
((BinaryMapEntry) _19, _20), ((BinaryMapEntry) _21, _22), \
((BinaryMapEntry) _23, _24), ((BinaryMapEntry) _25, _26), \
((BinaryMapEntry) _27, _28), ((BinaryMapEntry) _29, _30), \
((BinaryMapEntry) _31, _32), ((BinaryMapEntry) _33, _34), \
((BinaryMapEntry) _35, _36), ((BinaryMapEntry) _37, _38), \
((BinaryMapEntry) _39, _40), ((BinaryMapEntry) _41, _42), \
((BinaryMapEntry) _43, _44), ((BinaryMapEntry) _45, _46), \
((BinaryMapEntry) _47, _48), ((BinaryMapEntry) _49, _50), \
((BinaryMapEntry) _51, _52), ((BinaryMapEntry) _53, _54), \
((BinaryMapEntry) _55, _56), ((BinaryMapEntry) _57, _58), \
((BinaryMapEntry) _59, _60), ((BinaryMapEntry) _61, _62), \
((BinaryMapEntry) _63, _64), ((BinaryMapEntry) _65, _66), \
((BinaryMapEntry) _67, _68), ((BinaryMapEntry) _69, _70), \
((BinaryMapEntry) _71, _72), ((BinaryMapEntry) _73, _74), \
((BinaryMapEntry) _75, _76), ((BinaryMapEntry) _77, _78), \
((BinaryMapEntry) _79, _80), ((BinaryMapEntry) _81, _82), \
((BinaryMapEntry) _83, _84), ((BinaryMapEntry) _85, _86), \
((BinaryMapEntry) _87, _88), ((BinaryMapEntry) _89, _90), \
((BinaryMapEntry) _91, _92), ((BinaryMapEntry) _93, _94), \
((BinaryMapEntry) _95, _96), ((BinaryMapEntry) _97, _98), \
((BinaryMapEntry) _99, _100), ((BinaryMapEntry) _101, _102), \
((BinaryMapEntry) _103, _104), ((BinaryMapEntry) _105, _106), \
((BinaryMapEntry) _107, _108), ((BinaryMapEntry) _109, _110), \
((BinaryMapEntry) _111, _112), ((BinaryMapEntry) _113, _114), \
((BinaryMapEntry) _115, _116), ((BinaryMapEntry) _117, _118), \
((BinaryMapEntry) _119, _120), ((BinaryMapEntry) _121, _122), \
((BinaryMapEntry) _123, _124), ((BinaryMapEntry) _125, _126), \
((BinaryMapEntry) _127, _128)})