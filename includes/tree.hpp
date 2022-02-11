#ifndef TREE_HPP
#define TREE_HPP

namespace ft
{
	template <typename value_type>
	struct tree_node
	{
		value_type			value;

		enum { red, black }	color;

		tree_node			*left;
		tree_node			*right;
		tree_node			*parent;
	};

	template <typename T>
	class tree
	{
		public:
			typedef T						value_type;
			typedef tree_node<value_type>	node_type;
			typedef node_type*				node_ptr;

		private:
			node_ptr	root;


		public:
			tree(void)
			{}

			~tree(void)
			{}


	};
}

#endif
