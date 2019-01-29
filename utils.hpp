#ifndef UTILS_HPP
#define UTILS_HPP

namespace utils {
#ifdef NDEBUG
	constexpr bool debug = false;
#else
	constexpr bool debug = true;
#endif

	template <class ...Ts>
	void printWarning(Ts && ... args) {
		if constexpr (debug) {
			std::cout << "\033[0;33m";
			((std::cout << std::forward<Ts>(args) << " "), ...) << std::endl;
			std::cout << "\033[0;30m";
		}
	}
	template <class ...Ts>
	void printError(Ts && ... args) {
		if constexpr (debug) {
			((std::cerr << std::forward<Ts>(args) << " "), ...) << std::endl;
		}
	}

	template <class ...Ts>
	void printFatalError(Ts && ...args) {
		if constexpr (debug) {
			((std::cerr << std::forward<Ts>(args) << " "), ...) << std::endl;
			exit(1);
		}
	}

	template <class ...Ts>
	void print(Ts && ...args) {
		if constexpr (debug) {
			((std::cout << std::forward<Ts>(args) << " "), ...) << std::endl;
		}
	}
	std::string readFile(std::string const & file_path);
}

#endif