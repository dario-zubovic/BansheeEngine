//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

namespace BansheeEngine
{
	/** @addtogroup General
	 *  @{
	 */

	/** Wrapper around an enum that allows simple use of bitwise logic operations. */
	template<typename Enum, typename Storage = UINT32>
	class Flags
	{
	public:
		typedef Storage InternalType;

		Flags()
			:mBits(0)
		{ }
					
		Flags(Enum value)
		{
			mBits = static_cast<Storage>(value);
		}

		Flags(const Flags<Enum, Storage>& value)
		{
			mBits = value.mBits;
		}

		explicit Flags(Storage bits)
		{
			mBits = bits;
		}

		/** Checks whether all of the provided bits are set */
		bool isSet(Enum value) const
		{
			return (mBits & static_cast<Storage>(value)) == static_cast<Storage>(value);
		}

		/** Activates all of the provided bits. */
		Flags<Enum, Storage>& set(Enum value)
		{
			mBits = static_cast<Storage>(value);

			return *this;
		}

		/** Deactivates all of the provided bits. */
		void unset(Enum value)
		{
			mBits &= ~static_cast<Storage>(value);
		}

		bool operator==(Enum rhs) const
		{
			return mBits == static_cast<Storage>(rhs);
		}

		bool operator==(const Flags<Enum, Storage>& rhs) const
		{
			return mBits == rhs.mBits;
		}

		bool operator==(bool rhs) const
		{
			return ((bool)*this) == rhs;
		}

		bool operator!=(Enum rhs) const
		{
			return mBits != static_cast<Storage>(rhs);
		}

		bool operator!=(const Flags<Enum, Storage>& rhs) const
		{
			return mBits != rhs.mBits;
		}

		Flags<Enum, Storage>& operator= (Enum rhs)
		{
			mBits = static_cast<Storage>(rhs);

			return *this;
		}

		Flags<Enum, Storage>& operator= (const Flags<Enum, Storage>& rhs)
		{
			mBits = rhs.mBits;

			return *this;
		}

		Flags<Enum, Storage>& operator|= (Enum rhs)
		{
			mBits |= static_cast<Storage>(rhs);

			return *this;
		}

		Flags<Enum, Storage>& operator|= (const Flags<Enum, Storage>& rhs)
		{
			mBits |= rhs.mBits;

			return *this;
		}

		Flags<Enum, Storage> operator| (Enum rhs) const
		{
			Flags<Enum, Storage> out(*this);
			out |= rhs;

			return out;
		}

		Flags<Enum, Storage> operator| (const Flags<Enum, Storage>& rhs) const
		{
			Flags<Enum, Storage> out(*this);
			out |= rhs;

			return out;
		}

		Flags<Enum, Storage>& operator&= (Enum rhs)
		{
			mBits &= static_cast<Storage>(rhs);

			return *this;
		}

		Flags<Enum, Storage>& operator&= (const Flags<Enum, Storage>& rhs)
		{
			mBits &= rhs.mBits;

			return *this;
		}

		Flags<Enum, Storage> operator& (Enum rhs) const
		{
			Flags<Enum, Storage> out = *this;
			out.mBits &= static_cast<Storage>(rhs);

			return out;
		}

		Flags<Enum, Storage> operator& (const Flags<Enum, Storage>& rhs) const
		{
			Flags<Enum, Storage> out = *this;
			out.mBits &= rhs.mBits;

			return out;
		}

		Flags<Enum, Storage>& operator^= (Enum rhs)
		{
			mBits ^= static_cast<Storage>(rhs);

			return *this;
		}

		Flags<Enum, Storage>& operator^= (const Flags<Enum, Storage>& rhs)
		{
			mBits ^= rhs.mBits;

			return *this;
		}

		Flags<Enum, Storage> operator^ (Enum rhs) const
		{
			Flags<Enum, Storage> out = *this;
			out.mBits ^= static_cast<Storage>(rhs);

			return out;
		}

		Flags<Enum, Storage> operator^ (const Flags<Enum, Storage>& rhs) const
		{
			Flags<Enum, Storage> out = *this;
			out.mBits ^= rhs.mBits;

			return out;
		}

		Flags<Enum, Storage> operator~ () const
		{
			Flags<Enum, Storage> out;
			out.mBits = (Storage)~mBits;

			return out;
		}

		operator bool() const
		{
			return mBits ? true : false;
		}

		operator UINT8() const
		{
			return static_cast<UINT8>(mBits);
		}

		operator UINT16() const
		{
			return static_cast<UINT16>(mBits);
		}

		operator UINT32() const
		{
			return static_cast<UINT32>(mBits);
		}

		friend Flags<Enum, Storage> operator&(Enum a, Flags<Enum, Storage> &b)
		{
			Flags<Enum, Storage> out;
			out.mBits = a & b.mBits;
			return out;
		}

	private:
		Storage mBits;
	};

/** Defines global operators for a Flags<Enum, Storage> implementation. */
#define BS_FLAGS_OPERATORS(Enum) BS_FLAGS_OPERATORS_EXT(Enum, UINT32)

/** Defines global operators for a Flags<Enum, Storage> implementation. */
#define BS_FLAGS_OPERATORS_EXT(Enum, Storage)																   \
		inline Flags<Enum, Storage> operator|(Enum a, Enum b) { Flags<Enum, Storage> r(a); r |= b; return r; } \
		inline Flags<Enum, Storage> operator&(Enum a, Enum b) { Flags<Enum, Storage> r(a); r &= b; return r; } \
		inline Flags<Enum, Storage> operator~(Enum a) { return ~Flags<Enum, Storage>(a); }

	/** @cond SPECIALIZATIONS */

	/**
	 * RTTIPlainType for Flags.
	 * 			
	 * @see		RTTIPlainType
	 */
	template<class Enum, class Storage> struct RTTIPlainType<Flags<Enum, Storage>>
	{	
		enum { id = TID_Flags }; enum { hasDynamicSize = 0 };

		/** @copydoc RTTIPlainType::toMemory */
		static void toMemory(const Flags<Enum, Storage>& data, char* memory)
		{ 
			Storage storageData = (Storage)data;
			RTTIPlainType<Storage>::toMemory(storageData, memory);
		}

		/** @copydoc RTTIPlainType::fromMemory */
		static UINT32 fromMemory(Flags<Enum, Storage>& data, char* memory)
		{ 
			Storage storageData;
			RTTIPlainType<Storage>::fromMemory(storageData, memory);

			data = Flags<Enum, Storage>(storageData);
			return sizeof(Flags<Enum, Storage>);
		}

		/** @copydoc RTTIPlainType::getDynamicSize */
		static UINT32 getDynamicSize(const Flags<Enum, Storage>& data)
		{ 
			assert(false);
			return sizeof(Flags<Enum, Storage>);
		}	
	}; 

	/** @endcond */
	/** @} */
}
