#ifndef VECTOR_H
#define VECTOR_H
#include <memory>
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
        vect(){create();}
        explicit vect(size_type n, const T& t =T{}){create(n,t);}
        vect(const vect& v){create(v.begin(), v.end());}
        vect& operator=(const vect&);
        vect(std::initializer_list<T> initList){create(initList.begin(),initList.end());}
        template<class InputIterator>
        vect(InputIterator first, InputIterator last){create(first, last);}
        //destructor
        ~vect(){uncreate();}
        void assign(size_type n, const T&val){uncreate();create(n,val);}
        std::allocator<T> get_allocator() const{return alloc;}
    //element access
        reference operator[](size_type i ){return data[i];}
        const_reference operator[](size_type i)const{return data[i];}
        reference at(size_type i)
        {
            if(i>=size())
            {
                throw std::out_of_range("Vector::at");
            }
            return data[i];
        }
        const_reference at(size_t i)const
        {
            if(i>=size())
            {
                throw std::out_of_range("Vector::at");
            }
            return data[i];
        }

        reference front(){return data[0];}
        const_reference front()const{return data[0];}
        reference back(){return data[size()-1];}
        const_reference back()const{return data[size()-1];}
      //iterators
        iterator begin() {return data;}
        const_iterator begin() const{return data; }
        reverse_iterator rbegin(){return reverse_iterator(end());}
        const_reverse_iterator rbegin() const{return reverse_iterator(end());}
        iterator end() {return avail;}
        const_iterator end() const {return avail;}
        reverse_iterator rend() {return reverse_iterator(begin());}
        const_reverse_iterator rend()const{return reverse_iterator(begin());}
 //capacity 
        bool empty() const{return size()==0;}
        size_type size() const{return avail-data;}
        size_t max_size() const{return std::numeric_limits<size_t>::max();}
        size_t capacity()const{return limit-data;}
        void reserve(size_type  n){ if(n>capacity()) grow(n);}
        void shrink_to_fit()
        {
            iterator new_data = alloc.allocate(size());
            iterator new_avail = std::uninitialized_copy(data, avail, new_data);
            uncreate();
            data = new_data;
            avail = new_avail;
            limit = data + size();
        }
    //modifiers
        void clear(){return uncreate();}
        
        void push_back(const T& t)
        {
            if(avail==limit)
                grow();
            unchecked_append(t);
        }
        
        iterator insert(const_iterator pos, const T& value)
        {
            size_type i= pos-begin();
            if(avail==limit)
            {
                grow();
            }
            iterator p=begin()+i;
            std::copy_backward(p, avail, avail+1);
            *p=value;
            ++avail;
            return p;
        }

        iterator erase(const_iterator pos)
        {
           iterator n= const_cast<iterator>(pos);
           std::copy(n+1,avail, n);
           alloc.destroy(--avail);
           return n;
        }
        iterator erase(const_iterator first,const_iterator last)
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

        void pop_back(){erase(end()-1);}

        void resize(size_t count, const T& value)
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
vect<T>& vect<T>::operator=(const vect& rhs)//rhs is right-hand side
{
    if(&rhs !=this)
        {
            uncreate();
            create(rhs.begin(), rhs.end());
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
    uninitialized_fill(data,limit,val);
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