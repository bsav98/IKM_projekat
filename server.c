#include <stdio.h>
#include <stdlib.h>
#include <modbus.h>
#include <errno.h>

/* Temperatura od Raspberry Pi */
float get_cpu_temp() {
   FILE *fp;
   float temp;
    fp = popen("/usr/bin/vcgencmd measure_temp | awk -F '=' '{print $2}'", "r");
   if (fp == NULL) {
      printf("Failed to get temperature\n" );
      exit(1);
 }
   fscanf(fp, "%f", &temp);
    pclose(fp);
    return temp;
}
/* Kraj */

int main(int argc, char *argv[]) {

modbus_t *ctx;
modbus_mapping_t *mb_mapping;
int socket,i;
float temp;
uint16_t tab_reg[20];

printf("starting modbus server\n");
ctx = modbus_new_tcp(NULL, 502);
if(ctx==NULL){
printf("Unable to allocate libmodbus context\n");
return -1;
}
modbus_set_debug(ctx, 1);

mb_mapping = modbus_mapping_new(0, 0, 20, 0);
socket = modbus_tcp_listen(ctx, 1);
modbus_tcp_accept(ctx, &socket);

for (i = 0; i < 10; i=i+1)
{
modbus_set_float_dcba(temp=get_cpu_temp()+0.5, mb_mapping->tab_registers+i);
// printf("%f\n",*(float*)mb_mapping->tab_registers+i);
}

for (;;) {
    uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];
    int rc;

    rc = modbus_receive(ctx, query);
    if (rc > 0) {
        modbus_reply(ctx, query, rc, mb_mapping);
    } else if (rc == -1) {
        break;
    }
}

printf("Quit the loop: %s\n", modbus_strerror(errno));

modbus_mapping_free(mb_mapping);
modbus_close(ctx);
modbus_free(ctx);

return 0;
}