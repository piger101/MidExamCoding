# MidExamCoding
This is a coding question from ZJU’s midterm C programming exam.

Key Points Tested
1. Integer representation & bit-level thinking

Two’s complement: negative numbers, sign bit, why signed values break unsigned comparisons
IEEE 754 float encoding: sign bit / exponent / mantissa layout
Interpreting the same 32 bits as different types (int / pointer / string / float)

2. Bitwise operations
Masking (&0x7fffffff) to extract bit fields
Shift behavior: arithmetic shift on negatives (sign extension) vs logical shift
Operator precedence pitfalls (>> binds tighter than &)
Range checks on extracted bit fields

3. C language basics
Operator precedence and explicit parentheses
Reading pre-written skeleton code and filling exact gaps
Constraints: one-line answers, semicolon limits

5. Logic & quantifiers
Distinguishing “exists i” (∃) vs “for all i” (∀) conditions
Nested loops with early termination (break, flags like has_bad_number)
Priority/ordering of multiple checks and early return
5. Edge-case reasoning

Boundary values (2¹⁶, 2²⁰, 2²³, endpoints 120/134)
Cross-checking different variables (a[i] vs a[j])
Preventing overflow in subtraction (signed arithmetic)

6. Memory interpretation mindset
Understanding that memory content is type-agnostic — the whole problem is about recognizing “what type does this bit pattern look like,” a core systems-programming skill (pointer analysis, string detection, float exponent ranges)
In short: bit manipulation + data representation + careful logic + edge cases.
