#include <stdio.h>
#include <stdlib.h>
#include <modbus.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {

modbus_t *ctx;
ctx = modbus_new_tcp("192.168.100.102", 502);
if(ctx==NULL){
printf("Unable to allocate libmodbus context\n");
return -1;
}
uint16_t tab_reg[20];
int rc,i;
modbus_set_debug(ctx, 1);
modbus_connect(ctx);

rc = modbus_read_registers(ctx, 0, 10, tab_reg);

if (rc == 10) {
printf("Read registers: ");
for (i=0; i<10; i++)
printf("%f\n", *(float*)tab_reg+i);
}
else {
   fprintf(stderr, "Failed to read registers: %s\n", modbus_strerror(errno));
}

modbus_close(ctx);
modbus_free(ctx);
return 0;
}
