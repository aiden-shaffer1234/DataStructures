
    
    // default zero parameter constructor
    template <typename T>
    Vector<T>::Vector() : theSize{0}, theCapacity{0}
    {
        array = nullptr;
    }

    // copy constructor
    template <typename T>
    Vector<T>::Vector(const Vector &rhs): theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, array{ nullptr }
    { 
        array = new T[ theCapacity ];
        for( int k = 0; k < theSize; ++k )
            array[ k ] = rhs.array[ k ];
    }

    // move constructor
    template <typename T>
    Vector<T>::Vector(Vector &&rhs) : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, array{ rhs.array }
    {
        rhs.array = nullptr;
        rhs.theSize = 0;
        rhs.theCapacity = 0;
    }

    // num elements with value of val
    template <typename T>
    Vector<T>::Vector(int num, const T& val) : theSize{num}, theCapacity{num}
    {
        array = new T[theCapacity];

        for (int i = 0; i < num; i++)
        {
            array[i] = val;
        }
        
    }
    // constructs with elements [start, end)
    template <typename T>
    Vector<T>::Vector(const_iterator start, const_iterator end)
    {
        theSize = 0;
        for (auto itr = start; itr != end; itr++)
        {
            theSize++;
        }
        
        theCapacity = theSize;
        array = new T[theCapacity];
        int i = 0;

        for (auto itr = start; itr != end; itr++)
        {
            array[i++] = *itr; 
        }
    }
    
    // destructor
    template <typename T>
    Vector<T>::~Vector()
    {
        delete [ ] array;
    }

    // operators

    // index operator
    template <typename T>
    T& Vector<T>::operator[](int index)
    {
        return array[ index ];

    }
    template <typename T>
    const T& Vector<T>::operator[](int index) const
    {
        return array[ index ];
    }

    // copy assignment operator
    template <typename T>
    const Vector<T>& Vector<T>::operator=(const Vector &rhs)
    {
        Vector<T> copy = rhs;			// calling copy constructor
        std::swap( *this, copy );
        return *this;
    }

    // move assignment operator
    template <typename T>
    Vector<T> & Vector<T>::operator=(Vector &&rhs)
    {
        std::swap( theSize, rhs.theSize );
        std::swap( theCapacity, rhs.theCapacity );
        std::swap( array, rhs.array );
        
        return *this;
    }

    // at function. safer than operator[]
    template <typename T>
    T& Vector<T>::at(int loc )
    {
        if(loc < 0 || loc >= theSize) 
            throw std::out_of_range("Index out of range");

        return array[loc];
    }
    template <typename T>
    const T& Vector<T>::at(int loc ) const
    {
        if(loc < 0 || loc >= theSize) 
            throw std::out_of_range("Index out of range");

        return array[loc];
    }
    
    // reference to the first element
    template <typename T>
    T& Vector<T>::front()
    {
        return array[0]; 
    } 
    
    template <typename T>
    const T& Vector<T>::front() const
    {
         return array[0]; 
    }
    
    // reference to the last element
    template <typename T>
    T& Vector<T>::back()
    {
         return array[theSize - 1]; 
    }
    template <typename T>
    const T & Vector<T>::back() const
    {
         return array[theSize - 1]; 
    } 

    // accessor member functions

    // number of elements
    template <typename T>
    int Vector<T>::size() const
    {
        return theSize;
    } 
    
    // capacity of vector
    template <typename T>
    int Vector<T>::capacity() const
    {
        return theCapacity;
    } 

    // check if list is empty
    template <typename T>
    bool Vector<T>::empty() const
    {
        return theSize == 0;
    } 

   
   
    // mutator member functions


    // delete all elements
    template <typename T>
    void Vector<T>::clear()
    {
        theSize = 0;
    } 
    
    // insert to the end
    template <typename T>
    void Vector<T>::push_back(const T & val)
    {
        if(theSize >= theCapacity)
            doubleCapacity();       

        array[theSize++] = val; 
    } 

    // delete last element
    template <typename T>
    void Vector<T>::pop_back()
    {
        theSize--;
    } 

    // resize vector
    template <typename T>
    void Vector<T>::resize(int num, T val)
    {
        if (num > theCapacity)
        {
            reserve(2*theCapacity);
        }
        
        for (int i = theSize; i < theCapacity; i++)
        {
            array[i] = val;
        }
        
        theSize = num;
    } 

    // reserve memory
    template <typename T>
    void Vector<T>::reserve(int newCapacity)
    {
        if( newCapacity < theSize )
            return;

        T *newArray = new T[ newCapacity ];

        for( int k = 0; k < theSize; ++k )
            newArray[k] = array[k];

        theCapacity = newCapacity;
        std::swap( array, newArray );
        delete [ ] newArray;
    }

    template <typename T>
    void Vector<T>::doubleCapacity()
    {
        if(theCapacity == 0) reserve(1);
        else                 reserve(theCapacity*2);
    }

    // print out all elements. ofc is deliminitor
    template <typename T>
    void Vector<T>::print(std::ostream& os, char ofc) const
    {
        auto itr = this->begin();
        if(itr != this->end()) os << *itr;

        itr++;
        for(; itr != this->end(); itr++)
        {
            os << ofc << *itr;            
        }
    } 

    // iterator support

    // iterator to first element
    template <typename T>
    T* Vector<T>::begin()
    {
        return &array[ 0 ]; 
    } 

    template <typename T>
    const T* Vector<T>::begin() const
    {
        return &array[ 0 ]; 
    }

    // end marker iterator
    template <typename T>
    T* Vector<T>::end()
    {
        return &array[ theSize ]; 
    }

    template <typename T>
    const T* Vector<T>::end() const
    {
        return &array[ theSize ]; 
    } 

    // insert val ahead of itr
    template <typename T>
    T* Vector<T>::insert(iterator itr, const T& val)
    {
        resize(theSize + 1);
        int i = 0;
        auto it = begin();

        while(it != itr)
        {
            it++;
            i++;
        }
        
        int index = i;
        for (; i < theSize - 1; i++)
        {
            array[i+1] = array[i];
        }

        array[index] = val;
        return itr + 1;
    }

    // erase one element WRONG
    template <typename T>
    T* Vector<T>::erase(iterator itr)
    {
        int i = 0;
        auto it = begin();

        while(it != itr)
        {
            it++;
            i++;
        }

        for (; i < theSize - 1; i++)
        {
            array[i] = array[i+1];
        }
        
        theSize--;
        return itr; // double check
    }

    // erase [start, end)
    template <typename T>
    T* Vector<T>::erase(iterator start, iterator end)
    {
        for (auto i = start; i != end; i++)
        {
            erase(start);
        }

        return end;
    }

    template <typename T>
    bool operator==(const Vector<T> & lhs, const Vector<T> &rhs)
    {
        if(lhs.size() != rhs.size()) return false;

        auto itrL = lhs.begin();
        auto itrR = rhs.begin();

        while(itrL != lhs.end())
        {
            if(*itrL++ != *itrR++) return false;
        }

        return true;
        
    }

    template <typename T>
    bool operator!=(const Vector<T> & lhs, const Vector<T> &rhs)
    {
        return !(lhs == rhs);
    }

    // overloading output operator
    template <typename T>
    std::ostream & operator<<(std::ostream &os, const Vector<T> &v){
        v.print(os, ' ');
        return os;
    }