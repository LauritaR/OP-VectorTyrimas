#ifndef VECTOR_H
#define VECTOR_H
template <class T>
class vect{
    public: 
    //member types
        typedef T value_type; 
        typedef T* iterator;
        typedef const T* const_iterator;
        typedef size_t size_type;
        typedef T& reference;
        typedef const T& const_reference;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const iterator> const_reverse_iterator;
        typedef std::ptrdiff_t difference_type;

     //member functions
        //constructors
        vect(){create();}//default

        explicit vect(size_type n, const T& t =T{}){create(n,t);}//constructor with initial size and value

        vect(const vect& v){create(v.begin(), v.end());}//copy constructor

        vect& operator=(const vect&);//copy assignment

        vect(vect&& v): data(v.data),avail(v.avail), limit(v.limit){v.data=v.avail=v.limit=nullptr;}//move cons

        vect& operator=(vect&&);//move assign

        vect(std::initializer_list<T> initList){create(initList.begin(),initList.end());}//constructor with initializer list

        template<class InputIterator>
        vect(InputIterator first, InputIterator last){create(first, last);}//constructor with range
        
        void assign(size_type n, const T&val){uncreate();create(n,val);}//assigns new values to the vector

        std::allocator<T> get_allocator() const{return alloc;}

    //element access
        reference operator[](size_type i ){return data[i];}//access element as index

        const_reference operator[](size_type i)const{return data[i];} //access elem at indx

        reference at(size_type i){if(i>=size()){throw std::out_of_range("Vector::at");}return data[i];}//access elem at inx with bounds checking

        const_reference at(size_t i)const{if(i>=size()){throw std::out_of_range("Vector::at");}return data[i];}//access elem and indx with bounds checking

        reference front(){return data[0];}//access first elem

        const_reference front()const{return data[0];}//access first elem

        reference back(){return data[size()-1];}//access last elem

        const_reference back()const{return data[size()-1];}//access last elem
      //iterators
        iterator begin() {return data;}//iterator to the beginning

        const_iterator begin() const{return data;}//iterator to the beginning 

        reverse_iterator rbegin(){return reverse_iterator(end());}//reverse iterator to the beginning

        const_reverse_iterator rbegin() const{return reverse_iterator(end());}//reverse iterator to the beginning

        iterator end() {return avail;}//iteartor to the end

        const_iterator end() const {return avail;}//iterator to the end

        reverse_iterator rend() {return reverse_iterator(begin());}// reverse iterator to the end

        const_reverse_iterator rend()const{return reverse_iterator(begin());}//reverse iterator to the end
 //capacity 
        bool empty() const{return size()==0;}//check if vector is empty

        size_type size() const{return avail-data;}// get the current size of the vector

        size_type max_size() const{return std::numeric_limits<size_t>::max();}//get the max possible size of the vector

        size_type capacity()const{return limit-data;}// get the current capacity of the vector

        void reserve(size_type  n){ if(n>capacity()) grow(n);}//reserve memory for n elem

        void shrink_to_fit()//shrink the capacity to fit the current size
        {
            iterator new_data = alloc.allocate(size());
            iterator new_avail = std::uninitialized_copy(data, avail, new_data);
            uncreate();
            data = new_data;
            avail = new_avail;
            limit = data + size();
        }
    //modifiers
        void clear(){return uncreate();}//clear the vector
        
        void push_back(const T& t){if(avail==limit)grow();unchecked_append(t);}//add an element to the end

        iterator insert(const_iterator pos, const T& value)//insert an element at a specific position
        {
            size_type i= pos-begin();
            if(avail==limit){grow();}
            iterator p=begin()+i;
            std::copy_backward(p, avail, avail+1);
            *p=value;
            ++avail;
            return p;
        }

        iterator erase(const_iterator pos)//erase an element at a specific position
        {
           iterator n= const_cast<iterator>(pos);
           std::copy(n+1,avail, n);
           alloc.destroy(--avail);
           return n;
        }

        iterator erase(const_iterator first,const_iterator last)//erase element at a range
        {
            if(first>=data && last<=avail &&first<last)
            {
            iterator dest = const_cast<iterator>(first);
            iterator src = const_cast<iterator>(last);
            while (src != avail) {
                *dest = std::move(*src);
                ++dest;
                ++src;
            }
            while (avail != dest) {
                alloc.destroy(--avail);
            }
            return const_cast<iterator>(first);
            }
            return avail;
        }

        void pop_back(){erase(end()-1);}//remove the last elem

        void resize(size_t count, const T& value)//resize the vector
        {
            if(count>size())
            {
                if(count>capacity())
                {
                    reserve(count);
                }
                for(size_t i=size(); i<count; i++)
                {
                    push_back(value);
                }
            }
            else if(count<size())
            {
                while(size()>count)
                {
                    pop_back();
                }
            }
        }

        void unchecked_append(const T& val){alloc.construct(avail++,val);}
     
        ~vect(){uncreate();}//destructor

        private:
        iterator data;
        iterator avail;
        iterator limit;

        std::allocator<T> alloc;
        void create();
        void create(size_type, const T&);
        void create(const_iterator, const_iterator);

        void uncreate();

        void grow();
        void grow(int);
        template<class InputIterator>
        void create(InputIterator first, InputIterator last)
        {
            data=alloc.allocate(last-first);
            limit=avail=std::uninitialized_copy(first,last,data);
        }
};

template <class T>
vect<T>& vect<T>::operator=(const vect& v)
{
    if(&v !=this)
        {
            uncreate();
            create(v.begin(), v.end());
        }
    return *this;
}

template<class T>
vect<T>& vect<T>::operator=(vect&& v)
{
    if (&v != this) {
            uncreate();
            data = v.data;
            avail = v.avail;
            limit = v.limit;
            v.data = v.avail = v.limit = nullptr;
        }
        return *this;
}
template <class T>
void vect<T>::create()
{
    data=avail=limit=nullptr;
}
template <class T>
void vect<T>::create(size_type n, const T& val)
{
    data=alloc.allocate(n);
    limit=avail=data+n;
    uninitialized_fill_n(data,limit,val);
}

template<class T>
void vect<T>::create(const_iterator i,const_iterator n)
{
    size_type new_size=n-i;
    data=alloc.allocate(new_size);
    limit=avail=std::uninitialized_copy(i,n,data);
}

template<class T>
void vect<T>::uncreate()
{
    if(data)
    {
        iterator it=avail;
        while(it!=data)
        alloc.destroy(--it);
    
    alloc.deallocate(data, limit-data);
    }
    data=avail=limit=nullptr;
}

template<class T>
void vect<T>::grow()
{
    size_type new_size=std::max(2*(limit-data),static_cast<difference_type>(1));
    iterator new_data=alloc.allocate(new_size);

    iterator new_avail=std::uninitialized_copy(data, avail,new_data);

    uncreate();

    data=new_data;
    avail=new_avail;
    limit=data+new_size;
}
template<class T>
void vect<T>::grow(int n)
{
    size_type new_size=n;
    iterator new_data=alloc.allocate(new_size);
    iterator new_avail=std::uninitialized_copy(data, avail,new_data);
    uncreate();
    data=new_data;
    avail=new_avail;
    limit=data+new_size;
}
template <class T>
bool operator==(const vect<T>& lhs, const vect<T>& rhs) {
    return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class T>
bool operator!=(const vect<T>& lhs, const vect<T>& rhs) {
    return !(lhs == rhs);
}

template <class T>
bool operator<(const vect<T>& lhs, const vect<T>& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class T>
bool operator<=(const vect<T>& lhs, const vect<T>& rhs) {
    return !(rhs < lhs);
}

template <class T>
bool operator>(const vect<T>& lhs, const vect<T>& rhs) {
    return rhs < lhs;
}

template <class T>
bool operator>=(const vect<T>& lhs, const vect<T>& rhs) {
    return !(lhs < rhs);
}
#endif