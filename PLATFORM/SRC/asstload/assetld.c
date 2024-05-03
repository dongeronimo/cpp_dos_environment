#include "asstload/assetld.h"

#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <dos.h>

#define FILENAME_SIZE sizeof(char) * SHEET_FILENAME_SIZE

void write_asset(const char *path, character_sheet_desc_t *data) {
	FILE *f = NULL;
	f = fopen(path, "wb");
	assert(f != NULL);
	//Escreve o nome
	fwrite(data->filename, FILENAME_SIZE, 1, f);
	//Escreve a sprite list size
	fwrite(&data->sprite_list_size, sizeof(uint16_t), 1, f);
	//pra cada sprite, escrever no arquivo
	for (uint16_t i = 0; i < data->sprite_list_size; i++) {
		fwrite(&data->sprite_list[i], sizeof(sprite_desc_t), 1, f);
	}
	//escreve a qtd de animações
	fwrite(&data->animations_list_size, sizeof(uint16_t), 1, f);
	//escreve as animaçoes
	for (uint16_t i = 0; i < data->animations_list_size; i++) {
		fwrite(&data->animation_list[i], sizeof(animation_desc_t), 1, f);
	}
	fclose(f);
}
character_sheet_desc_t *load_asset(const char *path) {
	FILE *f = NULL;
	character_sheet_desc_t *data = malloc(sizeof(character_sheet_desc_t));
	f = fopen(path, "rb");
	//Lê o nome
	fread(data->filename, FILENAME_SIZE, 1, f);
	//lê o tamanho da sheet
	fread(&data->sprite_list_size, sizeof(uint16_t), 1, f);
	data->sprite_list = calloc(data->sprite_list_size, sizeof(sprite_desc_t));
	for (uint16_t i = 0; i < data->sprite_list_size; i++) {
		fread(&data->sprite_list[i], sizeof(sprite_desc_t), 1, f);
	}
	//le a qtd de animações
	fread(&data->animations_list_size, sizeof(uint16_t), 1, f);
	data->animation_list = calloc(data->animations_list_size, sizeof(animation_desc_t));
	//le as animações
	for (uint16_t i = 0; i < data->animations_list_size; i++) {
		fread(&data->animation_list[i], sizeof(animation_desc_t), 1, f);
	}
	fclose(f);
	return data;
}