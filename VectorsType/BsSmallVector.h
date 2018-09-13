#pragma once

#include "BsCorePrerequisites.h"

namespace bs 
{
	template<typename _InputIt, typename _ForwardIt>
	_ForwardIt uninitialized_copy(_InputIt first, _InputIt last, _ForwardIt d_first)
	{
		typedef typename std::iterator_traits<_ForwardIt>::value_type Value;
		_ForwardIt current = d_first;

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

	template<typename _Type>
	void memcpy(void* dest, const void* source, _Type num)
	{
		char* _d = (char*)dest;
		const char* _s = (const char*)source;
		const char* _e = _s + num;

		for (; _s < _e; _d++, _s++)
		{
			*_d = *_s;
		}
	}

	template <class _Type>
	class BS_CORE_EXPORT SmallVectorBuffer
	{
	public:
		/** Types */
		typedef _Type value_type;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;

		typedef _Type* iterator;
		typedef const _Type* const_iterator;
		typedef std::reverse_iterator<pointer> reverse_iterator;
		typedef std::reverse_iterator<const_pointer> const_reverse_iterator;

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
		void constructElements(pointer _f, pointer _l, const_reference element)
		{
			for (; _f != _l; ++_f)
			{
				new (_f) value_type(element);
			}
		}

		/** Destroy the elements range. */
		void destroyElements(pointer _f, pointer _l)
		{
			while (_f != _l)
			{
				--_l;
				_l->~value_type();
			}
		}

	protected:
		void grow(size_type _min = 0)
		{
			const size_type _current = capacity - first;
			const size_type _size = size();
			size_type _newCapacity = _current * 2;

			if (_newCapacity < _min)
			{
				_newCapacity = _min;
			}

			pointer newElements = static_cast<pointer>(operator new(_newCapacity * sizeof(value_type)));

			if (std::is_class<value_type>::value)
			{
				bs::uninitialized_copy(first, last, newElements);
			}
			else
			{
				bs::memcpy(newElements, first, _size * sizeof(value_type));
			}

			destroyElements(first, last);

			deallocateOldElements();

			first = newElements;
			last = newElements + _size;
			capacity = first + _newCapacity;
		}

	public:
		SmallVectorBuffer(unsigned N)
			: first(reinterpret_cast<_Type*>(&firstElement)), last(reinterpret_cast<_Type*>(&firstElement)),
			capacity(reinterpret_cast<_Type*>(&firstElement) + N) { }

		~SmallVectorBuffer()
		{
			destroyElements(first, last);

			deallocateOldElements();
		};

		bool operator== (const SmallVectorBuffer& other)
		{
			if (size() != other.size())
				return false;

			const size_type _s = size();
			for (_Type* tp = first, *tph = other.first, *_e = first + _s; tp != _e; ++tp, ++tph)
			{
				if (*tp != tph)
					return false;
			}

			return true;
		}

		bool operator!= (const SmallVectorBuffer& other) { return !(*this == other); }

		reference operator[] (size_type index)
		{
			return first[index];
		}

		const_reference operator[] (size_type index) const
		{
			return first[index];
		}

		bool isEmpty() const { return first == last; }

		/** Forward iteration methods. */
		iterator begin() { return first; }
		iterator end() { return last; }

		/** Constant Forward iteration methods. */
		const_iterator cbegin() const { return first; }
		const_iterator cend() const { return last; }

		/** Reverse iteration methods. */
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); }

		/** Constant Reverse iteration methods. */
		const_reverse_iterator crbegin() const { return reverse_iterator(end()); }
		const_reverse_iterator crend() const { return reverse_iterator(begin()); }

		/** Return the size of the small vector. */
		size_type size() { return last - first; }

		/** Return the front element of the small vector. */
		reference front() { return first[0]; }

		/** Return the back element of the small vector. */
		reference back() { return last[-1]; }

		/** Return the constant front element of the small vector. */
		const_reference front() const { return first[0]; }

		/** Return the constant back element of the small vector. */
		const_reference back() const { return last[-1]; }

		/** Push the element into the small vector. */
		void push_back(const_reference element)
		{
			if (last < capacity)
			{
				new (last) value_type(element);
				++last;
			}
		}

		/** Pop the element into the small vector. */
		void pop_back()
		{
			--last;
			last->~value_type();
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

				constructElements(last, first + N, value_type());
				last = first + N;
			}
		}

		/** Reserve N size allocations into the small vector. */
		void reserve(unsigned N)
		{
			if (static_cast<UINT32>(capacity - last) < N)
			{
				grow(N);
			}
		}

	protected:
		_Type* first;
		_Type* last;
		_Type* capacity;

		/**
		* Choose which system to use for the space representation.
		*/
#ifdef USE_CHAR
		typedef char U;
		U firstElement __declspec(align(16));
#else
		union U
		{
			INT64 L;
			long double LD;
			double D;
			void* ptr;
		} firstElement;
#endif
	};

	template <class _Type>
	class BS_CORE_EXPORT SmallVectorIter
	{
	public:
		SmallVectorIter(_Type* _ptr, _Type* _arr, _Type* _buffer, size_t _size)
			: ptr(ptr), arr(_arr), buffer(_buffer), size(_size) { }

		SmallVectorIter(const SmallVectorIter<_Type>& svec)
			: ptr(svec.ptr), arr(svec.arr), buffer(svec.buffer), size(svec.size) { }

		_Type& operator*() { return *ptr; }
		_Type* operator&() { return ptr; }
		const _Type& operator*() const { return *ptr; }
		const _Type* operator&() const { return ptr; }

		bool operator==(const SmallVectorIter<_Type>& other) { return ptr == other.ptr; }
		bool operator!=(const SmallVectorIter<_Type>& other) { return ptr != other.ptr; }
		const bool operator==(const SmallVectorIter<_Type>& other) const { return ptr == other.ptr; }
		const bool operator!=(const SmallVectorIter<_Type>& other) const { return ptr != other.ptr; }

		SmallVectorIter<_Type>& operator++()
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

		SmallVectorIter<_Type>& operator--()
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

		SmallVectorIter<_Type> operator++(INT32)
		{
			SmallVectorIter<_Type> tmp(*this);
			operator++();

			return tmp;
		}

		SmallVectorIter<_Type> operator--(INT32)
		{
			SmallVectorIter<_Type> tmp(*this);
			operator--();

			return tmp;
		}

		SmallVectorIter<_Type>& operator+=(const INT32& i)
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

		SmallVectorIter<_Type> operator+(const INT32& i)
		{
			SmallVectorIter<_Type> tmp(*this);
			operator+=(i);

			return tmp;
		}

		SmallVectorIter<_Type>& operator-=(const INT32& i)
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

		SmallVectorIter<_Type> operator-(const INT32& i)
		{
			SmallVectorIter<_Type> tmp(*this);
			operator-=(i);

			return tmp;
		}

		_Type* ptr;
		_Type* arr;
		_Type* buffer;
		size_t size;
	};

	template <class _Type, unsigned N>
	class BS_CORE_EXPORT SmallVector final : public SmallVectorBuffer<_Type>
	{
	public:
		typedef _Type value_type;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;

	private:
		typedef typename SmallVectorBuffer<_Type>::U Unit;

		/** The number of the union U require for N template type. */
		static const auto _minUnit = (static_cast<UINT32>(sizeof(value_type))*N +
			static_cast<UINT32>(sizeof(Unit)) - 1 /
			static_cast<UINT32>(sizeof(Unit)));

		/** Contains the number of elements of the array. */
		static const auto _elements = (_minUnit - 1) > 0 ? (_minUnit - 1) : 1;

		/** Contains the number of template type that the arrays has space for. */
		static const auto _alloc = (_elements + 1)*static_cast<UINT32>(sizeof(Unit)) /
			static_cast<UINT32>(sizeof(value_type));

		/** Instance of the union U in the small vector buffer. */
		Unit elements[_elements];

	public:
		SmallVector() : SmallVectorBuffer<value_type>(_alloc) { };
		SmallVector(size_type _size, const_reference value = value_type())
			: SmallVectorBuffer<value_type>(_alloc)
		{
			this->reserve(_size);
			while (_size--)
			{
				push_back(value);
			}
		}

		virtual ~SmallVector() { };

	};
}
