#include "BsCorePrerequisites.h"

namespace bs 
{
	template<class _Type>
	typename std::remove_reference<_Type>::type&& move(_Type&& arg)
	{
		return static_cast<typename std::remove_reference<_Type>::type&&>(arg);
	}

	template <class _Type>
	_Type&& forward(typename std::remove_reference<_Type>::type& arg)
	{
		return static_cast<_Type&&>(arg);
	}

	template <class _Type>
	_Type&& forward(typename std::remove_reference<_Type>::type&& arg)
	{
		static_assert(!std::is_lvalue_reference<_Type>::value, "Cannot make forward an rvalue as an lvalue.");
		return static_cast<_Type&&>(arg);
	}

	template <class _Type>
	class Vector final
	{
	public:
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

		typedef typename Vector<value_type>::iterator Iterator;
		typedef typename Vector<value_type>::iterator ConstIterator;

		Vector();
		Vector(size_type n, const_reference value);
		Vector(Iterator first, Iterator last);
		Vector(const Vector<_Type>& other);
		virtual ~Vector();

		Vector<value_type>& operator= (const Vector<value_type>& other);
		Vector<value_type>& operator= (Vector<value_type>&& other);

		bool operator== (const Vector<value_type>& other) const;
		bool operator!= (const Vector<value_type>& other) const;
		bool operator< (const Vector<value_type>& other) const;
		bool operator<= (const Vector<value_type>& other) const;
		bool operator> (const Vector<value_type>& other) const;
		bool operator>= (const Vector<value_type>& other) const;

		reference operator[] (size_type index);
		const_reference operator[] (size_type index) const;

		void assign(size_type n, const_reference value);
		void assign(Iterator first, Iterator last);

		bool empty() const;

		iterator begin();
		iterator end();

		const_iterator cbegin() const;
		const_iterator cend() const;

		reverse_iterator rbegin();
		reverse_iterator rend();

		const_reverse_iterator crbegin() const;
		const_reverse_iterator crend() const;

		size_type size() const;
		size_type max_size() const;
		size_type capacity() const;

		void resize(size_type _size);
		void resize(size_type _size, const_reference _ref);
		void reserve(size_type _size);
		void shrink_to_fit();

		reference at(size_type index);
		reference front();
		reference back();

		const_reference at(size_type index) const;
		const_reference front() const;
		const_reference back() const;

		pointer data();
		const_pointer data() const;

		template <typename ...Args>
		void emplace_back(Args&& ...args);

		void push_back(const_reference element);
		void push_back(value_type&& element);
		void pop_back();
		void swap(Vector<_Type>& other);
		void clear();
		void reallocate();

		iterator insert(const_iterator it, value_type&& element);
		iterator erase(const_iterator first, const_iterator last);

	private:
		pointer arr;
		size_type initSize = 2;
		size_type arrSize = 0;
		const size_type BS_VECTOR_SIZE = 2 << 16;
	};

	template <class _Type>
	Vector<_Type>::Vector()
	{
		arr = new _Type[initSize];
	}

	template <class _Type>
	Vector<_Type>::Vector(size_type n, const_reference value)
	{
		initSize = n << 2;
		arr = new _Type[initSize];

		for (size_type i = 0; i < n; ++i)
		{
			arr[i] = value;
		}

		arrSize = n;
	}

	template <class _Type>
	Vector<_Type>::Vector(Iterator first, Iterator last)
	{
		size_type count = last - first;
		initSize = count << 2;
		arr = new _Type[initSize];

		for (size_type i = 0; i < count; ++i, ++first)
		{
			arr[i] = *first;
		}

		arrSize = count;
	}

	template <class _Type>
	Vector<_Type>::Vector(const Vector<_Type>& other)
	{
		initSize = other.initSize;
		arr = new _Type[initSize];

		for (size_type i = 0; i < other.arrSize; ++i)
		{
			arr[i] = other.arr[i];
		}

		arrSize = other.arrSize;
	}

	template <class _Type>
	Vector<_Type>::~Vector()
	{
		delete[] arr;
	}

	template <class _Type>
	Vector<_Type>& Vector<_Type>::operator= (const Vector<_Type>& other)
	{
		if (initSize < other.arrSize)
		{
			initSize = other.arrSize << 2;
			reallocate();
		}

		for (size_type i = 0; i < other.arrSize; ++i)
		{
			arr[i] = other.arr[i];
		}

		arrSize = other.arrSize;
	}

	template <class _Type>
	Vector<_Type>& Vector<_Type>::operator= (Vector<_Type>&& other)
	{
		if (initSize < other.arrSize)
		{
			initSize = other.arrSize << 2;
			reallocate();
		}

		for (size_type i = 0; i < other.arrSize; ++i)
		{
			arr[i] = bs::move(other.arr[i]);
		}

		arrSize = other.arrSize;
	}

	template <typename _Type>
	bool Vector<_Type>::operator== (const Vector<_Type>& other) const
	{
		if (arrSize != other.arrSize)
			return false;

		for (size_type i = 0; i < arrSize; ++i)
		{
			if (arr[i] != other.arr[i])
				return false;
		}

		return true;
	}

	template <typename _Type>
	bool Vector<_Type>::operator!= (const Vector<_Type>& other) const
	{
		if (arrSize != other.arrSize)
			return true;

		for (size_type i = 0; i < arrSize; ++i)
		{
			if (arr[i] != other.arr[i])
				return true;
		}

		return false;
	}

	template <typename _Type>
	bool Vector<_Type>::operator< (const Vector<_Type>& other) const
	{
		size_type length = arrSize < other.arrSize ? arrSize : other.arrSize;

		for (size_type i = 0; i < length; ++i)
		{
			if (arr[i] != other.arr[i])
				return arr[i] < other.arr[i];
		}

		return arrSize < other.arrSize;
	}

	template <typename _Type>
	bool Vector<_Type>::operator<= (const Vector<_Type>& other) const
	{
		size_type length = arrSize < other.arrSize ? arrSize : other.arrSize;

		for (size_type i = 0; i < length; ++i)
		{
			if (arr[i] != other.arr[i])
				return arr[i] < other.arr[i];
		}

		return arrSize <= other.arrSize;
	}

	template <typename _Type>
	bool Vector<_Type>::operator> (const Vector<_Type>& other) const
	{
		size_type length = arrSize < other.arrSize ? arrSize : other.arrSize;

		for (size_type i = 0; i < length; ++i)
		{
			if (arr[i] != other.arr[i])
				return arr[i] > other.arr[i];
		}

		return arrSize > other.arrSize;
	}

	template <typename _Type>
	bool Vector<_Type>::operator>= (const Vector<_Type>& other) const
	{
		size_type length = arrSize < other.arrSize ? arrSize : other.arrSize;

		for (size_type i = 0; i < length; ++i)
		{
			if (arr[i] != other.arr[i])
				return arr[i] > other.arr[i];
		}

		return arrSize >= other.arrSize;
	}

	template <class _Type>
	void Vector<_Type>::assign(size_type count, const_reference value)
	{
		if (count > initSize)
		{
			initSize = count << 2;
			reallocate();
		}

		for (size_type i = 0; i < count; ++i)
		{
			arr[i] = value;
		}

		arrSize = count;
	}

	template <class _Type>
	void Vector<_Type>::assign(Iterator first, Iterator last)
	{
		size_type count = last - first;
		if (count > initSize)
		{
			initSize = count << 2;
			reallocate();
		}

		for (size_type i = 0; i < count; ++i, ++first)
		{
			arr[i] = *first;
		}

		arrSize = count;
	}

	template <class _Type>
	typename Vector<_Type>::iterator Vector<_Type>::begin()
	{
		return arr;
	}

	template <class _Type>
	typename Vector<_Type>::iterator Vector<_Type>::end()
	{
		return arr + arrSize;
	}

	template <class _Type>
	typename Vector<_Type>::const_iterator Vector<_Type>::cbegin() const
	{
		return arr;
	}


	template <class _Type>
	typename Vector<_Type>::const_iterator Vector<_Type>::cend() const
	{
		return arr + arrSize;
	}

	template <class _Type>
	typename Vector<_Type>::reverse_iterator Vector<_Type>::rbegin()
	{
		return reverse_iterator(arr + arrSize);
	}

	template <class _Type>
	typename Vector<_Type>::reverse_iterator Vector<_Type>::rend()
	{
		return reverse_iterator(arr);
	}

	template <class _Type>
	typename Vector<_Type>::const_reverse_iterator Vector<_Type>::crbegin() const
	{
		return reverse_iterator(arr + arrSize);
	}

	template <class _Type>
	typename Vector<_Type>::const_reverse_iterator Vector<_Type>::crend() const
	{
		return reverse_iterator(arr);
	}

	template <class _Type>
	void Vector<_Type>::reallocate()
	{
		_Type* tmp = new _Type[initSize];

		memcpy(tmp, arr, arrSize * sizeof(_Type));

		delete[] arr;
		arr = tmp;
	}

	template <class _Type>
	bool Vector<_Type>::empty() const
	{
		return arrSize == 0;
	}

	template <class _Type>
	typename Vector<_Type>::size_type Vector<_Type>::size() const
	{
		return arrSize;
	}

	template <typename _Type>
	typename Vector<_Type>::size_type Vector<_Type>::max_size() const
	{
		return BS_VECTOR_SIZE;
	}

	template <class _Type>
	typename Vector<_Type>::size_type Vector<_Type>::capacity() const
	{
		return initSize;
	}

	template <class _Type>
	void Vector<_Type>::resize(size_type sz)
	{
		if (sz > arrSize)
		{
			if (sz > initSize)
			{
				initSize = sz;
				reallocate();
			}
		}
		else
		{
			for (size_type i = arrSize; i < sz; ++i)
				arr[i].~Type();
		}

		arrSize = sz;
	}

	template <class _Type>
	void Vector<_Type>::resize(size_type _size, const_reference _ref)
	{
		if (_size > arrSize)
		{
			if (_size > initSize)
			{
				initSize = _size;
				reallocate();
			}

			for (size_type i = arrSize; i < _size; ++i)
			{
				arr[i] = _ref;
			}
		}
		else
		{
			for (size_type i = arrSize; i < _size; ++i)
				arr[i].~Type();
		}

		arrSize = _size;
	}

	template <class _Type>
	void Vector<_Type>::reserve(size_type _size)
	{
		if (_size > initSize)
		{
			initSize = _size;
			reallocate();
		}
	}

	template <class _Type>
	void Vector<_Type>::shrink_to_fit()
	{
		initSize = arrSize;
		reallocate();
	}

	template <typename _Type>
	typename Vector<_Type>::reference Vector<_Type>::operator[] (typename Vector<_Type>::size_type index)
	{
		return arr[index];
	}

	template <typename _Type>
	typename Vector<_Type>::const_reference Vector<_Type>::operator[] (typename Vector<_Type>::size_type index) const
	{
		return arr[index];
	}

	template <typename _Type>
	typename Vector<_Type>::reference Vector<_Type>::at(size_type index)
	{
		if (index < arrSize)
		{
			return arr[index];
		}
		else
		{
			LOGERR("index is out of range\n");
		}
	}

	template <typename _Type>
	typename Vector<_Type>::const_reference Vector<_Type>::at(size_type index) const
	{
		if (index < arrSize)
		{
			return arr[index];
		}
		else
		{
			LOGERR("index is out of range\n");
		}
	}

	template <typename _Type>
	typename Vector<_Type>::reference Vector<_Type>::front()
	{
		return arr[0];
	}

	template <typename _Type>
	typename Vector<_Type>::const_reference Vector<_Type>::front() const
	{
		return arr[0];
	}

	template <typename _Type>
	typename Vector<_Type>::reference Vector<_Type>::back()
	{
		return arr[arrSize - 1];
	}

	template <typename _Type>
	typename Vector<_Type>::const_reference Vector<_Type>::back() const
	{
		return arr[arrSize - 1];
	}


	template <typename _Type>
	_Type* Vector<_Type>::data()
	{
		return arr;
	}

	template <typename _Type>
	const _Type* Vector<_Type>::data() const
	{
		return arr;
	}

	template <typename _Type>
	template <class ...Args>
	void Vector<_Type>::emplace_back(Args&& ...args)
	{
		if (arrSize == initSize)
		{
			initSize <<= 2;
			reallocate();
		}

		arr[arrSize] = bs::move(_Type(bs::forward<Args>(args) ...));
		++arrSize;
	}

	template <typename _Type>
	void Vector<_Type>::push_back(const_reference element)
	{
		if (arrSize == initSize)
		{
			initSize <<= 2;
			reallocate();
		}

		arr[arrSize] = element;
		++arrSize;
	}

	template <typename _Type>
	void Vector<_Type>::push_back(value_type&& element)
	{
		if (arrSize == initSize)
		{
			initSize <<= 2;
			reallocate();
		}

		arr[arrSize] = bs::move(element);
		++arrSize;
	}

	template <typename _Type>
	void Vector<_Type>::pop_back()
	{
		--arrSize;
		arr[arrSize].~_Type();
	}

	template <typename _Type>
	typename Vector<_Type>::iterator Vector<_Type>::insert(const_iterator it, value_type&& element)
	{
		iterator iter = &arr[it - arr];
		if (arrSize == initSize)
		{
			initSize <<= 2;
			reallocate();
		}

		memmove(iter + 1, iter, (arrSize - (it - arr)) * sizeof(_Type));

		(*iter) = element;
		++arrSize;

		return iter;
	}

	template <typename _Type>
	typename Vector<_Type>::iterator Vector<_Type>::erase(typename Vector<_Type>::const_iterator first, typename Vector<_Type>::const_iterator last)
	{
		iterator iter = &arr[first - arr];
		if (first == last)
			return iter;

		for (; first != last; ++first)
		{
			(*first).~_Type();
		}

		memmove(iter, last, (arrSize - (last - arr)) * sizeof(_Type));
		arrSize -= last - first;

		return iter;
	}

	template <typename _Type>
	void Vector<_Type>::swap(Vector<_Type>& other)
	{
		const size_t tmpSize = arrSize;
		const size_t tmpInitSize = initSize;
		const _Type* tmp = arr;

		arrSize = other.arrSize;
		initSize = other.initSize;
		arr = other.arr;

		other.arrSize = tmpSize;
		other.initSize = tmpInitSize;
		other.arr = tmp;
	}

	template <typename _Type>
	void Vector<_Type>::clear()
	{
		for (size_type i = 0; i < arrSize; ++i)
		{
			arr[i].~_Type();
		}

		arrSize = 0;
	}
}