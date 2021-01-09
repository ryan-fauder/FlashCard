#include <stdio.h>
#include <string.h>
#include "controller.h"

int main(int argc, char *argv[]) {
	init();
	if(argc == 1){
		home();
	}
	else if(argc == 2){
		if(!strcmp(argv[1], "-h")){
			help();
		}
		else if(!strcmp(argv[1], "-playall")){
			playall();
		}
		else{
			printf("Opcao invalida\n");
		}
	}
	else if(argc == 3){
		if(!strcmp(argv[1], "-edit")){
			edit_card(argv[2]);
		}
		else if(!strcmp(argv[1], "-del")){
			del_card(argv[2]);
		}
		else if(!strcmp(argv[1], "-create")){
			create_collection(argv[2]);
		}
		else if(!strcmp(argv[1], "-view")){
			view_collection(argv[2]);
		}
		else if(!strcmp(argv[1], "-remove")){
			delete_collection(argv[2]);
		}
		else if(!strcmp(argv[1], "-new")){
			create_card(argv[2]);
		}
		else if(!strcmp(argv[1], "-play")){
			play(argv[2]);
		}
		else if(!strcmp(argv[1], "-playonly")){
			playonly(argv[2]);
		}
		else{
			printf("Opcao invalida\n");
		}
	}
	else{
		printf("Quantidade de parametros invalida\n");
	}
	return 0;
}
