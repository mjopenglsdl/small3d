small3d MinGW Issues and Workarounds
------------------------------------

If you are compiling with MinGW, please note that it has a little bug and
requires a small modification (at least my installation does, which was 
downloaded on the 20/10/2014 and runs gcc 4.8.1).

The engine uses certain features which obliged me to enable the C++11 switch in
CMakeLists.txt. But then I could not compile. I managed to solve the problem by
opening the io.h file, and going to line 300, more or less, where the 
following code is present:

_CRT_INLINE off64_t lseek64 (int, off64_t, int);

_CRT_INLINE off64_t lseek64 (int fd, off64_t offset, int whence) {
  return _lseeki64(fd, (__int64) offset, whence);

By changing all the occurrences of off64_t to _off64_t here, the code started
compiling, but there are still two problems. First, there is no text output,
so you cannot see what is happening at startup and, second, sometimes the
sample game will not start. I have found some information indicating that this
has to do with my MinGW setup and not with the code of the game itself.

