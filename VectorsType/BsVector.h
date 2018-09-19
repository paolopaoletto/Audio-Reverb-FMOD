#pragma once

#include "Prerequisites/BsPrerequisitesUtil.h"
#include "Allocators/BsStaticAlloc.h"

namespace bs 
{
	template <class Type>
	class Vector final
	{
	public:
		typedef Type ValueType;
		typedef Type* Iterator;
		typedef const Type* ConstIterator;
		typedef std::reverse_iterator<Type*> ReverseIterator;
		typedef std::reverse_iterator<const Type*> ConstReverseIterator;

		typedef typename Vector<ValueType>::Iterator IteratorType;
		typedef typename Vector<ValueType>::Iterator ConstIteratorType;

		Vector();
		Vector(size_t n, const Type& value);
		Vector(Iterator first, Iterator last);
		Vector(const Vector<Type>& other);
		~Vector();

		Vector<ValueType>& operator= (const Vector<ValueType>& other);
		Vector<ValueType>& operator= (Vector<ValueType>&& other);

		bool operator== (const Vector<ValueType>& other) const;
		bool operator!= (const Vector<ValueType>& other) const;
		bool operator< (const Vector<ValueType>& other) const;
		bool operator<= (const Vector<ValueType>& other) const;
		bool operator> (const Vector<ValueType>& other) const;
		bool operator>= (const Vector<ValueType>& other) const;

		Type& operator[] (size_t index);
		const Type& operator[] (size_t index) const;

		void assign(size_t n, const Type& value);
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

		size_t size() const;
		size_t max_size() const;
		size_t capacity() const;

		void resize(size_t _size);
		void resize(size_t _size, const Type& _ref);
		void reserve(size_t _size);
		void shrink_to_fit();

		Type& at(size_t index);
		Type& front();
		Type& back();

		const Type& at(size_t index) const;
		const Type& front() const;
		const Type& back() const;

		Type* data();
		const Type* data() const;

		template <typename ...Args>
		void emplace_back(Args&& ...args);

		void push_back(const Type& element);
		void push_back(ValueType&& element);
		void pop_back();
		void swap(Vector<Type>& other);
		void clear();
		void reallocate();

		Iterator insert(ConstIterator it, ValueType&& element);
		Iterator erase(ConstIterator first, ConstIterator last);

	private:
		Type* mArr;
		size_t mInitSize = 2;
		size_t mArrSize = 0;
		StaticAlloc alloc;
		const size_t BS_VECTOR_SIZE = 2 << 16;
	};

	template <class Type>
	Vector<Type>::Vector()
	{
		mArr = new Type[mInitSize];
	}

	template <class Type>
	Vector<Type>::Vector(size_t n, const Type& value)
	{
		mInitSize = n << 2;
		mArr = new Type[mInitSize];

		for (size_t i = 0; i < n; ++i)
		{
			mArr[i] = value;
		}

		mArrSize = n;
	}

	template <class Type>
	Vector<Type>::Vector(Iterator first, Iterator last)
	{
		size_t count = last - first;
		mInitSize = count << 2;
		mArr = new Type[mInitSize];

		for (size_t i = 0; i < count; ++i, ++first)
		{
			mArr[i] = *first;
		}

		mArrSize = count;
	}

	template <class Type>
	Vector<Type>::Vector(const Vector<Type>& other)
	{
		mInitSize = other.mInitSize;
		mArr = new Type[mInitSize];

		for (size_t i = 0; i < other.mArrSize; ++i)
		{
			mArr[i] = other.mArr[i];
		}

		mArrSize = other.mArrSize;
	}

	template <class Type>
	Vector<Type>::~Vector()
	{
		delete[] mArr;
	}

	template <class Type>
	Vector<Type>& Vector<Type>::operator= (const Vector<Type>& other)
	{
		if (mInitSize < other.mArrSize)
		{
			mInitSize = other.mArrSize << 2;
			reallocate();
		}

		for (size_t i = 0; i < other.mArrSize; ++i)
		{
			mArr[i] = other.mArr[i];
		}

		mArrSize = other.mArrSize;
	}

	template <class Type>
	Vector<Type>& Vector<Type>::operator= (Vector<Type>&& other)
	{
		if (mInitSize < other.mArrSize)
		{
			mInitSize = other.mArrSize << 2;
			reallocate();
		}

		for (size_t i = 0; i < other.mArrSize; ++i)
		{
			mArr[i] = std::move(other.mArr[i]);
		}

		mArrSize = other.mArrSize;
	}

	template <typename Type>
	bool Vector<Type>::operator== (const Vector<Type>& other) const
	{
		if (mArrSize != other.mArrSize)
			return false;

		for (size_t i = 0; i < mArrSize; ++i)
		{
			if (mArr[i] != other.mArr[i])
				return false;
		}

		return true;
	}

	template <typename Type>
	bool Vector<Type>::operator!= (const Vector<Type>& other) const
	{
		if (mArrSize != other.mArrSize)
			return true;

		for (size_t i = 0; i < mArrSize; ++i)
		{
			if (mArr[i] != other.mArr[i])
				return true;
		}

		return false;
	}

	template <typename Type>
	bool Vector<Type>::operator< (const Vector<Type>& other) const
	{
		size_t length = mArrSize < other.mArrSize ? mArrSize : other.mArrSize;

		for (size_t i = 0; i < length; ++i)
		{
			if (mArr[i] != other.mArr[i])
				return mArr[i] < other.mArr[i];
		}

		return mArrSize < other.mArrSize;
	}

	template <typename Type>
	bool Vector<Type>::operator<= (const Vector<Type>& other) const
	{
		size_t length = mArrSize < other.mArrSize ? mArrSize : other.mArrSize;

		for (size_t i = 0; i < length; ++i)
		{
			if (mArr[i] != other.mArr[i])
				return mArr[i] < other.mArr[i];
		}

		return mArrSize <= other.mArrSize;
	}

	template <typename Type>
	bool Vector<Type>::operator> (const Vector<Type>& other) const
	{
		size_t length = mArrSize < other.mArrSize ? mArrSize : other.mArrSize;

		for (size_t i = 0; i < length; ++i)
		{
			if (mArr[i] != other.mArr[i])
				return mArr[i] > other.mArr[i];
		}

		return mArrSize > other.mArrSize;
	}

	template <typename Type>
	bool Vector<Type>::operator>= (const Vector<Type>& other) const
	{
		size_t length = mArrSize < other.mArrSize ? mArrSize : other.mArrSize;

		for (size_t i = 0; i < length; ++i)
		{
			if (mArr[i] != other.mArr[i])
				return mArr[i] > other.mArr[i];
		}

		return mArrSize >= other.mArrSize;
	}

	template <class Type>
	void Vector<Type>::assign(size_t count, const Type& value)
	{
		if (count > mInitSize)
		{
			mInitSize = count << 2;
			reallocate();
		}

		for (size_t i = 0; i < count; ++i)
		{
			mArr[i] = value;
		}

		mArrSize = count;
	}

	template <class Type>
	void Vector<Type>::assign(IteratorType first, IteratorType last)
	{
		size_t count = last - first;
		if (count > mInitSize)
		{
			mInitSize = count << 2;
			reallocate();
		}

		for (size_t i = 0; i < count; ++i, ++first)
		{
			mArr[i] = *first;
		}

		mArrSize = count;
	}

	template <class Type>
	typename Vector<Type>::Iterator Vector<Type>::begin()
	{
		return mArr;
	}

	template <class Type>
	typename Vector<Type>::Iterator Vector<Type>::end()
	{
		return mArr + mArrSize;
	}

	template <class Type>
	typename Vector<Type>::ConstIterator Vector<Type>::cbegin() const
	{
		return mArr;
	}


	template <class Type>
	typename Vector<Type>::ConstIterator Vector<Type>::cend() const
	{
		return mArr + mArrSize;
	}

	template <class Type>
	typename Vector<Type>::ReverseIterator Vector<Type>::rbegin()
	{
		return ReverseIterator(mArr + mArrSize);
	}

	template <class Type>
	typename Vector<Type>::ReverseIterator Vector<Type>::rend()
	{
		return ReverseIterator(mArr);
	}

	template <class Type>
	typename Vector<Type>::ConstReverseIterator Vector<Type>::crbegin() const
	{
		return ReverseIterator(mArr + mArrSize);
	}

	template <class Type>
	typename Vector<Type>::ConstReverseIterator Vector<Type>::crend() const
	{
		return ReverseIterator(mArr);
	}

	template <class Type>
	void Vector<Type>::reallocate()
	{
		Type* tmp = new Type[mInitSize];

		memcpy(tmp, mArr, mArrSize * sizeof(Type));

		delete[] mArr;
		mArr = tmp;
	}

	template <class Type>
	bool Vector<Type>::empty() const
	{
		return mArrSize == 0;
	}

	template <class Type>
	size_t Vector<Type>::size() const
	{
		return mArrSize;
	}

	template <typename Type>
	size_t Vector<Type>::max_size() const
	{
		return BS_VECTOR_SIZE;
	}

	template <class Type>
	size_t Vector<Type>::capacity() const
	{
		return mInitSize;
	}

	template <class Type>
	void Vector<Type>::resize(size_t sz)
	{
		if (sz > mArrSize)
		{
			if (sz > mInitSize)
			{
				mInitSize = sz;
				reallocate();
			}
		}
		else
		{
			for (size_t i = mArrSize; i < sz; ++i)
				mArr[i].~Type();
		}

		mArrSize = sz;
	}

	template <class Type>
	void Vector<Type>::resize(size_t _size, const Type& _ref)
	{
		if (_size > mArrSize)
		{
			if (_size > mInitSize)
			{
				mInitSize = _size;
				reallocate();
			}

			for (size_t i = mArrSize; i < _size; ++i)
			{
				mArr[i] = _ref;
			}
		}
		else
		{
			for (size_t i = mArrSize; i < _size; ++i)
				mArr[i].~Type();
		}

		mArrSize = _size;
	}

	template <class Type>
	void Vector<Type>::reserve(size_t _size)
	{
		if (_size > mInitSize)
		{
			mInitSize = _size;
			reallocate();
		}
	}

	template <class Type>
	void Vector<Type>::shrink_to_fit()
	{
		mInitSize = mArrSize;
		reallocate();
	}

	template <typename Type>
	Type& Vector<Type>::operator[] (size_t index)
	{
		return mArr[index];
	}

	template <typename Type>
	const Type& Vector<Type>::operator[] (size_t index) const
	{
		return mArr[index];
	}

	template <typename Type>
	Type& Vector<Type>::at(size_t index)
	{
		if (index < mArrSize)
		{
			return mArr[index];
		}
		else
		{
			throw std::out_of_range("index is out of range\n");
		}
	}

	template <typename Type>
	const Type& Vector<Type>::at(size_t index) const
	{
		if (index < mArrSize)
		{
			return mArr[index];
		}
		else
		{
			throw std::out_of_range("index is out of range\n");
		}
	}

	template <typename Type>
	Type& Vector<Type>::front()
	{
		return mArr[0];
	}

	template <typename Type>
	const Type& Vector<Type>::front() const
	{
		return mArr[0];
	}

	template <typename Type>
	Type& Vector<Type>::back()
	{
		return mArr[mArrSize - 1];
	}

	template <typename Type>
	const Type& Vector<Type>::back() const
	{
		return mArr[mArrSize - 1];
	}


	template <typename Type>
	Type* Vector<Type>::data()
	{
		return mArr;
	}

	template <typename Type>
	const Type* Vector<Type>::data() const
	{
		return mArr;
	}

	template <typename Type>
	template <class ...Args>
	void Vector<Type>::emplace_back(Args&& ...args)
	{
		if (mArrSize == mInitSize)
		{
			mInitSize <<= 2;
			reallocate();
		}

		mArr[mArrSize] = std::move(Type(std::forward<Args>(args) ...));
		++mArrSize;
	}

	template <typename Type>
	void Vector<Type>::push_back(const Type& element)
	{
		if (mArrSize == mInitSize)
		{
			mInitSize <<= 2;
			reallocate();
		}

		mArr[mArrSize] = element;
		++mArrSize;
	}

	template <typename Type>
	void Vector<Type>::push_back(ValueType&& element)
	{
		if (mArrSize == mInitSize)
		{
			mInitSize <<= 2;
			reallocate();
		}

		mArr[mArrSize] = std::move(element);
		++mArrSize;
	}

	template <typename Type>
	void Vector<Type>::pop_back()
	{
		--mArrSize;
		mArr[mArrSize].~Type();
	}

	template <typename Type>
	typename Vector<Type>::Iterator Vector<Type>::insert(ConstIterator it, ValueType&& element)
	{
		Iterator iter = &mArr[it - mArr];
		if (mArrSize == mInitSize)
		{
			mInitSize <<= 2;
			reallocate();
		}

		memmove(iter + 1, iter, (mArrSize - (it - mArr)) * sizeof(Type));

		(*iter) = element;
		++mArrSize;

		return iter;
	}

	template <typename Type>
	typename Vector<Type>::Iterator Vector<Type>::erase(typename Vector<Type>::ConstIterator first, typename Vector<Type>::ConstIterator last)
	{
		Iterator iter = &mArr[first - mArr];
		if (first == last)
			return iter;

		for (; first != last; ++first)
		{
			(*first).~Type();
		}

		memmove(iter, last, (mArrSize - (last - mArr)) * sizeof(Type));
		mArrSize -= last - first;

		return iter;
	}

	template <typename Type>
	void Vector<Type>::swap(Vector<Type>& other)
	{
		const size_t tmpSize = mArrSize;
		const size_t tmpInitSize = mInitSize;
		const Type* tmp = mArr;

		mArrSize = other.mArrSize;
		mInitSize = other.mInitSize;
		mArr = other.mArr;

		other.mArrSize = tmpSize;
		other.mInitSize = tmpInitSize;
		other.mArr = tmp;
	}

	template <typename Type>
	void Vector<Type>::clear()
	{
		for (size_t i = 0; i < mArrSize; ++i)
		{
			mArr[i].~Type();
		}

		mArrSize = 0;
	}
}