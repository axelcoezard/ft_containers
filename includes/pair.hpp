#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft
{
	template <class T1, class T2>
	class pair
	{
		public:
			typedef T1	first_type;
			typedef T2	second_type;

			first_type	first;
			second_type	second;

			pair(void) {}

			pair(const first_type& u, const second_type& v) : first(u), second(v) {};

			template <class T1, class T2>
			pair(const pair<T1, T2>& pair) : first(pair.first), second(pair.second) {}

			~pair(void) {};
	};

	template <class T1, class T2>
	bool operator==(const pair<T1, T2> lhs, const pair<T1, T2> rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template <class T1, class T2>
	bool operator!=(const pair<T1, T2> lhs, const pair<T1, T2> rhs)
	{
		return !(lhs == rhs);
	}

	template <class T1, class T2>
	bool operator<(const pair<T1, T2> lhs, const pair<T1, T2> rhs)
	{}

	template <class T1, class T2>
	bool operator>(const pair<T1, T2> lhs, const pair<T1, T2> rhs)
	{}

	template <class T1, class T2>
	bool operator<=(const pair<T1, T2> lhs, const pair<T1, T2> rhs)
	{}

	template <class T1, class T2>
	bool operator>=(const pair<T1, T2> lhs, const pair<T1, T2> rhs)
	{}

	template <class T1, class T2>
	pair<T1, T2> make_pair(T1 u, T2 v)
	{
		return (pair<T1, T2>(u, v));
	}
}

#endif
