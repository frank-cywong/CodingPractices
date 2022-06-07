#include <stdlib.h>
#include <stdio.h>
typedef struct Vector{
	int size;
	int *memory;
	int capacity;
} vector;
void init_vector(vector *v){
	v->size = 0;
	v->capacity = 10;
	v->memory = malloc(sizeof(int) * (v->capacity));
}
void allocate_vector(vector *v, int capacity){
	int *temp = realloc(v->memory, sizeof(int) * capacity);
	if(temp){
		v->memory = temp;
		v->capacity = capacity;
	} else {
		free(v->memory);
		exit(1);
	}
}
void vector_add(vector *v, int value){
	if(v->capacity == v->size){ // need resizing
		allocate_vector(v, v->capacity * 2 + 5);
	}
	v->memory[v->size] = value;
	v->size++;
}
void vector_insert(vector *v, int index, int value){
	if(v->capacity == v->size){
		allocate_vector(v, v->capacity * 2 + 5);
	}
	for(int i = v->size - 1; i >= index; i--){
		v->memory[i+1] = v->memory[i];
	}
	v->memory[index] = value;
	v->size++;
}
void vector_set(vector *v, int index, int value){
	if(index >= 0 && index < v->size){
		v->memory[index] = value;
	}
}
int vector_get(vector *v, int index){
	if(index >= 0 && index < v->size){
		return (v->memory[index]);
	}
	return 0;
}
void vector_delete(vector *v, int index){
	if(index >= 0 && index < v->size){
		for(int i = index; i < v->size - 1; i++){
			v->memory[i] = v->memory[i+1];
		}
		v->size--;
	}
}
void vector_remove(vector *v){
	if(v->size >= 1){
		v->size--; // will be overrided eventually, no need to clear
	}
}
void clear_vector(vector *v){
	free(v->memory);
	v->capacity = 0;
	v->size = 0;
}
void print_vector(vector *v){
	printf("[");
	for(int i = 0; i < v->size; i++){
		if(i != 0){
			printf(", ");
		}
		printf("%i", v->memory[i]);
	}
	printf("]\n");
}
int main(int argc, char *argv[]){
	vector v;
	init_vector(&v);
	allocate_vector(&v, 2);
	vector_add(&v, 3);
	vector_add(&v, 4);
	print_vector(&v);
	vector_insert(&v, 0, 10);
	vector_insert(&v, 3, 8);
	printf("%i\n", vector_get(&v, 2));
	print_vector(&v);
	vector_set(&v, 1, -3);
	vector_delete(&v, 2);
	print_vector(&v);
	clear_vector(&v);
}
