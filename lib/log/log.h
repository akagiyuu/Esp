#pragma once
class Log {
	public:
	template <typename T> static void Info(T data);
	template <typename T> static void Error(T data);
};
