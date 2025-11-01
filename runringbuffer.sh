mkdir -p build
gcc -std=c11 -Wall -Wextra -O2 \
  -Iinclude /workspaces/Ring-Buffer/app/main.c /workspaces/Ring-Buffer/src/ring_buffer.c \
  -o build/ringbuffer
./build/ringbuffer