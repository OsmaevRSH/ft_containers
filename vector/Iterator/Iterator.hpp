template<class T>
class Iterator
{
	protected:
		T *ptr;
	public:
		Iterator() {}
		Iterator(T *ptr) : ptr(ptr) {}
		Iterator(const Iterator &copy) : ptr(copy.ptr) {}
		Iterator &operator=(const Iterator &copy)
		{
			if (*this != copy)
			{
				ptr = copy.ptr;
			}
			return *this;
		}
		virtual ~Iterator() {}

		friend bool operator==(const Iterator &left, const Iterator &right) { return left.ptr == right.ptr; }
		friend bool operator!=(const Iterator &left, const Iterator &right) { return left.ptr != right.ptr; }
		friend bool operator>(const Iterator &left, const Iterator &right) { return left.ptr > right.ptr; }
		friend bool operator<(const Iterator &left, const Iterator &right) { return left.ptr < right.ptr; }
		friend bool operator>=(const Iterator &left, const Iterator &right) { return left.ptr >= right.ptr; }
		friend bool operator<=(const Iterator &left, const Iterator &right) { return left.ptr <= right.ptr; }

		T &operator*() { return *ptr; }
		T *operator->() { return ptr; }
		T &operator[](int n) { return *(ptr + n); }

		Iterator &operator++()
		{
			++ptr;
			return *this;
		}

		Iterator &operator--()
		{
			--ptr;
			return *this;
		}

		Iterator operator++(int)
		{
			Iterator save(*this);
			++ptr;
			return save;
		}

		T operator--(int)
		{
			Iterator save(*this);
			--ptr;
			return save;
		}

		friend Iterator operator+(const Iterator &left, int n)
		{
			Iterator save(left);
			save.ptr += n;
			return save;
		}
		friend Iterator operator+(int n, const Iterator &right)
		{
			return right + n;
		}
		friend Iterator operator-(const Iterator &left, int n)
		{
			Iterator save(left);
			save.ptr -= n;
			return save;
		}
		friend Iterator operator-(const Iterator &left, const Iterator &right)
		{
			Iterator save(left);
			save.ptr += right.ptr;
			return save;
		}

		Iterator &operator+=(int n)
		{
			ptr += n;
			return *this;
		}
		Iterator &operator-=(int n)
		{
			ptr -= n;
			return *this;
		}
};


template<class T>
class Const_Iterator : public Iterator<T>
{
	public:
		Const_Iterator(T *ptr) : Iterator<T>(ptr) {}
		Const_Iterator(const Const_Iterator &copy) : Iterator<T>(copy) {}
		Const_Iterator(Iterator<T> iterator) : Iterator<T>(iterator.operator->()) {}
		Const_Iterator &operator=(const Const_Iterator &copy)
		{
			if (*this != copy)
			{
				this->ptr = copy.ptr;
			}
			return *this;
		}
		virtual ~Const_Iterator() {}

		const T &operator*() { return *(this->ptr); }
		const T *operator->() { return this->ptr; }
		const T &operator[](int n) { return *(this->ptr + n); }
};


template<class T>
class Reverse_Iterator
{
	protected:
		T *ptr;

	public:
		Reverse_Iterator(T *ptr) : ptr(ptr) {}
		Reverse_Iterator(const Reverse_Iterator &copy) : ptr(copy.ptr) {}
		Reverse_Iterator &operator=(const Reverse_Iterator &copy)
		{
			if (*this != copy)
			{
				ptr = copy.ptr;
			}
			return *this;
		}
		virtual ~Reverse_Iterator() {}

		friend bool operator==(const Reverse_Iterator &left, const Reverse_Iterator &right) { return left.ptr == right.ptr; }
		friend bool operator!=(const Reverse_Iterator &left, const Reverse_Iterator &right) { return left.ptr != right.ptr; }
		friend bool operator>(const Reverse_Iterator &left, const Reverse_Iterator &right) { return left.ptr > right.ptr; }
		friend bool operator<(const Reverse_Iterator &left, const Reverse_Iterator &right) { return left.ptr < right.ptr; }
		friend bool operator>=(const Reverse_Iterator &left, const Reverse_Iterator &right) { return left.ptr >= right.ptr; }
		friend bool operator<=(const Reverse_Iterator &left, const Reverse_Iterator &right) { return left.ptr <= right.ptr; }

		T &operator*() { return *ptr; }
		T *operator->() { return ptr; }
		T &operator[](int n) { return *(ptr - n); }

		Reverse_Iterator &operator++()
		{
			--ptr;
			return *this;
		}

		Reverse_Iterator &operator--()
		{
			++ptr;
			return *this;
		}

		Reverse_Iterator operator++(int)
		{
			Reverse_Iterator save(*this);
			--ptr;
			return save;
		}

		T operator--(int)
		{
			Reverse_Iterator save(*this);
			++ptr;
			return save;
		}

		friend Reverse_Iterator operator+(const Reverse_Iterator &left, int n)
		{
			Reverse_Iterator save(left);
			save.ptr -= n;
			return save;
		}
		friend Reverse_Iterator operator+(int n, const Reverse_Iterator &right)
		{
			return right - n;
		}
		friend Reverse_Iterator operator-(const Reverse_Iterator &left, int n)
		{
			Reverse_Iterator save(left);
			save.ptr += n;
			return save;
		}
		friend Reverse_Iterator operator-(const Reverse_Iterator &left, const Reverse_Iterator &right)
		{
			Reverse_Iterator save(left);
			save.ptr -= right.ptr;
			return save;
		}

		Reverse_Iterator &operator+=(int n)
		{
			ptr -= n;
			return *this;
		}
		Reverse_Iterator &operator-=(int n)
		{
			ptr += n;
			return *this;
		}
};


template<class T>
class Const_Reverse_Iterator : public Reverse_Iterator<T>
{
	public:
		Const_Reverse_Iterator(Reverse_Iterator<T> iterator) : Reverse_Iterator<T>(iterator.operator->()) {}
		Const_Reverse_Iterator(T *ptr) : Iterator<T>(ptr) {}
		Const_Reverse_Iterator(const Const_Reverse_Iterator &copy) : Reverse_Iterator<T>(copy) {}
		Const_Reverse_Iterator &operator=(const Const_Reverse_Iterator &copy)
		{
			if (*this != copy)
			{
				this->ptr = copy.ptr;
			}
			return *this;
		}
		virtual ~Const_Reverse_Iterator() {}

		const T &operator*() { return *(this->ptr); }
		const T *operator->() { return this->ptr; }
		const T &operator[](int n) { return *(this->ptr - n); }
};
