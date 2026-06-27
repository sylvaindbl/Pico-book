#pragma once
const unsigned long BOOK_SIZE_CHARACTERS = 14113;
const char BOOK[] PROGMEM = R"BOOKTEXT(

ANSI C

ANSI C, ISO C, and Standard C are successive standards for the C programming language published by the American National Standards Institute (ANSI) and ISO/IEC JTC 1/SC 22/WG 14 of the International Organization for Standardization (ISO) and the International Electrotechnical Commission (IEC). Historically, the names referred specifically to the original and best-supported version of the standard (known as C89 or C90). Software developers writing in C are encouraged to conform to the standards, as doing so helps portability between compilers.


History and outlook

The first standard for C was published by ANSI. Although this document was subsequently adopted by ISO/IEC and subsequent revisions published by ISO/IEC have been adopted by ANSI, "ANSI C" is still used to refer to the standard.[1] While some software developers use the term ISO C, others are standards-
body neutral and use Standard C.

Informal specification: K&R C (C78)
Informal specification in 1978 (Brian Kernighan and Dennis Ritchie book The C Programming Language).

Standardizing C
In 1983, the American National Standards Institute formed a committee, X3J11, to establish a standard specification of C. In 1985, the first Standard Draft was released, sometimes referred to as C85. In 1986, another Draft Standard was released, sometimes referred to as C86. The prerelease Standard C was
published in 1988, and sometimes referred to as C88.[2]

C89
The ANSI standard was completed in 1989 and ratified as ANSI X3.159-1989 "Programming Language C." This version of the language is often referred to as "ANSI C". Later on sometimes the label "C89" is used to distinguish it from C90 but using the same labeling method.

C90
The same standard as C89 was ratified by ISO/IEC as ISO/IEC 9899:1990, with only formatting changes,[3] which is sometimes referred to as C90. Therefore, the terms "C89" and "C90" refer to a language that is virtually identical.
This standard has been withdrawn by both ANSI/INCITS[4] and ISO/IEC.[5]

C94/C95
In 1995, the ISO/IEC published an extension, called Amendment 1, for the C standard. Its full name finally was ISO/IEC 9899:1990/AMD1:1995, nicknamed C94 or C95. Aside from error correction there were further changes to the language capabilities,[6][7] such as:

Improved multi-byte and wide character support in the standard library, introducing
<wchar.h> and <wctype.h> as well as multi-byte I/O Addition of digraphs to the language
Specification of standard macros for the alternative specification of operators, e.g. and for
&&
Specification of the standard macro 	STDC_VERSION	.
This was both the first standard with a  STDC_VERSION   value (199409L) and the first version in which the year in that value did not match the year of publication (1995), leading to common names of both C94 and C95. This would happen again in C17 (2018) and C23 (2024), but they are more commonly
known by their earlier years, while this standard is often referred to by its later year.[8]

In addition to the amendment, two technical corrigenda were published by ISO for C90:

ISO/IEC 9899:1990/Cor 1:1994 TCOR1 in 1994[9]
ISO/IEC 9899:1990/Cor 2:1996 in 1996[10]


Preprocessor test for C95 compatibility


C99
In March 2000, ANSI adopted the ISO/IEC 9899:1999 standard.[11] This standard is commonly referred to as C99. Some notable additions to the previous standard include:

New built-in data types: long long, _Bool, _Complex, and _Imaginary
Several new core language features, including static array indices, designated initializers, compound literals, variable-length arrays, flexible array members, variadic macros, and restrict keyword
Several new library headers, including stdint.h, <tgmath.h>, fenv.h, <complex.h>
Improved compatibility with several C++ features, including inline functions, single-line comments with //, mixing declarations and code, and universal character names in identifiers
Removed several dangerous C89 language features such as implicit function declarations and implicit int
Three technical corrigenda were published by ISO for C99:

ISO/IEC 9899:1999/Cor 1:2001(E) ISO/IEC 9899:1999/Cor 2:2004(E)
ISO/IEC 9899:1999/Cor 3:2007(E), notable for deprecating the standard library function gets
This standard has been withdrawn by both ANSI/INCITS[12] and ISO/IEC[13] in favour of C11.


C11
C11 was officially ratified and published on December 8, 2011. Notable features include improved Unicode support, type-generic expressions using the new _Generic keyword, a cross-platform multi- threading API (threads.h), and atomic types support in both core language and the library (stdatomic.h).
One technical corrigendum has been published by ISO for C11:

ISO/IEC 9899:2011/Cor 1:2012[14]


C17
C17 was published in June 2018.[15] Rather than introducing new language features, it only addresses defects in C11.[16]

C23
C23 was published in October 2024, and is the current standard for the C programming language.[17]


C2Y
C2Y is an informal name for the next revision of the C programming language that is hoped to be released in the later 2020s.

Other related ISO publications
As part of the standardization process, ISO/IEC also publishes technical reports and specifications related to the C language:

ISO/IEC TR 19769:2004,[18] on library extensions to support Unicode transformation formats, integrated into C11
ISO/IEC TR 24731-1:2007,[19] on library extensions to support bounds-checked interfaces, integrated into C11
ISO/IEC TR 18037:2008,[20] on embedded C extensions
ISO/IEC TR 24732:2009,[21] on decimal floating point arithmetic, superseded by ISO/IEC TS 18661-2:2015
ISO/IEC TR 24747:2009,[22] on special mathematical functions,
ISO/IEC TR 24731-2:2010,[23] on library extensions to support dynamic allocation functions ISO/IEC TS 17961:2013,[24] on secure coding in C
ISO/IEC TS 18661-1:2014,[25] on IEC 60559:2011-compatible binary floating-point arithmetic

ISO/IEC TS 18661-2:2015,[26] on IEC 60559:2011-compatible decimal floating point arithmetic
ISO/IEC TS 18661-3:2015,[27] on IEC 60559:2011-compatible interchange and extended floating-point types
ISO/IEC TS 18661-4:2015,[28] on IEC 60559:2011-compatible supplementary functions
More technical specifications are in development and pending approval, including the fifth and final part of TS 18661, a software transactional memory specification, and parallel library extensions.[29]


Support from major compilers

ANSI C is supported by almost all the widely used compilers. GCC and Clang are two major C compilers popular today, both based on the C11 with updates including changes from later specifications such as C17.[30][31] Any source code written only in standard C and without any hardware dependent assumptions is virtually guaranteed to compile correctly on any platform with a conforming C implementation. Without such precautions, most programs may compile only on a certain platform or with a particular compiler, due, for example, to the use of non-standard libraries, such as GUI libraries, or to the reliance on compiler- or platform-specific attributes such as the exact size of certain data types and byte endianness.

Compliance detectability
To mitigate the differences between K&R C and the ANSI C standard, the   STDC   ("standard c") macro can be used to split code into ANSI and K&R sections.


In the above example, a prototype is used in a function declaration for ANSI compliant implementations, while an obsolescent non-prototype declaration is used otherwise. Those are still ANSI-compliant as of C99. Note how this code checks both definition and evaluation: this is because some implementations
may set   STDC   to zero to indicate non-ANSI compliance.[32]


Compiler support

List of compilers supporting ANSI C:

Acornsoft ANSI C (first version in 1988, revised in 1989) Amsterdam Compiler Kit (C K&R and C89/90)
ARM RealView
Clang (full C89/C90 and C99, partial C11, C17, C23 and C2y), using LLVM backend GCC (full C89/90, C99, C11, C17, C23 and some of experimental/incomplete C2y) HP C/ANSI C compiler (C89 and C99)[33]
IBM XL C/C++ (C11, starting with version 12.1)[34]

Intel's ICC (later versions are based on clang, and have its support) LabWindows/CVI
LCC
Oracle Developer Studio OpenWatcom (C89/90 and some C99)
Pelles C (C99 and C11. Windows only.)[35] vbcc (C89/90 and C99)
Tiny C Compiler (C89/90 and some C99)

See also



Behavioral Description Language Compatibility of C and C++

References

1. Brad Kelechava (2017-09-14). "The Origin of ANSI C and ISO C" (https://blog.ansi.org/2017/ 09/origin-ansi-c-iso-c/). Retrieved 2018-08-14.
2. Richard Hale Shaw (13 September 1988). "Standard C: The ANSI Draft Grows Up" (https://a rchive.org/details/PC-Mag-1988-09-13/page/n115/). PC Magazine. Vol. 7, no. 15. pp. 116-
117. Retrieved 15 November 2022.
3. "Standards - Using the GNU Compiler Collection (GCC)" (https://gcc.gnu.org/onlinedocs/gc c/Standards.html). Retrieved 2012-06-24.
4. "INCITS/ISO/IEC 9899" (http://www.techstreet.com/cgi-bin/detail?doc_no=incits_iso_iec%7 C9899;product_id=232462). www.techstreet.com. Retrieved 2018-10-03.
5. "ISO/IEC 9899:1990 - Programming Languages -- C" (http://www.iso.org/iso/iso_catalogue/c atalogue_ics/catalogue_detail_ics.htm?csnumber=17782). Retrieved 2012-06-24.
6. Clive D.W. Feather (2010-09-12). "A brief description of Normative Addendum 1" (http://ww w.lysator.liu.se/c/na1.html).
7. "ISO/IEC 9899:1990/Amd 1:1995" (https://www.iso.org/standard/23909.html). International Organization for Standardization. 2013-03-22.
8. "GNU GCC 15.2 Manual" (https://gcc.gnu.org/onlinedocs/gcc-15.2.0/gcc/Standards.html#C- Language). Free Software Foundation. 2025.
9. "ISO/IEC 9899:1990/Cor 1:1994" (http://www.iso.org/cms/render/live/en/sites/isoorg/content s/data/standard/02/42/24271.html). ISO. Retrieved 2019-01-21.
10. "ISO/IEC 9899:1990/Cor 2:1996" (http://www.iso.org/cms/render/live/en/sites/isoorg/content s/data/standard/02/71/27110.html). ISO. Retrieved 2019-01-21.
11. "ISO/IEC 9899:1999" (http://www.iso.org/cms/render/live/en/sites/isoorg/contents/data/stand ard/02/92/29237.html). ISO. Retrieved 2019-01-21.
12. "INCITS/ISO/IEC 9899-2012" (https://webstore.ansi.org/Standards/INCITS/INCITSISOIEC9 8992012). ANSI.
13. "ISO/IEC 9899:1999 - Programming Languages -- C" (https://www.iso.org/standard/29237.ht ml). Retrieved 2012-06-24.
14. "ISO/IEC 9899:2011/Cor 1:2012" (https://www.iso.org/standard/61717.html). International Organization for Standardization.

15. "ISO/IEC 9899:2018 - Information technology -- Programming languages -- C" (https://www.i so.org/standard/74528.html). www.iso.org.
16. "The Standard - C" (http://www.iso-9899.info/wiki/The_Standard). www.iso-9899.info.
17. "ISO/IEC 9899:2024 - Information technology - Programming languages - C" (https://ww w.iso.org/standard/82075.html).
18. "ISO/IEC TR 19769:2004" (https://www.iso.org/standard/33907.html). International Organization for Standardization.
19. "ISO/IEC TR 24731-1:2007" (https://www.iso.org/standard/38841.html). International Organization for Standardization.
20. "ISO/IEC TR 18037:2008" (https://www.iso.org/standard/51126.html). International Organization for Standardization.
21. "ISO/IEC TR 24732:2009" (https://www.iso.org/standard/38842.html). International Organization for Standardization.
22. "ISO/IEC TR 24747:2009" (https://www.iso.org/standard/38857.html). International Organization for Standardization.
23. "ISO/IEC TR 24731-2:2010" (https://www.iso.org/standard/51678.html). International Organization for Standardization.
24. "ISO/IEC TS 17961:2013" (https://www.iso.org/standard/61134.html). International Organization for Standardization.
25. "ISO/IEC TS 18661-1:2014" (https://www.iso.org/standard/63146.html). International Organization for Standardization.
26. "ISO/IEC TS 18661-2:2015" (https://www.iso.org/standard/68882.html). International Organization for Standardization.
27. "ISO/IEC TS 18661-3:2015" (https://www.iso.org/standard/65615.html). International Organization for Standardization.
28. "ISO/IEC TS 18661-4:2015" (https://www.iso.org/standard/65616.html). International Organization for Standardization.
29. "Experimental C features" (https://en.cppreference.com/w/c/experimental).
cppreference.com. Retrieved 16 January 2016.
30. "2 Language Standards Supported by GCC - 2.1 C Language" (https://gcc.gnu.org/onlinedo cs/gcc-8.2.0/gcc/Standards.html#C-Language). Using the GNU Compiler Collection (GCC). GCC, the GNU Compiler Collection. Retrieved 2019-02-05.
31. "Language Compatibility" (https://clang.llvm.org/compatibility.html#c). Clang C Language Family Frontend for LLVM. Retrieved 2019-02-05.
32. "Standard predefined macro names" (https://www.ibm.com/support/knowledgecenter/SSPS QF_9.0.0/com.ibm.xlcpp111.aix.doc/language_ref/cplr367.html). www.ibm.com. Retrieved 2019-04-10.
33. "HP C/ANSI C developer's bundle" (https://www.hp.com/go/c). Retrieved 2015-07-12.
34. Support for ISO C11 added to IBM XL C/C++ compilers (https://www.ibm.com/developerwor ks/rational/library/support-iso-c11/index.html)
35. link to Pelles C pages (http://www.smorgasbordet.com/pellesc/)

Further reading


Schreiner, Axel-Tobias (1993). Object Oriented Programming with ANSI-C. Hanser. ISBN 3- 446-17426-5.

External links


ISO C working group (http://www.open-std.org/jtc1/sc22/wg14/)
Draft ANSI C Standard (ANSI X3J11/88-090) (https://web.archive.org/web/2016122312533 9/http://flash-gordon.me.uk/ansi.c.txt) (May 13, 1988), Third Public Review (https://groups.g oogle.com/group/comp.lang.c/msg/20b174b18cdd919d?hl=en)
Draft ANSI C Rationale (ANSI X3J11/88-151) (https://docs.google.com/file/d/0BxVCLS4f8Sg 5NWZmM2NjZWEtYmExMS00Y2EzLWE3ZTMtNzFmYjYwYzBiOTIw/view) (Nov 18, 1988)
C Information Bulletin #1 (ANSI X3J11/93-007) (https://docs.google.com/file/d/0B-3PfyBhOS OxOTdjYmM1N2ItMmE0ZC00OGE3LTllODUtZDNkMDMzYWU3NDlk/view) (May 27, 1992)
ANSI C Yacc grammar (http://www.quut.com/c/ANSI-C-grammar-y.html)
ANSI C grammar, Lex specification (http://www.lysator.liu.se/c/ANSI-C-grammar-l.html)

Retrieved from "https://en.wikipedia.org/w/index.php?title=ANSI_C&oldid=1351013851"

)BOOKTEXT";
