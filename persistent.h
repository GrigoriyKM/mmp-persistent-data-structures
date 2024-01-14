#ifndef PERSISTENT_H
#define PERSISTENT_H

#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <utility>

template <typename T>
struct Node
{
	Node<T>* left_child{};
	Node<T>* right_child{};
	T value{};
};

template <typename KeyType, typename ValueType>
struct AA_node
{
	KeyType key{};
	ValueType value{};
	AA_node<KeyType, ValueType>* left{};
	AA_node<KeyType, ValueType>* right{};

	AA_node(KeyType k, ValueType v) : key(k), value(v), left(nullptr), right(nullptr) {}
};

template <typename T>
struct DL_node
{
	T value{}; 
	DL_node<T>* prev{};
	DL_node<T>* next{};

	//DL_node(int d) : data(d), prev(nullptr), next(nullptr) {}
};

template <typename T>
class PersistentArray
{
private:

	// base version
	T* base{};

	// size of base version
	int size{};

	// container for roots of versions
	std::vector<Node<T>*> versions{};

	std::vector<std::pair<int, int>> parent_children_relation{};

	// recursive function to build tree with leafs as elemnts of _array in [_l..._r] and _node as root of version
	void buildTree(Node<T>* _node, T* _array, int _left_border, int _right_border);

	// recursive function to add new version by changing one value in one of previous version
	void add(Node<T>* _to, Node<T>* _from, int _left_border, int _right_border, int _position, T _new_value);

	// recursive function to get element of specific node
	T get(Node<T>* _node, int _left_border, int _right_border, int _position);

	// recursive function to count leaves in a tree
	int countLeaves(Node<T>* _node);

	// print from [_left] to [_right] 
	void printSlice(T* _arr, int _left, int _right);

public:

	// constructor with empty array of _size * elements
	PersistentArray(int _size);

	// constructor with _array of _size * elements
	PersistentArray(T* _arr, int _size);

	// destructor
	~PersistentArray();

	// set element to base version
	void setElementToBase(int _index, T _value);

	// change element by index in a specific version with new value  
	void changeVersion(int _number_of_version, int _change_index, T _new_value);

	// add new version by changing one value in one of previous version
	void addVersion(int _root_position, int _change_inde, T _new_value);

	// print all versions as a table
	void printAllVersions();

	// get size of a specific version
	int versionSize(int _number_of_version);

	// get a specific version as array
	T* getArray(int _number_of_version);

	// delete element in a specific version
	void deleteElement(int _root_position, int _delete_index);

	// insert a new value in a specific version
	void insertElement(int _root_position, int _insert_index, T _new_value);

	// get a root of specific version
	Node<T>* getVersion(int _number_of_version);
	
	// get number of versions
	int sizeVersions();
};

template <typename T>
class PersistentDoublyLinkedList
{
private:

	// base version
	DL_node<T>* base;

	// size of base version
	int size{};

	// container for roots of versions
	std::vector<Node<T>*> versions{};

	std::vector<std::pair<int, int>> parent_children_relation{};

	// recursive function to build tree with leafs as elemnts of _array in [_l..._r] and _node as root of version
	void buildTree(Node<T>* _node, DL_node<T>* _list_head, int _left_border, int _right_border);

	// recursive function to add new version by changing one value in one of previous version
	void add(Node<T>* _to, Node<T>* _from, int _left_border, int _right_border, int _position, T _new_value);

	// recursive function to get element of specific node
	T get(Node<T>* _node, int _left_border, int _right_border, int _position);

	// making a single node with data and assign it to base
	void initDL(T _data);

	// recursive function to count leaves in a tree
	int countLeaves(Node<T>* _node);

public:

	// constructor that creats one node with _data in it
	PersistentDoublyLinkedList(T _data);

	// constructor that creates double linked list from array
	PersistentDoublyLinkedList(T* _arr, int _size);

	// constructor that takes _head as base
	PersistentDoublyLinkedList(DL_node<T>* _head);

	// destructor
	~PersistentDoublyLinkedList();

	// adding data to end
	void append(T _data);

	// print from [_left] to [_right]
	void printSlice(DL_node<T>* _head, int _left, int _right);

	// get size of a specific DL_list
	int getSize(DL_node<T>* _head);

	// get element by index in DL list
	T getElement(DL_node<T>* _head, int _index);

	// change element by index in a specific version with new value  
	void changeVersion(int _number_of_version, int _new_position, T _new_value);

	// add new version by changing one value in one of previous version
	void addVersion(int _root_position, int _new_position, T _new_value);

	// print all versions as a table
	void printAllVersions();

	// get size of a specific version
	int versionSize(int _number_of_version);

	// get a specific version as array
	DL_node<T>* getList(int _number_of_version);

	// delete element in a specific version
	void deleteElement(int _root_position, int _delete_index);

	// insert a new value in a specific version
	void insertElement(int _root_position, int _insert_index, T _new_value);

	// get a root of specific version
	Node<T>* getVersion(int _number_of_version);

	// get number of versions
	int sizeVersions();
};

template <typename KeyType, typename ValueType>
class PersistentAssociativeArray
{
private:
	AA_node<KeyType, ValueType>* base{};
	std::vector<Node<ValueType>*> versions{};
	std::vector<Node<KeyType>*> key_versions{};
	std::vector<KeyType> keys{};
	std::vector<std::pair<int, int>> parent_children_relation{};

	void buildTreeValue(Node<ValueType>*, AA_node<KeyType, ValueType>*, int, int, std::vector<KeyType>);
	void buildTreeKey(Node<KeyType>*, AA_node<KeyType, ValueType>*, int, int, std::vector<KeyType>);

	template <typename X>
	void add(Node<X>*, Node<X>*, int, int, int, X);
	void addValue(Node<ValueType>*, Node<ValueType>*, int, int, int, ValueType);
	void addKey(Node<KeyType>*, Node<KeyType>*, int, int, int, KeyType);

	template <typename X>
	X get(Node<X>*, int, int, int);
	ValueType getValue(Node<ValueType>*, int, int, int);
	KeyType getKey(Node<KeyType>*, int, int, int);

	int countLeaves(Node<ValueType>* _node);
	AA_node<KeyType, ValueType>* insertRecursive(AA_node<KeyType, ValueType>*, KeyType, ValueType, std::vector<KeyType>);
	AA_node<KeyType, ValueType>* searchRecursive(AA_node<KeyType, ValueType>*, KeyType, std::vector<KeyType>);
	int sizeRecursive(AA_node<KeyType, ValueType>*);
	void printSliceRecursive(AA_node<KeyType, ValueType>*, int, int);
	void printKeys();
public:
	PersistentAssociativeArray(AA_node<KeyType, ValueType>*);
	PersistentAssociativeArray(KeyType, ValueType);
	PersistentAssociativeArray(KeyType*, ValueType*, int);
	~PersistentAssociativeArray();

	void setElementToBase(KeyType, ValueType);
	ValueType getElement(AA_node<KeyType, ValueType>*, KeyType);
	ValueType getElementByIndex(AA_node<KeyType, ValueType>*, int, std::vector<KeyType>);
	void addVersion(int, KeyType, ValueType);
	void printSlice(AA_node<KeyType, ValueType>*, int, int);
	void printAllVersions();
	void changeVersion(int, KeyType, ValueType);
	int versionSize(int);
	int getSize(AA_node<KeyType, ValueType>*);
	AA_node<KeyType, ValueType>* getAssociativeArray(int);
	void deleteElement(int, KeyType);
	void insertElement(int, int, KeyType, ValueType);
	Node<ValueType>* getVersion(int _number_of_version);
	// get number of versions
	int sizeVersions();
};

template <typename ValueType>
class Convert
{
private:

	// recursive function to insert by key with value
	//static AA_node<std::string, ValueType>* insertRecursive(AA_node<std::string, ValueType>*, std::string, ValueType, std::vector<KeyType>);

	// recursive function to get element of specific node
	static ValueType get(Node<ValueType>* _node, int _left_border, int _right_border, int _position);

	static int nodeSize(Node<ValueType>* _node);

public:
	// TODO : _version_size in deep

	// fuction that creates an object of PersistentArray class from tree
	static PersistentArray<ValueType> toArray(Node<ValueType>* _version);

	// fuction that creates an object of PersistentDoublyLinkedList class from tree
	static PersistentDoublyLinkedList<ValueType> toDLList(Node<ValueType>* _version);

	// fuction that creates an object of PersistentAssociativeArray class from tree
	template<typename KeyType>
	static PersistentAssociativeArray<KeyType, ValueType> toAssociativeArray(Node<ValueType>* _version, KeyType* _keys);
};


#endif // LIBRARY_H
//std::cout << "\n";


template<typename KeyType, typename ValueType>
inline void PersistentAssociativeArray<KeyType, ValueType>::buildTreeValue(Node<ValueType>* _node, AA_node<KeyType, ValueType>* _root, int _left, int _right, std::vector<KeyType> _keys_variant)
{
	//std::cout << "\nin build with: l = " << _left << " r = " << _right << "\n";
	//printSlice(_root, _left, _right);

	if (_left == _right)
	{
		_node->value = getElementByIndex(_root, (_left - 1), _keys_variant);
		//std::cout << "in if\t" << _node->value << "\n";
	}
	else
	{
		int middle = (_left + _right) / 2; //std::cout << "m = " << middle << "\n";
		_node->left_child = new Node<ValueType>(); //std::cout << "\nmaking left child";
		buildTreeValue(_node->left_child, _root, _left, middle, _keys_variant);
		_node->right_child = new  Node<ValueType>(); //std::cout << "\nmaking right child";
		buildTreeValue(_node->right_child, _root, middle + 1, _right, _keys_variant);
	}
}

template<typename KeyType, typename ValueType>
inline void PersistentAssociativeArray<KeyType, ValueType>::buildTreeKey(Node<KeyType>* _node, AA_node<KeyType, ValueType>* _root, int _left, int _right, std::vector<KeyType> _keys_variant)
{
	//std::cout << "\nin build with: l = " << _left << " r = " << _right << "\n";
	//printSlice(_root, _left, _right);

	if (_left == _right)
	{
		_node->value = _keys_variant.at(_left - 1);
		//std::cout << "in if\t" << _node->value << "\n";
	}
	else
	{
		int middle = (_left + _right) / 2; //std::cout << "m = " << middle << "\n";
		_node->left_child = new Node<KeyType>(); //std::cout << "\nmaking left child";
		buildTreeKey(_node->left_child, _root, _left, middle, _keys_variant);
		_node->right_child = new  Node<KeyType>(); //std::cout << "\nmaking right child";
		buildTreeKey(_node->right_child, _root, middle + 1, _right, _keys_variant);
	}
}

template<typename KeyType, typename ValueType>
inline void PersistentAssociativeArray<KeyType, ValueType>::addValue(Node<ValueType>* _to, Node<ValueType>* _from, int _left_border, int _right_border, int _position, ValueType _new_value)
{
	return add(_to, _from, _left_border, _right_border, _position, _new_value);
}

template<typename KeyType, typename ValueType>
inline void PersistentAssociativeArray<KeyType, ValueType>::addKey(Node<KeyType>* _to, Node<KeyType>* _from, int _left_border, int _right_border, int _position, KeyType _new_key)
{
	return add(_to, _from, _left_border, _right_border, _position, _new_key);
}

template<typename KeyType, typename ValueType>
inline ValueType PersistentAssociativeArray<KeyType, ValueType>::getValue(Node<ValueType>* _node, int _left_border, int _right_border, int _position)
{
	return get(_node, _left_border, _right_border, _position);
}

template<typename KeyType, typename ValueType>
inline KeyType PersistentAssociativeArray<KeyType, ValueType>::getKey(Node<KeyType>* _node, int _left_border, int _right_border, int _position)
{
	return get(_node, _left_border, _right_border, _position);
}

template<typename KeyType, typename ValueType>
inline int PersistentAssociativeArray<KeyType, ValueType>::countLeaves(Node<ValueType>* _node)
{
	if (_node == nullptr)
	{
		return 0;
	}

	// the node is a leaf
	if (_node->left_child == nullptr && _node->right_child == nullptr)
	{
		return 1;
	}

	int left_count = countLeaves(_node->left_child);
	int right_count = countLeaves(_node->right_child);

	return left_count + right_count;
}

template<typename KeyType, typename ValueType>
inline AA_node<KeyType, ValueType>* PersistentAssociativeArray<KeyType, ValueType>::insertRecursive(AA_node<KeyType, ValueType>* _root, KeyType _key, ValueType _value, std::vector<KeyType> _keys_variant)
{
	// Empty case
	if (_root == nullptr)
	{
		return new AA_node<KeyType, ValueType>(_key, _value);
	}

	//auto root_size = getSize(_root);

	//std::vector<KeyType> keys_temp{};
	//for (size_t i = 0; i < root_size; i++)
	//{
		//keys_temp.push_back(getKey(key_versions.at(_version_id), 1, root_size, i + 1));
		//std::cout << keys_temp[i] << "\t";
	//}

	//int key_index0{};
	//for (int i = 0; i < keys_temp.size(); i++)
	//{
		//if (_key == keys_temp.at(i))
		//{
			//key_index0 = i;
			//break;
		//}
	//}

	//std::cout << "key_index0 = " << key_index0 << "\t";

	int key_index{};
	for (int i = 0; i < _keys_variant.size(); i++)
	{
		if (_key == _keys_variant.at(i))
		{
			key_index = i;
			break;
		}
	}
	//std::cout << "key_index = " << key_index << "\n";

	int root_key_index{};
	for (int i = 0; i < _keys_variant.size(); i++)
	{
		if (_root->key == _keys_variant.at(i))
		{
			root_key_index = i;
			break;
		}
	}


	// Insert before
	if (key_index < root_key_index)
	{
		_root->left = insertRecursive(_root->left, _key, _value, _keys_variant);
	}
	else if (key_index > root_key_index) // Insert after
	{
		_root->right = insertRecursive(_root->right, _key, _value, _keys_variant);
	}
	else // Update case
	{
		_root->value = _value;
	}

	return _root;
}

template<typename KeyType, typename ValueType>
inline AA_node<KeyType, ValueType>* PersistentAssociativeArray<KeyType, ValueType>::searchRecursive(AA_node<KeyType, ValueType>*_root, KeyType _key, std::vector<KeyType> _keys_variant)
{
	if (_root == nullptr || _root->key == _key)
	{
		return _root;
	}

	int key_index{};
	for (int i = 0; i < _keys_variant.size(); i++)
	{
		if (_key == _keys_variant.at(i))
		{
			key_index = i;
			break;
		}
	}

	int root_key_index{};
	for (int i = 0; i < _keys_variant.size(); i++)
	{
		if (_root->key == _keys_variant.at(i))
		{
			root_key_index = i;
			break;
		}
	}

	if (key_index < root_key_index)
	{
		return searchRecursive(_root->left, _key, _keys_variant);
	}

	return searchRecursive(_root->right, _key, _keys_variant);
}

template<typename KeyType, typename ValueType>
inline int PersistentAssociativeArray<KeyType, ValueType>::sizeRecursive(AA_node<KeyType, ValueType>* _root)
{
	if (_root == nullptr)
	{
		return 0;
	}

	return 1 + sizeRecursive(_root->left) + sizeRecursive(_root->right);
}

template<typename KeyType, typename ValueType>
inline void PersistentAssociativeArray<KeyType, ValueType>::printSliceRecursive(AA_node<KeyType, ValueType>* _root, int _left, int _right)
{
	// Empty case
	if (_root == nullptr)
	{
		return;
	}

	int key_index{};
	for (int i = 0; i < keys.size(); i++)
	{
		if (_root->key == keys.at(i))
		{
			key_index = i;
			break;
		}
	}
	key_index += 1;

	// Key is in the range of left and right
	if (key_index >= _left && key_index <= _right)
	{
		std::cout << _root->key << " : " << _root->value << std::endl;
	}

	if (key_index > _right) // Left subtree case
	{
		printSliceRecursive(_root->left, _left, _right);
	}
	else if (key_index < _left) // Right subtree case
	{
		printSliceRecursive(_root->right, _left, _right);
	}
	else //  Key is in the range of left and right
	{
		printSliceRecursive(_root->left, _left, _right);
		printSliceRecursive(_root->right, _left, _right);
	}

}

template<typename KeyType, typename ValueType>
inline PersistentAssociativeArray<KeyType, ValueType>::PersistentAssociativeArray(AA_node<KeyType, ValueType>* _root)
{
	if (_root == nullptr)
	{
		std::cerr << "Empty Associative Array!!!\n";
	}

	this->base = _root;
}

template<typename KeyType, typename ValueType>
inline PersistentAssociativeArray<KeyType, ValueType>::PersistentAssociativeArray(KeyType _key, ValueType _value)
{
	base = new AA_node<KeyType, ValueType>(_key, _value);
	keys.push_back(_key);

	versions.push_back(new Node<ValueType>());
	key_versions.push_back(new Node<KeyType>());

	int left_border = 1;
	int right_border = 1;

	buildTreeValue(versions.at(0), base, left_border, right_border, keys);
	buildTreeKey(key_versions.at(0), base, left_border, right_border, keys);

	std::pair<int, int> temp = { -1, versions.size() - 1 };
	parent_children_relation.push_back(temp);
}

template<typename KeyType, typename ValueType>
inline PersistentAssociativeArray<KeyType, ValueType>::PersistentAssociativeArray(KeyType* _keys_arr, ValueType* _arr, int _size)
{
	base = nullptr;

	versions.push_back(new Node<ValueType>());
	key_versions.push_back(new Node<KeyType>());

	for (int i = 0; i < _size; i++)
	{
		setElementToBase(_keys_arr[i], _arr[i]);
		//keys.push_back(_keys_arr[i]);
	}

	int left_border = 1;
	int right_border = _size;

	buildTreeValue(versions.at(0), base, left_border, right_border, keys);
	buildTreeKey(key_versions.at(0), base, left_border, right_border, keys);

	std::pair<int, int> temp = { -1, versions.size() - 1 };
	parent_children_relation.push_back(temp);
}

template<typename KeyType, typename ValueType>
inline PersistentAssociativeArray<KeyType, ValueType>::~PersistentAssociativeArray()
{
	for (auto nodePtr : versions)
	{
		delete nodePtr;
	}
}

template<typename KeyType, typename ValueType>
inline void PersistentAssociativeArray<KeyType, ValueType>::setElementToBase(KeyType _key, ValueType _value)
{
	keys.push_back(_key);

	base = insertRecursive(base, _key, _value, keys); 
	//std::cout << "SETB\tK = " << _key << " V = " << _value << "\n";
	
	int left_border = 1;
	int right_border = getSize(base);

	//printSlice(base, left_border, right_border);

	buildTreeValue(versions.at(0), base, left_border, right_border, keys);
	buildTreeKey(key_versions.at(0), base, left_border, right_border, keys);
}

template<typename KeyType, typename ValueType>
inline ValueType PersistentAssociativeArray<KeyType, ValueType>::getElement(AA_node<KeyType, ValueType>* _root, KeyType _key)
{
	AA_node<KeyType, ValueType>* node = searchRecursive(_root, _key);

	if (node != nullptr)
	{
		return node->value;
	}

	return -1;
}

template<typename KeyType, typename ValueType>
inline ValueType PersistentAssociativeArray<KeyType, ValueType>::getElementByIndex(AA_node<KeyType, ValueType>* _root, int _key_index, std::vector<KeyType> _keys_variant)
{
	KeyType key = _keys_variant.at(_key_index);

	AA_node<KeyType, ValueType>* node = searchRecursive(_root, key, _keys_variant);

	if (node != nullptr)
	{
		return node->value;
	}

	return -1;
}

template<typename KeyType, typename ValueType>
inline void PersistentAssociativeArray<KeyType, ValueType>::addVersion(int _root_position, KeyType _key, ValueType _new_value)
{
	int position{};
	for (size_t i = 0; i < keys.size(); i++)
	{
		if (_key == keys.at(i))
		{
			position = i;
		}
	}

	_root_position += 1;
	position += 1;

	if (_root_position > versions.size())
	{
		return;
	}

	int l = 1;
	int r = versionSize(_root_position);

	if (position > r)
	{
		return;
	}

	versions.push_back(new Node<ValueType>());
	addValue(versions.back(), versions.at(_root_position - 1), l, r, position, _new_value);

	auto N = new Node<KeyType>();
	N = key_versions.at(_root_position - 1);
	key_versions.push_back(N);


	std::pair<int, int> temp = { _root_position - 1, versions.size() - 1 };
	parent_children_relation.push_back(temp);
}

template<typename KeyType, typename ValueType>
inline void PersistentAssociativeArray<KeyType, ValueType>::printSlice(AA_node<KeyType, ValueType>* _current, int _left, int _right)
{
	// Empty case
	if (_current == nullptr)
	{
		return;
	}

	int key_index{};
	for (int i = 0; i < keys.size(); i++)
	{
		if (_current->key == keys.at(i))
		{
			key_index = i;
		}
	}
	key_index += 1;

	// Key is in the range of left and right
	if (key_index >= _left && key_index <= _right)
	{
		std::cout << _current->key << " : " << _current->value << std::endl;
	}

	if (key_index > _right) // Left subtree case
	{
		printSliceRecursive(_current->left, _left, _right);
	}
	else if (key_index < _left) // Right subtree case
	{
		printSliceRecursive(_current->right, _left, _right);
	}
	else //  Key is in the range of left and right
	{
		printSliceRecursive(_current->left, _left, _right);
		printSliceRecursive(_current->right, _left, _right);
	}
}

template<typename KeyType, typename ValueType>
inline void PersistentAssociativeArray<KeyType, ValueType>::printAllVersions()
{
	for (size_t i = 0; i < versions.size(); i++)
	{
		auto version_size = versionSize(i + 1);
		std::cout << "Version [" << i << "]: \t";
		std::cout << "Parent ID: [" << parent_children_relation[i].first << "]\t";
		std::cout << "{";
		for (int j = 1; j < version_size + 1; j++)
		{
			//std::cout << "'" << keys.at(j - 1) << "' : '";
			std::cout << "'" << getKey(key_versions.at(i), 1, version_size, j) << "' : '";
			//std::cout << "n = " << number_of_elements << " i = " << i << " j = " << j << " ";
			std::cout << getValue(versions.at(i), 1, version_size, j);
			if (j < version_size)
			{
				std::cout << "', ";
			}
			else
			{
				std::cout << "'";
			}
		}
		//std::cout << "\tParent ID: " << parent_children_relation[i].first << " Children ID: " << parent_children_relation[i].second;
		//std::cout << "VS: " << versions.size() << " KVS: " << key_versions.size() << "\t";
		std::cout << "}\n";
	}
	//std::cout << "VS = " << parent_children_relation.size() << "\n";
}

template<typename KeyType, typename ValueType>
inline void PersistentAssociativeArray<KeyType, ValueType>::changeVersion(int _number_of_version, KeyType _key, ValueType _new_value)
{
	bool child_exists = false;
	for (const auto& pair : parent_children_relation)
	{
		if (pair.first == _number_of_version)
		{
			child_exists = true;
			std::cout << "Impossible to change a version which has children. ";
			std::cout << "Version [" << pair.first << "] has at least one child [" << pair.second << "]\n";
			return;
		}
	}

	

	int position{};
	for (size_t i = 0; i < keys.size(); i++)
	{
		if (_key == keys.at(i))
		{
			position = i;
		}
	}

	_number_of_version += 1;
	position += 1;

	int left_border = 1;
	int right_border = versionSize(_number_of_version);

	add(versions[_number_of_version - 1], versions.at(_number_of_version - 1), left_border, right_border, position, _new_value);
}

template<typename KeyType, typename ValueType>
inline int PersistentAssociativeArray<KeyType, ValueType>::versionSize(int _number_of_version)
{
	if (_number_of_version <= 0 || _number_of_version > versions.size())
	{
		return -1;
	}

	return countLeaves(versions[_number_of_version - 1]);
}

template<typename KeyType, typename ValueType>
inline int PersistentAssociativeArray<KeyType, ValueType>::getSize(AA_node<KeyType, ValueType>* _current)
{
	if (_current == nullptr)
	{
		return 0;
	}

	return 1 + sizeRecursive(_current->left) + sizeRecursive(_current->right);
}

template<typename KeyType, typename ValueType>
inline AA_node<KeyType, ValueType>* PersistentAssociativeArray<KeyType, ValueType>::getAssociativeArray(int)
{
	return nullptr;
}

template<typename KeyType, typename ValueType>
inline void PersistentAssociativeArray<KeyType, ValueType>::deleteElement(int _root_position, KeyType _key)
{
	auto root_size = versionSize(_root_position + 1);
	AA_node<KeyType, ValueType>* modified_version = nullptr;
	std::vector<KeyType> ks{}; std::vector<ValueType> vs{};
	for (size_t i = 0; i < root_size; i++)
	{
		//std::cout << getKey(key_versions.at(_root_position), 1, root_size, i+1) << " : ";
		ks.push_back(getKey(key_versions.at(_root_position), 1, root_size, i + 1));
		//std::cout << getValue(versions.at(_root_position), 1, root_size, i+1) << "\t";
		vs.push_back(getValue(versions.at(_root_position), 1, root_size, i + 1));
	}//std::cout << "\n";

	int key_index{};
	for (int i = 0; i < ks.size(); i++)
	{
		if (_key == ks.at(i))
		{
			key_index = i;
		}
	}

	_root_position += 1;
	key_index += 1;

	ks.erase(ks.begin() + key_index - 1);
	vs.erase(vs.begin() + key_index - 1);

	for (size_t i = 0; i < root_size - 1; i++)
	{
		KeyType key = ks.at(i);
		ValueType value = vs.at(i);
		modified_version = insertRecursive(modified_version, key, value, ks);
	}

	//std::vector<KeyType> temp_keys{};
	//temp_keys.assign(keys.begin(), keys.end());
	//temp_keys.erase(temp_keys.begin() + key_index - 1);

	//AA_node<KeyType, ValueType>* modified_array = nullptr;
	//auto source_size = versionSize(_root_position);

	//std::cout << "source_size = " << source_size << "\n";

	if (key_index < 1 || key_index > root_size + 1)
	{
		std::cerr << "Invalid _insert_index\n";
		return;
	}

	versions.push_back(new Node<ValueType>());
	key_versions.push_back(new Node<KeyType>());

	/*for (int i = 1, j = 0; i <= source_size; i++)
	{
		ValueType value = get(versions.at(_root_position - 1), 1, source_size, i);

		//std::cout << "value = " << value << "\t";
		//std::cout << "i = " << i << "\t";
		//std::cout << "_delete_index = " << _delete_index << "\n";

		if (i != key_index)
		{
			//insert(i, value);
			modified_array = insertRecursive(modified_array, keys.at(j), value, temp_keys);
			j++;
		}

	}*/

	int left_border = 1;
	int right_border = root_size - 1;

	buildTreeValue(versions.back(), modified_version, left_border, right_border, ks);
	buildTreeKey(key_versions.back(), modified_version, left_border, right_border, ks);

	std::pair<int, int> temp = { _root_position - 1, versions.size() - 1 };
	parent_children_relation.push_back(temp);
}

template<typename KeyType, typename ValueType>
inline void PersistentAssociativeArray<KeyType, ValueType>::insertElement(int _root_position, int _insert_index, KeyType _new_key, ValueType _new_value)
{
	auto root_size = versionSize(_root_position + 1);
	AA_node<KeyType, ValueType>* modified_version = nullptr;
	std::vector<KeyType> ks{}; std::vector<ValueType> vs{};
	for (size_t i = 0; i < root_size; i++)
	{
		//std::cout << getKey(key_versions.at(_root_position), 1, root_size, i+1) << " : ";
		ks.push_back(getKey(key_versions.at(_root_position), 1, root_size, i + 1));
		//std::cout << getValue(versions.at(_root_position), 1, root_size, i+1) << "\t";
		vs.push_back(getValue(versions.at(_root_position), 1, root_size, i + 1));
	}std::cout << "\n";

	_root_position += 1;
	_insert_index += 1;

	ks.insert(ks.begin() + _insert_index - 1, _new_key);
	vs.insert(vs.begin() + _insert_index - 1, _new_value);

	for (size_t i = 0; i < root_size + 1; i++)
	{
		KeyType key = ks.at(i);
		ValueType value = vs.at(i);
		modified_version = insertRecursive(modified_version, key, value, ks);
	} 

	//std::vector<KeyType> temp_keys{};
	//temp_keys.assign(keys.begin(), keys.end());
	//temp_keys.insert(temp_keys.begin() + _insert_index - 1, _new_key);

	//AA_node<KeyType, ValueType>* modified_array = nullptr;
	//auto source_size = versionSize(_root_position);

	if (_insert_index < 1 || _insert_index > root_size + 1)
	{
		std::cerr << "Invalid _insert_index\n";
		return;
	}

	versions.push_back(new Node<ValueType>());
	key_versions.push_back(new Node<KeyType>());

	//int new_size = source_size + 1;


	/*for (int i = 1, j = 1; i <= new_size; i++)
	{
		ValueType value{};
		KeyType key{};

		//std::cout << "value = " << value << "\t";
		//std::cout << "i = " << i << "\t";
		//std::cout << "_delete_index = " << _delete_index << "\n";

		if (i < _insert_index)
		{
			value = getValue(versions.at(_root_position - 1), 1, source_size, i);
			key = getKey(key_versions.at(_root_position - 1), 1, source_size, i);
			modified_array = insertRecursive(modified_array, key, value, temp_keys);
		}
		if (i > _insert_index)
		{
			value = getValue(versions.at(_root_position - 1), 1, source_size, i - 1);
			key = getKey(key_versions.at(_root_position - 1), 1, source_size, i - 1);
			modified_array = insertRecursive(modified_array, key, value, temp_keys);
		}
		else
		{
			value = _new_value;
			key = _new_key;
			modified_array = insertRecursive(modified_array, key, value, temp_keys);
		}
		//std::cout << "\ni-1: " << i - 1 << "\t";
		//std::cout << "_root_position: " << _root_position << "\t";
		//std::cout << "_insert_index: " << _insert_index << "\t";
		//std::cout << "value: " << value << "\t";
		//std::cout << "key: " << key << "\n";

		
		
		//std::cout << "SR: " << sizeRecursive(modified_array) << "\n\n";
	}*/
	//std::cout << "pp\n";
	//printSlice(modified_array, 1, new_size);
	//std::cout << "ff\n";

	int left_border = 1;
	int right_border = root_size + 1;

	buildTreeValue(versions.back(), modified_version, left_border, right_border, ks);
	buildTreeKey(key_versions.back(), modified_version, left_border, right_border, ks);

	std::pair<int, int> temp = { _root_position - 1, versions.size() - 1 };
	parent_children_relation.push_back(temp);

}

template<typename KeyType, typename ValueType>
inline void PersistentAssociativeArray<KeyType, ValueType>::printKeys()
{
	std::cout << "\nKeys:\n";
	for (size_t i = 0; i < keys.size(); i++)
	{
		std::cout << "Index: " << i << " Key: " << keys.at(i) << "\n";
	}
	std::cout << "\n";
}

template<typename KeyType, typename ValueType>
inline Node<ValueType>* PersistentAssociativeArray<KeyType, ValueType>::getVersion(int _number_of_version)
{
	_number_of_version += 1;

	if (_number_of_version <= 0 || _number_of_version > versions.size())
	{
		std::cerr << "There is no version [" << _number_of_version - 1 << "]\n";
		return nullptr;
	}

	return versions[_number_of_version - 1];
}

template<typename KeyType, typename ValueType>
inline int PersistentAssociativeArray<KeyType, ValueType>::sizeVersions()
{
	return versions.size();
}

template<typename KeyType, typename ValueType>
template<typename X>
inline void PersistentAssociativeArray<KeyType, ValueType>::add(Node<X>* _to, Node<X>* _from, int _left_border, int _right_border, int _position, X _new_value)
{
	//std::cout << "to->val = " << _to->value << "\t";// << "l: " << _to->lchild->val << "\tr: " << _to->rchild->val << "\t";
	//std::cout << "from->val = " << _from->value << "\t";
	//std::cout << "l = " << _left_border << "\tr = " << _right_border << "\t";
	//std::cout << "pos = " << _position << "\tnv = " << _new_value << "\n";

	if (_left_border == _right_border)
	{
		//std::cout << "in if:\t";
		_to->value = _new_value;
		//std::cout << _to->value << "\n";
	}
	else
	{
		int middle = (_left_border + _right_border) / 2; //std::cout << "m = " << middle << "\n";

		if (_position <= middle)
		{
			//std::cout << "npos(" << _position << ") <= m(" << middle << ") : left manipulations\n";

			_to->right_child = _from->right_child;
			Node<X>* left = new Node<X>();
			add(left, _from->left_child, _left_border, middle, _position, _new_value);
			_to->left_child = left;
		}
		else
		{
			//std::cout << "npos(" << _position << ") > m(" << middle << ") : right manipulations\n";

			_to->left_child = _from->left_child;
			Node<X>* right = new Node<X>();
			add(right, _from->right_child, middle + 1, _right_border, _position, _new_value);
			_to->right_child = right;
		}
	}
}

template<typename KeyType, typename ValueType>
template<typename X>
inline X PersistentAssociativeArray<KeyType, ValueType>::get(Node<X>* _node, int _left_border, int _right_border, int _position)
{
	if (_left_border == _right_border)
	{
		//std::cout << "l(" << _left_border << ") <= r(" << _right_border << ")\n"; 
		//if (node->lchild != nullptr) std::cout << "node->lchild->value = " << node->lchild->value << "\t";
		//else std::cout << "node->lchild = nullptr\t";
		//if (node->rchild != nullptr) std::cout << "node->rchild->value = " << node->rchild->value << "\n";
		//else std::cout << "node->rchild = nullptr\n";
		return _node->value;
	}
	else
	{
		int middle = (_left_border + _right_border) / 2;
		if (_position <= middle)
		{
			//std::cout << "pos(" << _position << ") <= m(" << middle << ")\n"; 
			//std::cout << "node->lchild->value = " << node->lchild->value << "\t";
			//std::cout << "node->rchild->value = " << node->rchild->value << "\n";
			return get(_node->left_child, _left_border, middle, _position);
		}
		else
		{
			//std::cout << "pos(" << pos << ") > m(" << middle << ")\n";
			//std::cout << "node->rchild->value = " << node->rchild->value << "\t";
			//std::cout << "node->lchild->value = " << node->lchild->value << "\n";
			return get(_node->right_child, middle + 1, _right_border, _position);
		}
	}
}

template<typename T>
inline void PersistentArray<T>::buildTree(Node<T>* _node, T* _array, int _left_border, int _right_border)
{
	//std::cout << "\nin build with: l = " << _left_border << " r = " << _right_border << "\n";
	//printSlice(_left_border, r);

	if (_left_border == _right_border) // leaf node
	{
		_node->value = _array[_left_border - 1];
		//std::cout << "in if\t" << _node->val << "\n";
	}
	else // intermediate node
	{
		int middle = (_left_border + _right_border) / 2; //std::cout << "m = " << middle << "\n";
		//std::cout << "\nmaking left child";
		_node->left_child = new Node<T>();
		buildTree(_node->left_child, _array, _left_border, middle);
		//std::cout << "\nmaking right child";
		_node->right_child = new  Node<T>();
		buildTree(_node->right_child, _array, middle + 1, _right_border);
	}
}

template<typename T>
inline void PersistentArray<T>::add(Node<T>* _to, Node<T>* _from, int _left_border, int _right_border, int _position, T _new_value)
{
	//std::cout << "to->val = " << _to->val << "\t";// << "l: " << _to->lchild->val << "\tr: " << _to->rchild->val << "\t";
	//std::cout << "from->val = " << _from->val << "\t";
	//std::cout << "l = " << _left_border << "\tr = " << _right_border << "\t";
	//std::cout << "pos = " << _position << "\tnv = " << _new_value << "\n";

	if (_left_border == _right_border)
	{
		//std::cout << "in if:\t";
		_to->value = _new_value;
		//std::cout << to->val << "\n";
	}
	else
	{
		int middle = (_left_border + _right_border) / 2; //std::cout << "m = " << m << "\n";

		if (_position <= middle)
		{
			//std::cout << "npos(" << npos << ") <= m(" << m << ") : left manipulations\n";

			_to->right_child = _from->right_child;
			Node<T>* left = new Node<T>();
			add(left, _from->left_child, _left_border, middle, _position, _new_value);
			_to->left_child = left;
		}
		else
		{
			//std::cout << "npos(" << npos << ") > m(" << m << ") : right manipulations\n";

			_to->left_child = _from->left_child;
			Node<T>* right = new Node<T>();
			add(right, _from->right_child, middle + 1, _right_border, _position, _new_value);
			_to->right_child = right;
		}
	}
}

template<typename T>
inline T PersistentArray<T>::get(Node<T>* _node, int _left_border, int _right_border, int _position)
{
	if (_left_border == _right_border)
	{
		//std::cout << "l(" << _left_border << ") <= r(" << _right_border << ")\n"; 
		//if (node->lchild != nullptr) std::cout << "node->lchild->value = " << node->lchild->value << "\t";
		//else std::cout << "node->lchild = nullptr\t";
		//if (node->rchild != nullptr) std::cout << "node->rchild->value = " << node->rchild->value << "\n";
		//else std::cout << "node->rchild = nullptr\n";
		return _node->value;
	}

	else
	{
		int middle = (_left_border + _right_border) / 2;
		if (_position <= middle)
		{
			//std::cout << "pos(" << _position << ") <= m(" << middle << ")\n"; 
			//std::cout << "node->lchild->value = " << node->lchild->value << "\t";
			//std::cout << "node->rchild->value = " << node->rchild->value << "\n";
			return get(_node->left_child, _left_border, middle, _position);
		}
		else
		{
			//std::cout << "pos(" << _position << ") > m(" << middle << ")\n";
			//std::cout << "node->rchild->value = " << node->rchild->value << "\t";
			//std::cout << "node->lchild->value = " << node->lchild->value << "\n";
			return get(_node->right_child, middle + 1, _right_border, _position);
		}
	}
}

template<typename T>
inline int PersistentArray<T>::countLeaves(Node<T>* _node)
{
	if (_node == nullptr)
	{
		return 0;
	}

	// the node is a leaf
	if (_node->left_child == nullptr && _node->right_child == nullptr)
	{
		return 1;
	}

	int left_count = countLeaves(_node->left_child);
	int right_count = countLeaves(_node->right_child);

	return left_count + right_count;
}

template<typename T>
inline void PersistentArray<T>::printSlice(T* _arr, int _left, int _right)
{
	//std::cout << "in printArr with: size = " << _right - _left + 1 << "\n";
	if (_arr == nullptr)
	{
		std::cout << "nullptr\n";
		return;
	}

	std::cout << "arr:\t";
	for (int i = _left - 1; i < _right; i++)
	{
		std::cout << _arr[i] << "\t";
	}
	std::cout << "\n";
}

template<typename T>
inline PersistentArray<T>::PersistentArray(int _size)
{
	// Create the base version
	this->base = new T[_size];
	// Set size of base version
	this->size = _size;

	// Add new root to versions
	versions.push_back(new Node<T>());

	// From fisrt element to the last (=_size)
	int left_border = 1;
	int right_border = _size;
	T* arr = base;

	// Build tree with arr
	buildTree(versions.at(0), arr, left_border, right_border);

	std::pair<int, int> temp = { -1, versions.size() - 1 };
	parent_children_relation.push_back(temp);
}

template<typename T>
inline PersistentArray<T>::PersistentArray(T* _arr, int _size)
{
	if (_arr == nullptr)
	{
		throw std::invalid_argument("Empty array");
	}

	// Create the base version
	this->base = new T[_size];
	// Set size of base version
	this->size = _size;

	// Fill base with elements of _arr
	for (int i = 0; i < _size; i++)
	{
		this->base[i] = _arr[i];
	}

	// Add new root to versions
	versions.push_back(new Node<T>());

	// From fisrt element to the last (=_size)
	int left_border = 1;
	int right_border = _size;
	T* arr = base;

	// Build tree with arr
	buildTree(versions.at(0), arr, left_border, right_border);

	std::pair<int, int> temp = { -1, versions.size() - 1 };
	parent_children_relation.push_back(temp);
}

template<typename T>
inline PersistentArray<T>::~PersistentArray()
{
	for (auto nodePtr : versions)
	{
		delete nodePtr;
	}

	delete[] base;
}

template<typename T>
inline void PersistentArray<T>::setElementToBase(int _index, T _value)
{
	if (_index >= 0 && _index < size)
	{
		base[_index] = _value;
		changeVersion(0, _index, _value);
	}
	else
	{
		throw std::out_of_range("Index out of borders");
	}
}

template<typename T>
inline void PersistentArray<T>::changeVersion(int _number_of_version, int _change_index, T _new_value)
{
	bool child_exists = false;
	for (const auto& pair : parent_children_relation)
	{
		if (pair.first == _number_of_version)
		{
			child_exists = true;
			std::cout << "Impossible to change a version which has children. ";
			std::cout << "Version [" << pair.first << "] has at least one child [" << pair.second << "]\n";
			return;
		}
	}

	_number_of_version += 1;
	_change_index += 1;

	if (_number_of_version > versions.size())
	{
		return;
	}

	int left_border = 1;
	int right_border = versionSize(_number_of_version);

	if (_change_index > right_border)
	{
		throw std::out_of_range("Index out of borders");
	}

	add(versions[_number_of_version - 1], versions.at(_number_of_version - 1), left_border, right_border, _change_index, _new_value);

}

template<typename T>
inline void PersistentArray<T>::addVersion(int _root_position, int _change_index, T _new_value)
{
	_root_position += 1;
	_change_index += 1;

	if (_root_position > versions.size())
	{
		return;
	}

	int left_border = 1;
	int right_border = versionSize(_root_position);

	if (_change_index > right_border)
	{
		throw std::out_of_range("Index out of borders");
	}

	versions.push_back(new Node<T>());
	add(versions.back(), versions.at(_root_position - 1), left_border, right_border, _change_index, _new_value);

	std::pair<int, int> temp = { _root_position - 1, versions.size() - 1 };
	parent_children_relation.push_back(temp);
}

template<typename T>
inline void PersistentArray<T>::printAllVersions()
{
	for (size_t i = 0; i < versions.size(); i++)
	{
		auto version_size = versionSize(i + 1);
		std::cout << "Version [" << i << "]: \t";
		std::cout << "Parent ID: [" << parent_children_relation[i].first << "]\t";
		std::cout << "{";
		for (int j = 1; j < version_size + 1; j++)
		{
			//std::cout << "'" << keys.at(j - 1) << "' : '";
			std::cout << "'";
			//std::cout << "n = " << number_of_elements << " i = " << i << " j = " << j << " ";
			std::cout << get(versions.at(i), 1, version_size, j);
			if (j < version_size)
			{
				std::cout << "', ";
			}
			else
			{
				std::cout << "'";
			}
		}
		//std::cout << "\tParent ID: " << parent_children_relation[i].first << " Children ID: " << parent_children_relation[i].second;
		//std::cout << "VS: " << versions.size() << " KVS: " << key_versions.size() << "\t";
		std::cout << "}\n";
	}
}

template<typename T>
inline int PersistentArray<T>::versionSize(int _number_of_version)
{
	if (_number_of_version <= 0 || _number_of_version > versions.size())
	{
		return -1;
	}

	return countLeaves(versions[_number_of_version - 1]);
}

template<typename T>
inline T* PersistentArray<T>::getArray(int _number_of_version)
{
	if (_number_of_version > versions.size())
	{
		return nullptr;
	}

	Node<T>* root = versions[_number_of_version - 1];
	auto version_size = versionSize(_number_of_version);
	T* result = new T[version_size];

	for (int i = 1; i <= version_size; i++)
	{
		result[i - 1] = get(root, 1, version_size, i);
	}

	return result;
}

template<typename T>
inline void PersistentArray<T>::deleteElement(int _root_position, int _delete_index)
{
	_root_position += 1;
	_delete_index += 1;

	T* source_array = getArray(_root_position);
	auto source_size = versionSize(_root_position);

	if (_delete_index < 1 || _delete_index > source_size)
	{
		std::cerr << "Index out of borders\n";
		delete[] source_array;
		return;
	}

	//std::cout << "Size = " << source_size << "; ";
	//std::cout << "arr[excludeIndex] = " << source_array[_exclude_index - 1] << ": \t";

	/*for (size_t j = 0; j < source_size; j++)
	{
		std::cout << source_array[j] << "\t";
	}
	std::cout << "\n";*/

	int new_size = source_size - 1;

	T* modified_array = new T[source_size];
	//std::vector<T> modified_vector{};

	// Copy elements from source_size to modified_array
	for (int i = 0; i < source_size; i++)
	{
		if (i != _delete_index - 1)
		{
			modified_array[i] = source_array[i];
			//modified_vector.push_back(source_array[i]);
		}
	}

	//T* modified_array = new T[modified_vector.size()];
	/*for (int i = 0; i < modified_vector.size(); ++i)
	{
		modified_array[i] = modified_vector[i];
	}*/

	/*std::cout << "Size = " << new_size << "; ";
	for (size_t j = 0; j < new_size; j++)
	{
		std::cout << modified_array[j] << "\t";
	}

	std::cout << "\n";*/

	// Create a new version by building a tree
	versions.push_back(new Node<T>());
	buildTree(versions.back(), modified_array, 1 + 1, new_size + 1);

	delete[] source_array;
	delete[] modified_array;

	std::pair<int, int> temp = { _root_position - 1, versions.size() - 1 };
	parent_children_relation.push_back(temp);
}

template<typename T>
inline void PersistentArray<T>::insertElement(int _root_position, int _insert_index, T _new_value)
{
	_root_position += 1;
	_insert_index += 1;

	T* source_array = getArray(_root_position);
	auto source_size = versionSize(_root_position);

	if (_insert_index < 1 || _insert_index > source_size + 1)
	{
		std::cerr << "Index out of borders\n";
		delete[] source_array;
		return;
	}

	/*std::cout << "Size = " << source_size << "; ";
	for (size_t j = 0; j < source_size; j++)
	{
		std::cout << source_array[j] << "\t";
	}

	std::cout << "\n";*/

	int new_size = source_size + 1;

	T* modified_array = new T[new_size];

	for (int i = 0, j = 0; j < new_size; j++)
	{
		if (j == _insert_index - 1)
		{
			modified_array[j] = _new_value;
		}
		else
		{
			modified_array[j] = source_array[i++];
		}
	}

	/*std::cout << "Size = " << new_size << "; ";
	for (size_t j = 0; j < new_size; j++)
	{
		std::cout << modified_array[j] << "\t";
	}

	std::cout << "\n";*/

	versions.push_back(new Node<T>());
	buildTree(versions.back(), modified_array, 1, new_size);

	delete[] source_array;
	delete[] modified_array;

	std::pair<int, int> temp = { _root_position - 1, versions.size() - 1 };
	parent_children_relation.push_back(temp);
}

template<typename T>
inline Node<T>* PersistentArray<T>::getVersion(int _number_of_version)
{
	_number_of_version += 1;

	if (_number_of_version <= 0 || _number_of_version > versions.size())
	{
		std::cerr << "There is no version [" << _number_of_version - 1 << "]\n";
		return nullptr;
	}

	return versions[_number_of_version - 1];
}

template<typename T>
inline int PersistentArray<T>::sizeVersions()
{
	return versions.size();
}

template<typename T>
inline void PersistentDoublyLinkedList<T>::buildTree(Node<T>* _node, DL_node<T>* _list_head, int _left_border, int _right_border)
{
	//std::cout << "\nin build with: l = " << _left_border << " r = " << _right_border << "\n";
	//printSlice(_list_head, _left_border, _right_border);

	if (_left_border == _right_border) // leaf node
	{
		_node->value = getElement(_list_head, _left_border - 1); //_list_head[_left_border - 1];
		//std::cout << "in if\t" << _node->val << "\n";
	}
	else // intermediate node
	{
		int middle = (_left_border + _right_border) / 2; //std::cout << "m = " << middle << "\n";
		//std::cout << "\nmaking left child";
		_node->left_child = new Node<T>();
		buildTree(_node->left_child, _list_head, _left_border, middle);
		//std::cout << "\nmaking right child";
		_node->right_child = new Node<T>();
		buildTree(_node->right_child, _list_head, middle + 1, _right_border);
	}
}

template<typename T>
inline void PersistentDoublyLinkedList<T>::add(Node<T>* _to, Node<T>* _from, int _left_border, int _right_border, int _position, T _new_value)
{
	//std::cout << "to->val = " << _to->val << "\t";// << "l: " << _to->lchild->val << "\tr: " << _to->rchild->val << "\t";
	//std::cout << "from->val = " << _from->val << "\t";
	//std::cout << "l = " << _left_border << "\tr = " << _right_border << "\t";
	//std::cout << "pos = " << _position << "\tnv = " << _new_value << "\n";

	if (_left_border == _right_border)
	{
		//std::cout << "in if:\t";
		_to->value = _new_value;
		//std::cout << to->val << "\n";
	}
	else
	{
		int middle = (_left_border + _right_border) / 2; //std::cout << "m = " << m << "\n";

		if (_position <= middle)
		{
			//std::cout << "npos(" << npos << ") <= m(" << m << ") : left manipulations\n";

			_to->right_child = _from->right_child;
			Node<T>* left = new Node<T>();
			add(left, _from->left_child, _left_border, middle, _position, _new_value);
			_to->left_child = left;
		}
		else
		{
			//std::cout << "npos(" << npos << ") > m(" << m << ") : right manipulations\n";

			_to->left_child = _from->left_child;
			Node<T>* right = new Node<T>();
			add(right, _from->right_child, middle + 1, _right_border, _position, _new_value);
			_to->right_child = right;
		}
	}
}

template<typename T>
inline T PersistentDoublyLinkedList<T>::get(Node<T>* _node, int _left_border, int _right_border, int _position)
{
	if (_left_border == _right_border)
	{
		//std::cout << "l(" << _left_border << ") <= r(" << _right_border << ")\n"; 
		//if (node->lchild != nullptr) std::cout << "node->lchild->value = " << node->lchild->value << "\t";
		//else std::cout << "node->lchild = nullptr\t";
		//if (node->rchild != nullptr) std::cout << "node->rchild->value = " << node->rchild->value << "\n";
		//else std::cout << "node->rchild = nullptr\n";
		return _node->value;
	}

	else
	{
		int middle = (_left_border + _right_border) / 2;
		if (_position <= middle)
		{
			//std::cout << "pos(" << _position << ") <= m(" << middle << ")\n"; 
			//std::cout << "node->lchild->value = " << node->lchild->value << "\t";
			//std::cout << "node->rchild->value = " << node->rchild->value << "\n";
			return get(_node->left_child, _left_border, middle, _position);
		}
		else
		{
			//std::cout << "pos(" << pos << ") > m(" << middle << ")\n";
			//std::cout << "node->rchild->value = " << node->rchild->value << "\t";
			//std::cout << "node->lchild->value = " << node->lchild->value << "\n";
			return get(_node->right_child, middle + 1, _right_border, _position);
		}
	}
}

template<typename T>
inline void PersistentDoublyLinkedList<T>::initDL(T _data)
{
	// Create an empty node
	base = new DL_node<T>();

	// Assign data to the head node
	base->value = _data;

	// Assign prev pointer to the head node
	base->prev = nullptr;

	// Assign next pointer to the head node
	base->next = nullptr;
}

template<typename T>
inline int PersistentDoublyLinkedList<T>::countLeaves(Node<T>* _node)
{
	if (_node == nullptr)
	{
		return 0;
	}

	// the node is a leaf
	if (_node->left_child == nullptr && _node->right_child == nullptr)
	{
		return 1;
	}

	int left_count = countLeaves(_node->left_child);
	int right_count = countLeaves(_node->right_child);

	return left_count + right_count;
}

template<typename T>
inline PersistentDoublyLinkedList<T>::PersistentDoublyLinkedList(T _data)
{
	// Making a single node with data 
	/*DL_node* head = new DL_node();
	head->data = _data;
	head->prev = nullptr;
	head->next = nullptr;
	// Assign it to base
	this->base = head;*/

	initDL(_data);

	this->size = 1;

	// New root of version
	versions.push_back(new Node<T>());

	// From fisrt element to the last (= 1)
	int left_border = 1;
	int right_border = 1;

	buildTree(versions.at(0), this->base, left_border, right_border);

	std::pair<int, int> temp = { -1, versions.size() - 1 };
	parent_children_relation.push_back(temp);
}

template<typename T>
inline PersistentDoublyLinkedList<T>::PersistentDoublyLinkedList(T* _arr, int _size)
{
	// Assign empty node to base
	this->base = nullptr;
	this->size = _size;

	// New root of version
	versions.push_back(new Node<T>());

	// Fill base list
	if (_size > 0)
	{
		initDL(_arr[0]);
		for (int i = 1; i < _size; i++)
		{
			append(_arr[i]);
		}
	}

	// From fisrt element to the last (=_size)
	int left_border = 1;
	int right_border = _size;

	buildTree(versions.at(0), this->base, left_border, right_border);

	std::pair<int, int> temp = { -1, versions.size() - 1 };
	parent_children_relation.push_back(temp);
}

template<typename T>
inline PersistentDoublyLinkedList<T>::PersistentDoublyLinkedList(DL_node<T>* _head)
{
	if (_head == nullptr)
	{
		std::cerr << "Empty list!!!\n";
	}

	this->base = _head;
	this->size = getSize(_head);

	// From fisrt element to the last (=_size)
	int left_border = 1;
	int right_border = this->size;

	buildTree(versions.at(0), this->base, left_border, right_border);

	std::pair<int, int> temp = { -1, versions.size() - 1 };
	parent_children_relation.push_back(temp);
}

template<typename T>
inline PersistentDoublyLinkedList<T>::~PersistentDoublyLinkedList()
{
	for (auto nodePtr : versions)
	{
		delete nodePtr;
	}
}

template<typename T>
inline void PersistentDoublyLinkedList<T>::append(T _data)
{
	// Create the new node of the doubly linked list
	DL_node<T>* new_node = new DL_node<T>();
	// Assign data to the new node
	new_node->value = _data;
	// Assign next pointer to nullptr
	new_node->next = nullptr;

	// If linked list is empty
	if (base == nullptr)
	{
		// This is the only node in the list
		new_node->prev = nullptr;
	}
	else
	{
		// Iterate to find the last node in the list
		DL_node<T>* end_node = base;
		while (end_node->next != nullptr)
		{
			end_node = end_node->next;
		}
		// Assign the new node as the next node of the last node
		end_node->next = new_node;
		// Assign the previous pointer of the new node to the last node
		new_node->prev = end_node;
	}
	this->size += 1;

	// calculate the left and right borders
	int left_border = 1;
	int right_border = this->size;

	buildTree(versions.at(0), this->base, left_border, right_border);
}

template<typename T>
inline void PersistentDoublyLinkedList<T>::printSlice(DL_node<T>* _head, int _left, int _right)
{
	// Create a temporary node 
	DL_node<T>* temp_node = _head;
	int counter = 1;

	// Iterate through the list until the temporary node != null and the count is < than the left boundary
	while (temp_node != nullptr && counter < _left)
	{
		// Move to the next node
		temp_node = temp_node->next;
		// Increase counter
		counter++;
	}

	//std::cout << "\nin printSlice(DL_node* _head, int _left, int _right): counter = " << counter << "\t";

	// Iterate through the list until the temporary node != null and the count is <= than the right boundary
	while (temp_node != nullptr && counter <= _right)
	{
		// Print data
		std::cout << temp_node->value << "\t";
		// Move to the next node
		temp_node = temp_node->next;
		// Increase counter
		counter++;
	}
	//std::cout << counter << std::endl;
	std::cout << std::endl;
}

template<typename T>
inline int PersistentDoublyLinkedList<T>::getSize(DL_node<T>* _head)
{
	int count = 0;
	DL_node<T>* temp_node = _head;

	while (temp_node != nullptr)
	{
		count++;
		temp_node = temp_node->next;
	}

	return count;
}

template<typename T>
inline T PersistentDoublyLinkedList<T>::getElement(DL_node<T>* _head, int _index)
{
	DL_node<T>* temp_node = _head;
	int count = 0;

	while (temp_node != nullptr && count < _index)
	{
		temp_node = temp_node->next;
		count++;
	}

	if (temp_node != nullptr)
	{
		return temp_node->value;
	}
	else
	{
		//std::cout << "Index out of bounds" << std::endl;
		return -1;
	}
}

template<typename T>
inline void PersistentDoublyLinkedList<T>::changeVersion(int _number_of_version, int _new_position, T _new_value)
{
	bool child_exists = false;
	for (const auto& pair : parent_children_relation)
	{
		if (pair.first == _number_of_version)
		{
			child_exists = true;
			std::cout << "Impossible to change a version which has children. ";
			std::cout << "Version [" << pair.first << "] has at least one child [" << pair.second << "]\n";
			return;
		}
	}

	_number_of_version += 1;
	_new_position += 1;

	int left_border = 1;
	int right_border = versionSize(_number_of_version);

	add(versions[_number_of_version - 1], versions.at(_number_of_version - 1), left_border, right_border, _new_position, _new_value);
}

template<typename T>
inline void PersistentDoublyLinkedList<T>::addVersion(int _root_position, int _new_position, T _new_value)
{
	_root_position += 1;
	_new_position += 1;

	int left_border = 1;
	int right_border = versionSize(_root_position);

	//std::cout << "\nl = " << l << ", r = " << r << "\n";

	versions.push_back(new Node<T>());
	add(versions.back(), versions.at(_root_position - 1), left_border, right_border, _new_position, _new_value);

	std::pair<int, int> temp = { _root_position - 1, versions.size() - 1 };
	parent_children_relation.push_back(temp);
}

template<typename T>
inline void PersistentDoublyLinkedList<T>::printAllVersions()
{
	for (size_t i = 0; i < versions.size(); i++)
	{
		auto version_size = versionSize(i + 1);
		std::cout << "Version [" << i << "]: \t";
		std::cout << "Parent ID: [" << parent_children_relation[i].first << "]\t";
		std::cout << "{";
		for (int j = 1; j < version_size + 1; j++)
		{
			//std::cout << "'" << keys.at(j - 1) << "' : '";
			std::cout << "'";
			//std::cout << "n = " << number_of_elements << " i = " << i << " j = " << j << " ";
			std::cout << get(versions.at(i), 1, version_size, j);
			if (j < version_size)
			{
				std::cout << "', ";
			}
			else
			{
				std::cout << "'";
			}
		}
		//std::cout << "\tParent ID: " << parent_children_relation[i].first << " Children ID: " << parent_children_relation[i].second;
		//std::cout << "VS: " << versions.size() << " KVS: " << key_versions.size() << "\t";
		std::cout << "}\n";
	}
}

template<typename T>
inline int PersistentDoublyLinkedList<T>::versionSize(int _number_of_version)
{
	if (_number_of_version <= 0 || _number_of_version > versions.size())
	{
		return -1;
	}

	return countLeaves(versions[_number_of_version - 1]);
}

template<typename T>
inline DL_node<T>* PersistentDoublyLinkedList<T>::getList(int _number_of_version)
{
	if (_number_of_version > versions.size())
	{
		return nullptr;
	}

	Node<T>* root = versions[_number_of_version - 1];
	auto version_size = versionSize(_number_of_version);

	DL_node<T>* head = nullptr;
	DL_node<T>* tail = nullptr;

	for (int i = 1; i <= version_size; i++)
	{
		int value = get(root, 1, version_size, i);

		// Create a new Node
		DL_node<T>* new_node = new DL_node<T>();
		new_node->value = value;
		new_node->next = nullptr;

		// If there is only one Node
		if (head == nullptr)
		{
			head = new_node;
			tail = new_node;
			new_node->prev = nullptr;
		}
		else // Add Node to the end
		{
			new_node->prev = tail;
			tail->next = new_node;
			tail = new_node;
		}
	}

	return head;
}

template<typename T>
inline void PersistentDoublyLinkedList<T>::deleteElement(int _root_position, int _delete_index)
{
	_root_position += 1;
	_delete_index += 1;

	//auto source_list = getList(_root_position);
	auto source_size = versionSize(_root_position);

	if (_delete_index < 1 || _delete_index > source_size)
	{
		std::cerr << "Invalid _delete_index\n";
		return;
	}

	int new_size = source_size - 1;

	//std::cout << get(versions.at(_root_position - 1), 1, versionSize(_root_position), _delete_index);

	DL_node<T>* head = nullptr;
	DL_node<T>* tail = nullptr;

	for (int i = 1; i <= source_size; i++)
	{
		if (i != _delete_index)
		{
			T value = get(versions.at(_root_position - 1), 1, versionSize(_root_position), i);

			// Create a new Node
			DL_node<T>* new_node = new DL_node<T>();
			new_node->value = value;
			new_node->next = nullptr;

			// If there is only one Node
			if (head == nullptr)
			{
				head = new_node;
				tail = new_node;
				new_node->prev = nullptr;
			}
			else // Add Node to the end
			{
				new_node->prev = tail;
				tail->next = new_node;
				tail = new_node;
			}
		}
		else
		{
			continue;
		}
	}

	versions.push_back(new Node<T>());
	buildTree(versions.back(), head, 1, new_size);

	std::pair<int, int> temp = { _root_position - 1, versions.size() - 1 };
	parent_children_relation.push_back(temp);
}

template<typename T>
inline void PersistentDoublyLinkedList<T>::insertElement(int _root_position, int _insert_index, T _new_value)
{
	_root_position += 1;
	_insert_index += 1;

	auto source_size = versionSize(_root_position);

	if (_insert_index < 1 || _insert_index > source_size + 1)
	{
		std::cerr << "Invalid _insert_index\n";
		return;
	}

	int new_size = source_size + 1;

	DL_node<T>* head = nullptr;
	DL_node<T>* tail = nullptr;

	for (int i = 1; i <= new_size; i++)
	{
		if (i == _insert_index)
		{
			// Create a new Node with the inserted value
			DL_node<T>* new_node = new DL_node<T>();
			new_node->value = _new_value;
			new_node->next = nullptr;

			if (head == nullptr)
			{
				head = new_node;
				tail = new_node;
				new_node->prev = nullptr;
			}
			else
			{
				new_node->prev = tail;
				tail->next = new_node;
				tail = new_node;
			}
		}

		if (i <= source_size)
		{
			T value = get(versions.at(_root_position - 1), 1, versionSize(_root_position), i);

			// Create a new Node with the existing values
			DL_node<T>* new_node = new DL_node<T>();
			new_node->value = value;
			new_node->next = nullptr;

			if (head == nullptr)
			{
				head = new_node;
				tail = new_node;
				new_node->prev = nullptr;
			}
			else
			{
				new_node->prev = tail;
				tail->next = new_node;
				tail = new_node;
			}
		}
	}

	versions.push_back(new Node<T>());
	buildTree(versions.back(), head, 1, new_size);

	std::pair<int, int> temp = { _root_position - 1, versions.size() - 1 };
	parent_children_relation.push_back(temp);
}

template<typename T>
inline Node<T>* PersistentDoublyLinkedList<T>::getVersion(int _number_of_version)
{
	_number_of_version += 1;

	if (_number_of_version <= 0 || _number_of_version > versions.size())
	{
		std::cerr << "There is no version [" << _number_of_version - 1 << "]\n";
		return nullptr;
	}

	return versions[_number_of_version - 1];
}

template<typename T>
inline int PersistentDoublyLinkedList<T>::sizeVersions()
{
	return versions.size();
}

template<typename ValueType>
inline ValueType Convert<ValueType>::get(Node<ValueType>* _node, int _left_border, int _right_border, int _position)
{
	if (_left_border == _right_border)
	{
		//std::cout << "l(" << _left_border << ") <= r(" << _right_border << ")\n"; 
		//if (node->lchild != nullptr) std::cout << "node->lchild->value = " << node->lchild->value << "\t";
		//else std::cout << "node->lchild = nullptr\t";
		//if (node->rchild != nullptr) std::cout << "node->rchild->value = " << node->rchild->value << "\n";
		//else std::cout << "node->rchild = nullptr\n";
		return _node->value;
	}

	else
	{
		int middle = (_left_border + _right_border) / 2;
		if (_position <= middle)
		{
			//std::cout << "pos(" << _position << ") <= m(" << middle << ")\n"; 
			//std::cout << "node->lchild->value = " << node->lchild->value << "\t";
			//std::cout << "node->rchild->value = " << node->rchild->value << "\n";
			return get(_node->left_child, _left_border, middle, _position);
		}
		else
		{
			//std::cout << "pos(" << _position << ") > m(" << middle << ")\n";
			//std::cout << "node->rchild->value = " << node->rchild->value << "\t";
			//std::cout << "node->lchild->value = " << node->lchild->value << "\n";
			return get(_node->right_child, middle + 1, _right_border, _position);
		}
	}
}

template<typename ValueType>
inline int Convert<ValueType>::nodeSize(Node<ValueType>* _node)
{
	if (_node == nullptr)
	{
		return 0;
	}

	// the node is a leaf
	if (_node->left_child == nullptr && _node->right_child == nullptr)
	{
		return 1;
	}

	int left_count = nodeSize(_node->left_child);
	int right_count = nodeSize(_node->right_child);

	return left_count + right_count;
}

template<typename ValueType>
inline PersistentArray<ValueType> Convert<ValueType>::toArray(Node<ValueType>* _version)
{
	auto version_size = nodeSize(_version);

	ValueType* array = new ValueType[version_size];

	for (int i = 1; i <= version_size; i++)
	{
		array[i - 1] = get(_version, 1, version_size, i);
	}

	PersistentArray<ValueType> result(array, version_size);

	delete[] array;

	return result;
}

template<typename ValueType>
inline PersistentDoublyLinkedList<ValueType> Convert<ValueType>::toDLList(Node<ValueType>* _version)
{
	auto version_size = nodeSize(_version);

	ValueType* array = new ValueType[version_size];

	for (int i = 1; i <= version_size; i++)
	{
		array[i - 1] = get(_version, 1, version_size, i);
	}

	PersistentDoublyLinkedList<ValueType> result(array, version_size);

	delete[] array;

	return result;
}

template<typename ValueType>
template<typename KeyType>
inline PersistentAssociativeArray<KeyType, ValueType> Convert<ValueType>::toAssociativeArray(Node<ValueType>* _version, KeyType* _keys)
{
	auto version_size = nodeSize(_version);

	ValueType* array = new ValueType[version_size];

	for (int i = 1; i <= version_size; i++)
	{
		array[i - 1] = get(_version, 1, version_size, i);
	}

	PersistentAssociativeArray<KeyType, ValueType> result(_keys, array, version_size);

	delete[] array;

	return result;
}
