for (int k = 0; k < rb.capacity; ++k) {
        int output;
        if (pop(&rb, &output) == noError) {
            printf("Pop: %d\n", output);
        }
        else {
            printf("Error!\n");
        }