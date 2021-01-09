#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "card.h"

void card_free(card * c){
	free(c->last_at);
	free(c->cooldown);
	free(c);
}

int fibbonacci(int number) {
	int aux, a1, a2;
	a1 = a2 = 1;
	while(a1 <= number){
		aux = a1 + a2;
		a1 = a2;
		a2 = aux;
	}
	return a2;
}

void recalc_cooldown(card * c, int boolean){
	if(verifyCooldown(c)) return;

	time_t now;
	int seconds = difftime(mktime(c->cooldown), mktime(c->last_at));
	int days = seconds/(60 * 60 * 24);

	time(&now);
	*(c->last_at)= *localtime(&now);
	*(c->cooldown) = *localtime(&now);

	if(!boolean){
		c->cooldown->tm_mday += 1;
		mktime(c->cooldown);
		return;
	} 

	c->cooldown->tm_mday += fibbonacci(days);
	mktime(c->cooldown);
	
}

card * card_create(int id, char front[150], char back[150]){
	card * c = (card *) malloc(sizeof(card));
	c->last_at = (moment *) malloc(sizeof(moment));
	c->cooldown = (moment *) malloc(sizeof(moment));
	time_t now;

	strcat(c->front, front);
	strcat(c->back, back);
	
	c->id = id;
	time(&now);	
	*(c->last_at)= *localtime(&now);
	*(c->cooldown) = *localtime(&now);

	c->cooldown->tm_hour += 1;
	mktime(c->cooldown);
	return c;
}

void moment_fprint(moment * m, FILE * f){
	fprintf(f,"{%d.%d.%d;", m->tm_hour, m->tm_min, m->tm_sec);
	fprintf(f,"%d-%d-%d}", m->tm_mday, m->tm_mon, m->tm_year);
	fprintf(f,";%d-%d;%d}", m->tm_wday, m->tm_yday, m->tm_isdst);
}

moment * moment_fscanf(FILE * f){
	moment * m = (moment *) malloc(sizeof(moment));
	fscanf(f,"{%d.%d.%d;", &(m->tm_hour), &(m->tm_min), &(m->tm_sec));
	fscanf(f,"%d-%d-%d}", &(m->tm_mday), &(m->tm_mon), &(m->tm_year));
	fscanf(f,";%d-%d;%d}",&(m->tm_wday), &(m->tm_yday), &(m->tm_isdst));
	return m;
}

card * card_fread(FILE * f){
 card * c = (card *) malloc(sizeof(card));
 fscanf(f, "{Id: %d, Front: %[^,], ", &(c->id), c->front);
 fscanf(f, "Back: %[^,], ", c->back);

 c->last_at = moment_fscanf(f);
 fscanf(f, "%*c");

 c->cooldown = moment_fscanf(f);
 fscanf(f, "%*c");
 return c;
}

void card_fprint(card * c, FILE * f){
	fprintf(f, "{Id: %d, Front: %s, Back: %s, ", c->id, c->front, c->back);
	moment_fprint(c->last_at, f);
	fprintf(f, ",");
	moment_fprint(c->cooldown, f);
	fprintf(f, "}");
}

void card_edit(card * c, char front[150], char back[150]){
	strcpy(c->front, front);
	strcpy(c->back, back);
}

void card_view(card * c){
	printf("\n---------------------------\n");
	printf("%s", c->front);
	printf("\n---------------------------\n");
	printf("%s", c->back);
	printf("\n---------------------------\n");
}

char verifyCooldown(card * c){
	time_t now;
	time(&now);
	int diff = difftime(mktime(c->cooldown), now);
	if(diff <= 0) return 0;
	return 1;
}

card * card_scanf(int index){
	card * d = NULL;
	char front[150], back[150];
	int boolean;
	while(1){
		printf("Digite o texto da parte frontal da carta ( limite de 150 caracteres)\n");
		printf("Para cancelar a operacao, digite \"-exit\"\n");
		scanf("%[^\n]s", front);
		if(!strcmp(front, "-exit")){
				card_free(d);
				return NULL;
		}
		if(strlen(front) > 150){
			printf("Quantidade  de caracteres invalida!\nTente novamente..\n\n");
			continue;
		}
		break;
	}
	scanf("%*c");
	while(1){
		printf("Digite o texto da parte traseira da carta ( limite de 150 caracteres)\n");
		printf("Para cancelar a operacao, digite \"-exit\"\n");
		scanf("%[^\n]s", back);
		if(!strcmp(back, "-exit")){
				card_free(d);
				return NULL;
		}
		if(strlen(back) > 150){
			printf("Quantidade de caracteres invalida!\nTente novamente..\n\n");
			continue;
		}
		break;
	}

	d = card_create(index, front, back);
	return d;
}

void play_card(card * c){
	int boolean = 0;

	printf("\n---------------------------\n");
	printf("%s", c->front);
	printf("\n---------------------------\n");

	while(boolean == 0 || boolean != 1){
		printf("Para visualizar o verso, digite 1:");
		scanf("%d", &boolean);
	}

	printf("\n---------------------------\n");
	printf("%s", c->back);
	printf("\n---------------------------\n");

	printf("Acertou?\n0 - nao\n1 - sim\n");
	scanf("%d", &boolean);

	recalc_cooldown(c, boolean);
}