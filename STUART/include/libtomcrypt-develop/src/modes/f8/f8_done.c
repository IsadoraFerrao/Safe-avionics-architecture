/* LibTomCrypt, modular cryptographic library -- Tom St Denis
 *
 * LibTomCrypt is a library that provides various cryptographic
 * algorithms in a highly modular and flexible manner.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 */
#include "tomcrypt_private.h"

/**
   @file f8_done.c
   F8 implementation, finish chain, Tom St Denis
*/

#ifdef LTC_F8_MODE

/** Terminate the chain
  @param f8    The F8 chain to terminate
  @return CRYPT_OK on success
*/
int f8_done(symmetric_F8 *f8)
{
   int err;
   LTC_ARGCHK(f8 != NULL);

   if ((err = cipher_is_valid(f8->cipher)) != CRYPT_OK) {
      return err;
   }
   cipher_descriptor[f8->cipher].done(&f8->key);
   return CRYPT_OK;
}



#endif

/* ref:         HEAD -> develop */
/* git commit:  e8afa13d5c19d2757ff56537d34802c1dad2c507 */
/* commit time: 2019-04-10 17:05:59 +0200 */
