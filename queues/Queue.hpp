
    
    template<typename T>
    Queue<T>::Queue()
    {}

    template<typename T>
    Queue<T>::~Queue()
    {
        while(size() != 0)
        {
            pop();
        }
    }

    template<typename T>
    Queue<T>::Queue(const Queue<T> &rhs) : queueList(rhs.queueList)
    {}

    template<typename T>
    Queue<T>::Queue(Queue<T> &&rhs) : queueList(std::move(rhs.queueList))
    {}

    template<typename T>
    Queue<T>& Queue<T>::operator=(const Queue<T> &rhs)
    {
        Queue<T> temp = rhs;
        std::swap(*this, temp);
        return *this;
    }

    template<typename T>
    Queue<T>& Queue<T>::operator=(Queue<T> &&rhs)
    {
        std::swap(queueList, rhs.queueList);
        return *this;
    }

    template<typename T>
    T& Queue<T>::back()
    {
        return queueList.back();
    }

    template<typename T>
    const T& Queue<T>::back() const
    {
        return queueList.back();
    }

    template<typename T>
    bool Queue<T>::empty() const
    {
        return queueList.size() == 0;
    }

    template<typename T>
    T& Queue<T>::front()
    {
        return queueList.front();
    }

    template<typename T>
    const T& Queue<T>::front() const
    {
        return queueList.front();
    }

    template<typename T>
    void Queue<T>::pop()
    {
        queueList.pop_front();
    }

    template<typename T>
    void Queue<T>::push(const T& val)
    {
        queueList.push_back(val);
    }

    template<typename T>
    void Queue<T>::push(T&& val)
    {
        queueList.push_back(std::move(val));
    }

    template<typename T>
    int Queue<T>::size() const
    {
        return queueList.size();
    }

