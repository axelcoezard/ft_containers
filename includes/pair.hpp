#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft
{
	template <class T1, class T2>
	struct pair
	{
		public:
			typedef T1	first_type;
			typedef T2	second_type;
		public:
			first_type	u;
			second_type	v;
		public:
			pair(first_type & u, second_type & v) : u(u), v(v) {};
			~pair(void) {};
	};

	template <class T1, class T2>
	pair<T1, T2>	make_pair(T1 u, T2 v)
	{
		pair<T1, T2>	npair(u, v);
		return (npair);
	}
}

#endif
