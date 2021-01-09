#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "card.h"
#include "collection.h"
void collection_free(collection * c){
	int i;
	for(i = 0; i < c->size; i++){
		card_free(c->vector[i]);
	}
	free(c);
}

collection * collection_create(char name[50], int id){
	collection * c = (collection *) malloc(sizeof(collection));
	c->id = id;
	strcat(c->name, name);
	c->size = 0;
	c->vector = NULL;
	return c;
}

void collection_fprint(collection * c, FILE * f){
	int i;
	fprintf(f, "Size: %d; Cards: {", c->size);
	for(i = 0; i < c->size; i++){
		card_fprint(c->vector[i], f);
	}
	fprintf(f, "}");
}

collection * collection_fread(int id, char name[50], FILE * f){
 	collection * c = (collection *) malloc(sizeof(collection));
 	int i;

 	c->id = id;
 	strcpy(c->name, name);
	
 	fscanf(f, "Size: %d; Cards: {", &(c->size));
	if(c->size > 0){
		c->vector = (card **) calloc(c->size, sizeof(card));
		for(i = 0; i < c->size; i++){
			c->vector[i] = card_fread(f);
		}
	} else{
		c->vector = NULL;
	}
 	fscanf(f, "%*c");

 	return c;
}

collection * collection_overdue(collection * c){
	collection * d = (collection *) malloc(sizeof(collection));
	int i, index = 0;

	d->id = c->id;
	strcpy(d->name, c->name);
	d->vector = (card **) malloc(c->size * sizeof(card *));

	for(i = 0; i < c->size; i++){
		if(!verifyCooldown(c->vector[i])){
			d->vector[index] = c->vector[i];
			index++;
		}
	}

	d->size = index;
	return d;
}

void collection_print(collection * c){
	int i;
	for(i = 0; i < c->size; i++){
		printf("%d\t\t%s\t\t%s\n", i + 1, c->vector[i]->front, c->vector[i]->back);
	}
}

void collection_append(collection * c, card * d){
	c->size += 1;
	c->vector = (card **) realloc(c->vector, c->size * sizeof(card));
	c->vector[c->size - 1] = d;
}

void collection_del_card(collection * c, int index){
	if(index < 0 || index > c->size) return;
	int i;
	for(i = index; i < c->size; i++){
		c->vector[index] = c->vector[index + 1];
	}
	c->size -= 1;
	c->vector = (card **) realloc(c->vector, c->size * sizeof(card));
}

void collection_edit_card(collection * c, card * d, int index){
	if(index < 0 || index > c->size) return;
	card_edit(c->vector[index], d->front, d->back);
}

int generate_id(collection * c){
	if(c->size == 0) return 0;
	return c->vector[c->size - 1]->id + 1;
}

void collection_play(collection * c){
	int i;
	printf("Jogando a colecao %s\n", c->name);
	for(i = 0; i < c->size; i++){
		play_card(c->vector[i]);
	}
	printf("\nFim da colecao. Parabens!!\n");
}

int collection_count_overdue(collection * c){
	int counter = 0, i;
	for(i = 0; i < c->size; i++){
		if(!verifyCooldown(c->vector[i])){
			counter++;
		}
	}
	return counter;
}