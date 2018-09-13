#include "BsCorePrerequisites.h"

namespace bs 
{
	template<class Type>
	typename std::remove_reference<Type>::type&& move(Type&& arg)
	{
		return static_cast<typename std::remove_reference<Type>::type&&>(arg);
	}

	template <class Type>
	Type&& forward(typename std::remove_reference<Type>::type& arg)
	{
		return static_cast<Type&&>(arg);
	}

	template <class Type>
	Type&& forward(typename std::remove_reference<Type>::type&& arg)
	{
		static_assert(!std::is_lvalue_reference<Type>::value, "Cannot make forward an rvalue as an lvalue.");
		return static_cast<Type&&>(arg);
	}

	template <class Type>
	class Vector final
	{
	public:
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

		typedef typename Vector<ValueType>::Iterator IteratorType;
		typedef typename Vector<ValueType>::Iterator ConstIteratorType;

		Vector();
		Vector(SizeType n, ConstReferenceType value);
		Vector(Iterator first, Iterator last);
		Vector(const Vector<Type>& other);
		virtual ~Vector();

		Vector<ValueType>& operator= (const Vector<ValueType>& other);
		Vector<ValueType>& operator= (Vector<ValueType>&& other);

		bool operator== (const Vector<ValueType>& other) const;
		bool operator!= (const Vector<ValueType>& other) const;
		bool operator< (const Vector<ValueType>& other) const;
		bool operator<= (const Vector<ValueType>& other) const;
		bool operator> (const Vector<ValueType>& other) const;
		bool operator>= (const Vector<ValueType>& other) const;

		ReferenceType operator[] (SizeType index);
		ConstReferenceType operator[] (SizeType index) const;

		void assign(SizeType n, ConstReferenceType value);
		void assign(IteratorType first, IteratorType last);

		bool empty() const;

		Iterator begin();
		Iterator end();

		ConstIterator cbegin() const;
		ConstIterator cend() const;

		ReverseIterator rbegin();
		ReverseIterator rend();

		ConstReverseIterator crbegin() const;
		ConstReverseIterator crend() const;

		SizeType size() const;
		SizeType max_size() const;
		SizeType capacity() const;

		void resize(SizeType _size);
		void resize(SizeType _size, ConstReferenceType _ref);
		void reserve(SizeType _size);
		void shrink_to_fit();

		ReferenceType at(SizeType index);
		ReferenceType front();
		ReferenceType back();

		ConstReferenceType at(SizeType index) const;
		ConstReferenceType front() const;
		ConstReferenceType back() const;

		Ptr data();
		ConstPtr data() const;

		template <typename ...Args>
		void emplace_back(Args&& ...args);

		void push_back(ConstReferenceType element);
		void push_back(ValueType&& element);
		void pop_back();
		void swap(Vector<Type>& other);
		void clear();
		void reallocate();

		Iterator insert(ConstIterator it, ValueType&& element);
		Iterator erase(ConstIterator first, ConstIterator last);

	private:
		Ptr arr;
		SizeType initSize = 2;
		SizeType arrSize = 0;
		const SizeType BS_VECTOR_SIZE = 2 << 16;
	};

	template <class Type>
	Vector<Type>::Vector()
	{
		arr = new Type[initSize];
	}

	template <class Type>
	Vector<Type>::Vector(SizeType n, ConstReferenceType value)
	{
		initSize = n << 2;
		arr = new Type[initSize];

		for (SizeType i = 0; i < n; ++i)
		{
			arr[i] = value;
		}

		arrSize = n;
	}

	template <class Type>
	Vector<Type>::Vector(Iterator first, Iterator last)
	{
		SizeType count = last - first;
		initSize = count << 2;
		arr = new Type[initSize];

		for (SizeType i = 0; i < count; ++i, ++first)
		{
			arr[i] = *first;
		}

		arrSize = count;
	}

	template <class Type>
	Vector<Type>::Vector(const Vector<Type>& other)
	{
		initSize = other.initSize;
		arr = new Type[initSize];

		for (SizeType i = 0; i < other.arrSize; ++i)
		{
			arr[i] = other.arr[i];
		}

		arrSize = other.arrSize;
	}

	template <class Type>
	Vector<Type>::~Vector()
	{
		delete[] arr;
	}

	template <class Type>
	Vector<Type>& Vector<Type>::operator= (const Vector<Type>& other)
	{
		if (initSize < other.arrSize)
		{
			initSize = other.arrSize << 2;
			reallocate();
		}

		for (SizeType i = 0; i < other.arrSize; ++i)
		{
			arr[i] = other.arr[i];
		}

		arrSize = other.arrSize;
	}

	template <class Type>
	Vector<Type>& Vector<Type>::operator= (Vector<Type>&& other)
	{
		if (initSize < other.arrSize)
		{
			initSize = other.arrSize << 2;
			reallocate();
		}

		for (SizeType i = 0; i < other.arrSize; ++i)
		{
			arr[i] = bs::move(other.arr[i]);
		}

		arrSize = other.arrSize;
	}

	template <typename Type>
	bool Vector<Type>::operator== (const Vector<Type>& other) const
	{
		if (arrSize != other.arrSize)
			return false;

		for (SizeType i = 0; i < arrSize; ++i)
		{
			if (arr[i] != other.arr[i])
				return false;
		}

		return true;
	}

	template <typename Type>
	bool Vector<Type>::operator!= (const Vector<Type>& other) const
	{
		if (arrSize != other.arrSize)
			return true;

		for (SizeType i = 0; i < arrSize; ++i)
		{
			if (arr[i] != other.arr[i])
				return true;
		}

		return false;
	}

	template <typename Type>
	bool Vector<Type>::operator< (const Vector<Type>& other) const
	{
		SizeType length = arrSize < other.arrSize ? arrSize : other.arrSize;

		for (SizeType i = 0; i < length; ++i)
		{
			if (arr[i] != other.arr[i])
				return arr[i] < other.arr[i];
		}

		return arrSize < other.arrSize;
	}

	template <typename Type>
	bool Vector<Type>::operator<= (const Vector<Type>& other) const
	{
		SizeType length = arrSize < other.arrSize ? arrSize : other.arrSize;

		for (SizeType i = 0; i < length; ++i)
		{
			if (arr[i] != other.arr[i])
				return arr[i] < other.arr[i];
		}

		return arrSize <= other.arrSize;
	}

	template <typename Type>
	bool Vector<Type>::operator> (const Vector<Type>& other) const
	{
		SizeType length = arrSize < other.arrSize ? arrSize : other.arrSize;

		for (SizeType i = 0; i < length; ++i)
		{
			if (arr[i] != other.arr[i])
				return arr[i] > other.arr[i];
		}

		return arrSize > other.arrSize;
	}

	template <typename Type>
	bool Vector<Type>::operator>= (const Vector<Type>& other) const
	{
		SizeType length = arrSize < other.arrSize ? arrSize : other.arrSize;

		for (SizeType i = 0; i < length; ++i)
		{
			if (arr[i] != other.arr[i])
				return arr[i] > other.arr[i];
		}

		return arrSize >= other.arrSize;
	}

	template <class Type>
	void Vector<Type>::assign(SizeType count, ConstReferenceType value)
	{
		if (count > initSize)
		{
			initSize = count << 2;
			reallocate();
		}

		for (SizeType i = 0; i < count; ++i)
		{
			arr[i] = value;
		}

		arrSize = count;
	}

	template <class Type>
	void Vector<Type>::assign(IteratorType first, IteratorType last)
	{
		SizeType count = last - first;
		if (count > initSize)
		{
			initSize = count << 2;
			reallocate();
		}

		for (SizeType i = 0; i < count; ++i, ++first)
		{
			arr[i] = *first;
		}

		arrSize = count;
	}

	template <class Type>
	typename Vector<Type>::Iterator Vector<Type>::begin()
	{
		return arr;
	}

	template <class Type>
	typename Vector<Type>::Iterator Vector<Type>::end()
	{
		return arr + arrSize;
	}

	template <class Type>
	typename Vector<Type>::ConstIterator Vector<Type>::cbegin() const
	{
		return arr;
	}


	template <class Type>
	typename Vector<Type>::ConstIterator Vector<Type>::cend() const
	{
		return arr + arrSize;
	}

	template <class Type>
	typename Vector<Type>::ReverseIterator Vector<Type>::rbegin()
	{
		return ReverseIterator(arr + arrSize);
	}

	template <class Type>
	typename Vector<Type>::ReverseIterator Vector<Type>::rend()
	{
		return ReverseIterator(arr);
	}

	template <class Type>
	typename Vector<Type>::ConstReverseIterator Vector<Type>::crbegin() const
	{
		return ReverseIterator(arr + arrSize);
	}

	template <class Type>
	typename Vector<Type>::ConstReverseIterator Vector<Type>::crend() const
	{
		return ReverseIterator(arr);
	}

	template <class Type>
	void Vector<Type>::reallocate()
	{
		Type* tmp = new Type[initSize];

		memcpy(tmp, arr, arrSize * sizeof(Type));

		delete[] arr;
		arr = tmp;
	}

	template <class Type>
	bool Vector<Type>::empty() const
	{
		return arrSize == 0;
	}

	template <class Type>
	typename Vector<Type>::SizeType Vector<Type>::size() const
	{
		return arrSize;
	}

	template <typename Type>
	typename Vector<Type>::SizeType Vector<Type>::max_size() const
	{
		return BS_VECTOR_SIZE;
	}

	template <class Type>
	typename Vector<Type>::SizeType Vector<Type>::capacity() const
	{
		return initSize;
	}

	template <class Type>
	void Vector<Type>::resize(SizeType sz)
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
			for (SizeType i = arrSize; i < sz; ++i)
				arr[i].~Type();
		}

		arrSize = sz;
	}

	template <class Type>
	void Vector<Type>::resize(SizeType _size, ConstReferenceType _ref)
	{
		if (_size > arrSize)
		{
			if (_size > initSize)
			{
				initSize = _size;
				reallocate();
			}

			for (SizeType i = arrSize; i < _size; ++i)
			{
				arr[i] = _ref;
			}
		}
		else
		{
			for (SizeType i = arrSize; i < _size; ++i)
				arr[i].~Type();
		}

		arrSize = _size;
	}

	template <class Type>
	void Vector<Type>::reserve(SizeType _size)
	{
		if (_size > initSize)
		{
			initSize = _size;
			reallocate();
		}
	}

	template <class Type>
	void Vector<Type>::shrink_to_fit()
	{
		initSize = arrSize;
		reallocate();
	}

	template <typename Type>
	typename Vector<Type>::ReferenceType Vector<Type>::operator[] (typename Vector<Type>::SizeType index)
	{
		return arr[index];
	}

	template <typename Type>
	typename Vector<Type>::ConstReferenceType Vector<Type>::operator[] (typename Vector<Type>::SizeType index) const
	{
		return arr[index];
	}

	template <typename Type>
	typename Vector<Type>::ReferenceType Vector<Type>::at(SizeType index)
	{
		if (index < arrSize)
		{
			return arr[index];
		}
		else
		{
			throw std::out_of_range("index is out of range\n");
		}
	}

	template <typename Type>
	typename Vector<Type>::ConstReferenceType Vector<Type>::at(SizeType index) const
	{
		if (index < arrSize)
		{
			return arr[index];
		}
		else
		{
			throw std::out_of_range("index is out of range\n");
		}
	}

	template <typename Type>
	typename Vector<Type>::ReferenceType Vector<Type>::front()
	{
		return arr[0];
	}

	template <typename Type>
	typename Vector<Type>::ConstReferenceType Vector<Type>::front() const
	{
		return arr[0];
	}

	template <typename Type>
	typename Vector<Type>::ReferenceType Vector<Type>::back()
	{
		return arr[arrSize - 1];
	}

	template <typename Type>
	typename Vector<Type>::ConstReferenceType Vector<Type>::back() const
	{
		return arr[arrSize - 1];
	}


	template <typename Type>
	Type* Vector<Type>::data()
	{
		return arr;
	}

	template <typename Type>
	const Type* Vector<Type>::data() const
	{
		return arr;
	}

	template <typename Type>
	template <class ...Args>
	void Vector<Type>::emplace_back(Args&& ...args)
	{
		if (arrSize == initSize)
		{
			initSize <<= 2;
			reallocate();
		}

		arr[arrSize] = bs::move(Type(bs::forward<Args>(args) ...));
		++arrSize;
	}

	template <typename Type>
	void Vector<Type>::push_back(ConstReferenceType element)
	{
		if (arrSize == initSize)
		{
			initSize <<= 2;
			reallocate();
		}

		arr[arrSize] = element;
		++arrSize;
	}

	template <typename Type>
	void Vector<Type>::push_back(ValueType&& element)
	{
		if (arrSize == initSize)
		{
			initSize <<= 2;
			reallocate();
		}

		arr[arrSize] = bs::move(element);
		++arrSize;
	}

	template <typename Type>
	void Vector<Type>::pop_back()
	{
		--arrSize;
		arr[arrSize].~Type();
	}

	template <typename Type>
	typename Vector<Type>::Iterator Vector<Type>::insert(ConstIterator it, ValueType&& element)
	{
		Iterator iter = &arr[it - arr];
		if (arrSize == initSize)
		{
			initSize <<= 2;
			reallocate();
		}

		memmove(iter + 1, iter, (arrSize - (it - arr)) * sizeof(Type));

		(*iter) = element;
		++arrSize;

		return iter;
	}

	template <typename Type>
	typename Vector<Type>::Iterator Vector<Type>::erase(typename Vector<Type>::ConstIterator first, typename Vector<Type>::ConstIterator last)
	{
		Iterator iter = &arr[first - arr];
		if (first == last)
			return iter;

		for (; first != last; ++first)
		{
			(*first).~Type();
		}

		memmove(iter, last, (arrSize - (last - arr)) * sizeof(Type));
		arrSize -= last - first;

		return iter;
	}

	template <typename Type>
	void Vector<Type>::swap(Vector<Type>& other)
	{
		const size_t tmpSize = arrSize;
		const size_t tmpInitSize = initSize;
		const Type* tmp = arr;

		arrSize = other.arrSize;
		initSize = other.initSize;
		arr = other.arr;

		other.arrSize = tmpSize;
		other.initSize = tmpInitSize;
		other.arr = tmp;
	}

	template <typename Type>
	void Vector<Type>::clear()
	{
		for (SizeType i = 0; i < arrSize; ++i)
		{
			arr[i].~Type();
		}

		arrSize = 0;
	}
}