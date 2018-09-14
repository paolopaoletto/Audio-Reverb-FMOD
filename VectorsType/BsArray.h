#pragma once

#include "BsCorePrerequisites.h"

namespace bs 
{
	template <class Type>
	class Array
	{
	public:
		typedef Type ValueType;
		typedef ValueType* Ptr;
		typedef const ValueType* ConstPtr;
		typedef ValueType& ReferenceType;
		typedef const ValueType& ConstReferenceType;
		typedef std::size_t SizeType;
		typedef std::ptrdiff_t DifferenceType;

		Array();
		Array(const Array& other);
		Array(UINT32 reserve);
		~Array();

		bool operator==(const Array<ValueType>& other) const;
		bool operator!=(const Array<ValueType>& other) const;

		ReferenceType operator[] (UINT32 index);
		ConstReferenceType operator[] (UINT32 index) const;

		Ptr addressOf();
		ConstPtr addressOf() const;

		void alloc(UINT32 elements, bool data);
		void smallAlloc(UINT32 elements, bool data);

		UINT32 getCapacity() const;

		void add(const ConstReferenceType element);
		ValueType pop();

		bool setLength(UINT32 element);
		bool setSmallLength(UINT32 element);
		UINT32 getLength() const;

		bool exists(ConstReferenceType element) const;
		UINT32 indexElement(ConstReferenceType element) const;

		void removeIndex(UINT32 index);
		void removeValue(ConstReferenceType element);

	private:
		ValueType* arr = nullptr;
		UINT32 length = 0;
		UINT32 maxLength = 0;
		char buffer[16];
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
		delete[] arr;
	}

	template <class Type>
	typename Array<Type>::ReferenceType Array<Type>::operator[] (UINT32 index)
	{
		return arr[index];
	}

	template <class Type>
	typename Array<Type>::ConstReferenceType Array<Type>::operator[] (UINT32 index) const
	{
		return arr[index];
	}


	template <class Type>
	bool Array<Type>::operator== (const Array<Type>& other) const
	{
		if (length != other.length)
		{
			return false;
		}

		for (UINT32 i = 0; i < length; i++)
		{
			if (arr[i] != other.arr[i])
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
	typename Array<Type>::Ptr Array<Type>::addressOf()
	{
		return arr;
	}

	template <class Type>
	typename Array<Type>::ConstPtr Array<Type>::addressOf() const
	{
		return arr;
	}

	template <class Type>
	void Array<Type>::add(typename Array<Type>::ConstReferenceType element)
	{
		if (length == maxLength)
		{
			if (maxLength == 0)
			{
				alloc(1, false);
			}
			else
			{
				alloc(2 * maxLength, true);
			}

			if (length == maxLength)
			{
				return;
			}
		}

		arr[length++] = element;
	}

	template <class Type>
	typename Array<Type>::ValueType Array<Type>::pop()
	{
		return arr[--length];
	}

	template <class Type>
	void Array<Type>::alloc(UINT32 elements, bool data)
	{
		Type* tmp = nullptr;

		if (elements)
		{
			if (sizeof(Type) * elements <= sizeof(buffer))
			{
				tmp = reinterpret_cast<Type*>(buffer);
			}
			else
			{
				tmp = new Type[sizeof(Type) * elements];

				if (tmp == 0)
				{
					return;
				}
			}

			if (arr == tmp)
			{

				for (UINT32 i = length; i < elements; i++)
				{
					new (&tmp[i]) Type();
				}
			}
			else
			{

				for (UINT32 i = 0; i < elements; i++)
				{
					new (&tmp[i]) Type();
				}
			}
		}

		if (arr)
		{
			const UINT32 oldLength = length;

			if (arr == tmp)
			{
				if (data)
				{
					if (length > elements)
					{
						length = elements;
					}
				}
				else
				{
					length = 0;
				}

				for (UINT32 i = length; i < oldLength; i++)
				{
					arr[i].~Type();
				}
			}
			else
			{
				if (data)
				{
					if (length > elements)
					{
						length = elements;
					}

					for (UINT32 i = 0; i < length; i++)
					{
						tmp[i] = arr[i];
					}
				}
				else
				{
					length = 0;
				}

				for (UINT32 i = 0; i < oldLength; i++)
				{
					arr[i].~Type();
				}

				if (arr != reinterpret_cast<Type*>(buffer))
				{
					delete[] arr;
				}
			}
		}

		arr = tmp;
		maxLength = elements;
	}

	template <class Type>
	void Array<Type>::smallAlloc(UINT32 numElements, bool data)
	{
		Type* tmp = nullptr;

		if (elements)
		{
			if (sizeof(Type) * elements <= sizeof(buffer))
			{
				tmp = reinterpret_cast<Type*>(buffer);
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

		if (arr)
		{
			if (arr == tmp)
			{
				if (data)
				{
					if (length > elements)
					{
						length = elements;
					}
				}
				else
				{
					length = 0;
				}
			}
			else
			{
				if (data)
				{
					if (length > elements)
					{
						length = elements;
					}

					memcpy(tmp, arr, sizeof(Type) * length);
				}
				else
				{
					length = 0;
				}

				if (arr != reINT32erpret_cast<Type*>(buffer))
				{
					delete[] arr;
				}
			}
		}

		arr = tmp;
		maxLength = elements;
	}

	template <class Type>
	UINT32 Array<Type>::getCapacity() const
	{
		return maxLength;
	}

	template <class Type>
	bool Array<Type>::setLength(UINT32 element)
	{
		if (elements > maxLength)
		{
			alloc(elements, true);

			if (elements > maxLength)
			{
				return false;
			}
		}

		length = elements;

		return true;
	}

	template <class Type>
	bool Array<Type>::setSmallLength(UINT32 elements)
	{
		if (elements > maxLength)
		{
			smallAlloc(elements, true);

			if (elements > maxLength)
			{
				return false;
			}
		}

		length = elements;

		return true;
	}

	template <class Type>
	UINT32 Array<Type>::getLength() const
	{
		return length;
	}

	template <class Type>
	bool Array<Type>::exists(typename Array<Type>::ConstReferenceType element) const
	{
		return indexElement(element) == -1 ? false : true;
	}

	template <class Type>
	INT32 Array<Type>::indexElement(typename Array<Type>::ConstReferenceType element) const
	{
		for (UINT32 i = 0; i < length; i++)
		{
			if (arr[i] == element)
			{
				return static_cast<INT32>(i);
			}
		}

		return -1;
	}

	template <class Type>
	void Array<Type>::removeIndex(UINT32 index)
	{
		if (index < length)
		{
			for (UINT32 i = index; i < length - 1; i++)
			{
				arr[i] = arr[i + 1];
			}

			pop();
		}
	}

	template <class Type>
	void Array<Type>::removeValue(typename Array<Type>::ConstReferenceType element)
	{
		for (UINT32 i = 0; i < length; i++)
		{
			if (arr[i] == element)
			{
				removeIndex(i);
				break;
			}
		}
	}
}
