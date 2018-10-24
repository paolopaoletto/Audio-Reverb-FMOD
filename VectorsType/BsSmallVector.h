#pragma once

#include "Prerequisites/BsPrerequisitesUtil.h"

namespace bs
{
	template <UINT32 N, class Type>
	class BsSmallVector final
	{
	public:
		typedef Type ValueType;
		typedef Type* Iterator;
		typedef const Type* ConstIterator;
		typedef std::reverse_iterator<Type*> ReverseIterator;
		typedef std::reverse_iterator<const Type*> ConstReverseIterator;

		typename std::aligned_storage<sizeof(Type), alignof(Type)>::type storage[N];

		BsSmallVector() {}

		BsSmallVector(const BsSmallVector<N, ValueType>& other)
		{
			*this = other;
		}

		BsSmallVector(UINT32 sz)
		{
			realloc(sz, false);
		}

		~BsSmallVector()
		{
			realloc(0, false);
		}

		BsSmallVector<N, ValueType>& operator= (const BsSmallVector<N, ValueType>& other)
		{
			if (mMaxSize < other.mMaxSize)
			{
				mMaxSize = other.mMaxSize << 2;
				realloc(mMaxSize, false);
			}

			for (UINT32 i = 0; i < other.mSize; ++i)
			{
				mArr[i] = other.mArr[i];
			}

			mSize = other.mSize;
		}

		BsSmallVector<N, ValueType>& operator= (BsSmallVector<N, ValueType>&& other)
		{
			if (mMaxSize < other.mMaxSize)
			{
				mMaxSize = other.mMaxSize << 2;
				realloc(mMaxSize, false);
			}

			for (UINT32 i = 0; i < other.mSize; ++i)
			{
				mArr[i] = std::move(other.mArr[i]);
			}

			mSize = other.mSize;
		}

		bool operator== (const BsSmallVector<N, ValueType>& other)
		{
			if (mSize != other.mSize)
				return false;

			for (UINT32 i = 0; i < mSize; ++i)
			{
				if (mArr[i] != other.mArr[i])
					return false;
			}

			return true;
		}

		bool operator!= (const BsSmallVector<N, ValueType>& other)
		{
			if (mSize != other.mSize)
				return true;

			for (UINT32 i = 0; i < mSize; ++i)
			{
				if (mArr[i] != other.mArr[i])
					return true;
			}

			return false;
		}

		bool operator< (const BsSmallVector<N, ValueType>& other) const
		{
			UINT32 lenght = mSize < other.mSize ? mSize : other.mSize;

			for (UINT32 i = 0; i < lenght; ++i)
			{
				if (mArr[i] != other.mArr[i])
					return mArr[i] < other.mArr[i];
			}

			return mSize < other.mSize;
		}

		bool operator<= (const BsSmallVector<N, ValueType>& other) const
		{
			UINT32 length = mSize < other.mSize ? mSize : other.mSize;

			for (UINT32 i = 0; i < length; ++i)
			{
				if (mArr[i] != other.mArr[i])
					return mArr[i] < other.mArr[i];
			}

			return mSize <= other.mSize;
		}

		bool operator> (const BsSmallVector<N, ValueType>& other) const
		{
			UINT32 length = mSize < other.mSize ? mSize : other.mSize;

			for (UINT32 i = 0; i < length; ++i)
			{
				if (mArr[i] != other.mArr[i])
					return mArr[i] > other.mArr[i];
			}

			return mSize > other.mSize;
		}

		bool operator>= (const BsSmallVector<N, ValueType>& other) const
		{
			UINT32 length = mSize < other.mSize ? mSize : other.mSize;

			for (UINT32 i = 0; i < length; ++i)
			{
				if (mArr[i] != other.mArr[i])
					return mArr[i] > other.mArr[i];
			}

			return mSize >= other.mSize;
		}

		Type& operator[] (UINT32 index) { return reinterpret_cast<Type*>(storage)[index]; };
		const Type& operator[] (UINT32 index) const { return reinterpret_cast<Type*>(storage)[index]; };

		bool isEmpty() const { return mSize == 0; };

		Iterator begin() { return reinterpret_cast<Type*>(storage); };
		Iterator end() { return reinterpret_cast<Type*>(storage) + mSize; };

		ConstIterator cbegin() const { return reinterpret_cast<Type*>(storage); };
		ConstIterator cend() const { return reinterpret_cast<Type*>(storage) + mSize; };

		ReverseIterator rbegin() { ReverseIterator(begin()); };
		ReverseIterator rend() { ReverseIterator(end()); };

		ConstReverseIterator crbegin() const { ReverseIterator(begin()); };
		ConstReverseIterator crend() const { ReverseIterator(end()); };

		UINT32 size() { return mSize; };
		UINT32 capacity() { return mMaxSize; }

		Type* data() { return mArr; }
		const Type* data() const { return mArr; }

		Type* front() { return reinterpret_cast<Type*>(storage)[0]; };
		Type* back() { return reinterpret_cast<Type*>(storage)[mSize - 1]; };

		const Type* front() const { reinterpret_cast<Type*>(storage)[0]; };
		const Type* back() const { reinterpret_cast<Type*>(storage)[mSize - 1]; };

		void add(const Type& element)
		{
			if (mSize == mMaxSize)
			{
				if (mMaxSize == 0)
				{
					realloc(1, false);
				}
				else
				{
					realloc(2 * mMaxSize, true);
				}

				if (mSize == mMaxSize)
				{
					return;
				}
			}

			mArr[mSize++] = element;
		}

		void add(Type&& element)
		{
			if (mSize == mMaxSize)
			{
				if (mMaxSize == 0)
				{
					realloc(1, false);
				}
				else
				{
					realloc(2 * mMaxSize, true);
				}

				if (mSize == mMaxSize)
				{
					return;
				}
			}

			mArr[mSize++] = std::move(element);
		}

		void pop()
		{
			return mArr[--mSize];
		}

		void remove(int index)
		{
			if (index < mSize)
			{
				for (UINT32 i = index; i < mSize - 1; i++)
				{
					mArr[i] = mArr[i + 1];
				}

				pop();
			}
		}

		bool contains(const Type& element)
		{
			for (UINT32 i = 0; i < mSize; i++)
			{
				if (mArr[i] == element)
					return true;
			}

			return false;
		}

		void removeValue(const Type& element)
		{
			for (UINT32 i = 0; i < mSize; i++)
			{
				if (mArr[i] == element)
				{
					remove(i);
					break;
				}
			}
		}

		void clear()
		{
			for (UINT32 i = 0; i < mSize; ++i)
			{
				mArr[i].~Type();
			}

			mSize = 0;
		}

		void reserve(UINT32 sz, bool c)
		{
			if (sz > mMaxSize)
			{
				if (sz > mMaxSize)
				{
					return;
				}

				if (c)
				{
					realloc(sz, true);
				}
				else
				{
					reallocNoConstruct(sz, true);
				}
			}

			mSize = sz;
		}

	private:
		void realloc(UINT32 elements, bool data)
		{
			Type* tmp = 0;

			if (elements)
			{
				if (sizeof(Type) * elements <= sizeof(storage))
				{
					// It uses the internal storage.
					tmp = reinterpret_cast<Type*>(storage);
				}
				else
				{
					// Allocate the elements.
					tmp = bs_allocN<Type>(elements);

					if (tmp == 0)
					{
						// Out of memory.
						return;
					}
				}

				if (mArr == tmp)
				{
					// Construct only the newly allocated elements.
					for (UINT32 i = mSize; i < elements; i++)
					{
						new (&tmp[i]) Type();
					}
				}
				else
				{
					// Construct all elements.
					for (UINT32 i = 0; i < elements; i++)
					{
						new (&tmp[i]) Type();
					}
				}
			}

			if (mArr)
			{
				const unsigned oldSize = mSize;
				if (mArr == tmp)
				{
					if (data)
					{
						if (mSize > elements)
						{
							mSize = elements;
						}
					}
					else
					{
						mSize = 0;
					}

					// Destruct the elements that are no longer used in the array.
					for (UINT32 i = mSize; i < oldSize; i++)
					{
						mArr[i].~Type();
					}
				}
				else
				{
					if (data)
					{
						if (mSize > elements)
						{
							mSize = elements;
						}

						for (UINT32 i = 0; i < mSize; i++)
						{
							tmp[i] = mArr[i];
						}
					}
					else
					{
						mSize = 0;
					}

					// Destruct all the elements.
					for (UINT32 i = 0; i < oldSize; i++)
					{
						mArr[i].~Type();
					}

					if (mArr != reinterpret_cast<Type*>(storage))
					{
						bs_free(mArr);
					}
				}
			}

			mArr = tmp;
			mMaxSize = elements;
		}

		void reallocNoConstruct(UINT32 elements, bool data)
		{
			Type* tmp = 0;

			if (elements)
			{
				if (sizeof(Type) * elements <= sizeof(storage))
				{
					tmp = reinterpret_cast<Type*>(storage);
				}
				else
				{
					tmp = bs_allocN<Type>(elements);

					if (tmp == 0)
					{
						return;
					}
				}
			}

			if (mArr)
			{
				if (mArr == tmp)
				{
					if (data)
					{
						if (mSize > elements)
						{
							mSize = elements;
						}
					}
					else
					{
						mSize = 0;
					}
				}
				else
				{
					if (data)
					{
						if (mSize > elements)
						{
							mSize = elements;
						}

						memcpy(tmp, mArr, sizeof(Type) * mArr);
					}
					else
					{
						mSize = 0;
					}

					if (mArr != reinterpret_cast<Type*>(storage))
					{
						bs_free(mArr);
					}
				}
			}

			mArr = tmp;
			mMaxSize = elements;
		}

		Type* mArr = nullptr;
		UINT32 mSize = 0;
		UINT32 mMaxSize = 0;
	};
}