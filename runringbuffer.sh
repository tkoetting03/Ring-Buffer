cc -std=c11 -Wall -Wextra -O2 -Iinclude -c src/ring_buffer.c  -o build/ring_buffer.o
cc -std=c11 -Wall -Wextra -O2 -Iinclude -c app/main.c      -o build/main.o
cc build/*.o -o build/ring_buffer && ./build/ring_buffer