# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
    stack<int> elements;
    stack<int> minimum;
public:
	StackExt() {};
	bool empty() const; 
	T &top();
	void pop();
	void push(const T & val);
	T &findMin();
};

// a alterar DONE
template <class T> 
bool StackExt<T>::empty() const
{
    return elements.empty();
}

//a alterar DONE
template <class T> 
T& StackExt<T>::top()
{
    return elements.top();
}

//a alterar DONE
template <class T> 
void StackExt<T>::pop()
{
    if(elements.top()==minimum.top())
        minimum.pop();
    elements.pop();
}

//a alterar DONE
template <class T> 
void StackExt<T>::push(const T & val)
{
    elements.push(val);
    if(minimum.empty() || val<=minimum.top())
        minimum.push(val);
}

//a alterar DONE
template <class T> 
T& StackExt<T>::findMin()
{
    return minimum.top();
}

