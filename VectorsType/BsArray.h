#pragma once

#include "Prerequisites/BsPrerequisitesUtil.h"

namespace bs 
{
	template <class Type>
	class Array
	{
	public:
		typedef Type ValueType;

		Array();
		Array(const Array& other);
		Array(UINT32 reserve);
		~Array();

		bool operator==(const Array<ValueType>& other) const;
		bool operator!=(const Array<ValueType>& other) const;

		Type& operator[] (UINT32 index);
		const Type& operator[] (UINT32 index) const;

		Type* address();
		const Type* address() const;

		void alloc(UINT32 elements, bool data);
		void smallAlloc(UINT32 elements, bool data);

		UINT32 getCapacity() const;

		void add(const Type& element);
		ValueType pop();

		bool setLength(UINT32 element);
		bool setSmallLength(UINT32 element);
		UINT32 getLength() const;

		bool exists(const Type& element) const;
		int indexElement(const Type& element) const;

		void removeIndex(UINT32 index);
		void removeValue(const Type& element);

	private:
		ValueType* mArr = nullptr;
		UINT32 mLength = 0;
		UINT32 mMaxLength = 0;
		char mBuffer[16];
	};

	template <class Type>
	Array<Type>::Array() { }

	template <class Type>
	Array<Type>::Array(const Array<Type>& other)
	{
		*this = other;
	}

	template <class Type>
	Array<Type>::Array(UINT32 reserve)
	{
		alloc(reserve, false);
	}

	template <class Type>
	Array<Type>::~Array()
	{
		delete[] mArr;
	}

	template <class Type>
	Type& Array<Type>::operator[] (UINT32 index)
	{
		return mArr[index];
	}

	template <class Type>
	const Type& Array<Type>::operator[] (UINT32 index) const
	{
		return mArr[index];
	}


	template <class Type>
	bool Array<Type>::operator== (const Array<Type>& other) const
	{
		if (mLength != other.mLength)
		{
			return false;
		}

		for (UINT32 i = 0; i < mLength; i++)
		{
			if (mArr[i] != other.mArr[i])
			{
				return false;
			}
		}

		return true;
	}

	template <class Type>
	bool Array<Type>::operator!= (const Array<Type>& other) const
	{
		return !(*this == other);
	}

	template <class Type>
	Type* Array<Type>::address()
	{
		return mArr;
	}

	template <class Type>
	const Type* Array<Type>::address() const
	{
		return mArr;
	}

	template <class Type>
	void Array<Type>::add(const Type& element)
	{
		if (mLength == mMaxLength)
		{
			if (mMaxLength == 0)
			{
				alloc(1, false);
			}
			else
			{
				alloc(2 * mMaxLength, true);
			}

			if (mLength == mMaxLength)
			{
				return;
			}
		}

		mArr[mLength++] = element;
	}

	template <class Type>
	typename Array<Type>::ValueType Array<Type>::pop()
	{
		return mArr[--mLength];
	}

	template <class Type>
	void Array<Type>::alloc(UINT32 elements, bool data)
	{
		Type* tmp = 0;

		if (elements)
		{
			if (sizeof(Type)*elements <= sizeof(mBuffer))
			{
				tmp = reinterpret_cast<Type*>(mBuffer);
			}
			else
			{
				tmp = new Type[sizeof(Type) * elements];

				if (tmp == 0)
				{
					return;
				}
			}

			if (mArr == tmp)
			{

				for (UINT32 i = mLength; i < elements; i++)
				{
					new (&tmp[i]) Type();
				}
			}
			else
			{

				for (UINT32 n = 0; n < elements; n++)
				{
					new (&tmp[i]) Type();
				}
			}
		}

		if (mArr)
		{
			const UINT32 oldLength = mLength;

			if (mArr == tmp)
			{
				if (data)
				{
					if (mLength > elements)
					{
						mLength = elements;
					}
				}
				else
				{
					mLength = 0;
				}

				for (UINT32 i = mLength; i < oldLength; i++)
				{
					mArr[i].~Type();
				}
			}
			else
			{
				if (data)
				{
					if (mLength > elements)
					{
						mLength = elements;
					}

					for (UINT32 i = 0; i < mLength; i++)
					{
						tmp[i] = mArr[i];
					}
				}
				else
				{
					mLength = 0;
				}

				for (UINT32 i = 0; i < oldLength; i++)
				{
					mArr[i].~Type();
				}

				if (mArr != reinterpret_cast<Type*>(mBuffer))
				{
					delete[] mArr;
				}
			}
		}

		mArr = tmp;
		mMaxLength = elements;
	}

	template <class Type>
	void Array<Type>::smallAlloc(UINT32 numElements, bool keepData)
	{
		Type* tmp = 0;

		if (elements)
		{
			if (sizeof(Type) * elements <= sizeof(mBuffer))
			{
				tmp = reinterpret_cast<Type*>(mBuffer);
			}
			else
			{
				tmp = new Type[sizeof(Type) * elements];

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
					if (mLength > elements)
					{
						mLength = elements;
					}
				}
				else
				{
					mLength = 0;
				}
			}
			else
			{
				if (data)
				{
					if (mLength > elements)
					{
						mLength = elements;
					}

					memcpy(tmp, mArr, sizeof(Type) * mLength);
				}
				else
				{
					mLength = 0;
				}

				if (mArr != reinterpret_cast<Type*>(mBuffer))
				{
					delete[] mArr;
				}
			}
		}

		mArr = tmp;
		mMaxLength = elements;
	}

	template <class Type>
	UINT32 Array<Type>::getCapacity() const
	{
		return mMaxLength;
	}

	template <class Type>
	bool Array<Type>::setLength(UINT32 element)
	{
		if (elements > mMaxLength)
		{
			alloc(elements, true);

			if (elements > mMaxLength)
			{
				return false;
			}
		}

		mLength = element;

		return true;
	}

	template <class Type>
	bool Array<Type>::setSmallLength(UINT32 elements)
	{
		if (elements > mMaxLength)
		{
			smallAlloc(elements, true);

			if (elements > mMaxLength)
			{
				return false;
			}
		}

		mLength = elements;

		return true;
	}

	template <class Type>
	UINT32 Array<Type>::getLength() const
	{
		return mLength;
	}

	template <class Type>
	bool Array<Type>::exists(const Type& element) const
	{
		return indexElement(element) == -1 ? false : true;
	}

	template <class Type>
	int Array<Type>::indexElement(const Type& element) const
	{
		for (UINT32 i = 0; i < mLength; i++)
		{
			if (mArr[i] == element)
			{
				return static_cast<int>(i);
			}
		}

		return -1;
	}

	template <class Type>
	void Array<Type>::removeIndex(UINT32 index)
	{
		if (index < mLength)
		{
			for (UINT32 i = index; i < mLength - 1; i++)
			{
				mArr[i] = mArr[i + 1];
			}

			pop();
		}
	}

	template <class Type>
	void Array<Type>::removeValue(const Type& element)
	{
		for (UINT32 i = 0; i < mLength; i++)
		{
			if (mArr[i] == element)
			{
				removeIndex(i);
				break;
			}
		}
	}
}
