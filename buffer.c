#include <stdlib.h>
#include <stdio.h>
#include "buffer.h"

static ring_buffer_421_t buffer;

long init_buffer_421(void) {
	// Note: You will need to initialize semaphores in this function.
	// Ensure we're not initializing a buffer that already exists.
	if (buffer.read || buffer.write) {
		printf("init_buffer_421(): Buffer already exists. Aborting.\n");
		return -1;
	}

	// Create the root node.
	node_421_t *node;
	node = (node_421_t *) malloc(sizeof(node_421_t));
	// Create the rest of the nodes, linking them all together.
	node_421_t *current;
	int i;
	current = node;
	// Note that we've already created one node, so i = 1.
	for (i = 1; i < SIZE_OF_BUFFER; i++) {
		current->next = (node_421_t *) malloc(sizeof(node_421_t));
		current = current->next;
	}
	// Complete the chain.
	current->next = node;
	buffer.read = node;
	buffer.write = node;
	buffer.length = 0;

	return 0;
}

long enqueue_buffer_421(char * data) {
	// NOTE: You have to modify this function for it to work correctly.
	if (!buffer.write) {
		printf("write_buffer_421(): The buffer does not exist. Aborting.\n");
		return -1;
	}
	memcpy(buffer.write->data, data, DATA_LENGTH);
	// Advance the pointer.
	buffer.write = buffer.write->next;
	buffer.length++;

	return 0;
}

long dequeue_buffer_421(char * data) {
	// NOTE: Implement this function.
	return 0;
}

long delete_buffer_421(void) {
	// Tip: Don't call this while any process is waiting to enqueue or dequeue.
	if (!buffer.read) {
		printf("delete_buffer_421(): The buffer does not exist. Aborting.\n");
		return -1;
	}
	// Get rid of all existing nodes.
	node_421_t *temp;
	node_421_t *current = buffer.read->next;
	while (current != buffer.read) {
		temp = current->next;
		free(current);
		current = temp;
	}
	// Free the final node.
	free(current);
	current = NULL;
	// Reset the buffer.
	buffer.read = NULL;
	buffer.write = NULL;
	buffer.length = 0;
	return 0;
}
