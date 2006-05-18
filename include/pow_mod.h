/*************************************************
* Modular Exponentiator Header File              *
* (C) 1999-2006 The Botan Project                *
*************************************************/

#ifndef BOTAN_POWER_MOD_H__
#define BOTAN_POWER_MOD_H__

#include <botan/bigint.h>

namespace Botan {

/*************************************************
* Modular Exponentiator Interface                *
*************************************************/
class Modular_Exponentiator
   {
   public:
      virtual void set_base(const BigInt&) = 0;
      virtual void set_exponent(const BigInt&) = 0;
      virtual BigInt execute() const = 0;
      virtual Modular_Exponentiator* copy() const = 0;
      virtual ~Modular_Exponentiator() {}
   };

/*************************************************
* Modular Exponentiator Proxy                    *
*************************************************/
class Power_Mod
   {
   public:
      enum Usage_Hints {
         NO_HINTS        = 0x0000,

         BASE_IS_FIXED   = 0x0001,
         BASE_IS_SMALL   = 0x0002,
         BASE_IS_LARGE   = 0x0004,
         BASE_IS_2       = 0x0008,

         EXP_IS_FIXED    = 0x0100,
         EXP_IS_SMALL    = 0x0200,
         EXP_IS_LARGE    = 0x0400
      };

      void set_modulus(const BigInt&, Usage_Hints = NO_HINTS) const;
      void set_base(const BigInt&) const;
      void set_exponent(const BigInt&) const;

      BigInt execute() const;

      Power_Mod& operator=(const Power_Mod&);

      Power_Mod(const BigInt& = 0, Usage_Hints = NO_HINTS);
      Power_Mod(const Power_Mod&);
      ~Power_Mod();
   private:
      mutable Modular_Exponentiator* core;
      Usage_Hints hints;
   };

/*************************************************
* Fixed Exponent Modular Exponentiator Proxy     *
*************************************************/
class Fixed_Exponent_Power_Mod : public Power_Mod
   {
   public:
      BigInt operator()(const BigInt& b) const
         { set_base(b); return execute(); }

      Fixed_Exponent_Power_Mod() {}
      Fixed_Exponent_Power_Mod(const BigInt&, const BigInt&,
                               Usage_Hints = NO_HINTS);
   };

/*************************************************
* Fixed Base Modular Exponentiator Proxy         *
*************************************************/
class Fixed_Base_Power_Mod : public Power_Mod
   {
   public:
      BigInt operator()(const BigInt& e) const
         { set_exponent(e); return execute(); }

      Fixed_Base_Power_Mod() {}
      Fixed_Base_Power_Mod(const BigInt&, const BigInt&,
                           Usage_Hints = NO_HINTS);
   };

}

#endif
