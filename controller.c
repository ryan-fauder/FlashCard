#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#include "card.h"
#include "collection.h"


void help(){
	printf("░█▀▀█ ░░▀ █░░█ █▀▀▄ █▀▀█ \n");
	printf("▒█▄▄█ ░░█ █░░█ █░░█ █▄▄█ \n");
	printf("▒█░▒█ █▄█ ░▀▀▀ ▀▀▀░ ▀░░▀ \n");
	printf("\n");
	printf("Comandos para o treino:\n");
	printf("%-30s\t\t%s", "-playall", "Treina todas cartas atrasadas\n");
	printf("%-30s\t\t%s", "-playonly (colecao)", "Treina todas as cartas atrasadas de uma colecao\n");
	printf("%-30s\t\t%s", "-play (colecao)", "Treina todas as cartas de uma colecao\n");
	printf("\n");
	printf("Comandos para cartas:\n");
	printf("%-30s\t\t%s", "-new (colecao)", "Criar uma carta\n");
	printf("%-30s\t\t%s", "-edit (colecao)", "Editar uma carta\n");
	printf("%-30s\t\t%s", "-del (colecao)", "Apagar uma carta\n");
	printf("\n");
	printf("Comandos para colecoes:\n");
	printf("%-30s\t\t%s", "-create (colecao)", "Criar uma colecao\n");
	printf("%-30s\t\t%s", "-view (colecao)", "Visualizar todas as cartas de uma colecao\n");
	printf("%-30s\t\t%s", "-remove (colecao)", "Remove uma colecao\n");
}

void make_directory(const char* name) {
	mkdir(name, 0700);
}

void init(){
 	struct stat * s;
	if(stat("data", s) == -1){
		make_directory("data");
	}
}

char verifyFile(char * str){
	DIR * d = opendir("./data");
	struct dirent * dir;
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			if(!strcmp(dir->d_name, str)){
				return 1;
			}
		}
		closedir(d);
	}
	return 0;
}

int countFile(){
	int i = -2;
	DIR * d = opendir("./data");
	struct dirent * dir;
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			i++;
		}
		closedir(d);
	}
	return i;
}

FILE * open_database(char * str, char * format){
	FILE * f = NULL;
	if(strlen(str) > 50){
		printf("Nome da colecao excede o limite de 50 caracteres! Tente outro nome..\n");
		return 0;
	}
	if(!verifyFile(str)){
		printf("Colecao invalida!\n");
		return f;
	}
	char dest[56] = "data/";
	strcat(dest, str);
	f = fopen(dest, format);
	return f;
}

void home(){
	int total_due = 0, qtt_due = 0;
	DIR * d = opendir("./data");
	struct dirent * dir;
	collection * c = NULL;
	FILE * f = NULL;

	printf("▒█▀▀▀ █░░ █▀▀█ █▀▀ █░░█ 　 ▒█▀▀█ █▀▀█ █▀▀█ █▀▀▄\n");
	printf("▒█▀▀▀ █░░ █▄▄█ ▀▀█ █▀▀█ 　 ▒█░░░ █▄▄█ █▄▄▀ █░░█\n");
	printf("▒█░░░ ▀▀▀ ▀░░▀ ▀▀▀ ▀░░▀ 　 ▒█▄▄█ ▀░░▀ ▀░▀▀ ▀▀▀░\n");

	printf("\n\n");

	printf("Coleções existentes:\n");

	if (d) {
		while ((dir = readdir(d)) != NULL) {
			if(strcmp(dir->d_name, ".") && strcmp(dir->d_name, "..")){

				f = open_database(dir->d_name, "r+");
				c = collection_fread(1, dir->d_name, f);
				qtt_due = collection_count_overdue(c);
				total_due += qtt_due;
				printf("- %-20s %d cartas atrasadas!!\n", dir->d_name, qtt_due);
			}
		}
		closedir(d);
	}
	printf("\n");

	printf("Total de cartas atrasadas: %d\n\n", total_due);
	printf("Utilize \"-h\" para visualizar todas as opcoes disponiveis\n");
}

void del_card(char * str){
	FILE * f = ( FILE *) open_database(str, "r+");
	if(f == NULL){
		fclose(f);
		return;
	}
	collection * c = collection_create(str, 1);
	int number;

	c = collection_fread(1, str, f);

	collection_print(c);
	printf("Digite um numero 1-%d para deletar a carta\n", c->size);
	printf("Digite 0 para sair\n");
	scanf("%d", &number);

	while(number != 0){
		if(number > c->size || number < 0){
			printf("Numero Invalido, digite novamente\n");
			scanf("%d", &number);
			continue;
		}
		printf("Digite 0 para sair\n");
		collection_del_card(c, number - 1);
		scanf("%d", &number);
	}
	f = ( FILE *) open_database(str, "w+");
	collection_fprint(c, f);
}

void edit_card(char * str){
	FILE * f = ( FILE *) open_database(str, "r+");
	if(f == NULL){
		fclose(f);
		return;
	}
	collection * c = collection_create(str, 1);
	card * d = NULL;
	int number;
	char front[150], back[150];
	c = collection_fread(1, str, f);

	collection_print(c);
	printf("Digite um numero 1-%d para editar a carta\n", c->size);
	printf("Digite 0 para sair\n");
	scanf("%d", &number);

	while(number != 0){
		if(number > c->size || number < 0){
			printf("Numero Invalido, digite novamente\n");
			scanf("%d", &number);
			continue;
		}
		scanf("%*c");
		d = card_scanf(generate_id(c));
		collection_edit_card(c, d, number - 1);
		
		collection_print(c);
		printf("Digite um numero 1-%d para editar a carta\n", c->size);
		printf("Digite 0 para sair\n");
		scanf("%d", &number);
	}
	f = ( FILE *) open_database(str, "w+");
	collection_fprint(c, f);

	fclose(f);
	collection_free(c);
}

void create_card(char * name){
	FILE * f = ( FILE *) open_database(name, "r+");
	if(f == NULL){
		fclose(f);
		return;
	}
	collection * c = collection_fread(1, name, f);

	int boolean;
	rewind(f);

	collection_append(c, card_scanf(generate_id(c)));

	while(1){
		printf("Deseja visualizar a carta?\n");
		printf("0 - nao\n1 - sim\n");
		scanf("%d", &boolean);
		if(boolean == 1){
			card_view(c->vector[c->size - 1]);
			break;
		} else if(boolean == 0) break;
		else{
			printf("Opcao invalida, tente novamente!\n");
		}
	}
	collection_fprint(c, f);
	
	collection_free(c);
	fclose(f);
}

void create_collection(char * name){
	if(strlen(name) > 50){
		printf("Nome da colecao excede o limite de 50 caracteres! Tente outro nome..\n");
		return;
	}
	if(verifyFile(name)){
		printf("Colecao existente! Tente outro nome..\n");
		return;
	}

	char dest[56] = "data/";
	strcat(dest, name);

	FILE * f = fopen(dest, "w");
	collection * c = collection_create(name, 0);
	collection_fprint(c, f);

	fclose(f);
	collection_free(c);
}

void delete_collection(char * name){
	if(!verifyFile(name) || strlen(name) > 50){
		printf("Colecao invalida!\n");
		return;
	}
	char dest[56] = "data/";
	strcat(dest, name);
	remove(dest);
}

void view_collection(char * name){
	FILE * f = ( FILE *) open_database(name, "r");
	if(f == NULL) return;
	
	int number;
	collection * c = collection_create(name, 1);

	c = collection_fread(1, name, f);
	if(c->size <= 0){
		printf("Colecao sem cartas\n");
		fclose(f);
		collection_free(c);
		return;
	}
	collection_print(c);
	
	if(c->size > 0){
		printf("Selecione um numero de 1-%d para visualizar a carta\n", c->size);
		printf("Digite 0 para sair\n");
		scanf("%d", &number);
		while(number != 0){
			if(number > c->size || number < 0){
				printf("Numero Invalido, digite novamente\n");
				scanf("%d", &number);
				continue;
			}
			printf("Digite 0 para sair\n");
			card_view(c->vector[number-1]);
			scanf("%d", &number);
		}
	}
	fclose(f);
	collection_free(c);
}

void playonly(char * string){
	FILE * f = open_database(string, "r+");
	collection * c = collection_fread(0, string, f);
	collection * d = collection_overdue(c);

	if(d->size <= 0){
		printf("Não há cartas atrasadas em %s ainda!\n", string);
		fclose(f);
		return;
	}
	collection_print(d);
	rewind(f);

	collection_play(d);
	collection_fprint(c, f);

	collection_free(c);
	fclose(f);
}

void playall(){
	DIR * d = opendir("./data");
	struct dirent * dir;
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			if(strcmp(dir->d_name, ".") && strcmp(dir->d_name, "..")){
				playonly(dir->d_name);
			}
		}
		closedir(d);
	}
}

void play(char * string){
	FILE * f = open_database(string, "r+");
	collection * c = collection_fread(0, string, f);

	rewind(f);
	collection_play(c);

	collection_fprint(c, f);

	collection_free(c);
	fclose(f);
}