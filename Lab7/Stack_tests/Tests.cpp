#define CATCH_CONFIG_MAIN
#include "../Stack/CMyStack.h"
#include "../../catch.hpp"
#include <string>

TEST_CASE("Int stack")
{
	CMyStack<int> stack;
	CMyStack<int> copyStack;
	CMyStack<int> moveStack;

	SECTION("One element")
	{
		stack.Push(99);
		CHECK(stack.GetTop() == 99);

		stack.Pop();
		CHECK_THROWS_AS(stack.GetTop(), std::logic_error);
		CHECK(stack.IsEmpty() == true);
	}

	SECTION("Empty")
	{
		CHECK(stack.IsEmpty() == true);
		CHECK_THROWS_AS(stack.GetTop(), std::logic_error);
	}

	SECTION("Not empty")
	{
		stack.Push(1);
		stack.Push(2);
		stack.Push(3);
		stack.Push(4);

		CHECK(stack.IsEmpty() == false);

		stack.Pop();
		CHECK(stack.GetTop() == 3);

		stack.Pop();
		CHECK(stack.GetTop() == 2);

		stack.Pop();
		CHECK(stack.GetTop() == 1);

		stack.Pop();
		CHECK_THROWS_AS(stack.GetTop(), std::logic_error);
		CHECK(stack.IsEmpty() == true);
	}

	SECTION("Clear")
	{
		stack.Push(1);
		stack.Push(2);
		stack.Push(3);
		stack.Push(4);

		CHECK(stack.IsEmpty() == false);

		stack.Clear();
		CHECK(stack.IsEmpty() == true);
	}

	SECTION("CopyStack constructor")
	{
		stack.Push(1);
		stack.Push(2);

		CMyStack<int> copyStack(stack);

		CHECK(copyStack.IsEmpty() == false);

		CHECK(stack.GetTop() == copyStack.GetTop());
	}

	SECTION("CopyStack constructor empty stack")
	{
		CMyStack<int> copyStack(stack);

		CHECK(stack.IsEmpty() == true);
		CHECK(copyStack.IsEmpty() == true);

		CHECK_THROWS_AS(stack.GetTop(), std::logic_error);
		CHECK_THROWS_AS(copyStack.GetTop(), std::logic_error);
	}

	SECTION("CopyStack operator =")
	{
		stack.Push(1);
		stack.Push(2);
		copyStack.Push(1);
		copyStack.Push(2);
		copyStack.Push(3);
		copyStack.Push(4);

		copyStack = stack;

		CHECK(stack.GetTop() == copyStack.GetTop());
		copyStack.Pop();
		CHECK(stack.GetTop() != copyStack.GetTop());
		CHECK(copyStack.GetTop() == 1);
	}

	SECTION("CopyStack empty stack operator =")
	{
		copyStack = stack;

		CHECK(stack.IsEmpty() == true);
		CHECK(copyStack.IsEmpty() == true);
		CHECK_THROWS_AS(stack.GetTop(), std::logic_error);
	}

	SECTION("Self-assignment CopyStack operator =")
	{
		stack.Push(1);
		stack.Push(2);

		stack = stack;

		CHECK_THROWS_AS(copyStack.GetTop(), std::logic_error);
		CHECK(copyStack.IsEmpty() == true);
		CHECK(stack.GetTop() == 2);
	}

	SECTION("MoveStack constructor")
	{
		stack.Push(1);
		stack.Push(2);

		CMyStack<int> moveStack(std::move(stack));

		CHECK(stack.IsEmpty() == true);
		CHECK(moveStack.IsEmpty() == false);
		CHECK_THROWS_AS(stack.GetTop(), std::logic_error);

		CHECK(moveStack.GetTop() == 2);
	}

	SECTION("MoveStack constructor empty stack")
	{
		CMyStack<int> moveStack(std::move(stack));

		CHECK(stack.IsEmpty() == true);
		CHECK(moveStack.IsEmpty() == true);

		CHECK_THROWS_AS(stack.GetTop(), std::logic_error);
		CHECK_THROWS_AS(moveStack.GetTop(), std::logic_error);
	}

	SECTION("MoveStack operator =")
	{
		stack.Push(12);
		moveStack.Push(1);
		moveStack.Push(2);
		moveStack.Push(3);
		moveStack.Push(4);

		stack = std::move(moveStack);

		CHECK(stack.GetTop() == 4);
		CHECK_THROWS_AS(moveStack.GetTop(), std::logic_error);
		CHECK(moveStack.IsEmpty() == true);
	}

	SECTION("MoveStack empty stack operator =")
	{
		stack = std::move(moveStack);

		CHECK(stack.IsEmpty() == true);
		CHECK(moveStack.IsEmpty() == true);
		CHECK_THROWS_AS(stack.GetTop(), std::logic_error);
		CHECK_THROWS_AS(moveStack.GetTop(), std::logic_error);
	}

	SECTION("Self-assignment MoveStack operator =")
	{
		stack.Push(1);
		stack.Push(2);

		stack = std::move(stack);

		CHECK(stack.IsEmpty() == false);
		CHECK(stack.GetTop() == 2);
	}
}

TEST_CASE("String stack")
{
	CMyStack<std::string> stack;
	CMyStack<std::string> copyStack;
	CMyStack<std::string> moveStack;

	SECTION("One element")
	{
		stack.Push("hello");
		CHECK(stack.GetTop() == "hello");

		stack.Pop();
		CHECK_THROWS_AS(stack.GetTop(), std::logic_error);
		CHECK(stack.IsEmpty() == true);
	}

	SECTION("Not empty")
	{
		stack.Push("Hello");
		stack.Push("World");
		stack.Push("How");
		stack.Push("Are");
		stack.Push("You");

		CHECK(stack.IsEmpty() == false);

		stack.Pop();
		CHECK(stack.GetTop() == "Are");

		stack.Pop();
		CHECK(stack.GetTop() == "How");

		stack.Pop();
		CHECK(stack.GetTop() == "World");

		stack.Pop();
		CHECK(stack.GetTop() == "Hello");

		stack.Pop();
		CHECK_THROWS_AS(stack.GetTop(), std::logic_error);
		CHECK(stack.IsEmpty() == true);
	}

	SECTION("Empty")
	{
		CHECK(stack.IsEmpty() == true);
		CHECK_THROWS_AS(stack.GetTop(), std::logic_error);
	}

	SECTION("Clear")
	{
		stack.Push("Hello");
		stack.Push("World");
		stack.Push("How");
		stack.Push("Are");
		stack.Push("You");

		CHECK(stack.IsEmpty() == false);

		stack.Clear();
		CHECK(stack.IsEmpty() == true);
	}

	SECTION("CopyStack constructor")
	{
		stack.Push("Hello");
		stack.Push("World");

		CMyStack<std::string> copyStack(stack);

		CHECK(copyStack.IsEmpty() == false);

		CHECK(stack.GetTop() == copyStack.GetTop());
	}

	SECTION("CopyStack constructor empty stack")
	{
		CMyStack<std::string> copyStack(stack);

		CHECK(stack.IsEmpty() == true);
		CHECK(copyStack.IsEmpty() == true);

		CHECK_THROWS_AS(stack.GetTop(), std::logic_error);
		CHECK_THROWS_AS(copyStack.GetTop(), std::logic_error);
	}

	SECTION("CopyStack operator =")
	{
		stack.Push("Hello");
		stack.Push("World");
		copyStack.Push("How");
		copyStack.Push("Are");

		copyStack = stack;

		CHECK(stack.GetTop() == copyStack.GetTop());
		copyStack.Pop();
		CHECK(stack.GetTop() != copyStack.GetTop());
		CHECK(copyStack.GetTop() == "Hello");
	}

	SECTION("CopyStack empty stack operator =")
	{
		copyStack = stack;

		CHECK(stack.IsEmpty() == true);
		CHECK(copyStack.IsEmpty() == true);
		CHECK_THROWS_AS(stack.GetTop(), std::logic_error);
	}

	SECTION("Self-assignment CopyStack operator =")
	{
		stack.Push("Hello");
		stack.Push("World");

		stack = stack;

		CHECK_THROWS_AS(copyStack.GetTop(), std::logic_error);
		CHECK(copyStack.IsEmpty() == true);
		CHECK(stack.GetTop() == "World");
	}

	SECTION("MoveStack constructor")
	{
		stack.Push("Hello");
		stack.Push("World");

		CMyStack<std::string> moveStack(std::move(stack));

		CHECK(stack.IsEmpty() == true);
		CHECK(moveStack.IsEmpty() == false);
		CHECK_THROWS_AS(stack.GetTop(), std::logic_error);

		CHECK(moveStack.GetTop() == "World");
	}

	SECTION("MoveStack constructor empty stack")
	{
		CMyStack<std::string> moveStack(std::move(stack));

		CHECK(stack.IsEmpty() == true);
		CHECK(moveStack.IsEmpty() == true);

		CHECK_THROWS_AS(stack.GetTop(), std::logic_error);
		CHECK_THROWS_AS(moveStack.GetTop(), std::logic_error);
	}

	SECTION("MoveStack operator =")
	{
		stack.Push("Hello stack");
		moveStack.Push("Hello");
		moveStack.Push("World");
		moveStack.Push("How");
		moveStack.Push("Are");

		stack = std::move(moveStack);

		CHECK(stack.GetTop() == "Are");
		CHECK_THROWS_AS(moveStack.GetTop(), std::logic_error);
		CHECK(moveStack.IsEmpty() == true);
	}

	SECTION("MoveStack empty stack operator =")
	{
		stack = std::move(moveStack);

		CHECK(stack.IsEmpty() == true);
		CHECK(moveStack.IsEmpty() == true);
		CHECK_THROWS_AS(stack.GetTop(), std::logic_error);
		CHECK_THROWS_AS(moveStack.GetTop(), std::logic_error);
	}

	SECTION("Self-assignment MoveStack operator =")
	{
		stack.Push("Hello");
		stack.Push("World");

		stack = std::move(stack);

		CHECK(stack.IsEmpty() == false);
		CHECK(stack.GetTop() == "World");
	}
}