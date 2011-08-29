#ifndef BOX_H_INCLUDED
#define BOX_H_INCLUDED

#ifdef DEBUG
#	define BOX
#endif

#ifdef BOX

#include <boost/shared_ptr.hpp>

template<typename T>
class box
{
public:
	box(): p_(new T()) {}
	template<typename A1>
	box(A1 a1): p_(new T(a1)) {}
	template<typename A1,typename A2>
	box(A1 a1, A2 a2): p_(new T(a1,a2)) {}
	template<typename A1,typename A2,typename A3>
	box(A1 a1, A2 a2, A3 a3): p_(new T(a1,a2,a3)) {}
	template<typename A1,typename A2,typename A3,typename A4>
	box(A1 a1, A2 a2, A3 a3, A4 a4): p_(new T(a1,a2,a3,a4)) {}
	template<typename A1,typename A2,typename A3,typename A4,typename A5>
	box(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5): p_(new T(a1,a2,a3,a4,a5)) {}
	template<typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
	box(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6): p_(new T(a1,a2,a3,a4,a5,a6)) {}
	template<typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7>
	box(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7): p_(new T(a1,a2,a3,a4,a5,a6,a7)) {}
	template<typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8>
	box(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8): p_(new T(a1,a2,a3,a4,a5,a6,a7,a8)) {}

	typedef T* pointer;
	operator pointer() {return p_.get();}
	T& operator*() {return *p_;}
	T* operator->() {return p_.get();}

	typedef T const* const_pointer;
	operator const_pointer() const {return p_.get();}
	T const& operator*() const {return *p_;}
	T const* operator->() const {return p_.get();}

private:
	boost::shared_ptr<T> p_;
};

#else

template<typename T>
class box
{
public:
	box(): obj_() {}
	template<typename A1>
	box(A1 a1): obj_(a1) {}
	template<typename A1,typename A2>
	box(A1 a1, A2 a2): obj_(a1,a2) {}
	template<typename A1,typename A2,typename A3>
	box(A1 a1, A2 a2, A3 a3): obj_(a1,a2,a3) {}
	template<typename A1,typename A2,typename A3,typename A4>
	box(A1 a1, A2 a2, A3 a3, A4 a4): obj_(a1,a2,a3,a4) {}
	template<typename A1,typename A2,typename A3,typename A4,typename A5>
	box(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5): obj_(a1,a2,a3,a4,a5) {}
	template<typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
	box(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6): obj_(a1,a2,a3,a4,a5,a6) {}
	template<typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7>
	box(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7): obj_(a1,a2,a3,a4,a5,a6,a7) {}
	template<typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8>
	box(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8): obj_(a1,a2,a3,a4,a5,a6,a7,a8) {}

	typedef T* pointer;
	operator pointer() {return &obj_;}
	T& operator*() {return obj_;}
	T* operator->() {return &obj_;}

	typedef T const* const_pointer;
	operator const_pointer() const {return &obj_;}
	T const& operator*() const {return obj_;}
	T const* operator->() const {return &obj_;}

private:
	T obj_;
};

#endif

#endif //BOX_H_INCLUDED
