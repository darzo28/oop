#pragma once
#include <memory>
#include <stdexcept>

template <typename T>
class CMyStack
{
public:
	CMyStack();
	CMyStack(const CMyStack& otherStack);
	CMyStack(CMyStack&& moveOtherStack);
	~CMyStack();
	void Push(const T& t);
	T GetTop() const;

	void Pop();
	void Clear();
	bool IsEmpty() const;

	CMyStack<T>& operator=(const CMyStack<T>& otherStack);
	CMyStack<T>& operator=(CMyStack<T>&& moveOtherStack);

private:
	struct Node
	{
		Node(const T& value, const std::shared_ptr<Node>& node)
			: data(value)
			, prev(node)
		{
		}

		T data;
		std::shared_ptr<Node> prev = nullptr;
	};

	typedef std::shared_ptr<Node> NodePtr;

	unsigned m_size;
	NodePtr m_top;
};

template <typename T>
CMyStack<T>::CMyStack::CMyStack()
	: m_size(0)
	, m_top(nullptr)
{
}

template <typename T>
CMyStack<T>::CMyStack::CMyStack(const CMyStack& otherStack)
{
	if (!otherStack.IsEmpty())
	{
		m_size = otherStack.m_size;

		NodePtr currentPtr = otherStack.m_top;

		NodePtr previousPtr = std::make_shared<Node>(currentPtr->data, nullptr);
		m_top = previousPtr;

		while (currentPtr != nullptr)
		{
			NodePtr newPtr = std::make_shared<Node>(currentPtr->data, nullptr);
			previousPtr->prev = newPtr;
			currentPtr = currentPtr->prev;
		}
	}
}

template <typename T>
CMyStack<T>::CMyStack::CMyStack(CMyStack&& moveOtherStack)
{
	if (!moveOtherStack.IsEmpty())
	{
		m_top = moveOtherStack.m_top;
		m_size = moveOtherStack.m_size;
		moveOtherStack.m_top = nullptr;
		moveOtherStack.m_size = 0;
	}
}

template <typename T>
CMyStack<T>::CMyStack::~CMyStack()
{
	Clear();
}

template <typename T>
void CMyStack<T>::Push(const T& t)
{
	m_top = std::make_shared<Node>(t, m_top);
	++m_size;
}

template <typename T>
T CMyStack<T>::GetTop() const
{
	if (IsEmpty())
	{
		throw std::logic_error("Empty stack");
	}
	return m_top->data;
}

template <typename T>
void CMyStack<T>::Pop()
{
	if (!IsEmpty())
	{
		m_top = m_top->prev;
		--m_size;
	}
}

template <typename T>
void CMyStack<T>::Clear()
{
	while (!IsEmpty())
	{
		Pop();
	}
}

template <typename T>
bool CMyStack<T>::IsEmpty() const
{
	return (m_size == 0) ? true : false;
}

template <typename T>
CMyStack<T>& CMyStack<T>::operator=(const CMyStack<T>& otherStack)
{
	if (this == &otherStack)
	{
		return *this;
	}

	if (!otherStack.IsEmpty())
	{
		Clear();
		m_size = otherStack.m_size;

		NodePtr currentPtr = otherStack.m_top;

		NodePtr previousPtr = std::make_shared<Node>(currentPtr->data, nullptr);
		m_top = previousPtr;

		while (currentPtr != nullptr)
		{
			NodePtr newPtr = std::make_shared<Node>(currentPtr->data, nullptr);
			previousPtr->prev = newPtr;
			currentPtr = currentPtr->prev;
		}
	}

	return *this;
}

template <typename T>
CMyStack<T>& CMyStack<T>::operator=(CMyStack<T>&& moveOtherStack)
{
	if (this == &moveOtherStack)
	{
		return *this;
	}

	if (!moveOtherStack.IsEmpty())
	{
		Clear();

		m_top = moveOtherStack.m_top;
		m_size = moveOtherStack.m_size;
		moveOtherStack.m_top = nullptr;
		moveOtherStack.m_size = 0;
	}

	return *this;
}
