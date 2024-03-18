#include "UI_UX.h"


void menu::init_containers(uint8_t num){
    UI_cont_ptr = (UI_container*)malloc(sizeof(UI_container)*num);

}

void menu::remove_containers(){
    free(UI_cont_ptr);
}