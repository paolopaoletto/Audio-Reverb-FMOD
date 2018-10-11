#pragma once

#include "Prerequisites/BsPrerequisitesUtil.h"
#include "Allocators/BsStaticAlloc.h"

namespace bs
{
	template <class Type, class StaticAllocator = StaticAlloc<>>
	class BsSmallVectorBuffer
	{
	public:
		/** Types */
		typedef Type ValueType;
		typedef Type* Iterator;
		typedef const Type* ConstIterator;
		typedef std::reverse_iterator<Type*> ReverseIterator;
		typedef std::reverse_iterator<const Type*> ConstReverseIterator;

		BsSmallVectorBuffer(UINT32 N)
			: mFirst(reinterpret_cast<Type*>(&firstElement)), mLast(reinterpret_cast<Type*>(&firstElement)),
			mCapacity(reinterpret_cast<Type*>(&firstElement) + N) { }

		~BsSmallVectorBuffer()
		{
			destroyElements(mFirst, mLast);

			deallocateOldElements();
		};

		bool operator== (const BsSmallVectorBuffer& other)
		{
			if (size() != other.size())
				return false;

			const size_t s = size();
			for (Type* tp = mFirst, *tph = other.mFirst, *e = mFirst + s; tp != e; ++tp, ++tph)
			{
				if (*tp != tph)
					return false;
			}

			return true;
		}

		bool operator!= (const BsSmallVectorBuffer& other) { return !(*this == other); }

		Type& operator[] (size_t index) { return mFirst[index]; }
		const Type& operator[] (size_t index) const { return mFirst[index]; }

		bool isEmpty() const { return mFirst == mLast; }

		/** Forward iteration methods. */
		Iterator begin() { return mFirst; }
		Iterator end() { return mLast; }

		/** Constant Forward iteration methods. */
		ConstIterator cbegin() const { return mFirst; }
		ConstIterator cend() const { return mLast; }

		/** Reverse iteration methods. */
		ReverseIterator rbegin() { return ReverseIterator(end()); }
		ReverseIterator rend() { return ReverseIterator(begin()); }

		/** Constant Reverse iteration methods. */
		ConstReverseIterator crbegin() const { return ReverseIterator(end()); }
		ConstReverseIterator crend() const { return ReverseIterator(begin()); }

		/** Return the size of the small vector. */
		size_t size() { return mLast - mFirst; }

		/** Return the front element of the small vector. */
		Type& front() { return mFirst[0]; }

		/** Return the back element of the small vector. */
		Type& back() { return mLast[-1]; }

		/** Return the constant front element of the small vector. */
		const Type& front() const { return mFirst[0]; }

		/** Return the constant back element of the small vector. */
		const Type& back() const { return mLast[-1]; }

		/** Push the element into the small vector. */
		void add(const Type& element)
		{
			if (mLast < mCapacity)
			{
				new (mLast) ValueType(element);
				++mLast;
			}
		}

		/** Pop the element into the small vector. */
		void pop()
		{
			--mLast;
			mLast->~ValueType();
		}

		/** Clear the elements of the small vector. */
		void clear()
		{
			destroyElements(mFirst, mLast);
			mLast = mFirst;
		}

		/** Resize N size allocations into the small vector. */
		void resize(UINT32 N)
		{
			if (N < size())
			{
				destroyElements(mFirst + N, mLast);
				mLast = mFirst + N;
			}
			else if (N > size())
			{
				if (static_cast<UINT32>(mCapacity - mLast) < N)
				{
					grow(N);
				}

				constructElements(mLast, mFirst + N, ValueType());
				mLast = mFirst + N;
			}
		}

		/** Reserve N size allocations into the small vector. */
		void reserve(UINT32 N)
		{
			if (static_cast<UINT32>(mCapacity - mLast) < N)
			{
				grow(N);
			}
		}

		protected:
			/** Determines when the small vector has not had dynamic allocation. */
			bool isSmall() const
			{
				return static_cast<const void*>(mFirst) == static_cast<const void*>(&firstElement);
			}

			void deallocateOldElements()
			{
				if (!isSmall())
				{
					//operator delete(mFirst);
					mStaticAlloc.destruct<Type>(mFirst); // Add New
				}
			}

			/** Construct the elements range. */
			void constructElements(Type* f, Type* l, const Type& element)
			{
				for (; f != l; ++f)
				{
					new (f) ValueType(element);
				}
			}

			/** Destroy the elements range. */
			void destroyElements(Type* f, Type* l)
			{
				while (f != l)
				{
					--l;
					l->~ValueType();
				}
			}

		void grow(size_t min = 0)
		{
			const size_t current = mCapacity - mFirst;
			const size_t size = size();
			size_t newCapacity = current * 2;

			if (newCapacity < min)
			{
				newCapacity = min;
			}

			//Type* newElements = static_cast<Type*>(operator new(newCapacity * sizeof(ValueType)));
			Type* newElements = static_cast<Type*>(mStaticAlloc.construct<Type>(newCapacity * sizeof(ValueType))); // Add Newf

			if (std::is_class<ValueType>::value)
			{
				std::uninitialized_copy(mFirst, mLast, newElements);
			}
			else
			{
				memcpy(newElements, mFirst, size * sizeof(ValueType));
			}

			destroyElements(mFirst, mLast);

			deallocateOldElements();

			mFirst = newElements;
			mLast = newElements + size;
			mCapacity = mFirst + newCapacity;
		}

	protected:
		ValueType* mFirst;
		ValueType* mLast;
		ValueType* mCapacity;
		StaticAlloc<> mStaticAlloc;

		/**
		* Choose which system to use for the space representation.
		*/
#ifdef BS_SMALL_VECTOR_USE_CHAR
		typedef char U;
		U firstElement __declspec(align(16));
#else
		union U
		{
			long long L;
			long double LD;
			double D;
			void* ptr;
		} firstElement;
#endif
	};

	template <UINT32 N, class Type>
	class BsSmallVector final : public BsSmallVectorBuffer<Type>
	{
	public:
		typedef Type ValueType;
	private:
		typedef typename BsSmallVectorBuffer<Type>::U Unit;

		/** The number of the union U require for N template type. */
		static constexpr auto MINUNIT = (static_cast<UINT32>(sizeof(ValueType))*N +
			static_cast<UINT32>(sizeof(Unit)) - 1 /
			static_cast<UINT32>(sizeof(Unit)));

		/** Contains the number of elements of the array. */
		static constexpr auto ELEMENTS = (MINUNIT - 1) > 0 ? (MINUNIT - 1) : 1;

		/** Contains the number of template type that the arrays has space for. */
		static constexpr auto ALLOC = (ELEMENTS + 1)*static_cast<UINT32>(sizeof(Unit)) /
			static_cast<UINT32>(sizeof(ValueType));

		/** Instance of the union U in the small vector buffer. */
		Unit element[ELEMENTS];

	public:
		BsSmallVector() : BsSmallVectorBuffer<ValueType>(ALLOC) { };
		BsSmallVector(size_t size, const Type& value = ValueType())
			: BsSmallVectorBuffer<ValueType>(ALLOC)
		{
			this->reserve(size);
			while (size--)
			{
				add(value);
			}
		}

		~BsSmallVector() = default;
	};
}