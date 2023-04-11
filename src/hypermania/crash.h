#if defined(_WIN32)
  #define PLATFORM_WIN
#elif defined(__unix__) || defined(__unix)
  #define PLATFORM_UNIX
#else
  #pragma message "Crash handling only supports Windows and Unix-like OSes"
#endif

#if defined(PLATFORM_WIN) || defined(PLATFORM_UNIX)
  #define CRASH_HANDLING_ENABLED
#endif

#if defined(CRASH_HANDLING_ENABLED)
  #include <signal.h>
  #include <limits.h>
  #if defined(PLATFORM_WIN)
    #include <winerror.h>
  #elif defined(PLATFORM_UNIX)
    #include <unistd.h>
    #include <sys/resource.h>
  #endif
#endif

// =============================================================================

// -----------------------------------------------------------------------------

// =============================================================================
#if defined(CRASH_HANDLING_ENABLED)
  #define CRASH_HANDLING_SETUP signal(SIGSEGV, handleCrash)

static void handleCrash(int sig) {
	char* msg = NULL;
  #if defined(PLATFORM_WIN)
	msg = "[HyperMania] Crash detected";
	exit(ERROR_INVALID_ADDRESS); // closest thing to SIGSEGV Windows has
  #else
	msg = "[HyperMania] Crash detected";
	write(1, msg, strlen(msg));
	struct rlimit limit;
	getrlimit(RLIMIT_CORE, &limit);
	if (limit.rlim_cur > 0) {
		char cwd[512];
		getcwd(cwd, sizeof(cwd));
		msg = ", generating coredump in ";
		write(1, msg, strlen(msg));
		write(1, cwd, strlen(cwd));
		msg = "...\n";
		write(1, msg, strlen(msg));
		abort();
	}
	msg = ", skipping core dump (use ulimit -c to enable)\n";
	write(1, msg, strlen(msg));
	exit(128 + sig);
  #endif
}

#else
  #define CRASH_HANDLING_SETUP
#endif