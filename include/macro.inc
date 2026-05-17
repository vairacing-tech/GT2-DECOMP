.include "gte_macros.s"

.macro glabel label
    .global \label
    .type \label, @function
    \label:
.endm

.macro dlabel label
    .global \label
    \label:
.endm

.macro jlabel label
    .global \label
    \label:
.endm

.macro move a, b
    addu \a, \b, $zero
.endm

# Marker emitted by newer splat-generated nonmatching assembly.
# Keep it as metadata only so older include-asm flows remain buildable.
.macro nonmatching label, size=1
    .global \label\().NON_MATCHING
    .type \label\().NON_MATCHING, @object
    .size \label\().NON_MATCHING, \size
    \label\().NON_MATCHING:
.endm

# End marker emitted for data symbols by newer splat/spimdisasm output.
.macro enddlabel label
    .size \label, . - \label
.endm
