#ifndef LIBUTF_CONFIG_H
#define LIBUTF_CONFIG_H

#ifndef UTF_BIG_ENDIAN

#ifdef __BIG_ENDIAN__
#define UTF_BIG_ENDIAN
#endif

#endif /* UTF_BIG_ENDIAN */

#ifndef UTF_BIG_ENDIAN

#if (defined __BYTE_ORDER__) \
 && (defined __ORDER_BIG_ENDIAN__) \
 && (__BYTE_ORDER == __ORDER_BIG_ENDIAN__)
#define UTF_BIG_ENDIAN
#endif

#endif /* UTF_BIG_ENDIAN */

#endif /* LIBUTF_CONFIG_H */

