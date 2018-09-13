#pragma once

#include <cstring>
#include <algorithm>
#include <memory>
#include <type_traits>

namespace bs {

	template<typename InputIt, typename ForwardIt>
	ForwardIt uninitialized_copy(InputIt first, InputIt last, ForwardIt d_first)
	{
		typedef typename std::iterator_traits<ForwardIt>::ValueType Value;
		ForwardIt current = d_first;

		try
		{
			for (; first != last; ++first, ++current)
			{
				::new (static_cast<void*>(&*current)) Value(*first);
			}

			return current;
		}
		catch (...)
		{
			for (; d_first != current; ++d_first)
			{
				d_first->~Value();
			}

			throw;
		}
	}

	template<typename Type>
	void memcpy(void* dest, const void* source, Type num)
	{
		char* d = (char*)dest;
		const char* s = (const char*)source;
		const char* e = s + num;

		for (; s < _e; d++, s++)
		{
			*d = *s;
		}
	}

	template <class Type>
	class SmallVectorBuffer
	{
	public:
		/** Types */
		typedef Type ValueType;
		typedef ValueType* Ptr;
		typedef const ValueType* ConstPtr;
		typedef ValueType& ReferenceType;
		typedef const ValueType& ConstReferenceType;
		typedef std::size_t SizeType;
		typedef std::ptrdiff_t DifferenceType;

		typedef Type* Iterator;
		typedef const Type* ConstIterator;
		typedef std::reverse_iterator<Ptr> ReverseIterator;
		typedef std::reverse_iterator<ConstPtr> ConstReverseIterator;

	protected:
		/** Determines when the small vector has not had dynamic allocation. */
		bool isSmall() const
		{
			return static_cast<const void*>(first) == static_cast<const void*>(&firstElement);
		}

		void deallocateOldElements()
		{
			if (!isSmall())
			{
				operator delete(first);
			}
		}

		/** Construct the elements range. */
		void constructElements(Ptr f, Ptr l, ConstReferenceType element)
		{
			for (; f != l; ++f)
			{
				new (f) ValueType(element);
			}
		}

		/** Destroy the elements range. */
		void destroyElements(Ptr f, Ptr l)
		{
			while (f != l)
			{
				--l;
				l->~ValueType();
			}
		}

	protected:
		void grow(SizeType min = 0)
		{
			const SizeType current = capacity - first;
			const SizeType size = size();
			SizeType newCapacity = current * 2;

			if (newCapacity < min)
			{
				newCapacity = min;
			}

			Ptr newElements = static_cast<Ptr>(operator new(newCapacity * sizeof(ValueType)));

			if (std::is_class<ValueType>::value)
			{
				bs::uninitialized_copy(first, last, newElements);
			}
			else
			{
				bs::memcpy(newElements, first, size * sizeof(ValueType));
			}

			destroyElements(first, last);

			deallocateOldElements();

			first = newElements;
			last = newElements + size;
			capacity = first + newCapacity;
		}

	public:
		SmallVectorBuffer(unsigned N)
			: first(reinterpret_cast<Type*>(&firstElement)), last(reinterpret_cast<Type*>(&firstElement)),
			capacity(reinterpret_cast<Type*>(&firstElement) + N) { }

		~SmallVectorBuffer()
		{
			destroyElements(first, last);

			deallocateOldElements();
		};

		bool operator== (const SmallVectorBuffer& other)
		{
			if (size() != other.size())
				return false;

			const SizeType s = size();
			for (Type* tp = first, *tph = other.first, *e = first + s; tp != e; ++tp, ++tph)
			{
				if (*tp != tph)
					return false;
			}

			return true;
		}

		bool operator!= (const SmallVectorBuffer& other) { return !(*this == other); }

		ReferenceType operator[] (SizeType index)
		{
			return first[index];
		}

		ConstReferenceType operator[] (SizeType index) const
		{
			return first[index];
		}

		bool isEmpty() const { return first == last; }

		/** Forward iteration methods. */
		Iterator begin() { return first; }
		Iterator end() { return last; }

		/** Constant Forward iteration methods. */
		ConstIterator cbegin() const { return first; }
		ConstIterator cend() const { return last; }

		/** Reverse iteration methods. */
		ReverseIterator rbegin() { return ReverseIterator(end()); }
		ReverseIterator rend() { return reverse_iterator(begin()); }

		/** Constant Reverse iteration methods. */
		ConstReverseIterator crbegin() const { return ReverseIterator(end()); }
		ConstReverseIterator crend() const { return ReverseIterator(begin()); }

		/** Return the size of the small vector. */
		SizeType size() { return last - first; }

		/** Return the front element of the small vector. */
		ReferenceType front() { return first[0]; }

		/** Return the back element of the small vector. */
		ReferenceType back() { return last[-1]; }

		/** Return the constant front element of the small vector. */
		ConstReferenceType front() const { return first[0]; }

		/** Return the constant back element of the small vector. */
		ConstReferenceType back() const { return last[-1]; }

		/** Push the element into the small vector. */
		void add(ConstReferenceType element)
		{
			if (last < capacity)
			{
				new (last) ValueType(element);
				++last;
			}
		}

		/** Pop the element into the small vector. */
		void pop()
		{
			--last;
			last->~ValueType();
		}

		/** Clear the elements of the small vector. */
		void clear()
		{
			destroyElements(first, last);
			last = first;
		}

		/** Resize N size allocations into the small vector. */
		void resize(unsigned N)
		{
			if (N < size())
			{
				destroyElements(first + N, last);
				last = first + N;
			}
			else if (N > size())
			{
				if (static_cast<unsigned>(capacity - last) < N)
				{
					grow(N);
				}

				constructElements(last, first + N, ValueType());
				last = first + N;
			}
		}

		/** Reserve N size allocations into the small vector. */
		void reserve(unsigned N)
		{
			if (static_cast<unsigned>(capacity - last) < N)
			{
				grow(N);
			}
		}

	protected:
		ValueType * first;
		ValueType* last;
		ValueType* capacity;

		/**
		* Choose which system to use for the space representation.
		*/
#ifdef USE_CHAR
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

	template <class Type>
	class SmallVectorIter
	{
	public:
		SmallVectorIter(Type* _ptr, Type* _arr, Type* _buffer, size_t _size)
			: ptr(ptr), arr(_arr), buffer(_buffer), size(_size) { }

		SmallVectorIter(const SmallVectorIter<Type>& svec)
			: ptr(svec.ptr), arr(svec.arr), buffer(svec.buffer), size(svec.size) { }

		Type& operator*() { return *ptr; }
		Type* operator&() { return ptr; }
		const Type& operator*() const { return *ptr; }
		const Type* operator&() const { return ptr; }

		bool operator==(const SmallVectorIter<Type>& other) { return ptr == other.ptr; }
		bool operator!=(const SmallVectorIter<Type>& other) { return ptr != other.ptr; }
		const bool operator==(const SmallVectorIter<Type>& other) const { return ptr == other.ptr; }
		const bool operator!=(const SmallVectorIter<Type>& other) const { return ptr != other.ptr; }

		SmallVectorIter<Type>& operator++()
		{
			if (ptr == arr + size - 1)
			{
				ptr = buffer;
			}
			else
			{
				++ptr;
			}

			return *this;
		}

		SmallVectorIter<Type>& operator--()
		{
			if (ptr == buffer)
			{
				ptr = arr + size - 1;
			}
			else
			{
				--ptr;
			}

			return *this;
		}

		SmallVectorIter<Type> operator++(int)
		{
			SmallVectorIter<Type> tmp(*this);
			operator++();

			return tmp;
		}

		SmallVectorIter<Type> operator--(int)
		{
			SmallVectorIter<Type> tmp(*this);
			operator--();

			return tmp;
		}

		SmallVectorIter<Type>& operator+=(const int& i)
		{
			if (offset + i >= size && ptr + i < buffer)
			{
				ptr = buffer + i - (size - ptr - buffer);
			}
			else
			{
				ptr += i;
			}

			return *this;
		}

		SmallVectorIter<Type> operator+(const int& i)
		{
			SmallVectorIter<Type> tmp(*this);
			operator+=(i);

			return tmp;
		}

		SmallVectorIter<Type>& operator-=(const int& i)
		{
			if (ptr - i < buffer && ptr - arr >= size)
			{
				ptr = arr + size - i + ptr - buffer;
			}
			else
			{
				ptr -= i;
			}

			return *this;
		}

		SmallVectorIter<Type> operator-(const int& i)
		{
			SmallVectorIter<Type> tmp(*this);
			operator-=(i);

			return tmp;
		}

		Type* ptr;
		Type* arr;
		Type* buffer;
		size_t size;
	};

	template <unsigned N, class Type>
	class SmallVector final : public SmallVectorBuffer<Type>
	{
	public:
		typedef Type ValueType;
		typedef ValueType* Ptr;
		typedef const ValueType* ConstPtr;
		typedef ValueType& ReferenceType;
		typedef const ValueType& ConstReferenceType;
		typedef std::size_t SizeType;
		typedef std::ptrdiff_t DifferenceType;

	private:
		typedef typename SmallVectorBuffer<Type>::U Unit;

		/** The number of the union U require for N template type. */
		static const auto minUnit = (static_cast<UINT32>(sizeof(ValueType))*N +
			static_cast<UINT32>(sizeof(Unit)) - 1 /
			static_cast<UINT32>(sizeof(Unit)));

		/** Contains the number of elements of the array. */
		static const auto elements = (minUnit - 1) > 0 ? (minUnit - 1) : 1;

		/** Contains the number of template type that the arrays has space for. */
		static const auto alloc = (elements + 1)*static_cast<UINT32>(sizeof(Unit)) /
			static_cast<UINT32>(sizeof(ValueType));

		/** Instance of the union U in the small vector buffer. */
		Unit element[elements];

	public:
		SmallVector() : SmallVectorBuffer<ValueType>(alloc) { };
		SmallVector(SizeType size, ConstReferenceType value = ValueType())
			: SmallVectorBuffer<ValueType>(alloc)
		{
			this->reserve(size);
			while (size--)
			{
				add(value);
			}
		}

		virtual ~SmallVector() { };

	};
}